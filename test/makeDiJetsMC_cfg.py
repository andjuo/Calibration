import FWCore.ParameterSet.Config as cms

process = cms.Process("Calib")


process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold             = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 5000

process.AdaptorConfig = cms.Service("AdaptorConfig",
                                    #tempDir=cms.untracked.string(""),
                                    cacheHint=cms.untracked.string("lazy-download"),
                                    #cacheHint=cms.untracked.string("storage-only"),             
                                    readHint=cms.untracked.string("auto-detect") )


process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    '/store/mc/Summer10/QCDDiJet_Pt0to15/GEN-SIM-RECO/START36_V9_S09-v1/0005/8C35F91C-0D7B-DF11-990E-001A4BA98052.root'
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
process.PFJetPartonMatching = cms.EDProducer("JetPartonMatcher",
   jets = cms.InputTag("ak5PFJets"),
   coneSizeToAssociate = cms.double(0.2),
   partons = cms.InputTag("myPartons")
)
process.JPTJetPartonMatching = cms.EDProducer("JetPartonMatcher",
   jets = cms.InputTag("JetPlusTrackZSPCorJetAntiKt5"),
   coneSizeToAssociate = cms.double(0.2),
   partons = cms.InputTag("myPartons")
)
process.TrackJetPartonMatching = cms.EDProducer("JetPartonMatcher",
   jets = cms.InputTag("ak5TrackJets"),
   coneSizeToAssociate = cms.double(0.2),
   partons = cms.InputTag("myPartons")
)

process.load("RecoJets.Configuration.GenJetParticles_cff")
process.load("RecoJets.Configuration.RecoGenJets_cff")


# Jet Energy Corrections
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')
process.ak5CaloL2Relative.useCondDB = False
process.ak5CaloL3Absolute.useCondDB = False
process.ak5CaloResidual.useCondDB = False
process.ak5PFL2Relative.useCondDB = False
process.ak5PFL3Absolute.useCondDB = False
process.ak5PFResidual.useCondDB = False
process.ak5JPTL2Relative.useCondDB = False
process.ak5JPTL3Absolute.useCondDB = False
process.ak5JPTResidual.useCondDB = False
process.ak5TrackL2Relative.useCondDB = False
process.ak5TrackL3Absolute.useCondDB = False
process.ak7CaloL2Relative.useCondDB = False
process.ak7CaloL3Absolute.useCondDB = False
process.ic5CaloL2Relative.useCondDB = False
process.ic5CaloL3Absolute.useCondDB = False
process.kt4CaloL2Relative.useCondDB = False
process.kt4CaloL3Absolute.useCondDB = False
process.kt6CaloL2Relative.useCondDB = False
process.kt6CaloL3Absolute.useCondDB = False
process.ak5CaloL3Absolute.useCondDB = False
process.ak7PFL2Relative.useCondDB = False
process.ak7PFL3Absolute.useCondDB = False
process.ic5PFL2Relative.useCondDB = False
process.ic5PFL3Absolute.useCondDB = False
process.kt4PFL2Relative.useCondDB = False
process.kt4PFL3Absolute.useCondDB = False
process.kt6PFL2Relative.useCondDB = False
process.kt6PFL3Absolute.useCondDB = False
process.ak5PFL3Absolute.useCondDB = False
#process.ak7JPTL2Relative.useCondDB = False
#process.ak7JPTL3Absolute.useCondDB = False
process.ak5CaloL2Relative.era = "Fall10"
process.ak5CaloL3Absolute.era = "Fall10"
process.ak5CaloResidual.era = "Fall10"
process.ak5PFL2Relative.era = "Fall10"
process.ak5PFL3Absolute.era = "Fall10"
process.ak5PFResidual.era = "Fall10"
process.ak5JPTL2Relative.era = "Fall10"
process.ak5JPTL3Absolute.era = "Fall10"
process.ak5JPTResidual.era = "Fall10"
process.ak5TrackL2Relative.era = "Fall10"
process.ak5TrackL3Absolute.era = "Fall10"
process.ak7CaloL2Relative.era = "Fall10"
process.ak7CaloL3Absolute.era = "Fall10"
process.ic5CaloL2Relative.era = "Fall10"
process.ic5CaloL3Absolute.era = "Fall10"
process.kt4CaloL2Relative.era = "Fall10"
process.kt4CaloL3Absolute.era = "Fall10"
process.kt6CaloL2Relative.era = "Fall10"
process.kt6CaloL3Absolute.era = "Fall10"
process.ak5CaloL3Absolute.era = "Fall10"
process.ak7PFL2Relative.era = "Fall10"
process.ak7PFL3Absolute.era = "Fall10"
process.ic5PFL2Relative.era = "Fall10"
process.ic5PFL3Absolute.era = "Fall10"
process.kt4PFL2Relative.era = "Fall10"
process.kt4PFL3Absolute.era = "Fall10"
process.kt6PFL2Relative.era = "Fall10"
process.kt6PFL3Absolute.era = "Fall10"
process.ak5PFL3Absolute.era = "Fall10"
#process.ak7JPTL2Relative.era = "Fall10"
#process.ak7JPTL3Absolute.era = "Fall10"

