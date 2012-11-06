## $Id: CalibTreeMaker_cfi.py,v 1.45 2012/11/05 12:56:20 kirschen Exp $

import FWCore.ParameterSet.Config as cms

from TrackingTools.TrackAssociator.default_cfi import *

ShortNameNextJetTypes          = 'ak5Calo'
calibTreeMakerCalo = cms.EDAnalyzer("CalibTreeMakerCalo",
    TrackAssociatorParameters,
    TrackAssociatorParameterBlock,
                              
    OutputFile    = cms.string(ShortNameNextJetTypes+'.root'),
    TreeName      = cms.string('DiJetTree'),
    GenEventScaleLabel   = cms.InputTag("genEventScale"),
               
    PhotonJetPhotons     = cms.InputTag("photons"),
    PhotonJetGenPhotons  = cms.InputTag("goodGenPhotons"),

    DimuonJetMuons       = cms.InputTag("muons"),
    DimuonJetGenMuons    = cms.InputTag("goodGenMuons"),

    TauAnaProducer       = cms.InputTag("hpsPFTauProducer"),
    TauAnaDiscriminator    = cms.InputTag("hpsPFTauDiscriminationByDecayModeFinding"),
       
    BeamSpot = cms.InputTag("offlineBeamSpot"),
                              
    NJet_Jets         = cms.InputTag(ShortNameNextJetTypes+"Jets"),
    NJet_MinNumJets   = cms.int32(1),                             
    NJet_MaxNumJets   = cms.int32(50),
    NJet_JetIDs       = cms.InputTag("ak5JetID"),
    NJet_PartonMatch  = cms.InputTag("CaloJetPartonMatching"),
    NJet_MET          = cms.InputTag("corMetGlobalMuons"),
    NJet_MET_T1       = cms.InputTag("caloType1CorrectedMet"),
    NJet_MET_T2       = cms.InputTag("caloType1p2CorrectedMet"),   
    NJet_MET_T1R      = cms.InputTag("caloType1CorrectedMetResidual"),   
    NJet_MET_T2R      = cms.InputTag("caloType1p2CorrectedMetResidual"),  
    NJet_Rho          = cms.InputTag('kt6CaloJets','rho'),
    NJet_Rho25        = cms.InputTag('rho25kt6CaloJets','rho'),
    NJetRecTracks     = cms.InputTag("generalTracks"),
    NJetRecMuons      = cms.InputTag("muons"),
    NJet_Weight       = cms.double(1),
    NJet_Weight_Tag   = cms.InputTag("genEventScale"),
    ECALDeadCellTPFilterModuleName = cms.InputTag(""), # Ignored if empty
    ECALDeadCellBEFilterModuleName = cms.InputTag(""), # Ignored if empty
    NJet_GenJets      = cms.InputTag("ak5GenJets"),
    NJet_GenParticles = cms.InputTag("genParticles"),
    NJetConeSize      = cms.double(0.5),
    NJetZSPJets       = cms.InputTag("ZSPJetCorJetAntiKt5"),
    NJetSecondVx      = cms.InputTag(ShortNameNextJetTypes+"CombinedSecondaryVertexBJetTags"),
    NJetSecondVxTagInfo      = cms.InputTag(ShortNameNextJetTypes+"SecondaryVertexTagInfos"),
    NJetTrackIPTagInfos      = cms.InputTag(ShortNameNextJetTypes+"ImpactParameterTagInfos"),
    NJet_svComputer          = cms.InputTag(ShortNameNextJetTypes+"StandardCombinedSecondaryVertex"),
    NJet_ProcessName         = cms.string("HLT"), #HLT default process used for processing triggers
    NJet_L1JetCorrector       = cms.string(ShortNameNextJetTypes+'L1Offset'),
    NJet_L2JetCorrector       = cms.string(ShortNameNextJetTypes+'L2Relative'),
    NJet_L3JetCorrector       = cms.string(ShortNameNextJetTypes+'L3Absolute'),
    NJet_JPTZSPCorrector      = cms.string('JetPlusTrackZSPCorrectorAntiKt5'),
    NJet_L1L2L3JetCorrector     = cms.string(ShortNameNextJetTypes+'L1L2L3'),
    NJet_L1L2L3L4JWJetCorrector = cms.string(ShortNameNextJetTypes+'L1L2L3'),
    NJet_L2L3JetCorrectorJPT  = cms.string('ak5JPTL2L3'),
    NJet_writeTracks  = cms.bool(False),
    NJet_writeTowers  = cms.bool(False),

    WriteGenJetParticles = cms.bool(False), 
    WriteStableGenParticles = cms.bool(False),                             
                                  
    WritePhotons  = cms.bool(False),
    WriteMuons    = cms.bool(False),
    WriteTaus    = cms.bool(False)                                 
)

