from Calibration.CalibTreeMaker.CalibTreeMaker_cfi import *


from TrackingTools.TrackAssociator.default_cfi import *
from PhysicsTools.HepMCCandAlgos.genParticles_cfi import *

genPhotons = cms.EDFilter("PdgIdAndStatusCandViewSelector",
    src = cms.InputTag("genParticles"),
    pdgId = cms.vint32(22),
    status = cms.vint32(1)
)

goodGenPhotons = cms.EDFilter("EtaPtMinCandViewSelector",
    src = cms.InputTag("genPhotons"),
    etaMin = cms.double(-3.0),
    etaMax = cms.double(3.0),
    ptMin = cms.double(20.0)
)

genMuons = cms.EDFilter("PdgIdAndStatusCandViewSelector",
    src = cms.InputTag("genParticles"),
    pdgId = cms.vint32(13),
    status = cms.vint32(1)
)

goodGenMuons = cms.EDFilter("EtaPtMinCandViewSelector",
     src = cms.InputTag("genMuons"),
     etaMin = cms.double(-2.5),
     etaMax = cms.double(2.5),
     ptMin = cms.double(5.0)
)

calibTreeMakerAK7Calo = calibTreeMakerCalo.clone(
    OutputFile = 'ak7Calo.root',
    NJet_Jets  = 'ak7CaloJets',
    NJet_JetIDs = 'ak7JetID',
    NJet_PartonMatch = 'AK7CaloJetPartonMatching',
    NJet_GenJets = 'ak7GenJets',
    NJet_L1JetCorrector = 'ak7CaloL1Offset',
    NJet_L2JetCorrector = 'ak7CaloL2Relative',
    NJet_L3JetCorrector = 'ak7CaloL3Absolute',
    NJet_L1L2L3JetCorrector = 'ak7CaloL1L2L3',
    NJet_L1L2L3L4JWJetCorrector = 'ak7CaloL1L2L3'
)
calibTreeMakerIC5Calo = calibTreeMakerCalo.clone(
    OutputFile = 'ic5Calo.root',
    NJet_Jets  = 'iterativeCone5CaloJets',
    NJet_JetIDs = 'ic5JetID',
    NJet_PartonMatch = 'IC5CaloJetPartonMatching',
    NJet_GenJets = 'iterativeCone5GenJets',
    NJet_L1JetCorrector = 'ic5CaloL1Offset',
    NJet_L2JetCorrector = 'ic5CaloL2Relative',
    NJet_L3JetCorrector = 'ic5CaloL3Absolute',
    NJet_L1L2L3JetCorrector = 'ic5CaloL1L2L3',
    NJet_L1L2L3L4JWJetCorrector = 'ic5CaloL1L2L3'
)

calibTreeMakerKT4Calo = calibTreeMakerCalo.clone(
    OutputFile = 'kt4Calo.root',
    NJet_Jets  = 'kt4CaloJets',
    NJet_JetIDs = 'kt4JetID',
    NJet_PartonMatch = 'KT4CaloJetPartonMatching',
    NJet_GenJets = 'kt4GenJets',
    NJet_L1JetCorrector = 'kt4CaloL1Offset',
    NJet_L2JetCorrector = 'kt4CaloL2Relative',
    NJet_L3JetCorrector = 'kt4CaloL3Absolute',
    NJet_L1L2L3JetCorrector = 'kt4CaloL1L2L3',
    NJet_L1L2L3L4JWJetCorrector = 'kt4CaloL1L2L3'
)

calibTreeMakerKT6Calo = calibTreeMakerCalo.clone(
    OutputFile = 'kt6Calo.root',
    NJet_Jets  = 'kt6CaloJets',
    NJet_JetIDs = 'kt6JetID',
    NJet_PartonMatch = 'KT6CaloJetPartonMatching',
    NJet_GenJets = 'kt6GenJets',
    NJet_L2JetCorrector = 'kt6CaloL2Relative',
    NJet_L3JetCorrector = 'kt6CaloL3Absolute',
    NJet_L1L2L3JetCorrector = 'kt6CaloL1L2L3',
    NJet_L1L2L3L4JWJetCorrector = 'kt6CaloL1L2L3'
)

calibTreeMakerAK7PF = calibTreeMakerPF.clone(
    OutputFile = 'ak7PF.root',
    NJet_Jets  = 'ak7PFJets',
    NJet_PartonMatch = 'AK7PFJetPartonMatching',
    NJet_GenJets = 'ak7GenJets',
    NJet_L1JetCorrector = 'ak7PFL1Offset',
    NJet_L2JetCorrector = 'ak7PFL2Relative',
    NJet_L3JetCorrector = 'ak7PFL3Absolute',
    NJet_L1L2L3JetCorrector = 'ak7PFL1L2L3',
    NJet_L1L2L3L4JWJetCorrector = 'ak7PFL1L2L3'
)

