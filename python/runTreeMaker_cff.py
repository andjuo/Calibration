# $Id: runTreeMaker_cff.py,v 1.4 2012/05/10 12:08:22 mschrode Exp $

import FWCore.ParameterSet.Config as cms
import os
import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Types as CfgTypes


def runTreeMaker(
    process,
    isData=True,
    globalTag="",
    treeName="",
    writePhotons=False,
    hltSelection=[],
    reportEveryEvt=5000,
    testFileName="",
    numProcessedEvt=100
    ):


    # ---- Configuration ----------------------------------------------------------
    process.load('Configuration.EventContent.EventContent_cff')
    process.load('Configuration.StandardSequences.MagneticField_38T_cff')
    process.load('Configuration.StandardSequences.Reconstruction_cff')
    process.load('Configuration.StandardSequences.EndOfProcess_cff')
    process.load('Configuration.StandardSequences.GeometryDB_cff')
    process.load('Configuration.StandardSequences.Services_cff')
    process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
    process.GlobalTag.globaltag = globalTag

    process.load('JetMETCorrections.Configuration.DefaultJEC_cff')
    process.load('RecoBTag.Configuration.RecoBTag_cff')

    process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
    process.load('SimGeneral.MixingModule.mixNoPU_cfi')



    # ---- Message logger ---------------------------------------------------------
    process.load('FWCore.MessageService.MessageLogger_cfi')
    process.load("FWCore.MessageLogger.MessageLogger_cfi")
    process.MessageLogger.cerr.threshold             = 'INFO'
    process.MessageLogger.cerr.FwkReport.reportEvery = reportEveryEvt



    # ---- Input ------------------------------------------------------------------
    process.source = cms.Source(
        "PoolSource",
        fileNames = cms.untracked.vstring(testFileName)	
        )
    process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(numProcessedEvt)
        )
    process.options = cms.untracked.PSet(
        SkipEvent = cms.untracked.vstring('ProductNotFound'),
        Rethrow = cms.untracked.vstring('ProductNotFound'),
        wantSummary = cms.untracked.bool(True)
        )


    
    # ---- Filters ----------------------------------------------------------------
    # HLT
    process.load('HLTrigger.HLTfilters.hltHighLevel_cfi')
    process.hltHighLevel.HLTPaths = cms.vstring(hltSelection)
    process.hltHighLevel.andOr = cms.bool(True)
    process.hltHighLevel.throw = cms.bool(False)

    # standard filter sequence + beamHalo filter
    process.load('Calibration.CalibTreeMaker.cleaningSequences_cff')

    # ECAL dead cell cleaning filter
    process.load('Calibration.CalibTreeMaker.ecalDeadCellFilter_cff')

    # sequence with filters
    process.filterSequence = cms.Sequence(
        process.hltHighLevel *
        process.standardCleaningPlusBeamHaloSequence *
        process.ecalDeadCellCleaningSequence
        )

    if not isData:
        process.filterSequence.remove( process.hltHighLevel )



    # ---- Tree makers ------------------------------------------------------------
    process.load("Calibration.CalibTreeMaker.CalibTreeMaker_cff")

    process.tmAK5CaloL1Offset = process.calibTreeMakerCaloData.clone(
        TreeName                       = treeName,
        WritePhotons                   = writePhotons,
        ECALDeadCellBEFilterModuleName = cms.InputTag("ecalDeadCellBEFilter"),
        ECALDeadCellTPFilterModuleName = cms.InputTag("ecalDeadCellTPFilter")
        )

    process.tmAK5CaloL1FastJet = process.calibTreeMakerAK5FastCaloData.clone(
        TreeName                       = process.tmAK5CaloL1Offset.TreeName,
        WritePhotons                   = process.tmAK5CaloL1Offset.WritePhotons,
        ECALDeadCellBEFilterModuleName = process.tmAK5CaloL1Offset.ECALDeadCellBEFilterModuleName,
        ECALDeadCellTPFilterModuleName = process.tmAK5CaloL1Offset.ECALDeadCellTPFilterModuleName
        )

    process.tmAK5PFL1FastJet = process.calibTreeMakerAK5FastPFData.clone(
        TreeName                       = process.tmAK5CaloL1Offset.TreeName,
        WritePhotons                   = process.tmAK5CaloL1Offset.WritePhotons,
        ECALDeadCellBEFilterModuleName = process.tmAK5CaloL1Offset.ECALDeadCellBEFilterModuleName,
        ECALDeadCellTPFilterModuleName = process.tmAK5CaloL1Offset.ECALDeadCellTPFilterModuleName
        )

    process.tmAK5PFL1CHS = process.calibTreeMakerAK5PFCHSData.clone(
        TreeName                       = process.tmAK5CaloL1Offset.TreeName,
        WritePhotons                   = process.tmAK5CaloL1Offset.WritePhotons,
        ECALDeadCellBEFilterModuleName = process.tmAK5CaloL1Offset.ECALDeadCellBEFilterModuleName,
        ECALDeadCellTPFilterModuleName = process.tmAK5CaloL1Offset.ECALDeadCellTPFilterModuleName
        )

    process.products = cms.Sequence(
        process.calibjets 
        )
    if not isData:
        process.products = cms.Sequence(
            process.calibjets *
            process.genPhotons *
            process.goodGenPhotons *
            process.myPartons *
            process.CaloJetPartonMatching *
            process.PFJetPartonMatching *
            process.AK5PFCHSJetPartonMatching
            )


    # ---- Path -------------------------------------------------------------------
    process.makeTrees = cms.Path(
        process.filterSequence *
        process.products *
        process.ak5CaloJetsBtag *
        process.tmAK5CaloL1Offset *
        process.tmAK5CaloL1FastJet *
        process.ak5PFJetsBtag *
        process.tmAK5PFL1FastJet *
        process.ak5PFCHSJetsBtag *
        process.tmAK5PFL1CHS
        )

    process.schedule = cms.Schedule(process.makeTrees)