calibTreeMaker = calibTreeMakerCalo.clone(
    OutputFile = 'calib.root'
)

ShortNameNextJetTypes          = 'ak5PF'
calibTreeMakerPF = cms.EDAnalyzer("CalibTreeMakerPF",
    TrackAssociatorParameters,
    TrackAssociatorParameterBlock,

    OutputFile         = cms.string(ShortNameNextJetTypes+'.root'),
    TreeName      = cms.string('DiJetTree'),

    GenEventScaleLabel   = cms.InputTag("genEventScale"),                             
               
    PhotonJetPhotons     = cms.InputTag("photons"),
    PhotonJetGenPhotons  = cms.InputTag("goodGenPhotons"),
 
    DimuonJetMuons       = cms.InputTag("muons"),
    DimuonJetGenMuons    = cms.InputTag("goodGenMuons"),
 
    TauAnaProducer       = cms.InputTag("hpsPFTauProducer"),
    TauAnaDiscriminator    = cms.InputTag("hpsPFTauDiscriminationByDecayModeFinding"),    
  
    BeamSpot = cms.InputTag("offlineBeamSpot"),
                              
    NJet_Jets         = cms.InputTag(ShortNameNextJetTypes+"Jets"),
    NJet_MinNumJets   = cms.int32(1),                             
    NJet_MaxNumJets   = cms.int32(50),
    NJet_JetIDs       = cms.InputTag(""), 
    NJet_PartonMatch  = cms.InputTag("PFJetPartonMatching"),
    NJet_MET          = cms.InputTag("pfMet"),
    NJet_MET_T1       = cms.InputTag("pfType1CorrectedMet"),
    NJet_MET_T2       = cms.InputTag("pfType1p2CorrectedMet"),  
    NJet_MET_T1R      = cms.InputTag("pfType1CorrectedMetResidual"),  
    NJet_MET_T2R      = cms.InputTag("pfType1p2CorrectedMetResidual"),   
    NJet_Rho          = cms.InputTag('kt6PFJets','rho'),
    NJet_Rho25        = cms.InputTag('rho25kt6PFJets','rho'),
    NJetRecTracks     = cms.InputTag("generalTracks"),
    NJetRecMuons      = cms.InputTag("muons"),
    NJet_Weight       = cms.double(1),
    NJet_Weight_Tag   = cms.InputTag("genEventWeight"),
    ECALDeadCellTPFilterModuleName = cms.InputTag(""), # Ignored if empty
    ECALDeadCellBEFilterModuleName = cms.InputTag(""), # Ignored if empty
    NJet_GenJets             = cms.InputTag("ak5GenJets"),
    NJet_GenParticles        = cms.InputTag("genParticles"),
    NJetConeSize             = cms.double(0.5),
    NJetZSPJets              = cms.InputTag("ZSPJetCorJetAntiKt5"),
    NJetSecondVx             = cms.InputTag(ShortNameNextJetTypes+"CombinedSecondaryVertexBJetTags"),
    NJetSecondVxTagInfo      = cms.InputTag(ShortNameNextJetTypes+"SecondaryVertexTagInfos"),
    NJetTrackIPTagInfos      = cms.InputTag(ShortNameNextJetTypes+"ImpactParameterTagInfos"),
    NJet_svComputer          = cms.InputTag(ShortNameNextJetTypes+"StandardCombinedSecondaryVertex"),
    NJet_ProcessName         = cms.string("HLT"), #HLT default process used for processing triggers
    NJet_L1JetCorrector       = cms.string(ShortNameNextJetTypes+'L1Offset'),
    NJet_L2JetCorrector       = cms.string(ShortNameNextJetTypes+'L2Relative'),
    NJet_L3JetCorrector       = cms.string(ShortNameNextJetTypes+'L3Absolute'),
    NJet_JPTZSPCorrector      = cms.string('JetPlusTrackZSPCorrectorAntiKt5'),
    NJet_L1L2L3JetCorrector     = cms.string(ShortNameNextJetTypes+'L1L2L3'),
    NJet_L1L2L3L4JWJetCorrector = cms.string(ShortNameNextJetTypes+'L1L2L3'),
    NJet_L2L3JetCorrectorJPT  = cms.string('ak5JPTL2L3'),
    NJet_writeTracks  = cms.bool(False),
    NJet_writeTowers  = cms.bool(False),

    WriteGenJetParticles = cms.bool(False), 
    WriteStableGenParticles = cms.bool(False),                             
                                  
    WritePhotons  = cms.bool(False),
    WriteMuons    = cms.bool(False),
    WriteTaus    = cms.bool(False)   
)

