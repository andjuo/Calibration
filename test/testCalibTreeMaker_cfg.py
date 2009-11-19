import FWCore.ParameterSet.Config as cms

process = cms.Process("Calib")

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
 # '/store/relval/CMSSW_2_1_9/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0001/6E9B44E2-0487-DD11-BFA7-001617C3B78C.root'
        '/store/mc/Summer08/QCDDiJetPt170to230/GEN-SIM-RECO/IDEAL_V9_v1/0000/0A4E75EB-C597-DD11-AADA-0019B9E4B047.root'
            )
                            )

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100) )
process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(True)
)

from RecoJets.Configuration.RecoJetAssociations_cff import *
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
process.GlobalTag.globaltag = 'MC_31X_V9::All'

process.load("Calibration.CalibTreeMaker.CalibTreeMaker_cff")

process.load("RecoJets.Configuration.RecoJets_cff")

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

process.load("JetMETCorrections.Configuration.ZSPJetCorrections219_cff")
process.load("JetMETCorrections.Configuration.JetPlusTrackCorrections_cff")




#process.load("JetMETCorrections.Configuration.L2L3Corrections_Summer08Redigi_cff")
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
#process.L2L3JetCorrector = cms.ESSource("L2L3CorJetSC5Calo", 
#                                      tagName = cms.string('Summer08Redigi_L2Relative_SC5Calo'),
#                                      label = cms.string('L2RelativeJetCorrector')
#      
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

process.photonCalIsolation.src = 'photons'
process.photonCalIsolation.dRMin = 0.20
process.photonCalIsolation.dRMax = 0.50
process.photonJetSample.Photons = 'photons'
process.photonJetSample.GenPhotons = 'genParticles'
process.photonJetSample.Jets = 'sisCone5CaloJets'
#process.photonJetSample.Jets = 'midPointCone5CaloJets'
process.photonJetSample.GenJets = 'sisCone5GenJets'
process.photonJetFilter.MinPhotonPt = 0.
process.photonJetFilter.MaxPhotonEta = 2.5
process.photonJetFilter.MinJetPt = 0.
process.photonJetFilter.MaxJetEta = 5.
process.photonJetFilter.MaxIsolation = 2.
process.photonJetFilter.MaxNonLeadingJetsPt = 5.
process.photonJetFilter.MaxSecondJetPt = 5.
process.photonJetFilter.MaxDeltaPhi = 0.10
process.photonJetFilter.Debug = False

process.zJetSample.Muons = 'muons' #'globalMuons' check for global muon & TMLastStationLoose in code
process.zJetSample.GenZs = 'genParticles'
process.zJetSample.Jets = 'sisCone5CaloJets'
#process.zJetSample.Jets = 'midPointCone5CaloJets'
process.zJetSample.GenJets = 'sisCone5GenJets'
process.zJetSample.MinMuonPt = 15.
process.zJetSample.MaxMuonEta = 2.3
process.zJetSample.Z_Mass = 91.2
process.zJetSample.Z_Mass_Tolerance = 15.
#process.zJetFilter.MinZPt = 0.
#process.zJetFilter.MaxZEta = 2.5
process.zJetFilter.MinJetPt = 0.
process.zJetFilter.MaxJetEta = 5.
process.zJetFilter.MaxNonLeadingJetsPt = 5.
process.zJetFilter.MaxSecondJetPt = 5.
process.zJetFilter.MaxDeltaPhi = 0.10
process.zJetFilter.Debug = False

process.trackTrkIsolation.dRMax = 0.5
process.trackTowerSample.MaxIsolation = 20.
process.trackTowerSample.MinPt = 10.
process.trackTowerSample.MaxEta = 3.
process.trackTowerSample.MaxTrkLength = 0.
process.trackTowerSample.MaxChiSquare = 100.
process.trackTowerSample.MinNumOfHits = 5
process.trackTowerSample.MaxDeltaPhi = 0.1
process.trackTowerSample.MaxDeltaEta = 0.1
process.trackTowerSample.GroupNTowers = 1


