#ifndef TrackTower_H
#define TrackTower_H

#include <string>
#include <vector>
#include <iostream>

#include "TFile.h"
#include "TNamed.h"
#include "TChain.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"

class TrackTower {
public:
  TrackTower(){}; 
  ~TrackTower(){}; 

  void setup(const edm::ParameterSet&, TTree*);
  void analyze(const edm::Event&, const edm::EventSetup&, TTree*);

private:
  edm::InputTag track_, tower_;

  // tree variables
  float tracket, tracketerr, tracketa, trackphi, tracken;
  float *towet, *toweta, *towphi, *towen, *towem, *towhd, *towoe;
  int   NobjTowCal,NobjTrackCal;
  int   *towid_phi, *towid_eta, *towid;
};

#endif