process.ak7JPTL3Absolute  = process.ak5CaloL3Absolute.clone( algorithm = 'AK7JPT' )
process.ak7JPTL2Relative  = process.ak5CaloL2Relative.clone( algorithm = 'AK7JPT' )
process.ak7JPTL2L3 = cms.ESSource(
    'JetCorrectionServiceChain',
    correctors = cms.vstring('ak7JPTL2Relative','ak7JPTL3Absolute')
    )
# L4JW Correction Services
# you need special versions of CondFormats and JetMETCorrections:
# copy the following dirs to your release (this works with 3_8_4):
# /afs/cern.ch/user/s/stadie/public/CondFormats
# /afs/cern.ch/user/s/stadie/public/JetMETCorrections
#

#process.ak5CaloL4JW = cms.ESSource(
#    'LXXXCorrectionService',
#    era = cms.string('Spring10'),
#    section   = cms.string(''),
#    level     = cms.string('L4JW'),
#    algorithm = cms.string('AK5Calo'),
#    useCondDB = cms.untracked.bool(False)
#    )
#process.ak5CaloL2L3L4JW = process.ak5CaloL2L3.clone()
#process.ak5CaloL2L3L4JW.correctors.append('ak5CaloL4JW')

# ZSP and JPT corrections
process.load("RecoJets.Configuration.RecoJPTJets_cff")


###  Parameters for module calibTreeMaker
process.calibTreeMakerCalo.WriteDiJetTree          = True
process.calibTreeMakerCalo.WriteStableGenParticles = False
process.calibTreeMakerCalo.OutputFile         = 'ak5Calo.root'
process.calibTreeMakerCalo.NJet_Jets         = 'ak5CaloJets'
process.calibTreeMakerCalo.NJet_JetIDs       = 'ak5JetID'
process.calibTreeMakerCalo.NJet_PartonMatch  = 'CaloJetPartonMatching'
process.calibTreeMakerCalo.NJet_GenJets      = 'ak5GenJets'
process.calibTreeMakerCalo.NJetZSPJets       = 'ZSPJetCorJetAntiKt5'
process.calibTreeMakerCalo.NJet_L2JetCorrector      = cms.string('ak5CaloL2Relative')
process.calibTreeMakerCalo.NJet_L3JetCorrector      = cms.string('ak5CaloL3Absolute')
process.calibTreeMakerCalo.NJet_JPTZSPCorrector     = cms.string('JetPlusTrackZSPCorrectorAntiKt5')
process.calibTreeMakerCalo.NJet_L2L3JetCorrector    = cms.string('ak5CaloL2L3')
process.calibTreeMakerCalo.NJet_L2L3L4JWJetCorrector = cms.string('ak5CaloL2L3')
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
process.calibTreeMakerPF.NJet_PartonMatch  = 'PFJetPartonMatching'
process.calibTreeMakerPF.NJet_GenJets      = 'ak5GenJets'
process.calibTreeMakerPF.NJetZSPJets       = 'ZSPJetCorJetAntiKt5'
process.calibTreeMakerPF.NJet_L2JetCorrector      = cms.string('ak5PFL2Relative')
process.calibTreeMakerPF.NJet_L3JetCorrector      = cms.string('ak5PFL3Absolute')
process.calibTreeMakerPF.NJet_JPTZSPCorrector     = cms.string('JetPlusTrackZSPCorrectorAntiKt5')
process.calibTreeMakerPF.NJet_L2L3JetCorrector    = cms.string('ak5PFL2L3')
process.calibTreeMakerPF.NJet_L2L3L4JWJetCorrector = cms.string('ak5PFL2L3')
process.calibTreeMakerPF.NJet_L2L3JetCorrectorJPT = cms.string('ak5JPTL2L3')
process.calibTreeMakerPF.NJetConeSize      = 0.5

