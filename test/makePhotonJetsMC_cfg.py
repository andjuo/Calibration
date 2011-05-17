import FWCore.ParameterSet.Config as cms
import os

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
#    '/store/mc/Spring11/QCD_Pt_15to3000_Flat_7TeV/AODSIM/START311_V1A-v1/0000/D6F6452C-3847-E011-A36C-003048D4770C.root'
    '/store/mc/Spring11/QCD_Pt_15to3000_TuneZ2_Flat_7TeV_pythia6/AODSIM/PU_S1_START311_V1G1-v1/0030/CEAF3187-C652-E011-BA2D-00215E222382.root'
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
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagator_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAny_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAlong_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorOpposite_cfi")
process.load("TrackingTools.TrackAssociator.DetIdAssociatorESProducer_cff")
process.load("TrackingTools.TrackAssociator.default_cfi")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'START311_V2::All'

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
process.load("CondCore.DBCommon.CondDBCommon_cfi")
process.jec = cms.ESSource("PoolDBESSource",
      DBParameters = cms.PSet(
        messageLevel = cms.untracked.int32(0)
        ),
      timetype = cms.string('runnumber'),
      toGet = cms.VPSet(
      cms.PSet(
            record = cms.string('JetCorrectionsRecord'),
            tag    = cms.string('JetCorrectorParametersCollection_Jec10V3_AK5PF'),
            label  = cms.untracked.string('AK5PF')
            ),
     cms.PSet(
            record = cms.string('JetCorrectionsRecord'),
            tag    = cms.string('JetCorrectorParametersCollection_Jec10V3_AK5Calo'),
            label  = cms.untracked.string('AK5Calo')
            ),
     cms.PSet(
            record = cms.string('JetCorrectionsRecord'),
            tag    = cms.string('JetCorrectorParametersCollection_Jec10V3_AK5JPT'),
            label  = cms.untracked.string('AK5JPT')
            ),
     cms.PSet(
            record = cms.string('JetCorrectionsRecord'),
            tag    = cms.string('JetCorrectorParametersCollection_Jec10V3_AK7PF'),
            label  = cms.untracked.string('AK7PF')
            ),
     cms.PSet(
            record = cms.string('JetCorrectionsRecord'),
            tag    = cms.string('JetCorrectorParametersCollection_Jec10V3_AK7Calo'),
            label  = cms.untracked.string('AK7Calo')
            ),
     cms.PSet(
            record = cms.string('JetCorrectionsRecord'),
            tag    = cms.string('JetCorrectorParametersCollection_Jec10V3_KT4PF'),
            label  = cms.untracked.string('KT4PF')
            ),
     cms.PSet(
            record = cms.string('JetCorrectionsRecord'),
            tag    = cms.string('JetCorrectorParametersCollection_Jec10V3_KT6PF'),
            label  = cms.untracked.string('KT6PF')
            ),
     cms.PSet(
            record = cms.string('JetCorrectionsRecord'),
            tag    = cms.string('JetCorrectorParametersCollection_Jec10V3_KT4Calo'),
            label  = cms.untracked.string('KT4Calo')
            ),
     cms.PSet(
            record = cms.string('JetCorrectionsRecord'),
            tag    = cms.string('JetCorrectorParametersCollection_Jec10V3_KT6Calo'),
            label  = cms.untracked.string('KT6Calo')
            )
      ),
      ## here you add as many jet types as you need (AK5Calo, AK5JPT, AK7PF, AK7Calo, KT4PF, KT4Calo, KT6PF, KT6Calo)
      connect = cms.string('sqlite_file:'+os.environ['CMSSW_BASE']+'/src/Jec10V3.db/Jec10V3.db')
)

process.es_prefer_jec = cms.ESPrefer('PoolDBESSource','jec')

# ZSP and JPT corrections
process.load("RecoJets.Configuration.RecoJPTJets_cff")

