import FWCore.ParameterSet.Config as cms

process = cms.Process("Calib")

#
# Define input source
#
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    #
    # TTbar sample 1
    #
    'file:/afs/cern.ch/cms/PRS/top/cmssw-data/relval200-for-pat-testing/FullSimTTBar-2_1_X_2008-07-08_STARTUP_V4-AODSIM.100.root'
    # TTbar sample 2
    #'/store/relval/CMSSW_2_1_9/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/16D75F0F-1186-DD11-80B9-000423D98C20.root',
    #'/store/relval/CMSSW_2_1_9/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/24CD41BB-1A86-DD11-9CDA-000423D98EC8.root',
    #'/store/relval/CMSSW_2_1_9/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/264D79AA-1786-DD11-9F3C-001617C3B6DC.root',
    #'/store/relval/CMSSW_2_1_9/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/327DE1B9-0E86-DD11-B7B1-000423D6C8E6.root',
    #'/store/relval/CMSSW_2_1_9/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/345AE083-1186-DD11-8D43-000423D99658.root',
    #'/store/relval/CMSSW_2_1_9/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/4A0ADB7D-1086-DD11-BD16-000423D98E6C.root',
    #'/store/relval/CMSSW_2_1_9/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/4E31E969-1886-DD11-8398-000423D9989E.root',
    #'/store/relval/CMSSW_2_1_9/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/4EEEA6AE-0886-DD11-90F9-000423D94990.root'
    )
                            )

#
# Define maximal number of events to loop over
#
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100) )


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

process.load("Calibration.CalibTreeMaker.CalibTreeMaker_cff")

process.load("RecoJets.Configuration.RecoJetsAll_cff")

process.dump = cms.EDAnalyzer("EventContentAnalyzer")

#############   Define the L2 correction service #####
process.L2JetCorrector = cms.ESSource("L2RelativeCorrectionService", 
                                      tagName = cms.string('iCSA08_S156_L2Relative_Scone5'),
                                      label = cms.string('L2RelativeJetCorrector')
                                      )
#############   Define the L3 correction service #####
process.L3JetCorrector = cms.ESSource("L3AbsoluteCorrectionService", 
                                      tagName = cms.string('iCSA08_S156_L3Absolute_Scone5'),
                                      label = cms.string('L3AbsoluteJetCorrector')
                                      )

# set the record's IOV. Must be defined once. Choose ANY correction service. #
process.prefer("L2JetCorrector")

#
# Configuration for Top
#
process.calibTreeMaker.TopTreeName    = 'TopTree'
process.calibTreeMaker.TopHadBJets    = 'topSample:TopHadBJets'
process.calibTreeMaker.TopHadWJets    = 'topSample:TopHadWJets'
process.calibTreeMaker.Top_Weight_Tag = 'tag'
process.calibTreeMaker.Top_Weight     = 1.

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
