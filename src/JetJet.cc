#include "Calibration/CalibTreeMaker/interface/JetJet.h"

void JetJet::setup(const edm::ParameterSet& cfg, TTree* CalibTree)
{
  jets_      = cfg.getParameter<edm::InputTag>("JetJetJets");
  genjets_   = cfg.getParameter<edm::InputTag>("JetJetGenJets");
  met_       = cfg.getParameter<edm::InputTag>("JetJetMet");

  //tower for jet 1
  const int kMAX = 10000;
  towj1et  = new float [ kMAX ];
  towj1eta = new float [ kMAX ];
  towj1phi = new float [ kMAX ];
  towj1en  = new float [ kMAX ];
  towj1em  = new float [ kMAX ];
  towj1hd  = new float [ kMAX ];
  towj1oe  = new float [ kMAX ];
  towj1id_phi = new int[ kMAX ];
  towj1id_eta = new int[ kMAX ];
  towj1id     = new int[ kMAX ];

  // CaloTower branches
  CalibTree->Branch( "NobjTowJ1Cal",&NobjTowJ1Cal,"NobjTowJ1Cal/I"             );
  CalibTree->Branch( "TowJ1Id",     towj1id,      "TowJ1Id[NobjTowJ1Cal]/I"    );
  CalibTree->Branch( "TowJ1Id_phi", towj1id_phi,  "TowJ1Id_phi[NobjTowJ1Cal]/I");
  CalibTree->Branch( "TowJ1Id_eta", towj1id_eta,  "TowJ1Id_eta[NobjTowJ1Cal]/I");
  CalibTree->Branch( "TowJ1Et",     towj1et,      "TowJ1Et[NobjTowJ1Cal]/F"    );
  CalibTree->Branch( "TowJ1Eta",    towj1eta,     "TowJ1Eta[NobjTowJ1Cal]/F"   );
  CalibTree->Branch( "TowJ1Phi",    towj1phi,     "TowJ1Phi[NobjTowJ1Cal]/F"   );
  CalibTree->Branch( "TowJ1E",      towj1en,      "TowJ1E[NobjTowJ1Cal]/F"     );
  CalibTree->Branch( "TowJ1Em",     towj1em,      "TowJ1Em[NobjTowJ1Cal]/F"    );
  CalibTree->Branch( "TowJ1Had",    towj1hd,      "TowJ1Had[NobjTowJ1Cal]/F"   );
  CalibTree->Branch( "TowJ1OE",     towj1oe,      "TowJ1OE[NobjTowJ1Cal]/F"    );

  //tower for jet 2
  towj2et  = new float [ kMAX ];
  towj2eta = new float [ kMAX ];
  towj2phi = new float [ kMAX ];
  towj2en  = new float [ kMAX ];
  towj2em  = new float [ kMAX ];
  towj2hd  = new float [ kMAX ];
  towj2oe  = new float [ kMAX ];
  towj2id_phi = new int[ kMAX ];
  towj2id_eta = new int[ kMAX ];
  towj2id     = new int[ kMAX ];

  // CaloTower branches
  CalibTree->Branch( "NobjTowJ2Cal",&NobjTowJ2Cal,"NobjTowJ2Cal/I"           );
  CalibTree->Branch( "TowJ2Id",     towj2id,"TowJ2Id[NobjTowJ2Cal]/I"        );
  CalibTree->Branch( "TowJ2Id_phi", towj2id_phi,"TowJ2Id_phi[NobjTowJ2Cal]/I");
  CalibTree->Branch( "TowJ2Id_eta", towj2id_eta,"TowJ2Id_eta[NobjTowJ2Cal]/I");
  CalibTree->Branch( "TowJ2Et",     towj2et,"TowJ2Et[NobjTowJ2Cal]/F"        );
  CalibTree->Branch( "TowJ2Eta",    towj2eta,"TowJ2Eta[NobjTowJ2Cal]/F"      );
  CalibTree->Branch( "TowJ2Phi",    towj2phi,"TowJ2Phi[NobjTowJ2Cal]/F"      );
  CalibTree->Branch( "TowJ2E",      towj2en,"TowJ2E[NobjTowJ2Cal]/F"         );
  CalibTree->Branch( "TowJ2Em",     towj2em,"TowJ2Em[NobjTowJ2Cal]/F"        );
  CalibTree->Branch( "TowJ2Had",    towj2hd,"TowJ2Had[NobjTowJ2Cal]/F"       );
  CalibTree->Branch( "TowJ2OE",     towj2oe,"TowJ2OE[NobjTowJ2Cal]/F"        );

  // Leading Jet-specific branches of the tree 
  CalibTree->Branch( "FirstJetPt", &fstjetpt, "FirstJetPt/F" );
  CalibTree->Branch( "FirstJetPhi",&fstjetphi,"FirstJetPhi/F");
  CalibTree->Branch( "FirstJetEta",&fstjeteta,"FirstJetEta/F");
  CalibTree->Branch( "FirstJetEt", &fstjetet, "FirstJetEt/F" );
  CalibTree->Branch( "FirstJetE",  &fstjete,  "FirstJetE/F"  );

  // Next-to-leading Jet-specific branches of the tree 
  CalibTree->Branch( "ScndJetPt", &scdjetpt, "ScndJetPt/F" );
  CalibTree->Branch( "ScndJetPhi",&scdjetphi,"ScndJetPhi/F");
  CalibTree->Branch( "ScndJetEta",&scdjeteta,"ScndJetEta/F");
  CalibTree->Branch( "ScndJetEt", &scdjetet, "ScndJetEt/F" );
  CalibTree->Branch( "ScndJetE",  &scdjete,  "ScndJetE/F"  );

  // Leading Gen-Jet- branches of the tree 
  CalibTree->Branch( "FirstJetGenPt", &fstgenjetpt, "FirstJetGenPt/F" );
  CalibTree->Branch( "FirstJetGenPhi",&fstgenjetphi,"FirstJetGenPhi/F");
  CalibTree->Branch( "FirstJetGenEta",&fstgenjeteta,"FirstJetGenEta/F");
  CalibTree->Branch( "FirstJetGenEt", &fstgenjetet, "FirstJetGenEt/F" );
  CalibTree->Branch( "FirstJetGenE",  &fstgenjete,  "FirstJetGenE/F"  );

  // Next-to-leading Gen-Jet- branches of the tree 
  CalibTree->Branch( "ScndJetGenPt", &scdgenjetpt, "ScndJetGenPt/F" );
  CalibTree->Branch( "ScndJetGenPhi",&scdgenjetphi,"ScndJetGenPhi/F");
  CalibTree->Branch( "ScndJetGenEta",&scdgenjeteta,"ScndJetGenEta/F");
  CalibTree->Branch( "ScndJetGenEt", &scdgenjetet, "ScndJetGenEt/F" );
  CalibTree->Branch( "ScndJetGenE",  &scdgenjete,  "ScndJetGenE/F"  );

  //met
  CalibTree->Branch( "MetCal",   &mcalmet,"MetCal/F"   );
  CalibTree->Branch( "MetCalPhi",&mcalphi,"MetCalPhi/F");
  CalibTree->Branch( "MetCalSum",&mcalsum,"MetCalSum/F");
}

