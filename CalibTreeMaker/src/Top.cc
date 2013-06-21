#include "Calibration/CalibTreeMaker/interface/Top.h"

void Top::setup(const edm::ParameterSet& cfg, TTree* CalibTree)
{
  bjets_     = cfg.getParameter<edm::InputTag> ("TopHadBJets");
  wjets_     = cfg.getParameter<edm::InputTag> ("TopHadWJets");
  bgenjets_  = cfg.getParameter<edm::InputTag> ("TopHadBGenJets");
  wgenjets_  = cfg.getParameter<edm::InputTag> ("TopHadWGenJets");
  weight     = (float)(cfg.getParameter<double>("Top_Weight"));
  weight_tag = cfg.getParameter<edm::InputTag> ("Top_Weight_Tag");

  // CaloTowers
  int kMAX = 10000;
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
  tow_jetidx= new int[ kMAX ];
  CalibTree->Branch( "NobjTow", &NobjTow,"NobjTow/I"             );
  CalibTree->Branch( "TowId",     towid,      "TowId[NobjTow]/I"    );
  CalibTree->Branch( "TowId_phi", towid_phi,  "TowId_phi[NobjTow]/I");
  CalibTree->Branch( "TowId_eta", towid_eta,  "TowId_eta[NobjTow]/I");
  CalibTree->Branch( "TowEt",     towet,      "TowEt[NobjTow]/F"    );
  CalibTree->Branch( "TowEta",    toweta,     "TowEta[NobjTow]/F"   );
  CalibTree->Branch( "TowPhi",    towphi,     "TowPhi[NobjTow]/F"   );
  CalibTree->Branch( "TowE",      towen,      "TowE[NobjTow]/F"     );
  CalibTree->Branch( "TowEm",     towem,      "TowEm[NobjTow]/F"    );
  CalibTree->Branch( "TowHad",    towhd,      "TowHad[NobjTow]/F"   );
  CalibTree->Branch( "TowOE",     towoe,      "TowOE[NobjTow]/F"    );
  CalibTree->Branch( "Tow_jetidx",tow_jetidx, "Tow_jetidx[NobjTow]/I");
  // RecoJets
  int kjMAX = 8;
  jetpt  = new float [ kjMAX ];
  jetphi = new float [ kjMAX ];
  jeteta = new float [ kjMAX ];
  jetet  = new float [ kjMAX ];
  jete   = new float [ kjMAX ];
  jetflavor = new int[ kjMAX ];
  jettopid  = new int[ kjMAX ];
  jscaleL1  = new float[ kjMAX ];
  jscaleL2  = new float[ kjMAX ];
  jscaleL3  = new float[ kjMAX ];
  jscaleL4  = new float[ kjMAX ];
  jscaleL5  = new float[ kjMAX ];
  for(int i = 0; i < kjMAX; i++) {
    jscaleL1[i] = 1.;
    jscaleL2[i] = 1.;
    jscaleL3[i] = 1.;
    jscaleL4[i] = 1.;
    jscaleL5[i] = 1.;
  }
  CalibTree->Branch( "NobjJet",&NobjJet,"NobjJet/I"     );
  CalibTree->Branch( "JetPt", jetpt, "JetPt[NobjJet]/F" );
  CalibTree->Branch( "JetPhi",jetphi,"JetPhi[NobjJet]/F");
  CalibTree->Branch( "JetEta",jeteta,"JetEta[NobjJet]/F");
  CalibTree->Branch( "JetEt", jetet, "JetEt[NobjJet]/F" );
  CalibTree->Branch( "JetE",  jete,  "JetE[NobjJet]/F"  );
  CalibTree->Branch( "JetFlavor", jetflavor, "JetFlavor[NobjJet]/I" );
  CalibTree->Branch( "JetTopID",  jettopid,  "JetTopID[NobjJet]/I"  );
  CalibTree->Branch( "JetCorrL1", jscaleL1,  "JetCorrL1[NobjJet]/F" );
  CalibTree->Branch( "JetCorrL2", jscaleL2,  "JetCorrL2[NobjJet]/F" );
  CalibTree->Branch( "JetCorrL3", jscaleL3,  "JetCorrL3[NobjJet]/F" );
  CalibTree->Branch( "JetCorrL4", jscaleL4,  "JetCorrL4[NobjJet]/F" );
  CalibTree->Branch( "JetCorrL5", jscaleL5,  "JetCorrL5[NobjJet]/F" );
  // GenJets
  genjetpt  = new float [ kjMAX ];
  genjetphi = new float [ kjMAX ];
  genjeteta = new float [ kjMAX ];
  genjetet  = new float [ kjMAX ];
  genjete   = new float [ kjMAX ];
  CalibTree->Branch( "GenJetPt", genjetpt, "GenJetPt[NobjJet]/F" );
  CalibTree->Branch( "GenJetPhi",genjetphi,"GenJetPhi[NobjJet]/F");
  CalibTree->Branch( "GenJetEta",genjeteta,"GenJetEta[NobjJet]/F");
  CalibTree->Branch( "GenJetEt", genjetet, "GenJetEt[NobjJet]/F" );
  CalibTree->Branch( "GenJetE",  genjete,  "GenJetE[NobjJet]/F"  );

  //EventWeight
  CalibTree->Branch( "Weight",&weight,"Weight/F"   );
}

