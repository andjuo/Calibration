## $Id: $
##
## Beam halo filter as used in the RA2 analysis

import FWCore.ParameterSet.Config as cms

beamHaloFilter = cms.EDFilter(
    "BeamHaloFilter",
    taggingMode = cms.bool(False)
    )
