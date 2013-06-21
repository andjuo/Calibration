# $Id: resPhotonJetData_cfg.py,v 1.3 2012/05/24 11:41:17 mschrode Exp $
#
# Write Photon+Jet-Trees in data

import FWCore.ParameterSet.Config as cms
process = cms.Process("Calib")

from Calibration.CalibTreeMaker.runTreeMakerPhotonJets_cff import runTreeMakerPhotonJets
runTreeMakerPhotonJets(
    process,
    isData=True,
    globalTag="FT_53_V6_AN2::All", #Run2012A+B Jul13 ReReco
    hltSelection=[
    'HLT_Photon20_CaloIdVL_IsoL_v*',
    'HLT_Photon30_CaloIdVL_IsoL_v*',
    'HLT_Photon50_CaloIdVL_IsoL_v*',
    'HLT_Photon75_CaloIdVL_IsoL_v*',
    'HLT_Photon90_CaloIdVL_IsoL_v*',
    'HLT_Photon135_v*',
    'HLT_Photon150_v*',
    'HLT_Photon160_v*'
    ],
    reportEveryEvt=5000,
    testFileName="/store/data/Run2012A/Photon/AOD/13Jul2012-v1/00000/FCDDD6B1-30CF-E111-88D0-002481E75ED0.root",
    numProcessedEvt=100
    )
