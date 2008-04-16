#include "Calibration/CalibTreeMaker/interface/PhotonJet.h"

//#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"
#include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleCandidate.h"

//check out first cvs co -d CSA07EffAnalyser UserCode/lowette/CSA07EffAnalyser/CSA07EffAnalyser
//#include "CSA07EffAnalyser/interface/CSA07ProcessId.h"

void PhotonJet::setup(const edm::ParameterSet& cfg, TTree* CalibTree)
{
  jets_      = cfg.getParameter<edm::InputTag>("PhotonJetJets");
  photon_    = cfg.getParameter<edm::InputTag>("PhotonJetPhotons");
  genjets_   = cfg.getParameter<edm::InputTag>("PhotonJetGenJets");
  genphotons_= cfg.getParameter<edm::InputTag>("PhotonJetGenPhotons");
  met_       = cfg.getParameter<edm::InputTag>("PhotonJetMet");
  ebrechits_ = cfg.getParameter<edm::InputTag>("EBRecHits");

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
  townum    = new int[ kMAX ];

  // CaloTower branches
  CalibTree->Branch( "NobjTowCal",&NobjTowCal,"NobjTowCal/I"            );
  CalibTree->Branch( "TowNum",    townum,     "TowNum[NobjTowCal]/I"    );
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

  //ecal cells data
  etowet  = new float [ kMAX ];
  etoweta = new float [ kMAX ];
  etowphi = new float [ kMAX ];
  etowe   = new float [ kMAX ];
  etowid_phi = new int[ kMAX ];
  etowid_eta = new int[ kMAX ];
  etowid     = new int[ kMAX ];
  etownum    = new int[ kMAX ];

  //EcalCell branches
  CalibTree->Branch( "NobjETowCal",&NobjETowCal,"NobjETowCal/I"            );
  CalibTree->Branch( "ETowNum",    etownum,     "ETowNum[NobjETowCal]/I"   );
  CalibTree->Branch( "ETowId",     etowid,      "ETowId[NobjETowCal]/I"    );
  CalibTree->Branch( "ETowId_phi", etowid_phi,  "ETowId_phi[NobjETowCal]/I");
  CalibTree->Branch( "ETowId_eta", etowid_eta,  "ETowId_eta[NobjETowCal]/I");
  CalibTree->Branch( "ETowEt",     etowet,      "ETowEt[NobjETowCal]/F"    );
  CalibTree->Branch( "ETowEta",    etoweta,     "ETowEta[NobjETowCal]/F"   );
  CalibTree->Branch( "ETowPhi",    etowphi,     "ETowPhi[NobjETowCal]/F"   );
  CalibTree->Branch( "ETowE",      etowe,       "ETowE[NobjETowCal]/F"     );

  // CaloJet branches 
  CalibTree->Branch( "JetCalPt",  &jcalpt,    "JetCalPt/F"  );
  CalibTree->Branch( "JetCalPhi", &jcalphi,   "JetCalPhi/F" );
  CalibTree->Branch( "JetCalEta", &jcaleta,   "JetCalEta/F" );
  CalibTree->Branch( "JetCalEt",  &jcalet,    "JetCalEt/F"  );
  CalibTree->Branch( "JetCalE",   &jcale,     "JetCalE/F"   );
  // GenJet branches 
  CalibTree->Branch( "JetGenPt",  &jgenpt,    "JetGenPt/F"  );
  CalibTree->Branch( "JetGenPhi", &jgenphi,   "JetGenPhi/F" );
  CalibTree->Branch( "JetGenEta", &jgeneta,   "JetGenEta/F" );
  CalibTree->Branch( "JetGenEt",  &jgenet,    "JetGenEt/F"  );
  CalibTree->Branch( "JetGenE",   &jgene,     "JetGenE/F"   );
  // MET branches
  CalibTree->Branch( "MetCal",    &mcalmet,   "MetCal/F"    );
  CalibTree->Branch( "MetCalPhi", &mcalphi,   "MetCalPhi/F" );
  CalibTree->Branch( "MetCalSum", &mcalsum,   "MetCalSum/F" );
  // Photons branches
  CalibTree->Branch( "PhotonPt",  &photonpt,  "PhotonPt/F"  );
  CalibTree->Branch( "PhotonPhi", &photonphi, "PhotonPhi/F" );
  CalibTree->Branch( "PhotonEta", &photoneta, "PhotonEta/F" );
  CalibTree->Branch( "PhotonEt",  &photonet,  "PhtonEt/F"   );
  CalibTree->Branch( "PhotonE",   &photone,   "PhotonE/F"   );
  // GenPhotons branches
  CalibTree->Branch( "GenPhotonPt",  &gphotonpt,  "GenPhotonPt/F"  );
  CalibTree->Branch( "GenPhotonPhi", &gphotonphi, "GenPhotonPhi/F" );
  CalibTree->Branch( "GenPhotonEta", &gphotoneta, "GenPhotonEta/F" );
  CalibTree->Branch( "GenPhotonEt",  &gphotonet,  "GenPhtonEt/F"   );
  CalibTree->Branch( "GenPhotonE",   &gphotone,   "GenPhotonE/F"   );

  // CSA07 weight and pid branches
  CalibTree->Branch( "EventWeight", &eventweight,  "EventWeight/F"  );
  //CalibTree->Branch( "ProcessID"  , &processid,    "ProcessID/I"  );
}

