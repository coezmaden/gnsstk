%include "Exception.hpp"
%include "TimeConstants.hpp"
%include "TimeSystem.hpp"
%include "TimeSystemConverter.hpp"
%include "CommonTime.hpp"
%include "HexDumpDataConfig.hpp"
 //%include "StringUtils.hpp"
%include "TimeTag.hpp"
%include "ANSITime.hpp"
%include "AllanDeviation.hpp"
%include "gps_constants.hpp"
%include "EnumIterator.hpp"
%include "SatelliteSystem.hpp"
%template(std_vector_GNSS)       std::vector<gpstk::SatelliteSystem>;
%include "SatID.hpp"
%template(std_vector_SatID)      std::vector<gpstk::SatID>;
%include "MathBase.hpp"
%include "VectorBase.hpp"
%include "VectorBaseOperators.hpp"
%include "Vector.hpp"
%include "Triple.hpp"
%include "EllipsoidModel.hpp"
%include "ReferenceFrame.hpp"
%include "DeprecatedConsts.hpp"
%include "FreqConsts.hpp"
%include "GNSSconstants.hpp"
%include "Xvt.hpp"
%include "AlmOrbit.hpp"
%include "AngleReduced.hpp"
%include "Angle.hpp"
%include "FFStreamError.hpp"
%include "FFData.hpp"
%include "AntexBase.hpp"
%include "FFStream.hpp"
%include "AntexHeader.hpp"
%include "CivilTime.hpp"
%feature("flatnested");
%include "AntexData.hpp"
%feature("flatnested", "");
%include "FFTextStream.hpp"
%include "AntexStream.hpp"
%include "AntennaStore.hpp"
%include "DataStatus.hpp"
%include "AshtechData.hpp"
%include "AshtechALB.hpp"
%include "AshtechEPB.hpp"
%feature("flatnested");
%include "AshtechMBEN.hpp"
%feature("flatnested", "");
%include "AshtechPBEN.hpp"
%include "FFBinaryStream.hpp"
%include "AshtechStream.hpp"
%include "MJD.hpp"
%include "TimeConverters.hpp"
%include "EphTime.hpp"
%include "AtmLoadTides.hpp"
%include "Rinex3ObsBase.hpp"
%include "ObservationType.hpp"
%template(std_map_ObservationType_string) std::map<gpstk::ObservationType, std::string>;
%template(std_map_char_ObservationType) std::map<char, gpstk::ObservationType>;
%template(std_map_ObservationType_char) std::map<gpstk::ObservationType,char>;
%include "CarrierBand.hpp"
%template(std_map_CarrierBand_string) std::map<gpstk::CarrierBand, std::string>;
%template(std_map_char_CarrierBand) std::map<char, gpstk::CarrierBand>;
%template(std_map_CarrierBand_char) std::map<gpstk::CarrierBand,char>;
%include "TrackingCode.hpp"
%template(std_map_TrackingCode_string) std::map<gpstk::TrackingCode, std::string>;
%template(std_map_char_TrackingCode) std::map<char, gpstk::TrackingCode>;
%template(std_map_TrackingCode_char) std::map<gpstk::TrackingCode,char>;
%include "XmitAnt.hpp"
%include "ObsID.hpp"
%template(std_vector_ObsID)      std::vector<gpstk::ObsID>;
%template(std_map_SvObsEpoch) std::map< gpstk::ObsID, double >;
%include "NavType.hpp"
%include "NavSignalID.hpp"
%include "NavID.hpp"
%include "NavSatelliteID.hpp"
%template(NavSatelliteIDSet) std::set<gpstk::NavSatelliteID>;
%include "NavMessageType.hpp"
%template(NavMessageTypeSet) std::set<gpstk::NavMessageType>;
%include "NavMessageID.hpp"
%template(NavMessageIDSet) std::set<gpstk::NavMessageID>;
%include "DumpDetail.hpp"
%include "NavData.hpp"
%include "OrbitData.hpp"
%include "SVHealth.hpp"
%include "OrbitDataKepler.hpp"
%include "BDSD1NavData.hpp"
%include "BDSD1NavAlm.hpp"
%include "BDSD1NavEph.hpp"
%include "NavHealthData.hpp"
%include "BDSD1NavHealth.hpp"
%include "PackedNavBits.hpp"
%include "InterSigCorr.hpp"
%include "BDSD1NavISC.hpp"
%include "Position.hpp"
%include "IonoData.hpp"
%include "KlobucharIonoData.hpp"
%include "BDSD1NavIono.hpp"
%include "TimeOffsetData.hpp"
%include "StdNavTimeOffset.hpp"
%include "BDSD1NavTimeOffset.hpp"
%include "BDSD2NavData.hpp"
%include "BDSD2NavAlm.hpp"
%include "BDSD2NavEph.hpp"
%include "BDSD2NavHealth.hpp"
%include "BDSD2NavISC.hpp"
%include "BDSD2NavIono.hpp"
%include "BDSD2NavTimeOffset.hpp"
%include "OrbitEph.hpp"
%include "BDSEphemeris.hpp"
%include "XvtStore.hpp"
%template(XvtStore_SatID)  gpstk::XvtStore<gpstk::SatID>;
%template(XvtStore_string) gpstk::XvtStore<std::string>;
%include "OrbitEphStore.hpp"
%include "BDSEphemerisStore.hpp"
%include "Week.hpp"
%include "WeekSecond.hpp"
%include "BDSWeekSecond.hpp"
%include "BDSconsts.hpp"
%include "MatrixBase.hpp"
%include "MatrixBaseOperators.hpp"
%include "Matrix.hpp"
%include "Matrix.i"
%include "BLQDataReader.hpp"
/* %include "CommandOption.hpp" */
/* %include "CommandOptionParser.hpp" */
/* %include "BasicFramework.hpp" */
%include "BasicTimeSystemConverter.hpp"
%feature("flatnested");
%include "BinexData.hpp"
%feature("flatnested", "");
%template(std_binary_function_BinexData) std::binary_function<gpstk::BinexData, gpstk::BinexData, bool>;
%feature("flatnested");
%include "FileSpec.hpp"
%feature("flatnested", "");
%feature("flatnested");
%include "FileFilter.hpp"
%feature("flatnested", "");
%include "BinexFilterOperators.hpp"
%include "BinexStream.hpp"
%include "MiscMath.hpp"
%template(SimpleLagrangeInterpolation_double) gpstk::SimpleLagrangeInterpolation<double>;
%template(LagrangeInterpolation_double) gpstk::LagrangeInterpolation<double>;
%template(LagrangeInterpolating2ndDerivative_double) gpstk::LagrangeInterpolating2ndDerivative<double>;
%template(RSS_double) gpstk::RSS<double>;
%include "Stats.hpp"
   // Template Instantiations for non-member Stats Functions
