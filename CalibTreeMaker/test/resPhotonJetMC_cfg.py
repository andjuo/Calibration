# $Id: resPhotonJetMC_cfg.py,v 1.1 2012/05/10 12:09:40 mschrode Exp $
#
# Write Photon+Jet-Trees in data

import FWCore.ParameterSet.Config as cms
process = cms.Process("Calib")

from Calibration.CalibTreeMaker.runTreeMakerPhotonJets_cff import runTreeMakerPhotonJets
runTreeMakerPhotonJets(
    process,
    isData=False,
    globalTag="START52_V9::All", # Summer12
    hltSelection=[],
    reportEveryEvt=5000,
    testFileName="",
    numProcessedEvt=-100
    )
