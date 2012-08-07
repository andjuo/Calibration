#include "Calibration/CalibTreeMaker/interface/DimuonJet.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"

#include "TrackingTools/TrackAssociator/interface/TrackDetectorAssociator.h"
#include "TrackingTools/TrackAssociator/interface/TrackAssociatorParameters.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"


#include "Calibration/CalibTreeMaker/interface/CalibTreeMakerHelper.h"

const int DimuonJet::NMax_ = 10;

DimuonJet::DimuonJet() : nmuons_(0),  ngenmuons_(0), hltDoubleMu3_(false), 
			 hltDoubleMu5_(false),hltDoubleMu6_(false), 
			 hltDoubleMu7_(false),hltDoubleMu45_(false),
			 hltMu5IsoMu5_(false),hltMu13Mu8_(false),
			 hltMu17Mu8_(false)
{
  muonpt_ = new float[NMax_];
  muonphi_ = new float[NMax_];
  muoneta_ = new float[NMax_];
  muone_ = new float[NMax_];
  muontrackchi2_ = new float[NMax_];
  muond0_ = new float[NMax_];
  muonisor03trk_ = new float[NMax_];
  muonisor03em_ = new float[NMax_];
  muonisor03had_ = new float[NMax_];
  muonisor05trk_ = new float[NMax_];
  muonisor05em_ = new float[NMax_];
  muonisor05had_ = new float[NMax_];
  muonpfisor04ch_ = new float[NMax_];
  muonpfisor04nh_ = new float[NMax_];
  muonpfisor04g_ = new float[NMax_];
  muonglobal_ = new bool[NMax_];
  muontracker_ = new bool[NMax_];
  muonstandalone_ = new bool[NMax_];
  muoncalo_ = new bool[NMax_];
  muonnchambers_ = new int[NMax_];
  muonntrackerhits_ = new int[NMax_];
  muonnpixelhits_ = new int[NMax_];
  muonnstations_ = new int[NMax_];
  muontrackndof_ = new int[NMax_];
  muoncharge_ = new int[NMax_];
  genmuonpt_ = new float[NMax_];
  genmuonphi_ = new float[NMax_];
  genmuoneta_ = new float[NMax_];
  genmuone_ = new float[NMax_];

}

DimuonJet::~DimuonJet() {
  delete [] muonpt_;
  delete [] muonphi_;
  delete [] muoneta_;
  delete [] muone_;
  delete [] muontrackchi2_;
  delete [] muond0_;
  delete [] muonisor03trk_;
  delete [] muonisor03em_;
  delete [] muonisor03had_;
  delete [] muonisor05trk_;
  delete [] muonisor05em_;
  delete [] muonisor05had_;
  delete [] muonpfisor04ch_;
  delete [] muonpfisor04nh_;
  delete [] muonpfisor04g_;
  delete [] muonglobal_;
  delete [] muontracker_;
  delete [] muonstandalone_;
  delete [] muoncalo_;
  delete [] muonnchambers_;
  delete [] muonntrackerhits_;
  delete [] muonnstations_;
  delete [] muonnpixelhits_;
  delete [] muontrackndof_;
  delete [] muoncharge_;
  delete [] genmuonpt_;
  delete [] genmuonphi_;
  delete [] genmuoneta_;
  delete [] genmuone_;
}