%template(median_double) gpstk::median<double>;
%template(median_int) gpstk::median<int>;
%template(mad_double) gpstk::mad<double>;
   // Stats Class
%template(Stats_double) gpstk::Stats<double>;
%template(SeqStats_double) gpstk::SeqStats<double>;
%template(WtdStats_double) gpstk::WtdStats<double>;
%template(TwoSampleStats_double) gpstk::TwoSampleStats<double>;
%include "BivarStats.hpp"
%template(BivarStats_double) gpstk::BivarStats<double>;
%include "GPSWeekSecond.hpp"
%include "NMCTMeta.hpp"
%include "EngNav.hpp"
%include "YDSTime.hpp"
%include "BrcClockCorrection.hpp"
%include "WGS84Ellipsoid.hpp"
%include "GPSEllipsoid.hpp"
%include "RinexSatID.hpp"
%template(std_vector_RinexSatID) std::vector<gpstk::RinexSatID>;
%include "GPS_URA.hpp"
%include "BrcKeplerOrbit.hpp"
%include "CCIR.hpp"
%include "CGCS2000Ellipsoid.hpp"
%include "NavFilterKey.hpp"
%template(std_binary_function_NavFilterKey) std::binary_function<gpstk::NavFilterKey *, gpstk::NavFilterKey *, bool >;
%include "NavFilter.hpp"
%include "CNav2SanityFilter.hpp"
%template(std_binary_function_CNavFilterData) std::binary_function< gpstk::CNavFilterData,gpstk::CNavFilterData,bool >;
%template(std_binary_function_CNavFilterDataPtr) std::binary_function< gpstk::CNavFilterData *, gpstk::CNavFilterData *, bool >;
%include "CNavFilterData.hpp"
%include "CNavCookFilter.hpp"
%include "NavFilterMgr.hpp"
%include "CNavCrossSourceFilter.hpp"
%include "SatMetaData.hpp"
%include "SatMetaDataSort.hpp"
%feature("flatnested");
%include "SatMetaDataStore.hpp"
%feature("flatnested", "");
/* %include "CNavDataElement.hpp" */
/* %include "CNavDataElementStore.hpp" */
/* %include "CNavEOP.hpp" */
/* %include "CNavEmptyFilter.hpp" */
/* %include "CNavGGTO.hpp" */
/* %include "CNavISC.hpp" */
%include "OrbData.hpp"
%include "OrbDataSys.hpp"
%include "CNavMidiAlm.hpp"
%include "CNavParityFilter.hpp"
%include "CNavReducedAlm.hpp"
%include "CNavTOWFilter.hpp"
/* %include "CNavText.hpp" */
/* %include "CNavUTC.hpp" */
%include "ClockModel.hpp"
%include "TimeString.hpp"
%include "TabularSatStore.hpp"
%include "ClockRecord.hpp"
%template(TabularSatStore_ClockRecord) gpstk::TabularSatStore<gpstk::ClockRecord>;
%include "FileStore.hpp"
%include "ClockSatStore.hpp"
%include "PCodeConst.hpp"
%include "CodeBuffer.hpp"
%include "Combinations.hpp"
/* %include "CommandLine.hpp" */
/* %include "CommandOptionWithCommonTimeArg.hpp" */
/* %include "CommandOptionWithPositionArg.hpp" */
/* %include "CommandOptionWithTimeArg.hpp" */
%include "ConfDataReader.hpp"
 /* %include "ConfDataWriter.hpp" */ // error on typemaps for list of double
