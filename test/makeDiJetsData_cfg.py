import FWCore.ParameterSet.Config as cms

process = cms.Process("Calib")


process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold             = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 5000


process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    '/store/data/Commissioning10/MinimumBias/RECO/v8/000/132/531/40DC3F79-473E-DF11-854B-000423D986C4.root'
            )
                            )

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100) )

process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(True)
)


# Trigger
process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff')
process.load('HLTrigger/HLTfilters/hltLevel1GTSeed_cfi')
process.hltLevel1GTSeed.L1TechTriggerSeeding = cms.bool(True)
process.hltLevel1GTSeed.L1SeedsLogicalExpression = cms.string('0 AND (40 OR 41) AND NOT (36 OR 37 OR 38 OR 39) AND NOT ((42 AND NOT 43) OR (43 AND NOT 42))')

# Vertex filter
process.primaryVertexFilter = cms.EDFilter("VertexSelector",
   src = cms.InputTag("offlinePrimaryVertices"),
   cut = cms.string("!isFake && ndof > 4 && abs(z) <= 15 && position.Rho <= 2"), # tracksSize() > 3 for the older cut
   filter = cms.bool(True),   # otherwise it won't filter the events, just produce an empty vertex collection.
)

# Monster Event filter
process.noscraping = cms.EDFilter("FilterOutScraping",
applyfilter = cms.untracked.bool(True),
debugOn = cms.untracked.bool(False),
numtrack = cms.untracked.uint32(10),
thresh = cms.untracked.double(0.25)
)


process.load('Configuration/StandardSequences/Services_cff')
process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load('Configuration/StandardSequences/MagneticField_38T_cff')
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagator_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAny_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAlong_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorOpposite_cfi")
process.load("TrackingTools.TrackAssociator.DetIdAssociatorESProducer_cff")
process.load("TrackingTools.TrackAssociator.default_cfi")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'GR10_P_V4::All'

process.load("Calibration.CalibTreeMaker.CalibTreeMaker_cff")

process.load("RecoJets.Configuration.RecoJets_cff")

process.dump = cms.EDAnalyzer("EventContentAnalyzer")

## from RecoJets.Configuration.RecoJetAssociations_cff import *

## process.load("PhysicsTools.JetMCAlgos.SelectPartons_cff")

## process.CaloJetPartonMatching = cms.EDFilter("JetPartonMatcher",
##    jets = cms.InputTag("ak5CaloJets"),
##    coneSizeToAssociate = cms.double(0.2),
##    partons = cms.InputTag("myPartons")
## )

## process.load("RecoJets.Configuration.GenJetParticles_cff")
## process.load("RecoJets.Configuration.RecoGenJets_cff")


# Jet Energy Corrections
process.load("JetMETCorrections.Configuration.L2L3Corrections_Summer09_7TeV_ReReco332_cff")

# ZSP and JPT corrections
process.load("JetMETCorrections.Configuration.ZSPJetCorrections219_cff")
#process.load("JetMETCorrections.Configuration.JetPlusTrackCorrections_cff")

#process.L2JetCorrectorIC5JPT= cms.ESSource("L2RelativeCorrectionService", 
#                                           tagName = cms.string('Winter09_L2Relative_IC5JPT'),
#                                           label = cms.string('L2RelativeJetCorrectorIC5JPT')
#)
#process.L3JetCorrectorIC5JPT = cms.ESSource("L3AbsoluteCorrectionService", 
#                                            tagName = cms.string('Winter09_L3Absolute_IC5JPT'),
#                                            label = cms.string('L3AbsoluteJetCorrectorIC5JPT')
#)
#process.L2L3JetCorrectorIC5JPT = cms.ESSource("JetCorrectionServiceChain",  
#    correctors = cms.vstring('L2RelativeJetCorrectorIC5JPT','L3AbsoluteJetCorrectorIC5JPT'),
#    label = cms.string('L2L3JetCorrectorIC5JPT') 
#)

###  Parameters for module calibTreeMaker
process.calibTreeMaker.WriteDiJetTree          = True
process.calibTreeMaker.WriteStableGenParticles = False

process.calibTreeMaker.OutputFile         = 'MinBias-BeamCommissioning10-7TeV-PromptReco_v8.root'

process.calibTreeMaker.DiJetTreeName      = 'DiJetTree'
process.calibTreeMaker.GenEventScaleLabel = 'genEventScale'
process.calibTreeMaker.NJet_Jets         = 'ak5CaloJets'
process.calibTreeMaker.NJet_MinNumJets   = 1
process.calibTreeMaker.NJet_JetIDs       = 'ak5JetID'
process.calibTreeMaker.NJet_GenJets      = 'ak5GenJets'
process.calibTreeMaker.NJet_GenParticles = 'genParticles'
process.calibTreeMaker.NJetZSPJets       = 'ZSPJetCorJetAntiKt5'
process.calibTreeMaker.NJet_L2JetCorrector      = cms.string('L2RelativeJetCorrectorAK5Calo')
process.calibTreeMaker.NJet_L3JetCorrector      = cms.string('L3AbsoluteJetCorrectorAK5Calo')
process.calibTreeMaker.NJet_JPTZSPCorrector     = cms.string('JetPlusTrackZSPCorrectorAntiKt5')
process.calibTreeMaker.NJet_L2L3JetCorrector    = cms.string('L2L3JetCorrectorAK5Calo')
process.calibTreeMaker.NJet_L2L3JetCorrectorJPT = cms.string('L2L3JetCorrectorIC5JPT')
process.calibTreeMaker.NJet_MET          = 'met'
process.calibTreeMaker.NJetRecTracks     = 'generalTracks'
process.calibTreeMaker.BeamSpot          = 'offlineBeamSpot'
process.calibTreeMaker.NJetRecMuons      = 'muons' #'globalMuons' check for global muon & TMLastStationLoose in code
process.calibTreeMaker.NJetConeSize      = 0.5
process.calibTreeMaker.NJet_Weight_Tag   = 'genEventWeight'
process.calibTreeMaker.NJet_Weight       =  600000  #1 #Summer09: 0-15: 1802353.8 (fuer 1mio ca 600000);   20-30: 21194.22 ;   50-80: 10193.66  ;    120-170: 469.1156 ;170-230: 89.325 ; 230-300:19.6624 ; 300-380: 5.1781 ; 380-470: 1.32352 ; 470-600: 0.43106 ; 600-800: 0.29169 ;  800-1k: 0.044800 ; 1k-1.4k: 0.010758 ; 1.4k-1.8k: 0.0007192 ; 1.8-2.2k: 0.000063557 ; 2.2k - 2.6k : 0.000005888; 2.6k-3k: 0.000000517 ; 3k-3.5k: 0.00000004 ; 3.5k-Inf: 0.000000001
#Unfinished  15-20: 47035.54 ; 30-50: 8650.123 ; 80-120: 293.22


process.pDump = cms.Path( process.dump )

process.pData = cms.Path( process.hltLevel1GTSeed
                          * process.primaryVertexFilter
                          * process.noscraping
                          #* process.ZSPJetCorrectionsAntiKt5
                          #* process.ZSPrecoJetAssociationsAntiKt5
                          * process.calibTreeMaker
                          )

process.schedule = cms.Schedule(process.pData)
