import FWCore.ParameterSet.Config as cms

process = cms.Process("Calib")


process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold             = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 5000


process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    '/store/mc/Spring10/QCDFlat_Pt15to3000/GEN-SIM-RECO/START3X_V26_S09-v1/0057/E6265471-0C4A-DF11-916C-002264984988.root'
            )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(5) )

process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(True)
)

# Vertex filter
process.primaryVertexFilter = cms.EDFilter("VertexSelector",
   src = cms.InputTag("offlinePrimaryVertices"),
   cut = cms.string("!isFake && ndof > 4 && abs(z) <= 15 && position.Rho <= 2"), # tracksSize() > 3 for the older cut
   filter = cms.bool(True),   # otherwise it won't filter the events, just produce an empty vertex collection.
)

process.load('Configuration/StandardSequences/Services_cff')
process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load('Configuration/StandardSequences/MagneticField_AutoFromDBCurrent_cff')
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagator_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAny_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAlong_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorOpposite_cfi")
process.load("TrackingTools.TrackAssociator.DetIdAssociatorESProducer_cff")
process.load("TrackingTools.TrackAssociator.default_cfi")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'START38_V12::All'

process.load("Calibration.CalibTreeMaker.CalibTreeMaker_cfi")

process.load("RecoJets.Configuration.RecoJets_cff")

process.dump = cms.EDAnalyzer("EventContentAnalyzer")

from RecoJets.Configuration.RecoJetAssociations_cff import *

process.load("PhysicsTools.JetMCAlgos.SelectPartons_cff")

process.CaloJetPartonMatching = cms.EDProducer("JetPartonMatcher",
   jets = cms.InputTag("ak5CaloJets"),
   coneSizeToAssociate = cms.double(0.2),
   partons = cms.InputTag("myPartons")
)

process.load("RecoJets.Configuration.GenJetParticles_cff")
process.load("RecoJets.Configuration.RecoGenJets_cff")


# Jet Energy Corrections
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')
# L4JW Correction Services
# you need special versions of CondFormats and JetMETCorrections:
# copy the following dirs to your release (this works with 3_8_4):
# /afs/cern.ch/user/s/stadie/public/CondFormats
# /afs/cern.ch/user/s/stadie/public/JetMETCorrections
#
process.ak5CaloL4JW = cms.ESSource(
    'LXXXCorrectionService',
    era = cms.string('Spring10'),
    section   = cms.string(''),
    level     = cms.string('L4JW'),
    algorithm = cms.string('AK5Calo'),
    useCondDB = cms.untracked.bool(False)
    )
process.ak5CaloL2L3L4JW = process.ak5CaloL2L3.clone()
process.ak5CaloL2L3L4JW.correctors.append('ak5CaloL4JW')

# ZSP and JPT corrections
process.load("RecoJets.Configuration.RecoJPTJets_cff")


###  Parameters for module calibTreeMaker
process.calibTreeMakerCalo.WriteDiJetTree          = True
process.calibTreeMakerCalo.WriteStableGenParticles = False
process.calibTreeMakerCalo.OutputFile         = 'ak5Calo.root'
process.calibTreeMakerCalo.NJet_Jets         = 'ak5CaloJets'
process.calibTreeMakerCalo.NJet_JetIDs       = 'ak5JetID'
process.calibTreeMakerCalo.NJet_GenJets      = 'ak5GenJets'
process.calibTreeMakerCalo.NJetZSPJets       = 'ZSPJetCorJetAntiKt5'
process.calibTreeMakerCalo.NJet_L2JetCorrector      = cms.string('ak5CaloL2Relative')
process.calibTreeMakerCalo.NJet_L3JetCorrector      = cms.string('ak5CaloL3Absolute')
process.calibTreeMakerCalo.NJet_JPTZSPCorrector     = cms.string('JetPlusTrackZSPCorrectorAntiKt5')
process.calibTreeMakerCalo.NJet_L2L3JetCorrector    = cms.string('ak5CaloL2L3')
process.calibTreeMakerCalo.NJet_L2L3L4JWJetCorrector = cms.string('ak5CaloL2L3L4JW')
process.calibTreeMakerCalo.NJet_L2L3JetCorrectorJPT = cms.string('ak5JPTL2L3')
process.calibTreeMakerCalo.NJetConeSize      = 0.5
#process.calibTreeMakerCalo.NJet_Weight_Tag   = 'genEventWeight'
#process.calibTreeMakerCalo.NJet_Weight       =  1 #Summer09: 0-15: 1802353.8 (fuer 1mio ca 600000);   20-30: 21194.22 ;   50-80: 10193.66  ;    120-170: 469.1156 ;170-230: 89.325 ; 230-300:19.6624 ; 300-380: 5.1781 ; 380-470: 1.32352 ; 470-600: 0.43106 ; 600-800: 0.29169 ;  800-1k: 0.044800 ; 1k-1.4k: 0.010758 ; 1.4k-1.8k: 0.0007192 ; 1.8-2.2k: 0.000063557 ; 2.2k - 2.6k : 0.000005888; 2.6k-3k: 0.000000517 ; 3k-3.5k: 0.00000004 ; 3.5k-Inf: 0.000000001
#Unfinished  15-20: 47035.54 ; 30-50: 8650.123 ; 80-120: 293.22

