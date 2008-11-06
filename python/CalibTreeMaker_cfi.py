import FWCore.ParameterSet.Config as cms

from TrackingTools.TrackAssociator.default_cfi import *
calibTreeMaker = cms.EDFilter("CalibTreeMaker",
    TrackAssociatorParameters,
    TrackAssociatorParameterBlock,
    PhotonJetJets = cms.InputTag("MyPhotonJetJets"),
    TrackTowerTracks = cms.InputTag("MyTrackTowerTracks"),
    PhotonJetPhotons = cms.InputTag("MyPhotonJetPhotons"),
    WriteDiJetTree = cms.bool(False),
    TriJetTreeName = cms.string('TriJetTree'),
    DiJetTreeName = cms.string('DiJetTree'),
    PhotonJetGenPhotons = cms.InputTag("MyPhotonJetGenPhotons"),
    NJet_Jets = cms.InputTag("MyNJet_Jets"),
    NJet_MET = cms.InputTag("MyNJet_MET"),
    EBRecHits = cms.InputTag("ecalRecHit","EcalRecHitsEB","Rec1"),
    PhotonJetNonLeadingJetsPt = cms.InputTag("MyPhotonJetNonLeadingJetsPt"),
    TrackTowerTreeName = cms.string('TrackTowerTree'),
    PhotonJetRecTracks = cms.InputTag("MyPhotonJetRecTracks"),
    PhotonJetRecMuons= cms.InputTag("MyPhotonJetRecMuons"),
    PhotonJetTreeName = cms.string('GammaJetTree'),
    WriteTrackTowerTree = cms.bool(False),
    PhotonJetMet = cms.InputTag("MyPhotonJetMet"),
    PhotonJetConeSize = cms.double(0.5),
    NJet_Weight = cms.InputTag("MyNJet_Weight"),
    PhotonJetGenJets = cms.InputTag("MyPhotonJetGenJets"),
    TrackTowerTowers = cms.InputTag("MyTrackTowerTowers"),
    OutputFile = cms.string('calib.root'),
    PhotonJetTowers = cms.InputTag("MyPhotonJetTowers"),
    WriteTriJetTree = cms.bool(False),
    NJet_GenJets = cms.InputTag("MyNJet_GenJets"),
    WritePhotonJetTree = cms.bool(False)
)

