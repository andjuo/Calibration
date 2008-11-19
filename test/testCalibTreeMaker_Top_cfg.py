import FWCore.ParameterSet.Config as cms

process = cms.Process("Calib")

## add message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('TtSemiLeptonicEvent')
process.MessageLogger.cerr.INFO = cms.untracked.PSet(
    default             = cms.untracked.PSet( limit = cms.untracked.int32( 0) ),
    TtSemiLeptonicEvent = cms.untracked.PSet( limit = cms.untracked.int32(-1) ),
)

#
# Define input source
#
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    #
    # TTbar sample 1 (100 events)
    #
    #'file:/afs/cern.ch/cms/PRS/top/cmssw-data/relval200-for-pat-testing/FullSimTTBar-2_1_X_2008-07-08_STARTUP_V4-AODSIM.100.root'
    # TTbar sample 2
    #'/store/relval/CMSSW_2_1_9/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/16D75F0F-1186-DD11-80B9-000423D98C20.root',
    #'/store/relval/CMSSW_2_1_9/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/24CD41BB-1A86-DD11-9CDA-000423D98EC8.root',
    #'/store/relval/CMSSW_2_1_9/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/264D79AA-1786-DD11-9F3C-001617C3B6DC.root',
    #'/store/relval/CMSSW_2_1_9/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/327DE1B9-0E86-DD11-B7B1-000423D6C8E6.root',
    #'/store/relval/CMSSW_2_1_9/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/345AE083-1186-DD11-8D43-000423D99658.root',
    #'/store/relval/CMSSW_2_1_9/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/4A0ADB7D-1086-DD11-BD16-000423D98E6C.root',
    #'/store/relval/CMSSW_2_1_9/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/4E31E969-1886-DD11-8398-000423D9989E.root',
    #'/store/relval/CMSSW_2_1_9/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/4EEEA6AE-0886-DD11-90F9-000423D94990.root'
    # TTbar sample 3 (25100 events, recently staged files marked with !!!)
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/0609A88C-F69A-DD11-AE42-001731AF6A8D.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/08DB9384-FD9A-DD11-ACFD-003048678DD6.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/12E0A583-F69A-DD11-9B03-003048678B38.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/1AFBB319-F89A-DD11-B491-001A928116C8.root',
    '/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/1CC22E59-069B-DD11-80F0-0018F3D09634.root', #!!!
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/1EDF3F84-F69A-DD11-BEDA-001A928116CC.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/2864381E-F89A-DD11-9E2D-001A92810AAA.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/28B5240A-FC9A-DD11-A178-003048678C3A.root',
    '/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/2EB12E11-F89A-DD11-8D9A-003048678A7E.root', #!!!
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/362701E1-4A9B-DD11-A9A4-001A92971BDA.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/446FE812-099B-DD11-B3CC-001A92810AEE.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/447DCD63-069B-DD11-8E7A-001731AF6A89.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/52349E81-FD9A-DD11-AF48-00304867918E.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/62085221-F89A-DD11-8F60-001731AF6BD3.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/6419021D-F89A-DD11-8F79-0018F3D096AE.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/669F3A16-F89A-DD11-805E-003048679000.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/6A476935-F99A-DD11-8D7C-003048678AF4.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/76815C20-F89A-DD11-A082-001731230A77.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/7AF9CE67-359B-DD11-8EC2-001731A283E1.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/7E9AE61A-F89A-DD11-BEC2-0018F3D096C2.root',
    '/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/8E423E15-F89A-DD11-BEA4-0030486790C0.root', #!!!
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/9097AC1D-F89A-DD11-937E-001A928116B2.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/90B8C28C-019B-DD11-AD6C-003048678B1C.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/9421B73D-F99A-DD11-97F1-0018F3D096C2.root', #?
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/984A721A-F89A-DD11-A351-0018F3D09708.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/9CB1827D-F69A-DD11-B362-003048678B0C.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/9CDF9A1C-F89A-DD11-A0D8-001A92810AD8.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/A8D04310-099B-DD11-9A5D-001A928116E2.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/ACFF381C-F89A-DD11-9ABB-001A92971B08.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/B07E4F36-F99A-DD11-9C17-001A92971B9C.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/B2D4E439-F99A-DD11-B2C8-0018F3D09650.root', #?
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/B42DD017-F89A-DD11-911E-001A92971B3A.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/B88DDA1C-F89A-DD11-A438-0018F3D096D4.root',
    '/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/C4CE1E88-F69A-DD11-8951-001A92811726.root', #!!!
    '/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/CE04991C-F89A-DD11-BB9E-001A92971B28.root', #!!!
    '/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/CEF0CA1C-F89A-DD11-ACDE-001A92971B8C.root', #!!!
    '/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/D253EE10-FC9A-DD11-A409-001A92971ACE.root', #!!!
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/DA914143-F99A-DD11-8859-0017312B5A75.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/DADC371C-F89A-DD11-8F20-001A92971B26.root',
    '/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/E8A52D35-F99A-DD11-8A52-0018F3D09642.root', #!!!
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/FCFD2C27-009B-DD11-BAC9-001A92971B9C.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/FECC8DE7-039B-DD11-89CD-003048769E65.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0002/04FB6353-0B9B-DD11-9FDF-001731AF66A5.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0002/1A7C8912-0D9B-DD11-92A4-00304876A13B.root',
    '/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0002/2C2D0EF5-5F9B-DD11-BF60-0018F3D095FA.root', #!!!
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0002/2EA0E20C-099B-DD11-B19A-001A92971ACE.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0002/381C3CF2-579B-DD11-8620-0018F3D09702.root',
    '/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0002/427F0A35-489B-DD11-ACEA-003048767DF9.root'  #!!!
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0002/747C2956-0B9B-DD11-B226-001731AF67EF.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0002/7C492256-0B9B-DD11-8C48-001731AF66C1.root',
    #'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0002/F87A0845-0B9B-DD11-BB8A-003048678BAC.root'
    )
                            )

