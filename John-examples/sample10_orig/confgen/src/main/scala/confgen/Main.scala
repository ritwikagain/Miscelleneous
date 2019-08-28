package confgen

/**
  Copyright SimpleDataLabs Inc
*/

import java.io.File
import java.nio.file.Files

import org.json4s.DefaultFormats
import org.json4s._
import scala.meta._
import org.json4s.native.JsonMethods.parse

import scala.collection.JavaConverters._
import scala.collection.mutable

object Main {
  implicit val formats = DefaultFormats

  sealed trait pConfig

  case class pSimple
  (
    kind      : String,
    key       : String,
    value     : String
  ) extends pConfig

  case class pTable
  (
    kind      : String,
    key       : String,
    value     : String,
    database  : Option[String],
    partition : Option[String]
  ) extends pConfig

  case class pFile
  (
    kind      : String,
    key       : String,
    value     : String,
    path      : Option[String]
  ) extends pConfig {
    def fullPath: String = if (path.isDefined) path.get + "/" + value else value
  }

  case class pConfigs
  (
    initial   : Array[pConfig],
    derived   : Array[pConfig]
  )

 def main(args: Array[String]): Unit = {
    //val args = args1.head.split(";")
    if (args.length < 2) throw new Exception("Expect atleast 1 source.json and target.scala")
    //if (! args(1).endsWith(".json")  ) throw new Exception("First arg should be source.json")
    if (! args(0).endsWith(".scala") ) throw new Exception("First arg should be target.scala")
    val targetScala  = args(0)
 
    val propMap = mutable.Map[String, pConfig]()
    args.tail.map { configJson =>
      // read & parse config
      val cFile = new File(configJson)
      val contents = Files.readAllLines(cFile.toPath).asScala.mkString("\n")
      val jsonContents = parse(contents)
 
      def parsePropertyArray(jContents: JValue, name: String): Array[pConfig] = {
        val initialProps = (jContents \ name).asInstanceOf[JArray]
        initialProps.arr.map { v ⇒
          (v \ "kind").asInstanceOf[JString].s match {
            case "simple" ⇒ v.extract[pSimple]
            case "table" ⇒ v.extract[pTable]
            case "file" ⇒ v.extract[pFile]
            case x ⇒ throw new Exception(s"Unknown type $x")
          }
        }.toArray
      }
 
      val initial = parsePropertyArray(jsonContents, "initial")
      val derived = parsePropertyArray(jsonContents, "derived")
 
      val configs = pConfigs(initial, derived)
 
      // process configs
 
      // simple properties are just written
      for (config ← configs.initial) {
        config match {
          case pSimple(_, key: String, _) ⇒ propMap(key) = config
          case pTable(_, key: String, _, _, _) ⇒ propMap(key) = config
          case pFile(_, key: String, _, _) ⇒ propMap(key) = config
        }
      }
 
      // write a resolve to replace references by their values
      def resolve(prop: String): String = {
        var p = prop
        var break = false
        while (p.contains('$') && !break) {
          val rx = "\\$[A-Za-z_]*".r
          val matches = rx.findFirstMatchIn(p)
          if (matches.isEmpty) {
            break = true
          } else {
            val key = matches.get.matched
            val value = propMap.get(key.replace("$", ""))
            if (value.isEmpty) throw new Exception(s"Missing $key")
            value.get match {
              case pSimple(kind: String, key: String, value: String) ⇒ p = rx.replaceFirstIn(p, value)
              case _ ⇒ throw new Exception(s"Can only depends on simple properties $key")
            }
          }
        }
        p
      }
 
      // replace references before storing derived properties
      for (config ← configs.derived) {
        config match {
          case x@pSimple(kind: String,
          key: String,
          value: String) ⇒
            propMap(key) = x.copy(value = resolve(value))
 
          case x@pTable(kind: String,
          key: String,
          value: String,
          database: Option[String],
          partition: Option[String]) ⇒
            propMap(key) = x.copy(database = database.map(y ⇒ resolve(y)), partition = partition.map(y ⇒ resolve(y)))
 
          case x@pFile(kind: String,
          key: String,
          value: String,
          path: Option[String]) ⇒
            propMap(key) = x.copy(path = path.map(y ⇒ resolve(y)), value = resolve(value))
        }
      }
    }
    val simples = propMap.filter(_._2.isInstanceOf[pSimple])
    val tables  = propMap.filter(_._2.isInstanceOf[pTable])
    val files   = propMap.filter(_._2.isInstanceOf[pFile])

    val simplesString = simples.map{ case (k: String ,v: pSimple) ⇒ s"""val $k = "${v.value}" """.trim }
    val filesString   = files.map  { case (k: String ,v: pFile)   ⇒ s"""val $k = "${v.fullPath}" """.trim }
    val tablesString  = tables.map { case (k: String ,v: pTable)  ⇒ s"""val $k = Table("${v.database.get}", "${v.value}", "${v.partition.get}") """.trim }

    val configSource = s"""package confgen

case class Table
(
  database  : String,
  table     : String,
  partition : String
)

object Config {

  // simple variables
  ${simplesString.mkString("\n  ")}

  // files
  ${filesString.mkString("\n  ")}

  // database tables
  ${tablesString.mkString("\n  ")}
}
"""
    // create legit Scala
    val srcContents = configSource.parse[Source].get.syntax.getBytes("UTF-8")

    val jfile = new File(targetScala)
    jfile.getParentFile.mkdirs()
    // Do scala.meta code generation here.
    Files.write(jfile.toPath, srcContents)
  }
}