void JetJet::analyze(const edm::Event& evt, const edm::EventSetup& setup, TTree* CalibTree)
{
  edm::Handle<reco::GenJetCollection> genjet;
  evt.getByLabel(genjets_, genjet);

  edm::Handle<reco::CaloJetCollection> calojet;
  evt.getByLabel(jets_, calojet);

  edm::Handle<CaloMETCollection> recmets;
  evt.getByLabel(met_, recmets);

  double const eta_cut = 3.5;
  double s_sum_et = 0.0;
  std::vector <CaloTowerRef> j1_towers, j2_towers;
  for(reco::CaloJetCollection::const_iterator jit1 = calojet->begin(); jit1!=calojet->end(); ++jit1){
    if(fabs(jit1->eta()) > eta_cut) continue;
    for(reco::CaloJetCollection::const_iterator jit2 = jit1; jit2!=calojet->end(); ++jit2){
      if(fabs(jit2->eta()) > eta_cut) continue;
      for(reco::CaloJetCollection::const_iterator jit3 = jit2; jit2!=calojet->end(); ++jit3){
	if(fabs(jit3->eta()) > eta_cut) continue;
	s_sum_et += jit3->pt();
      }
      if(s_sum_et<15. && s_sum_et/(jit1->pt()+jit2->pt())<0.1 ){
	fstjetpt  = jit1->pt();
	fstjetphi = jit1->phi();
	fstjeteta = jit1->eta();
	fstjetet  = jit1->et();
	fstjete   = jit1->energy();
	j1_towers = jit1->getConstituents ();
	scdjetpt  = jit2->pt();
	scdjetphi = jit2->phi();
	scdjeteta = jit2->eta();
	scdjetet  = jit2->et();
	scdjete   = jit2->energy();
	j2_towers = jit2->getConstituents ();
      } 
      else return;
      break;
    }
    break;	  
  }

  int jtow = 0;
  NobjTowJ1Cal=j1_towers.size();
  for (std::vector <CaloTowerRef>::const_iterator tow = j1_towers.begin(); 
       tow != j1_towers.end(); ++tow, ++jtow){
    towj1et[jtow]     = (*tow)->et();
    towj1eta[jtow]    = (*tow)->eta();
    towj1phi[jtow]    = (*tow)->phi();
    towj1en[jtow]     = (*tow)->energy();
    towj1em[jtow]     = (*tow)->emEnergy();
    towj1hd[jtow]     = (*tow)->hadEnergy();
    towj1oe[jtow]     = (*tow)->outerEnergy();
    towj1id_phi[jtow] = (*tow)->id().iphi();
    towj1id_eta[jtow] = (*tow)->id().ieta();
    towj1id[jtow]     = (*tow)->id().rawId();
  }
  jtow = 0;
  NobjTowJ2Cal=j2_towers.size();
  for (std::vector <CaloTowerRef>::const_iterator tow = j2_towers.begin();
       tow != j2_towers.end(); ++tow, ++jtow){
    towj2et[jtow]     = (*tow)->et();
    towj2eta[jtow]    = (*tow)->eta();
    towj2phi[jtow]    = (*tow)->phi();
    towj2en[jtow]     = (*tow)->energy();
    towj2em[jtow]     = (*tow)->emEnergy();
    towj2hd[jtow]     = (*tow)->hadEnergy();
    towj2oe[jtow]     = (*tow)->outerEnergy();
    towj2id_phi[jtow] = (*tow)->id().iphi();
    towj2id_eta[jtow] = (*tow)->id().ieta();
    towj2id[jtow]     = (*tow)->id().rawId();
  }
  
  typedef CaloMETCollection::const_iterator cmiter;
  for( cmiter i=recmets->begin(); i!=recmets->end(); i++) {
    mcalmet = i->pt();
    mcalphi = i->phi();
    mcalsum = i->sumEt();
    break;
  }
  
  s_sum_et = 0.0;
  //std::vector <CaloTowerRef> jgen1_towers, jgen2_towers;
  for(reco::GenJetCollection::const_iterator jit1 = genjet->begin(); jit1!=genjet->end(); ++jit1){
    if(fabs(jit1->eta()) > eta_cut) continue;
    for(reco::GenJetCollection::const_iterator jit2 = jit1; jit2!=genjet->end(); ++jit2){
      if(fabs(jit2->eta()) > eta_cut) continue;
      for(reco::GenJetCollection::const_iterator jit3 = jit2; jit2!=genjet->end(); ++jit3){
	if(fabs(jit3->eta()) > eta_cut) continue;
	s_sum_et += jit3->pt();
      }
      if(s_sum_et<15. && s_sum_et/(jit1->pt()+jit2->pt())<0.1 ){
	fstgenjetpt  = jit1->pt();
	fstgenjetphi = jit1->phi();
	fstgenjeteta = jit1->eta();
	fstgenjetet  = jit1->et();
	fstgenjete   = jit1->energy();
	//jgen1_towers = jit1->getConstituents ();
	scdgenjetpt  = jit2->pt();
	scdgenjetphi = jit2->phi();
	scdgenjeteta = jit2->eta();
	scdgenjetet  = jit2->et();
	scdgenjete   = jit2->energy();
	//jgen2_towers = jit2->getConstituents ();
      } 
      else {
	fstgenjetpt  = 0.0;
	fstgenjetphi = 0.0;
	fstgenjeteta = 0.0;
	fstgenjetet  = 0.0;
	fstgenjete   = 0.0;
	scdgenjetpt  = 0.0;
	scdgenjetphi = 0.0;
	scdgenjeteta = 0.0;
	scdgenjetet  = 0.0;
	scdgenjete   = 0.0;
      }
      break;
    }
    break;	  
  }
  CalibTree->Fill();
}