%include "CubicSpline.hpp"
%include "DCBDataReader.hpp"
/* %include "DebugTrace.hpp" */
%include "DiffCorrBase.hpp"
%include "DiffCorrClk.hpp"
%include "DiffCorrEph.hpp"
%include "GPSZcount.hpp"
%include "UnixTime.hpp"
%include "SystemTime.hpp"
%include "JulianDate.hpp"
%include "GPSWeek.hpp"
%include "GPSWeekZcount.hpp"
%include "GALWeekSecond.hpp"
%include "QZSWeekSecond.hpp"
/* %include "Epoch.hpp" */
%include "RinexObsBase.hpp"
%feature("flatnested");
%include "RinexObsHeader.hpp"
%feature("flatnested", "");
%template(std_vector_RinexObsType) std::vector<gpstk::RinexObsType>;
%template(std_unary_function_RinexObsHeader) std::unary_function<gpstk::RinexObsHeader, bool>;
%include "RinexDatum.hpp"
%template(std_vector_RinexDatum) std::vector<gpstk::RinexDatum>;
%template(std_map_RinexSatID_std_vector_RinexDatum) std::map<gpstk::RinexSatID, std::vector<gpstk::RinexDatum> >;
%template(std_map_RinexObsType_RinexDatum) std::map<gpstk::RinexObsType, gpstk::RinexDatum>;
%template(std_map_RinexSatID_RinexObsTypeMap) std::map<gpstk::SatID, std::map<gpstk::RinexObsType, gpstk::RinexDatum> >;
%include "RinexObsData.hpp"
%template(std_binary_function_RinexObsData) std::binary_function<gpstk::RinexObsData,gpstk::RinexObsData,bool>;
%include "GPSEphemeris.hpp"
%include "RinexNavBase.hpp"
%include "EngEphemeris.hpp"
%include "FormattedDouble.hpp"
%include "RNDouble.hpp"
%include "RinexNavData.hpp"
%template(std_binary_function_RinexNavData) std::binary_function<gpstk::RinexNavData,gpstk::RinexNavData,bool>;
%template(std_unary_function_RinexNavData) std::unary_function<gpstk::RinexNavData,bool>;
%include "GPSEphemerisStore.hpp"
%include "PositionRecord.hpp"
%template(TabularSatStore_PositionRecord) gpstk::TabularSatStore<gpstk::PositionRecord>;
%include "SP3SatID.hpp"
%include "SP3Base.hpp"
%include "SP3Data.hpp"
%include "PositionSatStore.hpp"
%include "SP3Header.hpp"
%feature("flatnested");
%include "Rinex3ClockBase.hpp"
%feature("flatnested", "");
%include "RinexObsID.hpp"
%template(std_vector_RinexObsID) std::vector<gpstk::RinexObsID>;
%template(std_map_string_vector_RinexObsID) std::map<std::string, std::vector<gpstk::RinexObsID> >;
%include "Rinex3ClockHeader.hpp"
%include "SP3EphemerisStore.hpp"
%include "RinexUtilities.hpp"
/* %include "SatPass.hpp" */
/* %include "DiscCorr.hpp" */
%include "ENUUtil.hpp"
%include "IERSConvention.hpp"
/* %include "EarthOrientation.hpp" */
/* %include "EOPPrediction.hpp" */
/* %include "EOPStore.hpp" */
%include "EngAlmanac.hpp"
%include "EphemerisRange.hpp"
%feature("flatnested");
%include "IonoModel.hpp"
%feature("flatnested", "");
%feature("flatnested");
%include "IonoModelStore.hpp"
%feature("flatnested", "");
%include "ValidType.hpp"
%include "SvObsEpoch.hpp"
%template(std_map_ObsEpoch) std::map<gpstk::SatID, gpstk::SvObsEpoch>;
%include "ObsEpochMap.hpp"
%template(ObsEpochMap) std::map<gpstk::CommonTime, gpstk::ObsEpoch>;
%include "WxObsMap.hpp"
%include "TropModel.hpp"
%include "NBTropModel.hpp"
%include "ObsRngDev.hpp"
%include "ORDEpoch.hpp"
%include "ObsClockModel.hpp"
%include "EpochClockModel.hpp"
%include "Expression.hpp"
%include "StatsFilterHit.hpp"
%include "RobustStats.hpp"
%include "FDiffFilter.hpp"
%include "FileSpecFind.hpp"
%include "FileUtils.hpp"
%include "FileFilterFrame.hpp"
 // Use a special wrapper for the include file which resolves issues
 // with the nested definitions
