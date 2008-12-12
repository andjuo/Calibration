import FWCore.ParameterSet.Config as cms

from TrackingTools.TrackAssociator.default_cfi import *
calibTreeMaker = cms.EDFilter("CalibTreeMaker",
    TrackAssociatorParameters,
    TrackAssociatorParameterBlock,
                              
    OutputFile         = cms.string('calib.root'),

    TriJetTreeName     = cms.string('TriJetTree'),
    DiJetTreeName      = cms.string('DiJetTree'),
    PhotonJetTreeName  = cms.string('GammaJetTree'),
    TrackTowerTreeName = cms.string('TrackTowerTree'),
    TopTreeName        = cms.string('TopTree'),
    ZJetTreeName       = cms.string('ZJetTree'),
               
    PhotonJetJets        = cms.InputTag("MyPhotonJetJets"),
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


               
    ZJetJets        = cms.InputTag("MyZJetJets"),
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


                              

    TrackTowerTracks = cms.InputTag("MyTrackTowerTracks"),
    TrackTowerTowers = cms.InputTag("MyTrackTowerTowers"),
                              
    NJet_Jets       = cms.InputTag("MyNJet_Jets"),
    NJet_MET        = cms.InputTag("MyNJet_MET"),
    NJetRecTracks   = cms.InputTag("MyNJetRecTracks"),
    NJetRecMuons    = cms.InputTag("MyNJetRecMuons"),
    NJet_Weight     = cms.double(1.),
    NJet_Weight_Tag = cms.InputTag("MyNJet_Weight_Tag"),
    NJet_GenJets    = cms.InputTag("MyNJet_GenJets"),
    NJetConeSize    = cms.double(0.5),

    TopHadBJets    = cms.InputTag("MyTopHadBJets"),
    TopHadWJets    = cms.InputTag("MyTopHadWJets"),
    Top_Weight     = cms.double(1.),
    Top_Weight_Tag = cms.InputTag("MyTop_Weight_Tag"),
                                  
    WritePhotonJetTree  = cms.bool(False),
    WriteDiJetTree      = cms.bool(False),
    WriteTriJetTree     = cms.bool(False),
    WriteTrackTowerTree = cms.bool(False),
    WriteTopTree        = cms.bool(False),
    WriteZJetTree       = cms.bool(False),
)

