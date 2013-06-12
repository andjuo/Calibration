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

process.GlobalTag.globaltag = 'START53_V22::All'

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(	
    '/store/mc/Summer12_DR53X/QCD_Pt_80_170_EMEnriched_TuneZ2star_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/0003/FEEC95EF-E4E4-E111-8FDA-00304867C04E.root'
    )
                            )

# photon selection
process.goodPhotons = cms.EDFilter("PhotonSelector",
                                   src = cms.InputTag("photons"),
                                   cut = cms.string('et > 20 && hadronicOverEm < 0.05 && ecalRecHitSumEtConeDR04 < 0.006*pt + 4.2 && hcalTowerSumEtConeDR04 <  0.0025*pt + 2.2 && trkSumPtHollowConeDR04 <  0.001*pt + 3.5')
                                   )

process.photonFilter = cms.EDFilter("EtMinPhotonCountFilter",
                            src = cms.InputTag("goodPhotons"),
                            etMin = cms.double(20.0),
                            minNumber = cms.uint32(1)
                            )

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000) )  # number of events 

process.options = cms.untracked.PSet(
    SkipEvent = cms.untracked.vstring('ProductNotFound'),
    Rethrow = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(True)
    )

#Filter
process.load('Calibration.CalibTreeMaker.cleaningSequences_cff')

## sequence with filters
process.filterSequence = cms.Sequence(  process.stdCleaningSequence
                                        ) 

process.load("Calibration.CalibTreeMaker.CalibTreeMaker_cff")


process.calibTreeMakerAK5FastPF.ECALDeadCellBEFilterModuleName = cms.InputTag("EcalDeadCellBoundaryEnergyFilter")
process.calibTreeMakerAK5FastPF.ECALDeadCellTPFilterModuleName = cms.InputTag("EcalDeadCellTriggerPrimitiveFilter")
process.calibTreeMakerAK5FastPF.WritePhotons = True
process.calibTreeMakerAK5FastPF.TreeName = "GammaJetTree"
process.calibTreeMakerAK5PFCHS.ECALDeadCellBEFilterModuleName = cms.InputTag("EcalDeadCellBoundaryEnergyFilter")
process.calibTreeMakerAK5PFCHS.ECALDeadCellTPFilterModuleName = cms.InputTag("EcalDeadCellTriggerPrimitiveFilter")
process.calibTreeMakerAK5PFCHS.WritePhotons = True
process.calibTreeMakerAK5PFCHS.TreeName = "GammaJetTree"

process.calibTreeMakerAK7FastPF.ECALDeadCellBEFilterModuleName = cms.InputTag("EcalDeadCellBoundaryEnergyFilter")
process.calibTreeMakerAK7FastPF.ECALDeadCellTPFilterModuleName = cms.InputTag("EcalDeadCellTriggerPrimitiveFilter")
process.calibTreeMakerAK7FastPF.WritePhotons = True
process.calibTreeMakerAK7FastPF.TreeName = "GammaJetTree"
process.calibTreeMakerAK7PFCHS.ECALDeadCellBEFilterModuleName = cms.InputTag("EcalDeadCellBoundaryEnergyFilter")
process.calibTreeMakerAK7PFCHS.ECALDeadCellTPFilterModuleName = cms.InputTag("EcalDeadCellTriggerPrimitiveFilter")
process.calibTreeMakerAK7PFCHS.WritePhotons = True
process.calibTreeMakerAK7PFCHS.TreeName = "GammaJetTree"

process.dump = cms.EDAnalyzer("EventContentAnalyzer")

process.pDump = cms.Path(process.dump )
process.pData = cms.Path(process.goodPhotons *
                         process.photonFilter *
                         process.filterSequence *
                         process.calibjets *
                         process.produceAllCaloMETCorrections *
                         process.produceAllPFMETCorrections *
			 process.produceAllPFCHSMETCorrections *
                         process.genPhotons *
                         process.goodGenPhotons *
                         process.myPartons *
                         process.PFJetPartonMatching *
                         process.AK5PFCHSJetPartonMatching *
                         process.ak5PFJetsBtag *
                         process.calibTreeMakerAK5FastPF *
                         process.ak5PFCHSJetsBtag *
                         process.calibTreeMakerAK5PFCHS *
                         process.ak7PFJetsBtag *
                         process.calibTreeMakerAK7FastPF *
                         process.ak7PFCHSJetsBtag *
                         process.calibTreeMakerAK7PFCHS
                         )
process.schedule = cms.Schedule(process.pData)
