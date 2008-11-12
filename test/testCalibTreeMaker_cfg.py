import FWCore.ParameterSet.Config as cms

process = cms.Process("Calib")

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
   '/store/relval/CMSSW_2_1_9/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0001/6E9B44E2-0487-DD11-BFA7-001617C3B78C.root'
    )
                            )

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000) )

process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FakeConditions_cff")
process.load("Geometry.CommonDetUnit.bareGlobalTrackingGeometry_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagator_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAny_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAlong_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorOpposite_cfi")
process.load("TrackingTools.TrackAssociator.DetIdAssociatorESProducer_cff")
#process.load("TrackingTools.TrackAssociator.default_cfi")

process.load("Calibration.CalibTreeMaker.CalibTreeMaker_cff")

process.load("RecoJets.Configuration.RecoJetsAll_cff")

process.dump = cms.EDAnalyzer("EventContentAnalyzer")

#############   Define the L2 correction service #####
process.L2JetCorrector = cms.ESSource("L2RelativeCorrectionService", 
                                      tagName = cms.string('iCSA08_S156_L2Relative_Scone5'),
                                      label = cms.string('L2RelativeJetCorrector')
                                      )
#############   Define the L3 correction service #####
process.L3JetCorrector = cms.ESSource("L3AbsoluteCorrectionService", 
                                      tagName = cms.string('iCSA08_S156_L3Absolute_Scone5'),
                                      label = cms.string('L3AbsoluteJetCorrector')
                                      )

# set the record's IOV. Must be defined once. Choose ANY correction service. #
process.prefer("L2JetCorrector")

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
process.diJetFilter.MaxRefEta          = 1.5
process.diJetFilter.MaxEta             = 5.0
process.diJetFilter.MinJetPt           = 10.
#process.diJetFilter.sumPtMaxFracThird  = 0.1 (in CalibCore config?)
process.diJetFilter.MinJetPhiSum       = 0.1
#process.diJetFilter.deltaPhiMETMax     = 0.15 (?)
process.diJetFilter.MinJetEMF          = 0.05
process.diJetFilter.MaxJetEMF          = 0.95
process.diJetFilter.MaxLastJetPt       = 5.

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

#process.calibTreeMaker.OutputFile = 'NJet_Test_Track.root'
process.calibTreeMaker.OutputFile = 'Gamma25_30_Track.root'
#process.calibTreeMaker.OutputFile = 'DiJet_Track.root'
#process.calibTreeMaker.OutputFile = 'TriJet_Track.root'

process.calibTreeMaker.PhotonJetTreeName = 'GammaJetTree'
process.calibTreeMaker.PhotonJetJets = 'photonJetSample:LeadingJet'
process.calibTreeMaker.PhotonJetGenJets = 'photonJetSample:LeadingGenJet'
process.calibTreeMaker.PhotonJetPhotons = 'photonJetSample:LeadingPhoton'
process.calibTreeMaker.PhotonJetGenPhotons = 'photonJetSample:LeadingGenPhoton'
process.calibTreeMaker.PhotonJetNonLeadingJetsPt = 'photonJetSample:NonLeadingJetsPt'
process.calibTreeMaker.PhotonJetMet          = 'met'
process.calibTreeMaker.PhotonJetRecTracks    = 'generalTracks'
process.calibTreeMaker.PhotonJetRecMuons     = 'globalMuons'
process.calibTreeMaker.PhotonJetConeSize     = 0.5
process.calibTreeMaker.PhotonJet_Weight      = 1.
process.calibTreeMaker.PhotonJet_Weight_Tag  =     'tag'



process.calibTreeMaker.DiJetTreeName     ='DiJetTree'
process.calibTreeMaker.TriJetTreeName    ='TriJetTree'
process.calibTreeMaker.NJet_Jets         = 'sisCone5CaloJets'
#prosess.calibTreeMaker.JetJetGenJets      = iterativeCone5GenJetsPt10
process.calibTreeMaker.NJet_GenJets      = 'sisCone5GenJets'
process.calibTreeMaker.NJet_MET          = 'met'
process.calibTreeMaker.NJetRecTracks     = 'generalTracks'
process.calibTreeMaker.NJetRecMuons      = 'globalMuons'
process.calibTreeMaker.NJetConeSize      = 0.5
process.calibTreeMaker.NJet_Weight_Tag   =   'tag'
process.calibTreeMaker.NJet_Weight       = 1.


process.calibTreeMaker.TopTreeName     ='TopTree'


process.calibTreeMaker.WritePhotonJetTree = True
process.calibTreeMaker.WriteDiJetTree    = False
process.calibTreeMaker.WriteTriJetTree   = False


#process.p1 = cms.Path(process.dump)
#process.p1 = cms.Path(process.midPointCone5CaloJets*process.dump)
#process.p2 = cms.Path(process.midPointCone5CaloJets*process.makePhotonJetTree)
process.p2 = cms.Path(process.makePhotonJetTree)
#process.p2 = cms.Path(process.makeDiJetTree)
#process.p2 = cms.Path(process.makeTriJetTree)
process.schedule = cms.Schedule(process.p2)