##################################################################
#  Parameters for module calibTreeMaker
##################################################################
process.calibTreeMakerCalo.WriteStableGenParticles = False
process.calibTreeMakerCalo.WriteStableGenParticles = False
process.calibTreeMakerCalo.OutputFile         = 'ak5Calo.root'
process.calibTreeMakerCalo.TreeName          = "GammaJetTree"
process.calibTreeMakerCalo.NJet_Jets         = 'ak5CaloJets'
process.calibTreeMakerCalo.NJet_JetIDs       = 'ak5JetID'
process.calibTreeMakerCalo.NJet_GenJets      = 'ak5GenJets'
process.calibTreeMakerCalo.NJet_PartonMatch  = 'CaloJetPartonMatching'
process.calibTreeMakerCalo.NJetZSPJets       = 'ZSPJetCorJetAntiKt5'
process.calibTreeMakerCalo.NJet_L1JetCorrector      = cms.string('ak5CaloL1Offset')
process.calibTreeMakerCalo.NJet_L2JetCorrector      = cms.string('ak5CaloL2Relative')
process.calibTreeMakerCalo.NJet_L3JetCorrector      = cms.string('ak5CaloL3Absolute')
process.calibTreeMakerCalo.NJet_JPTZSPCorrector     = cms.string('JetPlusTrackZSPCorrectorAntiKt5')
process.calibTreeMakerCalo.NJet_L2L3JetCorrector    = cms.string('ak5CaloL2L3Residual')
process.calibTreeMakerCalo.NJet_L2L3L4JWJetCorrector    = cms.string('ak5CaloL2L3Residual')
process.calibTreeMakerCalo.NJet_L2L3JetCorrectorJPT = cms.string('ak5JPTL2L3')
process.calibTreeMakerCalo.NJetConeSize      = 0.5
process.calibTreeMakerCalo.WritePhotons = True

process.calibTreeMakerPF.WriteStableGenParticles = False
process.calibTreeMakerPF.OutputFile         = 'ak5PF.root'
process.calibTreeMakerPF.TreeName          = "GammaJetTree"
process.calibTreeMakerPF.NJet_Jets         = 'ak5PFJets'
process.calibTreeMakerPF.NJet_JetIDs       = ''
process.calibTreeMakerPF.NJet_GenJets      = 'ak5GenJets'
process.calibTreeMakerPF.NJet_PartonMatch  = 'PFJetPartonMatching'
process.calibTreeMakerPF.NJetZSPJets       = 'ZSPJetCorJetAntiKt5'
process.calibTreeMakerPF.NJet_L1JetCorrector      = cms.string('ak5PFL1Offset')
process.calibTreeMakerPF.NJet_L2JetCorrector      = cms.string('ak5PFL2Relative')
process.calibTreeMakerPF.NJet_L3JetCorrector      = cms.string('ak5PFL3Absolute')
process.calibTreeMakerPF.NJet_JPTZSPCorrector     = cms.string('JetPlusTrackZSPCorrectorAntiKt5')
process.calibTreeMakerPF.NJet_L2L3JetCorrector    = cms.string('ak5PFL2L3Residual')
process.calibTreeMakerPF.NJet_L2L3L4JWJetCorrector    = cms.string('ak5PFL2L3Residual')
process.calibTreeMakerPF.NJet_L2L3JetCorrectorJPT = cms.string('ak5JPTL2L3Residual')
process.calibTreeMakerPF.NJetConeSize      = 0.5
process.calibTreeMakerPF.WritePhotons = True


process.calibTreeMakerTrack.WriteStableGenParticles = False
process.calibTreeMakerTrack.OutputFile        = 'ak5Track.root'
process.calibTreeMakerTrack.TreeName          = "GammaJetTree"
process.calibTreeMakerTrack.NJet_Jets         = 'ak5TrackJets'
process.calibTreeMakerTrack.NJet_JetIDs       = ''
process.calibTreeMakerTrack.NJet_GenJets      = 'ak5GenJets'
process.calibTreeMakerTrack.NJet_PartonMatch  = 'JPTJetPartonMatching'
process.calibTreeMakerTrack.NJetZSPJets       = 'ZSPJetCorJetAntiKt5'
process.calibTreeMakerTrack.WritePhotons = True

process.calibTreeMakerTrack.NJet_L1JetCorrector      = cms.string('ak5PFL1Offset')
process.calibTreeMakerTrack.NJet_L2JetCorrector      = cms.string('ak5TrackL2Relative')
process.calibTreeMakerTrack.NJet_L3JetCorrector      = cms.string('ak5TrackL3Absolute')
process.calibTreeMakerTrack.NJet_JPTZSPCorrector     = cms.string('JetPlusTrackZSPCorrectorAntiKt5')
process.calibTreeMakerTrack.NJet_L2L3JetCorrector    = cms.string('ak5TrackL2L3')
process.calibTreeMakerTrack.NJet_L2L3L4JWJetCorrector    = cms.string('ak5TrackL2L3')
process.calibTreeMakerTrack.NJet_L2L3JetCorrectorJPT = cms.string('ak5JPTL2L3Residual')
process.calibTreeMakerTrack.NJetConeSize      = 0.5

