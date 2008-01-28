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

#include "Calibration/CalibTreeMaker/interface/CalibTrackTower.h"


/*  Setup the analysis to put the branch-variables into the tree. */
void CalibTrackTower::setup(const edm::ParameterSet& pSet, TTree* CalibTree) {

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
  const int kMaxTracks = 10000;
  tracket = new float[kMaxTracks];
  tracketa = new float[kMaxTracks];
  trackphi = new float[kMaxTracks];
  tracken = new float[kMaxTracks];
  tracketerr = new float[kMaxTracks];
  CalibTree->Branch("NobjTrackCal",&NobjTrackCal,"NobjTrackCal/I");
  CalibTree->Branch("TrackEt",tracket,"TrackEt[NobjTrackCal]/F");
  CalibTree->Branch("TrackEterr",tracketerr,"TrackEterr[NobjTrackCal]/F");
  CalibTree->Branch("TrackEta",tracketa,"TrackEta[NobjTrackCal]/F");
  CalibTree->Branch("TrackPhi",trackphi,"TrackPhi[NobjTrackCal]/F");
  CalibTree->Branch("TrackE",tracken,"TrackE[NobjTrackCal]/F");
}

/* **Analyze the event** */
void CalibTrackTower::analyze(const reco::TrackCollection& tracks,
			    const CaloTowerCollection& towers,
			    TTree* CalibTree) {
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
//cout << "    phi=" << (*tow)->phi() << ", eta="<< (*tow)->eta() 
//     << ",   iphi=" << (*tow)->id().iphi() << ", ieta="<< (*tow)->id().ieta()
//     << ",   id="<< (*tow)->id().rawId()
//     << endl;;
  }

  //tracks
  int jtrack = 0;
  NobjTrackCal=tracks.size();
  for (reco::TrackCollection::const_iterator track = tracks.begin();
       track != tracks.end(); ++track, ++jtrack){
     tracket[jtrack]     = track->pt();
     tracketa[jtrack]    = track->eta();
     trackphi[jtrack]    = track->phi();
     tracken[jtrack]     = track->p();
     //tracketerr[jtrack]  = track->ptError();//Not  yet in CMSSW_1_3_5
//cout << "    phi=" << (*track)->phi() << ", eta="<< (*track)->eta() 
//     << endl;;
  }

  CalibTree->Fill();
}
