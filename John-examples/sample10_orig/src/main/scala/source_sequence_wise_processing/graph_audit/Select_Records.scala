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
object Select_Records {
  def Select_Records_Graph(spark: SparkSession, out_source_sequence_wise_processing_unix_rsi_audit_file: DataFrame): DataFrame = {
    val variables = Map[String, Any]()
    import spark.implicits._  /* Source Sequence_wise_Processing.Graph_Audit.Select_Records */
  lazy val t17 = out_source_sequence_wise_processing_unix_rsi_audit_file.select(col("run_date").as("run_date"),
col("file_name").as("name"),
col("tran_count").as("tran_count"),
col("new_line").as("newline"),
col("*"))
  lazy val t18 = t17.select($"run_date",
$"name",
$"tran_count",
$"newline")
  lazy val out_source_sequence_wise_processing_graph_audit_select_records = t18
    out_source_sequence_wise_processing_graph_audit_select_records
}
}
}

