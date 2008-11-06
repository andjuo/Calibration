import FWCore.ParameterSet.Config as cms

process = cms.Process("Calib")

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
      '/store/relval/CMSSW_2_1_9/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/04419036-F385-DD11-B3A7-001617C3B6E8.root',
      '/store/relval/CMSSW_2_1_9/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/0A28F869-F285-DD11-AF3C-001617DBD5B2.root',
      '/store/relval/CMSSW_2_1_9/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/162C4B5E-F585-DD11-872A-001617C3B64C.root',
      '/store/relval/CMSSW_2_1_9/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/205E6CE3-F485-DD11-9D53-001617C3B76A.root',
      '/store/relval/CMSSW_2_1_9/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/562BAFA1-F585-DD11-B931-001617DBD224.root',
      '/store/relval/CMSSW_2_1_9/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/565AFE10-EF85-DD11-8353-000423D6B42C.root',
      '/store/relval/CMSSW_2_1_9/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/5C66302A-F185-DD11-81D3-000423D98834.root',
      '/store/relval/CMSSW_2_1_9/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/66F60641-F685-DD11-A493-000423D987FC.root',
      '/store/relval/CMSSW_2_1_9/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/6E6A6E2D-F485-DD11-B707-001617DBD472.root',
      '/store/relval/CMSSW_2_1_9/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/70191C8D-F485-DD11-8280-001617E30D06.root',
      '/store/relval/CMSSW_2_1_9/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/9A204B65-F385-DD11-9CF1-000423D98B6C.root',
      '/store/relval/CMSSW_2_1_9/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/A6E8BAB0-F085-DD11-9AB1-000423D986C4.root',
      '/store/relval/CMSSW_2_1_9/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/B4D8FA14-F485-DD11-A41D-001617C3B76A.root',
      '/store/relval/CMSSW_2_1_9/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/B6CA9FAB-F185-DD11-B66B-001617E30D0A.root',
      '/store/relval/CMSSW_2_1_9/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/D8DAE3BF-F385-DD11-9C8E-001617C3B65A.root',
      '/store/relval/CMSSW_2_1_9/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0000/EA02E08F-F285-DD11-8AF3-000423D9870C.root',
      '/store/relval/CMSSW_2_1_9/RelValZEE/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v2/0001/6E9B44E2-0487-DD11-BFA7-001617C3B78C.root'
    )
                            )

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1) )

process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FakeConditions_cff")
process.load("Geometry.CommonDetUnit.bareGlobalTrackingGeometry_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagator_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAny_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAlong_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorOpposite_cfi")
process.load("TrackingTools.TrackAssociator.DetIdAssociatorESProducer_cff")

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
process.calibTreeMaker.OutputFile = 'GammaJet_Zee.root'
process.calibTreeMaker.PhotonJetTreeName = 'GammaJetTree'
process.calibTreeMaker.PhotonJetJets = 'photonJetSample:LeadingJet'
process.calibTreeMaker.PhotonJetGenJets = 'photonJetSample:LeadingGenJet'
process.calibTreeMaker.PhotonJetPhotons = 'photonJetSample:LeadingPhoton'
process.calibTreeMaker.PhotonJetGenPhotons = 'photonJetSample:LeadingGenPhoton'
process.calibTreeMaker.PhotonJetNonLeadingJetsPt = 'photonJetSample:NonLeadingJetsPt'
process.calibTreeMaker.PhotonJetMet = 'met'
process.calibTreeMaker.PhotonJetRecTracks = 'generalTracks'
process.calibTreeMaker.PhotonJetRecMuons = 'globalMuons'
process.calibTreeMaker.PhotonJetConeSize = 0.5
process.calibTreeMaker.WritePhotonJetTree = True

#process.p1 = cms.Path(process.dump)
#process.p1 = cms.Path(process.midPointCone5CaloJets*process.dump)
#process.p2 = cms.Path(process.midPointCone5CaloJets*process.makePhotonJetTree)
process.p2 = cms.Path(process.makePhotonJetTree)
process.schedule = cms.Schedule(process.p2)
