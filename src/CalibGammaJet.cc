#include <iostream>
#include <sstream>
#include <istream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <functional>
#include <stdlib.h>
#include <string.h>

#include "Calibration/CalibTreeMaker/interface/CalibGammaJet.h"


/*  Setup the analysis to put the branch-variables into the tree. */
void CalibGammaJet::setup(const edm::ParameterSet& pSet, TTree* CalibTree) {

  //tower
  const int kMaxTower = 10000;
  towet = new float[kMaxTower];
  toweta = new float[kMaxTower];
  towphi = new float[kMaxTower];
  towen = new float[kMaxTower];
  towem = new float[kMaxTower];
  towhd = new float[kMaxTower];
  towoe = new float[kMaxTower];
  towid_phi = new int[kMaxTower];
  towid_eta = new int[kMaxTower];
  towid     = new int[kMaxTower];
  CalibTree->Branch("NobjTowCal",&NobjTowCal,"NobjTowCal/I");
  CalibTree->Branch("TowId",towid,"TowId[NobjTowCal]/I");
  CalibTree->Branch("TowId_phi",towid_phi,"TowId_phi[NobjTowCal]/I");
  CalibTree->Branch("TowId_eta",towid_eta,"TowId_eta[NobjTowCal]/I");
  CalibTree->Branch("TowEt",towet,"TowEt[NobjTowCal]/F");
  CalibTree->Branch("TowEta",toweta,"TowEta[NobjTowCal]/F");
  CalibTree->Branch("TowPhi",towphi,"TowPhi[NobjTowCal]/F");
  CalibTree->Branch("TowE",towen,"TowE[NobjTowCal]/F");
  CalibTree->Branch("TowEm",towem,"TowEm[NobjTowCal]/F");
  CalibTree->Branch("TowHad",towhd,"TowHad[NobjTowCal]/F");
  CalibTree->Branch("TowOE",towoe,"TowOE[NobjTowCal]/F");
  // Jet- MEt-specific branches of the tree 
  CalibTree->Branch("JetCalPt",&jcalpt,"JetCalPt/F");
  CalibTree->Branch("JetCalPhi",&jcalphi,"JetCalPhi/F");
  CalibTree->Branch("JetCalEta",&jcaleta,"JetCalEta/F");
  CalibTree->Branch("JetCalEt",&jcalet,"JetCalEt/F");
  CalibTree->Branch("JetCalE",&jcale,"JetCalE/F");
  // Gen- Jet- branches of the tree 
  CalibTree->Branch("JetGenPt",&jgenpt,"JetGenPt/F");
  CalibTree->Branch("JetGenPhi",&jgenphi,"JetGenPhi/F");
  CalibTree->Branch("JetGenEta",&jgeneta,"JetGenEta/F");
  CalibTree->Branch("JetGenEt",&jgenet,"JetGenEt/F");
  CalibTree->Branch("JetGenE",&jgene,"JetGenE/F");
  //met
  CalibTree->Branch("MetCal",&mcalmet,"MetCal/F");
  CalibTree->Branch("MetCalPhi",&mcalphi,"MetCalPhi/F");
  CalibTree->Branch("MetCalSum",&mcalsum,"MetCalSum/F");
  //photons
  CalibTree->Branch("PhotonPt",&photonpt,"PhotonPt/F");
  CalibTree->Branch("PhotonPhi",&photonphi,"PhotonPhi/F");
  CalibTree->Branch("PhotonEta",&photoneta,"PhotonEta/F");
  CalibTree->Branch("PhotonEt",&photonet,"PhtonEt/F");
  CalibTree->Branch("PhotonE",&photone,"PhotonE/F");

}

/* **Analyze the event** */
void CalibGammaJet::analyze(const CaloJet& calojet,
			    const GenJet&  genjet,
			    const CaloMETCollection& recmets,
			    const Photon& Photon,
			    const CaloTowerCollection& caloTowers,
			    const CaloGeometry& geom,
			    TTree* CalibTree) {

  jcalpt  = calojet.pt();
  jcalphi = calojet.phi();
  jcaleta = calojet.eta();
  jcalet  = calojet.et();
  jcale   = calojet.energy();
  std::vector <CaloTowerRef> j_towers = calojet.getConstituents ();
//cout << "jet phi="<<calojet.phi()<<", eta="<<calojet.eta()<<", pt="<<calojet.pt()<<endl;
  int jtow = 0;
  NobjTowCal=j_towers.size();
  for (std::vector <CaloTowerRef>::const_iterator tow = j_towers.begin();
       tow != j_towers.end(); ++tow, ++jtow){
     towet[jtow]     = (*tow)->et();
     toweta[jtow]    = (*tow)->eta();
     towphi[jtow]    = (*tow)->phi();
     towen[jtow]     = (*tow)->energy();
     towem[jtow]     = (*tow)->emEnergy();
     towhd[jtow]     = (*tow)->hadEnergy();
     towoe[jtow]     = (*tow)->outerEnergy();
     towid_phi[jtow] = (*tow)->id().iphi();
     towid_eta[jtow] = (*tow)->id().ieta();
     towid[jtow]     = (*tow)->id().rawId();
//cout << "    phi=" << (*tow)->phi() << ", eta="<< (*tow)->eta() 
//     << ",   iphi=" << (*tow)->id().iphi() << ", ieta="<< (*tow)->id().ieta()
//     << ",   id="<< (*tow)->id().rawId()
//     << endl;;
  }

  jgenpt  = genjet.pt();
  jgenphi = genjet.phi();
  jgeneta = genjet.eta();
  jgenet  = genjet.et();
  jgene   = genjet.energy();

  photonpt  = Photon.pt();
  photonphi = Photon.phi();
  photoneta = Photon.eta();
  photonet  = Photon.et();
  photone   = Photon.energy();

  if (&recmets) {
    typedef CaloMETCollection::const_iterator cmiter;
    for ( cmiter i=recmets.begin(); i!=recmets.end(); i++) {
      mcalmet = i->pt();
      mcalphi = i->phi();
      mcalsum = i->sumEt();
      break;
    }
  }
  
  CalibTree->Fill();

}