process.calibTreeMakerTrack.WriteDiJetTree          = True
process.calibTreeMakerTrack.WriteStableGenParticles = False
process.calibTreeMakerTrack.OutputFile        = 'ak5Track.root'
process.calibTreeMakerTrack.NJet_Jets         = 'ak5TrackJets'
process.calibTreeMakerTrack.NJet_JetIDs       = ''
process.calibTreeMakerTrack.NJet_PartonMatch  = 'TrackJetPartonMatching'
process.calibTreeMakerTrack.NJet_GenJets      = 'ak5GenJets'
process.calibTreeMakerTrack.NJetZSPJets       = 'ZSPJetCorJetAntiKt5'
process.calibTreeMakerTrack.NJet_L2JetCorrector      = cms.string('ak5TrackL2Relative')
process.calibTreeMakerTrack.NJet_L3JetCorrector      = cms.string('ak5TrackL3Absolute')
process.calibTreeMakerTrack.NJet_JPTZSPCorrector     = cms.string('JetPlusTrackZSPCorrectorAntiKt5')
process.calibTreeMakerTrack.NJet_L2L3JetCorrector    = cms.string('ak5TrackL2L3')
process.calibTreeMakerTrack.NJet_L2L3L4JWJetCorrector    = cms.string('ak5TrackL2L3')
process.calibTreeMakerTrack.NJet_L2L3JetCorrectorJPT = cms.string('ak5JPTL2L3')
process.calibTreeMakerTrack.NJetConeSize      = 0.5


process.calibTreeMakerJPT.WriteDiJetTree          = True
process.calibTreeMakerJPT.WriteStableGenParticles = False
process.calibTreeMakerJPT.OutputFile        = 'ak5JPT.root'
process.calibTreeMakerJPT.NJet_Jets         = 'JetPlusTrackZSPCorJetAntiKt5'
process.calibTreeMakerJPT.NJet_JetIDs       = ''
process.calibTreeMakerJPT.NJet_PartonMatch  = 'JPTJetPartonMatching'
process.calibTreeMakerJPT.NJet_GenJets    = 'ak5GenJets'
process.calibTreeMakerJPT.NJetZSPJets     = 'ZSPJetCorJetAntiKt5'
process.calibTreeMakerJPT.NJet_L2JetCorrector      = cms.string('ak5JPTL2Relative')
process.calibTreeMakerJPT.NJet_L3JetCorrector      = cms.string('ak5JPTL3Absolute')
process.calibTreeMakerJPT.NJet_JPTZSPCorrector     = cms.string('JetPlusTrackZSPCorrectorAntiKt5')
process.calibTreeMakerJPT.NJet_L2L3JetCorrector    = cms.string('ak5JPTL2L3')
process.calibTreeMakerJPT.NJet_L2L3L4JWJetCorrector    = cms.string('ak5JPTL2L3')
process.calibTreeMakerJPT.NJet_L2L3JetCorrectorJPT = cms.string('ak5JPTL2L3')
process.calibTreeMakerJPT.NJetConeSize      = 0.5


