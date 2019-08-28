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



object sample10orig {
  val variables = Map[String, Any]()

def sample10origGraph(): Unit = {
  val spark: SparkSession = SparkSession.builder()
                            .appName("sample10orig")
                            .config("hive.metastore.uris", "")

                            .enableHiveSupport()
                            .getOrCreate()
  val sc = spark.sparkContext
  implicit val impSpark = spark
  import spark.implicits._
  val hadoopConf = sc.hadoopConfiguration
  //
  // instructions for the main workflow
  //
  
  /* Source Sequence_wise_Processing.Base2_Others_UNIX_File */
  lazy val tmp0 = spark.read
    .option("header", true)
    .option("sep", ",")
    .option("inferSchema", true)
    .csv("DERIVED_PARAM_B2OTC_FILE_LIST").cache()
    val out_source_sequence_wise_processing_base2_others_unix_file = tmp0
  /* Source Sequence_wise_Processing.Base2_TC40_UNIX_File */
  lazy val tmp1 = spark.read
    .option("header", true)
    .option("sep", ",")
    .option("inferSchema", true)
    .csv("DERIVED_PARAM_B2TC40_FILE_LIST").cache()
    val out_source_sequence_wise_processing_base2_tc40_unix_file = tmp1
  /* Source Sequence_wise_Processing.Scan_TC40log */
  lazy val out_source_sequence_wise_processing_scan_tc40log = out_source_sequence_wise_processing_base2_tc40_unix_file.select(lit("Sequence_wise_Processing__Scan_TC40").as("component"),
lit("finish").as("event_type"),
count("*").as("no_of_records_read"),
count("*").as("no_of_records_written"),
count("*").as("no_of_records_rejected"))
  /* Source Sequence_wise_Processing.Base_II_SMSOTC_Data */
  lazy val tmp2 = spark.read
    .option("header", true)
    .option("sep", ",")
    .option("inferSchema", true)
    .csv("DERIVED_PARAM_B2SMSOTC_FILE_LIST").cache()
    val out_source_sequence_wise_processing_base_ii_smsotc_data = tmp2
  /* Source End_of_Day_Processing.PEAK_Files_for_All_Day */
  lazy val tmp3 = spark.read
    .option("header", true)
    .option("sep", ",")
    .option("inferSchema", true)
    .csv("DERIVED_PARAM_PEAK_FILE_LIST").cache()
    val out_source_end_of_day_processing_peak_files_for_all_day = tmp3
  /* 90_Union_n76_in */
  lazy val out_90_union_n76_in = out_source_end_of_day_processing_peak_files_for_all_day
val out_source_sequence_wise_processing_scan_b2otc = Scan_B2OTC.Scan_B2OTC_Graph(spark, out_source_sequence_wise_processing_base2_others_unix_file)
  /* Source Sequence_wise_Processing.Base_II_CMLS_TC04_Data */
  lazy val tmp4 = spark.read
    .option("header", true)
    .option("sep", ",")
    .option("inferSchema", true)
    .csv("DERIVED_PARAM_B2TC04_FILE_LIST").cache()
    val out_source_sequence_wise_processing_base_ii_cmls_tc04_data = tmp4
  /* Source Sequence_wise_Processing.Scan_TC04log */
  lazy val out_source_sequence_wise_processing_scan_tc04log = out_source_sequence_wise_processing_base_ii_cmls_tc04_data.select(lit("Sequence_wise_Processing__Scan_TC04").as("component"),
lit("finish").as("event_type"),
count("*").as("no_of_records_read"),
count("*").as("no_of_records_written"),
count("*").as("no_of_records_rejected"))
  /* Source Sequence_wise_Processing.Base2_3839_UNIX_File */
  lazy val tmp5 = spark.read
    .option("header", true)
    .option("sep", ",")
    .option("inferSchema", true)
    .csv("DERIVED_PARAM_B2TC3839_FILE_LIST").cache()
    val out_source_sequence_wise_processing_base2_3839_unix_file = tmp5
val out_source_sequence_wise_processing_scan_tc3839 = Scan_TC3839.Scan_TC3839_Graph(spark, out_source_sequence_wise_processing_base2_3839_unix_file)
  /* Source Sequence_wise_Processing.Unix_RSI_Audit_File */
  lazy val tmp6 = spark.read
    .option("header", true)
    .option("sep", ",")
    .option("inferSchema", true)
    .csv("DERIVED_PARAM_AUDIT_FILE_LIST").cache()
    val out_source_sequence_wise_processing_unix_rsi_audit_file = tmp6
  /* Source Sequence_wise_Processing.Graph_Audit.Select_Recordslog */
  lazy val out_source_sequence_wise_processing_graph_audit_select_recordslog = out_source_sequence_wise_processing_unix_rsi_audit_file.select(lit("Sequence_wise_Processing__Graph_Audit__Select_Records").as("component"),
lit("finish").as("event_type"),
count("*").as("no_of_records_read"),
count("*").as("no_of_records_written"),
count("*").as("no_of_records_rejected"))
  /* Source End_of_Day_Processing.Rolup_ */
  lazy val tmp7 = out_90_union_n76_in.groupBy(col("BR_AUDT_YY"),col("BR_AUDT_MM"),col("BR_AUDT_TYPE1"),col("BR_AUDT_TYPE2"),col("BR_AUDT_VIC"),col("BR_IO_FLAG"))
  lazy val out_source_end_of_day_processing_rolup_ = tmp7.agg(sum(col("BR_AUDT_COUNT_1")).as("BR_AUDT_COUNT_1"),sum(col("BR_AUDT_AMOUNT_1")).as("BR_AUDT_AMOUNT_1"),sum(col("BR_AUDT_COUNT_2")).as("BR_AUDT_COUNT_2"),sum(col("BR_AUDT_AMOUNT_2")).as("BR_AUDT_AMOUNT_2"),sum(col("BR_AUDT_COUNT_3")).as("BR_AUDT_COUNT_3"),sum(col("BR_AUDT_AMOUNT_3")).as("BR_AUDT_AMOUNT_3"),sum(col("BR_AUDT_COUNT_4")).as("BR_AUDT_COUNT_4"),sum(col("BR_AUDT_AMOUNT_4")).as("BR_AUDT_AMOUNT_4"),sum(col("BR_AUDT_COUNT_5")).as("BR_AUDT_COUNT_5"),sum(col("BR_AUDT_AMOUNT_5")).as("BR_AUDT_AMOUNT_5"))
  /* Source End_of_Day_Processing.Sort */
  lazy val out_source_end_of_day_processing_sort = out_source_end_of_day_processing_rolup_.sortWithinPartitions(col("BR_AUDT_YY"),col("BR_AUDT_MM"),col("BR_AUDT_DD"),col("BR_AUDT_TYPE1"),col("BR_AUDT_TYPE2"),col("BR_AUDT_VIC"),col("BR_IO_FLAG"))
  /* Source End_of_Day_Processing.Intermediate_File_2 */
  lazy val tmp8 = out_source_end_of_day_processing_sort.select(
struct(struct(col("BR_AUDT_YY").as("BR_AUDT_YY"), col("BR_AUDT_MM").as("BR_AUDT_MM"), col("BR_AUDT_DD").as("BR_AUDT_DD")).as("BR_AUDT_ODATE"), col("BR_AUDT_TYPE1").as("BR_AUDT_TYPE1"), col("BR_AUDT_TYPE2").as("BR_AUDT_TYPE2"), col("BR_AUDT_VIC").as("BR_AUDT_VIC"), col("BR_IO_FLAG").as("BR_IO_FLAG")).as("BR_AUDT_KEY"),
    struct(col("BR_AUDT_COUNT_1").as("BR_AUDT_COUNT_1"), col("BR_AUDT_AMOUNT_1").as("BR_AUDT_AMOUNT_1"), col("BR_AUDT_COUNT_2").as("BR_AUDT_COUNT_2"), col("BR_AUDT_AMOUNT_2").as("BR_AUDT_AMOUNT_2"), col("BR_AUDT_COUNT_3").as("BR_AUDT_COUNT_3"), col("BR_AUDT_AMOUNT_3").as("BR_AUDT_AMOUNT_3"), col("BR_AUDT_COUNT_4").as("BR_AUDT_COUNT_4"), col("BR_AUDT_AMOUNT_4").as("BR_AUDT_AMOUNT_4"), col("BR_AUDT_COUNT_5").as("BR_AUDT_COUNT_5"), col("BR_AUDT_AMOUNT_5").as("BR_AUDT_AMOUNT_5"), col("BR_AUDT_COUNT_6").as("BR_AUDT_COUNT_6"), col("BR_AUDT_AMOUNT_6").as("BR_AUDT_AMOUNT_6"), col("BR_AUDT_COUNT_7").as("BR_AUDT_COUNT_7"), col("BR_AUDT_AMOUNT_7").as("BR_AUDT_AMOUNT_7"), col("BR_AUDT_COUNT_8").as("BR_AUDT_COUNT_8"), col("BR_AUDT_AMOUNT_8").as("BR_AUDT_AMOUNT_8"), col("BR_AUDT_COUNT_9").as("BR_AUDT_COUNT_9"), col("BR_AUDT_AMOUNT_9").as("BR_AUDT_AMOUNT_9"), col("BR_AUDT_COUNT_10").as("BR_AUDT_COUNT_10"), col("BR_AUDT_AMOUNT_10").as("BR_AUDT_AMOUNT_10")).as("BR_AUDT_COUNTS_AND_AMOUNTS"),
    col("BR_AUDT_FILLER").as("BR_AUDT_FILLER")  )
  writeDataFrame(tmp8, "file:ENV_PARAM_UNIX_TIM_GPFS/UX.DL.TIM.PEAK.COUNTS.DINPUT_PARAM_RUN_DATE", spark, Map("sep"->","), "csv")
  /* Source Sequence_wise_Processing.Draft_SMS_Data */
  lazy val tmp9 = spark.read
    .option("header", true)
    .option("sep", ",")
    .option("inferSchema", true)
    .csv("DERIVED_PARAM_B2SMSDRF_FILE_LIST").cache()
    val out_source_sequence_wise_processing_draft_sms_data = tmp9
  /* Source Sequence_wise_Processing.Scan_SMSDRFlog */
  lazy val out_source_sequence_wise_processing_scan_smsdrflog = out_source_sequence_wise_processing_draft_sms_data.select(lit("Sequence_wise_Processing__Scan_SMSDRF").as("component"),
lit("finish").as("event_type"),
count("*").as("no_of_records_read"),
count("*").as("no_of_records_written"),
count("*").as("no_of_records_rejected"))
  /* Source End_of_Day_Processing.PEAK_Files_for_All_Day_with_coll_flg */
  lazy val tmp10 = spark.read
    .option("header", true)
    .option("sep", ",")
    .option("inferSchema", true)
    .csv("DERIVED_PARAM_PEAK_FILE_LIST1").cache()
    val out_source_end_of_day_processing_peak_files_for_all_day_with_coll_flg = tmp10
val out_source_sequence_wise_processing_scan_smsotc = Scan_SMSOTC.Scan_SMSOTC_Graph(spark, out_source_sequence_wise_processing_base_ii_smsotc_data)
  /* Source Sequence_wise_Processing.Base2_1020_UNIX_File */
  lazy val tmp11 = spark.read
    .option("header", true)
    .option("sep", ",")
    .option("inferSchema", true)
    .csv("DERIVED_PARAM_TC1020_FILE_LIST").cache()
    val out_source_sequence_wise_processing_base2_1020_unix_file = tmp11
val out_source_sequence_wise_processing_scan_tc1020 = Scan_TC1020.Scan_TC1020_Graph(spark, out_source_sequence_wise_processing_base2_1020_unix_file)
  /* Source Sequence_wise_Processing.Base_II_CMLS_RFCO_Data */
  lazy val tmp12 = spark.read
    .option("header", true)
    .option("sep", ",")
    .option("inferSchema", true)
    .csv("DERIVED_PARAM_B2RFC_FILE_LIST").cache()
    val out_source_sequence_wise_processing_base_ii_cmls_rfco_data = tmp12
  /* Source Sequence_wise_Processing.Scan_RFCOlog */
  lazy val out_source_sequence_wise_processing_scan_rfcolog = out_source_sequence_wise_processing_base_ii_cmls_rfco_data.select(lit("Sequence_wise_Processing__Scan_RFCO").as("component"),
lit("finish").as("event_type"),
count("*").as("no_of_records_read"),
count("*").as("no_of_records_written"),
count("*").as("no_of_records_rejected"))
val out_source_sequence_wise_processing_scan_tc40 = Scan_TC40.Scan_TC40_Graph(spark, out_source_sequence_wise_processing_base2_tc40_unix_file)
  /* Source Sequence_wise_Processing.Base_II_TC50_Data */
  lazy val tmp13 = spark.read
    .option("header", true)
    .option("sep", ",")
    .option("inferSchema", true)
    .csv("DERIVED_PARAM_B2TC50_FILE_LIST").cache()
    val out_source_sequence_wise_processing_base_ii_tc50_data = tmp13
val out_source_sequence_wise_processing_scan_tc50 = Scan_TC50.Scan_TC50_Graph(spark, out_source_sequence_wise_processing_base_ii_tc50_data)
  /* Source Sequence_wise_Processing.Scan_TC50log */
  lazy val out_source_sequence_wise_processing_scan_tc50log = out_source_sequence_wise_processing_base_ii_tc50_data.select(lit("Sequence_wise_Processing__Scan_TC50").as("component"),
lit("finish").as("event_type"),
count("*").as("no_of_records_read"),
count("*").as("no_of_records_written"),
count("*").as("no_of_records_rejected"))
  /* Source Sequence_wise_Processing.Scan_TC1020log */
  lazy val out_source_sequence_wise_processing_scan_tc1020log = out_source_sequence_wise_processing_base2_1020_unix_file.select(lit("Sequence_wise_Processing__Scan_TC1020").as("component"),
lit("finish").as("event_type"),
count("*").as("no_of_records_read"),
count("*").as("no_of_records_written"),
count("*").as("no_of_records_rejected"))
val out_source_sequence_wise_processing_scan_smsdrf = Scan_SMSDRF.Scan_SMSDRF_Graph(spark, out_source_sequence_wise_processing_draft_sms_data)
  /* Source Sequence_wise_Processing.Scan_TC3839log */
  lazy val out_source_sequence_wise_processing_scan_tc3839log = out_source_sequence_wise_processing_base2_3839_unix_file.select(lit("Sequence_wise_Processing__Scan_TC3839").as("component"),
lit("finish").as("event_type"),
count("*").as("no_of_records_read"),
count("*").as("no_of_records_written"),
count("*").as("no_of_records_rejected"))
  /* Source Sequence_wise_Processing.Scan_B2OTClog */
  lazy val out_source_sequence_wise_processing_scan_b2otclog = out_source_sequence_wise_processing_base2_others_unix_file.select(lit("Sequence_wise_Processing__Scan_B2OTC").as("component"),
lit("finish").as("event_type"),
count("*").as("no_of_records_read"),
count("*").as("no_of_records_written"),
count("*").as("no_of_records_rejected"))
val out_source_sequence_wise_processing_scan_tc04 = Scan_TC04.Scan_TC04_Graph(spark, out_source_sequence_wise_processing_base_ii_cmls_tc04_data)
val out_source_sequence_wise_processing_graph_audit_select_records = Select_Records.Select_Records_Graph(spark, out_source_sequence_wise_processing_unix_rsi_audit_file)
  /* 92_Union_n56_in */
  lazy val out_92_union_n56_in = out_source_sequence_wise_processing_graph_audit_select_records
  /* Source Sequence_wise_Processing.Scan_SMSOTClog */
  lazy val out_source_sequence_wise_processing_scan_smsotclog = out_source_sequence_wise_processing_base_ii_smsotc_data.select(lit("Sequence_wise_Processing__Scan_SMSOTC").as("component"),
lit("finish").as("event_type"),
count("*").as("no_of_records_read"),
count("*").as("no_of_records_written"),
count("*").as("no_of_records_rejected"))
  /* Source Sequence_wise_Processing.Graph_Audit.Rollup_RSI_Audit_Record */
  lazy val tmp14 = out_92_union_n56_in.groupBy(col("name"))
  lazy val tmp15 = tmp14.agg(sum(col("tran_count")).as("tran_count"))
  lazy val out_source_sequence_wise_processing_graph_audit_rollup_rsi_audit_record = tmp15.select(col("*"), col("run_date"),col("name"),col("tran_count"))
val out_source_sequence_wise_processing_scan_rfco = Scan_RFCO.Scan_RFCO_Graph(spark, out_source_sequence_wise_processing_base_ii_cmls_rfco_data)
  /* Source Sequence_wise_Processing.Draft_B_II_Data */
  lazy val tmp16 = spark.read
    .option("header", true)
    .option("sep", ",")
    .option("inferSchema", true)
    .csv("DERIVED_PARAM_B2DRF_FILE_LIST").cache()
    val out_source_sequence_wise_processing_draft_b_ii_data = tmp16
  /* Source Sequence_wise_Processing.Scan_DRFlog */
  lazy val out_source_sequence_wise_processing_scan_drflog = out_source_sequence_wise_processing_draft_b_ii_data.select(lit("Sequence_wise_Processing__Scan_DRF").as("component"),
lit("finish").as("event_type"),
count("*").as("no_of_records_read"),
count("*").as("no_of_records_written"),
count("*").as("no_of_records_rejected"))
  /* Source Sequence_wise_Processing.Gather */
  lazy val out_source_sequence_wise_processing_gather = unionAll(out_source_sequence_wise_processing_scan_tc1020log, out_source_sequence_wise_processing_scan_tc04log, out_source_sequence_wise_processing_scan_b2otclog, out_source_sequence_wise_processing_scan_tc40log, out_source_sequence_wise_processing_scan_tc3839log, out_source_sequence_wise_processing_scan_rfcolog, out_source_sequence_wise_processing_scan_drflog, out_source_sequence_wise_processing_scan_smsdrflog, out_source_sequence_wise_processing_scan_tc50log, out_source_sequence_wise_processing_scan_smsotclog)
  /* Source Sequence_wise_Processing.Graph_Audit.Read_Log_log */
  lazy val out_source_sequence_wise_processing_graph_audit_read_log_log = out_source_sequence_wise_processing_gather.select(lit("Sequence_wise_Processing__Graph_Audit__Read_Log_").as("component"),
lit("finish").as("event_type"),
count("*").as("no_of_records_read"),
count("*").as("no_of_records_written"),
count("*").as("no_of_records_rejected"))
val out_source_sequence_wise_processing_graph_audit_read_log_ = Read_Log_.Read_Log__Graph(spark, out_source_sequence_wise_processing_gather)
  /* 93_Union_n41_in */
  lazy val out_93_union_n41_in = out_source_sequence_wise_processing_graph_audit_read_log_
  /* Source Sequence_wise_Processing.Graph_Audit.Rollup */
  lazy val tmp17 = out_93_union_n41_in.groupBy(col("run_date"),col("name"))
  lazy val tmp18 = tmp17.agg(sum(col("tran_count")).as("tran_count"))
  lazy val out_source_sequence_wise_processing_graph_audit_rollup = tmp18.select(col("*"), col("run_date"),col("name"),col("tran_count"))
  /* Source Sequence_wise_Processing.Graph_Audit.Ga_2 */
  lazy val out_source_sequence_wise_processing_graph_audit_ga_2 = out_source_sequence_wise_processing_graph_audit_rollup
  /* Source Sequence_wise_Processing.Graph_Audit.Audit_all */
  lazy val out_source_sequence_wise_processing_graph_audit_audit_all_tmp = out_source_sequence_wise_processing_graph_audit_rollup_rsi_audit_record.join(out_source_sequence_wise_processing_graph_audit_ga_2, out_source_sequence_wise_processing_graph_audit_rollup_rsi_audit_record("tran_count") === out_source_sequence_wise_processing_graph_audit_ga_2("tran_count"), "inner")

  lazy val out_source_sequence_wise_processing_graph_audit_audit_all = out_source_sequence_wise_processing_graph_audit_audit_all_tmp.select(when(col("tran_count") =!= col("tran_count") and write_to_log(col("name"), concat(lit("Audit Failed ::"), col("name"), lit("\nRecord Processed:"), col("tran_count"), lit("\n"), col("name"), lit("CS file has "), col("tran_count"), lit(" records"))), lit(1)).otherwise(lit(0)).as("error_count"),lit("CS").as("file_name"),col("run_date").as("run_date"),when(col("tran_count") === col("tran_count"), col("tran_count")).otherwise(lit(0)).as("record_count"))

  /* Source Sequence_wise_Processing.Graph_Audit.Trash_2 */
  lazy val out_source_sequence_wise_processing_graph_audit_trash_2 = out_source_sequence_wise_processing_graph_audit_audit_all.select("*")
val out_source_sequence_wise_processing_scan_drf = Scan_DRF.Scan_DRF_Graph(spark, out_source_sequence_wise_processing_draft_b_ii_data)
  /* 91_Union_n67_in */
  lazy val out_91_union_n67_in = unionAll(out_source_sequence_wise_processing_scan_tc50, out_source_sequence_wise_processing_scan_smsotc, out_source_sequence_wise_processing_scan_rfco, out_source_sequence_wise_processing_scan_tc40, out_source_sequence_wise_processing_scan_drf, out_source_sequence_wise_processing_scan_tc04, out_source_sequence_wise_processing_scan_smsdrf, out_source_sequence_wise_processing_scan_tc3839, out_source_sequence_wise_processing_scan_tc1020, out_source_sequence_wise_processing_scan_b2otc)
  /* Source Sequence_wise_Processing.Reformat */
  lazy val tmp19 = out_91_union_n67_in
  lazy val out0_source_sequence_wise_processing_reformat = tmp19.filter(when(col("CMLS_DEST_FLG") === col("D") and col("CMLS_SETLMT_SVC_ID") =!= lit(0) and col("CMLS_SETLMT_CD") =!= lit(3), lit(1)).otherwise(when(col("CMLS_DEST_FLG") === col("D") and col("CMLS_SETLMT_SVC_ID") === lit(0) and col("CMLS_SETLMT_CD") =!= lit(3), lit(0)).otherwise(lit(1).unary_-)) === lit(0))
  lazy val out1_source_sequence_wise_processing_reformat = tmp19.filter(when(col("CMLS_DEST_FLG") === col("D") and col("CMLS_SETLMT_SVC_ID") =!= lit(0) and col("CMLS_SETLMT_CD") =!= lit(3), lit(1)).otherwise(when(col("CMLS_DEST_FLG") === col("D") and col("CMLS_SETLMT_SVC_ID") === lit(0) and col("CMLS_SETLMT_CD") =!= lit(3), lit(0)).otherwise(lit(1).unary_-)) === lit(1))
  /* Source Sequence_wise_Processing.Reformat_out0log */
  lazy val out_source_sequence_wise_processing_reformat_out0log = out0_source_sequence_wise_processing_reformat.select(lit("Sequence_wise_Processing__Reformat").as("component"),
lit("finish").as("event_type"),
count("*").as("no_of_records_read"),
count("*").as("no_of_records_written"),
count("*").as("no_of_records_rejected"))
  /* Source Sequence_wise_Processing.Reformat_out1log */
  lazy val out_source_sequence_wise_processing_reformat_out1log = out1_source_sequence_wise_processing_reformat.select(lit("Sequence_wise_Processing__Reformat").as("component"),
lit("finish").as("event_type"),
count("*").as("no_of_records_read"),
count("*").as("no_of_records_written"),
count("*").as("no_of_records_rejected"))
val out_source_sequence_wise_processing_reformat_out1 = Reformat_out1.Reformat_out1_Graph(spark, out1_source_sequence_wise_processing_reformat)
val out_source_sequence_wise_processing_reformat_out0 = Reformat_out0.Reformat_out0_Graph(spark, out0_source_sequence_wise_processing_reformat)
  /* Source Sequence_wise_Processing.Rollup_ */
  lazy val tmp20 = out_source_sequence_wise_processing_reformat_out0.groupBy(col("BR_AUDT_YY"),col("BR_AUDT_MM"),col("BR_AUDT_TYPE1"),col("BR_AUDT_TYPE2"),col("BR_AUDT_VIC"),col("BR_IO_FLAG"))
  lazy val out_source_sequence_wise_processing_rollup_ = tmp20.agg(sum(col("BR_AUDT_COUNT_1")).as("BR_AUDT_COUNT_1"),sum(col("BR_AUDT_AMOUNT_1")).as("BR_AUDT_AMOUNT_1"),sum(col("BR_AUDT_COUNT_2")).as("BR_AUDT_COUNT_2"),sum(col("BR_AUDT_AMOUNT_2")).as("BR_AUDT_AMOUNT_2"),sum(col("BR_AUDT_COUNT_3")).as("BR_AUDT_COUNT_3"),sum(col("BR_AUDT_AMOUNT_3")).as("BR_AUDT_AMOUNT_3"),sum(col("BR_AUDT_COUNT_4")).as("BR_AUDT_COUNT_4"),sum(col("BR_AUDT_AMOUNT_4")).as("BR_AUDT_AMOUNT_4"),sum(col("BR_AUDT_COUNT_5")).as("BR_AUDT_COUNT_5"),sum(col("BR_AUDT_AMOUNT_5")).as("BR_AUDT_AMOUNT_5"))
  /* Source Sequence_wise_Processing.Sort_ */
  lazy val out_source_sequence_wise_processing_sort_ = out_source_sequence_wise_processing_rollup_.sortWithinPartitions(col("BR_AUDT_YY"),col("BR_AUDT_MM"),col("BR_AUDT_DD"),col("BR_AUDT_TYPE1"),col("BR_AUDT_TYPE2"),col("BR_AUDT_VIC"),col("BR_IO_FLAG"))
  /* Source Sequence_wise_Processing.Peak_Count_and_Amount_with_coll_flg */
  lazy val tmp21 = out_source_sequence_wise_processing_sort_.select(
struct(struct(col("BR_AUDT_YY").as("BR_AUDT_YY"), col("BR_AUDT_MM").as("BR_AUDT_MM"), col("BR_AUDT_DD").as("BR_AUDT_DD")).as("BR_AUDT_ODATE"), col("BR_AUDT_TYPE1").as("BR_AUDT_TYPE1"), col("BR_AUDT_TYPE2").as("BR_AUDT_TYPE2"), col("BR_AUDT_VIC").as("BR_AUDT_VIC"), col("BR_IO_FLAG").as("BR_IO_FLAG")).as("BR_AUDT_KEY"),
    struct(col("BR_AUDT_COUNT_1").as("BR_AUDT_COUNT_1"), col("BR_AUDT_AMOUNT_1").as("BR_AUDT_AMOUNT_1"), col("BR_AUDT_COUNT_2").as("BR_AUDT_COUNT_2"), col("BR_AUDT_AMOUNT_2").as("BR_AUDT_AMOUNT_2"), col("BR_AUDT_COUNT_3").as("BR_AUDT_COUNT_3"), col("BR_AUDT_AMOUNT_3").as("BR_AUDT_AMOUNT_3"), col("BR_AUDT_COUNT_4").as("BR_AUDT_COUNT_4"), col("BR_AUDT_AMOUNT_4").as("BR_AUDT_AMOUNT_4"), col("BR_AUDT_COUNT_5").as("BR_AUDT_COUNT_5"), col("BR_AUDT_AMOUNT_5").as("BR_AUDT_AMOUNT_5"), col("BR_AUDT_COUNT_6").as("BR_AUDT_COUNT_6"), col("BR_AUDT_AMOUNT_6").as("BR_AUDT_AMOUNT_6"), col("BR_AUDT_COUNT_7").as("BR_AUDT_COUNT_7"), col("BR_AUDT_AMOUNT_7").as("BR_AUDT_AMOUNT_7"), col("BR_AUDT_COUNT_8").as("BR_AUDT_COUNT_8"), col("BR_AUDT_AMOUNT_8").as("BR_AUDT_AMOUNT_8"), col("BR_AUDT_COUNT_9").as("BR_AUDT_COUNT_9"), col("BR_AUDT_AMOUNT_9").as("BR_AUDT_AMOUNT_9"), col("BR_AUDT_COUNT_10").as("BR_AUDT_COUNT_10"), col("BR_AUDT_AMOUNT_10").as("BR_AUDT_AMOUNT_10")).as("BR_AUDT_COUNTS_AND_AMOUNTS"),
    col("BR_AUDT_FILLER").as("BR_AUDT_FILLER")  )
  writeDataFrame(tmp21, "file:ENV_PARAM_UNIX_TIM_GPFS/INPUT_PARAM_HLQ.DL.TIM.PEAK.CNTCLF.SEQINPUT_PARAM_SEQ_NO.DINPUT_PARAM_RUN_DATE", spark, Map("sep"->","), "csv")
  /* Source Sequence_wise_Processing.Rllup */
  lazy val tmp22 = out_source_sequence_wise_processing_reformat_out1.groupBy(col("BR_AUDT_YY"),col("BR_AUDT_MM"),col("BR_AUDT_TYPE1"),col("BR_AUDT_TYPE2"),col("BR_AUDT_VIC"),col("BR_IO_FLAG"))
  lazy val out_source_sequence_wise_processing_rllup = tmp22.agg(sum(col("BR_AUDT_COUNT_1")).as("BR_AUDT_COUNT_1"),sum(col("BR_AUDT_AMOUNT_1")).as("BR_AUDT_AMOUNT_1"),sum(col("BR_AUDT_COUNT_2")).as("BR_AUDT_COUNT_2"),sum(col("BR_AUDT_AMOUNT_2")).as("BR_AUDT_AMOUNT_2"),sum(col("BR_AUDT_COUNT_3")).as("BR_AUDT_COUNT_3"),sum(col("BR_AUDT_AMOUNT_3")).as("BR_AUDT_AMOUNT_3"),sum(col("BR_AUDT_COUNT_4")).as("BR_AUDT_COUNT_4"),sum(col("BR_AUDT_AMOUNT_4")).as("BR_AUDT_AMOUNT_4"),sum(col("BR_AUDT_COUNT_5")).as("BR_AUDT_COUNT_5"),sum(col("BR_AUDT_AMOUNT_5")).as("BR_AUDT_AMOUNT_5"))
  /* Source Sequence_wise_Processing.Srt */
  lazy val out_source_sequence_wise_processing_srt = out_source_sequence_wise_processing_rllup.sortWithinPartitions(col("BR_AUDT_YY"),col("BR_AUDT_MM"),col("BR_AUDT_DD"),col("BR_AUDT_TYPE1"),col("BR_AUDT_TYPE2"),col("BR_AUDT_VIC"),col("BR_IO_FLAG"))
  /* Source Sequence_wise_Processing.Peak_Count_and_Amount */
  lazy val tmp23 = out_source_sequence_wise_processing_srt.select(
struct(struct(col("BR_AUDT_YY").as("BR_AUDT_YY"), col("BR_AUDT_MM").as("BR_AUDT_MM"), col("BR_AUDT_DD").as("BR_AUDT_DD")).as("BR_AUDT_ODATE"), col("BR_AUDT_TYPE1").as("BR_AUDT_TYPE1"), col("BR_AUDT_TYPE2").as("BR_AUDT_TYPE2"), col("BR_AUDT_VIC").as("BR_AUDT_VIC"), col("BR_IO_FLAG").as("BR_IO_FLAG")).as("BR_AUDT_KEY"),
    struct(col("BR_AUDT_COUNT_1").as("BR_AUDT_COUNT_1"), col("BR_AUDT_AMOUNT_1").as("BR_AUDT_AMOUNT_1"), col("BR_AUDT_COUNT_2").as("BR_AUDT_COUNT_2"), col("BR_AUDT_AMOUNT_2").as("BR_AUDT_AMOUNT_2"), col("BR_AUDT_COUNT_3").as("BR_AUDT_COUNT_3"), col("BR_AUDT_AMOUNT_3").as("BR_AUDT_AMOUNT_3"), col("BR_AUDT_COUNT_4").as("BR_AUDT_COUNT_4"), col("BR_AUDT_AMOUNT_4").as("BR_AUDT_AMOUNT_4"), col("BR_AUDT_COUNT_5").as("BR_AUDT_COUNT_5"), col("BR_AUDT_AMOUNT_5").as("BR_AUDT_AMOUNT_5"), col("BR_AUDT_COUNT_6").as("BR_AUDT_COUNT_6"), col("BR_AUDT_AMOUNT_6").as("BR_AUDT_AMOUNT_6"), col("BR_AUDT_COUNT_7").as("BR_AUDT_COUNT_7"), col("BR_AUDT_AMOUNT_7").as("BR_AUDT_AMOUNT_7"), col("BR_AUDT_COUNT_8").as("BR_AUDT_COUNT_8"), col("BR_AUDT_AMOUNT_8").as("BR_AUDT_AMOUNT_8"), col("BR_AUDT_COUNT_9").as("BR_AUDT_COUNT_9"), col("BR_AUDT_AMOUNT_9").as("BR_AUDT_AMOUNT_9"), col("BR_AUDT_COUNT_10").as("BR_AUDT_COUNT_10"), col("BR_AUDT_AMOUNT_10").as("BR_AUDT_AMOUNT_10")).as("BR_AUDT_COUNTS_AND_AMOUNTS"),
    col("BR_AUDT_FILLER").as("BR_AUDT_FILLER")  )
  writeDataFrame(tmp23, "file:ENV_PARAM_UNIX_TIM_GPFS/INPUT_PARAM_HLQ.DL.TIM.PEAK.COUNTS.SEQINPUT_PARAM_SEQ_NO.DINPUT_PARAM_RUN_DATE", spark, Map("sep"->","), "csv")
  /* 89_Union_n68_in */
  lazy val out_89_union_n68_in = out_source_end_of_day_processing_peak_files_for_all_day_with_coll_flg
  /* Source End_of_Day_Processing.Rllup */
  lazy val tmp24 = out_89_union_n68_in.groupBy(col("BR_AUDT_YY"),col("BR_AUDT_MM"),col("BR_AUDT_TYPE1"),col("BR_AUDT_TYPE2"),col("BR_AUDT_VIC"),col("BR_IO_FLAG"))
  lazy val out_source_end_of_day_processing_rllup = tmp24.agg(sum(col("BR_AUDT_COUNT_1")).as("BR_AUDT_COUNT_1"),sum(col("BR_AUDT_AMOUNT_1")).as("BR_AUDT_AMOUNT_1"),sum(col("BR_AUDT_COUNT_2")).as("BR_AUDT_COUNT_2"),sum(col("BR_AUDT_AMOUNT_2")).as("BR_AUDT_AMOUNT_2"),sum(col("BR_AUDT_COUNT_3")).as("BR_AUDT_COUNT_3"),sum(col("BR_AUDT_AMOUNT_3")).as("BR_AUDT_AMOUNT_3"),sum(col("BR_AUDT_COUNT_4")).as("BR_AUDT_COUNT_4"),sum(col("BR_AUDT_AMOUNT_4")).as("BR_AUDT_AMOUNT_4"),sum(col("BR_AUDT_COUNT_5")).as("BR_AUDT_COUNT_5"),sum(col("BR_AUDT_AMOUNT_5")).as("BR_AUDT_AMOUNT_5"))
  /* Source End_of_Day_Processing.Srt */
  lazy val out_source_end_of_day_processing_srt = out_source_end_of_day_processing_rllup.sortWithinPartitions(col("BR_AUDT_YY"),col("BR_AUDT_MM"),col("BR_AUDT_DD"),col("BR_AUDT_TYPE1"),col("BR_AUDT_TYPE2"),col("BR_AUDT_VIC"),col("BR_IO_FLAG"))
  /* Source End_of_Day_Processing.Intermediate_File_1 */
  lazy val tmp25 = out_source_end_of_day_processing_srt.select(
struct(struct(col("BR_AUDT_YY").as("BR_AUDT_YY"), col("BR_AUDT_MM").as("BR_AUDT_MM"), col("BR_AUDT_DD").as("BR_AUDT_DD")).as("BR_AUDT_ODATE"), col("BR_AUDT_TYPE1").as("BR_AUDT_TYPE1"), col("BR_AUDT_TYPE2").as("BR_AUDT_TYPE2"), col("BR_AUDT_VIC").as("BR_AUDT_VIC"), col("BR_IO_FLAG").as("BR_IO_FLAG")).as("BR_AUDT_KEY"),
    struct(col("BR_AUDT_COUNT_1").as("BR_AUDT_COUNT_1"), col("BR_AUDT_AMOUNT_1").as("BR_AUDT_AMOUNT_1"), col("BR_AUDT_COUNT_2").as("BR_AUDT_COUNT_2"), col("BR_AUDT_AMOUNT_2").as("BR_AUDT_AMOUNT_2"), col("BR_AUDT_COUNT_3").as("BR_AUDT_COUNT_3"), col("BR_AUDT_AMOUNT_3").as("BR_AUDT_AMOUNT_3"), col("BR_AUDT_COUNT_4").as("BR_AUDT_COUNT_4"), col("BR_AUDT_AMOUNT_4").as("BR_AUDT_AMOUNT_4"), col("BR_AUDT_COUNT_5").as("BR_AUDT_COUNT_5"), col("BR_AUDT_AMOUNT_5").as("BR_AUDT_AMOUNT_5"), col("BR_AUDT_COUNT_6").as("BR_AUDT_COUNT_6"), col("BR_AUDT_AMOUNT_6").as("BR_AUDT_AMOUNT_6"), col("BR_AUDT_COUNT_7").as("BR_AUDT_COUNT_7"), col("BR_AUDT_AMOUNT_7").as("BR_AUDT_AMOUNT_7"), col("BR_AUDT_COUNT_8").as("BR_AUDT_COUNT_8"), col("BR_AUDT_AMOUNT_8").as("BR_AUDT_AMOUNT_8"), col("BR_AUDT_COUNT_9").as("BR_AUDT_COUNT_9"), col("BR_AUDT_AMOUNT_9").as("BR_AUDT_AMOUNT_9"), col("BR_AUDT_COUNT_10").as("BR_AUDT_COUNT_10"), col("BR_AUDT_AMOUNT_10").as("BR_AUDT_AMOUNT_10")).as("BR_AUDT_COUNTS_AND_AMOUNTS"),
    col("BR_AUDT_FILLER").as("BR_AUDT_FILLER")  )
  writeDataFrame(tmp25, "file:ENV_PARAM_UNIX_TIM_GPFS/UX.DL.TIM.PEAK.CNTCLF.DINPUT_PARAM_RUN_DATE", spark, Map("sep"->","), "csv")


} // end sample10origGraph
//
// call the main workflow
//

  def main(args: Array[String]) = {
      sample10origGraph()
  }
}