process.calibTreeMakerPF.WriteDiJetTree          = True
process.calibTreeMakerPF.WriteStableGenParticles = False
process.calibTreeMakerPF.OutputFile         = 'ak5PF.root'
process.calibTreeMakerPF.NJet_Jets         = 'ak5PFJets'
process.calibTreeMakerPF.NJet_JetIDs       = ''
process.calibTreeMakerPF.NJet_GenJets      = 'ak5GenJets'
process.calibTreeMakerPF.NJetZSPJets       = 'ZSPJetCorJetAntiKt5'
process.calibTreeMakerPF.NJet_L2JetCorrector      = cms.string('ak5PFL2Relative')
process.calibTreeMakerPF.NJet_L3JetCorrector      = cms.string('ak5PFL3Absolute')
process.calibTreeMakerPF.NJet_JPTZSPCorrector     = cms.string('JetPlusTrackZSPCorrectorAntiKt5')
process.calibTreeMakerPF.NJet_L2L3JetCorrector    = cms.string('ak5PFL2L3')
process.calibTreeMakerPF.NJet_L2L3L4JWJetCorrector = cms.string('ak5PFL2L3')
process.calibTreeMakerPF.NJet_L2L3JetCorrectorJPT = cms.string('ak5JPTL2L3')
process.calibTreeMakerPF.NJetConeSize      = 0.5
#process.calibTreeMakerPF.NJet_Weight_Tag   = 'genEventWeight'
#process.calibTreeMakerPF.NJet_Weight       =  600000  #1 #Summer09: 0-15: 1802353.8 (fuer 1mio ca 600000);   20-30: 21194.22 ;   50-80: 10193.66  ;    120-170: 469.1156 ;170-230: 89.325 ; 230-300:19.6624 ; 300-380: 5.1781 ; 380-470: 1.32352 ; 470-600: 0.43106 ; 600-800: 0.29169 ;  800-1k: 0.044800 ; 1k-1.4k: 0.010758 ; 1.4k-1.8k: 0.0007192 ; 1.8-2.2k: 0.000063557 ; 2.2k - 2.6k : 0.000005888; 2.6k-3k: 0.000000517 ; 3k-3.5k: 0.00000004 ; 3.5k-Inf: 0.000000001
#Unfinished  15-20: 47035.54 ; 30-50: 8650.123 ; 80-120: 293.22

