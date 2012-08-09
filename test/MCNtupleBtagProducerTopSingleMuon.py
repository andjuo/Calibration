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

process.GlobalTag.globaltag = 'START44_V13::All' # 'START44_V13::All' # 'START42_V17::All' #'START42_V17::All' 'START52_V9::All'

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
                            '/store/mc/Fall11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S6-START44_V5-v1/0000/FEF6B833-C304-E111-B523-003048678FFA.root'
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
process.hltHighLevel.HLTPaths = cms.vstring('HLT_IsoMu24_eta2p1_v*')
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

for calibTreeMaker in (process.calibTreeMakerCalo,
                       process.calibTreeMakerPF,
                       process.calibTreeMakerJPT,
                       process.calibTreeMakerAK7Calo,
                       process.calibTreeMakerAK7PF,
                       process.calibTreeMakerAK5FastCalo,
                       process.calibTreeMakerAK5FastPF,
                       process.calibTreeMakerAK5PFCHS):
    calibTreeMaker.TreeName           = "TopTree"
    calibTreeMaker.WriteMuons         = True
    calibTreeMaker.NJet_MaxNumJets    = 10


process.dump = cms.EDAnalyzer("EventContentAnalyzer")

process.pDump = cms.Path( process.dump )
process.pData = cms.Path(process.hltHighLevel * process.calibjets * process.genMuons * process.goodGenMuons * process.myPartons * process.PFJetPartonMatching * process.ak5PFJetsBtag * process.calibTreeMakerAK5FastPF * process.AK5PFCHSJetPartonMatching * process.ak5PFCHSJetsBtag * process.calibTreeMakerAK5PFCHS)
process.schedule = cms.Schedule(process.pData)

process.pData.remove(process.kt4CaloJets)
process.pData.remove(process.kt6CaloJets)
process.pData.remove(process.iterativeCone5CaloJets)
process.pData.remove(process.ak5CaloJets)
process.pData.remove(process.ak7CaloJets)
process.pData.remove(process.kt4PFJets)
process.pData.remove(process.iterativeCone5PFJets)
process.pData.remove(process.ak7PFJets)