%include "Rinex3ObsHeader.i"
%template(std_unary_function_Rinex3ObsHeader) std::unary_function<gpstk::Rinex3ObsHeader, bool>;
%include "Rinex3ObsData.hpp"
%template(std_vector_Rinex3ObsData) std::vector<gpstk::Rinex3ObsData>;
%template(std_binary_function_Rinex3ObsData) std::binary_function<gpstk::Rinex3ObsData,gpstk::Rinex3ObsData,bool>;
%include "FileFilterFrameWithHeader.hpp"
%feature("flatnested");
%include "FirstDiffFilter.hpp"
%feature("flatnested", "");
%include "FreqConv.hpp"
%include "GCATTropModel.hpp"
%include "GGHeightTropModel.hpp"
%include "GGTropModel.hpp"
%include "Rinex3NavBase.hpp"
%include "IRNWeekSecond.hpp"
%include "TimeSystemCorr.hpp"
%include "Rinex3NavHeader.hpp"
%template(std_unary_function_Rinex3NavHeader) std::unary_function<gpstk::Rinex3NavHeader, bool>;
%include "Rinex3NavStream.hpp"
%include "PZ90Ellipsoid.hpp"
%include "GloEphemeris.hpp"
%include "GalEphemeris.hpp"
%include "QZSEphemeris.hpp"
%include "Rinex3NavData.hpp"
%template(std_binary_function_Rinex3NavData) std::binary_function<gpstk::Rinex3NavData,gpstk::Rinex3NavData,bool>;
%template(std_unary_function_Rinex3NavData) std::unary_function<gpstk::Rinex3NavData,bool>;
%include "OrbElemBase.hpp"
%include "OrbElemStore.hpp"
%include "GPSAlmanacStore.hpp"
%include "GPSCNav2Alm.hpp"
%include "GPSCNav2Eph.hpp"
%include "GPSCNav2Health.hpp"
%include "GPSCNav2ISC.hpp"
%include "GPSCNav2Iono.hpp"
%include "GPSCNav2TimeOffset.hpp"
%include "GPSCNavData.hpp"
%include "GPSCNavAlm.hpp"
%include "GPSCNavEph.hpp"
%include "GPSCNavHealth.hpp"
%include "GPSCNavISC.hpp"
%include "GPSCNavIono.hpp"
%include "GPSCNavRedAlm.hpp"
%include "GPSCNavTimeOffset.hpp"
%include "GPSLNavData.hpp"
%include "GPSLNavAlm.hpp"
%include "GPSLNavEph.hpp"
%include "GPSLNavHealth.hpp"
%include "GPSLNavISC.hpp"
%include "GPSLNavIono.hpp"
%include "GPSLNavTimeOffset.hpp"
%include "GPSOrbElemStore.hpp"
%include "GSatID.hpp"
%include "GalDataValid.hpp"
%include "GalEphemerisStore.hpp"
%include "GalHealthStatus.hpp"
%include "GalFNavAlm.hpp"
%include "GalFNavEph.hpp"
%include "GalFNavHealth.hpp"
%include "GalFNavISC.hpp"
%include "MODIP.hpp"
%include "GalileoEllipsoid.hpp"
%include "GalileoIonoEllipsoid.hpp"
%feature("flatnested");
%include "NeQuickIonoData.hpp"
%feature("flatnested", "");
%include "GalFNavIono.hpp"
%include "GalFNavTimeOffset.hpp"
%include "GalINavAlm.hpp"
%include "GalINavEph.hpp"
%include "GalINavHealth.hpp"
%include "GalINavISC.hpp"
%include "GalINavIono.hpp"
%include "GalINavTimeOffset.hpp"
%include "GenXSequence.hpp"
%include "GenericNavFilterData.hpp"
%include "GloEphemerisStore.hpp"
%include "GlobalTropModel.hpp"
%include "HelmertTransform.hpp"
 //%include "IERS1996NutationData.hpp"
 //%include "IERS1996UT1mUTCData.hpp"
 //%include "IERS2003NutationData.hpp"
