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

package source_sequence_wise_processing.graph_audit {
object Read_Log_ {
  def Read_Log__Graph(spark: SparkSession, out_source_sequence_wise_processing_gather: DataFrame): DataFrame = {
    val variables = Map[String, Any]()
    import spark.implicits._  /* Source Sequence_wise_Processing.Graph_Audit.Read_Log_ */
def Sequence_wise_Processing__Graph_Audit__Read_Log__componentUdf(event_type: String, event_text: String) = {
  return "component"
}
def Sequence_wise_Processing__Graph_Audit__Read_Log__componentUdf(event_type: String, event_text: String) = {
  return "component"
}
def Sequence_wise_Processing__Graph_Audit__Read_Log__componentUdf(event_type: String, event_text: String) = {
  return "component"
}
def Sequence_wise_Processing__Graph_Audit__Read_Log__componentUdf(event_type: String, event_text: String) = {
  return "component"
}
def Sequence_wise_Processing__Graph_Audit__Read_Log__componentUdf(event_type: String, event_text: String) = {
  return "component"
}
def Sequence_wise_Processing__Graph_Audit__Read_Log__componentUdf(event_type: String, event_text: String) = {
  return "component"
}
def Sequence_wise_Processing__Graph_Audit__Read_Log__componentUdf(event_type: String, event_text: String) = {
  return "component"
}
def Sequence_wise_Processing__Graph_Audit__Read_Log__componentUdf(event_type: String, event_text: String) = {
  return "component"
}
def Sequence_wise_Processing__Graph_Audit__Read_Log__componentUdf(event_type: String, event_text: String) = {
  return "component"
}
def Sequence_wise_Processing__Graph_Audit__Read_Log__componentUdf(event_type: String, event_text: String) = {
  return "component"
}
  lazy val t21 = out_source_sequence_wise_processing_gather.select(col("RUN_DATE").as("run_date"),
col("std_log_text.no_of_records_read").as("tran_count"),
col("*"))
  lazy val t22 = t21.select($"run_date",
$"tran_count")
  lazy val out_source_sequence_wise_processing_graph_audit_read_log_ = t22
    out_source_sequence_wise_processing_graph_audit_read_log_
}
}
}