calibTreeMakerIC5PF = calibTreeMakerPF.clone(
    OutputFile = 'ic5PF.root',
    NJet_Jets  = 'iterativeCone5PFJets',
    NJet_PartonMatch = 'IC5PFJetPartonMatching',
    NJet_GenJets = 'iterativeCone5GenJets',
    NJet_L2JetCorrector = 'ic5PFL2Relative',
    NJet_L3JetCorrector = 'ic5PFL3Absolute',
    NJet_L1L2L3JetCorrector = 'ic5PFL2L3',
    NJet_L1L2L3L4JWJetCorrector = 'ic5PFL2L3'
)


calibTreeMakerKT4PF = calibTreeMakerPF.clone(
    OutputFile = 'kt4PF.root',
    NJet_Jets  = 'kt4PFJets',
    NJet_PartonMatch = 'KT4PFJetPartonMatching',
    NJet_GenJets = 'kt4GenJets',
    NJet_L1JetCorrector = 'kt4PFL1Offset',
    NJet_L2JetCorrector = 'kt4PFL2Relative',
    NJet_L3JetCorrector = 'kt4PFL3Absolute',
    NJet_L1L2L3JetCorrector = 'kt4PFL1L2L3',
    NJet_L1L2L3L4JWJetCorrector = 'kt4PFL1L2L3'
)

calibTreeMakerKT6PF = calibTreeMakerPF.clone(
    OutputFile = 'kt6PF.root',
    NJet_Jets  = 'kt6PFJets',
    NJet_PartonMatch = 'KT6PFJetPartonMatching',
    NJet_GenJets = 'kt6GenJets',
    NJet_L1JetCorrector = 'kt6PFL1Offset',
    NJet_L2JetCorrector = 'kt6PFL2Relative',
    NJet_L3JetCorrector = 'kt6PFL3Absolute',
    NJet_L1L2L3JetCorrector = 'kt6PFL1L2L3',
    NJet_L1L2L3L4JWJetCorrector = 'kt6PFL1L2L3'
)

calibTreeMakerAK5PFCHS = calibTreeMakerPF.clone(
    OutputFile = 'ak5PFCHS.root',
    NJet_Jets  = 'ak5PFCHSJets',
    NJet_PartonMatch = 'AK5PFCHSJetPartonMatching',
    NJet_Rho         = cms.InputTag('kt6PFJets','rho'),
    NJet_L1JetCorrector = 'ak5PFL1Fastjet',
    NJet_L1L2L3JetCorrector = 'ak5PFL1FastL2L3',
    NJet_L1L2L3L4JWJetCorrector = 'ak5PFL1FastL2L3'
)

calibTreeMakerAK5FastCalo = calibTreeMakerCalo.clone(
    OutputFile = 'ak5FastCalo.root',
    NJet_L1JetCorrector = 'ak5CaloL1Fastjet',
    NJet_L1L2L3JetCorrector = 'ak5CaloL1FastL2L3',
    NJet_L1L2L3L4JWJetCorrector = 'ak5CaloL1FastL2L3'
)

calibTreeMakerAK5FastPF = calibTreeMakerPF.clone(
    OutputFile = 'ak5FastPF.root',
    NJet_L1JetCorrector = 'ak5PFL1Fastjet',
    NJet_L1L2L3JetCorrector = 'ak5PFL1FastL2L3',
    NJet_L1L2L3L4JWJetCorrector = 'ak5PFL1FastL2L3'
)

from PhysicsTools.JetMCAlgos.SelectPartons_cff import *

CaloJetPartonMatching = cms.EDProducer("JetPartonMatcher",
   jets = cms.InputTag("ak5CaloJets"),
   coneSizeToAssociate = cms.double(0.2),
   partons = cms.InputTag("myPartons")
)
PFJetPartonMatching = cms.EDProducer("JetPartonMatcher",
   jets = cms.InputTag("ak5PFJets"),
   coneSizeToAssociate = cms.double(0.2),
   partons = cms.InputTag("myPartons")
)
JPTJetPartonMatching = cms.EDProducer("JetPartonMatcher",
   jets = cms.InputTag("JetPlusTrackZSPCorJetAntiKt5"),
   coneSizeToAssociate = cms.double(0.2),
   partons = cms.InputTag("myPartons")
)
TrackJetPartonMatching = cms.EDProducer("JetPartonMatcher",
   jets = cms.InputTag("ak5TrackJets"),
   coneSizeToAssociate = cms.double(0.2),
   partons = cms.InputTag("myPartons")
)
PFClusterJetPartonMatching = cms.EDProducer("JetPartonMatcher",
   jets = cms.InputTag("ak5PFClusterJets"),
   coneSizeToAssociate = cms.double(0.2),
   partons = cms.InputTag("myPartons")
)
AK7CaloJetPartonMatching = CaloJetPartonMatching.clone( 
    jets = 'ak7CaloJets' 
)

