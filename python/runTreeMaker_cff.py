# $Id: $

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

    # vertex filter
    process.vertexFilter = cms.EDFilter(
        "VertexSelector",
        src = cms.InputTag("offlinePrimaryVertices"),
        cut = cms.string("!isFake && ndof > 4 && abs(z) <= 24 && position.Rho <= 2"),
        filter = cms.bool(True),
        )

    # monster event filter
    process.trackFilter = cms.EDFilter(
        "FilterOutScraping",
        applyfilter = cms.untracked.bool(True),
        debugOn     = cms.untracked.bool(False),
        numtrack    = cms.untracked.uint32(10),
        thresh      = cms.untracked.double(0.25)
        ) 

    # sequence with filters
    process.filterSequence = cms.Sequence(
        process.hltHighLevel *
        process.vertexFilter *
        process.trackFilter
        )

    if not isData:
        filterSequence.remove( hltHighLevel )



    # ---- Tree makers ------------------------------------------------------------
    process.load("Calibration.CalibTreeMaker.CalibTreeMaker_cff")

    process.calibTreeMakerCaloData.TreeName         = treeName
    process.calibTreeMakerAK5FastCaloData.TreeName  = treeName
    process.calibTreeMakerAK5FastPFData.TreeName    = treeName
    process.calibTreeMakerAK5PFCHSData.TreeName     = treeName

    process.calibTreeMakerCaloData.WritePhotons         = writePhotons
    process.calibTreeMakerAK5FastCaloData.WritePhotons  = writePhotons
    process.calibTreeMakerAK5FastPFData.WritePhotons    = writePhotons
    process.calibTreeMakerAK5PFCHSData.WritePhotons     = writePhotons

    process.products = cms.Sequence(
        process.calibjets 
        )
    if not isData:
        process.products.append(        
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
        process.calibTreeMakerCaloData *
        process.calibTreeMakerAK5FastCaloData *
        process.ak5PFJetsBtag *
        process.calibTreeMakerAK5FastPFData *
        process.ak5PFCHSJetsBtag *
        process.calibTreeMakerAK5PFCHSData
        )

    process.schedule = cms.Schedule(process.makeTrees)




