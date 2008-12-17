#include "Calibration/CalibTreeMaker/interface/ZJet.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"


//check out first cvs co -d CSA07EffAnalyser UserCode/lowette/CSA07EffAnalyser/CSA07EffAnalyser
//#include "CSA07EffAnalyser/interface/CSA07ProcessId.h"

void ZJet::setup(const edm::ParameterSet& cfg, TTree* CalibTree)
{
  jets_             = cfg.getParameter<edm::InputTag>("ZJetJets");
  z_                = cfg.getParameter<edm::InputTag>("ZJetZs");
  genzs_            = cfg.getParameter<edm::InputTag>("ZJetGenZs");
  genjets_          = cfg.getParameter<edm::InputTag>("ZJetGenJets");
  met_              = cfg.getParameter<edm::InputTag>("ZJetMet");
  ebrechits_        = cfg.getParameter<edm::InputTag>("EBRecHits");
  nonleadingjetspt_ = cfg.getParameter<edm::InputTag>("ZJetNonLeadingJetsPt");
  recTracks_        = cfg.getParameter<edm::InputTag>("ZJetRecTracks");
  recMuons_         = cfg.getParameter<edm::InputTag>("ZJetRecMuons");
  conesize_         = cfg.getParameter<double>("ZJetConeSize");
  weight_tag        = cfg.getParameter<edm::InputTag> ("ZJet_Weight_Tag");
  weight_            = (float)(cfg.getParameter<double> ("ZJet_Weight"));
   
  // TrackAssociator parameters
  edm::ParameterSet parameters = cfg.getParameter<edm::ParameterSet>("TrackAssociatorParameters");
  parameters_.loadParameters( parameters );

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

  //track branches
  trackpt       = new float [ kMAX ];
  tracketa      = new float [ kMAX ];
  trackphi      = new float [ kMAX ];
  trackp        = new float [ kMAX ];
  trackdr       = new float [ kMAX ];
  tracketaout   = new float [ kMAX ];
  trackphiout   = new float [ kMAX ];
  trackdrout    = new float [ kMAX ];
  trackemc1     = new float [ kMAX ];
  trackemc3     = new float [ kMAX ];
  trackemc5     = new float [ kMAX ];
  trackhac1     = new float [ kMAX ];
  trackhac3     = new float [ kMAX ];
  trackhac5     = new float [ kMAX ];
  tracktowid    = new int [ kMAX ];
  tracktowidphi = new int [ kMAX ];
  tracktowideta = new int [ kMAX ];
  trackid       = new int[ kMAX ]; // abs(PiD) if available, guess: muons only; =0: unknown
  tracknhits    = new int[ kMAX ];
  trackQuality  = new int[kMAX];
  trackchi2     = new float[ kMAX ];
  muDR          = new float[ kMAX ];
  muDE          = new float[ kMAX ];

  //track branches
  CalibTree->Branch( "NobjTrack",  &NobjTrack, "NobjTrack/I"             );
  CalibTree->Branch( "TrackTowId", tracktowid, "TrackTowId[NobjTrack]/I" );
  CalibTree->Branch( "TrackTowIdPhi", tracktowidphi, "TrackTowIdPhi[NobjTrack]/I" );
  CalibTree->Branch( "TrackTowIdEta", tracktowideta, "TrackTowIdEta[NobjTrack]/I" );
  CalibTree->Branch( "TrackId",    trackid,    "TrackId[NobjTrack]/I"    );
  CalibTree->Branch( "TrackNHits", tracknhits, "TrackNHits[NobjTrack]/I" );
  CalibTree->Branch( "TrackQuality",trackQuality,"TrackQuality[NobjTrack]/I");
  CalibTree->Branch( "TrackChi2",  trackchi2,  "TrackChi2[NobjTrack]/F"  );
  CalibTree->Branch( "TrackPt",    trackpt,    "TrackPt[NobjTrack]/F"    );
  CalibTree->Branch( "TrackEta",   tracketa,   "TrackEta[NobjTrack]/F"   );
  CalibTree->Branch( "TrackPhi",   trackphi,   "TrackPhi[NobjTrack]/F"   );
  CalibTree->Branch( "TrackP" ,    trackp,     "TrackP[NobjTrack]/F"     );
  CalibTree->Branch( "TrackDR" ,   trackdr,    "TrackDR[NobjTrack]/F"    );
  CalibTree->Branch( "TrackPhiOut",trackphiout,"TrackPhiout[NobjTrack]/F");
  CalibTree->Branch( "TrackEtaOut",tracketaout,"TrackEtaout[NobjTrack]/F");
  CalibTree->Branch( "TrackDROut", trackdrout, "TrackDRout[NobjTrack]/F" );
  CalibTree->Branch( "TrackEMC1",  trackemc1,  "TrackEMC1[NobjTrack]/F"  );
  CalibTree->Branch( "TrackEMC3",  trackemc3,  "TrackEMC3[NobjTrack]/F"  );
  CalibTree->Branch( "TrackEMC5",  trackemc5,  "TrackEMC5[NobjTrack]/F"  );
  CalibTree->Branch( "TrackHAC1",  trackhac1,  "TrackHAC1[NobjTrack]/F"  );
  CalibTree->Branch( "TrackHAC3",  trackhac3,  "TrackHAC3[NobjTrack]/F"  );
  CalibTree->Branch( "TrackHAC5",  trackhac5,  "TrackHAC5[NobjTrack]/F"  );
  CalibTree->Branch( "MuDR", muDR,  "MuDR[NobjTrack]/F"  );
  CalibTree->Branch( "MuDE", muDE,  "MuDE[NobjTrack]/F"  );

  // CaloJet branches 
  CalibTree->Branch( "JetCalPt",  &jcalpt,    "JetCalPt/F"  );
  CalibTree->Branch( "JetCalPhi", &jcalphi,   "JetCalPhi/F" );
  CalibTree->Branch( "JetCalEta", &jcaleta,   "JetCalEta/F" );
  CalibTree->Branch( "JetCalEt",  &jcalet,    "JetCalEt/F"  );
  CalibTree->Branch( "JetCalE",   &jcale,     "JetCalE/F"   );
  CalibTree->Branch( "JetCorrL2", &jscalel2,  "JetCorrL2/F" );
  CalibTree->Branch( "JetCorrL3", &jscalel3,  "JetCorrL3/F" );
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


  // Zs branches
  CalibTree->Branch( "ZPt",  &zpt,  "ZPt/F"  );
  CalibTree->Branch( "ZPhi", &zphi, "ZPhi/F" );
  CalibTree->Branch( "ZEta", &zeta, "ZEta/F" );
  CalibTree->Branch( "ZEt",  &zet,  "ZEt/F"   );
  CalibTree->Branch( "ZE",   &ze,   "ZE/F"   );
  // GenZs branches
  CalibTree->Branch( "GenZPt",  &gzpt,  "GenZPt/F"  );
  CalibTree->Branch( "GenZPhi", &gzphi, "GenZPhi/F" );
  CalibTree->Branch( "GenZEta", &gzeta, "GenZEta/F" );
  CalibTree->Branch( "GenZEt",  &gzet,  "GenZEt/F"   );
  CalibTree->Branch( "GenZE",   &gze,   "GenZE/F"   );
  // NonLeadingJetPt branch
  CalibTree->Branch( "NonLeadingJetPt", &nonleadingjetspt,   "NonLeadingJetPt/F"   );

  // CSA07 weight and pid branches
  CalibTree->Branch( "EventWeight", &weight,  "EventWeight/F"  );
  //CalibTree->Branch( "ProcessID"  , &processid,    "ProcessID/I"  );
}

