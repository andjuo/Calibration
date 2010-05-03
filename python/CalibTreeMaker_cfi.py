import FWCore.ParameterSet.Config as cms

from TrackingTools.TrackAssociator.default_cfi import *

calibTreeMakerCalo = cms.EDFilter("CalibTreeMakerCalo",
    TrackAssociatorParameters,
    TrackAssociatorParameterBlock,
                              
    OutputFile         = cms.string('calib.root'),

    TriJetTreeName     = cms.string('TriJetTree'),
    DiJetTreeName      = cms.string('DiJetTree'),
    PhotonJetTreeName  = cms.string('GammaJetTree'),
    TrackTowerTreeName = cms.string('TrackTowerTree'),
    TopTreeName        = cms.string('TopTree'),
    ZJetTreeName       = cms.string('ZJetTree'),

    GenEventScaleLabel   = cms.InputTag("genEventScale"),                             
               
    PhotonJetJets        = cms.InputTag("MyPhotonJetJets"),
    PhotonJetCaloJets    = cms.InputTag('sisCone5CaloJets'),
    PhotonJetPhotons     = cms.InputTag("MyPhotonJetPhotons"),
    PhotonJetGenPhotons  = cms.InputTag("MyPhotonJetGenPhotons"),
    PhotonJetGenJets     = cms.InputTag("MyPhotonJetGenJets"),
    PhotonJetNonLeadingJetsPt = cms.InputTag("MyPhotonJetNonLeadingJetsPt"),
    EBRecHits            = cms.InputTag("ecalRecHit","EcalRecHitsEB","Rec1"),
    PhotonJetRecTracks   = cms.InputTag("MyPhotonJetRecTracks"),
    PhotonJetRecMuons    = cms.InputTag("MyPhotonJetRecMuons"),
    PhotonJetTowers      = cms.InputTag("MyPhotonJetTowers"),
    PhotonJetMet         = cms.InputTag("MyPhotonJetMet"),
    PhotonJetConeSize    = cms.double(0.5),
    PhotonJet_Weight     = cms.double(1.),
    PhotonJet_Weight_Tag = cms.InputTag("MyPhotonJet_Weight_Tag"),
    PhotonJetZSPJets     = cms.InputTag("MyPhotonJetZSPJets"),
    PhotonJetPFJets      = cms.InputTag("MyZJetPFJets"),


               
    ZJetJets        = cms.InputTag("MyZJetJets"),
    ZJetCaloJets    = cms.InputTag('sisCone5CaloJets'),
    ZJetZs          = cms.InputTag("MyZJetZs"),
    ZJetGenZs  = cms.InputTag("MyZJetGenZs"),
    ZJetGenJets     = cms.InputTag("MyZJetGenJets"),
    ZJetNonLeadingJetsPt = cms.InputTag("MyZJetNonLeadingJetsPt"),
    ZJetRecTracks   = cms.InputTag("MyZJetRecTracks"),
    ZJetRecMuons    = cms.InputTag("MyZJetRecMuons"),
    ZJetTowers      = cms.InputTag("MyZJetTowers"),
    ZJetMet         = cms.InputTag("MyZJetMet"),
    ZJetConeSize    = cms.double(0.5),
    ZJet_Weight     = cms.double(1.),
    ZJet_Weight_Tag = cms.InputTag("MyZJet_Weight_Tag"),
    ZJetGenZ        = cms.InputTag("MyZGenZs"),
    ZJetZSPJets     = cms.InputTag("MyZJetZSPJets"),
    ZJetPFJets      = cms.InputTag("MyZJetPFJets"),


                              

    TrackTowerTracks = cms.InputTag("MyTrackTowerTracks"),
    TrackTowerTowers = cms.InputTag("MyTrackTowerTowers"),

    BeamSpot = cms.InputTag("offlineBeamSpot"),
                              
    NJet_Jets         = cms.InputTag("ak5CaloJets"),
    NJet_MinNumJets   = cms.int32(1),                             
    NJet_JetIDs       = cms.InputTag("ak5JetID"),
    NJet_MET          = cms.InputTag("met"),
    NJetRecTracks     = cms.InputTag("generalTracks"),
    NJetRecMuons      = cms.InputTag("muons"),
    NJet_Weight       = cms.double(1.),
    NJet_Weight_Tag   = cms.InputTag("genEventScale"),
    NJet_GenJets      = cms.InputTag("ak5GenKets"),
    NJet_GenParticles = cms.InputTag("genParticles"),
    NJetConeSize      = cms.double(0.5),
    NJetZSPJets       = cms.InputTag("ZSPJetCorJetAntiKt5"),

    TopHadBJets    = cms.InputTag("topSample:TopHadBJets"),
    TopHadWJets    = cms.InputTag("topSample:TopHadWJets"),
    TopHadBGenJets = cms.InputTag("topSample:TopHadBGenJets"),
    TopHadWGenJets = cms.InputTag("topSample:TopHadWGenJets"),
    Top_Weight     = cms.double(1.),
    Top_Weight_Tag = cms.InputTag("tag"),

    WriteGenJetParticles = cms.bool(False), 
    WriteStableGenParticles = cms.bool(False),                             
                                  
    WritePhotonJetTree  = cms.bool(False),
    WriteDiJetTree      = cms.bool(False),
    WriteTriJetTree     = cms.bool(False),
    WriteTrackTowerTree = cms.bool(False),
    WriteTopTree        = cms.bool(False),
    WriteZJetTree       = cms.bool(False),
)