process.diJetFilter.Jets               = 'sisCone5CaloJets'
process.diJetFilter.MaxRefEta          = 5.0 # 1.5
process.diJetFilter.MaxEta             = 5.0
process.diJetFilter.MinJetPt           = 0. # 10.
#process.diJetFilter.sumPtMaxFracThird  = 0.1 (in CalibCore config?)
process.diJetFilter.MinJetPhiSum       = 0.1
#process.diJetFilter.deltaPhiMETMax     = 0.15 (?)
process.diJetFilter.MinJetEMF          = 0.05
process.diJetFilter.MaxJetEMF          = 0.95
process.diJetFilter.MaxLastJetPt       =  5. # 0.

process.triJetFilter.Jets               = 'sisCone5CaloJets'
process.triJetFilter.MaxRefEta          = 1.5
process.triJetFilter.MaxEta             = 5.0
process.triJetFilter.MinJetPt           = 10.
#process.triJetFilter.sumPtMaxFracThird  = 0.1 (in CalibCore config?)
process.triJetFilter.MinJetPhiSum       = 0.1
#process.triJetFilter.deltaPhiMETMax     = 0.15 (?)
process.triJetFilter.MinJetEMF          = 0.05
process.triJetFilter.MaxJetEMF          = 0.95
process.triJetFilter.MaxLastJetPt       = 5.

process.calibTreeMaker.OutputFile = 'Gamma_Track_470_rereco.root'
#process.calibTreeMaker.OutputFile = 'DiJet_Track_600_800_rereco_incomplete.root'
#process.calibTreeMaker.OutputFile = 'ZJet_Track_0_15_rereco.root'
#50_80_rereco.root'


process.calibTreeMaker.PhotonJetTreeName = 'GammaJetTree'
process.calibTreeMaker.PhotonJetJets = 'photonJetSample:LeadingJet'
process.calibTreeMaker.PhotonJetCaloJets =  'sisCone5CaloJets'
process.calibTreeMaker.PhotonJetGenJets = 'photonJetSample:LeadingGenJet'
process.calibTreeMaker.PhotonJetPhotons = 'photonJetSample:LeadingPhoton'
process.calibTreeMaker.PhotonJetGenPhotons = 'photonJetSample:LeadingGenPhoton'
process.calibTreeMaker.PhotonJetZSPJets = 'ZSPJetCorJetScone5'
process.calibTreeMaker.PhotonJetPFJets = 'sisCone5PFJets'
process.calibTreeMaker.PhotonJetNonLeadingJetsPt = 'photonJetSample:NonLeadingJetsPt'
process.calibTreeMaker.PhotonJetMet          = 'met'
process.calibTreeMaker.PhotonJetRecTracks    = 'generalTracks'
process.calibTreeMaker.PhotonJetRecMuons     = 'muons' #'globalMuons' check for global muon & TMLastStationLoose in code
process.calibTreeMaker.PhotonJetConeSize     = 0.5
process.calibTreeMaker.PhotonJet_Weight      = -1.
process.calibTreeMaker.PhotonJet_Weight_Tag  = 'Summer08WeightProducer:weight' #'genEventWeight'



process.calibTreeMaker.ZJetTreeName = 'ZJetTree'
process.calibTreeMaker.ZJetJets = 'zJetSample:LeadingJet'
process.calibTreeMaker.ZJetCaloJets =  'sisCone5CaloJets'
process.calibTreeMaker.ZJetGenJets = 'zJetSample:LeadingGenJet'
process.calibTreeMaker.ZJetZs = 'zJetSample:LeadingZ'
process.calibTreeMaker.ZJetGenZs = 'zJetSample:LeadingGenZ'
process.calibTreeMaker.ZJetZSPJets = 'ZSPJetCorJetScone5'
process.calibTreeMaker.ZJetPFJets = 'sisCone5PFJets'
process.calibTreeMaker.ZJetNonLeadingJetsPt = 'zJetSample:NonLeadingJetsPt'
process.calibTreeMaker.ZJetMet          = 'met'
process.calibTreeMaker.ZJetRecTracks    = 'generalTracks'
process.calibTreeMaker.ZJetRecMuons     = 'muons' #'globalMuons' check for global muon & TMLastStationLoose in code
process.calibTreeMaker.ZJetConeSize     = 0.5
process.calibTreeMaker.ZJet_Weight      = 2.8288 #0.000178 #0.000416 #0.00144 #0.004967 #0.00936 #0.0513 #0.0901 #0.1328  #0.09384 #2.8288 
process.calibTreeMaker.ZJet_Weight_Tag  = 'genEventWeight'



