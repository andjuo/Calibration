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

rho25kt6PFJets = kt6PFJets.clone(
    rParam = cms.double(0.6),
    Rho_EtaMax = cms.double(2.5),
    doRhoFastjet = cms.bool(True)
    )
rho25kt6CaloJets = kt6CaloJets.clone(
    rParam = cms.double(0.6),
    Rho_EtaMax = cms.double(2.5),
    doRhoFastjet = cms.bool(True)
    )


#CHS
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
ak7PFCHSJets = ak7PFJets.clone(
    src = 'pfNoPileUp'
)
kt6PFCHSJets = kt6PFJets.clone(
    src = 'pfNoPileUp'
)


calibjets = cms.Sequence(recoJets * recoPFJets * goodOfflinePrimaryVertices 
                         * pfNoPileUpSequence * ak5PFCHSJets * ak7PFCHSJets * rho25kt6PFJets * rho25kt6CaloJets)
 
try:
    calibjets.remove(kt6PFJetsCentralChargedPileUp)
    calibjets.remove(kt6PFJetsCentralNeutral)
    calibjets.remove(kt6PFJetsCentralNeutralTight)
except NameError:
    print 'Ignoring NameError (CMSSW 44X)'