/* %include "IERS2010CIOSeriesData.hpp" */
/* %include "LoopedFramework.hpp" */
/* %include "InOutFramework.hpp" */
%include "IonexBase.hpp"
%feature("flatnested");
%include "IonexHeader.hpp"
%feature("flatnested", "");
%template(FileStore_IonexHeader) gpstk::FileStore<gpstk::IonexHeader>;
%include "IonexStream.hpp"
%feature("flatnested");
%include "IonexData.hpp"
%feature("flatnested", "");
%include "IonexStore.hpp"
%include "Namelist.hpp"
/* %include "SRIMatrix.hpp" */
/* %include "SparseVector.hpp" */
/* %include "SparseMatrix.hpp" */
/* %include "SRI.hpp" */
/* %include "SRIFilter.hpp" */
/* %include "logstream.hpp" */
%feature("flatnested");
%include "KalmanFilter.hpp"
%feature("flatnested", "");
%template(std_binary_function_LNavFilterData) std::binary_function< gpstk::LNavFilterData *, gpstk::LNavFilterData *, bool >;
%include "LNavFilterData.hpp"
%include "LNavAlmValFilter.hpp"
%include "LNavCookFilter.hpp"
%include "LNavCrossSourceFilter.hpp"
%include "LNavEmptyFilter.hpp"
%include "LNavEphMaker.hpp"
%include "LNavOrderFilter.hpp"
%include "LNavParityFilter.hpp"
%include "LNavTLMHOWFilter.hpp"
%include "LinearClockModel.hpp"
%include "MOPSTropModel.hpp"
%include "MatrixImplementation.hpp"
%include "MatrixFunctors.hpp"
%include "MatrixOperators.hpp"
%include "MetReader.hpp"
%include "MostCommonValue.hpp"
%include "NavValidityType.hpp"
%include "NavSearchOrder.hpp"
%include "NavDataFactory.hpp"
%include "NavDataFactoryWithStore.hpp"
%include "NavDataFactoryWithStoreFile.hpp"
%include "MultiFormatNavDataFactory.hpp"
%include "NDFUniqConstIterator.hpp"
%template (NDFUniqConstIterator_NavDataFactoryMap) gpstk::NDFUniqConstIterator<gpstk::NavDataFactoryMap>;
%include "NDFUniqIterator.hpp"
%template (NDFUniqIterator_NavDataFactoryMap) gpstk::NDFUniqIterator<gpstk::NavDataFactoryMap>;
%include "NEDUtil.hpp"
%include "NavLibrary.hpp"
%include "NavMsgData.hpp"
%include "NavMsgDataBits.hpp"
%include "NavMsgDataPNB.hpp"
%include "NavMsgDataWords.hpp"
%template(NavMsgDataWords_30) gpstk::NavMsgDataWords<30>;
%include "NavOrderFilter.hpp"
%include "NavTimeSystemConverter.hpp"
%include "NeillTropModel.hpp"
%feature("flatnested");
%include "OceanLoadTides.hpp"
%feature("flatnested", "");
%include "OceanLoading.hpp"
%include "OrbElem.hpp"
 /* %include "OrbAlm.hpp" */ // SEGFAULT
