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
  edm::InputTag wjets_, bjets_, weight_;

  //tree variables
  int   NobjWJet;
  float *wjetpt, *wjetphi, *wjeteta, *wjetet, *wjete;
  int   NobjWTow;
  float *wtowet, *wtoweta, *wtowphi, *wtowen, *wtowem, *wtowhd, *wtowoe;
  int   *wtowid_phi, *wtowid_eta, *wtowid, *wtow_jetidx;

  int   NobjBJet;
  float *bjetpt, *bjetphi, *bjeteta, *bjetet, *bjete;
  int   NobjBTow;
  float *btowet, *btoweta, *btowphi, *btowen, *btowem, *btowhd, *btowoe;
  int   *btowid_phi, *btowid_eta, *btowid, *btow_jetidx;

  float weight;
};

#endif
