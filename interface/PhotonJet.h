#ifndef PhotonJet_H
#define PhotonJet_H

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
#include "DataFormats/Common/interface/Handle.h"

#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/METReco/interface/CaloMETCollection.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"

class PhotonJet {
public:
  PhotonJet(){}; 
  ~PhotonJet(){}; 

  void setup(const edm::ParameterSet&, TTree*);
  void analyze(const edm::Event&, const edm::EventSetup&, TTree*);

private:
  edm::InputTag jets_,genjets_,met_,photon_;                    
  edm::InputTag ebrechits_;

  //tree variables
  float jcalpt, jcalphi, jcaleta, jcalet, jcale;
  float jgenpt, jgenphi, jgeneta, jgenet, jgene;
  float mcalmet,mcalphi,mcalsum;
  float photonpt, photonphi, photoneta, photonet, photone; 
  int   NobjTowCal;
  int   *towid_phi, *towid_eta, *towid, *townum;
  float *towet, *toweta, *towphi, *towen, *towem, *towhd, *towoe;
  int   NobjETowCal;
  int   *etowid_phi, *etowid_eta, *etowid, *etownum;
  float *etowet, *etoweta, *etowphi, *etowe;
  float eventweight;
  int   processid;
};

#endif
