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
  zspJets_          = cfg.getParameter<edm::InputTag>("ZJetZSPJets");
  pfJets_          = cfg.getParameter<edm::InputTag>("ZJetPFJets");
  caloJets_          = cfg.getParameter<edm::InputTag>("ZJetCaloJets");

   
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

  //PFCluster data
  clusterenergy  = new float [ kMAX ];
  clustereta = new float [ kMAX ];
  clusterphi = new float [ kMAX ];
  clustertype  = new int [ kMAX ];
  clusterid    = new int [ kMAX ];

  //PFClusterData
  CalibTree->Branch( "NobjCluster", &NobjCluster, "NobjCluster/I" );
  CalibTree->Branch( "ClusterEnergy", clusterenergy, "ClusterEnergy[NobjCluster]/F" );
  CalibTree->Branch( "ClusterEta", clustereta, "ClusterEta[NobjCluster]/F" );
  CalibTree->Branch( "ClusterPhi", clusterphi, "ClusterPhi[NobjCluster]/F" );
  CalibTree->Branch( "ClusterType", clustertype, "ClusterType[NobjCluster]/I" ); //0=HCAL, 1=ECAL, 2=PS1, 3=PS4,      4=GSF, 5=Brems
  CalibTree->Branch( "ClusterId", clusterid, "ClusterID[NobjCluster]/I" );

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
  trackpt        = new float [ kMAX ];
  tracketa       = new float [ kMAX ];
  trackphi       = new float [ kMAX ];
  trackp         = new float [ kMAX ];
  trackdr        = new float [ kMAX ];
  tracketaout    = new float [ kMAX ];
  trackphiout    = new float [ kMAX ];
  trackdrout     = new float [ kMAX ];
  trackemc1      = new float [ kMAX ];
  trackemc3      = new float [ kMAX ];
  trackemc5      = new float [ kMAX ];
  trackhac1      = new float [ kMAX ];
  trackhac3      = new float [ kMAX ];
  trackhac5      = new float [ kMAX ];
  tracktowid     = new int [ kMAX ];
  tracktowidphi  = new int [ kMAX ];
  tracktowideta  = new int [ kMAX ];
  trackid        = new int[ kMAX ]; // abs(PiD) if available, guess: muons only; =0: unknown
  tracknhits     = new int[ kMAX ];
  trackQualityL  = new bool[kMAX];
  trackQualityT  = new bool[kMAX];
  trackQualityHP = new bool[kMAX];
  trackchi2      = new float[ kMAX ];
  muDR           = new float[ kMAX ];
  muDE           = new float[ kMAX ];
  clustHID       = new int  [ kMAX ];  //closest HCAL Cluster
  clustHDR       = new float[ kMAX ];  //closest HCAL Cluster distance
  clustEID       = new int  [ kMAX ];  //closest ECAL Cluster
  clustEDR       = new float[ kMAX ];  //closest ECAL Cluster distance
  clustPS1ID     = new int  [ kMAX ];  //closest PS1 Cluster
  clustPS1DR     = new float[ kMAX ];  //closest PS1 Cluster distance
  clustPS2ID     = new int  [ kMAX ];  //closest PS2 Cluster
  clustPS2DR     = new float[ kMAX ];  //closest PS2 Cluster distance
  clustHEnergy   = new float[ kMAX ]; 
  clustEEnergySum = new float[ kMAX ];  //Sum of all linked ECAL Clusters

  //track branches
  CalibTree->Branch( "NobjTrack",  &NobjTrack, "NobjTrack/I"             );
  CalibTree->Branch( "TrackTowId", tracktowid, "TrackTowId[NobjTrack]/I" );
  CalibTree->Branch( "TrackTowIdPhi", tracktowidphi, "TrackTowIdPhi[NobjTrack]/I" );
  CalibTree->Branch( "TrackTowIdEta", tracktowideta, "TrackTowIdEta[NobjTrack]/I" );
  CalibTree->Branch( "TrackId",    trackid,    "TrackId[NobjTrack]/I"    );
  CalibTree->Branch( "TrackNHits", tracknhits, "TrackNHits[NobjTrack]/I" );
  CalibTree->Branch( "TrackQualityL",trackQualityL,"TrackQualityL[NobjTrack]/O");
  CalibTree->Branch( "TrackQualityT",trackQualityT,"TrackQualityT[NobjTrack]/O");
  CalibTree->Branch( "TrackQualityHP",trackQualityHP,"TrackQualityHP[NobjTrack]/O");
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
  CalibTree->Branch( "ClustHID",  clustHID,  "ClustHID[NobjTrack]/I"  );
  CalibTree->Branch( "ClustHDR",  clustHDR,  "ClustHDR[NobjTrack]/F"  );
  CalibTree->Branch( "ClustEID",  clustEID,  "ClustEID[NobjTrack]/I"  );
  CalibTree->Branch( "ClustEDR",  clustEDR,  "ClustEDR[NobjTrack]/F"  );
  CalibTree->Branch( "ClustPS1ID",  clustPS1ID,  "ClustPS1ID[NobjTrack]/I"  );
  CalibTree->Branch( "ClustPS1DR",  clustPS1DR,  "ClustPS1DR[NobjTrack]/F"  );
  CalibTree->Branch( "ClustPS2ID",  clustPS2ID,  "ClustPS2ID[NobjTrack]/I"  );
  CalibTree->Branch( "ClustPS2DR",  clustPS2DR,  "ClustPS2DR[NobjTrack]/F"  );
  CalibTree->Branch( "ClustHEnergy",  clustHEnergy,  "ClustHEnergy[NobjTrack]/F"  );
  CalibTree->Branch( "ClustEEnergySum",  clustEEnergySum,  "ClustEEnergySum[NobjTrack]/F"  );

  // CaloJet branches 
  CalibTree->Branch( "JetCalPt",  &jcalpt,    "JetCalPt/F"  );
  CalibTree->Branch( "JetCalPhi", &jcalphi,   "JetCalPhi/F" );
  CalibTree->Branch( "JetCalEta", &jcaleta,   "JetCalEta/F" );
  CalibTree->Branch( "JetCalEt",  &jcalet,    "JetCalEt/F"  );
  CalibTree->Branch( "JetCalE",   &jcale,     "JetCalE/F"   );
  CalibTree->Branch( "JetCalEMF",   &jEMF,     "JetCalEMF/F"   );
  CalibTree->Branch( "JetCorrZSP",&jscaleZSP, "JetCorrZSP/F" );
  CalibTree->Branch( "JetCorrL2", &jscalel2,  "JetCorrL2/F" );
  CalibTree->Branch( "JetCorrL3", &jscalel3,  "JetCorrL3/F" );
  CalibTree->Branch( "JetCorrJPT",&jscaleJPT, "JetCorrJPT/F" );
  CalibTree->Branch( "JetCorrPFLOW",&jscalePFLOW, "JetCorrPFLOW/F" );
  CalibTree->Branch( "JetCorrL2L3", &jscalel2l3,  "JetCorrL2L3/F" );
  CalibTree->Branch( "JetCorrL2L3JPT", &jscalel2l3JPT,  "JetCorrL2L3JPT/F" );
  CalibTree->Branch( "JetCorrL2L3PFLOW",&jscalel2l3PFLOW, "JetCorrL2L3PFLOW/F" );
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
  using namespace reco;
  if(weight_<0)
    {
      edm::Handle<double> weightHandle;
      evt.getByLabel (weight_tag, weightHandle);
      weight =(float)( *weightHandle);
    }
  else weight = weight_;

  edm::Handle<CaloJetCollection> jet;
  evt.getByLabel(jets_, jet);

  edm::Handle<GenJetCollection> genJet;
  evt.getByLabel(genjets_,genJet);

  edm::Handle<std::vector<reco::Particle> > z;
  evt.getByLabel(z_,z);

  edm::Handle<GenParticleCollection> genZ;
  evt.getByLabel(genzs_,genZ);

  edm::Handle<CaloMETCollection> met;
  evt.getByLabel(met_,met);

  edm::Handle<double> NonLeadingJetsPt;
  evt.getByLabel( nonleadingjetspt_, NonLeadingJetsPt ); 

  // get calo jet after zsp correction
  edm::Handle<CaloJetCollection> zspJets;
  evt.getByLabel(zspJets_, zspJets);

  //PFlow
  edm::Handle<PFJetCollection> pfJets;
  evt.getByLabel(pfJets_, pfJets);

  edm::Handle<PFBlockCollection> pfBlocks;
  evt.getByLabel("particleFlowBlock", pfBlocks);

  //calo jets to check for jet-track ambigueties
  edm::Handle<CaloJetCollection> otherCaloJets;
  evt.getByLabel(caloJets_, otherCaloJets);


  const CaloJet calojet = *jet->begin();
  const GenJet genjet = *genJet->begin();
  const GenParticle  genz = *genZ->begin(); 
  const GenParticle  Z;//*z->begin(); 
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
  //std::string l1name = "ZSPJetCorrector";
  std::string JPTname = "JetPlusTrackZSPCorrectorScone5";
  std::string l2l3name = "L2L3JetCorrectorSC5Calo";
  std::string l2l3JPTname = "L2L3JetCorrectorIC5JPT";
  std::string l2l3PFlowname = "L2L3JetCorrectorSC5PF";

  const JetCorrector* correctorL2   = JetCorrector::getJetCorrector (l2name,setup);   //Define the jet corrector
  const JetCorrector* correctorL3   = JetCorrector::getJetCorrector (l3name,setup);   //Define the jet corrector
  //const JetCorrector* correctorL1   = JetCorrector::getJetCorrector (l1name,setup);   //Define the jet corrector
  const JetCorrector* correctorJPT  = JetCorrector::getJetCorrector (JPTname, setup); //Define the jet corrector
  const JetCorrector* correctorL2L3  = JetCorrector::getJetCorrector (l2l3name, setup); //Define the jet corrector
  const JetCorrector* correctorL2L3JPT  = JetCorrector::getJetCorrector (l2l3JPTname, setup); //Define the jet corrector
  const JetCorrector* correctorL2L3PFlow  = JetCorrector::getJetCorrector (l2l3PFlowname, setup); //Define the jet corrector

  jscalel2   = correctorL2  ->correction(calojet.p4());  //calculate the correction
  jscalel3   = correctorL3  ->correction(calojet.p4());  //calculate the correction
  jscalel2l3   = correctorL2L3  ->correction(calojet.p4());  //calculate the correction

  for( reco::CaloJetCollection::const_iterator zspJet = zspJets->begin(); zspJet != zspJets->end(); ++zspJet)
      {
	if( deltaR(zspJet->eta(),zspJet->phi(), calojet.eta() , calojet.phi()) < 0.01)//no change in R
	  {
	    jscaleZSP = zspJet->et()/calojet.et();
	    jscaleJPT = correctorJPT ->correction((*zspJet));  //calculate the correction
	    jscalel2l3JPT   = correctorL2L3JPT  ->correction(zspJet->p4() * jscaleJPT );  //calculate the correction
	  }
      }
  //jscalel1   = correctorL1  ->correction(calojet.p4());  //calculate the correction

  /*
  cout<<" Jet Pt = "<<calojet.pt()
      <<" Jet Eta = "<<calojet.eta()
      <<" Scale L2 = "<<jscalel2
      <<" Scale L3 = "<<jscalel3
      <<endl;
  */
  double deltaMin = 100;
  reco::PFJet MyPFJet;
  for( reco::PFJetCollection::const_iterator pfJet = pfJets->begin(); pfJet != pfJets->end(); ++pfJet)
      {
	double deltaTemp =  deltaR(pfJet->eta(),pfJet->phi(), calojet.eta() , calojet.phi());
	if(deltaTemp < deltaMin) //closest in R
	  {
	    deltaMin = deltaTemp ;
	    MyPFJet = *pfJet;
	    //zspJet->et()/calojet.et();
	    jscalePFLOW = pfJet->et()/calojet.et();
	    jscalel2l3PFLOW   = correctorL2L3PFlow ->correction(pfJet->p4() );  //calculate the correction
	  }
      }
  


  /*
  std::vector<const reco::PFCandidate*> MyPFConstituents=  MyPFJet.getPFConstituents();
  double temp=0;
  double temp1;
  for( unsigned int prim=0; prim!= MyPFConstituents.size(); ++prim) {
    temp +=MyPFConstituents.at(prim)->pt();
    reco::TrackRef MyPFTrackRef = MyPFConstituents.at(prim)->trackRef();
    temp1=0;
    if(MyPFTrackRef.isNonnull())   temp1 = MyPFTrackRef->pt();
    cout<<"TrackPt: "<<temp1<<"   ClusterPt - TrackPt: "<<MyPFConstituents.at(prim)->pt() - temp1<<endl;
  }
  
  cout<<"DeltaR: "<<deltaMin<<" DeltaPt: "<<MyPFJet.pt() - calojet.pt()<<"  Jet: "<<MyPFJet.pt()<<"   SumConst: "<<temp<<"    Calo Jet: "<<calojet.pt()<<endl;
  */
  NobjCluster = 0;
  int clusternumber = 0;
  for(reco::PFBlockCollection::const_iterator pfBlock = pfBlocks->begin(); pfBlock != pfBlocks->end(); ++pfBlock)
    {
      edm::OwnVector<reco::PFBlockElement> MyPFBlockElements=  pfBlock->elements();
      for(edm::OwnVector<reco::PFBlockElement>::const_iterator pfElement = MyPFBlockElements.begin(); pfElement != MyPFBlockElements.end();++pfElement) {
	if(!(pfElement->type() == reco::PFBlockElement::TRACK || pfElement->type() == reco::PFBlockElement::NONE || pfElement->type() == reco::PFBlockElement::GSF || pfElement->type() == reco::PFBlockElement::BREM )){
	  if(deltaR(pfElement->clusterRef()->eta(),pfElement->clusterRef()->phi(), calojet.eta() , calojet.phi())  < 0.5)  //in cone
	    {
	      clusterenergy[NobjCluster] = pfElement->clusterRef()->energy();
	      clustereta[NobjCluster] = pfElement->clusterRef()->eta();
	      clusterphi[NobjCluster] = pfElement->clusterRef()->phi();
	      //clusterid[NobjCluster] = pfElement->clusterRef().id().id();  //index();
	      clusterid[NobjCluster] =clusternumber;
	      if(pfElement->type() == reco::PFBlockElement::HCAL)
		clustertype[NobjCluster] = 0;
	      if(pfElement->type() == reco::PFBlockElement::ECAL)
		clustertype[NobjCluster] = 1;
	      if(pfElement->type() == reco::PFBlockElement::PS1)
		clustertype[NobjCluster] = 2;
	      if(pfElement->type() == reco::PFBlockElement::PS2)
		clustertype[NobjCluster] = 3;
	      //if(pfElement->type() == reco::PFBlockElement::GSF)
	      //clustertype[nocluster] = 4;
	      //if(pfElement->type() == reco::PFBlockElement::BREM)
	      //clustertype[nocluster] = 5;
	      ++NobjCluster;		
	    }
	}
	/*
	  else{
	  if(pfElement->type() == reco::PFBlockElement::TRACK){      //or linked track in cone
	  DR = deltaR(pfElement->trackRef()->eta(),pfElement->trackRef()->phi(), it->eta() , it->phi());
	  if(DR < DRmin){
	  DRmin = DR;
	  PFTrackIndex = pfElement->index();
	  }
	  }
	  }
	*/
	++clusternumber;
      }
    }
  

  jcalpt  = calojet.pt();
  jcalphi = calojet.phi();
  jcaleta = calojet.eta();
  jcalet  = calojet.et();
  jcale   = calojet.energy();
  jEMF    = 1 - calojet.energyFractionHadronic();

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
 