ShortNameNextJetTypes          = 'ak5Track'
calibTreeMakerTrack = cms.EDAnalyzer("CalibTreeMakerTrack",
    TrackAssociatorParameters,
    TrackAssociatorParameterBlock,
                              
    OutputFile         = cms.string(ShortNameNextJetTypes+'.root'),
    TreeName      = cms.string('DiJetTree'),

    GenEventScaleLabel   = cms.InputTag("genEventScale"),                             
               
    PhotonJetPhotons     = cms.InputTag("photons"),
    PhotonJetGenPhotons  = cms.InputTag("goodGenPhotons"),    

    DimuonJetMuons       = cms.InputTag("muons"),
    DimuonJetGenMuons    = cms.InputTag("goodGenMuons"),
 
    TauAnaProducer       = cms.InputTag("hpsPFTauProducer"),
    TauAnaDiscriminator    = cms.InputTag("hpsPFTauDiscriminationByDecayModeFinding"),    
         
    BeamSpot = cms.InputTag("offlineBeamSpot"),
                              
    NJet_Jets         = cms.InputTag(ShortNameNextJetTypes+"Jets"),
    NJet_MinNumJets   = cms.int32(1),                             
    NJet_MaxNumJets   = cms.int32(50),
    NJet_JetIDs       = cms.InputTag(""),
    NJet_PartonMatch  = cms.InputTag("TrackJetPartonMatching"),
    NJet_MET          = cms.InputTag("pfMet"),
    NJet_Rho          = cms.InputTag('kt6PFJets','rho'), #should be changed to track jets (deprecated, anyway)?
    NJet_Rho25        = cms.InputTag('rho25kt6PFJets','rho'), #should be changed to track jets (deprecated, anyway)?
    NJet_MET_T1       = cms.InputTag("pfType1CorrectedMet"),
    NJet_MET_T2       = cms.InputTag("pfType1p2CorrectedMet"),  
    NJet_MET_T1R      = cms.InputTag("pfType1CorrectedMetResidual"),  
    NJet_MET_T2R      = cms.InputTag("pfType1p2CorrectedMetResidual"),   
    NJetRecTracks     = cms.InputTag("generalTracks"),
    NJetRecMuons      = cms.InputTag("muons"),
    NJet_Weight       = cms.double(1),
    NJet_Weight_Tag   = cms.InputTag("genEventWeight"),
    ECALDeadCellTPFilterModuleName = cms.InputTag(""), # Ignored if empty
    ECALDeadCellBEFilterModuleName = cms.InputTag(""), # Ignored if empty
    NJet_GenJets      = cms.InputTag("ak5GenJets"),
    NJet_GenParticles = cms.InputTag("genParticles"),
    NJetConeSize      = cms.double(0.5),
    NJetZSPJets       = cms.InputTag("ZSPJetCorJetAntiKt5"),    
    NJetSecondVx      = cms.InputTag(ShortNameNextJetTypes+"CombinedSecondaryVertexBJetTags"),
    NJetSecondVxTagInfo      = cms.InputTag(ShortNameNextJetTypes+"SecondaryVertexTagInfos"),
    NJetTrackIPTagInfos      = cms.InputTag(ShortNameNextJetTypes+"ImpactParameterTagInfos"),
    NJet_svComputer          = cms.InputTag(ShortNameNextJetTypes+"StandardCombinedSecondaryVertex"),
    NJet_ProcessName         = cms.string("HLT"), #HLT default process used for processing triggers
    NJet_L1JetCorrector       = cms.string(ShortNameNextJetTypes+'L1Offset'),
    NJet_L2JetCorrector       = cms.string(ShortNameNextJetTypes+'L2Relative'),
    NJet_L3JetCorrector       = cms.string(ShortNameNextJetTypes+'L3Absolute'),
    NJet_JPTZSPCorrector      = cms.string('JetPlusTrackZSPCorrectorAntiKt5'),
    NJet_L1L2L3JetCorrector     = cms.string(ShortNameNextJetTypes+'L1L2L3'),
    NJet_L1L2L3L4JWJetCorrector = cms.string(ShortNameNextJetTypes+'L1L2L3'),
    NJet_L2L3JetCorrectorJPT  = cms.string('ak5JPTL2L3'),
    NJet_writeTracks  = cms.bool(False),
    NJet_writeTowers  = cms.bool(False),
 
    WriteGenJetParticles = cms.bool(False), 
    WriteStableGenParticles = cms.bool(False),                             
                                   
    WritePhotons  = cms.bool(False),
    WriteMuons    = cms.bool(False),
    WriteTaus    = cms.bool(False)   
)
 
