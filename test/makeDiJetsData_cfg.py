import FWCore.ParameterSet.Config as cms

process = cms.Process("Calib")


process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold             = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 5000


process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
        '/store/data/Run2011A/Jet/AOD/PromptReco-v1/000/161/311/7293853E-CA57-E011-8DEF-001D09F24D4E.root'
#        '/store/data/Run2010B/Jet/AOD/Nov4ReReco_v1/0037/CC0418DC-22EB-DF11-9D28-002481E0D50C.root',
#        '/store/data/Run2010A/JetMET/RECO/Nov4ReReco_v1/0111/3A4C3A92-87E9-DF11-83FA-003048678C9A.root',
#        '/store/data/Run2010B/Jet/RECO/Nov4ReReco_v1/0039/3A0C842D-A4EB-DF11-B0F8-002481E94B2A.root'
    #'/store/data/Run2010A/JetMETTau/RECO/v1/000/136/082/147EC62F-DF66-DF11-9678-003048D2BE08.root'
    #'/store/data/Commissioning10/MinimumBias/RECO/May6thPDSkim2_SD_JetMETTau-v1/0137/FE3CCCB6-D05D-DF11-BB30-00261894383F.root'
    # '/store/data/Commissioning10/MinimumBias/RECO/GOODCOLL-Jun9thSkim_v1/0039/20C793BD-3678-DF11-AF29-0018F3D09706.root'
    # '/store/data/Run2010A/JetMET/RECO/v4/000/141/960/48753CF6-D39B-DF11-AB95-0030487A18F2.root'
    #'/store/data/Run2010A/JetMET/RECO/Sep17ReReco_v2/0024/7E51025E-18C7-DF11-BEA3-0018F3D0962A.root'
            )
                            )

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(50) )

process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(True)
)


# Trigger
process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff')
process.load('HLTrigger/HLTfilters/hltLevel1GTSeed_cfi')
process.hltLevel1GTSeed.L1TechTriggerSeeding = cms.bool(True)
process.hltLevel1GTSeed.L1SeedsLogicalExpression = cms.string('0 AND (40 OR 41) AND NOT (36 OR 37 OR 38 OR 39) AND NOT ((42 AND NOT 43) OR (43 AND NOT 42))')

# HLT
process.load('HLTrigger.HLTfilters.hltHighLevel_cfi')
process.hltHighLevel.HLTPaths = ('HLT_DiJetAve15U','HLT_DiJetAve30U','HLT_DiJetAve50U','HLT_DiJetAve70U','HLT_DiJetAve100U','HLT_DiJetAve140U','HLT_DiJetAve15U_v*','HLT_DiJetAve30U_v*','HLT_DiJetAve50U_v*','HLT_DiJetAve70U_v*','HLT_DiJetAve100U_v*','HLT_DiJetAve140U_v*','HLT_DiJetAve180U_v*','HLT_DiJetAve300U_v*')
#process.hltHighLevel.HLTPaths = cms.vstring('HLT_DiJetAve30U')
process.hltHighLevel.andOr = cms.bool(True)
process.hltHighLevel.throw = cms.bool(False)

