#ifndef NJet_H
#define NJet_H

#include <string>
#include <vector>
#include <iostream>

#include "TFile.h"
#include "TNamed.h"
#include "TChain.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/METReco/interface/CaloMET.h"
#include "DataFormats/METReco/interface/CaloMETCollection.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"

#include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"

#include "TrackingTools/TrackAssociator/interface/TrackDetectorAssociator.h"
#include "TrackingTools/TrackAssociator/interface/TrackAssociatorParameters.h"

#include "PhysicsTools/JetMCUtils/interface/JetMCTag.h"
#include "PhysicsTools/JetMCUtils/interface/CandMCTag.h"
#include "SimDataFormats/JetMatching/interface/JetMatchedPartons.h"

#include "DataFormats/MuonReco/interface/MuonSelectors.h"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"

//Version > CMSSW_3_1_X
#include "SimTracker/TrackerHitAssociation/interface/TrackerHitAssociator.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include "Geometry/CommonDetUnit/interface/GeomDetType.h"
#include "Geometry/CommonDetUnit/interface/GeomDetUnit.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetUnit.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetType.h"
#include "DataFormats/SiPixelDetId/interface/PXBDetId.h"
#include "DataFormats/SiPixelDetId/interface/PXFDetId.h"
#include "DataFormats/SiPixelDetId/interface/PixelSubdetector.h"

#include "DataFormats/TrackingRecHit/interface/TrackingRecHitFwd.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHit.h"

#include "TrackingTools/TrackAssociator/interface/TrackDetectorAssociator.h"
#include "SimTracker/Records/interface/TrackAssociatorRecord.h"



class NJet {
public:
  NJet(); 
  ~NJet(); 

  void setup(const edm::ParameterSet&, TTree*);
  void analyze(const edm::Event&, const edm::EventSetup&, TTree*);

private:
  edm::InputTag jets_, jetIDs_, genjets_, genparticles_, met_, weight_tag;                   
  edm::InputTag ebrechits_, beamSpot_;
  edm::InputTag recTracks_, recMuons_, zspJets_;
  edm::InputTag genEvtScale_;
  std::string l2name_;
  std::string l3name_;
  std::string JPTname_;
  std::string l2l3name_;
  std::string l2l3JPTname_;
  double conesize_;
  float weight_;
  TrackDetectorAssociator trackAssociator_;
  TrackAssociatorParameters parameters_;

  //tree variables:
  const int kjMAX;               // Max number of jets stored in an event
  const int kMAX;                // Max number of towers/tracks/particles stored in an event
  const int kMaxStableGenPart_;  // Max number of stable gen particles stored in an event

  // Event info
  unsigned int runNumber_;
  unsigned int luminosityBlockNumber_;
  unsigned int eventNumber_;
  bool hltPhysicsDeclared_;
  int vtxNTracks_;
  float vtxPosX_, vtxPosY_, vtxPosZ_;
  float vtxNormalizedChi2_, vtxNDof_;
  bool vtxIsFake_;

  // Calo jets and jet ID
  int    minNumJets_;
  int    NobjJet;
  float *jetpt, *jetphi, *jeteta, *jetet, *jete, *jetgenjetDeltaR;
  int *n90Hits_;
  float *fHad_, *fEMF_, *fHPD_, *fRBX_;
  float *jetEtWeightedSigmaPhi_, *jetEtWeightedSigmaEta_;
  float *jscalel2, *jscalel3, *jscaleZSP, *jscaleJPT, *jscalel2l3, *jscalel2l3JPT;
  int *jetieta_, *jetiphi_;

  // Gen jets matched to calo jets
  float *genjetpt, *genjetphi, *genjeteta, *genjetet, *genjete;

  // Gen jet collection
  int    NobjGenJet;
  float *genjetcolpt, *genjetcolphi, *genjetcoleta, *genjetcolet, *genjetcole;
  float *genjetcoleme,*genjetcolhade,*genjetcolinve,*genjetcolauxe;
  int   *genjetcol_jet_idx;

  // Get jet particles
  int NobjGenJetPart;
  float *genjetparte,*genjetpartpt,*genjetparteta,*genjetpartphi;
  int *genjetpartpdg,*genjetpart_genjetcolidx;

  //duplicated for ALGO and PHYS Def
  float *genpartpt_algo, *genpartphi_algo, *genparteta_algo, *genpartet_algo, *genparte_algo, *genpartm_algo;
  int   *genpartid_algo;
  float *genpartpt_phys, *genpartphi_phys, *genparteta_phys, *genpartet_phys, *genparte_phys, *genpartm_phys;
  int   *genpartid_phys;

  int   NobjTow;
  float *towet, *toweta, *towphi, *towen, *towem, *towhd, *towoe;
  int   *towid_phi, *towid_eta, *towid, *tow_jetidx;
  float mmet, mphi, msum, weight;
  unsigned int *numBadEcalCells_, *numBadHcalCells_;
  unsigned int *numProblematicEcalCells_, *numProblematicHcalCells_;
  unsigned int *numRecoveredEcalCells_, *numRecoveredHcalCells_;

  int   NobjTrack;
  bool *trackQualityL, *trackQualityT, *trackQualityHP;
  float *trackpt, *tracketa, *trackphi, *trackp, *tracketaout, *trackphiout;
  float *trackdr, *trackdrout, *trackchi2, *trackd0, *trackz0;
  float *trackemc1, *trackemc3, *trackemc5;
  float *trackhac1, *trackhac3, *trackhac5;
  float *muDR, *muDE;
  int   *trackid, *tracktowid, *tracktowidphi, *tracktowideta, *tracknhits, *track_jetidx;

  // pthat
  float genEvtScale;

  // ECAL cells
  bool  writeEcalCells;
  int   NobjETowCal;
  int   *etowid_phi, *etowid_eta, *etowid, *etownum, *etow_towidx, *etow_jetidx;
  float *etowet, *etoweta, *etowphi, *etowe;

  // Stable gen particles
  bool    writeGenJetPart_;
  bool    writeStableGenPart_;
  int     NobjStableGenPart_;
  float * stableGenPartM_;
  float * stableGenPartE_;
  float * stableGenPartEt_;
  float * stableGenPartP_;
  float * stableGenPartPt_;
  float * stableGenPartEta_;
  float * stableGenPartPhi_;
  int   * stableGenPartPDGId_;
};

#endif
