#ifndef CalibTreeMaker_H
#define CalibTreeMaker_H

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
#include "Calibration/CalibTreeMaker/interface/JetJet.h"

class CalibTreeMaker : public edm::EDAnalyzer {
 public:
  explicit CalibTreeMaker(const edm::ParameterSet&);
  ~CalibTreeMaker();
  
  TTree * PhotonJetTree;
  TTree * TrackTowerTree;
  TTree * JetJetTree;
  
 private:
  virtual void beginJob(const edm::EventSetup&) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  PhotonJet photonjet_analysis_;
  TrackTower tracktower_analysis_;
  JetJet jetjet_analysis_;

  std::string _HistName;
  std::string _TTTreeName, _PJTreeName, _JJTreeName;
  TFile* _file;
  bool writePhotonJet_, writeTrackTower_, writeJetJet_;
};

#endif