# Vertex filter
process.primaryVertexFilter = cms.EDFilter("VertexSelector",
   src = cms.InputTag("offlinePrimaryVertices"),
   cut = cms.string("!isFake && ndof > 4 && abs(z) <= 24 && position.Rho <= 2"), # tracksSize() > 3 for the older cut
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
process.load('Configuration/StandardSequences/GeometryDB_cff')
process.load('Configuration/StandardSequences/MagneticField_AutoFromDBCurrent_cff')
process.load("Configuration/StandardSequences/Reconstruction_cff")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagator_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAny_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAlong_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorOpposite_cfi")
process.load("TrackingTools.TrackAssociator.DetIdAssociatorESProducer_cff")
process.load("TrackingTools.TrackAssociator.default_cfi")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'GR_R_311_V2::All'


process.load("Calibration.CalibTreeMaker.CalibTreeMaker_cfi")

process.load("RecoJets.Configuration.RecoJets_cff")

process.dump = cms.EDAnalyzer("EventContentAnalyzer")


process.load("RecoJets.Configuration.GenJetParticles_cff")
process.load("RecoJets.Configuration.RecoGenJets_cff")


# Jet Energy Corrections
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')

# L4JW and L2L3Residual Correction Services
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
#)
#process.ak5CaloL2L3L4JW = cms.ESSource(
#    'JetCorrectionServiceChain',
#    correctors = cms.vstring('ak5CaloL2L3Residual','ak5CaloL4JW')
#)

# ZSP and JPT corrections
process.load("RecoJets.Configuration.RecoJPTJets_cff")

##################################################################
#  Parameters for module calibTreeMaker
##################################################################
process.calibTreeMakerCalo.WriteDiJetTree          = True
process.calibTreeMakerCalo.WriteStableGenParticles = False
process.calibTreeMakerCalo.WriteStableGenParticles = False
process.calibTreeMakerCalo.OutputFile         = 'ak5Calo.root'
process.calibTreeMakerCalo.NJet_Jets         = 'ak5CaloJets'
process.calibTreeMakerCalo.NJet_JetIDs       = 'ak5JetID'
process.calibTreeMakerCalo.NJet_GenJets      = 'ak5GenJets'
process.calibTreeMakerCalo.NJetZSPJets       = 'ZSPJetCorJetAntiKt5'
process.calibTreeMakerCalo.NJet_L1JetCorrector      = cms.string('ak5CaloL1Offset')
process.calibTreeMakerCalo.NJet_L2JetCorrector      = cms.string('ak5CaloL2Relative')
process.calibTreeMakerCalo.NJet_L3JetCorrector      = cms.string('ak5CaloL3Absolute')
process.calibTreeMakerCalo.NJet_JPTZSPCorrector     = cms.string('JetPlusTrackZSPCorrectorAntiKt5')
process.calibTreeMakerCalo.NJet_L2L3JetCorrector    = cms.string('ak5CaloL2L3Residual')
process.calibTreeMakerCalo.NJet_L2L3L4JWJetCorrector    = cms.string('ak5CaloL2L3Residual')
process.calibTreeMakerCalo.NJet_L2L3JetCorrectorJPT = cms.string('ak5JPTL2L3')
process.calibTreeMakerCalo.NJetConeSize      = 0.5

process.calibTreeMakerPF.WriteDiJetTree          = True
process.calibTreeMakerPF.WriteStableGenParticles = False
process.calibTreeMakerPF.OutputFile         = 'ak5PF.root'
process.calibTreeMakerPF.NJet_Jets         = 'ak5PFJets'
process.calibTreeMakerPF.NJet_JetIDs       = ''
process.calibTreeMakerPF.NJet_GenJets      = 'ak5GenJets'
process.calibTreeMakerPF.NJetZSPJets       = 'ZSPJetCorJetAntiKt5'
process.calibTreeMakerPF.NJet_L1JetCorrector      = cms.string('ak5PFL1Offset')
process.calibTreeMakerPF.NJet_L2JetCorrector      = cms.string('ak5PFL2Relative')
process.calibTreeMakerPF.NJet_L3JetCorrector      = cms.string('ak5PFL3Absolute')
process.calibTreeMakerPF.NJet_JPTZSPCorrector     = cms.string('JetPlusTrackZSPCorrectorAntiKt5')
process.calibTreeMakerPF.NJet_L2L3JetCorrector    = cms.string('ak5PFL2L3Residual')
process.calibTreeMakerPF.NJet_L2L3L4JWJetCorrector    = cms.string('ak5PFL2L3Residual')
process.calibTreeMakerPF.NJet_L2L3JetCorrectorJPT = cms.string('ak5JPTL2L3Residual')
process.calibTreeMakerPF.NJetConeSize      = 0.5


process.calibTreeMakerTrack.WriteDiJetTree          = True
process.calibTreeMakerTrack.WriteStableGenParticles = False
process.calibTreeMakerTrack.OutputFile        = 'ak5Track.root'
process.calibTreeMakerTrack.NJet_Jets         = 'ak5TrackJets'
process.calibTreeMakerTrack.NJet_JetIDs       = ''
process.calibTreeMakerTrack.NJet_GenJets      = 'ak5GenJets'
process.calibTreeMakerTrack.NJetZSPJets       = 'ZSPJetCorJetAntiKt5'

#ATTENTION: use CALO correction for the time being....
process.calibTreeMakerTrack.NJet_L1JetCorrector      = cms.string('ak5PFL1Offset')
process.calibTreeMakerTrack.NJet_L2JetCorrector      = cms.string('ak5TrackL2Relative')
process.calibTreeMakerTrack.NJet_L3JetCorrector      = cms.string('ak5TrackL3Absolute')
process.calibTreeMakerTrack.NJet_JPTZSPCorrector     = cms.string('JetPlusTrackZSPCorrectorAntiKt5')
process.calibTreeMakerTrack.NJet_L2L3JetCorrector    = cms.string('ak5TrackL2L3')
process.calibTreeMakerTrack.NJet_L2L3L4JWJetCorrector    = cms.string('ak5TrackL2L3')
process.calibTreeMakerTrack.NJet_L2L3JetCorrectorJPT = cms.string('ak5JPTL2L3Residual')
process.calibTreeMakerTrack.NJetConeSize      = 0.5

#ATTENTION: use CALOcorrections for the time being
process.calibTreeMakerJPT.WriteDiJetTree          = True
process.calibTreeMakerJPT.WriteStableGenParticles = False
process.calibTreeMakerJPT.OutputFile        = 'ak5JPT.root'
process.calibTreeMakerJPT.NJet_Jets         = 'JetPlusTrackZSPCorJetAntiKt5'
process.calibTreeMakerJPT.NJet_JetIDs       = ''
process.calibTreeMakerJPT.NJet_GenJets    = 'ak5GenJets'
process.calibTreeMakerJPT.NJetZSPJets     = 'ZSPJetCorJetAntiKt5'
process.calibTreeMakerJPT.NJet_L1JetCorrector      = cms.string('ak5JPTL1Offset')
process.calibTreeMakerJPT.NJet_L2JetCorrector      = cms.string('ak5JPTL2Relative')
process.calibTreeMakerJPT.NJet_L3JetCorrector      = cms.string('ak5JPTL3Absolute')
process.calibTreeMakerJPT.NJet_JPTZSPCorrector     = cms.string('JetPlusTrackZSPCorrectorAntiKt5')
process.calibTreeMakerJPT.NJet_L2L3JetCorrector    = cms.string('ak5JPTL2L3Residual')
process.calibTreeMakerJPT.NJet_L2L3L4JWJetCorrector    = cms.string('ak5JPTL2L3Residual')
process.calibTreeMakerJPT.NJet_L2L3JetCorrectorJPT = cms.string('ak5JPTL2L3Residual')
process.calibTreeMakerJPT.NJetConeSize      = 0.5

process.calibTreeMakerAK7Calo = process.calibTreeMakerCalo.clone(
    OutputFile = 'ak7Calo.root',
    NJet_Jets  = 'ak7CaloJets',
    NJet_JetIDs = 'ak7JetID',
    NJet_PartonMatch = '',
    NJet_GenJets = 'ak7GenJets',
    NJet_L1JetCorrector = 'ak7CaloL1Offset',
    NJet_L2JetCorrector = 'ak7CaloL2Relative',
    NJet_L3JetCorrector = 'ak7CaloL3Absolute',
    NJet_L2L3JetCorrector = 'ak7CaloL2L3',
    NJet_L2L3L4JWJetCorrector = 'ak7CaloL2L3'
)
process.calibTreeMakerIC5Calo = process.calibTreeMakerCalo.clone(
    OutputFile = 'ic5Calo.root',
    NJet_Jets  = 'iterativeCone5CaloJets',
    NJet_JetIDs = 'ic5JetID',
    NJet_PartonMatch = '',
    NJet_GenJets = 'iterativeCone5GenJets',
    NJet_L1JetCorrector = 'ic5CaloL1Offset',
    NJet_L2JetCorrector = 'ic5CaloL2Relative',
    NJet_L3JetCorrector = 'ic5CaloL3Absolute',
    NJet_L2L3JetCorrector = 'ic5CaloL2L3',
    NJet_L2L3L4JWJetCorrector = 'ic5CaloL2L3'
)

process.calibTreeMakerKT4Calo = process.calibTreeMakerCalo.clone(
    OutputFile = 'kt4Calo.root',
    NJet_Jets  = 'kt4CaloJets',
    NJet_JetIDs = 'kt4JetID',
    NJet_PartonMatch = '',
    NJet_GenJets = 'kt4GenJets',
    NJet_L1JetCorrector = 'kt4CaloL1Offset',
    NJet_L2JetCorrector = 'kt4CaloL2Relative',
    NJet_L3JetCorrector = 'kt4CaloL3Absolute',
    NJet_L2L3JetCorrector = 'kt4CaloL2L3',
    NJet_L2L3L4JWJetCorrector = 'kt4CaloL2L3'
)

process.calibTreeMakerKT6Calo = process.calibTreeMakerCalo.clone(
    OutputFile = 'kt6Calo.root',
    NJet_Jets  = 'kt6CaloJets',
    NJet_JetIDs = 'kt6JetID',
    NJet_PartonMatch = '',
    NJet_GenJets = 'kt6GenJets',
    NJet_L2JetCorrector = 'kt6CaloL2Relative',
    NJet_L3JetCorrector = 'kt6CaloL3Absolute',
    NJet_L2L3JetCorrector = 'kt6CaloL2L3',
    NJet_L2L3L4JWJetCorrector = 'kt6CaloL2L3'
)

process.calibTreeMakerAK7PF = process.calibTreeMakerPF.clone(
    OutputFile = 'ak7PF.root',
    NJet_Jets  = 'ak7PFJets',
    NJet_PartonMatch = '',
    NJet_GenJets = 'ak7GenJets',
    NJet_L1JetCorrector = 'ak7PFL1Offset',
    NJet_L2JetCorrector = 'ak7PFL2Relative',
    NJet_L3JetCorrector = 'ak7PFL3Absolute',
    NJet_L2L3JetCorrector = 'ak7PFL2L3',
    NJet_L2L3L4JWJetCorrector = 'ak7PFL2L3'
)

process.calibTreeMakerIC5PF = process.calibTreeMakerPF.clone(
    OutputFile = 'ic5PF.root',
    NJet_Jets  = 'iterativeCone5PFJets',
    NJet_PartonMatch = '',
    NJet_GenJets = 'iterativeCone5GenJets',
    NJet_L2JetCorrector = 'ic5PFL2Relative',
    NJet_L3JetCorrector = 'ic5PFL3Absolute',
    NJet_L2L3JetCorrector = 'ic5PFL2L3',
    NJet_L2L3L4JWJetCorrector = 'ic5PFL2L3'
)


process.calibTreeMakerKT4PF = process.calibTreeMakerPF.clone(
    OutputFile = 'kt4PF.root',
    NJet_Jets  = 'kt4PFJets',
    NJet_PartonMatch = '',
    NJet_GenJets = 'kt4GenJets',
    NJet_L1JetCorrector = 'kt4PFL1Offset',
    NJet_L2JetCorrector = 'kt4PFL2Relative',
    NJet_L3JetCorrector = 'kt4PFL3Absolute',
    NJet_L2L3JetCorrector = 'kt4PFL2L3',
    NJet_L2L3L4JWJetCorrector = 'kt4PFL2L3'
)

process.calibTreeMakerKT6PF = process.calibTreeMakerPF.clone(
    OutputFile = 'kt6PF.root',
    NJet_Jets  = 'kt6PFJets',
    NJet_PartonMatch = '',
    NJet_GenJets = 'kt6GenJets',
    NJet_L1JetCorrector = 'kt6PFL1Offset',
    NJet_L2JetCorrector = 'kt6PFL2Relative',
    NJet_L3JetCorrector = 'kt6PFL3Absolute',
    NJet_L2L3JetCorrector = 'kt6PFL2L3',
    NJet_L2L3L4JWJetCorrector = 'kt6PFL2L3'
)


process.pDump = cms.Path( process.dump )

process.pData = cms.Path( #process.hltLevel1GTSeed*
                          process.hltHighLevel
                          #* process.primaryVertexFilter
                          #* process.noscraping
                          #* process.dump
                          #* process.ZSPJetCorrectionsAntiKt5
                          #* process.ZSPrecoJetAssociationsAntiKt5
                          * process.calibTreeMakerCalo
                          * process.calibTreeMakerPF
                          * process.calibTreeMakerTrack
                          * process.calibTreeMakerJPT
                          * process.calibTreeMakerAK7Calo
                          #* process.calibTreeMakerIC5Calo
                          * process.calibTreeMakerKT4Calo
                          * process.calibTreeMakerKT6Calo
                          * process.calibTreeMakerAK7PF
                          #* process.calibTreeMakerIC5PF
                          * process.calibTreeMakerKT4PF
                          * process.calibTreeMakerKT6PF
                          )

process.schedule = cms.Schedule(process.pData)
