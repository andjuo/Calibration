import FWCore.ParameterSet.Config as cms

from TrackingTools.TrackAssociator.default_cfi import *
calibTreeMaker = cms.EDFilter("CalibTreeMaker",
    TrackAssociatorParameters,
    TrackAssociatorParameterBlock,

    PhotonJetJets = cms.InputTag("MyPhotonJetJets"),
    PhotonJetPhotons = cms.InputTag("MyPhotonJetPhotons"),
    PhotonJetGenPhotons = cms.InputTag("MyPhotonJetGenPhotons"),
    PhotonJetNonLeadingJetsPt = cms.InputTag("MyPhotonJetNonLeadingJetsPt"),
    PhotonJetRecTracks = cms.InputTag("MyPhotonJetRecTracks"),
    PhotonJetRecMuons= cms.InputTag("MyPhotonJetRecMuons"),
    PhotonJetTreeName = cms.string('GammaJetTree'),
    PhotonJetMet = cms.InputTag("MyPhotonJetMet"),
    PhotonJetConeSize = cms.double(0.5),
    PhotonJetGenJets = cms.InputTag("MyPhotonJetGenJets"),
    PhotonJetTowers = cms.InputTag("MyPhotonJetTowers"),
    WritePhotonJetTree = cms.bool(False)

    TrackTowerTracks = cms.InputTag("MyTrackTowerTracks"),
    TrackTowerTreeName = cms.string('TrackTowerTree'),
    TrackTowerTowers = cms.InputTag("MyTrackTowerTowers"),
    WriteTrackTowerTree = cms.bool(False),

    NJet_Jets = cms.InputTag("MyNJet_Jets"),
    NJet_MET = cms.InputTag("MyNJet_MET"),
    NJet_GenJets = cms.InputTag("MyNJet_GenJets"),
    NJet_Weight = cms.InputTag("MyNJet_Weight"),
    TriJetTreeName = cms.string('TriJetTree'),
    DiJetTreeName = cms.string('DiJetTree'),
    WriteDiJetTree = cms.bool(False),
    WriteTriJetTree = cms.bool(False),

    TopHadBJets  = cms.InputTag("MyTopHadBJets"),
    TopHadWJets  = cms.InputTag("MyTopHadWJets"),
    Top_Weight = cms.InputTag("MyNJet_Weight"),
    TopTreeName = cms.string('TriJetTree'),
    TopTree = cms.bool(False),

    EBRecHits = cms.InputTag("ecalRecHit","EcalRecHitsEB","Rec1"),
    OutputFile = cms.string('calib.root'),
)

