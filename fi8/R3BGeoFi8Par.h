#ifndef R3BGEOFI8PAR_H
#define R3BGEOFI8PAR_H
 
#include "FairParGenericSet.h"

#include "TH1F.h"

class R3BGeoFi8Par : public FairParGenericSet {
public:
  TObjArray            *fGeoSensNodes; // List of FairGeoNodes for sensitive volumes
  TObjArray            *fGeoPassNodes; // List of FairGeoNodes for sensitive volumes

  R3BGeoFi8Par(const char* name="R3BGeoFi8Par",
             const char* title="Fi8 Geometry Parameters",
             const char* context="TestDefaultContext");
  ~R3BGeoFi8Par(void);
  void clear(void);
  void putParams(FairParamList*);
  Bool_t getParams(FairParamList*);
  TObjArray             *GetGeoSensitiveNodes(){return fGeoSensNodes;}
  TObjArray             *GetGeoPassiveNodes(){return fGeoPassNodes;}

  ClassDef(R3BGeoFi8Par,1)
};

#endif /* !R3BGEOFI8PAR_H */
