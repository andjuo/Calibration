import FWCore.ParameterSet.Config as cms
import os
import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Types as CfgTypes


process = cms.Process("Calib")
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.load('Configuration/StandardSequences/GeometryDB_cff')
process.load('Configuration/StandardSequences/Services_cff')
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold             = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 500
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')
process.load('RecoBTag/Configuration/RecoBTag_cff')

process.GlobalTag.globaltag = 'FT_P_V42_AN3::All' 	

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(	
     '/store/data/Run2012D/SinglePhoton/AOD/PromptReco-v1/000/206/446/0C9FF335-A925-E211-9D65-001D09F2932B.root'
  #  '/store/data/Run2012C/SinglePhoton/AOD/PromptReco-v2/000/203/754/440A9894-320A-E211-9AC4-001D09F252E9.root'
  #   '/store/data/Run2012C/SinglePhoton/AOD/PromptReco-v2/000/203/742/E2D4A967-6C0A-E211-A7F8-001D09F2B30B.root'
            )
                            )

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(2000) )  # number of events 

process.options = cms.untracked.PSet(
    SkipEvent = cms.untracked.vstring('ProductNotFound'),
    Rethrow = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(True)
)

# HLT
process.load('HLTrigger.HLTfilters.hltHighLevel_cfi')
process.hltHighLevel.HLTPaths = cms.vstring('HLT_Photon20_CaloIdVL_IsoL_v*','HLT_Photon30_CaloIdVL_IsoL_v*','HLT_Photon50_CaloIdVL_IsoL_v*','HLT_Photon75_CaloIdVL_IsoL_v*','HLT_Photon90_CaloIdVL_IsoL_v*','HLT_Photon135_v*','HLT_Photon150_v*','HLT_Photon160_v*')
process.hltHighLevel.andOr = cms.bool(True) 
process.hltHighLevel.throw = cms.bool(False)

#Filter
process.load('Calibration.CalibTreeMaker.cleaningSequences_cff')

## sequence with filters
process.filterSequence = cms.Sequence(  process.hltHighLevel *
					process.stdCleaningSequence
                                        )

from RecoMET.METFilters.multiEventFilter_cfi import multiEventFilter
process.HCALLaserEvtFilterList2012 = multiEventFilter.clone(
    file        = cms.FileInPath('Calibration/CalibTreeMaker/data/HCAL_laser_event_list.txt'),
    taggingMode = cms.bool(False)
    )
process.filterSequence += process.HCALLaserEvtFilterList2012

process.load("Calibration.CalibTreeMaker.CalibTreeMaker_cff")

process.calibTreeMakerAK5FastPFData.ECALDeadCellBEFilterModuleName = cms.InputTag("EcalDeadCellBoundaryEnergyFilter")
process.calibTreeMakerAK5FastPFData.ECALDeadCellTPFilterModuleName = cms.InputTag("EcalDeadCellTriggerPrimitiveFilter")
process.calibTreeMakerAK5FastPFData.WritePhotons = True
process.calibTreeMakerAK5FastPFData.TreeName = "GammaJetTree"
process.calibTreeMakerAK5PFCHSData.ECALDeadCellBEFilterModuleName = cms.InputTag("EcalDeadCellBoundaryEnergyFilter")
process.calibTreeMakerAK5PFCHSData.ECALDeadCellTPFilterModuleName = cms.InputTag("EcalDeadCellTriggerPrimitiveFilter")
process.calibTreeMakerAK5PFCHSData.WritePhotons = True
process.calibTreeMakerAK5PFCHSData.TreeName = "GammaJetTree"

process.calibTreeMakerAK7PFData.ECALDeadCellBEFilterModuleName = cms.InputTag("EcalDeadCellBoundaryEnergyFilter")
process.calibTreeMakerAK7PFData.ECALDeadCellTPFilterModuleName = cms.InputTag("EcalDeadCellTriggerPrimitiveFilter")
process.calibTreeMakerAK7PFData.WritePhotons = True
process.calibTreeMakerAK7PFData.TreeName = "GammaJetTree"
process.calibTreeMakerAK7PFCHSData.ECALDeadCellBEFilterModuleName = cms.InputTag("EcalDeadCellBoundaryEnergyFilter")
process.calibTreeMakerAK7PFCHSData.ECALDeadCellTPFilterModuleName = cms.InputTag("EcalDeadCellTriggerPrimitiveFilter")
process.calibTreeMakerAK7PFCHSData.WritePhotons = True
process.calibTreeMakerAK7PFCHSData.TreeName = "GammaJetTree"

process.dump = cms.EDAnalyzer("EventContentAnalyzer")

process.pDump = cms.Path(process.dump)
process.pData = cms.Path(process.filterSequence *
                         process.calibjets *
                         process.produceAllCaloMETCorrections *
                         process.produceAllPFMETCorrections *
			 process.produceAllPFCHSMETCorrections *
                         process.ak5PFJetsBtag *
                         process.calibTreeMakerAK5FastPFData *
                         process.ak5PFCHSJetsBtag *
                         process.calibTreeMakerAK5PFCHSData *
                         process.ak7PFJetsBtag *
                         process.calibTreeMakerAK7PFData *
                         process.ak7PFCHSJetsBtag *
                         process.calibTreeMakerAK7PFCHSData
                         )
process.schedule = cms.Schedule(process.pData)
