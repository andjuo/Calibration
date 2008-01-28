#ifndef CalibTrackTower_H
#define CalibTrackTower_H

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

/** \class CalibTrackTower
  *  
  * $Date: July 2007
  * \author Christian Autermann
  * original code by L. Apanasevich - UIC, P. Bargassa - Rice U.
  */
class CalibTrackTower {
public:
  CalibTrackTower(){}; 
  ~CalibTrackTower(){}; 

  void setup(const edm::ParameterSet& pSet, TTree* tree);

  /** Analyze the Data */
  void analyze(const reco::TrackCollection& tracks,
	       const CaloTowerCollection& towers,
	       TTree* tree);

private:

  // Tree variables
  float *tracket,*tracketerr, *tracketa, *trackphi, *tracken;
  float *towet, *toweta, *towphi, *towen, *towem, *towhd, *towoe;
  int   NobjTowCal,NobjTrackCal;
  int   *towid_phi, *towid_eta, *towid;
};

#endif
