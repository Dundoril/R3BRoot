// R3BFibDigitizer.h 07. 08. 2017.
// Created by: Aron Kripko

#ifndef R3BFibDIGITISER_H
#define R3BFIBDIGITISER_H 1


#include "FairTask.h"
#include <map>
#include <string>
#include "R3BFibHitItem.h"
#include <TRandom3.h>


class TClonesArray;
class TH1F;
class TH2F;



class R3BFibDigitizer : public FairTask
{

 public:

  /** Default constructor **/  
  R3BFibDigitizer();
  
  
  R3BFibDigitizer(Double_t esigma, Double_t tsigma, Double_t ysigma);


  /** Destructor **/
  ~R3BFibDigitizer();


  /** Virtual method Init **/
  virtual InitStatus Init();


  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);

  virtual void Finish();
  virtual void Reset();
  
  void SetEnergyResolution(Double_t e);
  void SetTimeResolution(Double_t t);
  void SetYPositionResolution(Double_t y);
  

  protected:
  
	  //TClonesArray* fFibPoints;
	  //TClonesArray* fFi6Points;
	  //TClonesArray* fFi5Points;
	  TClonesArray* fFi11Points;
	  
	  TClonesArray* fMCTrack; 
	  
	  //TClonesArray* fFibHits;
	  //TClonesArray* fFi6Hits;
	  //TClonesArray* fFi5Hits;
	  TClonesArray* fFi11Hits;
	  
  private:
  
	TRandom3* prnd;
	Double_t esigma;
	Double_t tsigma;
	Double_t ysigma;
	
	
   ClassDef(R3BFibDigitizer,1);
  
};

#endif
