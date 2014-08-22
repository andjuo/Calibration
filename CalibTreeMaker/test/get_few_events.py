# copy a sample of data file

import FWCore.ParameterSet.Config as cms

process = cms.Process("MYCOPY")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
        '/store/mc/Summer12_DR53X/G_Pt-15to3000_TuneZ2_Flat_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/0035BB1E-950E-E211-B5FE-002481E101DA.root'
        )
)

process.copyAll = cms.OutputModule("PoolOutputModule",
          fileName = cms.untracked.string("selection.root") )
process.printEventNumber = cms.OutputModule("AsciiOutputModule")
process.p = cms.EndPath(process.copyAll + process.printEventNumber)
