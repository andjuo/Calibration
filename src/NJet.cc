#include "Calibration/CalibTreeMaker/interface/NJet.h"
#include "DataFormats/METReco/interface/CaloMET.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"


void NJet::setup(const edm::ParameterSet& cfg, TTree* CalibTree)
{
  jets_       = cfg.getParameter<edm::InputTag>("NJet_Jets");
  genjets_    = cfg.getParameter<edm::InputTag>("NJet_GenJets");
  met_        = cfg.getParameter<edm::InputTag>("NJet_MET");
  weight_      = (float)(cfg.getParameter<double> ("NJet_Weight"));
  weight_tag  = cfg.getParameter<edm::InputTag> ("NJet_Weight_Tag");
  recTracks_  = cfg.getParameter<edm::InputTag>("NJetRecTracks");
  recMuons_   = cfg.getParameter<edm::InputTag>("NJetRecMuons");
  conesize_   = cfg.getParameter<double>("NJetConeSize");

  // TrackAssociator parameters
  edm::ParameterSet parameters = cfg.getParameter<edm::ParameterSet>("TrackAssociatorParameters");
  parameters_.loadParameters( parameters );

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
  track_jetidx  = new int[ kMAX ];
  trackid       = new int[ kMAX ]; // abs(PiD) if available, guess: muons only; =0: unknown
  tracknhits    = new int[ kMAX ]; 
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

  //All jets
  const int kjMAX = 50;
  jetpt     = new float [ kjMAX ];
  jetphi    = new float [ kjMAX ];
  jeteta    = new float [ kjMAX ];
  jetet     = new float [ kjMAX ];
  jete      = new float [ kjMAX ];
  jscalel2  = new float [ kjMAX ];
  jscalel3  = new float [ kjMAX ];
  // Jet-specific branches of the tree 
  CalibTree->Branch( "NobjJet",&NobjJet,"NobjJet/I"             );
  CalibTree->Branch( "JetPt", jetpt, "JetPt[NobjJet]/F" );
  CalibTree->Branch( "JetPhi",jetphi,"JetPhi[NobjJet]/F");
  CalibTree->Branch( "JetEta",jeteta,"JetEta[NobjJet]/F");
  CalibTree->Branch( "JetEt", jetet, "JetEt[NobjJet]/F" );
  CalibTree->Branch( "JetE",  jete,  "JetE[NobjJet]/F"  );
  CalibTree->Branch( "JetCorrL2", jscalel2,  "JetCorrL2[NobjJet]/F" );
  CalibTree->Branch( "JetCorrL3", jscalel3,  "JetCorrL3[NobjJet]/F" );

  //met
  CalibTree->Branch( "Met",   &mmet,"Met/F"   );
  CalibTree->Branch( "MetPhi",&mphi,"MetPhi/F");
  CalibTree->Branch( "MetSum",&msum,"MetSum/F");

  //EventWeight
  CalibTree->Branch( "Weight",&weight,"Weight/F"   );
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
  //edm::Handle<edm::View<reco::Jet> > pJets;
  evt.getByLabel(jets_, pJets);

  edm::Handle<CaloMETCollection> recmets;
  evt.getByLabel(met_, recmets);


  std::string l2name = "L2RelativeJetCorrector";
  std::string l3name = "L3AbsoluteJetCorrector";

  const JetCorrector* correctorL2   = JetCorrector::getJetCorrector (l2name,setup);   //Define the jet corrector
  const JetCorrector* correctorL3   = JetCorrector::getJetCorrector (l3name,setup);   //Define the jet corrector

  NobjTow=0;
  NobjJet = pJets->size();
  unsigned int towno = 0;
  for (unsigned int jtno = 0; (int)jtno<NobjJet; ++jtno)
  {
    jscalel2[jtno]  = correctorL2  ->correction( (*pJets)[jtno].p4());  //calculate the correction
    jscalel3[jtno]  = correctorL3  ->correction( (*pJets)[jtno].p4());  //calculate the correction

    jetpt[  jtno ] = (*pJets)[jtno].pt();
    jetphi[ jtno ] = (*pJets)[jtno].phi();
    jeteta[ jtno ] = (*pJets)[jtno].eta();
    jetet[  jtno ] = (*pJets)[jtno].et();
    jete[   jtno ] = (*pJets)[jtno].energy();

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
    }
  }
  
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
  //edm::Handle<reco::MuonCollection> muons;
  edm::Handle<reco::TrackCollection> muons;
  evt.getByLabel(recMuons_,muons);

  // see here for detailed track cluster matching and jet track association
  //   -> CMSSW/TrackingTools/TrackAssociator/test/CaloMatchingExample.cc

  int iTrack = 0;
  for(reco::TrackCollection::const_iterator it = tracks->begin(); it != tracks->end(); ++it) {
    // skip low Pt tracks
    if (it->pt() < 2) continue;
    TrackDetMatchInfo info = trackAssociator_.associate(evt, setup, *it, parameters_);

    for (unsigned int jtno = 0; (int)jtno<NobjJet; ++jtno)
      {
	bool saveTrack = false;
	double dRin   = deltaR(*it,(*pJets)[jtno]);
	double outeta = info.trkGlobPosAtEcal.eta();
	double outphi = info.trkGlobPosAtEcal.phi();
	double dRout  = deltaR((*pJets)[jtno].eta(),(*pJets)[jtno].phi(),outeta,outphi);
	if (dRin < conesize_ || dRout < conesize_){
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
  }
  NobjTrack=iTrack;

  CalibTree->Fill();
}
