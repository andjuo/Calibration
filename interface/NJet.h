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

class NJet {
public:
  NJet(); 
  ~NJet(); 

  void setup(const edm::ParameterSet&, TTree*);
  void analyze(const edm::Event&, const edm::EventSetup&, TTree*);

private:
  edm::InputTag jets_, genjets_, genparticles_, met_, weight_tag;                   
  edm::InputTag ebrechits_;
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
  const int kMAX;                // Max number of towers stored in an event
  const int kMaxStableGenPart_;  // Max number of stable gen particles stored in an event

  bool isData_;

  // Calo jets
  int    NobjJet;
  float *jetpt, *jetphi, *jeteta, *jetet, *jete, *jetgenjetDeltaR;
  float *jscalel2, *jscalel3, *jscaleZSP, *jscaleJPT, *jscalel2l3, *jscalel2l3JPT;

  // Gen jets matched to calo jets
  float *genjetpt, *genjetphi, *genjeteta, *genjetet, *genjete;

  // Gen jet collection
  int    NobjGenJet;
  float *genjetcolpt, *genjetcolphi, *genjetcoleta, *genjetcolet, *genjetcole;
  int   *genjetcol_jet_idx;

  //duplicated for ALGO and PHYS Def
  float *genpartpt_algo, *genpartphi_algo, *genparteta_algo, *genpartet_algo, *genparte_algo, *genpartm_algo;
  int   *genpartid_algo;
  float *genpartpt_phys, *genpartphi_phys, *genparteta_phys, *genpartet_phys, *genparte_phys, *genpartm_phys;
  int   *genpartid_phys;

  int   NobjTow;
  float *towet, *toweta, *towphi, *towen, *towem, *towhd, *towoe;
  int   *towid_phi, *towid_eta, *towid, *tow_jetidx;
  float mmet, mphi, msum, weight;
  int   NobjTrack;
  bool *trackQualityL, *trackQualityT, *trackQualityHP;
  float *trackpt, *tracketa, *trackphi, *trackp, *tracketaout, *trackphiout;
  float *trackdr, *trackdrout, *trackchi2;
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
