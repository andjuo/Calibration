from RecoJets.Configuration.RecoJets_cff import *
from RecoJets.Configuration.RecoPFJets_cff import *
from CommonTools.ParticleFlow.pfNoPileUp_cff import *	
#from CommonTools.ParticleFlow.pfParticleSelection_cff import *
from PhysicsTools.SelectorUtils.pvSelector_cfi import pvSelector


kt6CaloJets.doRhoFastjet = True
kt6CaloJets.doAreaFastjet = True
#kt6CaloJets.voronoiRfact = 0.9
ak5CaloJets.doAreaFastjet = True
ak7CaloJets.doAreaFastjet = True

kt6PFJets.doRhoFastjet = True
kt6PFJets.doAreaFastjet = True
#kt6PFJets.voronoiRfact = 0.9
ak5PFJets.doAreaFastjet = True
ak7PFJets.doAreaFastjet = True

#CHS

selectedPrimaryVertexQuality = cms.EDFilter("VertexSelector",
   	src = cms.InputTag('offlinePrimaryVertices'),
	cut = cms.string("isValid & ndof >= 4 & chi2 > 0 & tracksSize > 0 & abs(z) < 24 & abs(position.Rho) < 2."),
	filter = cms.bool(False),
)

### GeneralTrack AssociationMap-specific includes		
from CommonTools.RecoUtils.pf_pu_assomap_cfi import Tracks2Vertex
		
Tracks2VertexAM = Tracks2Vertex.clone(
        VertexCollection = cms.InputTag('selectedPrimaryVertexQuality'),
	VertexAssOneDim = cms.untracked.bool(False),
	VertexAssUseAbsDistance = cms.untracked.bool(True),
	UseBeamSpotCompatibility = cms.untracked.bool(True),
        ignoreMissingCollection = cms.bool(True)
)
		
### PFCandidate AssociationMap-specific includes
from CommonTools.RecoUtils.pfcand_assomap_cfi import PFCandAssoMap
		
PFCand2VertexAM = PFCandAssoMap.clone(
          VertexCollection = cms.InputTag('selectedPrimaryVertexQuality'),
          VertexTrackAssociationMap = cms.InputTag('Tracks2VertexAM'),
          ignoreMissingCollection = cms.bool(True)
)
		
### PFCandidateCollection-specific includes
from CommonTools.RecoUtils.pfcand_nopu_witham_cfi import FirstVertexPFCandidates
		
PFCand = FirstVertexPFCandidates.clone(
          VertexPFCandAssociationMap = cms.InputTag('PFCand2VertexAM'),
)
	
### JetProducer-specific includes
from RecoJets.JetProducers.ak5PFJets_cfi import ak5PFJets	

ak5PFCHSNewJets = ak5PFJets.clone(
	src = cms.InputTag("PFCand")
)

###old CHS
goodOfflinePrimaryVertices = cms.EDFilter(
    "PrimaryVertexObjectFilter",
    filterParams = pvSelector.clone( minNdof = cms.double(4.0), maxZ = cms.double(24.0) ),
    src=cms.InputTag('offlinePrimaryVertices')
)


pfPileUp.Vertices = 'goodOfflinePrimaryVertices'
pfPileUp.checkClosestZVertex = cms.bool(False)
pfPileUp.PFCandidates = 'particleFlow'
pfNoPileUp.bottomCollection = 'particleFlow'

ak5PFCHSJets = ak5PFJets.clone(
    src = 'pfNoPileUp'
)
kt6PFCHSJets = kt6PFJets.clone(
    src = 'pfNoPileUp'
)


calibjetsnew = cms.Sequence(recoJets * recoPFJets * goodOfflinePrimaryVertices 
                            * pfNoPileUpSequence * ak5PFCHSJets * 
                            selectedPrimaryVertexQuality * Tracks2VertexAM * 
                            PFCand2VertexAM * PFCand * ak5PFCHSNewJets)
 
try:
    calibjetsnew.remove(kt6PFJetsCentralChargedPileUp)
    calibjetsnew.remove(kt6PFJetsCentralNeutral)
    calibjetsnew.remove(kt6PFJetsCentralNeutralTight)
except NameError:
    print 'Ignoring NameError (CMSSW 44X)'