void Top::analyze(const edm::Event& evt, const edm::EventSetup& setup, TTree* CalibTree)
{
  //Event Weighting
  //double weight = 1.; 
  if(weight < 0) {
    edm::Handle<double> weightHandle;
    evt.getByLabel (weight_tag, weightHandle);
    weight = (float)( *weightHandle );
  }

  edm::Handle<edm::View<reco::Jet> > pBJets;
  evt.getByLabel(bjets_, pBJets);

  edm::Handle<edm::View<reco::Jet> > pWJets;
  evt.getByLabel(wjets_, pWJets);

  edm::Handle<std::vector<reco::GenJet> > pBGenJets;
  evt.getByLabel(bgenjets_, pBGenJets);

  edm::Handle<std::vector<reco::GenJet> > pWGenJets;
  evt.getByLabel(wgenjets_, pWGenJets);

  // need 2*n W-jets and n B-jets, where n is the number of hypotheses
  if (pWJets->size()%2!=0 || pWJets->size()%pBJets->size()!=0)
    return;

  NobjTow = 0;
  NobjJet = pWJets->size() + pBJets->size();
  unsigned int towno = 0;

  // filling W-jets

  for(unsigned int jtno = 0; jtno<pWJets->size(); ++jtno) {

    fillRecJet( (*pWJets)[jtno], jtno, 1, jtno/2 );

    // GenJets for W-jets

    fillGenJet( (*pWGenJets)[jtno], jtno);

    if( dynamic_cast<const reco::CaloJet*>( &((*pWJets)[jtno]) ) ) {

      // towers for W-jets from CaloJets

      std::vector<CaloTowerPtr> j_towers = ( dynamic_cast<const reco::CaloJet*>( &((*pWJets)[jtno]) ) )->getCaloConstituents();
      NobjTow+=j_towers.size();
      fillTowers(j_towers, towno, jtno);

    }
    else if( dynamic_cast<const pat::Jet*>( &((*pWJets)[jtno]) ) ) {

      // towers and corrFactors for W-jets from patJets

      const pat::Jet* patJet = dynamic_cast<const pat::Jet*>( &((*pWJets)[jtno]) );

      std::vector<CaloTowerPtr> j_towers = patJet->getCaloConstituents();
      NobjTow+=j_towers.size();
      fillTowers(j_towers, towno, jtno);

      fillCorrFactors(*patJet, jtno, "uds");

    }

  }

  // filling b-jets

  for(unsigned int jtno = pWJets->size(); 
      jtno<pBJets->size()+pWJets->size(); ++jtno) {

    fillRecJet( (*pBJets)[jtno-pWJets->size()], jtno, 3, jtno-pWJets->size() );

    // GenJets for b-jets
    
    fillGenJet( (*pBGenJets)[jtno-pWJets->size()], jtno);

    if( dynamic_cast<const reco::CaloJet*>( &((*pBJets)[jtno-pWJets->size()]) ) ) {
    
      // towers for b-jets from CaloJets

      std::vector<CaloTowerPtr> j_towers = ( dynamic_cast<const reco::CaloJet*>( &((*pBJets)[jtno-pWJets->size()]) ) )->getCaloConstituents();
      NobjTow+=j_towers.size();
      fillTowers(j_towers, towno, jtno);

    }
    else if( dynamic_cast<const pat::Jet*>( &((*pBJets)[jtno-pWJets->size()]) ) ) {

      // towers and corrFactors for b-jets from patJets

      const pat::Jet* patJet = dynamic_cast<const pat::Jet*>( &((*pBJets)[jtno-pWJets->size()]) );

      std::vector<CaloTowerPtr> j_towers = patJet->getCaloConstituents();
      NobjTow+=j_towers.size();
      fillTowers(j_towers, towno, jtno);

      fillCorrFactors(*patJet, jtno, "b");

    }

  }

  CalibTree->Fill();
}

void Top::fillRecJet(const reco::Jet& recJet, const unsigned int jtno, const unsigned int flavor, const unsigned int topid) {

  jetpt    [jtno] = recJet.pt();
  jetphi   [jtno] = recJet.phi();
  jeteta   [jtno] = recJet.eta();
  jetet    [jtno] = recJet.et();
  jete     [jtno] = recJet.energy();
  jetflavor[jtno] = flavor; // 1=uds, 3=b
  jettopid [jtno] = topid;

}

void Top::fillTowers(const std::vector<CaloTowerPtr> &towers, unsigned int& towno, const unsigned int jtno) {

  for(std::vector<CaloTowerPtr>::const_iterator tow = towers.begin(); 
      tow != towers.end(); ++tow, ++towno){

    towet     [towno] = (*tow)->et();
    toweta    [towno] = (*tow)->eta();
    towphi    [towno] = (*tow)->phi();
    towen     [towno] = (*tow)->energy();
    towem     [towno] = (*tow)->emEnergy();
    towhd     [towno] = (*tow)->hadEnergy();
    towoe     [towno] = (*tow)->outerEnergy();
    towid_phi [towno] = (*tow)->id().iphi();
    towid_eta [towno] = (*tow)->id().ieta();
    towid     [towno] = (*tow)->id().rawId();
    tow_jetidx[towno] = jtno;

  }

}

void Top::fillCorrFactors(const pat::Jet &jet, const unsigned int jtno, const std::string &flavor) {

  /*
  if( jet.hasCorrFactors() ) {
    jscaleL1[jtno] = jet.corrFactor("off");
    jscaleL2[jtno] = jet.corrFactor("rel")/jet.corrFactor("off");
    jscaleL3[jtno] = jet.corrFactor("abs")/jet.corrFactor("rel");
    jscaleL4[jtno] = jet.corrFactor("emf")/jet.corrFactor("abs");
    jscaleL5[jtno] = jet.corrFactor("had", flavor)/jet.corrFactor("emf");
  }
  */

}

void Top::fillGenJet(const reco::GenJet &genJet, const unsigned int jtno) {

  genjetpt [jtno] = genJet.pt();
  genjetphi[jtno] = genJet.phi();
  genjeteta[jtno] = genJet.eta();
  genjetet [jtno] = genJet.et();
  genjete  [jtno] = genJet.energy();

}
