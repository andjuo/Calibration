#ifndef Top_H
#define Top_H

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

class Top {
public:
  Top(){}; 
  ~Top(){}; 

  void setup(const edm::ParameterSet&, TTree*);
  void analyze(const edm::Event&, const edm::EventSetup&, TTree*);

private:
  edm::InputTag wjets_, bjets_, genjets_, weight_tag;

  //tree variables
  int   NobjJet, *jetflavor, *jettopid;
  float *jetpt, *jetphi, *jeteta, *jetet, *jete;
  float *genjetpt, *genjetphi, *genjeteta, *genjetet, *genjete;
  int   NobjTow;
  float *towet, *toweta, *towphi, *towen, *towem, *towhd, *towoe;
  int   *towid_phi, *towid_eta, *towid, *tow_jetidx;

  float weight;
};

#endif
