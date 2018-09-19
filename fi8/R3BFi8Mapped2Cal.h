// ------------------------------------------------------------
// -----                R3BFi8Mapped2Cal                -----
// -----            Created Jan 13th 2018 by M.Heil       -----
// ----- Convert mapped data to time calibrated data      -----
// ------------------------------------------------------------

#ifndef R3BFI8MAPPED2CAL
#define R3BFI8MAPPED2CAL

#include "R3BBunchedFiberMapped2Cal.h"

class R3BFi8Mapped2Cal: public R3BBunchedFiberMapped2Cal
{
  public:
    R3BFi8Mapped2Cal(Int_t = 1);
    virtual ~R3BFi8Mapped2Cal();

    ClassDef(R3BFi8Mapped2Cal, 1)
};

#endif
