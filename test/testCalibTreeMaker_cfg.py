import FWCore.ParameterSet.Config as cms

process = cms.Process("Calib")

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
 # '/store/relval/CMSSW_2_1_9/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0001/6E9B44E2-0487-DD11-BFA7-001617C3B78C.root'
    
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/000AD2A4-6E86-DD11-AA99-000423D9863C.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/02D641CC-6D86-DD11-B1AA-001617C3B64C.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/0876950D-6F86-DD11-B4B8-000423D6A6F4.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/0AC366B7-6D86-DD11-8695-001617E30D0A.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/1415D0A5-6E86-DD11-8F0C-001617C3B778.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/145FBEB9-6D86-DD11-BD98-001617DF785A.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/1815C2A0-6E86-DD11-A160-001617E30F58.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/1869C2C0-6D86-DD11-ADB6-001617C3B76E.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/186A3FC0-6D86-DD11-B020-000423D6CA72.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/1A688BC9-6D86-DD11-8C60-001617DBD5AC.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/20EBA2C9-6D86-DD11-88EC-001617E30D40.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/24822ABB-6D86-DD11-B76B-001617E30F4C.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/24E0B0C7-6D86-DD11-8C09-0019DB29C5FC.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/2652503A-6F86-DD11-9552-001617E30F4C.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/26E79ACA-6D86-DD11-8A10-001617E30D00.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/2A0341A9-6E86-DD11-9AE4-000423D6CA02.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/3038D377-6E86-DD11-A974-001617C3B5E4.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/369AEBC5-6D86-DD11-B911-001617E30D4A.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/3841A6BC-6D86-DD11-9D84-001617E30D52.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/3C049BBF-6D86-DD11-8D0D-001617DBD556.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/3EBAB9A6-6E86-DD11-AB4D-001617C3B70E.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/3EBCA837-6F86-DD11-8892-001617E30D4A.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/3EDB9AD6-6E86-DD11-9EE3-000423D992A4.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/42CED2B7-6D86-DD11-B551-001617C3B6E2.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/441FDE81-6D86-DD11-863A-000423D985E4.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/48659740-6F86-DD11-926F-001617E30D12.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/488BFB15-6F86-DD11-B4A2-000423D6C8EE.root',
        '/store/relval/CMSSW_2_1_9/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0001/4AA2ACC0-6D86-DD11-8CC9-001617E30E2C.root'

    )
                            )

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(200) )

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

process.zJetSample.Muons = 'globalMuons'
process.zJetSample.GenZs = 'genParticles'
process.zJetSample.Jets = 'sisCone5CaloJets'
#process.zJetSample.Jets = 'midPointCone5CaloJets'
process.zJetSample.GenJets = 'sisCone5GenJets'
process.zJetSample.MinMuonPt = 15.
process.zJetSample.MaxMuonEta = 2.3
process.zJetSample.Z_Mass = 91.2
process.zJetSample.Z_Mass_Tolerance = 10.
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
#process.calibTreeMaker.OutputFile = 'Gamma_15_skim_hlt_Track.root'
#process.calibTreeMaker.OutputFile = 'DiJet_Track_2600_3000.root'
#process.calibTreeMaker.OutputFile = 'TriJet_Track.root'
process.calibTreeMaker.OutputFile = 'ZJet_Track.root'

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
process.calibTreeMaker.PhotonJet_Weight      = -1.
process.calibTreeMaker.PhotonJet_Weight_Tag  = 'genEventWeight'



process.calibTreeMaker.ZJetTreeName = 'ZJetTree'
process.calibTreeMaker.ZJetJets = 'zJetSample:LeadingJet'
process.calibTreeMaker.ZJetGenJets = 'zJetSample:LeadingGenJet'
process.calibTreeMaker.ZJetZs = 'zJetSample:LeadingZ'
process.calibTreeMaker.ZJetGenZs = 'zJetSample:LeadingGenZ'
process.calibTreeMaker.ZJetNonLeadingJetsPt = 'zJetSample:NonLeadingJetsPt'
process.calibTreeMaker.ZJetMet          = 'met'
process.calibTreeMaker.ZJetRecTracks    = 'generalTracks'
process.calibTreeMaker.ZJetRecMuons     = 'globalMuons'
process.calibTreeMaker.ZJetConeSize     = 0.5
process.calibTreeMaker.ZJet_Weight      = -1.
process.calibTreeMaker.ZJet_Weight_Tag  = 'genEventWeight'



process.calibTreeMaker.DiJetTreeName     ='DiJetTree'
process.calibTreeMaker.TriJetTreeName    ='TriJetTree'
process.calibTreeMaker.NJet_Jets         = 'sisCone5CaloJets'
#prosess.calibTreeMaker.JetJetGenJets      = iterativeCone5GenJetsPt10
process.calibTreeMaker.NJet_GenJets      = 'sisCone5GenJets'
process.calibTreeMaker.NJet_MET          = 'met'
process.calibTreeMaker.NJetRecTracks     = 'generalTracks'
process.calibTreeMaker.NJetRecMuons      = 'globalMuons'
process.calibTreeMaker.NJetConeSize      = 0.5
process.calibTreeMaker.NJet_Weight_Tag   = 'genEventWeight'
process.calibTreeMaker.NJet_Weight       = -1.


process.calibTreeMaker.TopTreeName     ='TopTree'


process.calibTreeMaker.WritePhotonJetTree = False#True
process.calibTreeMaker.WriteDiJetTree    = False
process.calibTreeMaker.WriteTriJetTree   = False
process.calibTreeMaker.WriteZJetTree   = True #False


#process.p1 = cms.Path(process.dump)
#process.p1 = cms.Path(process.midPointCone5CaloJets*process.dump)
#process.p2 = cms.Path(process.midPointCone5CaloJets*process.makePhotonJetTree)
#process.p2 = cms.Path(process.makePhotonJetTree)
#process.p2 = cms.Path(process.makeDiJetTree)
#process.p2 = cms.Path(process.makeTriJetTree)
process.p2 = cms.Path(process.makeZJetTree)
process.schedule = cms.Schedule(process.p2)
