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


#include "FWCore/Framework/interface/Event.h"
//#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

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
  void analyze(const edm::Event& iEvent, 
               const edm::EventSetup& iSetup, 
	       TTree* CalibTree);

private:
  edm::InputTag jets_,genjets_,met_,alltowers_,photon_;                    
  edm::InputTag EBrechitCollection_;
 
  // Tree variables
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
};

#endif
