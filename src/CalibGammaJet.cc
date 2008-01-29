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

#include "Calibration/CalibTreeMaker/interface/CalibGammaJet.h"
#include <DataFormats/EcalDetId/interface/EBDetId.h>
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
//#include "DataFormats/EcalDigi/interface/EBDataFrame.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"


/*  Setup the analysis to put the branch-variables into the tree. */
void CalibGammaJet::setup(const edm::ParameterSet& iConfig, TTree* CalibTree) {

  //GammaJet
  jets_      = iConfig.getParameter<edm::InputTag> ("jets");
  genjets_   = iConfig.getParameter<edm::InputTag> ("genjets");
  met_       = iConfig.getParameter<edm::InputTag> ("met");
  alltowers_ = iConfig.getParameter<edm::InputTag> ("alltowers");
  photon_    = iConfig.getParameter<edm::InputTag> ("photon");
  EBrechitCollection_ = iConfig.getParameter<edm::InputTag>("EBrechitCollection");

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
  townum    = new int[kMaxTower];
  CalibTree->Branch("NobjTowCal",&NobjTowCal,"NobjTowCal/I");
  CalibTree->Branch("TowNum",townum,"TowNum[NobjTowCal]/I");
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
  //ECAL-tower
  const int kMaxETower = 10000;
  etowet = new float[kMaxETower];
  etoweta = new float[kMaxETower];
  etowphi = new float[kMaxETower];
  etowe   = new float[kMaxETower];
  etowid_phi = new int[kMaxETower];
  etowid_eta = new int[kMaxETower];
  etowid     = new int[kMaxETower];
  etownum    = new int[kMaxETower];
  CalibTree->Branch("NobjETowCal",&NobjETowCal,"NobjETowCal/I");
  CalibTree->Branch("ETowNum",etownum,"ETowNum[NobjETowCal]/I");
  CalibTree->Branch("ETowId",etowid,"ETowId[NobjETowCal]/I");
  CalibTree->Branch("ETowId_phi",etowid_phi,"ETowId_phi[NobjETowCal]/I");
  CalibTree->Branch("ETowId_eta",etowid_eta,"ETowId_eta[NobjETowCal]/I");
  CalibTree->Branch("ETowEt",etowet,"ETowEt[NobjETowCal]/F");
  CalibTree->Branch("ETowEta",etoweta,"ETowEta[NobjETowCal]/F");
  CalibTree->Branch("ETowPhi",etowphi,"ETowPhi[NobjETowCal]/F");
  CalibTree->Branch("ETowE",etowe,"ETowE[NobjETowCal]/F");
  // Jet- MEt-specific branches of the tree 
  CalibTree->Branch("JetCalPt",&jcalpt,"JetCalPt/F");
  CalibTree->Branch("JetCalPhi",&jcalphi,"JetCalPhi/F");
  CalibTree->Branch("JetCalEta",&jcaleta,"JetCalEta/F");
  CalibTree->Branch("JetCalEt",&jcalet,"JetCalEt/F");
  CalibTree->Branch("JetCalE",&jcale,"JetCalE/F");
  // Gen- Jet- branches of the tree 
  CalibTree->Branch("JetGenPt",&jgenpt,"JetGenPt/F");
  CalibTree->Branch("JetGenPhi",&jgenphi,"JetGenPhi/F");
  CalibTree->Branch("JetGenEta",&jgeneta,"JetGenEta/F");
  CalibTree->Branch("JetGenEt",&jgenet,"JetGenEt/F");
  CalibTree->Branch("JetGenE",&jgene,"JetGenE/F");
  //met
  CalibTree->Branch("MetCal",&mcalmet,"MetCal/F");
  CalibTree->Branch("MetCalPhi",&mcalphi,"MetCalPhi/F");
  CalibTree->Branch("MetCalSum",&mcalsum,"MetCalSum/F");
  //photons
  CalibTree->Branch("PhotonPt",&photonpt,"PhotonPt/F");
  CalibTree->Branch("PhotonPhi",&photonphi,"PhotonPhi/F");
  CalibTree->Branch("PhotonEta",&photoneta,"PhotonEta/F");
  CalibTree->Branch("PhotonEt",&photonet,"PhtonEt/F");
  CalibTree->Branch("PhotonE",&photone,"PhotonE/F");

}

