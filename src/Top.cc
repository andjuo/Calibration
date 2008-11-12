#include "Calibration/CalibTreeMaker/interface/Top.h"
#include "DataFormats/METReco/interface/CaloMET.h"


void Top::setup(const edm::ParameterSet& cfg, TTree* CalibTree)
{
  bjets_   = cfg.getParameter<edm::InputTag>("TopHadBJets");
  wjets_   = cfg.getParameter<edm::InputTag>("TopHadWJets");
  weight_  = cfg.getParameter<edm::InputTag>("Top_Weight");

  //tower for all W-jets
  const int kMAX = 10000;
  wtowet  = new float [ kMAX ];
  wtoweta = new float [ kMAX ];
  wtowphi = new float [ kMAX ];
  wtowen  = new float [ kMAX ];
  wtowem  = new float [ kMAX ];
  wtowhd  = new float [ kMAX ];
  wtowoe  = new float [ kMAX ];
  wtowid_phi = new int[ kMAX ];
  wtowid_eta = new int[ kMAX ];
  wtowid     = new int[ kMAX ];
  wtow_jetidx= new int[ kMAX ];
  // CaloTower branches for W-Jets
  CalibTree->Branch( "NobjWTow", &NobjWTow,"NobjWTow/I"             );
  CalibTree->Branch( "WTowId",     wtowid,      "WTowId[NobjWTow]/I"    );
  CalibTree->Branch( "WTowId_phi", wtowid_phi,  "WTowId_phi[NobjWTow]/I");
  CalibTree->Branch( "WTowId_eta", wtowid_eta,  "WTowId_eta[NobjWTow]/I");
  CalibTree->Branch( "WTowEt",     wtowet,      "WTowEt[NobjWTow]/F"    );
  CalibTree->Branch( "WTowEta",    wtoweta,     "WTowEta[NobjWTow]/F"   );
  CalibTree->Branch( "WTowPhi",    wtowphi,     "WTowPhi[NobjWTow]/F"   );
  CalibTree->Branch( "WTowE",      wtowen,      "WTowE[NobjWTow]/F"     );
  CalibTree->Branch( "WTowEm",     wtowem,      "WTowEm[NobjWTow]/F"    );
  CalibTree->Branch( "WTowHad",    wtowhd,      "WTowHad[NobjWTow]/F"   );
  CalibTree->Branch( "WTowOE",     wtowoe,      "WTowOE[NobjWTow]/F"    );
  CalibTree->Branch( "WTow_jetidx",wtow_jetidx, "WTow_jetidx[NobjWTow]/I");
  //All W-jets
  const int kjMAX = 8;
  wjetpt  = new float [ kjMAX ];
  wjetphi = new float [ kjMAX ];
  wjeteta = new float [ kjMAX ];
  wjetet  = new float [ kjMAX ];
  wjete   = new float [ kjMAX ];
  // W-Jet-specific branches of the tree 
  CalibTree->Branch( "NobjWJet",&NobjWJet,"NobjWJet/I"             );
  CalibTree->Branch( "WJetPt", wjetpt, "WJetPt[NobjWJet]/F" );
  CalibTree->Branch( "WJetPhi",wjetphi,"WJetPhi[NobjWJet]/F");
  CalibTree->Branch( "WJetEta",wjeteta,"WJetEta[NobjWJet]/F");
  CalibTree->Branch( "WJetEt", wjetet, "WJetEt[NobjWJet]/F" );
  CalibTree->Branch( "WJetE",  wjete,  "WJetE[NobjWJet]/F"  );

  //tower for all b-jets
  btowet  = new float [ kMAX ];
  btoweta = new float [ kMAX ];
  btowphi = new float [ kMAX ];
  btowen  = new float [ kMAX ];
  btowem  = new float [ kMAX ];
  btowhd  = new float [ kMAX ];
  btowoe  = new float [ kMAX ];
  btowid_phi = new int[ kMAX ];
  btowid_eta = new int[ kMAX ];
  btowid     = new int[ kMAX ];
  btow_jetidx= new int[ kMAX ];
  // CaloTower branches for b-Jets
  CalibTree->Branch( "NobjBTow", &NobjBTow,"NobjBTow/I"             );
  CalibTree->Branch( "BTowId",     btowid,      "BTowId[NobjBTow]/I"    );
  CalibTree->Branch( "BTowId_phi", btowid_phi,  "BTowId_phi[NobjBTow]/I");
  CalibTree->Branch( "BTowId_eta", btowid_eta,  "BTowId_eta[NobjBTow]/I");
  CalibTree->Branch( "BTowEt",     btowet,      "BTowEt[NobjBTow]/F"    );
  CalibTree->Branch( "BTowEta",    btoweta,     "BTowEta[NobjBTow]/F"   );
  CalibTree->Branch( "BTowPhi",    btowphi,     "BTowPhi[NobjBTow]/F"   );
  CalibTree->Branch( "BTowE",      btowen,      "BTowE[NobjBTow]/F"     );
  CalibTree->Branch( "BTowEm",     btowem,      "BTowEm[NobjBTow]/F"    );
  CalibTree->Branch( "BTowHad",    btowhd,      "BTowHad[NobjBTow]/F"   );
  CalibTree->Branch( "BTowOE",     btowoe,      "BTowOE[NobjBTow]/F"    );
  CalibTree->Branch( "BTow_jetidx",btow_jetidx, "BTow_jetidx[NobjBTow]/I");
  //All b-jets
  wjetpt  = new float [ kjMAX ];
  wjetphi = new float [ kjMAX ];
  wjeteta = new float [ kjMAX ];
  wjetet  = new float [ kjMAX ];
  wjete   = new float [ kjMAX ];
  // b-Jet-specific branches of the tree 
  CalibTree->Branch( "NobjBJet",&NobjBJet,"NobjBJet/I"             );
  CalibTree->Branch( "BJetPt", wjetpt, "BJetPt[NobjBJet]/F" );
  CalibTree->Branch( "BJetPhi",wjetphi,"BJetPhi[NobjBJet]/F");
  CalibTree->Branch( "BJetEta",wjeteta,"BJetEta[NobjBJet]/F");
  CalibTree->Branch( "BJetEt", wjetet, "BJetEt[NobjBJet]/F" );
  CalibTree->Branch( "BJetE",  wjete,  "BJetE[NobjBJet]/F"  );

  //EventWeight
  CalibTree->Branch( "Weight",&weight,"Weight/F"   );
}

