#ifndef CalibGammaJet_H
#define CalibGammaJet_H

#include "TH1.h"
#include "TH2.h"
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
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/METReco/interface/CaloMETCollection.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"

/** \class CalibGammaJet
  *  
  * $Date: July 2007
  * \author Christian Autermann
  * original code by L. Apanasevich - UIC, P. Bargassa - Rice U.
  */
class CalibGammaJet {
public:
  CalibGammaJet(){}; 
  ~CalibGammaJet(){}; 

  void setup(const edm::ParameterSet& pSet, TTree* tree);

  /** Analyze the Data */
  void analyze(const CaloJet& rjet,
	       const GenJet&  gjet,
	       const CaloMETCollection& rmets,
	       const Photon& photon,
	       const CaloTowerCollection& caloTowers,
	       const CaloGeometry& geom,
	       TTree* tree);

private:

  // Tree variables
  float jcalpt, jcalphi, jcaleta, jcalet, jcale;
  float jgenpt, jgenphi, jgeneta, jgenet, jgene;
  float *towet, *toweta, *towphi, *towen, *towem, *towhd, *towoe;
  float mcalmet,mcalphi,mcalsum;
  float photonpt, photonphi, photoneta, photonet, photone; 
  int   NobjTowCal;
  int   *towid_phi, *towid_eta, *towid;
};

#endif