process.AK7CaloJetPartonMatching = process.CaloJetPartonMatching.clone( 
    jets = 'ak7CaloJets' 
)
process.calibTreeMakerAK7Calo = process.calibTreeMakerCalo.clone(
    OutputFile = 'ak7Calo.root',
    NJet_Jets  = 'ak7CaloJets',
    NJet_JetIDs = 'ak7JetID',
    NJet_PartonMatch = 'AK7CaloJetPartonMatching',
    NJet_GenJets = 'ak7GenJets',
    NJet_L2JetCorrector = 'ak7CaloL2Relative',
    NJet_L3JetCorrector = 'ak7CaloL3Absolute',
    NJet_L2L3JetCorrector = 'ak7CaloL2L3',
    NJet_L2L3L4JWJetCorrector = 'ak7CaloL2L3'
)

process.IC5CaloJetPartonMatching = process.CaloJetPartonMatching.clone( 
    jets = 'iterativeCone5CaloJets' 
)
process.calibTreeMakerIC5Calo = process.calibTreeMakerCalo.clone(
    OutputFile = 'ic5Calo.root',
    NJet_Jets  = 'iterativeCone5CaloJets',
    NJet_JetIDs = 'ic5JetID',
    NJet_PartonMatch = 'IC5CaloJetPartonMatching',
    NJet_GenJets = 'iterativeCone5GenJets',
    NJet_L2JetCorrector = 'ic5CaloL2Relative',
    NJet_L3JetCorrector = 'ic5CaloL3Absolute',
    NJet_L2L3JetCorrector = 'ic5CaloL2L3',
    NJet_L2L3L4JWJetCorrector = 'ic5CaloL2L3'
)

process.KT4CaloJetPartonMatching = process.CaloJetPartonMatching.clone( 
    jets = 'kt4CaloJets' 
)
process.calibTreeMakerKT4Calo = process.calibTreeMakerCalo.clone(
    OutputFile = 'kt4Calo.root',
    NJet_Jets  = 'kt4CaloJets',
    NJet_JetIDs = 'kt4JetID',
    NJet_PartonMatch = 'KT4CaloJetPartonMatching',
    NJet_GenJets = 'kt4GenJets',
    NJet_L2JetCorrector = 'kt4CaloL2Relative',
    NJet_L3JetCorrector = 'kt4CaloL3Absolute',
    NJet_L2L3JetCorrector = 'kt4CaloL2L3',
    NJet_L2L3L4JWJetCorrector = 'kt4CaloL2L3'
)

process.KT6CaloJetPartonMatching = process.CaloJetPartonMatching.clone( 
    jets = 'kt6CaloJets' 
)

process.calibTreeMakerKT6Calo = process.calibTreeMakerCalo.clone(
    OutputFile = 'kt6Calo.root',
    NJet_Jets  = 'kt6CaloJets',
    NJet_JetIDs = 'kt6JetID',
    NJet_PartonMatch = 'KT6CaloJetPartonMatching',
    NJet_GenJets = 'kt6GenJets',
    NJet_L2JetCorrector = 'kt6CaloL2Relative',
    NJet_L3JetCorrector = 'kt6CaloL3Absolute',
    NJet_L2L3JetCorrector = 'kt6CaloL2L3',
    NJet_L2L3L4JWJetCorrector = 'kt6CaloL2L3'
)

process.AK7PFJetPartonMatching = process.PFJetPartonMatching.clone( 
    jets = 'ak7PFJets' 
)
process.calibTreeMakerAK7PF = process.calibTreeMakerPF.clone(
    OutputFile = 'ak7PF.root',
    NJet_Jets  = 'ak7PFJets',
    NJet_PartonMatch = 'AK7PFJetPartonMatching',
    NJet_GenJets = 'ak7GenJets',
    NJet_L2JetCorrector = 'ak7PFL2Relative',
    NJet_L3JetCorrector = 'ak7PFL3Absolute',
    NJet_L2L3JetCorrector = 'ak7PFL2L3',
    NJet_L2L3L4JWJetCorrector = 'ak7PFL2L3'
)

