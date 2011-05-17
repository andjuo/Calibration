#include "Calibration/CalibTreeMaker/interface/PhotonJet.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"

#include "TrackingTools/TrackAssociator/interface/TrackDetectorAssociator.h"
#include "TrackingTools/TrackAssociator/interface/TrackAssociatorParameters.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"

#include "Calibration/CalibTreeMaker/interface/CalibTreeMakerHelper.h"

const int PhotonJet::NMax_ = 10;

PhotonJet::PhotonJet() : nphotons_(0),  ngenphotons_(0), hltPhoton20_(false),
			 hltPhoton30_(false),hltPhoton50_(false),hltPhoton75_(false)
{
  photonpt_ = new float[NMax_];
  photonphi_ = new float[NMax_];
  photoneta_ = new float[NMax_];
  photone_ = new float[NMax_];
  photonisoecal04_ = new float[NMax_];
  photonisohcal04_ = new float[NMax_];
  photonisotrk04_ = new float[NMax_];
  photonidloose_ = new bool[NMax_];
  photonidtight_ = new bool[NMax_];
  genphotonpt_ = new float[NMax_];
  genphotonphi_ = new float[NMax_];
  genphotoneta_ = new float[NMax_];
  genphotone_ = new float[NMax_];

}

PhotonJet::~PhotonJet() {
  delete [] photonpt_;
  delete [] photonphi_;
  delete [] photoneta_;
  delete [] photone_;
  delete [] photonisoecal04_;
  delete [] photonisohcal04_;
  delete [] photonisotrk04_;
  delete [] photonidloose_;
  delete [] photonidtight_;
  delete [] genphotonpt_;
  delete [] genphotonphi_;
  delete [] genphotoneta_;
  delete [] genphotone_;
}



void PhotonJet::setup(const edm::ParameterSet& cfg, TTree* CalibTree)
{
  photon_           = cfg.getParameter<edm::InputTag>("PhotonJetPhotons");
  genphotons_       = cfg.getParameter<edm::InputTag>("PhotonJetGenPhotons");

  //trigger
  CalibTree->Branch("HltPhoton20",&hltPhoton20_,"HltPhoton20/O");
  CalibTree->Branch("HltPhoton30",&hltPhoton30_,"HltPhoton30/O");
  CalibTree->Branch("HltPhoton50",&hltPhoton50_,"HltPhoton50/O");
  CalibTree->Branch("HltPhoton75",&hltPhoton75_,"HltPhoton75/O");
  // Photons branches
  CalibTree->Branch( "NobjPhoton",&nphotons_,"NobjPhoton/I");
  CalibTree->Branch( "PhotonPt",  photonpt_,  "PhotonPt[NobjPhoton]/F"  );
  CalibTree->Branch( "PhotonPhi", photonphi_, "PhotonPhi[NobjPhoton]/F" );
  CalibTree->Branch( "PhotonEta", photoneta_, "PhotonEta[NobjPhoton]/F" );
  CalibTree->Branch( "PhotonE",   photone_,   "PhotonE[NobjPhoton]/F"   );
  CalibTree->Branch( "PhotonIsoECAL04", photonisoecal04_, "PhotonIsoECAL04[NobjPhoton]/F");
  CalibTree->Branch( "PhotonIsoHCAL04", photonisohcal04_, "PhotonIsoHCAL04[NobjPhoton]/F");
  CalibTree->Branch( "PhotonIsoTrk04", photonisotrk04_, "PhotonIsoTrk04[NobjPhoton]/F");
  CalibTree->Branch( "PhotonIDLoose",photonidloose_,"PhotonIDLoose[NobjPhoton]/O");
  CalibTree->Branch( "PhotonIDTight",photonidtight_,"PhotonIDTight[NobjPhoton]/O");
  // GenPhotons branches
  CalibTree->Branch( "NobjGenPhoton",&ngenphotons_,"NobjGenPhoton/I");
  CalibTree->Branch( "GenPhotonPt",  genphotonpt_,  "GenPhotonPt[NobjGenPhoton]/F"  );
  CalibTree->Branch( "GenPhotonPhi", genphotonphi_, "GenPhotonPhi[NobjGenPhoton]/F" );
  CalibTree->Branch( "GenPhotonEta", genphotoneta_, "GenPhotonEta[NobjGenPhoton]/F" );
  CalibTree->Branch( "GenPhotonE",   genphotone_,   "GenPhotonE[NobjGenPhoton]/F"   );
}

void PhotonJet::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{  
  edm::Handle<edm::TriggerResults> triggerResults;
  
  if( evt.getByLabel(edm::InputTag("TriggerResults::HLT"),triggerResults) ) {
    const edm::TriggerNames & trigNames = evt.triggerNames(*triggerResults);
    size_t id = 0;
    
    hltPhoton20_ = false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_Photon20_CaloIdVL_IsoL");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltPhoton20_ = true;
    }
    hltPhoton30_ = false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_Photon30_CaloIdVL_IsoL");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltPhoton30_ = true;
    }
    hltPhoton50_ = false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_Photon50_CaloIdVL_IsoL");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltPhoton50_ = true;
    }
    hltPhoton75_ = false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_Photon75_CaloIdVL_IsoL");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltPhoton75_ = true;
    }
  }

  edm::Handle<reco::PhotonCollection> photonColl;
  evt.getByLabel(photon_, photonColl);

  edm::Handle<edm::ValueMap<Bool_t> > loosePhotonQual,tightPhotonQual;
  evt.getByLabel("PhotonIDProd", "PhotonCutBasedIDLoose", loosePhotonQual);
  evt.getByLabel("PhotonIDProd", "PhotonCutBasedIDTight", tightPhotonQual);

  // create reference to the object types we are interested in
  const edm::ValueMap<Bool_t> *phoMapLoose = loosePhotonQual.product();
  const edm::ValueMap<Bool_t> *phoMapTight = tightPhotonQual.product();
  
  nphotons_ = 0;
  for (reco::PhotonCollection::const_iterator pho = photonColl->begin(); pho!= photonColl->end(); ++pho){   
    edm::Ref<reco::PhotonCollection> photonref(photonColl, nphotons_);
    
    photonpt_[nphotons_]  = pho->pt();
    photonphi_[nphotons_] = pho->phi();
    photoneta_[nphotons_] = pho->eta();
    photone_[nphotons_]   = pho->energy();
    photonisoecal04_[nphotons_] = pho->ecalRecHitSumEtConeDR04();
    photonisohcal04_[nphotons_] = pho->hcalTowerSumEtConeDR04();
    photonisotrk04_[nphotons_] = pho->trkSumPtSolidConeDR04();
    photonidloose_[nphotons_] = (*phoMapLoose)[photonref];
    photonidtight_[nphotons_] = (*phoMapTight)[photonref];
    
    ++nphotons_;
    if(nphotons_ == NMax_) break;
  }
  
  
  edm::Handle<reco::GenParticleCollection> genphotonColl;
  evt.getByLabel(genphotons_,genphotonColl);
  
  ngenphotons_ = 0;
  if(! genphotonColl.isValid()) return;
  for (reco::GenParticleCollection::const_iterator ig = genphotonColl->begin(); ig!= genphotonColl->end(); ++ig){  
    genphotonpt_[ngenphotons_]  = ig->pt();
    genphotonphi_[ngenphotons_] = ig->phi();
    genphotoneta_[ngenphotons_] = ig->eta();
    genphotone_[ngenphotons_]   = ig->energy();
    ++ngenphotons_;
    if(ngenphotons_ == NMax_) break;
  }
}
