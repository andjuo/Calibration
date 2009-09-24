import FWCore.ParameterSet.Config as cms

process = cms.Process("Calib")

## Add message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('TtSemiLeptonicEvent')
process.MessageLogger.categories.append('JetPartonMatching')
process.MessageLogger.cerr.TtSemiLeptonicEvent = cms.untracked.PSet(
    limit = cms.untracked.int32(100)
)
process.MessageLogger.cerr.JetPartonMatching = cms.untracked.PSet(
    limit = cms.untracked.int32(100)
)

process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

#
# Define input source
#
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    '/store/mc/Summer09/TTbar/AODSIM/MC_31X_V3_AODSIM-v1/0026/F2B6764A-6D89-DE11-8585-0018FEFAC384.root'
    )
)

#
# Define maximal number of events to loop over
#
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100) )

process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('MC_31X_V3::All')

#
# Configuration for Top
#
process.load("Calibration.CalibTreeMaker.CalibTreeMaker_Top_cff")
process.ttSemiLepJetPartonMatch.algorithm  = 'unambiguousOnly'
process.ttSemiLepJetPartonMatch.useMaxDist = True
process.ttSemiLepJetPartonMatch.maxDist    = 0.5
process.ttSemiLepJetPartonMatch.maxNJets   = -1
process.ttSemiLepJetPartonMatch.partonsToIgnore = ["HadB", "LepB"]
process.ttSemiLepGenJetPartonMatch.algorithm  = "unambiguousOnly"
process.ttSemiLepGenJetPartonMatch.useMaxDist = True
process.ttSemiLepGenJetPartonMatch.maxDist    = 0.5
process.ttSemiLepGenJetPartonMatch.maxNJets   = -1
process.ttSemiLepGenJetPartonMatch.partonsToIgnore = ["HadB", "LepB"]

#
# Printout for debugging
#
process.ttSemiLepJetPartonMatch.verbosity = 1
process.ttSemiLepGenJetPartonMatch.verbosity = 1
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

## restrict input to AOD
from PhysicsTools.PatAlgos.tools.coreTools import *
restrictInputToAOD(process,['All'])

#
# Switch jet collection to anti-kt
#
from PhysicsTools.PatAlgos.tools.jetTools import *
switchJetCollection(process, 
                    cms.InputTag('antikt5CaloJets'),   
                    doJTA            = True,            
                    doBTagging       = True,            
                    jetCorrLabel     = ('AK5','Calo'),  
                    doType1MET       = True,            
                    genJetCollection = cms.InputTag("antikt5GenJets")
                    ) 

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
