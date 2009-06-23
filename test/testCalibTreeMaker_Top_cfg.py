import FWCore.ParameterSet.Config as cms

process = cms.Process("Calib")

## add message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.MessageLogger.cerr.threshold = 'INFO'
#process.MessageLogger.categories.append('TtSemiLeptonicEvent')
process.MessageLogger.cerr.INFO = cms.untracked.PSet(
    default             = cms.untracked.PSet( limit = cms.untracked.int32( 0) ),
#    TtSemiLeptonicEvent = cms.untracked.PSet( limit = cms.untracked.int32(-1) ),
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
    ## Summer08 TauolaTTBar at DESY (just one file of the sample)
   '/store/mc/Summer08/TauolaTTbar/GEN-SIM-RECO/IDEAL_V9_v2/0009/0054812D-26F7-DD11-99D7-001F2908F0E4.root'
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

#
# Configuration for Top
#
process.load("Calibration.CalibTreeMaker.CalibTreeMaker_Top_cff")
process.calibTreeMaker.TopTreeName    = 'TopTree'
process.calibTreeMaker.TopHadBJets    = 'topSample:TopHadBJets'
process.calibTreeMaker.TopHadWJets    = 'topSample:TopHadWJets'
process.calibTreeMaker.Top_GenJets    = 'sisCone5GenJets'
process.calibTreeMaker.Top_Weight_Tag = 'tag'
process.calibTreeMaker.Top_Weight     = 1.
process.ttSemiLepJetPartonMatch.algorithm  = 'unambiguousOnly'
process.ttSemiLepJetPartonMatch.useMaxDist = True
process.ttSemiLepJetPartonMatch.maxDist    = 0.3
process.ttSemiLepJetPartonMatch.maxNJets   = 5
# For debugging
process.ttSemiLepEvent.verbosity = 0

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

## necessary fixes to run 2.2.X on 2.1.X data
## comment this when running on samples produced
## with 22X
from PhysicsTools.PatAlgos.tools.cmsswVersionTools import run22XonSummer08AODSIM
run22XonSummer08AODSIM(process)

#
# The path
#
process.p = cms.Path(process.makeTopTree)
process.schedule = cms.Schedule(process.p)
