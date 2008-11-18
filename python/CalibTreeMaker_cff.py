import FWCore.ParameterSet.Config as cms

from Calibration.CalibSamples.PhotonJetSample_cff import *
from Calibration.CalibSamples.TrackTowerSample_cff import *
from Calibration.CalibSamples.DiJetSample_cff import *
from Calibration.CalibSamples.TriJetSample_cff import *
from Calibration.CalibTreeMaker.CalibTreeMaker_cfi import *

photonJetInput     = cms.Sequence(selectedPhotonJetSample)
trackTowerInput    = cms.Sequence(selectedTrackTowerSample)
DiJetInput         = cms.Sequence(selectedDiJetSample)
TriJetInput        = cms.Sequence(selectedTriJetSample)

makePhotonJetTree  = cms.Sequence(photonJetInput*calibTreeMaker)
makeTrackTowerTree = cms.Sequence(trackTowerInput*calibTreeMaker)
makeDiJetTree      = cms.Sequence(DiJetInput*calibTreeMaker)
makeTriJetTree     = cms.Sequence(TriJetInput*calibTreeMaker)
makeNJetTree       = cms.Sequence(DiJetInput+TriJetInput*calibTreeMaker)

#makeAllTrees = cms.Sequence(photonJetInput+trackTowerInput+DiJetInput+TriJetInput*calibTreeMaker)