calibTreeMaker = calibTreeMakerCalo.clone()

calibTreeMakerPF = cms.EDFilter("CalibTreeMakerPF",
    TrackAssociatorParameters,
    TrackAssociatorParameterBlock,
                              
    OutputFile         = cms.string('calib.root'),

    TriJetTreeName     = cms.string('TriJetTree'),
    DiJetTreeName      = cms.string('DiJetTree'),
    PhotonJetTreeName  = cms.string('GammaJetTree'),
    TrackTowerTreeName = cms.string('TrackTowerTree'),
    TopTreeName        = cms.string('TopTree'),
    ZJetTreeName       = cms.string('ZJetTree'),

    GenEventScaleLabel   = cms.InputTag("genEventScale"),                             
               
    PhotonJetJets        = cms.InputTag("MyPhotonJetJets"),
    PhotonJetCaloJets    = cms.InputTag('sisCone5CaloJets'),
    PhotonJetPhotons     = cms.InputTag("MyPhotonJetPhotons"),
    PhotonJetGenPhotons  = cms.InputTag("MyPhotonJetGenPhotons"),
    PhotonJetGenJets     = cms.InputTag("MyPhotonJetGenJets"),
    PhotonJetNonLeadingJetsPt = cms.InputTag("MyPhotonJetNonLeadingJetsPt"),
    EBRecHits            = cms.InputTag("ecalRecHit","EcalRecHitsEB","Rec1"),
    PhotonJetRecTracks   = cms.InputTag("MyPhotonJetRecTracks"),
    PhotonJetRecMuons    = cms.InputTag("MyPhotonJetRecMuons"),
    PhotonJetTowers      = cms.InputTag("MyPhotonJetTowers"),
    PhotonJetMet         = cms.InputTag("MyPhotonJetMet"),
    PhotonJetConeSize    = cms.double(0.5),
    PhotonJet_Weight     = cms.double(1.),
    PhotonJet_Weight_Tag = cms.InputTag("MyPhotonJet_Weight_Tag"),
    PhotonJetZSPJets     = cms.InputTag("MyPhotonJetZSPJets"),
    PhotonJetPFJets      = cms.InputTag("MyZJetPFJets"),


               
    ZJetJets        = cms.InputTag("MyZJetJets"),
    ZJetCaloJets    = cms.InputTag('sisCone5CaloJets'),
    ZJetZs          = cms.InputTag("MyZJetZs"),
    ZJetGenZs  = cms.InputTag("MyZJetGenZs"),
    ZJetGenJets     = cms.InputTag("MyZJetGenJets"),
    ZJetNonLeadingJetsPt = cms.InputTag("MyZJetNonLeadingJetsPt"),
    ZJetRecTracks   = cms.InputTag("MyZJetRecTracks"),
    ZJetRecMuons    = cms.InputTag("MyZJetRecMuons"),
    ZJetTowers      = cms.InputTag("MyZJetTowers"),
    ZJetMet         = cms.InputTag("MyZJetMet"),
    ZJetConeSize    = cms.double(0.5),
    ZJet_Weight     = cms.double(1.),
    ZJet_Weight_Tag = cms.InputTag("MyZJet_Weight_Tag"),
    ZJetGenZ        = cms.InputTag("MyZGenZs"),
    ZJetZSPJets     = cms.InputTag("MyZJetZSPJets"),
    ZJetPFJets      = cms.InputTag("MyZJetPFJets"),


                              

    TrackTowerTracks = cms.InputTag("MyTrackTowerTracks"),
    TrackTowerTowers = cms.InputTag("MyTrackTowerTowers"),

    BeamSpot = cms.InputTag("offlineBeamSpot"),
                              
    NJet_Jets         = cms.InputTag("ak5PFJets"),
    NJet_MinNumJets   = cms.int32(1),                             
    NJet_JetIDs       = cms.InputTag(""),
    NJet_MET          = cms.InputTag("met"),
    NJetRecTracks     = cms.InputTag("generalTracks"),
    NJetRecMuons      = cms.InputTag("muons"),
    NJet_Weight       = cms.double(1.),
    NJet_Weight_Tag   = cms.InputTag("genEventWeight"),
    NJet_GenJets      = cms.InputTag("ak5GenJet"),
    NJet_GenParticles = cms.InputTag("genParticles"),
    NJetConeSize      = cms.double(0.5),
    NJetZSPJets       = cms.InputTag("ZSPJetCorJetAntiKt5"),

    TopHadBJets    = cms.InputTag("topSample:TopHadBJets"),
    TopHadWJets    = cms.InputTag("topSample:TopHadWJets"),
    TopHadBGenJets = cms.InputTag("topSample:TopHadBGenJets"),
    TopHadWGenJets = cms.InputTag("topSample:TopHadWGenJets"),
    Top_Weight     = cms.double(1.),
    Top_Weight_Tag = cms.InputTag("tag"),

    WriteGenJetParticles = cms.bool(False), 
    WriteStableGenParticles = cms.bool(False),                             
                                  
    WritePhotonJetTree  = cms.bool(False),
    WriteDiJetTree      = cms.bool(False),
    WriteTriJetTree     = cms.bool(False),
    WriteTrackTowerTree = cms.bool(False),
    WriteTopTree        = cms.bool(False),
    WriteZJetTree       = cms.bool(False),
)

