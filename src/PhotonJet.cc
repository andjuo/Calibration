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

PhotonJet::PhotonJet() : nphotons_(0),  ngenphotons_(0), hltPhoton20calo_(false),hltPhoton30calo_(false), hltPhoton50calo_(false),hltPhoton75calo_(false),hltPhoton90calo_(false),
                         hltPhoton135_(false),hltPhoton150_(false),hltPhoton160_(false),
			 hltPhoton20iso_(false),hltPhoton30iso_(false),hltPhoton50iso_(false),hltPhoton75iso_(false),hltPhoton90iso_(false),hltPhoton30_(false),hltPhoton30R9_(false)
{
  photonpt_ = new float[NMax_];
  photonphi_ = new float[NMax_];
  photoneta_ = new float[NMax_];
  photone_ = new float[NMax_];
  photonisoecal04_ = new float[NMax_];
  photonisohcal04_ = new float[NMax_];
  photonisotrk04_ = new float[NMax_];
  photonsigmaietaieta_ = new float[NMax_];
  photonhovere_ = new float[NMax_];
  photonhaspixelseed_ = new bool[NMax_];
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
  delete [] photonsigmaietaieta_;
  delete [] photonhovere_;
  delete [] photonhaspixelseed_;
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
  CalibTree->Branch("HltPhoton20iso",&hltPhoton20iso_,"HltPhoton20iso/O");
  CalibTree->Branch("HltPhoton20calo",&hltPhoton20calo_,"HltPhoton20calo/O");
  CalibTree->Branch("HltPhoton30iso",&hltPhoton30iso_,"HltPhoton30iso/O");
  CalibTree->Branch("HltPhoton30calo",&hltPhoton30calo_,"HltPhoton30calo/O");
  CalibTree->Branch("HltPhoton30R9",&hltPhoton30R9_,"HltPhoton30R9/O");
  CalibTree->Branch("HltPhoton30",&hltPhoton30_,"HltPhoton30/O");
  CalibTree->Branch("HltPhoton50iso",&hltPhoton50iso_,"HltPhoton50iso/O");
  CalibTree->Branch("HltPhoton50calo",&hltPhoton50calo_,"HltPhoton50calo/O");
  CalibTree->Branch("HltPhoton75iso",&hltPhoton75iso_,"HltPhoton75iso/O");
  CalibTree->Branch("HltPhoton75calo",&hltPhoton75calo_,"HltPhoton75calo/O");
  CalibTree->Branch("HltPhoton90iso",&hltPhoton90iso_,"HltPhoton90iso/O");
  CalibTree->Branch("HltPhoton90calo",&hltPhoton90calo_,"HltPhoton90calo/O");
  CalibTree->Branch("HltPhoton135",&hltPhoton135_,"HltPhoton135/O");
  CalibTree->Branch("HltPhoton150",&hltPhoton150_,"HltPhoton150/O");
  CalibTree->Branch("HltPhoton160",&hltPhoton160_,"HltPhoton160/O");

  // Photons branches
  CalibTree->Branch( "NobjPhoton",&nphotons_,"NobjPhoton/I");
  CalibTree->Branch( "PhotonPt",  photonpt_,  "PhotonPt[NobjPhoton]/F"  );
  CalibTree->Branch( "PhotonPhi", photonphi_, "PhotonPhi[NobjPhoton]/F" );
  CalibTree->Branch( "PhotonEta", photoneta_, "PhotonEta[NobjPhoton]/F" );
  CalibTree->Branch( "PhotonE",   photone_,   "PhotonE[NobjPhoton]/F"   );
  CalibTree->Branch( "PhotonIsoECAL04", photonisoecal04_, "PhotonIsoECAL04[NobjPhoton]/F");
  CalibTree->Branch( "PhotonIsoHCAL04", photonisohcal04_, "PhotonIsoHCAL04[NobjPhoton]/F");
  CalibTree->Branch( "PhotonIsoTrk04", photonisotrk04_, "PhotonIsoTrk04[NobjPhoton]/F");
  CalibTree->Branch( "PhotonSigmaIetaIeta", photonsigmaietaieta_, "PhotonSigmaIetaIeta[NobjPhoton]/F");
  CalibTree->Branch( "PhotonHadronicOverEM", photonhovere_, "PhotonHadronicOverEM[NobjPhoton]/F");
  CalibTree->Branch( "PhotonHasPixelSeed",photonhaspixelseed_,"PhotonHasPixelSeed[NobjPhoton]/O");
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
    
    hltPhoton20iso_ = false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_Photon20_CaloIdVL_IsoL");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltPhoton20iso_ = true;
    }
    hltPhoton20calo_ = false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_Photon20_CaloIdVL");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltPhoton20calo_ = true;
    }
    hltPhoton30iso_ = false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_Photon30_CaloIdVL_IsoL");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltPhoton30iso_ = true;
    }
    hltPhoton30calo_ = false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_Photon30_CaloIdVL");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltPhoton30calo_ = true;
    }
    hltPhoton30_ = false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_Photon30");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltPhoton30_ = true;
    }
    hltPhoton30R9_ = false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_Photon30_R9Id90_CaloId_HE10_Iso40_EBOnly");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltPhoton30R9_ = true;
    }
    hltPhoton50iso_ = false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_Photon50_CaloIdVL_IsoL");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltPhoton50iso_ = true;
    }
    hltPhoton50calo_ = false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_Photon50_CaloIdVL");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltPhoton50calo_ = true;
    }
    hltPhoton75iso_ = false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_Photon75_CaloIdVL_IsoL");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltPhoton75iso_ = true;
    } 
    hltPhoton75calo_ = false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_Photon75_CaloIdVL");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltPhoton75calo_ = true;
    } 
    hltPhoton90iso_ = false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_Photon90_CaloIdVL_IsoL");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltPhoton90iso_ = true;
    }
    hltPhoton90calo_ = false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_Photon90_CaloIdVL");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltPhoton90calo_ = true;
    }
    hltPhoton135_ = false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_Photon135");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltPhoton135_ = true;
    }
    hltPhoton150_ = false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_Photon150");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltPhoton150_ = true;
    }
    hltPhoton160_ = false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_Photon160");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltPhoton160_ = true;
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
    photonisotrk04_[nphotons_]  = pho->trkSumPtHollowConeDR04();
    photonsigmaietaieta_[nphotons_] = pho->sigmaIetaIeta();
    photonhovere_[nphotons_] = pho->hadronicOverEm();
    photonhaspixelseed_[nphotons_] = pho->hasPixelSeed();
    photonidloose_[nphotons_] = (*phoMapLoose)[photonref];
    photonidtight_[nphotons_] = (*phoMapTight)[photonref];
    
    ++nphotons_;
    if(nphotons_ == NMax_) break;
  }
  
  
  edm::Handle<reco::CandidateCollection> genphotonColl;
  evt.getByLabel(genphotons_,genphotonColl);
  
  ngenphotons_ = 0;
  if(! genphotonColl.isValid()) return;
  for (reco::CandidateCollection::const_iterator ig = genphotonColl->begin(); ig!= genphotonColl->end(); ++ig){  
    genphotonpt_[ngenphotons_]  = ig->pt();
    genphotonphi_[ngenphotons_] = ig->phi();
    genphotoneta_[ngenphotons_] = ig->eta();
    genphotone_[ngenphotons_]   = ig->energy();
    ++ngenphotons_;
    if(ngenphotons_ == NMax_) break;
  }
}
