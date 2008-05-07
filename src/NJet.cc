#include "Calibration/CalibTreeMaker/interface/NJet.h"

void NJet::setup(const edm::ParameterSet& cfg, TTree* CalibTree)
{
  jets_      = cfg.getParameter<edm::InputTag>("NJetJets");
  genjets_   = cfg.getParameter<edm::InputTag>("NJetGenJets");
  met_       = cfg.getParameter<edm::InputTag>("NJetMet");

  //tower for all jets
  unsigned int kMAX = 10000;
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

  // CaloTower branches
  CalibTree->Branch( "NobjTow",&NobjTow,"NobjTow/I"             );
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
  CalibTree->Branch( "Tow_jetidx",tow_jetidx, "Tow_jetidx[NobjTow]/F");

  //All jets
  kMAX = 30;
  jetpt  = new float [ kMAX ];
  jetphi = new float [ kMAX ];
  jeteta = new float [ kMAX ];
  jetet  = new float [ kMAX ];
  jete   = new float [ kMAX ];
  // Jet-specific branches of the tree 
  CalibTree->Branch( "NobjJet",&NobjJet,"NobjJet/I"             );
  CalibTree->Branch( "JetPt", jetpt, "JetPt[NobjJet]/F" );
  CalibTree->Branch( "JetPhi",jetphi,"JetPhi[NobjJet]/F");
  CalibTree->Branch( "JetEta",jeteta,"JetEta[NobjJet]/F");
  CalibTree->Branch( "JetEt", jetet, "JetEt[NobjJet]/F" );
  CalibTree->Branch( "JetE",  jete,  "JetE[NobjJet]/F"  );

  //met
  CalibTree->Branch( "Met",   &mmet,"Met/F"   );
  CalibTree->Branch( "MetPhi",&mphi,"MetPhi/F");
  CalibTree->Branch( "MetSum",&msum,"MetSum/F");
}

void NJet::analyze(const edm::Event& evt, const edm::EventSetup& setup, TTree* CalibTree)
{
  edm::Handle<reco::CaloJetCollection> pJets;
  //edm::Handle<edm::View<reco::Jet> > pJets;
  evt.getByLabel(jets_, pJets);

  edm::Handle<CaloMETCollection> recmets;
  evt.getByLabel(met_, recmets);

  NobjJet = pJets->size();
  unsigned int towno = 0;
  for (unsigned int jtno = 0; (int)jtno<NobjJet; ++jtno)
  {
    jetpt[  jtno ] = (*pJets)[jtno].pt();
    jetphi[ jtno ] = (*pJets)[jtno].phi();
    jeteta[ jtno ] = (*pJets)[jtno].eta();
    jetet[  jtno ] = (*pJets)[jtno].et();
    jete[   jtno ] = (*pJets)[jtno].energy();
    std::vector<CaloTowerRef> j_towers = (*pJets)[jtno].getConstituents();
    NobjTow=j_towers.size();
    for (std::vector<CaloTowerRef>::const_iterator tow = j_towers.begin(); 
	 tow != j_towers.end(); ++tow, ++towno){
      towet[towno]     = (*tow)->et();
      toweta[towno]    = (*tow)->eta();
      towphi[towno]    = (*tow)->phi();
      towen[towno]     = (*tow)->energy();
      towem[towno]     = (*tow)->emEnergy();
      towhd[towno]     = (*tow)->hadEnergy();
      towoe[towno]     = (*tow)->outerEnergy();
      towid_phi[towno] = (*tow)->id().iphi();
      towid_eta[towno] = (*tow)->id().ieta();
      towid[towno]     = (*tow)->id().rawId();
      tow_jetidx[towno]= jtno;
    }
  }
  
  typedef CaloMETCollection::const_iterator cmiter;
  for( cmiter i=recmets->begin(); i!=recmets->end(); i++) {
    mmet = i->pt();
    mphi = i->phi();
    msum = i->sumEt();
    break;
  }
  
  CalibTree->Fill();
}
