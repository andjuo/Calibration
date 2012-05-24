## $Id: $
##
## Filter to tag events with jets hitting detector regions with
## masked ECAL cells. The filter is a combination of two filters,
## the "trigger-primitve (TP)" and the boundary-energy (BE) filter".
## If applied, the filter will add two booleans to the event with
## labels 'ecalDeadCellTPFilter' and 'ecalDeadCellBEFilter' which
## store the filter decision (false means there is at least one
## jet in a masked region).
##
##
## To apply, you need to add the appropriate plugins first
##
## addpkg RecoMET/METFilters V00-00-01
##
## Note: This will only work in 52X and above!


import FWCore.ParameterSet.Config as cms

## Configure TP filter
from RecoMET.METFilters.EcalDeadCellTriggerPrimitiveFilter_cfi import EcalDeadCellTriggerPrimitiveFilter
ecalDeadCellTPFilter = EcalDeadCellTriggerPrimitiveFilter.clone(
    taggingMode               = cms.bool(True),
    tpDigiCollection          = cms.InputTag("ecalTPSkim"),
    etValToBeFlagged          = cms.double(63.75),
    ebReducedRecHitCollection = cms.InputTag("reducedEcalRecHitsEB"),
    eeReducedRecHitCollection = cms.InputTag("reducedEcalRecHitsEE"),
    maskedEcalChannelStatusThreshold = cms.int32( 1 ),
    doEEfilter                = cms.untracked.bool( True ),
    makeProfileRoot           = cms.untracked.bool( False ),
    )
## Configure BE filter
from RecoMET.METFilters.EcalDeadCellBoundaryEnergyFilter_cfi import EcalDeadCellBoundaryEnergyFilter
ecalDeadCellBEFilter = EcalDeadCellBoundaryEnergyFilter.clone(
    taggingMode                    = cms.bool(True),
    recHitsEB                      = cms.InputTag("reducedEcalRecHitsEB"),
    recHitsEE                      = cms.InputTag("reducedEcalRecHitsEE"),
    cutBoundEnergyGapEE            = cms.untracked.double(100),
    cutBoundEnergyGapEB            = cms.untracked.double(100),
    cutBoundEnergyDeadCellsEB      = cms.untracked.double(10),
    cutBoundEnergyDeadCellsEE      = cms.untracked.double(10),
    limitDeadCellToChannelStatusEB = cms.vint32(12,14),
    limitDeadCellToChannelStatusEE = cms.vint32(12,14),
    enableGap                      = cms.untracked.bool(False)
    )

## Filter sequence to be applied in config
ecalDeadCellCleaningSequence = cms.Sequence(
    ecalDeadCellTPFilter *
    ecalDeadCellBEFilter
    )


