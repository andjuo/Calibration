#ifndef CalibTreeMaker_H
#define CalibTreeMaker_H

#define CMSSW_2_1_X

#include <memory>
#include <iostream>

#include "TFile.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
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

class CalibTreeMaker : public edm::EDAnalyzer {
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
  NJet  DiJet_analysis_;
  NJet  TriJet_analysis_;
  Top   Top_analysis_;
  ZJet  zjet_analysis_;

  std::string _HistName;
  std::string _TTTreeName, _PJTreeName, _JJTreeName, _JJJTreeName, _TopTreeName, _ZJTreeName;
  TFile* _file;
  bool writePhotonJet_, writeTrackTower_, writeDiJet_, writeTriJet_, writeTop_, writeZJet_;
};

#endif
