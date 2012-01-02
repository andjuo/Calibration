import FWCore.ParameterSet.Config as cms

from TrackingTools.TrackAssociator.default_cfi import *

calibTreeMakerCalo = cms.EDAnalyzer("CalibTreeMakerCalo",
    TrackAssociatorParameters,
    TrackAssociatorParameterBlock,
                              
    OutputFile    = cms.string('ak5Calo.root'),
    TreeName      = cms.string('DiJetTree'),
    GenEventScaleLabel   = cms.InputTag("genEventScale"),
               
    PhotonJetPhotons     = cms.InputTag("photons"),
    PhotonJetGenPhotons  = cms.InputTag("goodGenPhotons"),

    DimuonJetMuons       = cms.InputTag("muons"),
    DimuonJetGenMuons    = cms.InputTag("goodGenMuons"),
       
    BeamSpot = cms.InputTag("offlineBeamSpot"),
                              
    NJet_Jets         = cms.InputTag("ak5CaloJets"),
    NJet_MinNumJets   = cms.int32(1),                             
    NJet_JetIDs       = cms.InputTag("ak5JetID"),
    NJet_PartonMatch  = cms.InputTag("CaloJetPartonMatching"),
    NJet_MET          = cms.InputTag("corMetGlobalMuons"),
    NJet_Rho          = cms.InputTag('kt6CaloJets','rho'),
    NJetRecTracks     = cms.InputTag("generalTracks"),
    NJetRecMuons      = cms.InputTag("muons"),
    NJet_Weight       = cms.double(1),
    NJet_Weight_Tag   = cms.InputTag("genEventScale"),
    NJet_GenJets      = cms.InputTag("ak5GenJets"),
    NJet_GenParticles = cms.InputTag("genParticles"),
    NJetConeSize      = cms.double(0.5),
    NJetZSPJets       = cms.InputTag("ZSPJetCorJetAntiKt5"),
    NJetSecondVx      = cms.InputTag("ak5CaloSimpleSecondaryVertexBJetTags"),
    NJet_L1JetCorrector       = cms.string('ak5CaloL1Offset'),
    NJet_L2JetCorrector       = cms.string('ak5CaloL2Relative'),
    NJet_L3JetCorrector       = cms.string('ak5CaloL3Absolute'),
    NJet_JPTZSPCorrector      = cms.string('JetPlusTrackZSPCorrectorAntiKt5'),
    NJet_L1L2L3JetCorrector     = cms.string('ak5CaloL1L2L3'),
    NJet_L1L2L3L4JWJetCorrector = cms.string('ak5CaloL1L2L3'),
    NJet_L2L3JetCorrectorJPT  = cms.string('ak5JPTL2L3'),
    NJet_writeTracks  = cms.bool(False),
    NJet_writeTowers  = cms.bool(False),

    WriteGenJetParticles = cms.bool(False), 
    WriteStableGenParticles = cms.bool(False),                             
                                  
    WritePhotons  = cms.bool(False),
    WriteMuons    = cms.bool(False)                                
)

calibTreeMaker = calibTreeMakerCalo.clone(
    OutputFile = 'calib.root'
)

calibTreeMakerPF = cms.EDAnalyzer("CalibTreeMakerPF",
    TrackAssociatorParameters,
    TrackAssociatorParameterBlock,
                              
    OutputFile         = cms.string('ak5PF.root'),
    TreeName      = cms.string('DiJetTree'),

    GenEventScaleLabel   = cms.InputTag("genEventScale"),                             
               
    PhotonJetPhotons     = cms.InputTag("photons"),
    PhotonJetGenPhotons  = cms.InputTag("goodGenPhotons"),
 
    DimuonJetMuons       = cms.InputTag("muons"),
    DimuonJetGenMuons    = cms.InputTag("goodGenMuons"),
       
    BeamSpot = cms.InputTag("offlineBeamSpot"),
                              
    NJet_Jets         = cms.InputTag("ak5PFJets"),
    NJet_MinNumJets   = cms.int32(1),                             
    NJet_JetIDs       = cms.InputTag(""), 
    NJet_PartonMatch  = cms.InputTag("PFJetPartonMatching"),
    NJet_MET          = cms.InputTag("pfMet"),
    NJet_Rho          = cms.InputTag('kt6PFJets','rho'),
    NJetRecTracks     = cms.InputTag("generalTracks"),
    NJetRecMuons      = cms.InputTag("muons"),
    NJet_Weight       = cms.double(1),
    NJet_Weight_Tag   = cms.InputTag("genEventWeight"),
    NJet_GenJets      = cms.InputTag("ak5GenJets"),
    NJet_GenParticles = cms.InputTag("genParticles"),
    NJetConeSize      = cms.double(0.5),
    NJetZSPJets       = cms.InputTag("ZSPJetCorJetAntiKt5"),
    NJetSecondVx      = cms.InputTag("ak5PFSimpleSecondaryVertexBJetTags"),
    NJet_L1JetCorrector       = cms.string('ak5PFL1Offset'),
    NJet_L2JetCorrector       = cms.string('ak5PFL2Relative'),
    NJet_L3JetCorrector       = cms.string('ak5PFL3Absolute'),
    NJet_JPTZSPCorrector      = cms.string('JetPlusTrackZSPCorrectorAntiKt5'),
    NJet_L1L2L3JetCorrector     = cms.string('ak5PFL1L2L3'),
    NJet_L1L2L3L4JWJetCorrector = cms.string('ak5PFL1L2L3'),
    NJet_L2L3JetCorrectorJPT  = cms.string('ak5JPTL2L3'),
    NJet_writeTracks  = cms.bool(False),
    NJet_writeTowers  = cms.bool(False),

    WriteGenJetParticles = cms.bool(False), 
    WriteStableGenParticles = cms.bool(False),                             
                                  
    WritePhotons  = cms.bool(False),
    WriteMuons    = cms.bool(False)  
)