process.calibTreeMaker.DiJetTreeName     ='DiJetTree'
process.calibTreeMaker.TriJetTreeName    ='TriJetTree'
process.calibTreeMaker.NJet_Jets         = 'sisCone5CaloJets'
#prosess.calibTreeMaker.JetJetGenJets      = iterativeCone5GenJetsPt10
process.calibTreeMaker.NJet_GenJets      = 'sisCone5GenJets'

process.calibTreeMaker.NJet_GenParticles = 'genParticleCandidates'
process.calibTreeMaker.NJetZSPJets       = 'ZSPJetCorJetScone5'
process.calibTreeMaker.NJet_L2JetCorrector      = cms.string('L2RelativeJetCorrector')
process.calibTreeMaker.NJet_L3JetCorrector      = cms.string('L3AbsoluteJetCorrector')
process.calibTreeMaker.NJet_JPTZSPCorrector     = cms.string('JetPlusTrackZSPCorrectorScone5')
process.calibTreeMaker.NJet_L2L3JetCorrector    = cms.string('L2L3JetCorrectorSC5Calo')
process.calibTreeMaker.NJet_L2L3JetCorrectorJPT = cms.string('L2L3JetCorrectorIC5JPT')
process.calibTreeMaker.NJet_MET          = 'met'
process.calibTreeMaker.NJetRecTracks     = 'generalTracks'
process.calibTreeMaker.NJetRecMuons      = 'muons' #'globalMuons' check for global muon & TMLastStationLoose in code
process.calibTreeMaker.NJetConeSize      = 0.5
process.calibTreeMaker.NJet_Weight_Tag   = 'genEventWeight'
process.calibTreeMaker.NJet_Weight       =   0.30943 #0.0000000395 #0.000005807 #0.00673362 # 0.30943# 84858.871  #-1.                        #incomplete 20-30: 887521 ;     50-80: 12460.7;     80-120: 5445.253 ;      120-170: 938.712 ;       170-230: 99.434;     230-300: 33.92 ;    300-380: ; 13.862    380-470: 1.5477    470-600: 1.3282;

process.calibTreeMaker.TopTreeName     ='TopTree'


process.calibTreeMaker.WritePhotonJetTree = True #False
process.calibTreeMaker.WriteDiJetTree    = False #True
process.calibTreeMaker.WriteTriJetTree   = False
process.calibTreeMaker.WriteZJetTree   = False # True

process.ZSPJetCorrections = cms.Sequence(process.ZSPJetCorrectionsSisCone5
                       * process.ZSPrecoJetAssociationsSisCone5)

#process.p1 = cms.Path(process.dump)
#process.p2 = cms.Path(process.myPartons*process.CaloJetPartonMatching*process.makeDiJetTree)
#process.p2 = cms.Path(process.myPartons*process.CaloJetPartonMatching*process.calibTreeMaker)
process.p2 = cms.Path(process.ZSPJetCorrections * process.makePhotonJetTree)
#process.p2 = cms.Path(process.ZSPJetCorrections* process.makeDiJetTree)
#process.p2 = cms.Path(process.ZSPJetCorrections* process.makeTriJetTree)
#process.p2 = cms.Path(process.ZSPJetCorrections* process.makeZJetTree)

process.schedule = cms.Schedule(process.p2)
