import FWCore.ParameterSet.Config as cms

# Jet corrections.
#
# Define the correction services for each algorithm.
#
ZSPJetCorrectorScone5 = cms.ESSource("ZSPJetCorrectionService",
    tagName = cms.string('ZSP_CMSSW219_Iterative_Cone_05'),
    label = cms.string('ZSPJetCorrectorScone5')
#    tagName = cms.string('ZSP_CMSSW152_Iterative_Cone_05'),
)

#   
#   Define the producers of corrected jet collections for each algorithm.
#
ZSPJetCorJetScone5 = cms.EDProducer("CaloJetCorrectionProducer",
    src = cms.InputTag("sisCone5CaloJets"),
    correctors = cms.vstring('ZSPJetCorrectorScone5'),
    alias = cms.untracked.string('ZSPJetCorJetScone5')
)

#
#  Define a sequence to make all corrected jet collections at once.
#
ZSPJetCorrections = cms.Sequence(ZSPJetCorJetScone5)

