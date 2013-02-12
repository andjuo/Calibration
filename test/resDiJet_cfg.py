# $Id: resDiJet_cfg.py,v 1.1 2013/02/08 13:50:18 kheine Exp $
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
    testFileName="/store/data/Run2012B/JetHT/AOD/13Jul2012-v1/00001/FCC8A4E0-BDD2-E111-9E79-003048FFCBFC.root",
    numProcessedEvt=100
    )



 