//   zpt  = Z.pt();
//   zphi = Z.phi();
//   zeta = Z.eta();
//   zet  = Z.et();
//   ze   = Z.energy();
 
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
  edm::Handle<reco::MuonCollection> muons;
  //edm::Handle<reco::TrackCollection> muons;
  evt.getByLabel(recMuons_,muons);

  // see here for detailed track cluster matching and jet track association
  //   -> CMSSW/TrackingTools/TrackAssociator/test/CaloMatchingExample.cc

  int iTrack = 0;
  for(reco::TrackCollection::const_iterator it = tracks->begin(); it != tracks->end(); ++it) {
    // skip low Pt tracks
    //if (it->pt() < 1) continue;
    bool saveTrack = false;
    TrackDetMatchInfo info = trackAssociator_.associate(evt, setup, *it, parameters_);

    double dRin   = deltaR(*it,calojet);
    double outeta = info.trkGlobPosAtEcal.eta();
    double outphi = info.trkGlobPosAtEcal.phi();
    double dRout  = deltaR(calojet.eta(),calojet.phi(),outeta,outphi);

    //loop over other jets to see, if that one is closer (dRin) or constituent (dRout)
    for( reco::CaloJetCollection::const_iterator otherCaloJet = otherCaloJets->begin(); otherCaloJet != otherCaloJets->end(); ++otherCaloJet)
      {
	//inner part
	if(deltaR(*it,*otherCaloJet) < dRin && (otherCaloJet->eta() != calojet.eta()) )
	  dRin = 1000;
	//outer part
	bool inJet = false;
	std::vector <CaloTowerPtr> towers = calojet.getCaloConstituents();
	for(unsigned int i = 0; i<towers.size();++i)
	  {
	    //if(info.findMaxDeposition(TrackDetMatchInfo::EnergyType::TowerTotal) == towers[i].id())
	    for(unsigned int a = 0; a < towers[i].get()->constituentsSize(); ++a)
	      {
		if(info.findMaxDeposition(TrackDetMatchInfo::TowerTotal).rawId() == towers[i].get()->constituent(a).rawId())
		  inJet =true;
	      }
	  }
	if(!inJet)   dRout = 1000;
      }

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
      clustEEnergySum[iTrack] = 0;
      clustHEnergy[iTrack] = 0;
      clustHID[iTrack] = -1;
      clustEID[iTrack] = -1;
      int PFTrackIndex = 0;
      double DRmin = 100;
      reco::PFBlockCollection::const_iterator TrackBlock;
      for(reco::PFBlockCollection::const_iterator pfBlock = pfBlocks->begin(); pfBlock != pfBlocks->end(); ++pfBlock)
	{
	  double DR;
	  edm::OwnVector<reco::PFBlockElement> MyPFBlockElements=  pfBlock->elements();
	  for(edm::OwnVector<reco::PFBlockElement>::const_iterator pfElement = MyPFBlockElements.begin(); pfElement != MyPFBlockElements.end();++pfElement) {
	    if(pfElement->type() == reco::PFBlockElement::TRACK){
	      DR = deltaR(pfElement->trackRef()->eta(),pfElement->trackRef()->phi(), it->eta() , it->phi());
	      if(DR < DRmin){
		DRmin = DR;
		PFTrackIndex = pfElement->index();
		TrackBlock = pfBlock;
	      }
	    }
	  }
	}
      DRmin = 100;
      double DRminE = 100;
      double DRminPS1 = 100;
      double DRminPS2 = 100; 
      clusternumber = -1;
      for(reco::PFBlockCollection::const_iterator pfBlock = pfBlocks->begin(); pfBlock != pfBlocks->end(); ++pfBlock)
	{
	  double dist;
	  edm::OwnVector<reco::PFBlockElement> MyPFBlockElements=  pfBlock->elements();
	  for(edm::OwnVector<reco::PFBlockElement>::const_iterator pfElement = MyPFBlockElements.begin(); pfElement != MyPFBlockElements.end();++pfElement) {
	    ++clusternumber;
	    if(TrackBlock != pfBlock)  continue;
	    double temp = 100;// pfBlock->dist(PFTrackIndex, pfElement->index(),pfBlock->linkData(),reco::PFBlock::LINKTEST_CHI2); 
	    if(temp>-1)
	      {	    
	      dist = temp;
	      }
	    else 
	      dist = 100;

	    if(pfElement->type() == reco::PFBlockElement::HCAL){
	      //if(deltaR(pfElement->trackRef()->eta(),pfElement->trackRef()->phi(), calojet.eta() , calojet.phi())<0.5)
	      if(dist <DRmin){
		DRmin = dist;
		clustHID[iTrack] = clusternumber;//pfElement->clusterRef().id().id();  //index();
		clustHEnergy[iTrack] = pfElement->clusterRef()->energy();
	      }
	    }
	    if(pfElement->type() == reco::PFBlockElement::ECAL){
	      //if(deltaR(pfElement->trackRef()->eta(),pfElement->trackRef()->phi(), calojet.eta() , calojet.phi())<0.5)
	      if(dist <DRminE){
		DRminE = dist;
		clustEID[iTrack] = clusternumber;//pfElement->clusterRef().id().id();  //index();
	      }
	      if(dist < 0.5)
		clustEEnergySum[iTrack] += pfElement->clusterRef()->energy();
	    }
	    if(pfElement->type() == reco::PFBlockElement::PS1){
	      //if(deltaR(pfElement->trackRef()->eta(),pfElement->trackRef()->phi(), calojet.eta() , calojet.phi())<0.5)
	      if(dist <DRminPS1){
		DRminPS1 = dist;
		clustPS1ID[iTrack] = clusternumber;//pfElement->clusterRef().id().id();  //index();
	      }
	    }
	    if(pfElement->type() == reco::PFBlockElement::PS2){
	      //if(deltaR(pfElement->trackRef()->eta(),pfElement->trackRef()->phi(), calojet.eta() , calojet.phi())<0.5)
	      if(dist <DRminPS2){
		DRminPS2 = dist;
		clustPS2ID[iTrack] = clusternumber;//pfElement->clusterRef().id().id();  //index();
	      }
	    }

	  }
	}

      //cout<<"Track: "<<it->p()<<"    HCAL-Cluster: "<<clustHEnergy[iTrack]<<"    ECAL Sum: "<<clustEEnergySum[iTrack]<<"     Sum: "<<clustEEnergySum[iTrack] + clustHEnergy[iTrack]<<endl;
      clustHDR[iTrack] = DRmin;
      clustEDR[iTrack] = DRminE;
      clustPS1DR[iTrack] = DRminPS1;
      clustPS2DR[iTrack] = DRminPS2;

      
      
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
   
      //if(it->quality(reco::TrackBase::undefQuality)) trackQuality[iTrack] = -1;
      if(it->quality(reco::TrackBase::loose))  trackQualityL[iTrack] = true;
      else  trackQualityL[iTrack] = false;
      if(it->quality(reco::TrackBase::tight))  trackQualityT[iTrack] = true;
      else  trackQualityT[iTrack] = false;
      if(it->quality(reco::TrackBase::highPurity)) trackQualityHP[iTrack] = true; 
      else  trackQualityHP[iTrack] = false;
      //if(it->quality(reco::TrackBase::confirmed))  trackQuality[iTrack] = 3;
      //if(it->quality(reco::TrackBase::goodIterative))  trackQuality[iTrack] = 4;
      //if(it->quality(reco::TrackBase::qualitySize))  trackQuality[iTrack] = 5;
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
      for(reco::MuonCollection::const_iterator im = muons->begin(); im != muons->end(); ++im) {
	//for(reco::TrackCollection::const_iterator im = muons->begin(); im != muons->end(); ++im) {
// 	if(im->isGood(reco::Muon::AllGlobalMuons) && im->isGood(reco::Muon::TMLastStationLoose)) continue;
// 	double dRm = deltaR(*im,*it);
// 	double dE = fabs( (im->pt()-it->pt())/it->pt() );
// 	muDR[iTrack] = dRm;
// 	muDE[iTrack] = dE;
// 	if (dRm<0.1 && dE < 0.2) muonMatch = true;
      }
      if (muonMatch) {
	trackid[iTrack] = 13;
      }
      else {
	trackid[iTrack] = 0;
      }
      ++iTrack;
    }
  }
  NobjTrack=iTrack;

  CalibTree->Fill();
}
