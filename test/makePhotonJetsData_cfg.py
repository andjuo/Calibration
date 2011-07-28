import FWCore.ParameterSet.Config as cms
import os

process = cms.Process("Calib")


process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.load('Configuration/StandardSequences/Services_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.GlobalTag.globaltag = 'GR_R_42_V19::All'

process.MessageLogger.cerr.threshold             = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 5000


process.AdaptorConfig = cms.Service("AdaptorConfig",
                                    #tempDir=cms.untracked.string(""),
                                    cacheHint=cms.untracked.string("lazy-download"),
                                    #cacheHint=cms.untracked.string("storage-only"),             
                                    readHint=cms.untracked.string("auto-detect") )


process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
        '/store/data/Run2011A/Photon/AOD/PromptReco-v4/000/165/364/981DE32D-A584-E011-A16A-001D09F2305C.root'
            )
                            )

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000) )

process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(True)
)


# Trigger
process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff')
process.load('HLTrigger/HLTfilters/hltLevel1GTSeed_cfi')
process.hltLevel1GTSeed.L1TechTriggerSeeding = cms.bool(True)
process.hltLevel1GTSeed.L1SeedsLogicalExpression = cms.string('0 AND (40 OR 41) AND NOT (36 OR 37 OR 38 OR 39) AND NOT ((42 AND NOT 43) OR (43 AND NOT 42))')

# HLT
process.load('HLTrigger.HLTfilters.hltHighLevel_cfi')
#process.hltHighLevel.HLTPaths = ('HLT_DiJetAve15U','HLT_DiJetAve30U','HLT_DiJetAve50U','HLT_DiJetAve70U','HLT_DiJetAve100U','HLT_DiJetAve140U','HLT_DiJetAve15U_v*','HLT_DiJetAve30U_v*','HLT_DiJetAve50U_v*','HLT_DiJetAve70U_v*','HLT_DiJetAve100U_v*','HLT_DiJetAve140U_v*','HLT_DiJetAve180U_v*','HLT_DiJetAve300U_v*')
#process.hltHighLevel.HLTPaths = cms.vstring('HLT_DiJetAve30U')
process.hltHighLevel.HLTPaths = cms.vstring('HLT_Photon20_CaloIdVL_IsoL_v*','HLT_Photon30_CaloIdVL_IsoL_v*','HLT_Photon50_CaloIdVL_IsoL_v*','HLT_Photon75_CaloIdVL_IsoL_v*','HLT_Photon90_CaloIdVL_IsoL_v*')
process.hltHighLevel.andOr = cms.bool(True)
process.hltHighLevel.throw = cms.bool(False)

# Vertex filter
process.primaryVertexFilter = cms.EDFilter("VertexSelector",
   src = cms.InputTag("offlinePrimaryVertices"),
   cut = cms.string("!isFake && ndof > 4 && abs(z) <= 24 && position.Rho <= 2"), # tracksSize() > 3 for the older cut
   filter = cms.bool(True),   # otherwise it won't filter the events, just produce an empty vertex collection.
)

# Monster Event filter
process.noscraping = cms.EDFilter("FilterOutScraping",
applyfilter = cms.untracked.bool(True),
debugOn = cms.untracked.bool(False),
numtrack = cms.untracked.uint32(10),
thresh = cms.untracked.double(0.25)
)

process.dump = cms.EDAnalyzer("EventContentAnalyzer")



# Jet Energy Corrections
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')

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

process.pDump = cms.Path( process.dump )

process.load("Calibration.CalibTreeMaker.calibjets_cff")

process.pData = cms.Path( #process.hltLevel1GTSeed*
                          process.hltHighLevel *
                          process.primaryVertexFilter
                          #process.genPhotonCandidates *
                          #process.goodGenPhotons
                          #* process.noscraping
                          #* process.dump
                          #* process.ZSPJetCorrectionsAntiKt5
                          #* process.ZSPrecoJetAssociationsAntiKt5 
                          * process.calibjets
                          * process.calibTreeMakersData
                          )

process.schedule = cms.Schedule(process.pData)
