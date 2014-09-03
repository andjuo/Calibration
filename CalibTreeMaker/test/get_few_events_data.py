# copy a sample of data file

import FWCore.ParameterSet.Config as cms

process = cms.Process("MYCOPY")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(50) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
        #'/store/mc/Summer12_DR53X/G_Pt-15to3000_TuneZ2_Flat_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/0035BB1E-950E-E211-B5FE-002481E101DA.root'
        '/store/data/Run2012D/SinglePhotonParked/AOD/22Jan2013-v1/30003/2651A609-ED84-E211-B41D-003048D477AA.root'
        )
)

process.copyAll = cms.OutputModule("PoolOutputModule",
          fileName = cms.untracked.string("selection_data.root") )
process.printEventNumber = cms.OutputModule("AsciiOutputModule")
process.p = cms.EndPath(process.copyAll + process.printEventNumber)
