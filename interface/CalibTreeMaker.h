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
// $Id: CalibTreeMaker.h,v 1.10 2008/01/23 15:27:57 auterman Exp $
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
#include "Calibration/CalibTreeMaker/interface/CalibJetJet.h"

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
      TTree * JetJetTree;

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
 
      CalibGammaJet     gammajet_analysis_;
      CalibTrackTower   tracktower_analysis_;
      CalibTrackCluster trackcluster_analysis_;
      CalibJetJet       jetjet_analysis_;

      edm::InputTag track_,tower_;              //SRC for Track/Tower analysis
      edm::InputTag tc_track_,tc_tower_;        //SRC for Track/Cluster analysis
      edm::InputTag jj_jets_,jj_genjets_;       //SRC for Jet/Jet analysis
      edm::InputTag met_,alltowers_;
      string _HistName, _TTTreeName, 
             _GJTreeName, _TCTreeName,
	     _JJTreeName;          	        // Name of histogram file
      TFile* _file;     			// pointer to Histogram file
      bool writeGammaJet_, writeTrackTower_, writeTrackCluster_,
           writeJetJet_;
      //int errCnt;

};
