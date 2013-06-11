## $Id: cleaningSequences_cff.py,v 1.8 2013/04/23 11:33:39 mschrode Exp $

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
## You have to check out the following additional packages (>=53X)
## cvs co -r V00-03-23      CommonTools/RecoAlgos                            
## cvs co -r V00-11-17      DPGAnalysis/SiStripTools                         
## cvs co -r V01-00-11-01   DPGAnalysis/Skims                                
## cvs co -r V00-00-08      DataFormats/TrackerCommon                        
## cvs co -r V01-09-05      RecoLocalTracker/SubCollectionProducers          
## cvs co -r V00-00-08      RecoMET/METAnalyzers                             
## cvs co -r V00-00-13-01   RecoMET/METFilters                  
##
## Please check the above TWiki to confirm that the tags are still appropriate!

## PKAM filter
from Calibration.CalibTreeMaker.beamBkgFilter_cfi import beamBkgFilter

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