calibTreeMakerTrack = cms.EDFilter("CalibTreeMakerTrack",
    TrackAssociatorParameters,
    TrackAssociatorParameterBlock,
                              
    OutputFile         = cms.string('calib.root'),

    TriJetTreeName     = cms.string('TriJetTree'),
    DiJetTreeName      = cms.string('DiJetTree'),
    PhotonJetTreeName  = cms.string('GammaJetTree'),
    TrackTowerTreeName = cms.string('TrackTowerTree'),
    TopTreeName        = cms.string('TopTree'),
    ZJetTreeName       = cms.string('ZJetTree'),

    GenEventScaleLabel   = cms.InputTag("genEventScale"),                             
               
    PhotonJetJets        = cms.InputTag("MyPhotonJetJets"),
    PhotonJetCaloJets    = cms.InputTag('sisCone5CaloJets'),
    PhotonJetPhotons     = cms.InputTag("MyPhotonJetPhotons"),
    PhotonJetGenPhotons  = cms.InputTag("MyPhotonJetGenPhotons"),
    PhotonJetGenJets     = cms.InputTag("MyPhotonJetGenJets"),
    PhotonJetNonLeadingJetsPt = cms.InputTag("MyPhotonJetNonLeadingJetsPt"),
    EBRecHits            = cms.InputTag("ecalRecHit","EcalRecHitsEB","Rec1"),
    PhotonJetRecTracks   = cms.InputTag("MyPhotonJetRecTracks"),
    PhotonJetRecMuons    = cms.InputTag("MyPhotonJetRecMuons"),
    PhotonJetTowers      = cms.InputTag("MyPhotonJetTowers"),
    PhotonJetMet         = cms.InputTag("MyPhotonJetMet"),
    PhotonJetConeSize    = cms.double(0.5),
    PhotonJet_Weight     = cms.double(1.),
    PhotonJet_Weight_Tag = cms.InputTag("MyPhotonJet_Weight_Tag"),
    PhotonJetZSPJets     = cms.InputTag("MyPhotonJetZSPJets"),
    PhotonJetPFJets      = cms.InputTag("MyZJetPFJets"),


               
    ZJetJets        = cms.InputTag("MyZJetJets"),
    ZJetCaloJets    = cms.InputTag('sisCone5CaloJets'),
    ZJetZs          = cms.InputTag("MyZJetZs"),
    ZJetGenZs  = cms.InputTag("MyZJetGenZs"),
    ZJetGenJets     = cms.InputTag("MyZJetGenJets"),
    ZJetNonLeadingJetsPt = cms.InputTag("MyZJetNonLeadingJetsPt"),
    ZJetRecTracks   = cms.InputTag("MyZJetRecTracks"),
    ZJetRecMuons    = cms.InputTag("MyZJetRecMuons"),
    ZJetTowers      = cms.InputTag("MyZJetTowers"),
    ZJetMet         = cms.InputTag("MyZJetMet"),
    ZJetConeSize    = cms.double(0.5),
    ZJet_Weight     = cms.double(1.),
    ZJet_Weight_Tag = cms.InputTag("MyZJet_Weight_Tag"),
    ZJetGenZ        = cms.InputTag("MyZGenZs"),
    ZJetZSPJets     = cms.InputTag("MyZJetZSPJets"),
    ZJetPFJets      = cms.InputTag("MyZJetPFJets"),


                              

    TrackTowerTracks = cms.InputTag("MyTrackTowerTracks"),
    TrackTowerTowers = cms.InputTag("MyTrackTowerTowers"),

    BeamSpot = cms.InputTag("offlineBeamSpot"),
                              
    NJet_Jets         = cms.InputTag("ak5TrackJets"),
    NJet_MinNumJets   = cms.int32(1),                             
    NJet_JetIDs       = cms.InputTag(""),
    NJet_MET          = cms.InputTag("met"),
    NJetRecTracks     = cms.InputTag("generalTracks"),
    NJetRecMuons      = cms.InputTag("muons"),
    NJet_Weight       = cms.double(1.),
    NJet_Weight_Tag   = cms.InputTag("genEventWeight"),
    NJet_GenJets      = cms.InputTag("ak5GenJet"),
    NJet_GenParticles = cms.InputTag("genParticles"),
    NJetConeSize      = cms.double(0.5),
    NJetZSPJets       = cms.InputTag("ZSPJetCorJetAntiKt5"),

    TopHadBJets    = cms.InputTag("topSample:TopHadBJets"),
    TopHadWJets    = cms.InputTag("topSample:TopHadWJets"),
    TopHadBGenJets = cms.InputTag("topSample:TopHadBGenJets"),
    TopHadWGenJets = cms.InputTag("topSample:TopHadWGenJets"),
    Top_Weight     = cms.double(1.),
    Top_Weight_Tag = cms.InputTag("tag"),

    WriteGenJetParticles = cms.bool(False), 
    WriteStableGenParticles = cms.bool(False),                             
                                  
    WritePhotonJetTree  = cms.bool(False),
    WriteDiJetTree      = cms.bool(False),
    WriteTriJetTree     = cms.bool(False),
    WriteTrackTowerTree = cms.bool(False),
    WriteTopTree        = cms.bool(False),
    WriteZJetTree       = cms.bool(False),
)

