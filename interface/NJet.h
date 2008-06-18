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
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/METReco/interface/CaloMETCollection.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"

class NJet {
public:
  NJet(){}; 
  ~NJet(){}; 

  void setup(const edm::ParameterSet&, TTree*);
  void analyze(const edm::Event&, const edm::EventSetup&, TTree*);

private:
  edm::InputTag jets_, genjets_, met_, weight_;

  //tree variables
  int   NobjJet;
  float *jetpt, *jetphi, *jeteta, *jetet, *jete;
  int   NobjTow;
  float *towet, *toweta, *towphi, *towen, *towem, *towhd, *towoe;
  int   *towid_phi, *towid_eta, *towid, *tow_jetidx;
  float mmet, mphi, msum, weight;
};

#endif
