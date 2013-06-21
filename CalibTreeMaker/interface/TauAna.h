#ifndef TauAna_H
#define TauAna_H

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

class TauAna {
public:
  TauAna(); 
  ~TauAna(); 

  void setup(const edm::ParameterSet&, TTree*);
  void analyze(const edm::Event&, const edm::EventSetup&);

private:
  edm::InputTag tau_, discriminator_;                    

  //tree variables
  int ntaus_, ngentaus_;
  bool hltDoubleMu3_, hltDoubleMu5_,hltDoubleMu6_, hltDoubleMu7_,hltDoubleMu45_,hltMu5IsoMu5_,hltMu13Mu8_,hltMu17Mu8_,hltisomu24eta2p1_;
  float *taupt_, *tauphi_, *taueta_, *taue_;
  float *tauid_;
  static const int NMax_;
};

#endif
