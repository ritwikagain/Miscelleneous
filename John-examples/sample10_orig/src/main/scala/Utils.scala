import java.net.URI

import org.apache.hadoop.fs.{FileSystem, Path}
import org.apache.hadoop.fs.permission.{FsAction, FsPermission}
import org.apache.spark.sql.expressions.UserDefinedFunction
import org.apache.spark.sql.{DataFrame, SparkSession, functions}

import scala.collection.{immutable, mutable}
import scala.util.matching.Regex

trait UserDefinedType[T <: UserDefinedType[T]] extends Serializable

trait UserDefinedTypeFactory[T <: UserDefinedType[T]] extends Serializable {
  def parse(str: String): T
}

object Utils {
  private val COLUMN_MAP = mutable.Map[String, mutable.Map[String, String]]()
  private val regex: Regex = "[a-zA-Z0-9_]*".r
  private val underScoreRegex: Regex = "[_]*".r

  private def validName(name: String): Boolean = {
    val matcher = regex.pattern.matcher(name)
    if (matcher == null || !matcher.matches()) {
      return false
    }
    val usMatcher = underScoreRegex.pattern.matcher(name)
    if (usMatcher != null && usMatcher.matches()) {
      return false
    }
    true
  }

  def cleanData(df: DataFrame, spark: SparkSession): DataFrame = {
    val columns = df.dtypes
    df.select(
      columns.map {
        case (column, colType) ⇒ {
          colType match {
            case "StringType" ⇒ functions.regexp_replace(df(column), "[^\\p{Print}&&[^~,]]" /*"^[a-zA-Z0-9_]*"*/ , "").as(column)
            case _ ⇒ df(column)
          }
        }
      }: _*
    )
  }

  private def fixName(name: String): String = {
    name.replaceAll("[^A-Za-z0-9]", "_")
  }

  def cleanColumnNames(df: DataFrame, dfName: String): DataFrame = {
    val columns = df.columns
    if (!COLUMN_MAP.contains(dfName)) {
      COLUMN_MAP(dfName) = mutable.Map[String, String]()
    }
    COLUMN_MAP(dfName).clear()
    val newColumns: Array[(String, String)] = columns.map {
      name ⇒ {
        val newName: String = {
          if (!validName(name)) {
            val newName = fixName(name)
            println(s"OLD_NAME: ${name}, NEW_NAME: ${newName}")
            COLUMN_MAP(dfName).update(name, newName)
            newName
          } else {
            name
          }
        }
        (name, newName)
      }
    }
    df.select(
      newColumns.map {
        case (k, v) ⇒ {
          if (k == v)
            df(k)
          else
            df(k).as(v)
        }
      }: _*
    )
  }

  def writeDataFrame
  (
    df: DataFrame,
    path: String,
    spark: SparkSession,
    props: immutable.Map[String, String],
    format: String,
    partitionColumns: List[String] = Nil,
    bucketColumns: List[String] = Nil,
    numBuckets: Option[Int] = None,
    sortColumns: List[String] = Nil,
    tableName: Option[String] = None,
    databaseName: Option[String] = None
  ) = {
    val newPathStr = cleanDir(spark, path)
    val writer = df.repartition(10).write.options(props)
    writer.partitionBy(partitionColumns: _*)
    numBuckets match {
      case None ⇒ //ignore
      case Some(b) ⇒ writer.bucketBy(b, bucketColumns.head, bucketColumns.tail: _*)
    }
    if (sortColumns.nonEmpty) {
      writer.sortBy(sortColumns.head, sortColumns.tail: _*)
    }
    format match {
      case "csv" ⇒ writer.format("csv")
      case "text" ⇒ writer.format("text")
      case "json" ⇒ writer.format("json")
      case "parquet" ⇒ writer.format("parquet")
      case "orc" ⇒ writer.format("orc")
      case _ ⇒ //ignore
    }
    writer.option("path", newPathStr)
    tableName match {
      case None ⇒ writer.save(newPathStr)
      case Some(table) ⇒ {
        databaseName match {
          case None ⇒ writer.saveAsTable(table)
          case Some(dbName) ⇒ writer.saveAsTable(s"$dbName.$table")
        }
      }
    }
    makeReadable(newPathStr, spark)
  }

  private def cleanDir(spark: SparkSession, path: String): String = {
    val newPathStr = if (path.contains("://")) {
      path
    } else {
      "file://" + path
    }
    val fileSystem: FileSystem = getFileSystem(spark, newPathStr)
    val newPath = new Path(newPathStr)
    if (fileSystem.exists(newPath)) {
      fileSystem.delete(newPath, true)
    }
    newPathStr
  }

  private def makeReadable(path: String, spark: SparkSession) = {
    val fs = getFileSystem(spark, path)
    fs.setPermission(new Path(path), new FsPermission(FsAction.ALL, FsAction.ALL, FsAction.ALL))
  }

  private def getFileSystem(spark: SparkSession, path: String): FileSystem = {
    val hadoopConf = spark.sparkContext.hadoopConfiguration
    FileSystem.get(new URI(path), hadoopConf)
  }

  def unionAll(df: DataFrame*): DataFrame = {
    var tmp: DataFrame = null
    val dfs = df.map{x ⇒ x.checkpoint(true)}
    dfs.foreach {
      x ⇒ {
        if (tmp == null) {
          tmp = x
        } else {
          tmp = tmp.union(x)
        }
        tmp = tmp.checkpoint(true)
      }
    }
    tmp.checkpoint(true)
  }

  def reinterpret_as[T <: UserDefinedType[T]](factory: UserDefinedTypeFactory[T])(str: String): T = {
    val c = factory.parse(str)
    c
  }

  lazy val write_to_log: UserDefinedFunction = functions.udf {
    (name: String, line: String) ⇒ 1
  }
}