#include "Calibration/CalibTreeMaker/interface/Top.h"
#include "DataFormats/METReco/interface/CaloMET.h"

#include "DataFormats/Math/interface/deltaR.h"

void Top::setup(const edm::ParameterSet& cfg, TTree* CalibTree)
{
  bjets_     = cfg.getParameter<edm::InputTag> ("TopHadBJets");
  wjets_     = cfg.getParameter<edm::InputTag> ("TopHadWJets");
  genjets_   = cfg.getParameter<edm::InputTag> ("Top_GenJets");
  weight     = (float)(cfg.getParameter<double>("Top_Weight"));
  weight_tag = cfg.getParameter<edm::InputTag> ("Top_Weight_Tag");

  //tower for all -jets
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
  // CaloTower Branches for -Jets
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
  //All -jets
  int kjMAX = 8;
  jetpt  = new float [ kjMAX ];
  jetphi = new float [ kjMAX ];
  jeteta = new float [ kjMAX ];
  jetet  = new float [ kjMAX ];
  jete   = new float [ kjMAX ];
  jetflavor = new int[ kjMAX ];
  jettopid  = new int[ kjMAX ];
  // -Jet-specific ranches of the tree 
  CalibTree->Branch( "NobjJet",&NobjJet,"NobjJet/I"     );
  CalibTree->Branch( "JetPt", jetpt, "JetPt[NobjJet]/F" );
  CalibTree->Branch( "JetPhi",jetphi,"JetPhi[NobjJet]/F");
  CalibTree->Branch( "JetEta",jeteta,"JetEta[NobjJet]/F");
  CalibTree->Branch( "JetEt", jetet, "JetEt[NobjJet]/F" );
  CalibTree->Branch( "JetE",  jete,  "JetE[NobjJet]/F"  );
  CalibTree->Branch( "JetFlavor", jetflavor,  "JetFlavor[NobjJet]/I" );
  CalibTree->Branch( "JetTopID",  jettopid,   "JetTopID[NobjJet]/I"  );
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

  edm::Handle<reco::CaloJetCollection> pBJets;
  //edm::Handle<edm::View<reco::Jet> > pBJets;
  evt.getByLabel(bjets_, pBJets);

  edm::Handle<reco::CaloJetCollection> pWJets;
  //edm::Handle<edm::View<reco::Jet> > pWJets;
  evt.getByLabel(wjets_, pWJets);

  edm::Handle<reco::GenJetCollection> genJets;
  evt.getByLabel(genjets_, genJets);

  //Need 2*n W-jets and n B-jets, where n is the number of hypotheses
  if (pWJets->size()%2!=0 || pWJets->size()%pBJets->size()!=0)
    return;

  //Filling W-jets
  NobjTow=0;
  NobjJet = pWJets->size() + pBJets->size();
  unsigned int towno = 0;
  for (unsigned int jtno = 0; jtno<pWJets->size(); ++jtno)
  {
    jetpt [ jtno ] = (*pWJets)[jtno].pt();
    jetphi[ jtno ] = (*pWJets)[jtno].phi();
    jeteta[ jtno ] = (*pWJets)[jtno].eta();
    jetet [ jtno ] = (*pWJets)[jtno].et();
    jete  [ jtno ] = (*pWJets)[jtno].energy();
    jete  [ jtno ] = (*pWJets)[jtno].energy();
    jetflavor[jtno]= 1;//uds
    jettopid [jtno]= jtno/2;

    double gjpt = 0;
    double gjphi = 0;
    double gjeta = 0;
    double gjet = 0;
    double gje = 0;
    double DeltaR = 1000;
    double DeltaRtemp = 0;

    for( reco::GenJetCollection::const_iterator genJet = genJets->begin(); genJet != genJets->end(); ++genJet)
      {
	DeltaRtemp = deltaR(genJet->eta(), genJet->phi(),
			    (*pWJets)[jtno].eta(), (*pWJets)[jtno].phi() );
	if(DeltaRtemp < DeltaR)
	  {
	    DeltaR = DeltaRtemp;
	    gjpt  = genJet->pt();
	    gjphi = genJet->phi();
	    gjeta = genJet->eta();
	    gjet  = genJet->et();
	    gje   = genJet->energy();
	  }
      }
    genjetpt [ jtno ] = gjpt;
    genjetphi[ jtno ] =	gjphi;
    genjeteta[ jtno ] =	gjeta;
    genjetet [ jtno ] =	gjet;
    genjete  [ jtno ] = gje;
    
    std::vector<CaloTowerPtr> j_towers = (*pWJets)[jtno].getCaloConstituents();
    NobjTow+=j_towers.size();
    for (std::vector<CaloTowerPtr>::const_iterator tow = j_towers.begin(); 
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

  //Filling b-jets
  for (unsigned int jtno = pWJets->size(); 
       jtno<pBJets->size()+pWJets->size(); ++jtno)
  {
    jetpt [ jtno ] = (*pBJets)[jtno-pWJets->size()].pt();
    jetphi[ jtno ] = (*pBJets)[jtno-pWJets->size()].phi();
    jeteta[ jtno ] = (*pBJets)[jtno-pWJets->size()].eta();
    jetet [ jtno ] = (*pBJets)[jtno-pWJets->size()].et();
    jete  [ jtno ] = (*pBJets)[jtno-pWJets->size()].energy();
    jetflavor[jtno]= 3;//b
    jettopid [jtno]= jtno - pWJets->size();

    double gjpt = 0;
    double gjphi = 0;
    double gjeta = 0;
    double gjet = 0;
    double gje = 0;
    double DeltaR = 1000;
    double DeltaRtemp = 0;

    for( reco::GenJetCollection::const_iterator genJet = genJets->begin(); genJet != genJets->end(); ++genJet)
      {
	DeltaRtemp = deltaR(genJet->eta(), genJet->phi(),
			    (*pBJets)[jtno-pWJets->size()].eta() , (*pBJets)[jtno-pWJets->size()].phi() );
	if(DeltaRtemp < DeltaR)
	  {
	    DeltaR = DeltaRtemp;
	    gjpt  = genJet->pt();
	    gjphi = genJet->phi();
	    gjeta = genJet->eta();
	    gjet  = genJet->et();
	    gje   = genJet->energy();
	  }
      }
    genjetpt [ jtno ] = gjpt;
    genjetphi[ jtno ] =	gjphi;
    genjeteta[ jtno ] =	gjeta;
    genjetet [ jtno ] =	gjet;
    genjete  [ jtno ] = gje;

    std::vector<CaloTowerPtr> j_towers = (*pBJets)[jtno-pWJets->size()].getCaloConstituents();
    NobjTow+=j_towers.size();
    for (std::vector<CaloTowerPtr>::const_iterator tow = j_towers.begin(); 
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

  CalibTree->Fill();
}
