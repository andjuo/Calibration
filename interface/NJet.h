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

class NJet {
public:
  NJet(){}; 
  ~NJet(){}; 

  void setup(const edm::ParameterSet&, TTree*);
  void analyze(const edm::Event&, const edm::EventSetup&, TTree*);

private:
  edm::InputTag jets_, genjets_, met_, weight_tag;                   
  edm::InputTag ebrechits_;
  edm::InputTag recTracks_, recMuons_;
  double conesize_;
  TrackDetectorAssociator trackAssociator_;
  TrackAssociatorParameters parameters_;

  //tree variables
  int   NobjJet;
  float *jetpt, *jetphi, *jeteta, *jetet, *jete, *jscalel2, *jscalel3;
  int   NobjTow;
  float *towet, *toweta, *towphi, *towen, *towem, *towhd, *towoe;
  int   *towid_phi, *towid_eta, *towid, *tow_jetidx;
  float mmet, mphi, msum, weight;
  int   NobjTrack;
  float *trackpt, *tracketa, *trackphi, *trackp, *tracketaout, *trackphiout;
  float *trackdr, *trackdrout, *trackchi2;
  float *trackemc1, *trackemc3, *trackemc5;
  float *trackhac1, *trackhac3, *trackhac5;
  float *muDR, *muDE;
  int   *trackid, *tracktowid, *tracktowidphi, *tracktowideta, *tracknhits, *track_jetidx;
};

#endif
