#ifndef R3BFI3CONTFACT_H
#define R3BFI3CONTFACT_H

#include "FairContFact.h"

class FairContainer;

class R3BFi3ContFact : public FairContFact {
private:
  void setAllContainers();
public:
  R3BFi3ContFact();
  ~R3BFi3ContFact() {}
  FairParSet* createContainer(FairContainer*);
  void  activateParIo(FairParIo* io);
  ClassDef( R3BFi3ContFact,0) // Factory for all Fi4 parameter containers
};

#endif  /* !R3BFI3CONTFACT_H */