KT6CaloJetPartonMatching = CaloJetPartonMatching.clone( 
    jets = 'kt6CaloJets' 
)

AK7PFJetPartonMatching = PFJetPartonMatching.clone( 
    jets = 'ak7PFJets' 
)

IC5PFJetPartonMatching = PFJetPartonMatching.clone( 
    jets = 'iterativeCone5PFJets' 
)

KT4PFJetPartonMatching = PFJetPartonMatching.clone( 
    jets = 'kt4PFJets' 
)

KT6PFJetPartonMatching = PFJetPartonMatching.clone( 
    jets = 'kt6PFJets' 
)

AK5PFCHSJetPartonMatching = PFJetPartonMatching.clone( 
    jets = 'ak5PFCHSJets' 
)

calibTreeMakersMC = cms.Sequence( genPhotons * goodGenPhotons 
                                  * genMuons * goodGenMuons
                                  * myPartons 
                                  * CaloJetPartonMatching
                                  * PFJetPartonMatching
                                  * JPTJetPartonMatching
                                  * calibTreeMakerCalo
                                  * calibTreeMakerPF
                                  * calibTreeMakerJPT
                                  * AK7CaloJetPartonMatching
                                  * calibTreeMakerAK7Calo
                                  * AK7PFJetPartonMatching
                                  * calibTreeMakerAK7PF
                                  * calibTreeMakerAK5FastCalo
                                  * calibTreeMakerAK5FastPF
                                  * AK5PFCHSJetPartonMatching
                                  * calibTreeMakerAK5PFCHS)

### data
calibTreeMakerCaloData = calibTreeMakerCalo.clone(
    NJet_PartonMatch = '',
    NJet_L1L2L3JetCorrector = 'ak5CaloL1L2L3Residual',
    NJet_L1L2L3L4JWJetCorrector = 'ak5CaloL1L2L3Residual'
)
calibTreeMakerPFData = calibTreeMakerPF.clone(
    NJet_PartonMatch = '',
    NJet_L1L2L3JetCorrector = 'ak5PFL1L2L3Residual',
    NJet_L1L2L3L4JWJetCorrector = 'ak5PFL1L2L3Residual'
)
calibTreeMakerJPTData = calibTreeMakerJPT.clone(
    NJet_PartonMatch = '',
    NJet_L1L2L3JetCorrector = 'ak5JPTL1L2L3Residual',
    NJet_L1L2L3L4JWJetCorrector = 'ak5JPTL1L2L3Residual'
)
calibTreeMakerAK7CaloData = calibTreeMakerAK7Calo.clone(
    NJet_PartonMatch = '',
    NJet_L1L2L3JetCorrector = 'ak7CaloL1L2L3Residual',
    NJet_L1L2L3L4JWJetCorrector = 'ak7CaloL1L2L3Residual'
)
calibTreeMakerAK7PFData = calibTreeMakerAK7PF.clone(
    NJet_PartonMatch = '',
    NJet_L1L2L3JetCorrector = 'ak7PFL1L2L3Residual',
    NJet_L1L2L3L4JWJetCorrector = 'ak7PFL1L2L3Residual'
)

calibTreeMakerAK5FastCaloData = calibTreeMakerAK5FastCalo.clone(
    NJet_PartonMatch = '',
    NJet_L1L2L3JetCorrector = 'ak5CaloL1FastL2L3Residual',
    NJet_L1L2L3L4JWJetCorrector = 'ak5CaloL1FastL2L3Residual'
)

calibTreeMakerAK5FastPFData = calibTreeMakerAK5FastPF.clone(
    NJet_PartonMatch = '',
    NJet_L1L2L3JetCorrector = 'ak5PFL1FastL2L3Residual',
    NJet_L1L2L3L4JWJetCorrector = 'ak5PFL1FastL2L3Residual'
)

calibTreeMakerAK5PFCHSData = calibTreeMakerAK5PFCHS.clone(
    NJet_PartonMatch = '',
    NJet_L1L2L3JetCorrector = 'ak5PFL1FastL2L3Residual',
    NJet_L1L2L3L4JWJetCorrector = 'ak5PFL1FastL2L3Residual'
)

calibTreeMakersData = cms.Sequence( calibTreeMakerCaloData
                                    * calibTreeMakerPFData
                                    * calibTreeMakerJPTData
                                    * calibTreeMakerAK7CaloData
                                    * calibTreeMakerAK7PFData
                                    * calibTreeMakerAK5FastCaloData
                                    * calibTreeMakerAK5FastPFData
                                    * calibTreeMakerAK5PFCHSData)
