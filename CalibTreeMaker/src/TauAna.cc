#include "Calibration/CalibTreeMaker/interface/TauAna.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/TauReco/interface/PFTau.h"
#include "DataFormats/TauReco/interface/PFTauDiscriminator.h"

#include "TrackingTools/TrackAssociator/interface/TrackDetectorAssociator.h"
#include "TrackingTools/TrackAssociator/interface/TrackAssociatorParameters.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"


#include "Calibration/CalibTreeMaker/interface/CalibTreeMakerHelper.h"

const int TauAna::NMax_ = 10;

TauAna::TauAna() : ntaus_(0),  ngentaus_(0), hltDoubleMu3_(false), 
			 hltDoubleMu5_(false),hltDoubleMu6_(false), 
			 hltDoubleMu7_(false),hltDoubleMu45_(false),
			 hltMu5IsoMu5_(false),hltMu13Mu8_(false),
			 hltMu17Mu8_(false), hltisomu24eta2p1_(false)
{
  //Taus
  taupt_ = new float[NMax_];
  tauphi_ = new float[NMax_];
  taueta_ = new float[NMax_];
  taue_ = new float[NMax_];
  tauid_ = new float[NMax_];
}

TauAna::~TauAna() 
{
  delete [] taupt_;
  delete [] tauphi_;
  delete [] taueta_;
  delete [] taue_;
  delete [] tauid_;
}



void TauAna::setup(const edm::ParameterSet& cfg, TTree* CalibTree)
{
  tau_            = cfg.getParameter<edm::InputTag>("TauAnaProducer");
  discriminator_  = cfg.getParameter<edm::InputTag>("TauAnaDiscriminator");

  //trigger
  /*CalibTree->Branch("HltDoubleMu3" ,&hltDoubleMu3_ ,"HltDoubleMu3/O");
  CalibTree->Branch("HltDoubleMu5" ,&hltDoubleMu5_ ,"HltDoubleMu5/O");
  CalibTree->Branch("HltDoubleMu6" ,&hltDoubleMu6_ ,"HltDoubleMu6/O");
  CalibTree->Branch("HltDoubleMu7" ,&hltDoubleMu7_ ,"HltDoubleMu7/O");
  CalibTree->Branch("HltDoubleMu45",&hltDoubleMu45_,"HltDoubleMu45/O");
  CalibTree->Branch("HltMu5IsoMu5" ,&hltMu5IsoMu5_ ,"HltMu5IsoMu5/O");
  CalibTree->Branch("HltMu13Mu8"   ,&hltMu13Mu8_   ,"HltMu13Mu8/O");
  CalibTree->Branch("HltMu17Mu8"   ,&hltMu17Mu8_   ,"HltMu17Mu8/O");*/
  CalibTree->Branch("HltIsoMu24Eta2P1"   ,&hltisomu24eta2p1_   ,"HltIsoMu24Eta2P1/O");
  // tau branches
  CalibTree->Branch("NobjTau",&ntaus_, "NobjTau/I");
  CalibTree->Branch("TauPt",   taupt_,  "TauPt[NobjTau]/F");
  CalibTree->Branch("TauPhi",  tauphi_, "TauPhi[NobjTau]/F");
  CalibTree->Branch("TauEta",  taueta_, "TauEta[NobjTau]/F");
  CalibTree->Branch("TauE",    taue_,   "MuonE[NobjTau]/F");
  CalibTree->Branch("TauID",      tauid_,   "TauID[NobjTau]/F");
}

void TauAna::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{  
  edm::Handle<edm::TriggerResults> triggerResults;
  
  if( evt.getByLabel(edm::InputTag("TriggerResults::HLT"),triggerResults) ) {
    const edm::TriggerNames & trigNames = evt.triggerNames(*triggerResults);
    size_t id = 0;
    
    /* hltDoubleMu3_ = false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_DoubleMu3");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltDoubleMu3_ = true;
    }
    hltDoubleMu5_ = false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_DoubleMu5");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltDoubleMu5_ = true;
    }
    hltDoubleMu6_ = false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_DoubleMu6");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltDoubleMu6_ = true;
    }
    hltDoubleMu7_ = false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_DoubleMu7");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltDoubleMu7_ = true;
    }
    hltDoubleMu45_ = false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_DoubleMu45");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltDoubleMu45_ = true;
    }
    hltMu5IsoMu5_= false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_DoubleMu5_IsoMu5");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltMu5IsoMu5_ = true;
    } 
    hltMu13Mu8_= false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_Mu13_Mu8");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltMu13Mu8_ = true;
    }
    hltMu17Mu8_= false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_Mu17_Mu8");
    if( id != trigNames.size() ) {
      if( triggerResults->accept(id) ) hltMu17Mu8_ = true;
    }*/
    hltisomu24eta2p1_= false;
    id = CalibTreeMakerHelper::findTrigger(trigNames.triggerNames(),"HLT_IsoMu24_eta2p1");
    if( id != trigNames.size() ) 
      {
	if( triggerResults->accept(id) ) hltMu17Mu8_ = true;
      }
  
  }

  edm::Handle<reco::PFTauCollection> tauColl;
  evt.getByLabel(tau_, tauColl);
  edm::Handle<reco::PFTauDiscriminator> discriminatorColl;
  evt.getByLabel(discriminator_, discriminatorColl);
  ntaus_ = tauColl->size();
  if(ntaus_>NMax_)ntaus_=NMax_;
  if(ntaus_ >=1)
    {
      for (unsigned int tauno = 0; (int)tauno<ntaus_; ++tauno)
	{  
	  reco::PFTauRef tauCandidate(tauColl, tauno);
	  taupt_[tauno]  =(*tauColl)[tauno].pt();
	  tauphi_[tauno] =(*tauColl)[tauno].phi();
	  taueta_[tauno] =(*tauColl)[tauno].eta();
	  taue_[tauno]   =(*tauColl)[tauno].energy();
	  tauid_[tauno]  =(*discriminatorColl)[tauCandidate];
	}
    }
}
