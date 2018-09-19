// ------------------------------------------------------------
// -----                R3BFi11Mapped2Cal                -----
// -----            Created Jan 13th 2018 by M.Heil       -----
// ----- Convert mapped data to time calibrated data      -----
// ------------------------------------------------------------

#ifndef R3BFI11MAPPED2CAL
#define R3BFI11MAPPED2CAL

#include "R3BBunchedFiberMapped2Cal.h"

class R3BFi11Mapped2Cal: public R3BBunchedFiberMapped2Cal
{
  public:
    R3BFi11Mapped2Cal(Int_t = 1);
    virtual ~R3BFi11Mapped2Cal();

    ClassDef(R3BFi11Mapped2Cal, 1)
};

#endif
