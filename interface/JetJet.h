#ifndef JetJet_H
#define JetJet_H

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

//
// class decleration
//
class PtGreater {
public:
  template <typename T> bool operator () (const T& i, const T& j) {
    return (i.pt() > j.pt());
  }
};

class JetJet {
public:
  JetJet(){}; 
  ~JetJet(){}; 

  void setup(const edm::ParameterSet&, TTree*);
  void analyze(const edm::Event&, const edm::EventSetup&, TTree*);

private:
  edm::InputTag jets_, genjets_, met_;
  double etaMaxTag_, etaMaxProbe_, PtMin_, sumPtMaxFracThird_, deltaPhiJetMax_, deltaPhiMETMax_;
  double minEMF_, maxEMF_;

  //tree variables
  float fstjetpt, fstjetphi, fstjeteta, fstjetet, fstjete;
  float scdjetpt, scdjetphi, scdjeteta, scdjetet, scdjete;
  float fstgenjetpt, fstgenjetphi, fstgenjeteta, fstgenjetet, fstgenjete;
  float scdgenjetpt, scdgenjetphi, scdgenjeteta, scdgenjetet, scdgenjete;
  float mcalmet,mcalphi,mcalsum;
  int   NobjTowJ1Cal,NobjTowJ2Cal;
  float *towj1et, *towj1eta, *towj1phi, *towj1en, *towj1em, *towj1hd, *towj1oe;
  float *towj2et, *towj2eta, *towj2phi, *towj2en, *towj2em, *towj2hd, *towj2oe;
  int   *towj1id_phi, *towj1id_eta, *towj1id;
  int   *towj2id_phi, *towj2id_eta, *towj2id;
};

#endif
