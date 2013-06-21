#ifndef PhotonJet_H
#define PhotonJet_H

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

class PhotonJet {
public:
  PhotonJet(); 
  ~PhotonJet(); 

  void setup(const edm::ParameterSet&, TTree*);
  void analyze(const edm::Event&, const edm::EventSetup&);

private:
  edm::InputTag photon_, genphotons_;                    

  //tree variables
  int nphotons_, ngenphotons_;
  bool hltPhoton20calo_, hltPhoton30calo_, hltPhoton50calo_,hltPhoton75calo_,hltPhoton90calo_,hltPhoton135_,hltPhoton150_,hltPhoton160_;
  bool hltPhoton20iso_, hltPhoton30iso_, hltPhoton50iso_,hltPhoton75iso_,hltPhoton90iso_;
  bool hltPhoton30_,  hltPhoton30R9_;
  float *photonpt_, *photonphi_, *photoneta_, *photone_;
  float *photonisoecal04_,*photonisohcal04_, *photonisotrk04_, *photonsigmaietaieta_, *photonhovere_;
  bool *photonidloose_,*photonidtight_,*photonhaspixelseed_;
  float *genphotonpt_, *genphotonphi_, *genphotoneta_, *genphotone_; 
  static const int NMax_;
};

#endif
 
