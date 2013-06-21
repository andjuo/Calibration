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
	
'/store/data/Run2011A/DoubleMu/AOD/PromptReco-v6/000/172/620/98AE6B89-17C0-E011-9376-001D09F2426D.root'

            )
                            )

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1) )

process.options = cms.untracked.PSet(
    SkipEvent = cms.untracked.vstring('ProductNotFound'),
    Rethrow = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(True)
)

process.load('HLTrigger.HLTfilters.hltHighLevel_cfi')
process.hltHighLevel.HLTPaths = cms.vstring('HLT_DoubleMu3_v*','HLT_DoubleMu5_v*','HLT_DoubleMu6_v*','HLT_DoubleMu7_v*','HLT_DoubleMu45_v*','HLT_DoubleMu5_IsoMu5_v*','HLT_Mu13_Mu8_v*','HLT_Mu17_Mu8_v*')
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

process.calibTreeMakerCaloData.TreeName          = "ZJetTree"
process.calibTreeMakerCaloData.WriteMuons = True
process.calibTreeMakerPFData.TreeName          = "ZJetTree"
process.calibTreeMakerPFData.WriteMuons = True
process.calibTreeMakerJPTData.TreeName          = "ZJetTree"
process.calibTreeMakerJPTData.WriteMuons = True
process.calibTreeMakerAK7CaloData.TreeName          = "ZJetTree"
process.calibTreeMakerAK7CaloData.WriteMuons = True
process.calibTreeMakerAK7PFData.TreeName          = "ZJetTree"
process.calibTreeMakerAK7PFData.WriteMuons = True
process.calibTreeMakerAK5FastCaloData.TreeName          = "ZJetTree"
process.calibTreeMakerAK5FastCaloData.WriteMuons = True
process.calibTreeMakerAK5FastPFData.TreeName          = "ZJetTree"
process.calibTreeMakerAK5FastPFData.WriteMuons = True
process.calibTreeMakerAK5PFCHSData.TreeName          = "ZJetTree"
process.calibTreeMakerAK5PFCHSData.WriteMuons = True


process.dump = cms.EDAnalyzer("EventContentAnalyzer")

process.pDump = cms.Path( process.dump )
process.pData = cms.Path(process.filterSequence * process.calibjets * process.ak5PFJetsBtag * process.calibTreeMakerAK5FastPFData * process.ak5PFCHSJetsBtag * process.calibTreeMakerAK5PFCHSData)
process.schedule = cms.Schedule(process.pData)




