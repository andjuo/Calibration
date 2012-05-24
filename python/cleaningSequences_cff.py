## $Id: $

import FWCore.ParameterSet.Config as cms


## Standard cleaning steps as recommended in
## https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookCollisionsDataAnalysis#Analysis_of_the_processed_data
##
## -- Should always be included! --

from Calibration.CalibTreeMaker.goodPrimaryVertexFilter_cfi import goodPrimaryVertexFilter
from Calibration.CalibTreeMaker.beamBkgFilter_cfi import beamBkgFilter
from CommonTools.RecoAlgos.HBHENoiseFilter_cfi import HBHENoiseFilter
standardCleaningSequence = cms.Sequence(
    goodPrimaryVertexFilter *
    beamBkgFilter *
    HBHENoiseFilter
    )



## Standard cleaning sequence as above with additional removal
## of beam halo events
from Calibration.CalibTreeMaker.beamHaloFilter_cfi import beamHaloFilter
standardCleaningPlusBeamHaloSequence = cms.Sequence(
    standardCleaningSequence *
    beamHaloFilter
    )
