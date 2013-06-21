#ifndef DimuonJet_H
#define DimuonJet_H

#include <string>
#include <vector>
#include <iostream>

#include "TFile.h"
#include "TNamed.h"
#include "TChain.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"

class DimuonJet {
public:
  DimuonJet(); 
  ~DimuonJet(); 

  void setup(const edm::ParameterSet&, TTree*);
  void analyze(const edm::Event&, const edm::EventSetup&);

private:
  edm::InputTag muon_, genmuons_,beamspot_;                    

  //tree variables
  int nmuons_, ngenmuons_;
  bool hltDoubleMu3_, hltDoubleMu5_,hltDoubleMu6_, hltDoubleMu7_,hltDoubleMu45_,hltMu5IsoMu5_,hltMu13Mu8_,hltMu17Mu8_;
  float *muonpt_, *muonphi_, *muoneta_, *muone_;
  float *muontrackchi2_,*muond0_,*muonisor03trk_,*muonisor03em_,*muonisor03had_,*muonisor05trk_,*muonisor05em_,*muonisor05had_,*muonpfisor04ch_,*muonpfisor04nh_,*muonpfisor04g_;
  bool *muonglobal_,*muontracker_,*muonstandalone_,*muoncalo_;
  int *muonnchambers_,*muonntrackerhits_,*muonnpixelhits_,*muonnstations_,*muontrackndof_,*muoncharge_;
  float *genmuonpt_, *genmuonphi_, *genmuoneta_, *genmuone_; 
  static const int NMax_;
};

#endif