process.IC5PFJetPartonMatching = process.PFJetPartonMatching.clone( 
    jets = 'iterativeCone5PFJets' 
)
process.calibTreeMakerIC5PF = process.calibTreeMakerPF.clone(
    OutputFile = 'ic5PF.root',
    NJet_Jets  = 'iterativeCone5PFJets',
    NJet_PartonMatch = 'IC5PFJetPartonMatching',
    NJet_GenJets = 'iterativeCone5GenJets',
    NJet_L2JetCorrector = 'ic5PFL2Relative',
    NJet_L3JetCorrector = 'ic5PFL3Absolute',
    NJet_L2L3JetCorrector = 'ic5PFL2L3',
    NJet_L2L3L4JWJetCorrector = 'ic5PFL2L3'
)

process.KT4PFJetPartonMatching = process.PFJetPartonMatching.clone( 
    jets = 'kt4PFJets' 
)
process.calibTreeMakerKT4PF = process.calibTreeMakerPF.clone(
    OutputFile = 'kt4PF.root',
    NJet_Jets  = 'kt4PFJets',
    NJet_PartonMatch = 'KT4PFJetPartonMatching',
    NJet_GenJets = 'kt4GenJets',
    NJet_L2JetCorrector = 'kt4PFL2Relative',
    NJet_L3JetCorrector = 'kt4PFL3Absolute',
    NJet_L2L3JetCorrector = 'kt4PFL2L3',
    NJet_L2L3L4JWJetCorrector = 'kt4PFL2L3'
)

process.KT6PFJetPartonMatching = process.PFJetPartonMatching.clone( 
    jets = 'kt6PFJets' 
)

process.calibTreeMakerKT6PF = process.calibTreeMakerPF.clone(
    OutputFile = 'kt6PF.root',
    NJet_Jets  = 'kt6PFJets',
    NJet_PartonMatch = 'KT6PFJetPartonMatching',
    NJet_GenJets = 'kt6GenJets',
    NJet_L2JetCorrector = 'kt6PFL2Relative',
    NJet_L3JetCorrector = 'kt6PFL3Absolute',
    NJet_L2L3JetCorrector = 'kt6PFL2L3',
    NJet_L2L3L4JWJetCorrector = 'kt6PFL2L3'
)

process.pDump = cms.Path( process.dump )

process.pMC = cms.Path( #process.dump *
                        #process.recoJPTJets *
                        process.myPartons *
                        process.CaloJetPartonMatching
                        * process.PFJetPartonMatching
                        * process.JPTJetPartonMatching
                        * process.TrackJetPartonMatching
#                        * process.genJetParticles
#                        * process.recoGenJets
#                        * process.dump
                        * process.calibTreeMakerCalo
                        * process.calibTreeMakerPF
#                        * process.calibTreeMakerTrack
                        * process.calibTreeMakerJPT
                        * process.AK7CaloJetPartonMatching
                        * process.calibTreeMakerAK7Calo
                        * process.IC5CaloJetPartonMatching
                        * process.calibTreeMakerIC5Calo
                        * process.KT4CaloJetPartonMatching
                        * process.calibTreeMakerKT4Calo
                        * process.KT6CaloJetPartonMatching
                        * process.calibTreeMakerKT6Calo
                        * process.AK7PFJetPartonMatching
                        * process.calibTreeMakerAK7PF
                        * process.IC5PFJetPartonMatching
                        * process.calibTreeMakerIC5PF
                        * process.KT4PFJetPartonMatching
                        * process.calibTreeMakerKT4PF
                        * process.KT6PFJetPartonMatching
                        * process.calibTreeMakerKT6PF
                        )

process.schedule = cms.Schedule(process.pMC)
