import FWCore.ParameterSet.Config as cms

# $Id: sisCone5JTA_cff.py,v 1.3 2008/06/19 14:55:16 rahatlou Exp $
from TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAlong_cfi import * ##propagator

from RecoJets.JetAssociationProducers.j2tParametersCALO_cfi import *
from RecoJets.JetAssociationProducers.j2tParametersVX_cfi import *
ZSPsisCone5JetTracksAssociatorAtVertex = cms.EDFilter("JetTracksAssociatorAtVertex",
    j2tParametersVX,
    jets = cms.InputTag("ZSPJetCorJetScone5")
)

ZSPsisCone5JetTracksAssociatorAtCaloFace = cms.EDFilter("JetTracksAssociatorAtCaloFace",
    j2tParametersCALO,
    jets = cms.InputTag("ZSPJetCorJetScone5")
)

ZSPsisCone5JetExtender = cms.EDFilter("JetExtender",
    jets = cms.InputTag("ZSPJetCorJetScone5"),
    jet2TracksAtCALO = cms.InputTag("ZSPsisCone5JetTracksAssociatorAtCaloFace"),
    jet2TracksAtVX = cms.InputTag("ZSPsisCone5JetTracksAssociatorAtVertex"),
    coneSize = cms.double(0.5)
)

ZSPsisCone5JTA = cms.Sequence(ZSPsisCone5JetTracksAssociatorAtVertex*ZSPsisCone5JetTracksAssociatorAtCaloFace*ZSPsisCone5JetExtender)
