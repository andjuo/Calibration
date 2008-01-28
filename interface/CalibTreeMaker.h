// -*- C++ -*-
//
// Package:    CalibTreeMaker
// Class:      CalibTreeMaker
// 
/**\class CalibTreeMaker CalibTreeMaker.cc Calibration/CalibTreeMaker/src/CalibTreeMaker.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Christian Autermann
//         Created:  Wed Jul 18 13:54:50 CEST 2007
// $Id: CalibTreeMaker.h,v 1.9 2007/10/25 17:25:05 auterman Exp $
//
//


// system include files
#include <memory>
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"

#include "Calibration/CalibTreeMaker/interface/CalibGammaJet.h"
#include "Calibration/CalibTreeMaker/interface/CalibTrackTower.h"
#include "Calibration/CalibTreeMaker/interface/CalibTrackCluster.h"

//
// class decleration
//

class CalibTreeMaker : public edm::EDAnalyzer {
   public:
      explicit CalibTreeMaker(const edm::ParameterSet&);
      ~CalibTreeMaker();

      TTree * GammaJetTree;
      TTree * TrackTowerTree;
      TTree * TrackClusterTree;

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      //const int errMax(){return 100;}
 
      CalibGammaJet     gammajet_analysis_;
      CalibTrackTower   tracktower_analysis_;
      CalibTrackCluster trackcluster_analysis_;

      edm::InputTag jets_,genjets_,met_,alltowers_,
                    photon_;                    //SRC for gamma/jet analysis
      edm::InputTag track_,tower_;              //SRC for Track/Tower analysis
      edm::InputTag tc_track_,tc_tower_;        //SRC for Track/Cluster analysis
      string _HistName, _TTTreeName, 
             _GJTreeName, _TCTreeName; 	        // Name of histogram file
      TFile* _file;     			// pointer to Histogram file
      bool writeGammaJet_, writeTrackTower_, writeTrackCluster_;
      //int errCnt;

};
