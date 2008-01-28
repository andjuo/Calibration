#include <iostream>
#include <sstream>
#include <istream>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <cmath>
#include <functional>
#include <stdlib.h>
#include <string.h>

#include "FWCore/Utilities/interface/Exception.h"
#include "Calibration/CalibTreeMaker/interface/CalibTrackCluster.h"


/*  Setup the analysis to put the branch-variables into the tree. */
void CalibTrackCluster::setup(const edm::ParameterSet& pSet, TTree* CalibTree) {

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
  // tracks
  CalibTree->Branch("TrackEt",&tracket,"TrackEt/F");
  CalibTree->Branch("TrackEterr",&tracketerr,"TrackEterr/F");
  CalibTree->Branch("TrackEta",&tracketa,"TrackEta/F");
  CalibTree->Branch("TrackPhi",&trackphi,"TrackPhi/F");
  CalibTree->Branch("TrackE",&tracken,"TrackE/F");
}

/* **Analyze the event** */
void CalibTrackCluster::analyze(const reco::TrackCollection& tracks,
			    const CaloTowerCollection& towers,
			    TTree* CalibTree) {
  //tracks
  if (tracks.size()>1) {
    throw cms::Exception("Unexpected size of TrackCollection!");
  };
  for (reco::TrackCollection::const_iterator track = tracks.begin();
       track != tracks.end(); ++track){
     tracket     = track->pt();
     tracketa    = track->eta();
     trackphi    = track->phi();
     tracken     = track->p();
  }
  
  //tower
  int jtow = 0;
  NobjTowCal=towers.size();
  for (CaloTowerCollection::const_iterator tow = towers.begin();
       tow != towers.end(); ++tow, ++jtow){
     towet[jtow]     = tow->et();
     toweta[jtow]    = tow->eta();
     towphi[jtow]    = tow->phi();
     towen[jtow]     = tow->energy();
     towem[jtow]     = tow->emEnergy();
     towhd[jtow]     = tow->hadEnergy();
     towoe[jtow]     = tow->outerEnergy();
     towid_phi[jtow] = tow->id().iphi();
     towid_eta[jtow] = tow->id().ieta();
     towid[jtow]     = tow->id().rawId();
  }

  CalibTree->Fill();
}