calibTreeMakerTrack = cms.EDAnalyzer("CalibTreeMakerTrack",
    TrackAssociatorParameters,
    TrackAssociatorParameterBlock,
                              
    OutputFile         = cms.string('ak5Track.root'),
    TreeName      = cms.string('DiJetTree'),

    GenEventScaleLabel   = cms.InputTag("genEventScale"),                             
               
    PhotonJetPhotons     = cms.InputTag("photons"),
    PhotonJetGenPhotons  = cms.InputTag("goodGenPhotons"),    

    DimuonJetMuons       = cms.InputTag("muons"),
    DimuonJetGenMuons    = cms.InputTag("goodGenMuons"),
       
    BeamSpot = cms.InputTag("offlineBeamSpot"),
                              
    NJet_Jets         = cms.InputTag("ak5TrackJets"),
    NJet_MinNumJets   = cms.int32(1),                             
    NJet_JetIDs       = cms.InputTag(""),
    NJet_PartonMatch  = cms.InputTag("TrackJetPartonMatching"),
    NJet_MET          = cms.InputTag("pfMet"),
    NJet_Rho          = cms.InputTag('kt6PFJets','rho'),
    NJetRecTracks     = cms.InputTag("generalTracks"),
    NJetRecMuons      = cms.InputTag("muons"),
    NJet_Weight       = cms.double(1),
    NJet_Weight_Tag   = cms.InputTag("genEventWeight"),
    NJet_GenJets      = cms.InputTag("ak5GenJets"),
    NJet_GenParticles = cms.InputTag("genParticles"),
    NJetConeSize      = cms.double(0.5),
    NJetZSPJets       = cms.InputTag("ZSPJetCorJetAntiKt5"),    
    NJetSecondVx      = cms.InputTag("ak5TrackSimpleSecondaryVertexBJetTags"),
    NJet_L1JetCorrector       = cms.string('ak5TrackL1Offset'),
    NJet_L2JetCorrector       = cms.string('ak5TrackL2Relative'),
    NJet_L3JetCorrector       = cms.string('ak5TrackL3Absolute'),
    NJet_JPTZSPCorrector      = cms.string('JetPlusTrackZSPCorrectorAntiKt5'),
    NJet_L1L2L3JetCorrector     = cms.string('ak5TrackL1L2L3'),
    NJet_L1L2L3L4JWJetCorrector = cms.string('ak5TrackL1L2L3'),
    NJet_L2L3JetCorrectorJPT  = cms.string('ak5JPTL2L3'),
    NJet_writeTracks  = cms.bool(False),
    NJet_writeTowers  = cms.bool(False),
 
    WriteGenJetParticles = cms.bool(False), 
    WriteStableGenParticles = cms.bool(False),                             
                                   
    WritePhotons  = cms.bool(False),
    WriteMuons    = cms.bool(False)  
)
 
