#ifndef NTUPLEREADER_H
#define NTUPLEREADER_H 

//root includes:
#include "TFile.h"
#include "TH1F.h"
#include "TChain.h"
#include "TTree.h"
#include "TString.h"
#include "TMath.h"

//File work includes:
#include <iostream>
#include <ostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include "TROOT.h"
#include <stdio.h>

/*
This code is meant to read ntuples for one type of oscillation analysis at a time
Signal options are currently "nue" and "numu"
This code reads the reprocessed files and creates hist files, or it reads the hist files
if they already exist.  
Either way, you can access the data with the GetData() and GetDataOsc() methods.

 */

class NtupleReader
{
public:
  NtupleReader();
  NtupleReader( std::string signal,
                std::string path,
                int baseline,
                std::string beammode,
                std::string energy,
                int npoints,
                bool forceRemake);
  // ~NtupleReader();

  std::vector<float> GetData() const;
  std::vector<std::vector<float > > GetDataOsc() const;
  std::vector<float> GetVectorFromTree(char * branchName, char * treeName = NULL, bool osc = false) const;

  //return 0 on successful completion.  Return >0 if failure.
  /* Error codes I'm using...
  1:  Unknown "mode", has to be a string that is "nu" or "nubar"
  2:  Failure to open input file, prints out the files it tried and their directory
  3:  Unknown baseline, doesn't know POT Normalization
  4:  Error on looping over the events.
  5:  Error opening tree from file.
  6:  Some sort of problem with input parameters
  */
  int processData();

  void setBins(std::vector<float>);
  void setSignal(std::string);
  void setPath(std::string);
  void setBeammode(std::string);
  void setBaseline(int);
  void setForceRemake(bool);
  void setEnergy(std::string);
  void setNpoints(int);
  void setScale(double);
  void setSpecialNameText(std::string s);
  void setSpecialNameTextOsc(std::string s);

  int LoopNue();
  int LoopNumu();
  int LoopNueOsc();
  int LoopNumuOsc();

  int ReadNue();
  int ReadNueOsc();
  int ReadNumu();
  int ReadNumuOsc();

private:

  std::string signal;
  TString path;
  int baseline;
  std::string beammode;
  bool forceRemake;
  std::vector<float> bins;
  std::string energy;
  int npoints;


  std::string specialNameText;
  std::string specialNameTextOsc;
  bool isScaling;
  double scale;

  TString fileNameHists;
  TString fileNameHistsOsc;
  TString fileNameSource;
  TString fileNameSourceOsc;

  void buildFileNameHists();
  void buildFileNameSource();

  bool fileExists(const char *filename) const;
  bool UpToDate(const char *, const char *) const;
  bool remakeHists() const;
  bool remakeHistsOsc() const;

  /* data */
  std::vector<float> data;
  std::vector<std::vector<float> > dataOsc;
};


inline void NtupleReader::setBins(std::vector<float> input_bins)  { bins = input_bins;}
inline void NtupleReader::setSignal(std::string input_signal)     { signal = input_signal;}
inline void NtupleReader::setPath(std::string input_path)         { path = input_path;}
inline void NtupleReader::setBeammode(std::string input_beammode) { beammode = input_beammode;}
inline void NtupleReader::setBaseline(int input_baseline)         { baseline = input_baseline;}
inline void NtupleReader::setForceRemake(bool input_forceRemake)  { forceRemake = input_forceRemake;}
inline void NtupleReader::setEnergy(std::string input_energy)     { energy = input_energy;}
inline void NtupleReader::setNpoints(int input_Npoints)           { npoints = input_Npoints;}





#endif