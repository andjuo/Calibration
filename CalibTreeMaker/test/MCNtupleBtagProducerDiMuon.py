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

process.GlobalTag.globaltag = 'FT_R_44_V11::All' #'START42_V15B::All' 	

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(	
	
	'/store/mc/Fall11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/C89C5B86-282B-E111-B8CB-90E6BA0D09AF.root'

            )
                            )

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100) )

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

process.calibTreeMakerCalo.TreeName          = "ZJetTree"
process.calibTreeMakerCalo.WriteMuons = True
process.calibTreeMakerPF.TreeName          = "ZJetTree"
process.calibTreeMakerPF.WriteMuons = True
process.calibTreeMakerJPT.TreeName          = "ZJetTree"
process.calibTreeMakerJPT.WriteMuons = True
process.calibTreeMakerAK7Calo.TreeName          = "ZJetTree"
process.calibTreeMakerAK7Calo.WriteMuons = True
process.calibTreeMakerAK7PF.TreeName          = "ZJetTree"
process.calibTreeMakerAK7PF.WriteMuons = True
process.calibTreeMakerAK5FastCalo.TreeName          = "ZJetTree"
process.calibTreeMakerAK5FastCalo.WriteMuons = True
process.calibTreeMakerAK5FastPF.TreeName          = "ZJetTree"
process.calibTreeMakerAK5FastPF.WriteMuons = True
process.calibTreeMakerAK5PFCHS.TreeName          = "ZJetTree"
process.calibTreeMakerAK5PFCHS.WriteMuons = True


process.dump = cms.EDAnalyzer("EventContentAnalyzer")

process.pDump = cms.Path( process.dump )
process.pData = cms.Path(process.calibjets * process.genMuons * process.goodGenMuons * process.myPartons * process.PFJetPartonMatching * process.ak5PFJetsBtag * process.calibTreeMakerAK5FastPF * process.AK5PFCHSJetPartonMatching * process.ak5PFCHSJetsBtag * process.calibTreeMakerAK5PFCHS)
process.schedule = cms.Schedule(process.pData)




