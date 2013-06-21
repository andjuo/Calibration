# $Id: $
#
# Write Dijet-Trees in data

import FWCore.ParameterSet.Config as cms
process = cms.Process("Calib")

from Calibration.CalibTreeMaker.runTreeMakerDiJets_cff import runTreeMakerDiJets
runTreeMakerDiJets(
    process,
    isData=True,
    globalTag="FT_53_V21_AN4::All",
    hltSelection=[
    'HLT_DiPFJetAve40_v*',
    'HLT_DiPFJetAve80_v*',
    'HLT_DiPFJetAve140_v*',
    'HLT_DiPFJetAve200_v*',
    'HLT_DiPFJetAve260_v*',
    'HLT_DiPFJetAve320_v*',
    'HLT_DiPFJetAve400_v*',
    ],
    reportEveryEvt=5000,
    testFileName="/store/data/Run2012D/JetHT/AOD/22Jan2013-v1/10002/FC08B914-A297-E211-A946-001EC9D7DF62.root",
    numProcessedEvt=100
    )