void ZJet::analyze(const edm::Event& evt, const edm::EventSetup& setup, TTree* CalibTree)
{
  if(weight_<0)
    {
      edm::Handle<double> weightHandle;
      evt.getByLabel (weight_tag, weightHandle);
      weight =(float)( *weightHandle);
    }
  else weight = weight_;

  edm::Handle<CaloJet> jet;
  evt.getByLabel(jets_, jet);

  edm::Handle<GenJet> genJet;
  evt.getByLabel(genjets_,genJet);

  edm::Handle<Particle> z;
  evt.getByLabel(z_,z);

  edm::Handle<GenParticle> genZ;
  evt.getByLabel(genzs_,genZ);

  edm::Handle<CaloMETCollection> met;
  evt.getByLabel(met_,met);

  edm::Handle<double> NonLeadingJetsPt;
  evt.getByLabel( nonleadingjetspt_, NonLeadingJetsPt );

  const CaloJet& calojet = *jet;
  const GenJet& genjet = *genJet;
  const GenParticle&  genz = *genZ; 
  const GenParticle&  Z = *z; 
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

  std::string l2name = "L2RelativeJetCorrector";
  std::string l3name = "L3AbsoluteJetCorrector";

  const JetCorrector* correctorL2   = JetCorrector::getJetCorrector (l2name,setup);   //Define the jet corrector
  const JetCorrector* correctorL3   = JetCorrector::getJetCorrector (l3name,setup);   //Define the jet corrector
  jscalel2   = correctorL2  ->correction(calojet.p4());  //calculate the correction
  jscalel3   = correctorL3  ->correction(calojet.p4());  //calculate the correction
  /*
  cout<<" Jet Pt = "<<calojet.pt()
      <<" Jet Eta = "<<calojet.eta()
      <<" Scale L2 = "<<jscalel2
      <<" Scale L3 = "<<jscalel3
      <<endl;
  */

  jcalpt  = calojet.pt();
  jcalphi = calojet.phi();
  jcaleta = calojet.eta();
  jcalet  = calojet.et();
  jcale   = calojet.energy();

  int jtow=0, icell=0;

  // uncomment for CMSSW_2_1_X compatibility
  std::vector <CaloTowerPtr> jetTowers = calojet.getCaloConstituents();
  NobjTowCal=jetTowers.size();
  for(std::vector<CaloTowerPtr>::const_iterator tow = jetTowers.begin();
      tow != jetTowers.end(); ++tow, ++jtow){

    // uncomment for CMSSW_2_0_X compatibility
//  std::vector <CaloTowerRef> jetTowers = calojet.getConstituents();
//  NobjTowCal=jetTowers.size();
//  for(std::vector<CaloTowerRef>::const_iterator tow = jetTowers.begin();
//      tow != jetTowers.end(); ++tow, ++jtow){

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
 
  zpt  = Z.pt();
  zphi = Z.phi();
  zeta = Z.eta();
  zet  = Z.et();
  ze   = Z.energy();
 
  gzpt  = genz.pt();
  gzphi = genz.phi();
  gzeta = genz.eta();
  gzet  = genz.et();
  gze   = genz.energy();

  typedef CaloMETCollection::const_iterator cmiter;
  for ( cmiter i=recmets.begin(); i!=recmets.end(); i++) {
    mcalmet = i->pt();
    mcalphi = i->phi();
    mcalsum = i->sumEt();
    break;
  }

  nonleadingjetspt = (float)(*NonLeadingJetsPt);

  //Tracks
  edm::Handle<reco::TrackCollection> tracks;
  evt.getByLabel(recTracks_,tracks);

  //Muons
  //edm::Handle<reco::MuonCollection> muons;
  edm::Handle<reco::TrackCollection> muons;
  evt.getByLabel(recMuons_,muons);

  // see here for detailed track cluster matching and jet track association
  //   -> CMSSW/TrackingTools/TrackAssociator/test/CaloMatchingExample.cc

  int iTrack = 0;
  for(reco::TrackCollection::const_iterator it = tracks->begin(); it != tracks->end(); ++it) {
    // skip low Pt tracks
    //if (it->pt() < 2) continue;
    bool saveTrack = false;
    TrackDetMatchInfo info = trackAssociator_.associate(evt, setup, *it, parameters_);

    double dRin   = deltaR(*it,calojet);
    double outeta = info.trkGlobPosAtEcal.eta();
    double outphi = info.trkGlobPosAtEcal.phi();
    double dRout  = deltaR(calojet.eta(),calojet.phi(),outeta,outphi);
    if (dRin < conesize_ || dRout < conesize_){
      saveTrack=true;
    }
    /*
    std::cout<<"trackpt["<<iTrack<<"]       ="<< it->pt()<<std::endl;
    std::cout<<"trackemc1["<<iTrack<<"]     ="<< info.nXnEnergy(TrackDetMatchInfo::EcalRecHits, 0)<<std::endl;
    std::cout<<"trackemc3["<<iTrack<<"]     ="<< info.nXnEnergy(TrackDetMatchInfo::EcalRecHits, 1)<<std::endl;
    std::cout<<"trackemc5["<<iTrack<<"]     ="<< info.nXnEnergy(TrackDetMatchInfo::EcalRecHits, 2)<<std::endl;
    std::cout<<"trackecaltow1["<<iTrack<<"] ="<< info.nXnEnergy(TrackDetMatchInfo::TowerEcal, 0)<<std::endl;
    std::cout<<"trackecaltow3["<<iTrack<<"] ="<< info.nXnEnergy(TrackDetMatchInfo::TowerEcal, 1)<<std::endl;
    std::cout<<"trackecaltow5["<<iTrack<<"] ="<< info.nXnEnergy(TrackDetMatchInfo::TowerEcal, 2)<<std::endl;
    std::cout<<"trackhcaltow1["<<iTrack<<"] ="<< info.nXnEnergy(TrackDetMatchInfo::TowerHcal, 0)<<std::endl;
    std::cout<<"trackhcaltow3["<<iTrack<<"] ="<< info.nXnEnergy(TrackDetMatchInfo::TowerHcal, 1)<<std::endl;
    std::cout<<"trackhcaltow5["<<iTrack<<"] ="<< info.nXnEnergy(TrackDetMatchInfo::TowerHcal, 2)<<std::endl;
    std::cout<<"trackecalrh1["<<iTrack<<"] ="<< info.nXnEnergy(TrackDetMatchInfo::EcalRecHits, 0)<<std::endl;
    std::cout<<"trackecalrh3["<<iTrack<<"] ="<< info.nXnEnergy(TrackDetMatchInfo::EcalRecHits, 1)<<std::endl;
    std::cout<<"trackecalrh5["<<iTrack<<"] ="<< info.nXnEnergy(TrackDetMatchInfo::EcalRecHits, 2)<<std::endl;
    std::cout<<"trackhcalrh1["<<iTrack<<"] ="<< info.nXnEnergy(TrackDetMatchInfo::HcalRecHits, 0)<<std::endl;
    std::cout<<"trackhcalrh3["<<iTrack<<"] ="<< info.nXnEnergy(TrackDetMatchInfo::HcalRecHits, 1)<<std::endl;
    std::cout<<"trackhcalrh5["<<iTrack<<"] ="<< info.nXnEnergy(TrackDetMatchInfo::HcalRecHits, 2)<<std::endl;
    */
    if (saveTrack){
      trackpt[iTrack]     = it->pt();
      tracketa[iTrack]    = it->eta();
      trackphi[iTrack]    = it->phi();
      trackp[iTrack]      = it->p();
      trackdr[iTrack]     = dRin;
      trackdrout[iTrack]  = dRout;
      tracketaout[iTrack] = outeta;
      trackphiout[iTrack] = outphi;
      trackemc1[iTrack]   = info.nXnEnergy(TrackDetMatchInfo::EcalRecHits, 0);
      trackemc3[iTrack]   = info.nXnEnergy(TrackDetMatchInfo::EcalRecHits, 1);
      trackemc5[iTrack]   = info.nXnEnergy(TrackDetMatchInfo::EcalRecHits, 2);
      trackhac1[iTrack]   = info.nXnEnergy(TrackDetMatchInfo::HcalRecHits, 0);
      trackhac3[iTrack]   = info.nXnEnergy(TrackDetMatchInfo::HcalRecHits, 1);
      trackhac5[iTrack]   = info.nXnEnergy(TrackDetMatchInfo::HcalRecHits, 2);
      DetId centerId = info.findMaxDeposition(TrackDetMatchInfo::HcalRecHits);
      HcalDetId HcalCenterId(centerId);
      tracktowidphi[iTrack] = HcalCenterId.iphi();
      tracktowideta[iTrack] = HcalCenterId.ieta();
      tracktowid[iTrack]    = centerId.rawId();
      trackchi2[iTrack]     = it->normalizedChi2();
      tracknhits[iTrack]    = it->numberOfValidHits();

      trackQuality[iTrack] = -10;      
      if(it->quality(reco::TrackBase::undefQuality)) trackQuality[iTrack] = -1;
      if(it->quality(reco::TrackBase::loose))  trackQuality[iTrack] = 0;
      if(it->quality(reco::TrackBase::tight))  trackQuality[iTrack] = 1;
      if(it->quality(reco::TrackBase::highPurity)) trackQuality[iTrack] = 2; 
      if(it->quality(reco::TrackBase::confirmed))  trackQuality[iTrack] = 3;
      if(it->quality(reco::TrackBase::goodIterative))  trackQuality[iTrack] = 4;
      if(it->quality(reco::TrackBase::qualitySize))  trackQuality[iTrack] = 5;
      /*
	std::cout<<"rawId: "<<centerId.rawId()
	       <<"iphiId: "<<HcalCenterId.iphi()
	       <<"ietaId: "<<HcalCenterId.ieta()
	       <<std::endl;
      */
      
      //Match track with muons
      muDR[iTrack] = -1;
      muDE[iTrack] = -1;
      bool muonMatch = false;
      //for(reco::MuonCollection::const_iterator im = muons->begin(); im != muons->end(); ++im) {
      for(reco::TrackCollection::const_iterator im = muons->begin(); im != muons->end(); ++im) {
	double dRm = deltaR(*im,*it);
	double dE = fabs( (im->pt()-it->pt())/it->pt() );
	muDR[iTrack] = dRm;
	muDE[iTrack] = dE;
	if (dRm<0.1 && dE < 0.2) muonMatch = true;
      }
      if (muonMatch) {
	trackid[iTrack] = 13;
      } else {
	trackid[iTrack] = 0;
      }
      ++iTrack;
    }
  }
  NobjTrack=iTrack;

  CalibTree->Fill();
}
