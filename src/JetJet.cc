#include "DataFormats/Math/interface/deltaR.h"
#include "Calibration/CalibTreeMaker/interface/JetJet.h"
#include "DataFormats/Math/interface/LorentzVector.h"

void JetJet::setup(const edm::ParameterSet& cfg, TTree* CalibTree)
{
  jets_              = cfg.getParameter<edm::InputTag>("JetJetJets");
  genjets_           = cfg.getParameter<edm::InputTag>("JetJetGenJets");
  met_               = cfg.getParameter<edm::InputTag>("JetJetMET");
  etaMaxTag_         = cfg.getParameter<double>("etaMaxTag");
  etaMaxProbe_       = cfg.getParameter<double>("etaMaxProbe");
  PtMin_             = cfg.getParameter<double>("PtMin");
  sumPtMaxFracThird_ = cfg.getParameter<double>("sumPtMaxFracThird");
  deltaPhiJetMax_    = cfg.getParameter<double>("deltaPhiJetMax");
  deltaPhiMETMax_    = cfg.getParameter<double>("deltaPhiMETMax");

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
  reco::CaloJetCollection CaloJets = *calojet;
  std::sort( CaloJets.begin(), CaloJets.end(), PtGreater());

  edm::Handle<CaloMETCollection> recmets;
  evt.getByLabel(met_, recmets);
  math::XYZTLorentzVector lvec_met;
  math::XYZTLorentzVector lvec_jet1, lvec_jet2;
  typedef CaloMETCollection::const_iterator cmiter;
  for( cmiter i=recmets->begin(); i!=recmets->end(); i++) {
    mcalmet = i->pt();
    mcalphi = i->phi();
    mcalsum = i->sumEt();
    lvec_met = i->p4();
    break;
  }

  std::vector <CaloTowerRef> j1_towers, j2_towers;
  //return if not enough jets
  if (CaloJets.size() <= 2) return;
  //return if none of two leading jets in tag region
  if ( abs(CaloJets.at(0).eta()) > etaMaxTag_ && abs(CaloJets.at(1).eta()) > etaMaxTag_ ) return;
  //return if one of two leading jets outside probe region
  if ( abs(CaloJets.at(0).eta()) > etaMaxProbe_ || abs(CaloJets.at(1).eta()) > etaMaxProbe_ ) return;
  //return if one of two leading jets too soft
  if ( abs(CaloJets.at(0).pt()) < PtMin_ || abs(CaloJets.at(1).pt()) < PtMin_ ) return;
  //return if two leading jets are not back to back
  if ( abs(deltaPhi(CaloJets.at(0).phi(), CaloJets.at(1).phi()) - 3.1415927) > deltaPhiJetMax_ ) return;
  //return if one two leading jets are not in direction of MET
  if ( deltaPhi(CaloJets.at(0).phi(), lvec_met.phi()) > deltaPhiMETMax_ && 
       deltaPhi(CaloJets.at(1).phi(), lvec_met.phi()) > deltaPhiMETMax_ ) return;
  //four vectors of two leading jets
  lvec_jet1 = CaloJets.at(0).p4();
  lvec_jet2 = CaloJets.at(1).p4();
  double s_sum_et = 0.0;
  for(reco::CaloJetCollection::const_iterator jit1 = CaloJets.begin()+2; jit1!=CaloJets.end(); ++jit1){
    s_sum_et += jit1->pt();
  }
  
  if ( s_sum_et/(CaloJets.at(0).pt()+CaloJets.at(1).pt()) < sumPtMaxFracThird_ ) {
    fstjetpt  = CaloJets.at(0).pt();
    fstjetphi = CaloJets.at(0).phi();
    fstjeteta = CaloJets.at(0).eta();
    fstjetet  = CaloJets.at(0).et();
    fstjete   = CaloJets.at(0).energy();
    j1_towers = CaloJets.at(0).getConstituents ();
    scdjetpt  = CaloJets.at(1).pt();
    scdjetphi = CaloJets.at(1).phi();
    scdjeteta = CaloJets.at(1).eta();
    scdjetet  = CaloJets.at(1).et();
    scdjete   = CaloJets.at(1).energy();
    j2_towers = CaloJets.at(1).getConstituents();
  } else {
    return;
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
  
  double dRmax1 = 10.;
  math::XYZTLorentzVector lvec_gjet1;
  for(reco::GenJetCollection::const_iterator jit1 = genjet->begin(); jit1!=genjet->end(); ++jit1){
    if ( deltaR(lvec_jet1.eta(), lvec_jet1.phi(), jit1->eta(), jit1->phi()) < dRmax1 ){
      dRmax1 = deltaR(lvec_jet1.eta(), lvec_jet1.phi(), jit1->eta(), jit1->phi());
      lvec_gjet1 = jit1->p4();
    }
  }

  double dRmax2 = 10.;
  math::XYZTLorentzVector lvec_gjet2;
  for(reco::GenJetCollection::const_iterator jit1 = genjet->begin(); jit1!=genjet->end(); ++jit1){
    if ( deltaR(lvec_jet2.eta(), lvec_jet2.phi(), jit1->eta(), jit1->phi()) < dRmax2 ){
      dRmax2 = deltaR(lvec_jet2.eta(), lvec_jet2.phi(), jit1->eta(), jit1->phi());
      lvec_gjet2 = jit1->p4();
    }
  }

  //only fill generator jet information, if both jets are matched
  if ( dRmax1 < 0.15 && dRmax2 < 0.15 ){
    fstgenjetpt  = lvec_gjet1.Pt();
    fstgenjetphi = lvec_gjet1.Phi();
    fstgenjeteta = lvec_gjet1.Eta();
    fstgenjetet  = lvec_gjet1.Et();
    fstgenjete   = lvec_gjet1.E();
    scdgenjetpt  = lvec_gjet2.Pt();
    scdgenjetphi = lvec_gjet2.Phi();
    scdgenjeteta = lvec_gjet2.Eta();
    scdgenjetet  = lvec_gjet2.Et();
    scdgenjete   = lvec_gjet2.E();
  }  else {
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

  CalibTree->Fill();

}
