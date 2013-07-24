import FWCore.ParameterSet.Config as cms

process = cms.Process("Calib")


process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration/StandardSequences/Services_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

#process.GlobalTag.globaltag = 'GR_R_53_V19::All'
process.GlobalTag.globaltag = 'FT_53_V21_AN4::All'
#process.GlobalTag.globaltag = 'START53_V25::All'


process.MessageLogger.cerr.threshold             = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 5000


process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    #'/store/data/Run2012B/JetMon/AOD/13Jul2012-v1/00000/8CA83B67-75E8-E111-ACD2-003048678D6C.root',
    #'/store/data/Run2012B/JetMon/AOD/13Jul2012-v1/00000/88A84556-58E8-E111-9271-0026189438D7.root',
    #'/store/data/Run2012B/JetMon/AOD/13Jul2012-v1/00000/525C8D19-89E8-E111-B918-00261894392B.root',
    #'/store/data/Run2012B/JetMon/AOD/13Jul2012-v1/00000/22881C3C-72E8-E111-9742-002618FDA279.root',
    #'/store/data/Run2012B/JetMon/AOD/13Jul2012-v1/00000/F48BA9D6-79E8-E111-964F-00304867BFA8.root',
    #'/store/data/Run2012B/JetMon/AOD/13Jul2012-v1/00000/2C42C1D8-94E8-E111-8CD8-002618943982.root'
    #'/store/data/Run2012C/JetMon/AOD/PromptReco-v2/000/198/969/E4D890EB-E9D0-E111-912C-5404A638868F.root'
    #'file:/scratch/hh/dust/naf/cms/user/eschliec/7200FA02-CC85-E211-9966-001E4F3F165E.root',
    '/store/data/Run2012B/MultiJet1Parked/AOD/05Nov2012-v2/10000/0003D331-5C49-E211-8210-00259020081C.root',
    #'/store/data/Run2012B/MultiJet1Parked/AOD/05Nov2012-v2/10000/046B7C65-4A49-E211-9FED-001E67397F3F.root',
    #'/store/data/Run2012B/MultiJet1Parked/AOD/05Nov2012-v2/10000/08ED7F22-3B49-E211-86E9-001E67398CE1.root',
    #'/store/data/Run2012B/MultiJet1Parked/AOD/05Nov2012-v2/10000/002287AD-5849-E211-AAF0-002481E14E82.root',
    #'/store/data/Run2012B/MultiJet1Parked/AOD/05Nov2012-v2/10000/04D0236B-4C49-E211-9395-001E67396707.root',
    #'/store/data/Run2012B/MultiJet1Parked/AOD/05Nov2012-v2/10000/0A0219D3-3949-E211-B529-001E67397238.root',
    #'/store/data/Run2012B/MultiJet1Parked/AOD/05Nov2012-v2/10000/00322AB0-5C49-E211-A000-003048D4777A.root',
    #'/store/data/Run2012B/MultiJet1Parked/AOD/05Nov2012-v2/10000/062269EE-4D49-E211-84CE-001E67397431.root',
    #'/store/data/Run2012B/MultiJet1Parked/AOD/05Nov2012-v2/10000/0A500056-FD63-E211-BE51-0025B3E05CDA.root',
    #'/store/data/Run2012B/MultiJet1Parked/AOD/05Nov2012-v2/10000/0080A449-5A49-E211-BEB1-001E67397616.root',
    #'/store/data/Run2012B/MultiJet1Parked/AOD/05Nov2012-v2/10000/0665C07A-5949-E211-9803-0025B3E05D8C.root',
    #'/store/data/Run2012B/MultiJet1Parked/AOD/05Nov2012-v2/10000/0A988582-5A49-E211-BE84-001E67397747.root',
    #'/store/data/Run2012B/MultiJet1Parked/AOD/05Nov2012-v2/10000/009B4B34-5D49-E211-89C7-001E67396577.root',
    #'/store/data/Run2012B/MultiJet1Parked/AOD/05Nov2012-v2/10000/0679598A-E163-E211-ABD8-003048D4604C.root',
    #'/store/data/Run2012B/MultiJet1Parked/AOD/05Nov2012-v2/10000/0AC3FECB-4449-E211-80CF-001E67397C33.root',
    #'/store/data/Run2012B/MultiJet1Parked/AOD/05Nov2012-v2/10000/00C29E00-6749-E211-A4C9-001E673968A6.root',
    #'/store/data/Run2012B/MultiJet1Parked/AOD/05Nov2012-v2/10000/0693612A-5D49-E211-BD70-001E67396D5B.root',
    #'/store/data/Run2012B/MultiJet1Parked/AOD/05Nov2012-v2/10000/0AD674B0-5949-E211-A07B-001E67398B29.root',
    #'/store/data/Run2012B/MultiJet1Parked/AOD/05Nov2012-v2/10000/0250D482-3849-E211-89B1-001E67396D5B.root',
    #'/store/data/Run2012B/MultiJet1Parked/AOD/05Nov2012-v2/10000/06BB0427-5949-E211-B58E-001E67398D72.root',
    #'/store/data/Run2012B/MultiJet1Parked/AOD/05Nov2012-v2/10000/0C04193F-4749-E211-BDA7-001E6739834A.root',
    #'/store/data/Run2012B/MultiJet1Parked/AOD/05Nov2012-v2/10000/0292A42A-5B49-E211-9F8F-001E6739830E.root'
    )
                            #,eventsToProcess =  cms.untracked.VEventRange('163252:26075640','163255:546909755')
                            #,eventsToProcess =  cms.untracked.VEventRange('198969:198705079')
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1) )

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
process.hltHighLevel.HLTPaths = cms.vstring('HLT_DiPFJetAve*','HLT_QuadJet*','HLT_SixJet*','HLT_Mu*','HLT_IsoMu*')
#process.hltHighLevel.HLTPaths = cms.vstring('*')
process.hltHighLevel.andOr = cms.bool(True)
process.hltHighLevel.throw = cms.bool(False)