void Top::analyze(const edm::Event& evt, const edm::EventSetup& setup, TTree* CalibTree)
{
  //Event Weighting
  //double weight = 1.; 
  edm::Handle<double> weightHandle;
  evt.getByLabel (weight_, weightHandle);
  weight = (float)( *weightHandle );

  edm::Handle<reco::CaloJetCollection> pBJets;
  //edm::Handle<edm::View<reco::Jet> > pBJets;
  evt.getByLabel(bjets_, pBJets);

  edm::Handle<reco::CaloJetCollection> pWJets;
  //edm::Handle<edm::View<reco::Jet> > pWJets;
  evt.getByLabel(wjets_, pWJets);

  //Need 2*n W-jets and n B-jets, where n is the number of hypotheses
  if (pWJets->size()%2!=0 || pWJets->size()%pBJets->size()!=0)
    return;

  //Filling W-jets
  NobjWTow=0;
  NobjWJet = pWJets->size();
  unsigned int towno = 0;
  for (unsigned int jtno = 0; jtno<pWJets->size(); ++jtno)
  {
    wjetpt[  jtno ] = (*pBJets)[jtno].pt();
    wjetphi[ jtno ] = (*pBJets)[jtno].phi();
    wjeteta[ jtno ] = (*pBJets)[jtno].eta();
    wjetet[  jtno ] = (*pBJets)[jtno].et();
    wjete[   jtno ] = (*pBJets)[jtno].energy();

    // uncomment for CMSSW_2_1_X compatibility
    std::vector<CaloTowerPtr> j_towers = (*pBJets)[jtno].getCaloConstituents();
    NobjWTow+=j_towers.size();
    for (std::vector<CaloTowerPtr>::const_iterator tow = j_towers.begin(); 
	 tow != j_towers.end(); ++tow, ++towno){

// uncomment for CMSSW_2_0_X compatibility
//    std::vector<CaloTowerRef> j_towers = (*pBJets)[jtno].getConstituents(); 
//    NobjTow+=j_towers.size();
//    for (std::vector<CaloTowerRef>::const_iterator tow = j_towers.begin(); 
//         tow != j_towers.end(); ++tow, ++towno){

      wtowet[towno]     = (*tow)->et();
      wtoweta[towno]    = (*tow)->eta();
      wtowphi[towno]    = (*tow)->phi();
      wtowen[towno]     = (*tow)->energy();
      wtowem[towno]     = (*tow)->emEnergy();
      wtowhd[towno]     = (*tow)->hadEnergy();
      wtowoe[towno]     = (*tow)->outerEnergy();
      wtowid_phi[towno] = (*tow)->id().iphi();
      wtowid_eta[towno] = (*tow)->id().ieta();
      wtowid[towno]     = (*tow)->id().rawId();
      wtow_jetidx[towno]= jtno;
    }
  }

  //Filling b-jets
  NobjBTow=0;
  NobjBJet = pBJets->size();
  towno = 0;
  for (unsigned int jtno = 0; jtno<pBJets->size(); ++jtno)
  {
    bjetpt[  jtno ] = (*pBJets)[jtno].pt();
    bjetphi[ jtno ] = (*pBJets)[jtno].phi();
    bjeteta[ jtno ] = (*pBJets)[jtno].eta();
    bjetet[  jtno ] = (*pBJets)[jtno].et();
    bjete[   jtno ] = (*pBJets)[jtno].energy();

    // uncomment for CMSSW_2_1_X compatibility
    std::vector<CaloTowerPtr> j_towers = (*pBJets)[jtno].getCaloConstituents();
    NobjBTow+=j_towers.size();
    for (std::vector<CaloTowerPtr>::const_iterator tow = j_towers.begin(); 
	 tow != j_towers.end(); ++tow, ++towno){

// uncomment for CMSSW_2_0_X compatibility
//    std::vector<CaloTowerRef> j_towers = (*pBJets)[jtno].getConstituents(); 
//    NobjTow+=j_towers.size();
//    for (std::vector<CaloTowerRef>::const_iterator tow = j_towers.begin(); 
//         tow != j_towers.end(); ++tow, ++towno){

      btowet[towno]     = (*tow)->et();
      btoweta[towno]    = (*tow)->eta();
      btowphi[towno]    = (*tow)->phi();
      btowen[towno]     = (*tow)->energy();
      btowem[towno]     = (*tow)->emEnergy();
      btowhd[towno]     = (*tow)->hadEnergy();
      btowoe[towno]     = (*tow)->outerEnergy();
      btowid_phi[towno] = (*tow)->id().iphi();
      btowid_eta[towno] = (*tow)->id().ieta();
      btowid[towno]     = (*tow)->id().rawId();
      btow_jetidx[towno]= jtno;
    }
  }

  CalibTree->Fill();
}