ShortNameNextJetTypes          = 'ak5JPT'
calibTreeMakerJPT = cms.EDAnalyzer("CalibTreeMakerJPT",
    TrackAssociatorParameters,
    TrackAssociatorParameterBlock,
                              
    OutputFile         = cms.string(ShortNameNextJetTypes+'.root'),
    TreeName      = cms.string('DiJetTree'),

    GenEventScaleLabel   = cms.InputTag("genEventScale"),
    
    PhotonJetPhotons     = cms.InputTag("photons"),
    PhotonJetGenPhotons  = cms.InputTag("goodGenPhotons"),    
 
    DimuonJetMuons       = cms.InputTag("muons"),
    DimuonJetGenMuons    = cms.InputTag("goodGenMuons"),
 
    TauAnaProducer       = cms.InputTag("hpsPFTauProducer"),
    TauAnaDiscriminator    = cms.InputTag("hpsPFTauDiscriminationByDecayModeFinding"),    
         
    BeamSpot = cms.InputTag("offlineBeamSpot"),
                               
    NJet_Jets         = cms.InputTag("JetPlusTrackZSPCorJetAntiKt5"),
    NJet_MinNumJets   = cms.int32(1),                             
    NJet_MaxNumJets   = cms.int32(50),
    NJet_JetIDs       = cms.InputTag("ak5JetID"),
    NJet_PartonMatch  = cms.InputTag("JPTJetPartonMatching"),
    NJet_MET          = cms.InputTag("tcMet"),
    NJet_MET_T1       = cms.InputTag("tcMet"),    
    NJet_MET_T2       = cms.InputTag("tcMet"),    
    NJet_MET_T1R      = cms.InputTag("tcMet"),    
    NJet_MET_T2R      = cms.InputTag("tcMet"),    
    NJetRecTracks     = cms.InputTag("generalTracks"), 
    NJetRecMuons      = cms.InputTag("muons"),
    NJet_Rho          = cms.InputTag('kt6PFJets','rho'), #should be changed to JPT/Calo jets?
    NJet_Rho25        = cms.InputTag('rho25kt6PFJets','rho'), #should be changed to JPT/Calo jets?
    NJet_Weight       = cms.double(1),
    NJet_Weight_Tag   = cms.InputTag("genEventWeight"),
    ECALDeadCellTPFilterModuleName = cms.InputTag(""), # Ignored if empty
    ECALDeadCellBEFilterModuleName = cms.InputTag(""), # Ignored if empty
    NJet_GenJets      = cms.InputTag("ak5GenJets"),
    NJet_GenParticles = cms.InputTag("genParticles"),
    NJetConeSize      = cms.double(0.5),
    NJetZSPJets       = cms.InputTag("ZSPJetCorJetAntiKt5"),
    NJetSecondVx      = cms.InputTag(ShortNameNextJetTypes+"CombinedSecondaryVertexBJetTags"),
    NJetSecondVxTagInfo      = cms.InputTag(ShortNameNextJetTypes+"SecondaryVertexTagInfos"),
    NJetTrackIPTagInfos      = cms.InputTag(ShortNameNextJetTypes+"ImpactParameterTagInfos"),
    NJet_svComputer          = cms.InputTag(ShortNameNextJetTypes+"StandardCombinedSecondaryVertex"),
    NJet_ProcessName         = cms.string("HLT"), #HLT default process used for processing triggers
    NJet_L1JetCorrector       = cms.string(ShortNameNextJetTypes+'L1Offset'),
    NJet_L2JetCorrector       = cms.string(ShortNameNextJetTypes+'L2Relative'),
    NJet_L3JetCorrector       = cms.string(ShortNameNextJetTypes+'L3Absolute'),
    NJet_JPTZSPCorrector      = cms.string('JetPlusTrackZSPCorrectorAntiKt5'),
    NJet_L1L2L3JetCorrector     = cms.string(ShortNameNextJetTypes+'L1L2L3'),
    NJet_L1L2L3L4JWJetCorrector = cms.string(ShortNameNextJetTypes+'L1L2L3'),
    NJet_L2L3JetCorrectorJPT  = cms.string('ak5JPTL2L3'),
    NJet_writeTracks  = cms.bool(False),
    NJet_writeTowers  = cms.bool(False),

    WriteGenJetParticles = cms.bool(False), 
    WriteStableGenParticles = cms.bool(False),                             
                                  
    WritePhotons  = cms.bool(False),
    WriteMuons  = cms.bool(False),
    WriteTaus    = cms.bool(False) 
)

