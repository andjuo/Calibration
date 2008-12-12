import FWCore.ParameterSet.Config as cms

from Calibration.CalibSamples.PhotonJetSample_cff import *
from Calibration.CalibSamples.TrackTowerSample_cff import *
from Calibration.CalibSamples.DiJetSample_cff import *
from Calibration.CalibSamples.TriJetSample_cff import *
#from Calibration.CalibSamples.TopSample_cff import *
from Calibration.CalibSamples.ZJetSample_cff import *
from Calibration.CalibTreeMaker.CalibTreeMaker_cfi import *

photonJetInput     = cms.Sequence(selectedPhotonJetSample)
trackTowerInput    = cms.Sequence(selectedTrackTowerSample)
DiJetInput         = cms.Sequence(selectedDiJetSample)
TriJetInput        = cms.Sequence(selectedTriJetSample)
#TopInput           = cms.Sequence(makeTopSample_semiLepFilter)
ZJetInput          = cms.Sequence(selectedZJetSample)

makePhotonJetTree  = cms.Sequence(photonJetInput*calibTreeMaker)
makeTrackTowerTree = cms.Sequence(trackTowerInput*calibTreeMaker)
makeDiJetTree      = cms.Sequence(DiJetInput*calibTreeMaker)
makeTriJetTree     = cms.Sequence(TriJetInput*calibTreeMaker)
makeNJetTree       = cms.Sequence(DiJetInput+TriJetInput*calibTreeMaker)
#makeTopTree        = cms.Sequence(TopInput*calibTreeMaker)
makeZJetTree       = cms.Sequence(ZJetInput*calibTreeMaker)

#makeAllTrees = cms.Sequence(photonJetInput+trackTowerInput+DiJetInput+TriJetInput*calibTreeMaker)