void DimuonJet::setup(const edm::ParameterSet& cfg, TTree* CalibTree)
{
  muon_           = cfg.getParameter<edm::InputTag>("DimuonJetMuons");
  genmuons_       = cfg.getParameter<edm::InputTag>("DimuonJetGenMuons");
  beamspot_       = cfg.getParameter<edm::InputTag>("BeamSpot");

  //trigger
  CalibTree->Branch("HltDoubleMu3" ,&hltDoubleMu3_ ,"HltDoubleMu3/O");
  CalibTree->Branch("HltDoubleMu5" ,&hltDoubleMu5_ ,"HltDoubleMu5/O");
  CalibTree->Branch("HltDoubleMu6" ,&hltDoubleMu6_ ,"HltDoubleMu6/O");
  CalibTree->Branch("HltDoubleMu7" ,&hltDoubleMu7_ ,"HltDoubleMu7/O");
  CalibTree->Branch("HltDoubleMu45",&hltDoubleMu45_,"HltDoubleMu45/O");
  CalibTree->Branch("HltMu5IsoMu5" ,&hltMu5IsoMu5_ ,"HltMu5IsoMu5/O");
  CalibTree->Branch("HltMu13Mu8"   ,&hltMu13Mu8_   ,"HltMu13Mu8/O");
  CalibTree->Branch("HltMu17Mu8"   ,&hltMu17Mu8_   ,"HltMu17Mu8/O");
  // Dimuons branches
  CalibTree->Branch("NobjMuon",&nmuons_, "NobjMuon/I");
  CalibTree->Branch("MuonPt",   muonpt_,  "MuonPt[NobjMuon]/F");
  CalibTree->Branch("MuonPhi",  muonphi_, "MuonPhi[NobjMuon]/F");
  CalibTree->Branch("MuonEta",  muoneta_, "MuonEta[NobjMuon]/F");
  CalibTree->Branch("MuonE",    muone_,   "MuonE[NobjMuon]/F");
  CalibTree->Branch("MuonTrackChi2", muontrackchi2_, "MuonTrackChi2[NobjMuon]/F");
  CalibTree->Branch("MuonD0",        muond0_,        "MuonD0[NobjMuon]/F");
  CalibTree->Branch("MuonIsoR03Trk",    muonisor03trk_,    "MuonIsoR03Trk[NobjMuon]/F");
  CalibTree->Branch("MuonIsoR03Em",    muonisor03em_,    "MuonIsoR03Em[NobjMuon]/F");
  CalibTree->Branch("MuonIsoR03Had",    muonisor03had_,    "MuonIsoR03Had[NobjMuon]/F");  
  CalibTree->Branch("MuonIsoR05Trk",    muonisor05trk_,    "MuonIsoR05Trk[NobjMuon]/F");
  CalibTree->Branch("MuonIsoR05Em",    muonisor05em_,    "MuonIsoR05Em[NobjMuon]/F");
  CalibTree->Branch("MuonIsoR05Had",    muonisor05had_,    "MuonIsoR05Had[NobjMuon]/F");
  CalibTree->Branch("MuonPFIsoR04CH",    muonpfisor04ch_,    "MuonPFIsoR04CH[NobjMuon]/F");
  CalibTree->Branch("MuonPFIsoR04NH",    muonpfisor04nh_,    "MuonPFIsoR04NH[NobjMuon]/F");
  CalibTree->Branch("MuonPFIsoR04G",    muonpfisor04g_,    "MuonPFIsoR04G[NobjMuon]/F");
  CalibTree->Branch("MuonGlobal",    muonglobal_,    "MuonGlobal[NobjMuon]/O");
  CalibTree->Branch("MuonTracker",   muontracker_,   "MuonTracker[NobjMuon]/O");
  CalibTree->Branch("MuonStandalone",muonstandalone_,"MuonStandalone[NobjMuon]/O");
  CalibTree->Branch("MuonCalo",      muoncalo_,      "MuonCalo[NobjMuon]/O");
  CalibTree->Branch("MuonNChambers",   muonnchambers_,   "MuonNChambers[NobjMuon]/I");
  CalibTree->Branch("MuonNTrackerHits",muonntrackerhits_,"MuonNTrackerHits[NobjMuon]/I");
  CalibTree->Branch("MuonNPixelHits",  muonnpixelhits_,  "MuonNPixelHits[NobjMuon]/I");
  CalibTree->Branch("MuonNStations",   muonnstations_,   "MuonNStations[NobjMuon]/I");
  CalibTree->Branch("MuonTrackNDoF",   muontrackndof_,   "MuonTrackNDoF[NobjMuon]/I");
  CalibTree->Branch("MuonCharge",      muoncharge_,      "MuonCharge[NobjMuon]/I");
  // GenMuons branches
  CalibTree->Branch("NobjGenMuon",&ngenmuons_,"NobjGenMuon/I");
  CalibTree->Branch("GenMuonPt",  genmuonpt_,  "GenMuonPt[NobjGenMuon]/F");
  CalibTree->Branch("GenMuonPhi", genmuonphi_, "GenMuonPhi[NobjGenMuon]/F");
  CalibTree->Branch("GenMuonEta", genmuoneta_, "GenMuonEta[NobjGenMuon]/F");
  CalibTree->Branch("GenMuonE",   genmuone_,   "GenMuonE[NobjGenMuon]/F");
}

