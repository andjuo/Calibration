#include <TROOT.h>
#include <TTree.h>
#include <TDirectory.h>
#include <TH1.h>
#include <TFile.h>
#include <TString.h>
#include <iostream>

// -------------------------------------------------

void printStats(TString branchName, TTree *tree);
void chkInfoInFile(TString inpName);
void chkInfoInFile(int isData, TString inpName);

// -------------------------------------------------

void chkInfo(int isData=0) {
  chkInfoInFile(isData,"ak5FastPF.root");
  chkInfoInFile(isData,"ak7FastPF.root");
  chkInfoInFile(isData,"ak5FastCalo.root");
  chkInfoInFile(isData,"ak7FastCalo.root");
}

// -------------------------------------------------

void chkInfoInFile(int isData, TString inpName) {
  if ((inpName.Index("MC_") == -1) &&
      (inpName.Index("data_") == -1)) {
    inpName.Prepend((isData) ? "data_" : "MC_");
  }
  chkInfoInFile(inpName);
}

// -------------------------------------------------

void chkInfoInFile(TString inpFName) {
  std::cout << "opening file < "<< inpFName << ">\n";
  TFile fin(inpFName,"read");
  if (!fin.IsOpen()) {
    std::cout << "failed to open the file <" << fin.GetName() << ">\n";
    return;
  }
  TTree *tree=(TTree*) fin.Get("GammaJetTree");
  if (!tree) {
    std::cout << "failed to get the tree\n";
    return;
  }
  printStats("NobjTow",tree);
  printStats("NobjJet",tree);
  printStats("NobjGenJet",tree);
  return;
}

// -------------------------------------------------

void printStats(TString branchName, TTree *tree) {
  TString comm= branchName + TString(" >> h1");
  tree->Draw(comm);
  TH1 *h1 = (TH1*)gDirectory->Get("h1");
  if (!h1) {
    std::cout << "failed to get the histo for branch <" << branchName << ">\n";
    return;
  }
  std::cout << branchName << ": h1->GetMean=" << h1->GetMean() << "\n";
  delete h1;
  return;
}

// -------------------------------------------------