calibTreeMakerJPT = cms.EDFilter("CalibTreeMakerJPT",
    TrackAssociatorParameters,
    TrackAssociatorParameterBlock,
                              
    OutputFile         = cms.string('calib.root'),

    TriJetTreeName     = cms.string('TriJetTree'),
    DiJetTreeName      = cms.string('DiJetTree'),
    PhotonJetTreeName  = cms.string('GammaJetTree'),
    TrackTowerTreeName = cms.string('TrackTowerTree'),
    TopTreeName        = cms.string('TopTree'),
    ZJetTreeName       = cms.string('ZJetTree'),

    GenEventScaleLabel   = cms.InputTag("genEventScale"),                             
               
    PhotonJetJets        = cms.InputTag("MyPhotonJetJets"),
    PhotonJetCaloJets    = cms.InputTag('sisCone5CaloJets'),
    PhotonJetPhotons     = cms.InputTag("MyPhotonJetPhotons"),
    PhotonJetGenPhotons  = cms.InputTag("MyPhotonJetGenPhotons"),
    PhotonJetGenJets     = cms.InputTag("MyPhotonJetGenJets"),
    PhotonJetNonLeadingJetsPt = cms.InputTag("MyPhotonJetNonLeadingJetsPt"),
    EBRecHits            = cms.InputTag("ecalRecHit","EcalRecHitsEB","Rec1"),
    PhotonJetRecTracks   = cms.InputTag("MyPhotonJetRecTracks"),
    PhotonJetRecMuons    = cms.InputTag("MyPhotonJetRecMuons"),
    PhotonJetTowers      = cms.InputTag("MyPhotonJetTowers"),
    PhotonJetMet         = cms.InputTag("MyPhotonJetMet"),
    PhotonJetConeSize    = cms.double(0.5),
    PhotonJet_Weight     = cms.double(1.),
    PhotonJet_Weight_Tag = cms.InputTag("MyPhotonJet_Weight_Tag"),
    PhotonJetZSPJets     = cms.InputTag("MyPhotonJetZSPJets"),
    PhotonJetPFJets      = cms.InputTag("MyZJetPFJets"),


               
    ZJetJets        = cms.InputTag("MyZJetJets"),
    ZJetCaloJets    = cms.InputTag('sisCone5CaloJets'),
    ZJetZs          = cms.InputTag("MyZJetZs"),
    ZJetGenZs  = cms.InputTag("MyZJetGenZs"),
    ZJetGenJets     = cms.InputTag("MyZJetGenJets"),
    ZJetNonLeadingJetsPt = cms.InputTag("MyZJetNonLeadingJetsPt"),
    ZJetRecTracks   = cms.InputTag("MyZJetRecTracks"),
    ZJetRecMuons    = cms.InputTag("MyZJetRecMuons"),
    ZJetTowers      = cms.InputTag("MyZJetTowers"),
    ZJetMet         = cms.InputTag("MyZJetMet"),
    ZJetConeSize    = cms.double(0.5),
    ZJet_Weight     = cms.double(1.),
    ZJet_Weight_Tag = cms.InputTag("MyZJet_Weight_Tag"),
    ZJetGenZ        = cms.InputTag("MyZGenZs"),
    ZJetZSPJets     = cms.InputTag("MyZJetZSPJets"),
    ZJetPFJets      = cms.InputTag("MyZJetPFJets"),


                              

    TrackTowerTracks = cms.InputTag("MyTrackTowerTracks"),
    TrackTowerTowers = cms.InputTag("MyTrackTowerTowers"),

    BeamSpot = cms.InputTag("offlineBeamSpot"),
                              
    NJet_Jets         = cms.InputTag("ak5JPTJets"),
    NJet_MinNumJets   = cms.int32(1),                             
    NJet_JetIDs       = cms.InputTag(""),
    NJet_MET          = cms.InputTag("met"),
    NJetRecTracks     = cms.InputTag("generalTracks"),
    NJetRecMuons      = cms.InputTag("muons"),
    NJet_Weight       = cms.double(1.),
    NJet_Weight_Tag   = cms.InputTag("genEventWeight"),
    NJet_GenJets      = cms.InputTag("ak5GenJet"),
    NJet_GenParticles = cms.InputTag("genParticles"),
    NJetConeSize      = cms.double(0.5),
    NJetZSPJets       = cms.InputTag("ZSPJetCorJetAntiKt5"),

    TopHadBJets    = cms.InputTag("topSample:TopHadBJets"),
    TopHadWJets    = cms.InputTag("topSample:TopHadWJets"),
    TopHadBGenJets = cms.InputTag("topSample:TopHadBGenJets"),
    TopHadWGenJets = cms.InputTag("topSample:TopHadWGenJets"),
    Top_Weight     = cms.double(1.),
    Top_Weight_Tag = cms.InputTag("tag"),

    WriteGenJetParticles = cms.bool(False), 
    WriteStableGenParticles = cms.bool(False),                             
                                  
    WritePhotonJetTree  = cms.bool(False),
    WriteDiJetTree      = cms.bool(False),
    WriteTriJetTree     = cms.bool(False),
    WriteTrackTowerTree = cms.bool(False),
    WriteTopTree        = cms.bool(False),
    WriteZJetTree       = cms.bool(False),
)

