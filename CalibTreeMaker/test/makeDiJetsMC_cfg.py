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


process.GlobalTag.globaltag = 'START53_V13::All'


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
#    '/store/mc/Summer11/QCD_Pt-15to3000_TuneD6T_Flat_7TeV-pythia6/AODSIM/PU_S3_START42_V11-v1/0000/6AD764B7-D878-E011-9AB5-E41F131817C4.root'
#    '/store/mc/Fall11/QCD_Pt-15to3000_Tune23_Flat_7TeV_herwigpp/AODSIM/PU_S6_START44_V9B-v1/0000/BA0F5C39-3B41-E111-9960-002481E0E912.root'
#    '/store/mc/Fall11/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/AODSIM/PU_S6_START44_V9B-v1/0000/4A9F238C-CB3F-E111-ADAF-003048678B76.root'
#    '/store/mc/Summer12/QCD_Pt-15to3000_TuneZ2star_Flat_8TeV_pythia6/AODSIM/PU_S7_START52_V5-v1/0000/104B87EF-927B-E111-9E8E-00266CFFA204.root'
#    '/store/mc/Summer12/QCD_Pt-15to3000_TuneZ2star_Flat_8TeV_pythia6/AODSIM/NoPU_START52_V5-v1/0000/46646478-797B-E111-91CB-0025901D490C.root'
    '/store/mc/Summer12_DR53X/QCD_Pt-15to3000_TuneZ2_Flat_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/0000/96C761A5-16CE-E111-8AED-003048D4DEAC.root'
            )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(50) )

process.options = cms.untracked.PSet(
#    Rethrow = cms.untracked.vstring('ProductNotFound'),
    SkipEvent = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(True),
    useData = cms.untracked.bool(False)
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


process.pDump = cms.Path( process.dump )

process.load("Calibration.CalibTreeMaker.CalibTreeMaker_cff")

process.load("Calibration.CalibTreeMaker.calibjets_cff")
process.load("Calibration.CalibTreeMaker.cleaningSequences_cff")

process.pMC = cms.Path( #process.dump *
                        #process.recoJPTJets * 
                        #process.hltHighLevel*
                        process.stdCleaningSequence *
                        process.calibjets *
                        process.calibTreeMakersMC
                        )

process.schedule = cms.Schedule(process.pMC)
