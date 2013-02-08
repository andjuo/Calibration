# $Id: resPhotonJetData_cfg.py,v 1.4 2012/10/11 18:47:20 mschrode Exp $
#
# Write Kalibri DiJet Tree

# Read parameters
from RA2Classic.Utils.CommandLineParams import CommandLineParams
parameters = CommandLineParams()

globalTag = parameters.value("global_tag","")+"::All"
isData    = parameters.value("is_data",False)

print "***** SETUP ************************************"
print "  globalTag : "+globalTag
print "     isData : "+str(isData)
print "************************************************"



import FWCore.ParameterSet.Config as cms
process = cms.Process("Calib")

from Calibration.CalibTreeMaker.runTreeMaker_cff import runTreeMaker
runTreeMaker(
    process,
    isData=isData,
    globalTag=globalTag,
    treeName="DiJetTree",
    writePhotons=False,
    hltSelection=[],
    reportEveryEvt=5000,
    testFileName="file:///scratch/hh/dust/naf/cms/user/mschrode/SMS-AOD/store/mc/Summer12/SMS-T1tttt_Mgluino-350to2000_mLSP-0to1650_8TeV-Pythia6Z/AODSIM/START52_V9_FSIM-v3/0000/28988716-97EF-E111-A1A8-18A90570ABE0.root",
    numProcessedEvt=100
    )



 
