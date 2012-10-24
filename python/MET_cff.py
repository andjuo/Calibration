from JetMETCorrections.Configuration.DefaultJEC_cff import *
from JetMETCorrections.Type1MET.pfMETCorrections_cff import *
from JetMETCorrections.Configuration.JetCorrectionServices_cff import *
from JetMETCorrections.Type1MET.caloMETCorrections_cff import *

#residual corrected MET: PF

pfJetMETcorrResidual          = pfJetMETcorr.clone( jetCorrLabel = cms.string("ak5PFL1FastL2L3Residual") )

pfType1CorrectedMetResidual   = pfType1CorrectedMet.clone( srcType1Corrections = cms.VInputTag( cms.InputTag('pfJetMETcorrResidual', 'type1') ) )

pfType1p2CorrectedMetResidual = pfType1p2CorrectedMet.clone( srcType1Corrections = cms.VInputTag( cms.InputTag('pfJetMETcorrResidual', 'type1') ), srcUnclEnergySums = cms.VInputTag( cms.InputTag('pfJetMETcorr', 'type2'), cms.InputTag('pfJetMETcorr', 'offset'), cms.InputTag('pfCandMETcorr') ) )

producePFMETCorrectionsResidual = cms.Sequence(
   pfJetMETcorrResidual
   * pfType1CorrectedMetResidual
   * pfType1p2CorrectedMetResidual
)

produceAllPFMETCorrections = cms.Sequence(
   producePFMETCorrections
   * producePFMETCorrectionsResidual
)

#MET for PFCHS jets

pfCHSCandsNotInJet = pfNoJet.clone(
    topCollection = cms.InputTag('ak5PFCHSJets'),
    bottomCollection = cms.InputTag('particleFlow') #no idea of the bottom collection...
)

pfCHSJetMETcorr = cms.EDProducer("PFJetMETcorrInputProducer",
    src = cms.InputTag('ak5PFCHSJets'),
    offsetCorrLabel = cms.string("ak5PFL1Fastjet"),
    jetCorrLabel = cms.string("ak5PFL1FastL2L3"), # NOTE: use "ak5PFL1FastL2L3" for MC / "ak5PFL1FastL2L3Residual" for Data
    jetCorrEtaMax = cms.double(9.9),
    type1JetPtThreshold = cms.double(10.0),
    skipEM = cms.bool(True),
    skipEMfractionThreshold = cms.double(0.90),
    skipMuons = cms.bool(True),
    skipMuonSelection = cms.string("isGlobalMuon | isStandAloneMuon")
)                      

pfCHSType1CorrectedMet = pfType1CorrectedMet.clone( srcType1Corrections = cms.VInputTag( cms.InputTag('pfCHSJetMETcorr', 'type1') ) )

pfCHSType1p2CorrectedMet = pfType1p2CorrectedMet.clone( srcType1Corrections = cms.VInputTag( cms.InputTag('pfCHSJetMETcorr', 'type1') ), srcUnclEnergySums = cms.VInputTag( cms.InputTag('pfCHSJetMETcorr', 'type2'), cms.InputTag('pfCHSJetMETcorr', 'offset'), cms.InputTag('pfCandMETcorr') ) )

pfCHSJetMETcorrResidual          = pfCHSJetMETcorr.clone( jetCorrLabel = cms.string("ak5PFL1FastL2L3Residual") )

pfCHSType1CorrectedMetResidual   = pfType1CorrectedMet.clone( srcType1Corrections = cms.VInputTag( cms.InputTag('pfCHSJetMETcorrResidual', 'type1') ) )

pfCHSType1p2CorrectedMetResidual = pfType1p2CorrectedMet.clone( srcType1Corrections = cms.VInputTag( cms.InputTag('pfCHSJetMETcorrResidual', 'type1') ), srcUnclEnergySums = cms.VInputTag( cms.InputTag('pfCHSJetMETcorr', 'type2'), cms.InputTag('pfCHSJetMETcorr', 'offset'), cms.InputTag('pfCandMETcorr') ) )

producePFCHSMETCorrections = cms.Sequence(
   pfCHSJetMETcorr
   * pfCHSType1CorrectedMet
   * pfCHSType1p2CorrectedMet
)

producePFCHSMETCorrectionsResidual = cms.Sequence(
   pfCHSJetMETcorrResidual
   * pfCHSType1CorrectedMetResidual
   * pfCHSType1p2CorrectedMetResidual
)

produceAllPFCHSMETCorrections = cms.Sequence(
   producePFCHSMETCorrections
   * producePFCHSMETCorrectionsResidual
)

#residual corrected MET: Calo

caloJetMETcorrResidual          = caloJetMETcorr.clone( jetCorrLabel = cms.string("ak5CaloL2L3Residual") )

caloType1CorrectedMetResidual   = caloType1CorrectedMet.clone( srcType1Corrections = cms.VInputTag( cms.InputTag('caloJetMETcorrResidual', 'type1') ) )

caloType1p2CorrectedMetResidual = caloType1p2CorrectedMet.clone( srcType1Corrections = cms.VInputTag( cms.InputTag('caloJetMETcorrResidual', 'type1') ), srcUnclEnergySums = cms.VInputTag( cms.InputTag('caloJetMETcorrResidual', 'type2') ) )

produceCaloMETCorrectionsResidual = cms.Sequence(
   caloJetMETcorrResidual
   * caloType1CorrectedMetResidual
   * caloType1p2CorrectedMetResidual
)

produceAllCaloMETCorrections = cms.Sequence(
   produceCaloMETCorrections
   * produceCaloMETCorrectionsResidual
)
