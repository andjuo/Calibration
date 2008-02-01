#include "Calibration/CalibTreeMaker/interface/TrackTower.h"

void TrackTower::setup(const edm::ParameterSet& cfg, TTree* CalibTree)
{
  track_    = cfg.getParameter<edm::InputTag>("TrackTowerTracks");
  tower_    = cfg.getParameter<edm::InputTag>("TrackTowerTowers");

  //tower data
  const int kMAX = 10000;
  towet  = new float [ kMAX ];
  toweta = new float [ kMAX ];
  towphi = new float [ kMAX ];
  towen  = new float [ kMAX ];
  towem  = new float [ kMAX ];
  towhd  = new float [ kMAX ];
  towoe  = new float [ kMAX ];
  towid_phi = new int[ kMAX ];
  towid_eta = new int[ kMAX ];
  towid     = new int[ kMAX ];

  // CaloTower branches
  CalibTree->Branch( "NobjTowCal",&NobjTowCal,"NobjTowCal/I"            );
  CalibTree->Branch( "TowId",     towid,      "TowId[NobjTowCal]/I"     );
  CalibTree->Branch( "TowId_phi", towid_phi,  "TowId_phi[NobjTowCal]/I" );
  CalibTree->Branch( "TowId_eta", towid_eta,  "TowId_eta[NobjTowCal]/I" );
  CalibTree->Branch( "TowEt",     towet,      "TowEt[NobjTowCal]/F"     );
  CalibTree->Branch( "TowEta",    toweta,     "TowEta[NobjTowCal]/F"    );
  CalibTree->Branch( "TowPhi",    towphi,     "TowPhi[NobjTowCal]/F"    );
  CalibTree->Branch( "TowE",      towen,      "TowE[NobjTowCal]/F"      );
  CalibTree->Branch( "TowEm",     towem,      "TowEm[NobjTowCal]/F"     );
  CalibTree->Branch( "TowHad",    towhd,      "TowHad[NobjTowCal]/F"    );
  CalibTree->Branch( "TowOE",     towoe,      "TowOE[NobjTowCal]/F"     );
  // Tracks branches
  CalibTree->Branch( "TrackEt",   &tracket,   "TrackEt/F"   );
  CalibTree->Branch( "TrackEterr",&tracketerr,"TrackEterr/F");
  CalibTree->Branch( "TrackEta",  &tracketa,  "TrackEta/F"  );
  CalibTree->Branch( "TrackPhi",  &trackphi,  "TrackPhi/F"  );
  CalibTree->Branch( "TrackE",    &tracken,   "TrackE/F"    );
}

void TrackTower::analyze(const edm::Event& evt, const edm::EventSetup& setup, TTree* CalibTree)
{
  edm::Handle<reco::Track> track;
  evt.getByLabel(track_, track);

  edm::Handle<CaloTowerCollection> towers;
  evt.getByLabel(tower_, towers);

  if(!(track->p()>0 && towers->size()>0)) return;
  tracket  = track->pt ();
  tracketa = track->eta();
  trackphi = track->phi();
  tracken  = track->p  ();
  
  int jtow = 0;
  NobjTowCal=towers->size();
  for(CaloTowerCollection::const_iterator tow = towers->begin();
      tow != towers->end(); ++tow, ++jtow){
    towet [jtow] = tow->et();
    toweta[jtow] = tow->eta();
    towphi[jtow] = tow->phi();
    towen [jtow] = tow->energy();
    towem [jtow] = tow->emEnergy();
    towhd [jtow] = tow->hadEnergy();
    towoe [jtow] = tow->outerEnergy();
    towid_phi[jtow] = tow->id().iphi();
    towid_eta[jtow] = tow->id().ieta();
    towid [jtow] = tow->id().rawId();
  }
  CalibTree->Fill();
}
