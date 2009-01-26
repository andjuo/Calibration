#ifndef PhotonJet_H
#define PhotonJet_H

#include <string>
#include <vector>
#include <iostream>

#include "TFile.h"
#include "TNamed.h"
#include "TChain.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
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
#include "DataFormats/EgammaCandidates/interface/Photon.h"
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

class PhotonJet {
public:
  PhotonJet(){}; 
  ~PhotonJet(){}; 

  void setup(const edm::ParameterSet&, TTree*);
  void analyze(const edm::Event&, const edm::EventSetup&, TTree*);

private:
  edm::InputTag jets_,genjets_, met_, photon_, genphotons_;                    
  edm::InputTag ebrechits_, nonleadingjetspt_;
  edm::InputTag recTracks_, recMuons_;
  edm::InputTag weight_tag, zspJets_;
  double conesize_;
  float weight_;
  TrackDetectorAssociator trackAssociator_;
  TrackAssociatorParameters parameters_;


  //tree variables
  float jcalpt, jcalphi, jcaleta, jcalet, jcale, jscalel2, jscalel3, jscaleZSP, jscaleJPT;
  float jgenpt, jgenphi, jgeneta, jgenet, jgene;
  float mcalmet,mcalphi,mcalsum, weight;
  float photonpt, photonphi, photoneta, photonet, photone; 
  float gphotonpt, gphotonphi, gphotoneta, gphotonet, gphotone; 
  int   NobjTowCal;
  int   *towid_phi, *towid_eta, *towid, *townum;
  float *towet, *toweta, *towphi, *towen, *towem, *towhd, *towoe;
  int   NobjETowCal;
  int   *etowid_phi, *etowid_eta, *etowid, *etownum;
  float *etowet, *etoweta, *etowphi, *etowe;
  float nonleadingjetspt;
  int   NobjTrack;
  bool  *trackQualityL, *trackQualityT, *trackQualityHP;
  float *trackpt, *tracketa, *trackphi, *trackp, *tracketaout, *trackphiout;
  float *trackdr, *trackdrout, *trackchi2;
  float *trackemc1, *trackemc3, *trackemc5;
  float *trackhac1, *trackhac3, *trackhac5;
  float *muDR, *muDE;
  int   *trackid, *tracktowid, *tracktowidphi, *tracktowideta, *tracknhits;
  //int   processid;
};

#endif
