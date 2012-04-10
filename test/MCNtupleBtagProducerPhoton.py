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
	
'/store/mc/Summer11/GJets_TuneZ2_40_HT_100_7TeV-madgraph/AODSIM/PU_S4_START42_V11-v1/0000/7AC7AB41-4CCF-E011-9C40-003048678BB2.root '

            )
                            )

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10) )

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

process.calibTreeMakerCalo.TreeName          = "GammaJetTree"
process.calibTreeMakerCalo.WritePhotons = True
process.calibTreeMakerPF.TreeName          = "GammaJetTree"
process.calibTreeMakerPF.WritePhotons = True
process.calibTreeMakerJPT.TreeName          = "GammaJetTree"
process.calibTreeMakerJPT.WritePhotons = True
process.calibTreeMakerAK7Calo.TreeName          = "GammaJetTree"
process.calibTreeMakerAK7Calo.WritePhotons = True
process.calibTreeMakerAK7PF.TreeName          = "GammaJetTree"
process.calibTreeMakerAK7PF.WritePhotons = True
process.calibTreeMakerAK5FastCalo.TreeName          = "GammaJetTree"
process.calibTreeMakerAK5FastCalo.WritePhotons = True
process.calibTreeMakerAK5FastPF.TreeName          = "GammaJetTree"
process.calibTreeMakerAK5FastPF.WritePhotons = True
process.calibTreeMakerAK5PFCHS.TreeName          = "GammaJetTree"
process.calibTreeMakerAK5PFCHS.WritePhotons = True

process.dump = cms.EDAnalyzer("EventContentAnalyzer")

process.pDump = cms.Path( process.dump )
process.pData = cms.Path(process.calibjets * process.genPhotons * process.goodGenPhotons * process.myPartons * process.PFJetPartonMatching * process.ak5PFJetsBtag * process.calibTreeMakerAK5FastPF * process.AK5PFCHSJetPartonMatching * process.ak5PFCHSJetsBtag * process.calibTreeMakerAK5PFCHS)
process.schedule = cms.Schedule(process.pData)




