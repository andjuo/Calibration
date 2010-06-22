import FWCore.ParameterSet.Config as cms

process = cms.Process("Calib")


process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold             = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000


process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    #'/store/data/Run2010A/JetMETTau/RECO/v1/000/136/082/147EC62F-DF66-DF11-9678-003048D2BE08.root'
    '/store/data/Commissioning10/MinimumBias/RECO/May6thPDSkim2_SD_JetMETTau-v1/0137/FE3CCCB6-D05D-DF11-BB30-00261894383F.root'

            )
                            )

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(5000) )

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
process.hltHighLevel.HLTPaths = ('HLT_Jet15U','HLT_Jet30U','HLT_Jet50U','HLT_DiJetAve15U_8E29','HLT_DiJetAve30U_8E29')
process.hltHighLevel.andOr = cms.bool(True)
process.hltHighLevel.throw = cms.bool(True)

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
#process.GlobalTag.globaltag = 'GR_R_36X_V11A::All'
process.GlobalTag.globaltag = 'GR_R_35X_V8B::All'


process.load("Calibration.CalibTreeMaker.CalibTreeMaker_cfi")

process.load("RecoJets.Configuration.RecoJets_cff")

process.dump = cms.EDAnalyzer("EventContentAnalyzer")


process.load("RecoJets.Configuration.GenJetParticles_cff")
process.load("RecoJets.Configuration.RecoGenJets_cff")


# Jet Energy Corrections
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')

# ZSP and JPT corrections
process.load("RecoJets.Configuration.RecoJPTJets_cff")

##################################################################
#  Parameters for module calibTreeMaker
##################################################################
process.calibTreeMakerCalo.WriteDiJetTree          = True
process.calibTreeMakerCalo.WriteStableGenParticles = False
process.calibTreeMakerCalo.WriteStableGenParticles = False
process.calibTreeMakerCalo.OutputFile         = 'Dijet-ak5Calo.root'
process.calibTreeMakerCalo.NJet_Jets         = 'ak5CaloJets'
process.calibTreeMakerCalo.NJet_JetIDs       = 'ak5JetID'
process.calibTreeMakerCalo.NJet_GenJets      = 'ak5GenJets'
process.calibTreeMakerCalo.NJetZSPJets       = 'ZSPJetCorJetAntiKt5'
process.calibTreeMakerCalo.NJet_L2JetCorrector      = cms.string('ak5CaloL2Relative')
process.calibTreeMakerCalo.NJet_L3JetCorrector      = cms.string('ak5CaloL3Absolute')
process.calibTreeMakerCalo.NJet_JPTZSPCorrector     = cms.string('JetPlusTrackZSPCorrectorAntiKt5')
process.calibTreeMakerCalo.NJet_L2L3JetCorrector    = cms.string('ak5CaloL2L3')
process.calibTreeMakerCalo.NJet_L2L3JetCorrectorJPT = cms.string('ak5JPTL2L3')
process.calibTreeMakerCalo.NJetConeSize      = 0.5

process.calibTreeMakerPF.WriteDiJetTree          = True
process.calibTreeMakerPF.WriteStableGenParticles = False
process.calibTreeMakerPF.OutputFile         = 'Dijet-ak5PF.root'
process.calibTreeMakerPF.NJet_Jets         = 'ak5PFJets'
process.calibTreeMakerPF.NJet_JetIDs       = ''
process.calibTreeMakerPF.NJet_GenJets      = 'ak5GenJets'
process.calibTreeMakerPF.NJetZSPJets       = 'ZSPJetCorJetAntiKt5'
process.calibTreeMakerPF.NJet_L2JetCorrector      = cms.string('ak5PFL2Relative')
process.calibTreeMakerPF.NJet_L3JetCorrector      = cms.string('ak5PFL3Absolute')
process.calibTreeMakerPF.NJet_JPTZSPCorrector     = cms.string('JetPlusTrackZSPCorrectorAntiKt5')
process.calibTreeMakerPF.NJet_L2L3JetCorrector    = cms.string('ak5PFL2L3')
process.calibTreeMakerPF.NJet_L2L3JetCorrectorJPT = cms.string('ak5JPT')
process.calibTreeMakerPF.NJetConeSize      = 0.5


process.calibTreeMakerTrack.WriteDiJetTree          = True
process.calibTreeMakerTrack.WriteStableGenParticles = False
process.calibTreeMakerTrack.OutputFile        = 'Dijet-ak5Track.root'
process.calibTreeMakerTrack.NJet_Jets         = 'ak5TrackJets'
process.calibTreeMakerTrack.NJet_JetIDs       = ''
process.calibTreeMakerTrack.NJet_GenJets      = 'ak5GenJets'
process.calibTreeMakerTrack.NJetZSPJets       = 'ZSPJetCorJetAntiKt5'

#ATTENTION: use CALO correction for the time being....
process.calibTreeMakerTrack.NJet_L2JetCorrector      = cms.string('ak5TrackL2Relative')
process.calibTreeMakerTrack.NJet_L3JetCorrector      = cms.string('ak5TrackL3Absolute')
process.calibTreeMakerTrack.NJet_JPTZSPCorrector     = cms.string('JetPlusTrackZSPCorrectorAntiKt5')
process.calibTreeMakerTrack.NJet_L2L3JetCorrector    = cms.string('ak5TrackL2L3')
process.calibTreeMakerTrack.NJet_L2L3JetCorrectorJPT = cms.string('ak5JPTL2L3')
process.calibTreeMakerTrack.NJetConeSize      = 0.5

#ATTENTION: use CALOcorrections for the time being
process.calibTreeMakerJPT.WriteDiJetTree          = True
process.calibTreeMakerJPT.WriteStableGenParticles = False
process.calibTreeMakerJPT.OutputFile        = 'Dijet-ak5JPT.root'
process.calibTreeMakerJPT.NJet_Jets         = 'JetPlusTrackZSPCorJetAntiKt5'
process.calibTreeMakerJPT.NJet_JetIDs       = ''
process.calibTreeMakerTrack.NJet_GenJets    = 'ak5GenJets'
process.calibTreeMakerTrack.NJetZSPJets     = 'ZSPJetCorJetAntiKt5'
process.calibTreeMakerJPT.NJet_L2JetCorrector      = cms.string('ak5JPTL2Relative')
process.calibTreeMakerJPT.NJet_L3JetCorrector      = cms.string('ak5JPTL3Absolute')
process.calibTreeMakerJPT.NJet_JPTZSPCorrector     = cms.string('JetPlusTrackZSPCorrectorAntiKt5')
process.calibTreeMakerJPT.NJet_L2L3JetCorrector    = cms.string('ak5JPTL2L3')
process.calibTreeMakerJPT.NJet_L2L3JetCorrectorJPT = cms.string('ak5JPTL2L3')
process.calibTreeMakerJPT.NJetConeSize      = 0.5


process.pDump = cms.Path( process.dump )

process.pData = cms.Path( process.hltLevel1GTSeed
                          * process.hltHighLevel
                          * process.primaryVertexFilter
                          * process.noscraping
                          #* process.ZSPJetCorrectionsAntiKt5
                          #* process.ZSPrecoJetAssociationsAntiKt5
                          * process.calibTreeMakerCalo
                          * process.calibTreeMakerPF
                          #* process.calibTreeMakerTrack
                          #* process.calibTreeMakerJPT
                          )

process.schedule = cms.Schedule(process.pData)
