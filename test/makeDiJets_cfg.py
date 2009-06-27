import FWCore.ParameterSet.Config as cms

process = cms.Process("Calib")

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
  '/store/mc/Summer08//QCDDiJetPt80to120/GEN-SIM-RECO/IDEAL_V9_v1/0000/009AC3E3-BF97-DD11-93B5-00093D13BB43.root',
            )
                            )

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10) )

from RecoJets.Configuration.RecoJetAssociations_cff import *
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FakeConditions_cff")
process.load("Geometry.CommonDetUnit.bareGlobalTrackingGeometry_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagator_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAny_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAlong_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorOpposite_cfi")
process.load("TrackingTools.TrackAssociator.DetIdAssociatorESProducer_cff")
process.load("TrackingTools.TrackAssociator.default_cfi")

process.load("Calibration.CalibTreeMaker.CalibTreeMaker_cff")

process.load("RecoJets.Configuration.RecoJetsAll_cff")

process.dump = cms.EDAnalyzer("EventContentAnalyzer")


process.myPartons = cms.EDFilter("PartonSelector",
   withLeptons = cms.bool(False)
)
process.CaloJetPartonMatching = cms.EDFilter("JetPartonMatcher",
   jets = cms.InputTag("sisCone5CaloJets"),
   coneSizeToAssociate = cms.double(0.2),
   partons = cms.InputTag("myPartons")
)


from JetMETCorrections.Configuration.JetPlusTrackCorrections_cff import *


#The following file are in ZSPJetCorrections219_cff, but with SisConeJets. ZSP correction factors are derived for Iterative though.
process.load("Calibration.CalibTreeMaker.ZSPJetCorrections219Sis_cff")

process.JetPlusTrackZSPCorrectorScone5 = cms.ESSource("JetPlusTrackCorrectionService",
    JetTrackCollectionAtCalo = cms.InputTag("ZSPsisCone5JetTracksAssociatorAtCaloFace"),
    respalgo = cms.int32(5),
    JetTrackCollectionAtVertex = cms.InputTag("ZSPsisCone5JetTracksAssociatorAtVertex"),
    muonSrc = cms.InputTag("globalMuons"),
    AddOutOfConeTracks = cms.bool(True),
    NonEfficiencyFile = cms.string('CMSSW_167_TrackNonEff'),
    NonEfficiencyFileResp = cms.string('CMSSW_167_TrackLeakage'),
    ResponseFile = cms.string('CMSSW_167_response'),
    label = cms.string('JetPlusTrackZSPCorrectorScone5'),
    TrackQuality = cms.string('highPurity'),
    UseQuality = cms.bool(True)
)

process.load("Calibration.CalibTreeMaker.ZSPsisCone5JTA_cff")


#############   Define the L2 correction service #####
process.L2JetCorrector = cms.ESSource("L2RelativeCorrectionService", 
                                      tagName = cms.string('Summer08Redigi_L2Relative_SC5Calo'),
                                      label = cms.string('L2RelativeJetCorrector')
                                      )
#############   Define the L3 correction service #####
process.L3JetCorrector = cms.ESSource("L3AbsoluteCorrectionService", 
                                      tagName = cms.string('Summer08Redigi_L3Absolute_SC5Calo'),
                                      label = cms.string('L3AbsoluteJetCorrector')
                                      )
process.L2JetCorrectorSC5PF= cms.ESSource("L2RelativeCorrectionService", 
    tagName = cms.string('Summer08Redigi_L2Relative_SC5PF'),
    label = cms.string('L2RelativeJetCorrectorSC5PF')
)
process.L2JetCorrectorIC5JPT= cms.ESSource("L2RelativeCorrectionService", 
    tagName = cms.string('Summer08Redigi_L2Relative_IC5JPT'),
    label = cms.string('L2RelativeJetCorrectorIC5JPT')
)
process.L3JetCorrectorIC5JPT = cms.ESSource("L3AbsoluteCorrectionService", 
    tagName = cms.string('Summer08Redigi_L3Absolute_IC5JPT'),
    label = cms.string('L3AbsoluteJetCorrectorIC5JPT')
)
process.L3JetCorrectorSC5PF = cms.ESSource("L3PFAbsoluteCorrectionService", 
    tagName = cms.string('Summer08Redigi_L3Absolute_SC5PF'),
    label = cms.string('L3AbsoluteJetCorrectorSC5PF')
)
process.L2JetCorrectorSC5Calo = cms.ESSource("L2RelativeCorrectionService", 
    tagName = cms.string('Summer08Redigi_L2Relative_SC5Calo'),
    label = cms.string('L2RelativeJetCorrectorSC5Calo')
)
process.L3JetCorrectorSC5Calo = cms.ESSource("L3AbsoluteCorrectionService", 
    tagName = cms.string('Summer08Redigi_L3Absolute_SC5Calo'),
    label = cms.string('L3AbsoluteJetCorrectorSC5Calo')
)




#############   Define the L2+L3 correction service #####
process.L2L3JetCorrectorSC5Calo = cms.ESSource("JetCorrectionServiceChain",  
    correctors = cms.vstring('L2RelativeJetCorrectorSC5Calo','L3AbsoluteJetCorrectorSC5Calo'),
    label = cms.string('L2L3JetCorrectorSC5Calo') 
)

#############   Define the L2+L3 JPT correction service #####
process.L2L3JetCorrectorIC5JPT = cms.ESSource("JetCorrectionServiceChain",  
    correctors = cms.vstring('L2RelativeJetCorrectorIC5JPT','L3AbsoluteJetCorrectorIC5JPT'),
    label = cms.string('L2L3JetCorrectorIC5JPT') 
)


#############   Define the L2+L3 PFlow correction service ####
process.L2L3JetCorrectorSC5PF = cms.ESSource("JetCorrectionServiceChain",  
    correctors = cms.vstring('L2RelativeJetCorrectorSC5PF','L3AbsoluteJetCorrectorSC5PF'),
    label = cms.string('L2L3JetCorrectorSC5PF') 
)

# set the record's IOV. Must be defined once. Choose ANY correction service. #
process.prefer("L2L3JetCorrectorSC5Calo")



###  Parameters for module calibTreeMaker
process.calibTreeMaker.WriteDiJetTree     = True
process.calibTreeMaker.WriteEcalCells     = True

process.calibTreeMaker.OutputFile         = 'DiJet_test.root'

process.calibTreeMaker.DiJetTreeName      = 'DiJetTree'
process.calibTreeMaker.GenEventScaleLabel = 'genEventScale'

process.calibTreeMaker.NJet_Jets         = 'sisCone5CaloJets'
process.calibTreeMaker.NJet_GenJets      = 'sisCone5GenJets'
process.calibTreeMaker.NJet_GenParticles = 'genParticleCandidates'
process.calibTreeMaker.NJetZSPJets       = 'ZSPJetCorJetScone5'
process.calibTreeMaker.NJet_MET          = 'met'
process.calibTreeMaker.NJetRecTracks     = 'generalTracks'
process.calibTreeMaker.NJetRecMuons      = 'muons' #'globalMuons' check for global muon & TMLastStationLoose in code
process.calibTreeMaker.NJetConeSize      = 0.5
process.calibTreeMaker.NJet_Weight_Tag   = 'genEventWeight'
process.calibTreeMaker.NJet_Weight       = 1.


process.p2 = cms.Path( process.ZSPJetCorrections
                       * process.ZSPsisCone5JTA
                       * process.myPartons
                       * process.CaloJetPartonMatching
                       * process.calibTreeMaker)

process.schedule = cms.Schedule(process.p2)