ShortNameNextJetTypes          = 'ak5PFCluster'
calibTreeMakerPFCluster = cms.EDAnalyzer("CalibTreeMakerPFCluster",
    TrackAssociatorParameters,
    TrackAssociatorParameterBlock,
                              
    OutputFile =  cms.string(ShortNameNextJetTypes+'.root'),
    TreeName      = cms.string('DiJetTree'),

    GenEventScaleLabel   = cms.InputTag("genEventScale"),                             
               
    PhotonJetPhotons     = cms.InputTag("photons"),
    PhotonJetGenPhotons  = cms.InputTag("goodGenPhotons"),

    DimuonJetMuons       = cms.InputTag("muons"),
    DimuonJetGenMuons    = cms.InputTag("goodGenMuons"),
  
    TauAnaProducer       = cms.InputTag("hpsPFTauProducer"),
    TauAnaDiscriminator    = cms.InputTag("hpsPFTauDiscriminationByDecayModeFinding"),    
        
    BeamSpot = cms.InputTag("offlineBeamSpot"),
                              
    NJet_Jets         = cms.InputTag(ShortNameNextJetTypes+"Jets"),
    NJet_MinNumJets   = cms.int32(0),                             
    NJet_MaxNumJets   = cms.int32(50),
    NJet_JetIDs       = cms.InputTag(""), 
    NJet_PartonMatch  = cms.InputTag("PFClusterJetPartonMatching"),
    NJet_MET          = cms.InputTag("pfClusterMet"),
    NJet_Rho          = cms.InputTag('kt6CaloJets','rho'), #should be changed to PFjets?
    NJet_Rho25        = cms.InputTag('rho25kt6CaloJets','rho'), #should be changed to PFjets?
    NJet_MET_T1       = cms.InputTag("pfCHSType1CorrectedMet"),
    NJet_MET_T2       = cms.InputTag("pfCHSType1p2CorrectedMet"),  
    NJet_MET_T1R      = cms.InputTag("pfCHSType1CorrectedMetResidual"),  
    NJet_MET_T2R      = cms.InputTag("pfCHSType1p2CorrectedMetResidual"),      
    NJetRecTracks     = cms.InputTag("generalTracks"),
    NJetRecMuons      = cms.InputTag("muons"),
    NJet_Weight       = cms.double(1),
    NJet_Weight_Tag   = cms.InputTag("genEventWeight"),
    ECALDeadCellTPFilterModuleName = cms.InputTag(""), # Ignored if empty
    ECALDeadCellBEFilterModuleName = cms.InputTag(""), # Ignored if empty
    NJet_GenJets      = cms.InputTag("ak5GenJets"),
    NJet_GenParticles = cms.InputTag("genParticles"),
    NJetConeSize      = cms.double(0.5),
    NJetZSPJets       = cms.InputTag("ZSPJetCorJetAntiKt5"),
    NJetSecondVx      = cms.InputTag(ShortNameNextJetTypes+"CombinedSecondaryVertexBJetTags"),
    NJetSecondVxTagInfo      = cms.InputTag(ShortNameNextJetTypes+"SecondaryVertexTagInfos"),
    NJetTrackIPTagInfos      = cms.InputTag(ShortNameNextJetTypes+"ImpactParameterTagInfos"),
    NJet_svComputer          = cms.InputTag(ShortNameNextJetTypes+"StandardCombinedSecondaryVertex"),
    NJet_ProcessName         = cms.string("HLT"), #HLT default process used for processing triggers
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
    WriteMuons    = cms.bool(False),
    WriteTaus    = cms.bool(False) 
)


