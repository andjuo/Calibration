## $Id: cleaningSequences_cff.py,v 1.3 2012/10/30 21:07:00 mschrode Exp $

import FWCore.ParameterSet.Config as cms


##
## Standard cleaning steps as recommended in
## https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookCollisionsDataAnalysis#Analysis_of_the_processed_data
##

from Calibration.CalibTreeMaker.goodPrimaryVertexFilter_cfi import goodPrimaryVertexFilter, goodPrimaryVertices
from Calibration.CalibTreeMaker.beamBkgFilter_cfi import beamBkgFilter



##
## MET filter recommended at
## https://twiki.cern.ch/twiki/bin/view/CMS/MissingETOptionalFilters
##
## You have to check out the RecoMET/METFilters and RecoMET/METAnalyzers
## packages:
##
##  cvs co -r V00-00-10 RecoMET/METFilters
##  cvs co -r V00-00-08 RecoMET/METAnalyzers
##
## Please check at the above TWiki whether the tags are still appropriate!

## The iso-based HBHE noise filter ___________________________________________||
from CommonTools.RecoAlgos.HBHENoiseFilter_cfi import HBHENoiseFilter
HBHENoiseFilter.taggingMode = cms.bool(False)

## The CSC beam halo tight filter ____________________________________________||
from RecoMET.METAnalyzers.CSCHaloFilter_cfi import CSCTightHaloFilter

## The HCAL laser filter _____________________________________________________||
from RecoMET.METFilters.hcalLaserEventFilter_cfi import hcalLaserEventFilter
hcalLaserEventFilter.taggingMode = cms.bool(False)

## The EE bad SuperCrystal filter ____________________________________________||
from RecoMET.METFilters.eeBadScFilter_cfi import eeBadScFilter
eeBadScFilter.taggingMode = cms.bool(False)

## The ECAL laser correction filter __________________________________________||
from RecoMET.METFilters.ecalLaserCorrFilter_cfi import ecalLaserCorrFilter
ecalLaserCorrFilter.taggingMode = cms.bool(False)

## The tracking failure filter _______________________________________________||
from RecoMET.METFilters.trackingFailureFilter_cfi import trackingFailureFilter
trackingFailureFilter.taggingMode = cms.bool(False)
trackingFailureFilter.VertexSource = cms.InputTag('goodPrimaryVertices')

## The ECAL dead cell filters ________________________________________________||
## Filter is set up in tagging mode; decision can be written
## to the ntuple if specified in calibTreeMaker...
from RecoMET.METFilters.EcalDeadCellTriggerPrimitiveFilter_cfi import EcalDeadCellTriggerPrimitiveFilter
EcalDeadCellTriggerPrimitiveFilter.taggingMode = cms.bool(False)
from RecoMET.METFilters.EcalDeadCellBoundaryEnergyFilter_cfi import EcalDeadCellBoundaryEnergyFilter
EcalDeadCellBoundaryEnergyFilter.taggingMode = cms.bool(False)

## The tracking POG filters __________________________________________________||
from RecoMET.METFilters.trackingPOGFilters_cff import *

##
##  Cleaning sequence to be used before ntupling
##

## Rejects the events
stdCleaningSequence = cms.Sequence(
   goodPrimaryVertexFilter *
   beamBkgFilter *
   HBHENoiseFilter *
   CSCTightHaloFilter *
   hcalLaserEventFilter *
   eeBadScFilter *
   ecalLaserCorrFilter *
   goodPrimaryVertices * trackingFailureFilter *
   EcalDeadCellTriggerPrimitiveFilter *
   EcalDeadCellBoundaryEnergyFilter *
   trkPOGFilters
)


