import Utils._
import source_sequence_wise_processing.Scan_RFCO
import org.apache.spark.sql.functions
import confgen.Config._
import org.apache.spark.ml._
import source_sequence_wise_processing.Scan_TC40
import scala.util.parsing.json._
import org.apache.spark.sql
import com.amazonaws.auth.profile.ProfileCredentialsProvider
import org.apache.spark.ml.param.ParamMap
import source_sequence_wise_processing.Scan_SMSDRF
import source_sequence_wise_processing.Scan_TC50
import com.amazonaws.services.s3.model._
import org.apache.spark.sql.functions._
import org.apache.spark.SparkContext._
import source_sequence_wise_processing.graph_audit.Read_Log_
import org.apache.spark.ml
import source_sequence_wise_processing.Reformat_out0
import org.apache.spark.ml.tuning.ParamGridBuilder
import org.apache.hadoop.fs.Path
import source_sequence_wise_processing.Scan_DRF
import java.io.FileWriter
import org.apache.spark.ml.feature._
import source_sequence_wise_processing.Reformat_out1
import org.apache.hadoop.fs.s3native.NativeS3FileSystem
import org.apache.spark.SparkConf
import org.apache.spark.sql.types._
import source_sequence_wise_processing.Scan_TC1020
import org.apache.spark.sql.SparkSession
import org.apache.spark.ml.tuning._
import com.amazonaws.services.s3._
import org.apache.spark.ml.evaluation._
import org.apache.spark.sql.expressions.UserDefinedFunction
import org.apache.spark.ml.clustering._
import source_sequence_wise_processing.Scan_TC3839
import com.amazonaws.auth.BasicAWSCredentials
import scala.collection.mutable
import org.apache.spark.sql.DataFrame
import za.co.absa.cobrix.spark.cobol.utils.SparkUtils
import org.apache.spark.SparkContext
import java.io.File
import org.apache.spark.sql.SQLContext
import java.net.URI
import scala.collection.JavaConversions._
import source_sequence_wise_processing.graph_audit.Select_Records
import org.apache.hadoop.fs.FileSystem
import source_sequence_wise_processing.Scan_B2OTC
import source_sequence_wise_processing.Scan_SMSOTC
import source_sequence_wise_processing.Scan_TC04
import com.amazonaws.AmazonServiceException
import org.apache.commons.lang.StringEscapeUtils.escapeJava
import org.apache.spark.sql.Row
import org.apache.spark.ml.classification._
import Defs._

package source_sequence_wise_processing {
object Reformat_out1 {
  def Reformat_out1_Graph(spark: SparkSession, out1_source_sequence_wise_processing_reformat: DataFrame): DataFrame = {
    val variables = Map[String, Any]()
    import spark.implicits._  /* Source Sequence_wise_Processing.Reformat_out1 */
  lazy val t25 = out1_source_sequence_wise_processing_reformat.select(concat(substring(col("BR_AUDT_TYPE1"), 1, 6), lit(" "), substring(col("BR_AUDT_TYPE1"), 8, 1)).as("BR_AUDT_TYPE1"),
col("*"))
  lazy val t26 = t25.select($"BR_AUDT_YY",
$"BR_AUDT_MM",
$"BR_AUDT_DD",
$"BR_AUDT_TYPE1",
$"BR_AUDT_TYPE2",
$"BR_AUDT_VIC",
$"BR_IO_FLAG",
$"BR_AUDT_COUNT_1",
$"BR_AUDT_AMOUNT_1",
$"BR_AUDT_COUNT_2",
$"BR_AUDT_AMOUNT_2",
$"BR_AUDT_COUNT_3",
$"BR_AUDT_AMOUNT_3",
$"BR_AUDT_COUNT_4",
$"BR_AUDT_AMOUNT_4",
$"BR_AUDT_COUNT_5",
$"BR_AUDT_AMOUNT_5",
$"BR_AUDT_COUNT_6",
$"BR_AUDT_AMOUNT_6",
$"BR_AUDT_COUNT_7",
$"BR_AUDT_AMOUNT_7",
$"BR_AUDT_COUNT_8",
$"BR_AUDT_AMOUNT_8",
$"BR_AUDT_COUNT_9",
$"BR_AUDT_AMOUNT_9",
$"BR_AUDT_COUNT_10",
$"BR_AUDT_AMOUNT_10",
$"BR_AUDT_FILLER")
  lazy val out_source_sequence_wise_processing_reformat_out1 = t26
    out_source_sequence_wise_processing_reformat_out1
}
}
}

