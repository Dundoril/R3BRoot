#include "R3BFi11Cal2Hit.h"

R3BFi11Cal2Hit::R3BFi11Cal2Hit(Int_t a_verbose)
  : R3BBunchedFiberCal2Hit("Fi11", a_verbose, 256, 4)
{
  CreateSub(VERTICAL, 0);
  CreateSub(VERTICAL, 1);
}

R3BFi11Cal2Hit::~R3BFi11Cal2Hit()
{
}

UInt_t R3BFi11Cal2Hit::FixMistake(UInt_t a_fiber_id)
{
//  if (192 == a_fiber_id) a_fiber_id = 15;
//  if (256 == a_fiber_id) a_fiber_id = 16;
 

  return a_fiber_id;
}

ClassImp(R3BFi11Cal2Hit)