#
# Define maximal number of events to loop over
#
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1) )


process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FakeConditions_cff")
process.load("Geometry.CommonDetUnit.bareGlobalTrackingGeometry_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagator_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAny_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAlong_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorOpposite_cfi")
process.load("TrackingTools.TrackAssociator.DetIdAssociatorESProducer_cff")
#process.load("TrackingTools.TrackAssociator.default_cfi")

process.load("Calibration.CalibTreeMaker.CalibTreeMaker_Top_cff")

process.load("RecoJets.Configuration.RecoJetsAll_cff")

process.dump = cms.EDAnalyzer("EventContentAnalyzer")

##############   Define the L2 correction service #####
#process.L2JetCorrector = cms.ESSource("L2RelativeCorrectionService", 
#                                      tagName = cms.string('iCSA08_S156_L2Relative_Scone5'),
#                                      label = cms.string('L2RelativeJetCorrector')
#                                      )
##############   Define the L3 correction service #####
#process.L3JetCorrector = cms.ESSource("L3AbsoluteCorrectionService", 
#                                      tagName = cms.string('iCSA08_S156_L3Absolute_Scone5'),
#                                      label = cms.string('L3AbsoluteJetCorrector')
#                                      )
#
## set the record's IOV. Must be defined once. Choose ANY correction service. #
#process.prefer("L2JetCorrector")

#
# Configuration for Top
#
process.calibTreeMaker.TopTreeName    = 'TopTree'
process.calibTreeMaker.TopHadBJets    = 'topSample:TopHadBJets'
process.calibTreeMaker.TopHadWJets    = 'topSample:TopHadWJets'
process.calibTreeMaker.Top_Weight_Tag = 'tag'
process.calibTreeMaker.Top_Weight     = 1.
process.ttSemiLepJetPartonMatch.algorithm  = cms.int32(3)
process.ttSemiLepJetPartonMatch.useMaxDist = cms.bool(True)
process.ttSemiLepJetPartonMatch.maxDist    = cms.double(0.3)
process.ttSemiLepJetPartonMatch.nJets      = cms.int32(5)
# For debugging
process.ttSemiLepEvent.verbosity = cms.int32(1)

#
# Choose name of output file
#
process.calibTreeMaker.OutputFile = 'Top_Calib.root'

#
# Choose the tree to produce
#
process.calibTreeMaker.WritePhotonJetTree = False
process.calibTreeMaker.WriteDiJetTree     = False
process.calibTreeMaker.WriteTriJetTree    = False
process.calibTreeMaker.WriteTopTree       = True

#
# The path
#
process.p2 = cms.Path(process.makeTopTree)
process.schedule = cms.Schedule(process.p2)
