#ifndef CalibTreeMaker_H
#define CalibTreeMaker_H

#define CMSSW_2_1_X

#include <memory>
#include <iostream>

#include "TFile.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"

#include "Calibration/CalibTreeMaker/interface/PhotonJet.h"
#include "Calibration/CalibTreeMaker/interface/TrackTower.h"
#include "Calibration/CalibTreeMaker/interface/NJet.h"
#include "Calibration/CalibTreeMaker/interface/Top.h"
#include "Calibration/CalibTreeMaker/interface/ZJet.h"

template <typename T> class CalibTreeMaker : public edm::EDAnalyzer {
 public:
  explicit CalibTreeMaker(const edm::ParameterSet&);
  ~CalibTreeMaker();
  
  TTree * PhotonJetTree;
  TTree * TrackTowerTree;
  TTree * DiJetTree;
  TTree * TriJetTree;
  TTree * TopTree;
  TTree * ZJetTree;
  
 private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  PhotonJet photonjet_analysis_;
  TrackTower tracktower_analysis_;
  NJet<T>  DiJet_analysis_;
  NJet<T>  TriJet_analysis_;
  Top   Top_analysis_;
  ZJet  zjet_analysis_;

  std::string _HistName;
  std::string _TTTreeName, _PJTreeName, _JJTreeName, _JJJTreeName, _TopTreeName, _ZJTreeName;
  TFile* _file;
  bool writePhotonJet_, writeTrackTower_, writeDiJet_, writeTriJet_, writeTop_, writeZJet_;
};

//implementation
template <typename T>
CalibTreeMaker<T>::CalibTreeMaker(const edm::ParameterSet& cfg)
{
  _file=0;
  
  //admins
  _HistName    = cfg.getParameter<std::string>("OutputFile");
  _TTTreeName  = cfg.getParameter<std::string>("TrackTowerTreeName");
  _PJTreeName  = cfg.getParameter<std::string>("PhotonJetTreeName" );
  _JJTreeName  = cfg.getParameter<std::string>("DiJetTreeName");
  _JJJTreeName = cfg.getParameter<std::string>("TriJetTreeName");
  _TopTreeName = cfg.getParameter<std::string>("TopTreeName");
  _ZJTreeName  = cfg.getParameter<std::string>("ZJetTreeName" );

  //select
  writePhotonJet_ = cfg.getParameter<bool>("WritePhotonJetTree" );
  writeTrackTower_= cfg.getParameter<bool>("WriteTrackTowerTree");
  writeDiJet_     = cfg.getParameter<bool>("WriteDiJetTree");
  writeTriJet_    = cfg.getParameter<bool>("WriteTriJetTree");
  writeTop_       = cfg.getParameter<bool>("WriteTopTree");
  writeZJet_      = cfg.getParameter<bool>("WriteZJetTree");

  //open tree file
  _file=new TFile(_HistName.c_str(),"RECREATE");
  _file->cd();

  //init tree
  if( writePhotonJet_){
    PhotonJetTree   = new TTree(_PJTreeName.c_str(),"");
   photonjet_analysis_.setup( cfg, PhotonJetTree );
  }
  if( writeTrackTower_){
    TrackTowerTree  = new TTree(_TTTreeName.c_str(),"");
    tracktower_analysis_.setup( cfg, TrackTowerTree );
  }
  if (writeDiJet_){
    DiJetTree      = new TTree(_JJTreeName.c_str(),"");
    DiJet_analysis_.setup( cfg, DiJetTree );
  }
  if (writeTriJet_){
    TriJetTree      = new TTree(_JJJTreeName.c_str(),"");
    TriJet_analysis_.setup( cfg, TriJetTree );
  }
  if (writeTop_){ 	 
    TopTree      = new TTree(_TopTreeName.c_str(),""); 	 
    Top_analysis_.setup( cfg, TopTree ); 	 
  }
  if( writeZJet_){
    ZJetTree   = new TTree(_ZJTreeName.c_str(),"");
    zjet_analysis_.setup( cfg, ZJetTree );
  }
}

template <typename T> CalibTreeMaker<T>::~CalibTreeMaker()
{
}

template <typename T> void CalibTreeMaker<T>::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{
  edm::ESHandle<CaloGeometry> geometry;
  
  if( writePhotonJet_){
    photonjet_analysis_.analyze(evt, setup, PhotonJetTree);
  }

  if( writeTrackTower_){
    tracktower_analysis_.analyze(evt, setup, TrackTowerTree);
  }

  if (writeDiJet_){
    DiJet_analysis_.analyze(evt, setup, DiJetTree);
  }
  if (writeTriJet_){
    TriJet_analysis_.analyze(evt, setup, TriJetTree);
  }
  if (writeTop_){ 	 
    Top_analysis_.analyze(evt, setup, TopTree); 	 
  }
  if( writeZJet_){
    zjet_analysis_.analyze(evt, setup, ZJetTree);
  }
}

template <typename T> void CalibTreeMaker<T>::beginJob()
{
}

template <typename T> void CalibTreeMaker<T>::endJob()
{  
  _file->cd(); 
  if( writePhotonJet_){
    PhotonJetTree->Write();
    delete PhotonJetTree;
  }
  if(writeTrackTower_){
    TrackTowerTree->Write();
    delete TrackTowerTree;
  }
  if(writeDiJet_){
    DiJetTree->Write();
    delete DiJetTree;
  } 
  if(writeTriJet_){
    TriJetTree->Write();
    delete TriJetTree;
  } 
  if(writeTop_){ 	 
    TopTree->Write(); 	 
    delete TopTree; 	 
  }
  if( writeZJet_){
    ZJetTree->Write();
    delete ZJetTree;
  }

  if (_file!=0) {   // if there was a tree file...
    _file->Write(); // write out the branches
    _file->Close();
    delete _file;   // close and delete the file
    _file=0;        // set to zero to clean up
  }
}


#endif