void DimuonJet::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{  
  edm::Handle<edm::TriggerResults> triggerResults;
  
  if( evt.getByLabel(edm::InputTag("TriggerResults::HLT"),triggerResults) ) {
    const edm::TriggerNames & trigNames = evt.triggerNames(*triggerResults);
    size_t id = 0;
    
    hltDoubleMu3_ = false;
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
    }
  }
  //BeamSpot
  edm::Handle<reco::BeamSpot> beamSpotHandle;
  evt.getByLabel(beamspot_,beamSpotHandle);
  reco::BeamSpot myBeamSpot = *beamSpotHandle;
  


  edm::Handle<reco::MuonCollection> muonColl;
  evt.getByLabel(muon_, muonColl);

  nmuons_ = 0;
  for (reco::MuonCollection::const_iterator muo = muonColl->begin(); muo!= muonColl->end(); ++muo){  
    edm::Ref<reco::MuonCollection> muonref(muonColl, nmuons_);
    muonpt_[nmuons_]  = muo->pt();
    muonphi_[nmuons_] = muo->phi();
    muoneta_[nmuons_] = muo->eta();
    muone_[nmuons_]   = muo->energy();
    reco::TrackRef trk = muo->innerTrack();
    if(trk.isNonnull()) {
      muontrackchi2_[nmuons_] = trk-> chi2();
      muond0_[nmuons_] = trk->dxy(myBeamSpot.position());
      muonntrackerhits_[nmuons_] = trk->hitPattern().numberOfValidTrackerHits();
      muonnpixelhits_[nmuons_] = trk->hitPattern().numberOfValidPixelHits();
      muontrackndof_[nmuons_] = trk->ndof();
    } else {
      muontrackchi2_[nmuons_] = 0;
      muond0_[nmuons_] = 0;
      muonntrackerhits_[nmuons_] = 0;
      muonnpixelhits_[nmuons_] = 0;
      muontrackndof_[nmuons_] = 0;
    }
    muonisor03trk_[nmuons_] = muo->isolationR03().sumPt/muo->pt();
    muonisor03em_[nmuons_]  = muo->isolationR03().emEt/muo->pt();
    muonisor03had_[nmuons_] = muo->isolationR03().hadEt/muo->pt();
    muonisor05trk_[nmuons_] = muo->isolationR05().sumPt/muo->pt();
    muonisor05em_[nmuons_]  = muo->isolationR05().emEt/muo->pt();
    muonisor05had_[nmuons_] = muo->isolationR05().hadEt/muo->pt();
    muonpfisor04ch_[nmuons_] = muo->pfIsolationR04().sumChargedHadronPt/muo->pt();
    muonpfisor04nh_[nmuons_] = muo->pfIsolationR04().sumNeutralHadronEt/muo->pt();
    muonpfisor04g_[nmuons_]  = muo->pfIsolationR04().sumPhotonEt/muo->pt();
    muonglobal_[nmuons_] = muo->isGlobalMuon();
    muontracker_[nmuons_] = muo->isTrackerMuon();
    muonstandalone_[nmuons_] = muo->isStandAloneMuon();
    muoncalo_[nmuons_] = muo->isCaloMuon();
    muonnchambers_[nmuons_] = muo->numberOfChambers();
    muonnstations_[nmuons_] = muo->numberOfMatchedStations();
    muoncharge_[nmuons_] = muo->charge();
    
    ++nmuons_;
    if(nmuons_ == NMax_) break;
  }
  
  
  edm::Handle<reco::CandidateCollection> genmuonColl;
  evt.getByLabel(genmuons_,genmuonColl);
  
  ngenmuons_ = 0;
  if(! genmuonColl.isValid()) return;
  for (reco::CandidateCollection::const_iterator ig = genmuonColl->begin(); ig!= genmuonColl->end(); ++ig){  
    genmuonpt_[ngenmuons_]  = ig->pt();
    genmuonphi_[ngenmuons_] = ig->phi();
    genmuoneta_[ngenmuons_] = ig->eta();
    genmuone_[ngenmuons_]   = ig->energy();
    ++ngenmuons_;
    if(ngenmuons_ == NMax_) break;
  }
}
