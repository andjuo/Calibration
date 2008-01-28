#ifndef CalibTrackCluster_H
#define CalibTrackCluster_H

#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TNamed.h"
#include <vector>
#include <map>
#include "TROOT.h"
#include "TChain.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "DataFormats/TrackReco/interface/Track.h"

/** \class CalibTrackCluster
  *  
  * $Date: July 2007
  * \author Christian Autermann
  */
class CalibTrackCluster {
public:
  CalibTrackCluster(){}; 
  ~CalibTrackCluster(){}; 

  void setup(const edm::ParameterSet& pSet, TTree* tree);

  /** Analyze the Data */
  void analyze(const reco::TrackCollection& tracks,
	       const CaloTowerCollection& towers,
	       TTree* tree);

private:

  // Tree variables
  float tracket,tracketerr, tracketa, trackphi, tracken;
  float *towet, *toweta, *towphi, *towen, *towem, *towhd, *towoe;
  int   NobjTowCal,NobjTrackCal;
  int   *towid_phi, *towid_eta, *towid;
};

#endif
