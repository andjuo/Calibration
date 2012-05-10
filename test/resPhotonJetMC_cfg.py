# $Id: $
#
# Write Photon+Jet-Trees in data

import FWCore.ParameterSet.Config as cms
process = cms.Process("Calib")

from Calibration.CalibTreeMaker.runTreeMakerPhotonJets_cff import runTreeMakerPhotonJets
runTreeMakerPhotonJets(
    process,
    isData=False,
    globalTag="START44_V13::All", # Fall11
    hltSelection=[],
    reportEveryEvt=5000,
    testFileName="/store/mc/Fall11/G_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/AODSIM/PU_S6_START44_V9B-v1/0000/0087C9E4-C03F-E111-A9A5-00261894388A.root",
    numProcessedEvt=-100
    )