process.calibTreeMakerJPT.WriteStableGenParticles = False
process.calibTreeMakerJPT.OutputFile        = 'ak5JPT.root'
process.calibTreeMakerJPT.TreeName          = "GammaJetTree"
process.calibTreeMakerJPT.NJet_Jets         = 'JetPlusTrackZSPCorJetAntiKt5'
process.calibTreeMakerJPT.NJet_JetIDs       = 'ak5JetID'
process.calibTreeMakerJPT.NJet_GenJets    = 'ak5GenJets'
process.calibTreeMakerJPT.NJet_PartonMatch  = 'JPTJetPartonMatching'
process.calibTreeMakerJPT.NJetZSPJets     = 'ZSPJetCorJetAntiKt5'
process.calibTreeMakerJPT.NJet_L1JetCorrector      = cms.string('ak5JPTL1Offset')
process.calibTreeMakerJPT.NJet_L2JetCorrector      = cms.string('ak5JPTL2Relative')
process.calibTreeMakerJPT.NJet_L3JetCorrector      = cms.string('ak5JPTL3Absolute')
process.calibTreeMakerJPT.NJet_JPTZSPCorrector     = cms.string('JetPlusTrackZSPCorrectorAntiKt5')
process.calibTreeMakerJPT.NJet_L2L3JetCorrector    = cms.string('ak5JPTL2L3Residual')
process.calibTreeMakerJPT.NJet_L2L3L4JWJetCorrector    = cms.string('ak5JPTL2L3Residual')
process.calibTreeMakerJPT.NJet_L2L3JetCorrectorJPT = cms.string('ak5JPTL2L3Residual')
process.calibTreeMakerJPT.NJetConeSize      = 0.5
process.calibTreeMakerJPT.WritePhotons = True


process.AK7CaloJetPartonMatching = process.CaloJetPartonMatching.clone( 
    jets = 'ak7CaloJets' 
)

process.calibTreeMakerAK7Calo = process.calibTreeMakerCalo.clone(
    OutputFile = 'ak7Calo.root',
    NJet_Jets  = 'ak7CaloJets',
    NJet_JetIDs = 'ak7JetID',
    NJet_PartonMatch = 'AK7CaloJetPartonMatching',
    NJet_GenJets = 'ak7GenJets',
    NJet_L1JetCorrector = 'ak7CaloL1Offset',
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
    NJet_L1JetCorrector = 'ic5CaloL1Offset',
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
    NJet_L1JetCorrector = 'kt4CaloL1Offset',
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
    NJet_L1JetCorrector = 'kt6CaloL1Offset',
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
    NJet_L1JetCorrector = 'ak7PFL1Offset',
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
    NJet_L1JetCorrector = 'ic5PFL1Offset',
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
    NJet_L1JetCorrector = 'kt4PFL1Offset',
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
    NJet_L1JetCorrector = 'kt6PFL1Offset',
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
                        * process.genParticleCandidates
                        * process.genPhotonCandidates 
                        *  process.goodGenPhotons
#                        * process.TrackJetPartonMatching
#                        * process.genJetParticles
#                        * process.recoGenJets
#                        * process.dump
                        * process.calibTreeMakerCalo
                        * process.calibTreeMakerPF
#                        * process.calibTreeMakerTrack
                        * process.calibTreeMakerJPT
                        * process.AK7CaloJetPartonMatching
                        * process.calibTreeMakerAK7Calo
 #                       * process.IC5CaloJetPartonMatching
 #                       * process.calibTreeMakerIC5Calo
                        * process.KT4CaloJetPartonMatching
                        * process.calibTreeMakerKT4Calo
                        * process.KT6CaloJetPartonMatching
                        * process.calibTreeMakerKT6Calo
                        * process.AK7PFJetPartonMatching
                        * process.calibTreeMakerAK7PF
#                        * process.IC5PFJetPartonMatching
#                        * process.calibTreeMakerIC5PF
                        * process.KT4PFJetPartonMatching
                        * process.calibTreeMakerKT4PF
                        * process.KT6PFJetPartonMatching
                        * process.calibTreeMakerKT6PF
                        )

process.schedule = cms.Schedule(process.pMC)