/* %include "OrbAlmFactory.hpp" */
/* %include "OrbAlmGen.hpp" */
 /* %include "OrbAlmStore.hpp" */ // requires OrbAlm to build
%include "OrbDataSysFactory.hpp"
%include "OrbDataUTC.hpp"
%include "OrbElemRinex.hpp"
%include "OrbSysGpsC.hpp"
%include "OrbSysGpsC_30.hpp"
%include "OrbSysGpsC_33.hpp"
/* %include "OrbSysGpsC_32.hpp" */
%include "OrbSysGpsL.hpp"
/* %include "OrbSysGpsL_51.hpp" */
%include "OrbSysGpsL_52.hpp"
%include "OrbSysGpsL_55.hpp"
%include "OrbSysGpsL_56.hpp"
/* %include "OrbSysGpsL_63.hpp" */
%include "OrbSysGpsL_Reserved.hpp"
%include "OrbSysStore.hpp"
%include "OrbitDataSP3.hpp"
%include "PNBNavDataFactory.hpp"
%feature("flatnested");
%include "PNBBDSD1NavDataFactory.hpp"
%feature("flatnested", "");
%feature("flatnested");
%include "PNBBDSD2NavDataFactory.hpp"
%feature("flatnested", "");
%include "PNBGPSCNav2DataFactory.hpp"
%include "PNBGPSCNavDataFactory.hpp"
%include "PNBGPSLNavDataFactory.hpp"
%include "PNBGalFNavDataFactory.hpp"
%include "PNBGalINavDataFactory.hpp"
%include "PNBMultiGNSSNavDataFactory.hpp"
%include "stl_helpers.hpp"
%include "PRSolution.hpp"
%include "PRSolutionLegacy.hpp"
%include "PoleTides.hpp"
%include "PolyFit.hpp"
%template(PolyFit_double) gpstk::PolyFit<double>;
%include "PosixTime.hpp"
 //%include "PowerSum.hpp"