calibTreeMakerJPT = cms.EDAnalyzer("CalibTreeMakerJPT",
    TrackAssociatorParameters,
    TrackAssociatorParameterBlock,
                              
    OutputFile         = cms.string('ak5JPT.root'),
    TreeName      = cms.string('DiJetTree'),

    GenEventScaleLabel   = cms.InputTag("genEventScale"),
    
    PhotonJetPhotons     = cms.InputTag("photons"),
    PhotonJetGenPhotons  = cms.InputTag("goodGenPhotons"),    
 
    DimuonJetMuons       = cms.InputTag("muons"),
    DimuonJetGenMuons    = cms.InputTag("goodGenMuons"),
       
    BeamSpot = cms.InputTag("offlineBeamSpot"),
                               
    NJet_Jets         = cms.InputTag("JetPlusTrackZSPCorJetAntiKt5"),
    NJet_MinNumJets   = cms.int32(1),                             
    NJet_JetIDs       = cms.InputTag("ak5JetID"),
    NJet_PartonMatch  = cms.InputTag("JPTJetPartonMatching"),
    NJet_MET          = cms.InputTag("tcMet"),
    NJetRecTracks     = cms.InputTag("generalTracks"), 
    NJetRecMuons      = cms.InputTag("muons"),
    NJet_Rho          = cms.InputTag('kt6PFJets','rho'),
    NJet_Weight       = cms.double(1),
    NJet_Weight_Tag   = cms.InputTag("genEventWeight"),
    NJet_GenJets      = cms.InputTag("ak5GenJets"),
    NJet_GenParticles = cms.InputTag("genParticles"),
    NJetConeSize      = cms.double(0.5),
    NJetZSPJets       = cms.InputTag("ZSPJetCorJetAntiKt5"),
    NJetSecondVx      = cms.InputTag("ak5JPTSimpleSecondaryVertexBJetTags"),
    NJet_L1JetCorrector       = cms.string('ak5JPTL1Offset'),
    NJet_L2JetCorrector       = cms.string('ak5JPTL2Relative'),
    NJet_L3JetCorrector       = cms.string('ak5JPTL3Absolute'),
    NJet_JPTZSPCorrector      = cms.string('JetPlusTrackZSPCorrectorAntiKt5'),
    NJet_L1L2L3JetCorrector     = cms.string('ak5JPTL1L2L3'),
    NJet_L1L2L3L4JWJetCorrector = cms.string('ak5JPTL1L2L3'),
    NJet_L2L3JetCorrectorJPT  = cms.string('ak5JPTL2L3'),
    NJet_writeTracks  = cms.bool(False),
    NJet_writeTowers  = cms.bool(False),

    WriteGenJetParticles = cms.bool(False), 
    WriteStableGenParticles = cms.bool(False),                             
                                  
    WritePhotons  = cms.bool(False),
    WriteMuons  = cms.bool(False)
)

calibTreeMakerPFCluster = cms.EDAnalyzer("CalibTreeMakerPFCluster",
    TrackAssociatorParameters,
    TrackAssociatorParameterBlock,
                              
    OutputFile =  cms.string('ak5PFCluster.root'),
    TreeName      = cms.string('DiJetTree'),

    GenEventScaleLabel   = cms.InputTag("genEventScale"),                             
               
    PhotonJetPhotons     = cms.InputTag("photons"),
    PhotonJetGenPhotons  = cms.InputTag("goodGenPhotons"),

    DimuonJetMuons       = cms.InputTag("muons"),
    DimuonJetGenMuons    = cms.InputTag("goodGenMuons"),
       
    BeamSpot = cms.InputTag("offlineBeamSpot"),
                              
    NJet_Jets         = cms.InputTag("ak5PFClusterJets"),
    NJet_MinNumJets   = cms.int32(0),                             
    NJet_JetIDs       = cms.InputTag(""), 
    NJet_PartonMatch  = cms.InputTag("PFClusterJetPartonMatching"),
    NJet_MET          = cms.InputTag("pfClusterMet"),
    NJet_Rho          = cms.InputTag('kt6CaloJets','rho'),
    NJetRecTracks     = cms.InputTag("generalTracks"),
    NJetRecMuons      = cms.InputTag("muons"),
    NJet_Weight       = cms.double(1),
    NJet_Weight_Tag   = cms.InputTag("genEventWeight"),
    NJet_GenJets      = cms.InputTag("ak5GenJets"),
    NJet_GenParticles = cms.InputTag("genParticles"),
    NJetConeSize      = cms.double(0.5),
    NJetZSPJets       = cms.InputTag("ZSPJetCorJetAntiKt5"),
    NJetSecondVx      = cms.InputTag("ak5PFClusterSimpleSecondaryVertexBJetTags"),
    NJet_L1JetCorrector       = cms.string('ak5CaloL1Offset'),
    NJet_L2JetCorrector       = cms.string('ak5CaloL2Relative'),
    NJet_L3JetCorrector       = cms.string('ak5CaloL3Absolute'),
    NJet_JPTZSPCorrector      = cms.string('JetPlusTrackZSPCorrectorAntiKt5'),
    NJet_L1L2L3JetCorrector     = cms.string('ak5CaloL1L2L3'),
    NJet_L1L2L3L4JWJetCorrector = cms.string('ak5CaloL1L2L3'),
    NJet_L2L3JetCorrectorJPT  = cms.string('ak5JPTL2L3'),
    NJet_writeTracks  = cms.bool(False),
    NJet_writeTowers  = cms.bool(False),

    WriteGenJetParticles = cms.bool(False), 
    WriteStableGenParticles = cms.bool(False),                             
                                  
    WritePhotons  = cms.bool(False),
    WriteMuons    = cms.bool(False)  
)
