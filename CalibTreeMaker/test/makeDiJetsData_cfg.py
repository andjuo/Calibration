import FWCore.ParameterSet.Config as cms

process = cms.Process("Calib")


process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration/StandardSequences/Services_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

#process.GlobalTag.globaltag = 'GR_R_44_V14::All'
process.GlobalTag.globaltag = 'GR_R_53_V15::All'


process.MessageLogger.cerr.threshold             = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 5000


process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
#        '/store/data/Run2011B/Jet/AOD/19Nov2011-v1/0000/8EA85FAA-3A15-E111-B1B0-001D09690ABD.root'
#        '/store/data/Run2011A/Jet/AOD/May10ReReco-v1/0002/4C8D2782-F17B-E011-BFC0-0015178C49C0.root',
#        '/store/data/Run2011A/Jet/AOD/May10ReReco-v1/0000/862F1DCB-307C-E011-86F0-001D0967D55D.root'

#        '/store/data/Run2011A/Jet/RECO/PromptReco-v2/000/163/586/4C80085D-0A73-E011-93A4-0030487A17B8.root'
#        '/store/data/Run2011A/Jet/AOD/May10ReReco-v1/0000/8CE5E293-227C-E011-B58F-0024E86E8D4C.root'
#        '/store/data/Run2012A/Jet/AOD/PromptReco-v1/000/190/539/468F8B5C-BF81-E111-8567-001D09F24EE3.root'
#        '/store/data/Run2012A/Jet/AOD/PromptReco-v1/000/190/661/BC89ED8F-CC82-E111-B9E9-BCAEC5364C93.root'
        '/store/data/Run2012B/JetHT/AOD/PromptReco-v1/000/193/835/76E0EB2A-4F9C-E111-9294-003048F1C420.root'
        )
#May10 selection of events
#                            ,
#                            eventsToProcess =  cms.untracked.VEventRange('163252:26075640','163255:546909755')               
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(40) )

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
process.hltHighLevel.HLTPaths = cms.vstring('HLT_DiJetAve*','HLT_Jet*','HLT_DiPFJetAve*','HLT_PFJet*')
process.hltHighLevel.HLTPaths = cms.vstring('*')
process.hltHighLevel.andOr = cms.bool(True)
process.hltHighLevel.throw = cms.bool(False)



process.dump = cms.EDAnalyzer("EventContentAnalyzer")


# Jet Energy Corrections
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')


process.load("Calibration.CalibTreeMaker.CalibTreeMaker_cff")

process.pDump = cms.Path( process.dump )

process.load("Calibration.CalibTreeMaker.calibjets_cff")
process.load("Calibration.CalibTreeMaker.cleaningSequences_cff")

process.pData = cms.Path( #process.hltLevel1GTSeed*
                          process.hltHighLevel*
                          process.stdCleaningSequence
                          #* process.noscraping
                          #* process.dump
                          #* process.ZSPJetCorrectionsAntiKt5
                          #* process.ZSPrecoJetAssociationsAntiKt5
                          * process.calibjets
                          * process.calibTreeMakersData
                          )

process.schedule = cms.Schedule(process.pData)
