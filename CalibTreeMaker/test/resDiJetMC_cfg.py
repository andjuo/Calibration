# $Id: $
#
# Write Dijet-Trees in data

import FWCore.ParameterSet.Config as cms
process = cms.Process("Calib")

from Calibration.CalibTreeMaker.runTreeMakerDiJets_cff import runTreeMakerDiJets
runTreeMakerDiJets(
    process,
    isData=False,
    globalTag="START53_V23::All",
    hltSelection=[],
    reportEveryEvt=5000,
    testFileName="/store/mc/Summer12_DR53X/QCD_Pt-15to3000_TuneZ2star_Flat_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/0000/007D8FA7-B7D3-E111-B904-003048F0E1B0.root",
    numProcessedEvt=100
    )
