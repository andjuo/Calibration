## import FWCore.ParameterSet.Config as cms

from Calibration.CalibSamples.TopSample_cff import *
from Calibration.CalibTreeMaker.CalibTreeMaker_cfi import *

TopInput           = cms.Sequence(makeTopSample_semiLepFilter)

makeTopTree        = cms.Sequence(TopInput*calibTreeMaker)
