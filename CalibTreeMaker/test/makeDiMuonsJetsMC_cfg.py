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

#process.AdaptorConfig = cms.Service("AdaptorConfig",
#                                    #tempDir=cms.untracked.string(""),
#                                    cacheHint=cms.untracked.string("lazy-download"),
#                                    #cacheHint=cms.untracked.string("storage-only"),             
#                                    readHint=cms.untracked.string("auto-detect") )


process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
        '/store/mc/Summer11/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/GEN-SIM-RECO/HCal_PU_S4_START42_V11-v1/0000/02CCDD0A-E595-E011-BA05-0025901D4AF0.root' 
            )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(5) )

process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(True)
)

process.dump = cms.EDAnalyzer("EventContentAnalyzer")

# Jet Energy Corrections
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')

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

process.load("Calibration.CalibTreeMaker.calibjets_cff")

process.pDump = cms.Path( process.dump )

process.pMC = cms.Path( #process.dump *
                        #process.recoJPTJets *   
                        process.calibjets *
                        process.calibTreeMakersMC 
                        )

process.schedule = cms.Schedule(process.pMC)
