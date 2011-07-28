import FWCore.ParameterSet.Config as cms
import os

process = cms.Process("Calib")
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.GlobalTag.globaltag = 'START42_V13::All'

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold             = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 5000

process.AdaptorConfig = cms.Service("AdaptorConfig",
                                    #tempDir=cms.untracked.string(""),
                                    cacheHint=cms.untracked.string("lazy-download"),
                                    #cacheHint=cms.untracked.string("storage-only"),             
                                    readHint=cms.untracked.string("auto-detect") )


process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
        '/store/mc/Summer11/QCD_Pt-15to3000_TuneD6T_Flat_7TeV-pythia6/AODSIM/PU_S3_START42_V11-v1/0000/6AD764B7-D878-E011-9AB5-E41F131817C4.root' 
            )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(5) )

process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(True)
)

# Vertex filter
process.primaryVertexFilter = cms.EDFilter("VertexSelector",
   src = cms.InputTag("offlinePrimaryVertices"),
   cut = cms.string("!isFake && ndof > 4 && abs(z) <= 15 && position.Rho <= 2"), # tracksSize() > 3 for the older cut
   filter = cms.bool(True),   # otherwise it won't filter the events, just produce an empty vertex collection.
)

process.dump = cms.EDAnalyzer("EventContentAnalyzer")

# Jet Energy Corrections
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')

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

process.load("Calibration.CalibTreeMaker.calibjets_cff")

process.pDump = cms.Path( process.dump )

process.pMC = cms.Path( #process.dump *
                        #process.recoJPTJets *   
                        process.calibjets *
                        process.calibTreeMakersMC                       
                        )

process.schedule = cms.Schedule(process.pMC)
