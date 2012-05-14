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


process.GlobalTag.globaltag = 'START52_V9::All'


process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold             = 'ERROR'
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
    '/store/mc/Summer12/QCD_Pt-15to3000_TuneZ2star_Flat_8TeV_pythia6/AODSIM/PU_S7_START52_V9-v5/0000/780ECB4C-E598-E111-93C5-003048C68F6A.root'
            )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1) )

process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(True),
    useData = cms.untracked.bool(False)
)

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

process.load("Calibration.CalibTreeMaker.calibjetsnew_cff")

#
process.AK5PFCHSNewJetPartonMatching = process.PFJetPartonMatching.clone( 
    jets = 'ak5PFCHSNewJets' 
)

process.calibTreeMakerAK5PFCHSNew = process.calibTreeMakerPF.clone(
    OutputFile = 'ak5PFCHSNew.root',
    NJet_Jets  = 'ak5PFCHSNewJets',
    NJet_PartonMatch = 'AK5PFCHSNewJetPartonMatching',
    NJet_Rho         = cms.InputTag('kt6PFJets','rho'),    
    NJetSecondVx = '',
    NJet_L1JetCorrector = 'ak5PFL1Fastjet',
    NJet_L1L2L3JetCorrector = 'ak5PFL1FastL2L3',
    NJet_L1L2L3L4JWJetCorrector = 'ak5PFL1FastL2L3'
)

process.pMC = cms.Path( #process.dump *
                        #process.recoJPTJets * 
                        process.calibjetsnew *
                        process.calibTreeMakersMC *
                        process.AK5PFCHSNewJetPartonMatching *
                        process.calibTreeMakerAK5PFCHSNew
                        )

process.schedule = cms.Schedule(process.pMC)