void CalibGammaJet::analyze(const edm::Event& iEvent, 
        const edm::EventSetup& iSetup, TTree* CalibTree)
{
  bool goodEvent = true;
   
  edm::Handle<CaloJet> jet;
  edm::Handle<GenJet> genjets;
  //edm::Handle<CaloTowerCollection> alltowers;
  edm::Handle<CaloMETCollection> met;
  edm::Handle<Photon> photon;
  iEvent.getByLabel(met_,met);
  //iEvent.getByLabel(alltowers_,alltowers);
  iEvent.getByLabel(jets_,jet);
  iEvent.getByLabel(genjets_,genjets);
  iEvent.getByLabel(photon_,photon);
  const CaloJet& calojet = *jet;
  const GenJet&  genjet = *genjets;
  const CaloMETCollection& recmets = *met; 
  const Photon& Photon = *photon; 
  //const CaloTowerCollection& caloTowers = *alltowers;

  const EBRecHitCollection *EBRecHit = 0;
  edm::Handle<EBRecHitCollection> EcalRecHitEB;
  iEvent.getByLabel( EBrechitCollection_, EcalRecHitEB);
  if (EcalRecHitEB.isValid()){ 
    EBRecHit = EcalRecHitEB.product();
  } else {
    cerr << "Error! can't get the product " << EBrechitCollection_.label() << ":" << EBrechitCollection_.instance()
         << endl;
  }
  
  edm::ESHandle<CaloGeometry> pG;
  iSetup.get<IdealGeometryRecord>().get(pG);
  const CaloGeometry cG = *pG;
  const CaloSubdetectorGeometry* EBgeom=cG.getSubdetectorGeometry(DetId::Ecal,1);
  
  jcalpt  = calojet.pt();
  jcalphi = calojet.phi();
  jcaleta = calojet.eta();
  jcalet  = calojet.et();
  jcale   = calojet.energy();
  std::vector <CaloTowerRef> j_towers = calojet.getConstituents ();

  int jtow = 0;
  int jetow = 0;
  NobjTowCal=j_towers.size();
  //ECAL-Barrel:
  for (std::vector <CaloTowerRef>::const_iterator tow = j_towers.begin();
       tow != j_towers.end(); ++tow, ++jtow){
     towet[jtow]     = (*tow)->et();
     toweta[jtow]    = (*tow)->eta();
     towphi[jtow]    = (*tow)->phi();
     towen[jtow]     = (*tow)->energy();
     towem[jtow]     = (*tow)->emEnergy();
     towhd[jtow]     = (*tow)->hadEnergy();
     towoe[jtow]     = (*tow)->outerEnergy();
     towid_phi[jtow] = (*tow)->id().iphi();
     towid_eta[jtow] = (*tow)->id().ieta();
     towid[jtow]     = (*tow)->id().rawId();
     townum[jtow]    = jtow;

     double eem=0.;
     for (size_t it=0; it<(*tow)->constituentsSize(); ++it) {
	const DetId detid = (*tow)->constituent(it);
          EcalRecHitCollection::const_iterator myRecHit = EBRecHit->find(detid);
	  if(myRecHit != EBRecHit->end()) {
  	    eem +=  myRecHit->energy(); 
	    EBDetId det = myRecHit->id();
	       
	    const CaloCellGeometry* cell=EBgeom->getGeometry( myRecHit->id() );
	    etowet[jetow]     = myRecHit->energy()*sin( cell->getPosition().theta());
	    etoweta[jetow]    = cell->getPosition().eta();
	    etowphi[jetow]    = cell->getPosition().phi();
	    etowe[jetow]      = myRecHit->energy();
	    etowid_phi[jetow] = det.iphi();
	    etowid_eta[jetow] = det.ieta();
	    etowid[jetow]     = myRecHit->id().rawId();
	    etownum[jetow]    = jetow;
	    ++jetow;
	}
     }
     if (eem-towem[jtow]>0.01) goodEvent=false;	
  }
  //ECal-Forward:  STILL MISSING !!!!
  // ...
  
  NobjETowCal = jetow;

  jgenpt  = genjet.pt();
  jgenphi = genjet.phi();
  jgeneta = genjet.eta();
  jgenet  = genjet.et();
  jgene   = genjet.energy();

  photonpt  = Photon.pt();
  photonphi = Photon.phi();
  photoneta = Photon.eta();
  photonet  = Photon.et();
  photone   = Photon.energy();

  if (&recmets) {
    typedef CaloMETCollection::const_iterator cmiter;
    for ( cmiter i=recmets.begin(); i!=recmets.end(); i++) {
      mcalmet = i->pt();
      mcalphi = i->phi();
      mcalsum = i->sumEt();
      break;
    }
  }
  
  if (goodEvent)
  CalibTree->Fill();

}