process.dump = cms.EDAnalyzer("EventContentAnalyzer")


# Jet Energy Corrections
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')

process.load("Calibration.CalibTreeMaker.CalibTreeMaker_cff")

process.pDump = cms.Path( process.dump )

process.load("Calibration.CalibTreeMaker.calibjets_cff")
process.load("Calibration.CalibTreeMaker.cleaningSequences_cff")

# set min jets to select and max jets to save
process.calibTreeMakerAK5PFCHSTopData.NJet_MinNumJets = 4
process.calibTreeMakerAK5PFCHSTopData.NJet_MaxNumJets = 10
process.calibTreeMakerAK5PFCHSData   .NJet_MinNumJets = 4
process.calibTreeMakerAK5PFCHSData   .NJet_MaxNumJets = 10
process.calibTreeMakerAK5FastPFData  .NJet_MinNumJets = 4
process.calibTreeMakerAK5FastPFData  .NJet_MaxNumJets = 10
process.calibTreeMakerAK5FastCaloData.NJet_MinNumJets = 4
process.calibTreeMakerAK5FastCaloData.NJet_MaxNumJets = 10


## reduce size of output by removing collections that are not needed
process.calibTreeMakersData.remove(process.calibTreeMakerJPTData)
process.calibTreeMakersData.remove(process.calibTreeMakerAK7CaloData)
process.calibTreeMakersData.remove(process.calibTreeMakerAK7PFData)
process.calibTreeMakersData.remove(process.calibTreeMakerAK7PFCHSData)
process.calibTreeMakersData.remove(process.calibTreeMakerCaloData)
process.calibTreeMakersData.remove(process.calibTreeMakerPFData)

process.calibjets.remove(process.ak7CaloJets)
process.calibjets.remove(process.ak7PFJets)
process.calibjets.remove(process.ak7PFCHSJets)

process.calibTreeMakersData.remove(process.ak5JPTJetsBtag)
process.calibTreeMakersData.remove(process.ak7CaloJetsBtag)
process.calibTreeMakersData.remove(process.ak7PFJetsBtag)
process.calibTreeMakersData.remove(process.ak7PFCHSJetsBtag)

## remove unused jet collections
process.calibjets.remove(process.kt4CaloJets)
process.calibjets.remove(process.kt6CaloJetsCentral)
process.calibjets.remove(process.iterativeCone5CaloJets)
process.calibjets.remove(process.kt4PFJets)
process.calibjets.remove(process.iterativeCone5PFJets)

process.calibjets.remove(process.fixedGridRhoAll)
process.calibjets.remove(process.fixedGridRhoFastjetAll)

process.pData = cms.Path( #process.hltLevel1GTSeed*
                          process.hltHighLevel*
                          process.stdCleaningSequence
                          #* process.noscraping
                          #* process.dump
                          * process.calibjets
                          * process.softElectronCands
                          * process.calibTreeMakersData
                          )

process.schedule = cms.Schedule(process.pData)