process.calibTreeMakerTrack.WriteDiJetTree          = True
process.calibTreeMakerTrack.WriteStableGenParticles = False
process.calibTreeMakerTrack.OutputFile        = 'ak5Track.root'
process.calibTreeMakerTrack.NJet_Jets         = 'ak5TrackJets'
process.calibTreeMakerTrack.NJet_JetIDs       = ''
process.calibTreeMakerTrack.NJet_GenJets      = 'ak5GenJets'
process.calibTreeMakerTrack.NJetZSPJets       = 'ZSPJetCorJetAntiKt5'
#ATTENTION: use CALO correction for the time being....
process.calibTreeMakerTrack.NJet_L2JetCorrector      = cms.string('ak5TRKL2Relative')
process.calibTreeMakerTrack.NJet_L3JetCorrector      = cms.string('ak5TRKL3Absolute')
process.calibTreeMakerTrack.NJet_JPTZSPCorrector     = cms.string('JetPlusTrackZSPCorrectorAntiKt5')
process.calibTreeMakerTrack.NJet_L2L3JetCorrector    = cms.string('ak5TRKL2L3')
process.calibTreeMakerTrack.NJet_L2L3L4JWJetCorrector    = cms.string('ak5TRKL2L3')
process.calibTreeMakerTrack.NJet_L2L3JetCorrectorJPT = cms.string('ak5JPTL2L3')
process.calibTreeMakerTrack.NJetConeSize      = 0.5
#process.calibTreeMakerTrack.NJet_Weight_Tag   = 'genEventWeight'
#process.calibTreeMakerTrack.NJet_Weight       =  600000  #1 #Summer09: 0-15: 1802353.8 (fuer 1mio ca 600000);   20-30: 21194.22 ;   50-80: 10193.66  ;    120-170: 469.1156 ;170-230: 89.325 ; 230-300:19.6624 ; 300-380: 5.1781 ; 380-470: 1.32352 ; 470-600: 0.43106 ; 600-800: 0.29169 ;  800-1k: 0.044800 ; 1k-1.4k: 0.010758 ; 1.4k-1.8k: 0.0007192 ; 1.8-2.2k: 0.000063557 ; 2.2k - 2.6k : 0.000005888; 2.6k-3k: 0.000000517 ; 3k-3.5k: 0.00000004 ; 3.5k-Inf: 0.000000001
#Unfinished  15-20: 47035.54 ; 30-50: 8650.123 ; 80-120: 293.22

#ATTENTION: use CALOcorrections for the time being
process.calibTreeMakerJPT.WriteDiJetTree          = True
process.calibTreeMakerJPT.WriteStableGenParticles = False
process.calibTreeMakerJPT.OutputFile        = 'ak5JPT.root'
process.calibTreeMakerJPT.NJet_Jets         = 'JetPlusTrackZSPCorJetAntiKt5'
process.calibTreeMakerJPT.NJet_JetIDs       = ''
process.calibTreeMakerJPT.NJet_GenJets    = 'ak5GenJets'
process.calibTreeMakerJPT.NJetZSPJets     = 'ZSPJetCorJetAntiKt5'
process.calibTreeMakerJPT.NJet_L2JetCorrector      = cms.string('ak5JPTL2Relative')
process.calibTreeMakerJPT.NJet_L3JetCorrector      = cms.string('ak5JPTL3Absolute')
process.calibTreeMakerJPT.NJet_JPTZSPCorrector     = cms.string('JetPlusTrackZSPCorrectorAntiKt5')
process.calibTreeMakerJPT.NJet_L2L3JetCorrector    = cms.string('ak5JPTL2L3')
process.calibTreeMakerJPT.NJet_L2L3L4JWJetCorrector    = cms.string('ak5JPTL2L3')
process.calibTreeMakerJPT.NJet_L2L3JetCorrectorJPT = cms.string('ak5JPTL2L3')
process.calibTreeMakerJPT.NJetConeSize      = 0.5
#process.calibTreeMakerJPT.NJet_Weight_Tag   = 'genEventWeight'
#process.calibTreeMakerJPT.NJet_Weight       =  600000  #1 #Summer09: 0-15: 1802353.8 (fuer 1mio ca 600000);   20-30: 21194.22 ;   50-80: 10193.66  ;    120-170: 469.1156 ;170-230: 89.325 ; 230-300:19.6624 ; 300-380: 5.1781 ; 380-470: 1.32352 ; 470-600: 0.43106 ; 600-800: 0.29169 ;  800-1k: 0.044800 ; 1k-1.4k: 0.010758 ; 1.4k-1.8k: 0.0007192 ; 1.8-2.2k: 0.000063557 ; 2.2k - 2.6k : 0.000005888; 2.6k-3k: 0.000000517 ; 3k-3.5k: 0.00000004 ; 3.5k-Inf: 0.000000001
#Unfinished  15-20: 47035.54 ; 30-50: 8650.123 ; 80-120: 293.22



process.pDump = cms.Path( process.dump )

process.pMC = cms.Path( #process.dump *
                        process.recoJPTJets *
                        process.myPartons *
                        process.CaloJetPartonMatching
                        * process.genJetParticles
                        * process.ak5GenJets
#                        * process.dump
                        * process.calibTreeMakerCalo
                        * process.calibTreeMakerPF
                        * process.calibTreeMakerTrack
                        * process.calibTreeMakerJPT
                        )

process.schedule = cms.Schedule(process.pMC)
