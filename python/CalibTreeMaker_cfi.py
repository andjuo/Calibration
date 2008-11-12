import FWCore.ParameterSet.Config as cms

from TrackingTools.TrackAssociator.default_cfi import *
calibTreeMaker = cms.EDFilter("CalibTreeMaker",
    TrackAssociatorParameters,
    TrackAssociatorParameterBlock,
                              
    OutputFile = cms.string('calib.root'),
    TriJetTreeName = cms.string('TriJetTree'),
    DiJetTreeName = cms.string('DiJetTree'),
    PhotonJetTreeName = cms.string('GammaJetTree'),
    TrackTowerTreeName = cms.string('TrackTowerTree'),
    TopTreeName = cms.string('TopTree'),
               
    PhotonJetJets = cms.InputTag("MyPhotonJetJets"),
    PhotonJetPhotons = cms.InputTag("MyPhotonJetPhotons"),
    PhotonJetGenPhotons = cms.InputTag("MyPhotonJetGenPhotons"),
    PhotonJetGenJets = cms.InputTag("MyPhotonJetGenJets"),
    PhotonJetNonLeadingJetsPt = cms.InputTag("MyPhotonJetNonLeadingJetsPt"),
    EBRecHits = cms.InputTag("ecalRecHit","EcalRecHitsEB","Rec1"),
    PhotonJetRecTracks = cms.InputTag("MyPhotonJetRecTracks"),
    PhotonJetRecMuons= cms.InputTag("MyPhotonJetRecMuons"),
    PhotonJetTowers = cms.InputTag("MyPhotonJetTowers"),
    PhotonJetMet = cms.InputTag("MyPhotonJetMet"),
    PhotonJetConeSize = cms.double(0.5),
    PhotonJet_Weight = cms.double(1.),
    PhotonJet_Weight_Tag = cms.InputTag("MyPhotonJet_Weight_Tag"),

    TrackTowerTracks = cms.InputTag("MyTrackTowerTracks"),
    TrackTowerTowers = cms.InputTag("MyTrackTowerTowers"),
                              
    NJet_Jets = cms.InputTag("MyNJet_Jets"),
    NJet_MET = cms.InputTag("MyNJet_MET"),
    NJetRecTracks = cms.InputTag("MyPhotonJetRecTracks"),
    NJetRecMuons= cms.InputTag("MyPhotonJetRecMuons"),
    NJet_Weight = cms.double(1.),
    NJet_Weight_Tag = cms.InputTag("MyNJet_Weight_Tag"),
    NJet_GenJets = cms.InputTag("MyNJet_GenJets"),
    NJetConeSize = cms.double(0.5),

                                  
    WritePhotonJetTree = cms.bool(False),
    WriteDiJetTree = cms.bool(False),
    WriteTriJetTree = cms.bool(False),
    WriteTrackTowerTree = cms.bool(False),
    WriteTopTree = cms.bool(False),

    TopHadBJets  = cms.InputTag("MyTopHadBJets"),
    TopHadWJets  = cms.InputTag("MyTopHadWJets"),
    Top_Weight = cms.InputTag("MyNJet_Weight"),
)

