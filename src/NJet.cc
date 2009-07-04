#include "Calibration/CalibTreeMaker/interface/NJet.h"
#include "DataFormats/METReco/interface/CaloMET.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"

void NJet::setup(const edm::ParameterSet& cfg, TTree* CalibTree)
{
  // Read parameters
  jets_          = cfg.getParameter<edm::InputTag>("NJet_Jets");
  genjets_       = cfg.getParameter<edm::InputTag>("NJet_GenJets");
  genparticles_  = cfg.getParameter<edm::InputTag>("NJet_GenParticles");
  met_           = cfg.getParameter<edm::InputTag>("NJet_MET");
  weight_        = (float)(cfg.getParameter<double> ("NJet_Weight"));
  weight_tag     = cfg.getParameter<edm::InputTag> ("NJet_Weight_Tag");
  recTracks_     = cfg.getParameter<edm::InputTag>("NJetRecTracks");
  recMuons_      = cfg.getParameter<edm::InputTag>("NJetRecMuons");
  conesize_      = cfg.getParameter<double>("NJetConeSize");
  zspJets_       = cfg.getParameter<edm::InputTag>("NJetZSPJets");
  genEvtScale_   = cfg.getParameter<edm::InputTag>("GenEventScaleLabel");
  writeEcalCells = cfg.getParameter<bool>("WriteEcalCells");

  // TrackAssociator parameters
  edm::ParameterSet parameters = cfg.getParameter<edm::ParameterSet>("TrackAssociatorParameters");
  parameters_.loadParameters( parameters );
  trackAssociator_.useDefaultPropagator();




  // Set up branches

  // CaloTower branches for all jets
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


  // track branches
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
  track_jetidx   = new int[ kMAX ];
  trackid        = new int[ kMAX ]; // abs(PiD) if available, guess: muons only; =0: unknown
  tracknhits     = new int[ kMAX ]; 
  trackQualityL  = new bool[kMAX];
  trackQualityT  = new bool[kMAX];
  trackQualityHP = new bool[kMAX];
  trackchi2      = new float[ kMAX ];
  muDR           = new float[ kMAX ];
  muDE           = new float[ kMAX ];

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
  CalibTree->Branch( "Track_jetidx",track_jetidx, "Track_jetidx[NobjTrack]/I");
  CalibTree->Branch( "MuDR", muDR,  "MuDR[NobjTrack]/F"  );
  CalibTree->Branch( "MuDE", muDE,  "MuDE[NobjTrack]/F"  );


  //All calo jets
  jetpt           = new float [ kjMAX ];
  jetphi          = new float [ kjMAX ];
  jeteta          = new float [ kjMAX ];
  jetet           = new float [ kjMAX ];
  jete            = new float [ kjMAX ];
  jetgenjetDeltaR = new float [ kjMAX ];
  jscaleZSP       = new float [ kjMAX ];
  jscalel2        = new float [ kjMAX ];
  jscalel3        = new float [ kjMAX ];
  jscaleJPT       = new float [ kjMAX ];
  jscalel2l3      = new float [ kjMAX ];
  jscalel2l3JPT   = new float [ kjMAX ];
  //jscalel2l2PFlow  = new float [ kjMAX ]; 
  for(int i = 0; i < kjMAX; i++) {
    jscaleZSP[i]      = 1.;
    jscalel2[i]       = 1.;
    jscalel3[i]       = 1.;
    jscaleJPT[i]      = 1.;
    jscalel2l3[i]     = 1.;
    jscalel2l3JPT[i]  = 1.;
  }

  CalibTree->Branch( "NobjJet",            &NobjJet,         "NobjJet/I"             );
  CalibTree->Branch( "JetPt",               jetpt,           "JetPt[NobjJet]/F" );
  CalibTree->Branch( "JetPhi",              jetphi,          "JetPhi[NobjJet]/F");
  CalibTree->Branch( "JetEta",              jeteta,          "JetEta[NobjJet]/F");
  CalibTree->Branch( "JetEt",               jetet,           "JetEt[NobjJet]/F" );
  CalibTree->Branch( "JetE",                jete,            "JetE[NobjJet]/F"  );
  CalibTree->Branch( "JetGenJetDeltaR",     jetgenjetDeltaR, "JetGenJetDeltaR[NobjJet]/F"  );
  CalibTree->Branch( "JetCorrZSP",          jscaleZSP,       "JetCorrZSP[NobjJet]/F" );
  CalibTree->Branch( "JetCorrL2",           jscalel2,        "JetCorrL2[NobjJet]/F" );
  CalibTree->Branch( "JetCorrL3",           jscalel3,        "JetCorrL3[NobjJet]/F" );
  CalibTree->Branch( "JetCorrJPT",          jscaleJPT,       "JetCorrJPT[NobjJet]/F" );
  CalibTree->Branch( "JetCorrL2L3",         jscalel2l3,      "JetCorrL2L3[NobjJet]/F" );
  CalibTree->Branch( "JetCorrL2L3JPT",      jscalel2l3JPT,   "JetCorrL2L3JPT[NobjJet]/F" );
  //CalibTree->Branch( "JetCorrL2L3PFlow",  jscalel2l3PFlow, "JetCorrL2L3PFlow[NobjJet]/F" );


  // Gen jets (matched to calo jets)
  genjetpt       = new float [ kjMAX ];
  genjetphi      = new float [ kjMAX ];
  genjeteta      = new float [ kjMAX ];
  genjetet       = new float [ kjMAX ];
  genjete        = new float [ kjMAX ];

  CalibTree->Branch( "GenJetPt",            genjetpt,       "GenJetPt[NobjJet]/F" );
  CalibTree->Branch( "GenJetPhi",           genjetphi,      "GenJetPhi[NobjJet]/F");
  CalibTree->Branch( "GenJetEta",           genjeteta,      "GenJetEta[NobjJet]/F");
  CalibTree->Branch( "GenJetEt",            genjetet,       "GenJetEt[NobjJet]/F" );
  CalibTree->Branch( "GenJetE",             genjete,        "GenJetE[NobjJet]/F"  );


  // Gen jet collection
  genjetcolpt       = new float [ kjMAX ];
  genjetcolphi      = new float [ kjMAX ];
  genjetcoleta      = new float [ kjMAX ];
  genjetcolet       = new float [ kjMAX ];
  genjetcole        = new float [ kjMAX ];
  genjetcol_jet_idx = new int   [ kjMAX ];

  CalibTree->Branch( "NobjGenJet",     &NobjGenJet,        "NobjGenJet/I"                 );
  CalibTree->Branch( "GenJetColPt",     genjetcolpt,       "GenJetColPt[NobjGenJet]/F"    );
  CalibTree->Branch( "GenJetColPhi",    genjetcolphi,      "GenJetColPhi[NobjGenJet]/F"   );
  CalibTree->Branch( "GenJetColEta",    genjetcoleta,      "GenJetColEta[NobjGenJet]/F"   );
  CalibTree->Branch( "GenJetColEt",     genjetcolet,       "GenJetColEt[NobjGenJet]/F"    );
  CalibTree->Branch( "GenJetColE",      genjetcole,        "GenJetColE[NobjGenJet]/F"     );
  CalibTree->Branch( "GenJetColJetIdx", genjetcol_jet_idx, "GenJetColJetIdx[NobjGenJet]/I");



  // Matched gen particles
  // Alogrithmic matching
  genpartpt_algo     = new float [ kjMAX ];
  genpartphi_algo    = new float [ kjMAX ];
  genparteta_algo    = new float [ kjMAX ];
  genpartet_algo     = new float [ kjMAX ];
  genparte_algo      = new float [ kjMAX ];
  genpartm_algo      = new float [ kjMAX ];
  genpartid_algo     = new int   [ kjMAX ];
  // GenPart_algo branches        );
  CalibTree->Branch( "GenPartPt_algo", genpartpt_algo, "GenPartPt_algo[NobjJet]/F" );
  CalibTree->Branch( "GenPartPhi_algo",genpartphi_algo,"GenPartPhi_algo[NobjJet]/F");
  CalibTree->Branch( "GenPartEta_algo",genparteta_algo,"GenPartEta_algo[NobjJet]/F");
  CalibTree->Branch( "GenPartEt_algo", genpartet_algo, "GenPartEt_algo[NobjJet]/F" );
  CalibTree->Branch( "GenPartE_algo",  genparte_algo,  "GenPartE_algo[NobjJet]/F"  );
  CalibTree->Branch( "GenPartM_algo",  genpartm_algo,  "GenPartM_algo[NobjJet]/F"  );
  CalibTree->Branch( "GenPartId_algo", genpartid_algo, "GenPartId_algo[NobjJet]/I" );

  // Physical matching
  genpartpt_phys      = new float [ kjMAX ];
  genpartphi_phys     = new float [ kjMAX ];
  genparteta_phys     = new float [ kjMAX ];
  genpartet_phys      = new float [ kjMAX ];
  genparte_phys       = new float [ kjMAX ];
  genpartm_phys       = new float [ kjMAX ];
  genpartid_phys      = new int   [ kjMAX ];
  // GenPart_phys branches        );
  CalibTree->Branch( "GenPartPt_phys", genpartpt_phys, "GenPartPt_phys[NobjJet]/F" );
  CalibTree->Branch( "GenPartPhi_phys",genpartphi_phys,"GenPartPhi_phys[NobjJet]/F");
  CalibTree->Branch( "GenPartEta_phys",genparteta_phys,"GenPartEta_phys[NobjJet]/F");
  CalibTree->Branch( "GenPartEt_phys", genpartet_phys, "GenPartEt_phys[NobjJet]/F" );
  CalibTree->Branch( "GenPartE_phys",  genparte_phys,  "GenPartE_phys[NobjJet]/F"  );
  CalibTree->Branch( "GenPartM_phys",  genpartm_phys,  "GenPartM_phys[NobjJet]/F"  );
  CalibTree->Branch( "GenPartId_phys", genpartid_phys, "GenPartId_phys[NobjJet]/I" );


  //met
  CalibTree->Branch( "Met",   &mmet,"Met/F"   );
  CalibTree->Branch( "MetPhi",&mphi,"MetPhi/F");
  CalibTree->Branch( "MetSum",&msum,"MetSum/F");


  // GenEventScale (pthat)
  CalibTree->Branch( "GenEvtScale",&genEvtScale,"GenEvtScale/F");


  //EventWeight
  CalibTree->Branch( "Weight",&weight,"Weight/F"   );


  //ecal cells data
  etowet      = new float [ kMAX ];
  etoweta     = new float [ kMAX ];
  etowphi     = new float [ kMAX ];
  etowe       = new float [ kMAX ];
  etowid_phi  = new int[ kMAX ];
  etowid_eta  = new int[ kMAX ];
  etowid      = new int[ kMAX ];
  etownum     = new int[ kMAX ];
  etow_towidx = new int[ kMAX ];
  etow_jetidx = new int[ kMAX ];

  //EcalCell branches
  if( writeEcalCells ) {
    CalibTree->Branch( "NobjETowCal",&NobjETowCal,"NobjETowCal/I"            );
    CalibTree->Branch( "ETowNum",    etownum,     "ETowNum[NobjETowCal]/I"   );
    CalibTree->Branch( "ETowId",     etowid,      "ETowId[NobjETowCal]/I"    );
    CalibTree->Branch( "ETowId_phi", etowid_phi,  "ETowId_phi[NobjETowCal]/I");
    CalibTree->Branch( "ETowId_eta", etowid_eta,  "ETowId_eta[NobjETowCal]/I");
    CalibTree->Branch( "ETowEt",     etowet,      "ETowEt[NobjETowCal]/F"    );
    CalibTree->Branch( "ETowEta",    etoweta,     "ETowEta[NobjETowCal]/F"   );
    CalibTree->Branch( "ETowPhi",    etowphi,     "ETowPhi[NobjETowCal]/F"   );
    CalibTree->Branch( "ETowE",      etowe,       "ETowE[NobjETowCal]/F"     );
    CalibTree->Branch( "ETow_towidx",etow_towidx, "ETow_towidx[NobjETowCal]/I"     );
    CalibTree->Branch( "ETow_jetidx",etow_jetidx, "ETow_jetidx[NobjETowCal]/I"     );
  }
}


  
void NJet::analyze(const edm::Event& evt, const edm::EventSetup& setup, TTree* CalibTree)
{
  //Event Weighting
  if(weight_ < 0)
    {
      edm::Handle<double> weightHandle;
      evt.getByLabel (weight_tag, weightHandle);
      weight = (float)( *weightHandle );
    }
  else weight = weight_;

  edm::Handle<reco::CaloJetCollection> pJets;
  evt.getByLabel(jets_, pJets);

  edm::Handle<CaloMETCollection> recmets;
  evt.getByLabel(met_, recmets);

  edm::Handle<reco::GenJetCollection> genJets;
  evt.getByLabel(genjets_,genJets);
  reco::GenJetCollection::const_iterator genJet;

  edm::Handle<reco::GenParticleCollection> genParticles;
  evt.getByLabel(genparticles_,genParticles);

  edm::Handle<JetMatchedPartonsCollection> matchedParticleMap;
  evt.getByLabel("CaloJetPartonMatching", matchedParticleMap); 

  // get calo jet after zsp collection
  edm::Handle<CaloJetCollection> zspJets;
  evt.getByLabel(zspJets_, zspJets);
  reco::CaloJetCollection::const_iterator zspJet;

  // Get pthat
  edm::Handle<double> pthat;
  evt.getByLabel(genEvtScale_,pthat);
  genEvtScale = static_cast<float>(*pthat);

  // To access ECAL cells
  edm::InputTag ebrechits_ = edm::InputTag("ecalRecHit","EcalRecHitsEB","RECO");
  const EBRecHitCollection *EBRecHit = 0;
  edm::Handle<EBRecHitCollection> EcalRecHitEB;
  evt.getByLabel( ebrechits_, EcalRecHitEB);
  EBRecHit = EcalRecHitEB.product();

  edm::ESHandle<CaloGeometry> pG;
  setup.get<CaloGeometryRecord>().get(pG);
  const CaloGeometry cG = *pG;
  const CaloSubdetectorGeometry* EBgeom = cG.getSubdetectorGeometry(DetId::Ecal,1);


  std::string l2name = "L2RelativeJetCorrector";
  std::string l3name = "L3AbsoluteJetCorrector";
  std::string JPTname = "JetPlusTrackZSPCorrectorScone5";
  std::string l2l3name = "L2L3JetCorrectorSC5Calo";
  std::string l2l3JPTname = "L2L3JetCorrectorIC5JPT";
  //std::string l2l3PFlowname = "L2L3JetCorrectorSC5PF";

  const JetCorrector* correctorL2   = JetCorrector::getJetCorrector (l2name,setup);   //Define the jet corrector
  const JetCorrector* correctorL3   = JetCorrector::getJetCorrector (l3name,setup);   //Define the jet corrector
//   const JetCorrector* correctorJPT  = JetCorrector::getJetCorrector (JPTname, setup); //Define the jet corrector
//   const JetCorrector* correctorL2L3  = JetCorrector::getJetCorrector (l2l3name, setup); //Define the jet corrector
//   const JetCorrector* correctorL2L3JPT  = JetCorrector::getJetCorrector (l2l3JPTname, setup); //Define the jet corrector
  //const JetCorrector* correctorL2L3PFlow  = JetCorrector::getJetCorrector (l2l3PFlowname, setup); //Define the jet corrector

  NobjTow=0;
  NobjETowCal = 0;
  NobjJet = pJets->size();
  if(NobjJet > kjMAX) NobjJet = kjMAX;
  unsigned int towno = 0;   // Calo tower counting index
  unsigned int icell = 0;   // Ecal cell counting index

  // Loop over calo jets
  for (unsigned int jtno = 0; (int)jtno<NobjJet; ++jtno) {

    // Write jet kinematics
    jetpt[  jtno ] = (*pJets)[jtno].pt();
    jetphi[ jtno ] = (*pJets)[jtno].phi();
    jeteta[ jtno ] = (*pJets)[jtno].eta();
    jetet[  jtno ] = (*pJets)[jtno].et();
    jete[   jtno ] = (*pJets)[jtno].energy();


    // L2L3 correction
    jscalel2[jtno]   = correctorL2  ->correction( (*pJets)[jtno].p4());  //calculate the correction
    jscalel3[jtno]   = correctorL3  ->correction( jscalel2[jtno] * (*pJets)[jtno].p4());  //calculate the correction
    //    jscalel2l3[jtno] = correctorL2L3->correction( (*pJets)[jtno].p4());  //calculate the correction


//     // JPT correction (uses ZSP corrected jets)
//     for(zspJet = zspJets->begin(); zspJet != zspJets->end(); ++zspJet) {
//       if( deltaR(zspJet->eta(),zspJet->phi(),(*pJets)[jtno].eta() , (*pJets)[jtno].phi()) < 0.01)//no change in R by ZSP or JPT
// 	  {
// 	    jscaleZSP[jtno]     = zspJet->et()/ (*pJets)[jtno].et();
// 	    jscaleJPT[jtno]     = correctorJPT ->correction((*zspJet),evt,setup);  //calculate the correction
// 	    jscalel2l3JPT[jtno] = correctorL2L3JPT  ->correction(zspJet->p4() * jscaleJPT[jtno] );  //calculate the correction
// 	  }
//       }




    // Find closest genjet (DeltaR) to the current calo jet
    double closestDeltaR    = 1000;
    int    closestGenJetIdx = 0;
    for(size_t gjidx = 0; gjidx < genJets->size(); gjidx++) {
      double deltaRtmp  = deltaR( (*genJets)[gjidx].eta(), (*genJets)[gjidx].phi(),
				  (*pJets)[jtno].eta(),    (*pJets)[jtno].phi()     );

      if( deltaRtmp < closestDeltaR ) {
	closestDeltaR    = deltaRtmp;
	closestGenJetIdx = gjidx;
      }
    }
    jetgenjetDeltaR[ jtno ] = closestDeltaR;

    genjetpt[  jtno ] = (*genJets)[closestGenJetIdx].pt();
    genjetphi[ jtno ] =	(*genJets)[closestGenJetIdx].phi();
    genjeteta[ jtno ] =	(*genJets)[closestGenJetIdx].eta();
    genjetet[  jtno ] =	(*genJets)[closestGenJetIdx].et();
    genjete[   jtno ] = (*genJets)[closestGenJetIdx].energy();



    // Write calo towers

    // uncomment for CMSSW_2_1_X compatibility
    std::vector<CaloTowerPtr> j_towers = (*pJets)[jtno].getCaloConstituents();
    NobjTow+=j_towers.size();
    for (std::vector<CaloTowerPtr>::const_iterator tow = j_towers.begin(); 
	 tow != j_towers.end(); ++tow, ++towno){

      // uncomment for CMSSW_2_0_X compatibility
      //    std::vector<CaloTowerRef> j_towers = (*pJets)[jtno].getConstituents(); 
      //    NobjTow+=j_towers.size();
      //    for (std::vector<CaloTowerRef>::const_iterator tow = j_towers.begin(); 
      //         tow != j_towers.end(); ++tow, ++towno){

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


      // Ecal cells
      if( writeEcalCells ) {
	// Loop over tower constituents
	for (size_t it=0; it<(*tow)->constituentsSize(); ++it) {
	  assert( icell < 10000 );
	  const DetId detid = (*tow)->constituent(it);
	  EcalRecHitCollection::const_iterator myRecHit = EBRecHit->find(detid);
	  if( myRecHit != EBRecHit->end() ) {
	    EBDetId det = myRecHit->id();
	    
	    const CaloCellGeometry* cell=EBgeom->getGeometry( myRecHit->id() );
	    
	    etowet [icell]     = myRecHit->energy()*sin( cell->getPosition().theta());
	    etoweta[icell]     = cell->getPosition().eta();
	    etowphi[icell]     = cell->getPosition().phi();
	    etowe  [icell]     = myRecHit->energy();
	    etowid_phi[icell]  = det.iphi();
	    etowid_eta[icell]  = det.ieta();
	    etowid [icell]     = myRecHit->id().rawId();
	    etownum[icell]     = icell;
	    etow_towidx[icell] = towno;
	    etow_jetidx[icell] = jtno;
	    ++icell;
	  } // End if( myRecHit != EBRecHit->end() )
	} // End loop over tower constituents
      } // End if( writeEcalCells )
    } // End loop over towers

    //// GenParticle Matching ALGO and PHYSICS

    double gppt_algo = 0;
    double gpphi_algo = 0;
    double gpeta_algo = 0;
    double gpet_algo = 0;
    double gpe_algo = 0;
    double gpm_algo = 0;
    int gpid_algo = 0;

    double gppt_phys = 0;
    double gpphi_phys = 0;
    double gpeta_phys = 0;
    double gpet_phys = 0;
    double gpe_phys = 0;
    double gpm_phys = 0;
    int gpid_phys = 0;


    JetMatchedPartonsCollection::const_iterator j_sel;
    bool matchedPartonFound=false;
    //       //cout<<"calo Jet (pt,eta,phi): "<< (*pJets)[jtno].et() << " " << (*pJets)[jtno].eta() << " " << (*pJets)[jtno].phi() <<endl;
    for (JetMatchedPartonsCollection::const_iterator j = matchedParticleMap->begin(); j != matchedParticleMap->end(); j ++) {
      const Jet *aJet = (*j).first.get();
      //cout<<"maped Jet (pt,eta,phi): "<< ((aJet))->et() << " " << ((aJet))->eta() << " " << ((aJet))->phi() <<endl;
      if (((*pJets)[jtno].eta()==((aJet))->eta()) && ((*pJets)[jtno].phi()==((aJet))->phi())) {
    	j_sel=j;
    	matchedPartonFound=true;
    	break;
      }
    }

    if (matchedPartonFound) {
      const MatchedPartons aMatch = (*j_sel).second;


      
      //           cout<<"matched Jet (pt,eta,phi):         "<< aJet->et() <<" "<< aJet->eta()<<" "<< aJet->phi()<<endl;
      
      GenParticleRef theAlgoDef = aMatch.algoDefinitionParton();
      if (theAlgoDef.isNonnull()) {
	
	gppt_algo = theAlgoDef->pt();
	gpphi_algo = theAlgoDef->phi();
	gpeta_algo = theAlgoDef->eta();
	gpet_algo = theAlgoDef->et();
	gpe_algo = theAlgoDef->energy();
	gpm_algo = theAlgoDef->mass();
	gpid_algo = theAlgoDef->pdgId();
      }
      
      GenParticleRef thePhyDef = aMatch.physicsDefinitionParton();
      if (thePhyDef.isNonnull()) {
	//          cout<<"matched parton PhysDef:        "<< thePhyDef->et() <<" "<< thePhyDef->eta()<<" "<< thePhyDef->phi()<<endl;
	gppt_phys = thePhyDef->pt();
	gpphi_phys = thePhyDef->phi();
	gpeta_phys = thePhyDef->eta();
	gpet_phys = thePhyDef->et();
	gpe_phys = thePhyDef->energy();
	gpm_phys = thePhyDef->mass();
	gpid_phys = thePhyDef->pdgId();
      
      }


    } 
    genpartpt_algo[  jtno ] = gppt_algo;
    genpartphi_algo[ jtno ] = gpphi_algo ;
    genparteta_algo[ jtno ] = gpeta_algo ;
    genpartet_algo[  jtno ] = gpet_algo ;
    genparte_algo[   jtno ] = gpe_algo ;
    genpartm_algo[   jtno ] = gpm_algo ;
    genpartid_algo[  jtno ] = gpid_algo ;
  

    genpartpt_phys[  jtno ] = gppt_phys;
    genpartphi_phys[ jtno ] = gpphi_phys ;
    genparteta_phys[ jtno ] = gpeta_phys ;
    genpartet_phys[  jtno ] = gpet_phys ;
    genparte_phys[   jtno ] = gpe_phys ;
    genpartm_phys[   jtno ] = gpm_phys ;
    genpartid_phys[  jtno ] = gpid_phys ;
  
  } // End of loop over calo jets
  
  NobjETowCal = icell;



  typedef CaloMETCollection::const_iterator cmiter;
  for( cmiter i=recmets->begin(); i!=recmets->end(); i++) {
    mmet = i->pt();
    mphi = i->phi();
    msum = i->sumEt();
    break;
  }


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
    if (it->pt() < 1) continue;
    TrackDetMatchInfo info = trackAssociator_.associate(evt, setup, *it, parameters_);

    for (unsigned int jtno = 0; (int)jtno<NobjJet; ++jtno)
      {
	bool saveTrack = false;
	double dRin   = deltaR(*it,(*pJets)[jtno]);
	double outeta = info.trkGlobPosAtEcal.eta();
	double outphi = info.trkGlobPosAtEcal.phi();
	double dRout  = deltaR((*pJets)[jtno].eta(),(*pJets)[jtno].phi(),outeta,outphi);
	if (dRin < conesize_ ) { //|| dRout < conesize_){
	  saveTrack=true;
	}
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
	  track_jetidx[iTrack]  = jtno;
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
	  
	  //Match track with muons
	  muDR[iTrack] = -1;
	  muDE[iTrack] = -1;
	  bool muonMatch = false;
	  for(reco::MuonCollection::const_iterator im = muons->begin(); im != muons->end(); ++im) {
	    //for(reco::TrackCollection::const_iterator im = muons->begin(); im != muons->end(); ++im) {
	    if(im->isGood(reco::Muon::AllGlobalMuons) && im->isGood(reco::Muon::TMLastStationLoose)) continue;
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
  }
  NobjTrack=iTrack;




  /////////// Write genjet collection ///////////////////

  // Loop over genjets
  NobjGenJet = genJets->size();
  if(NobjGenJet > kjMAX) NobjGenJet = kjMAX;

  for(int gjidx = 0; gjidx < NobjGenJet; gjidx++) {

    // Write genjet kinematics
    genjetcolpt[  gjidx ] = genJets->at(gjidx).pt();
    genjetcolphi[ gjidx ] = genJets->at(gjidx).phi();
    genjetcoleta[ gjidx ] = genJets->at(gjidx).eta();
    genjetcolet[  gjidx ] = genJets->at(gjidx).et();
    genjetcole[   gjidx ] = genJets->at(gjidx).energy();


    // Find closest calojet to this genjet
    // Note: NobjJet was set above to min( pJets->size(), kjMAX )
    double closestDeltaR = 1000;
    int    closestJetIdx = 0;
    for(int cjidx = 0; cjidx < NobjJet; cjidx++) {
      double deltaRtmp = deltaR( genJets->at(gjidx).eta(), genJets->at(gjidx).phi(),
				 pJets->at(cjidx).eta(),    pJets->at(cjidx).phi()     );
    
      if( deltaRtmp < closestDeltaR ) {
	closestDeltaR = deltaRtmp;
	closestJetIdx = cjidx;
      }
    }
    genjetcol_jet_idx[gjidx] = closestJetIdx;
  
  } // End of loop over genjets
  

  CalibTree->Fill();
}
