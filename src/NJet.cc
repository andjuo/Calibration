#include "Calibration/CalibTreeMaker/interface/NJet.h"
#include "DataFormats/METReco/interface/CaloMET.h"


void NJet::setup(const edm::ParameterSet& cfg, TTree* CalibTree)
{
  jets_ = cfg.getParameter<edm::InputTag>("NJet_Jets");
  //genjets_=cfg.getParameter<edm::InputTag>("NJet_GenJets");
  met_  = cfg.getParameter<edm::InputTag>("NJet_MET");

  //tower for all jets
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
  CalibTree->Branch( "Tow_jetidx",tow_jetidx, "Tow_jetidx[NobjTow]/I");

  //All jets
  const int kjMAX = 50;
  jetpt  = new float [ kjMAX ];
  jetphi = new float [ kjMAX ];
  jeteta = new float [ kjMAX ];
  jetet  = new float [ kjMAX ];
  jete   = new float [ kjMAX ];
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
//std::cout << "before Handle" << std::endl;
  edm::Handle<reco::CaloJetCollection> pJets;
  //edm::Handle<edm::View<reco::Jet> > pJets;
  evt.getByLabel(jets_, pJets);

  edm::Handle<CaloMETCollection> recmets;
  evt.getByLabel(met_, recmets);

//std::cout << "before loop over jets" << std::endl;
  NobjTow=0;
  NobjJet = pJets->size();
  unsigned int towno = 0;
  for (unsigned int jtno = 0; (int)jtno<NobjJet; ++jtno)
  {
//std::cout << jtno << ". jet, pt=" << (*pJets)[jtno].pt() << std::endl;
    jetpt[  jtno ] = (*pJets)[jtno].pt();
    jetphi[ jtno ] = (*pJets)[jtno].phi();
    jeteta[ jtno ] = (*pJets)[jtno].eta();
    jetet[  jtno ] = (*pJets)[jtno].et();
    jete[   jtno ] = (*pJets)[jtno].energy();
    std::vector<CaloTowerRef> j_towers = (*pJets)[jtno].getConstituents();
    NobjTow+=j_towers.size();
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

//std::cout << "before met " << std::endl;
  
  typedef CaloMETCollection::const_iterator cmiter;
  for( cmiter i=recmets->begin(); i!=recmets->end(); i++) {
    mmet = i->pt();
    mphi = i->phi();
    msum = i->sumEt();
    break;
  }

//std::cout << "before Tree fill " << std::endl;
 
  CalibTree->Fill();
}