%include "SolarSystemEphemeris.hpp"
%include "SunEarthSatGeometry.i"
%include "SolidEarthTides.hpp"
/* %include "SolarSystem.hpp" */
/* %include "PreciseRange.hpp" */
%include "QZSEphemerisStore.hpp"
%include "RACRotation.hpp"
/* %include "RTFileFrame.hpp" */
%include "RationalizeRinexNav.hpp"
%include "Rinex3ClockData.hpp"
%include "Rinex3ClockStream.hpp"
%include "Rinex3EphemerisStore.hpp"
%include "Rinex3NavFilterOperators.hpp"
/* %include "Rinex3ObsFileLoader.hpp" */
%include "Rinex3ObsFilterOperators.hpp"
%include "Rinex3ObsStream.hpp"
%feature("flatnested");
%include "RinexClockBase.hpp"
%feature("flatnested", "");
%include "RinexClockData.hpp"
%feature("flatnested");
%include "RinexClockHeader.hpp"
%feature("flatnested", "");
%include "RinexClockStream.hpp"
 //%include "RinexClockStore.hpp"
%include "RinexNavHeader.hpp"
%template (FileStore_RinexNavHeader) gpstk::FileStore<gpstk::RinexNavHeader>;
%template(std_unary_function_RinexNavHeader) std::unary_function<gpstk::RinexNavHeader,bool>;
%include "RinexNavStream.hpp"
%include "RinexEphemerisStore.hpp"
%include "RinexMetBase.hpp"
%feature("flatnested");
%include "RinexMetHeader.hpp"
%feature("flatnested", "");
%template(std_unary_function_RinexMetHeader) std::unary_function<gpstk::RinexMetHeader,bool>;
%include "RinexMetData.hpp"
%template(std_binary_function_RinexMetData) std::binary_function<gpstk::RinexMetData,gpstk::RinexMetData,bool>;
%include "RinexMetFilterOperators.hpp"
%include "RinexMetStream.hpp"
%include "RinexNavDataFactory.hpp"
%include "RinexNavFilterOperators.hpp"
%include "RinexObsFilterOperators.hpp"
%include "RinexObsStream.hpp"
%include "RinexTimeOffset.hpp"
%include "SEMBase.hpp"
%include "SEMHeader.hpp"
%template(FileStore_SEMHeader) gpstk::FileStore<gpstk::SEMHeader>;
%include "SEMData.hpp"
%include "SEMStream.hpp"
 /* %include "SEMAlmanacStore.hpp" */ // requires OrbAlmStore
%include "SEMNavDataFactory.hpp"
%include "SP3NavDataFactory.hpp"
%include "SP3Stream.hpp"
/* %include "SRIleastSquares.hpp" */
%include "X1Sequence.hpp"
%include "X2Sequence.hpp"
%include "SVPCodeGen.hpp"
%include "SaasTropModel.hpp"
%include "SatDataReader.hpp"
/* %include "SatPassIterator.hpp" */
%include "msecHandler.hpp"
/* %include "SatPassUtilities.hpp" */
%include "SimpleTropModel.hpp"
/* %include "SinexBase.hpp" */
/* %include "SinexHeader.hpp" */
/* %include "SinexTypes.hpp" */
/* %include "SinexBlock.hpp" */
/* %include "SinexData.hpp" */
/* %include "SinexStream.hpp" */
%include "SolarPosition.hpp"
/* %include "SpecialFuncs.hpp" */
%include "StreamBuf.hpp"
%include "TimeCorrection.hpp"
%include "TimeNamedFileStream.hpp"
%feature("flatnested");
%include "TimeRange.hpp"
%feature("flatnested", "");
%include "VectorOperators.hpp"
%include "WNJfilter.hpp"
%feature("flatnested");
%include "WindowFilter.hpp"
%feature("flatnested", "");
%include "YumaBase.hpp"
%include "YumaHeader.hpp"
%template(FileStore_YumaHeader) gpstk::FileStore<gpstk::YumaHeader>;
%include "YumaData.hpp"
%include "YumaStream.hpp"
 /* %include "YumaAlmanacStore.hpp" */ // requires OrbAlmStore
%include "YumaNavDataFactory.hpp"
%include "convhelp.hpp"
%include "expandtilde.hpp"
%include "format.hpp"
/* %include "gdc.hpp" */
%include "ord.hpp"
%include "random.hpp"
%include "singleton.hpp"
