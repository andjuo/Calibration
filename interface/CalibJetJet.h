#ifndef CalibJetJet_H
#define CalibJetJet_H

#include "TFile.h"
#include "TNamed.h"
#include <vector>
#include <map>
#include "TROOT.h"
#include "TChain.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/CaloJetfwd.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/GenJetfwd.h"
#include "DataFormats/METReco/interface/CaloMETCollection.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"

//#include "DataFormats/Candidate/interface/Candidate.h"

/** \class CalibJetJet
  *  
  * $Date: July 2007
  * \author Christian Autermann
  * original code by L. Apanasevich - UIC, P. Bargassa - Rice U.
  */
class CalibJetJet {
public:
  CalibJetJet(){}; 
  ~CalibJetJet(){}; 

  void setup(const edm::ParameterSet& pSet, TTree* tree);

  /** Analyze the Data */
  void analyze(const reco::CaloJetCollection& rjet,
	       const reco::GenJetCollection&  gjet,
	       const CaloMETCollection& rmets,
	       const CaloTowerCollection& caloTowers,
	       TTree* tree);

private:

  // Tree variables
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