void PhotonJet::analyze(const edm::Event& evt, const edm::EventSetup& setup, TTree* CalibTree)
{
  //CSA07 event weights
  edm::Handle<double> weightHandle;
  evt.getByLabel ("csaweightproducer","weight", weightHandle);
  eventweight = *weightHandle;
  //processid = csa07::csa07ProcessId(evt); //Stew lower pt bound was reduced from 15 to 0 GeV (pid=28)

  edm::Handle<CaloJet> jet;
  evt.getByLabel(jets_, jet);

  edm::Handle<Photon> photon;
  evt.getByLabel(photon_,photon);

  edm::Handle<GenJet> genJet;
  evt.getByLabel(genjets_,genJet);

  edm::Handle<GenParticleCandidate> genPhoton;
  evt.getByLabel(genphotons_,genPhoton);

  edm::Handle<CaloMETCollection> met;
  evt.getByLabel(met_,met);

  const CaloJet& calojet = *jet;
  const Photon& Photon = *photon; 
  const GenJet& genjet = *genJet;
  const GenParticleCandidate&  genphoton = *genPhoton; 
  const CaloMETCollection& recmets = *met; 

  /*
  const EBRecHitCollection *EBRecHit = 0;
  edm::Handle<EBRecHitCollection> EcalRecHitEB;
  evt.getByLabel( ebrechits_, EcalRecHitEB);
  if( EcalRecHitEB.isValid() ){ 
    EBRecHit = EcalRecHitEB.product();
  } else {
    cerr << "Error! can't get the product " 
	 << ebrechits_.label() 
	 << ":" 
	 << ebrechits_.instance()
         << endl;
  }
  */

  /*
  edm::ESHandle<CaloGeometry> pG;
  setup.get<IdealGeometryRecord>().get(pG);
  const CaloGeometry cG = *pG;
  const CaloSubdetectorGeometry* EBgeom=cG.getSubdetectorGeometry(DetId::Ecal,1);
  */

  jcalpt  = calojet.pt();
  jcalphi = calojet.phi();
  jcaleta = calojet.eta();
  jcalet  = calojet.et();
  jcale   = calojet.energy();

  int jtow=0, icell=0;
  std::vector <CaloTowerRef> jetTowers = calojet.getConstituents();
  NobjTowCal=jetTowers.size();
  for(std::vector<CaloTowerRef>::const_iterator tow = jetTowers.begin();
      tow != jetTowers.end(); ++tow, ++jtow){
    towet [jtow] = (*tow)->et();
    toweta[jtow] = (*tow)->eta();
    towphi[jtow] = (*tow)->phi();
    towen [jtow] = (*tow)->energy();
    towem [jtow] = (*tow)->emEnergy();
    towhd [jtow] = (*tow)->hadEnergy();
    towoe [jtow] = (*tow)->outerEnergy();
    towid_phi[jtow] = (*tow)->id().iphi();
    towid_eta[jtow] = (*tow)->id().ieta();
    towid [jtow] = (*tow)->id().rawId();
    townum[jtow] = jtow;

    /*
    double eem=0.;
    for (size_t it=0; it<(*tow)->constituentsSize(); ++it) {
      const DetId detid = (*tow)->constituent(it);
      EcalRecHitCollection::const_iterator myRecHit = EBRecHit->find(detid);
      if(myRecHit != EBRecHit->end()) {
	eem +=  myRecHit->energy(); 
	EBDetId det = myRecHit->id();
	
	const CaloCellGeometry* cell=EBgeom->getGeometry( myRecHit->id() );
	etowet [icell] = myRecHit->energy()*sin( cell->getPosition().theta());
	etoweta[icell] = cell->getPosition().eta();
	etowphi[icell] = cell->getPosition().phi();
	etowe  [icell] = myRecHit->energy();
	etowid_phi[icell] = det.iphi();
	etowid_eta[icell] = det.ieta();
	etowid [icell] = myRecHit->id().rawId();
	etownum[icell] = icell;
	++icell;
      }
    }
    */
  }
  NobjETowCal = icell;

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

  gphotonpt  = genphoton.pt();
  gphotonphi = genphoton.phi();
  gphotoneta = genphoton.eta();
  gphotonet  = genphoton.et();
  gphotone   = genphoton.energy();

  typedef CaloMETCollection::const_iterator cmiter;
  for ( cmiter i=recmets.begin(); i!=recmets.end(); i++) {
    mcalmet = i->pt();
    mcalphi = i->phi();
    mcalsum = i->sumEt();
    break;
  }
  CalibTree->Fill();
}
