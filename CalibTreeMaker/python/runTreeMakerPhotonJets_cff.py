# $Id: $

import FWCore.ParameterSet.Config as cms

from Calibration.CalibTreeMaker.runTreeMaker_cff import runTreeMaker
def runTreeMakerPhotonJets(
    process,
    isData=True,
    globalTag="",
    hltSelection=[],
    reportEveryEvt=5000,
    testFileName="",
    numProcessedEvt=100
    ):
    
    runTreeMaker(
        process=process,
        isData=isData,
        globalTag=globalTag,
        hltSelection=hltSelection,
        reportEveryEvt=reportEveryEvt,
        testFileName=testFileName,
        numProcessedEvt=numProcessedEvt,
        treeName="GammaJetTree",
        writePhotons=True
        )

