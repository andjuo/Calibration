#ifndef Top_H
#define Top_H

#include <string>
#include <vector>
#include <iostream>

#include "TChain.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

class Top {
public:
  Top(){}; 
  ~Top(){}; 

  void setup(const edm::ParameterSet&, TTree*);
  void analyze(const edm::Event&, const edm::EventSetup&, TTree*);

private:

  void fillRecJet(const reco::Jet& recJet, const unsigned int jtno, const unsigned int flavor, const unsigned int topid);
  void fillTowers(const std::vector<CaloTowerPtr> &towers, unsigned int &towno, const unsigned int jtno);
  void fillCorrFactors(const pat::Jet &jet, const unsigned int jtno, const std::string &flavor);
  void fillGenJet(const reco::GenJet &genJet, const unsigned int jtno);

  edm::InputTag wjets_, bjets_, wgenjets_, bgenjets_, weight_tag;

  //tree variables
  int   NobjJet, *jetflavor, *jettopid;
  float *jetpt, *jetphi, *jeteta, *jetet, *jete;
  float *jscaleL1, *jscaleL2, *jscaleL3, *jscaleL4, *jscaleL5;
  float *genjetpt, *genjetphi, *genjeteta, *genjetet, *genjete;
  int   NobjTow;
  float *towet, *toweta, *towphi, *towen, *towem, *towhd, *towoe;
  int   *towid_phi, *towid_eta, *towid, *tow_jetidx;

  float weight;
};

#endif
