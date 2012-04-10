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

process.GlobalTag.globaltag = 'GR_R_44_V15::All' 	

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(	
	
'/store/data/Run2011A/Photon/AOD/PromptReco-v6/000/172/620/229AD050-1BC0-E011-88CB-001D09F251FE.root'

            )
                            )

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1) )

process.options = cms.untracked.PSet(
    SkipEvent = cms.untracked.vstring('ProductNotFound'),
    Rethrow = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(True)
)

# HLT
process.load('HLTrigger.HLTfilters.hltHighLevel_cfi')
process.hltHighLevel.HLTPaths = cms.vstring('HLT_Photon20_CaloIdVL_IsoL_v*','HLT_Photon30_CaloIdVL_IsoL_v*','HLT_Photon50_CaloIdVL_IsoL_v*','HLT_Photon75_CaloIdVL_IsoL_v*','HLT_Photon90_CaloIdVL_IsoL_v*')
process.hltHighLevel.andOr = cms.bool(True)
process.hltHighLevel.throw = cms.bool(False)


# vertex filter
process.vertexFilter = cms.EDFilter("VertexSelector",
                                  	src = cms.InputTag("offlinePrimaryVertices"),
                                  	cut = cms.string("!isFake && ndof > 4 && abs(z) <= 24 && position.Rho <= 2"),
                                  	filter = cms.bool(True),
                                   ) 
## monster event filter
process.trackFilter = cms.EDFilter("FilterOutScraping",
                                   applyfilter = cms.untracked.bool(True),
                                   debugOn     = cms.untracked.bool(False),
                                   numtrack    = cms.untracked.uint32(10),
                                   thresh      = cms.untracked.double(0.25)
                                   ) 



## sequence with filters
process.filterSequence = cms.Sequence(  process.hltHighLevel *
                                        process.vertexFilter *
					process.trackFilter
                                     ) 

process.load("Calibration.CalibTreeMaker.CalibTreeMaker_cff")

process.calibTreeMakerCaloData.TreeName          = "GammaJetTree"
process.calibTreeMakerCaloData.WritePhotons = True
process.calibTreeMakerPFData.TreeName          = "GammaJetTree"
process.calibTreeMakerPFData.WritePhotons = True
process.calibTreeMakerJPTData.TreeName          = "GammaJetTree"
process.calibTreeMakerJPTData.WritePhotons = True
process.calibTreeMakerAK7CaloData.TreeName          = "GammaJetTree"
process.calibTreeMakerAK7CaloData.WritePhotons = True
process.calibTreeMakerAK7PFData.TreeName          = "GammaJetTree"
process.calibTreeMakerAK7PFData.WritePhotons = True
process.calibTreeMakerAK5FastCaloData.TreeName          = "GammaJetTree"
process.calibTreeMakerAK5FastCaloData.WritePhotons = True
process.calibTreeMakerAK5FastPFData.TreeName          = "GammaJetTree"
process.calibTreeMakerAK5FastPFData.WritePhotons = True
process.calibTreeMakerAK5PFCHSData.TreeName          = "GammaJetTree"
process.calibTreeMakerAK5PFCHSData.WritePhotons = True

process.dump = cms.EDAnalyzer("EventContentAnalyzer")

process.pDump = cms.Path( process.dump )
process.pData = cms.Path(process.filterSequence * process.calibjets * process.ak5PFJetsBtag * process.calibTreeMakerAK5FastPFData * process.ak5PFCHSJetsBtag * process.calibTreeMakerAK5PFCHSData)
process.schedule = cms.Schedule(process.pData)




