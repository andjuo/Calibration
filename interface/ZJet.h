#ifndef ZJet_H
#define ZJet_H

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

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
//#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/METReco/interface/CaloMET.h"
#include "DataFormats/METReco/interface/CaloMETCollection.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"

#include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"

#include "TrackingTools/TrackAssociator/interface/TrackDetectorAssociator.h"
#include "TrackingTools/TrackAssociator/interface/TrackAssociatorParameters.h"

#include <DataFormats/ParticleFlowCandidate/interface/PFCandidate.h>
#include <DataFormats/ParticleFlowReco/interface/PFCluster.h>
#include <DataFormats/ParticleFlowReco/interface/PFBlock.h>
#include <DataFormats/JetReco/interface/PFJet.h>

class ZJet {
public:
  ZJet(){}; 
  ~ZJet(){}; 

  void setup(const edm::ParameterSet&, TTree*);
  void analyze(const edm::Event&, const edm::EventSetup&, TTree*);

private:
  edm::InputTag jets_,genjets_, met_, z_, genzs_;                    
  edm::InputTag ebrechits_, nonleadingjetspt_;
  edm::InputTag recTracks_, recMuons_;
  edm::InputTag weight_tag, zspJets_, pfJets_, caloJets_;
  double conesize_;
  float weight_;
  TrackDetectorAssociator trackAssociator_;
  TrackAssociatorParameters parameters_;


  //tree variables
  float jcalpt, jcalphi, jcaleta, jcalet, jcale, jscalel2, jscalel3, jscaleZSP, jscaleJPT, jscalePFLOW;
  float jgenpt, jgenphi, jgeneta, jgenet, jgene, jEMF, jscalel2l3, jscalel2l3JPT, jscalel2l3PFLOW;
  float mcalmet,mcalphi,mcalsum, weight;
  float zpt, zphi, zeta, zet, ze; 
  float gzpt, gzphi, gzeta, gzet, gze; 
  int   NobjTowCal;
  int   *towid_phi, *towid_eta, *towid, *townum;
  float *towet, *toweta, *towphi, *towen, *towem, *towhd, *towoe;
  int   NobjETowCal;
  int   *etowid_phi, *etowid_eta, *etowid, *etownum;
  float *etowet, *etoweta, *etowphi, *etowe;
  float nonleadingjetspt;
  int   NobjTrack, NobjCluster;
  bool *trackQualityL, *trackQualityT, *trackQualityHP;
  float *trackpt, *tracketa, *trackphi, *trackp, *tracketaout, *trackphiout;
  float *trackdr, *trackdrout, *trackchi2;
  float *trackemc1, *trackemc3, *trackemc5;
  float *trackhac1, *trackhac3, *trackhac5;
  float *muDR, *muDE;
  int   *trackid, *tracktowid, *tracktowidphi, *tracktowideta, *tracknhits;
  float *clusterenergy, *clustereta, *clusterphi,*clustHDR,*clustEDR,*clustPS1DR,*clustPS2DR, *clustHEnergy, *clustEEnergySum;
  int *clusterid,*clustertype,*clustHID,*clustEID,*clustPS1ID,*clustPS2ID;
  //int   processid;
};

#endif
