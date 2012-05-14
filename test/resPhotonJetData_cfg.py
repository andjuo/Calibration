# $Id: resPhotonJetData_cfg.py,v 1.1 2012/05/10 12:09:40 mschrode Exp $
#
# Write Photon+Jet-Trees in data

import FWCore.ParameterSet.Config as cms
process = cms.Process("Calib")

from Calibration.CalibTreeMaker.runTreeMakerPhotonJets_cff import runTreeMakerPhotonJets
runTreeMakerPhotonJets(
    process,
    isData=True,
    globalTag="GR_R_52_V7::All", # Run2012A-PromptReco-v1
    hltSelection=[
    'HLT_Photon20_CaloIdVL_IsoL_v*',
    'HLT_Photon30_CaloIdVL_IsoL_v*',
    'HLT_Photon50_CaloIdVL_IsoL_v*',
    'HLT_Photon75_CaloIdVL_IsoL_v*',
    'HLT_Photon90_CaloIdVL_IsoL_v*'
    'HLT_Photon135_v*',
    'HLT_Photon150_v*',
    'HLT_Photon160_v*',
    ],
    reportEveryEvt=5000,
    testFileName="/store/data/Run2012A/Photon/AOD/PromptReco-v1/000/193/575/E83BCD15-F499-E111-B51C-003048D2BC52.root",
    numProcessedEvt=-10
    )
