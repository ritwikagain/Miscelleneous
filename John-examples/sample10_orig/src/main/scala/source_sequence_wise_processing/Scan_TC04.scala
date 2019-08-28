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
object Scan_TC04 {
  def Scan_TC04_Graph(spark: SparkSession, out_source_sequence_wise_processing_base_ii_cmls_tc04_data: DataFrame): DataFrame = {
    val variables = Map[String, Any]()
    import spark.implicits._  /* Source Sequence_wise_Processing.Scan_TC04 */
  lazy val t15 = out_source_sequence_wise_processing_base_ii_cmls_tc04_data.select(substring(col("CMLS_CPD_DT"), 3, 2).as("BR_AUDT_YY"),
substring(col("CMLS_CPD_DT"), 5, 2).as("BR_AUDT_MM"),
substring(col("CMLS_CPD_DT"), 7, 2).as("BR_AUDT_DD"),
concat(col("CMLS_TRAN_CD"), when(col("CMLS_TRAN_CD") === lit("05") or col("CMLS_TRAN_CD") === lit("06") or col("CMLS_TRAN_CD") === lit("07"), when(col("CMLS_TRAN_DRCTN") === lit("SS"), when(col("CMLS_POSCOND_CD") =!= lit("13"), lit("1")).otherwise(lit("2"))).otherwise(when(col("CMLS_USAGE_CD") === lit("1"), lit("1")).otherwise(lit("2")))).otherwise(lit(" ")), when(col("CMLS_SETLMT_SVC_ID") === lit(1), lit("I")).otherwise(lit("N")), when(col("CMLS_RTRN_RSN_FLG") =!= lit(" "), lit("R")).otherwise(lit(" ")), when(col("CMLS_RTRN_RSN_FLG") === lit(" "), when(col("CMLS_ACCT_USAGE_CD") === lit("C"), lit("C")).otherwise(when(col("CMLS_ACCT_USAGE_CD") === lit("D") or col("CMLS_ACCT_USAGE_CD") === lit("F"), lit("D")).otherwise(lit(" ")))).otherwise(lit(" ")), col("CMLS_COLL_FLG"), when(col("CMLS_TRAN_DRCTN") === lit("BB"), lit("B")).otherwise(when(col("CMLS_TRAN_DRCTN") === lit("SB"), lit("F")).otherwise(when(col("CMLS_TRAN_DRCTN") === lit("BS"), lit("R")).otherwise(lit("S"))))).as("BR_AUDT_TYPE1"),
col("CMLS_DEST_BIN_REGN_CD").as("BR_AUDT_TYPE2"),
col("CMLS_VIC").as("BR_AUDT_VIC"),
lit("R").as("BR_IO_FLAG"),
when(substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("01") or substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("02") or substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("03"), lit(1)).otherwise(lit(0)).as("BR_AUDT_COUNT_1"),
when(substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("01") or substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("02") or substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("03"), when(col("CMLS_COLL_FLG") === lit("C"), col("CMLS_US_CDI_TRAN_AMT")).otherwise(col("CMLS_SETLMT_SRCE_AMT_USD"))).otherwise(lit(0)).as("BR_AUDT_AMOUNT_1"),
when(substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("04") or substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("05") or substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("06"), lit(1)).otherwise(lit(0)).as("BR_AUDT_COUNT_2"),
when(substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("04") or substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("05") or substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("06"), when(col("CMLS_COLL_FLG") === lit("C"), col("CMLS_US_CDI_TRAN_AMT")).otherwise(col("CMLS_SETLMT_SRCE_AMT_USD"))).otherwise(lit(0)).as("BR_AUDT_AMOUNT_2"),
when(substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("07") or substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("08") or substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("09"), lit(1)).otherwise(lit(0)).as("BR_AUDT_COUNT_3"),
when(substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("07") or substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("08") or substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("09"), when(col("CMLS_COLL_FLG") === lit("C"), col("CMLS_US_CDI_TRAN_AMT")).otherwise(col("CMLS_SETLMT_SRCE_AMT_USD"))).otherwise(lit(0)).as("BR_AUDT_AMOUNT_3"),
when(substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("10") or substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("11") or substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("12"), lit(1)).otherwise(lit(0)).as("BR_AUDT_COUNT_4"),
when(substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("10") or substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("11") or substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("12"), when(col("CMLS_COLL_FLG") === lit("C"), col("CMLS_US_CDI_TRAN_AMT")).otherwise(col("CMLS_SETLMT_SRCE_AMT_USD"))).otherwise(lit(0)).as("BR_AUDT_AMOUNT_4"),
when(substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("13") or substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("14") or substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("15"), lit(1)).otherwise(lit(0)).as("BR_AUDT_COUNT_5"),
when(substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("13") or substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("14") or substring(col("CMLS_TRAN_SEQ_ID"), 2, 2) === lit("15"), when(col("CMLS_COLL_FLG") === lit("C"), col("CMLS_US_CDI_TRAN_AMT")).otherwise(col("CMLS_SETLMT_SRCE_AMT_USD"))).otherwise(lit(0)).as("BR_AUDT_AMOUNT_5"),
lit(0).as("BR_AUDT_COUNT_6"),
lit(0).as("BR_AUDT_AMOUNT_6"),
lit(0).as("BR_AUDT_COUNT_7"),
lit(0).as("BR_AUDT_AMOUNT_7"),
lit(0).as("BR_AUDT_COUNT_8"),
lit(0).as("BR_AUDT_AMOUNT_8"),
lit(0).as("BR_AUDT_COUNT_9"),
lit(0).as("BR_AUDT_AMOUNT_9"),
lit(0).as("BR_AUDT_COUNT_10"),
lit(0).as("BR_AUDT_AMOUNT_10"),
lit("").as("BR_AUDT_FILLER"),
col("*"))
  lazy val t16 = t15.select($"BR_AUDT_YY",
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
$"CMLS_DEST_FLG",
$"CMLS_SETLMT_SVC_ID",
$"CMLS_SETLMT_CD",
$"BR_AUDT_FILLER")
  lazy val out_source_sequence_wise_processing_scan_tc04 = t16
    out_source_sequence_wise_processing_scan_tc04
}
}
}

