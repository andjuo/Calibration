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
#include "FWCore/Framework/interface/EventSetup.h"

#include "Calibration/CalibTreeMaker/interface/PhotonJet.h"
#include "Calibration/CalibTreeMaker/interface/DimuonJet.h"
#include "Calibration/CalibTreeMaker/interface/TauAna.h"
#include "Calibration/CalibTreeMaker/interface/NJet.h"


template <typename T> class CalibTreeMaker : public edm::EDAnalyzer {
 public:
  explicit CalibTreeMaker(const edm::ParameterSet&);
  ~CalibTreeMaker();
  
  TTree * tree_;
  
 private:
  virtual void beginJob() ;
  virtual void beginRun(const edm::Run&, const edm::EventSetup&) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  PhotonJet photon_analysis_;
  DimuonJet dimuon_analysis_;
  TauAna tau_analysis_;
  NJet<T>  jet_analysis_;

  TFile* file_;
  bool writePhotons_;
  bool writeMuons_;
  bool writeTaus_;
};

//implementation
template <typename T>
CalibTreeMaker<T>::CalibTreeMaker(const edm::ParameterSet& cfg)
{
  //admins
  std::string fileName  = cfg.getParameter<std::string>("OutputFile");
  std::string treeName  = cfg.getParameter<std::string>("TreeName");
  //select
  writePhotons_ = cfg.getParameter<bool>("WritePhotons" );
  writeMuons_ = cfg.getParameter<bool>("WriteMuons" );
  writeTaus_ = cfg.getParameter<bool>("WriteTaus" );

  //open tree file
  file_= new TFile(fileName.c_str(),"RECREATE");
  file_->cd();

  //init tree
  tree_ =  new TTree(treeName.c_str(),"");
  tree_->SetAutoSave(100000000);

  jet_analysis_.setup( cfg, tree_ );
 
  if( writePhotons_){
    photon_analysis_.setup( cfg, tree_ );
  } 
  if( writeMuons_){
    dimuon_analysis_.setup( cfg, tree_ );
  }
  if( writeTaus_){
    tau_analysis_.setup( cfg, tree_ );
  }
}

template <typename T> CalibTreeMaker<T>::~CalibTreeMaker()
{
  file_->Write(); // write out the branches
  file_->Close();
  delete file_;   // close and delete the file
 }

template <typename T> void CalibTreeMaker<T>::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{ 
  jet_analysis_.analyze(evt, setup);

  if( writePhotons_){
    photon_analysis_.analyze(evt, setup);
  }  
  if( writeMuons_){
    dimuon_analysis_.analyze(evt, setup);
  }
  if( writeTaus_){
    tau_analysis_.analyze(evt, setup);
  }
  tree_->Fill();
}

template <typename T> void CalibTreeMaker<T>::beginRun(edm::Run const & iRun, edm::EventSetup const& setup) 
{
  jet_analysis_.beginRun(iRun, setup);
}

template <typename T> void CalibTreeMaker<T>::beginJob()
{
}

template <typename T> void CalibTreeMaker<T>::endJob()
{  
}


#endif
