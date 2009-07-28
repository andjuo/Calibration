import FWCore.ParameterSet.Config as cms

process = cms.Process("Calib")

## Add message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('TtSemiLeptonicEvent')
process.MessageLogger.categories.append('JetPartonMatching')
process.MessageLogger.cerr.TtSemiLeptonicEvent = cms.untracked.PSet(
    limit = cms.untracked.int32(0)
)
process.MessageLogger.cerr.JetPartonMatching = cms.untracked.PSet(
    limit = cms.untracked.int32(0)
)

process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

#
# Define input source
#
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    '/store/mc/Fall08/TTJets-madgraph/GEN-SIM-RECO/IDEAL_V11_redigi_v10/0010/B493FB91-EA00-DE11-B852-00E081791899.root'
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
process.ttSemiLepJetPartonMatch.algorithm  = 'unambiguousOnly'
process.ttSemiLepJetPartonMatch.useMaxDist = True
process.ttSemiLepJetPartonMatch.maxDist    = 0.3
process.ttSemiLepJetPartonMatch.maxNJets   = 5
process.ttSemiLepJetPartonMatch.partonsToIgnore = ["HadB", "LepB"]
process.ttSemiLepGenJetPartonMatch.algorithm  = "unambiguousOnly"
process.ttSemiLepGenJetPartonMatch.useMaxDist = True
process.ttSemiLepGenJetPartonMatch.maxDist    = 0.3
process.ttSemiLepGenJetPartonMatch.maxNJets   = 5
process.ttSemiLepGenJetPartonMatch.partonsToIgnore = ["HadB", "LepB"]

#
# Printout for debugging
#
process.ttSemiLepJetPartonMatch.verbosity = 100
process.ttSemiLepGenJetPartonMatch.verbosity = 100
process.ttSemiLepEvent.verbosity = 1

#
# Turn on event selection cuts
#
from Calibration.CalibSamples.TopFilter_cff import setupEventSelection
setupEventSelection()

#
# Choose sampleType for L5 corrections
#
process.jetCorrFactors.sampleType = "ttbar" # dijet or ttbar

#
# Switch jet collection to sisCone5CaloJets
#
from PhysicsTools.PatAlgos.tools.jetTools import *
switchJetCollection(process, 
        cms.InputTag('sisCone5CaloJets'), # Jet collection; must be already in the event when patDefaultSequence is executed
        doJTA=True,                       # Run Jet-Track association & JetCharge
        doBTagging=True,                  # Run b-tagging
        jetCorrLabel=('SC5','Calo'),      # Example jet correction name; set to None for no JEC
        doType1MET=True,                  # Recompute Type1 MET using these jets
        genJetCollection=cms.InputTag("sisCone5GenJets"))

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
process.p = cms.Path(process.makeTopTree)
process.schedule = cms.Schedule(process.p)
