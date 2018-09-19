#include "FairLogger.h"

#include "TClonesArray.h"
#include "FairRootManager.h"
#include "R3BLosReader.h"
#include "R3BLosMappedData.h"
extern "C" {
#include "ext_data_client.h"
#include "ext_h101_los_tamex.h"
}
#include "TMath.h"
#define IS_NAN(x) TMath::IsNaN(x)
#define NUM_LOS_DETECTORS 1
#define NUM_LOS_CHANNELS  8
#include <iostream>

using namespace std;

R3BLosReader::R3BLosReader(EXT_STR_h101_LOS_TAMEX* data, UInt_t offset)
	: R3BReader("R3BLosReader")
	, fData(data)
	, fOffset(offset)
	, fLogger(FairLogger::GetLogger())
    , fArray(new TClonesArray("R3BLosMappedData"))
{	
}

R3BLosReader::~R3BLosReader()
{
}

Bool_t R3BLosReader::Init(ext_data_struct_info *a_struct_info)
{

	int ok;

	EXT_STR_h101_LOS_TAMEX_ITEMS_INFO(ok, *a_struct_info, fOffset,
	    EXT_STR_h101_LOS_TAMEX, 0);

	if (!ok) {
		perror("ext_data_struct_info_item");
		fLogger->Error(MESSAGE_ORIGIN,
		    "Failed to setup structure information.");
		return kFALSE;
	}

    // Register output array in tree
    FairRootManager::Instance()->Register("LosMapped", "Land", fArray, kTRUE);

	// clear struct_writer's output struct. Seems ucesb doesn't do that
	// for channels that are unknown to the current ucesb config.
	EXT_STR_h101_LOS_TAMEX_onion* data = (EXT_STR_h101_LOS_TAMEX_onion*)fData;
	for (int d=0;d<NUM_LOS_DETECTORS;d++)
	{
	    data->LOS[d].VTFM=0;
	    data->LOS[d].VTCM=0;
	    data->LOS[d].TTFLM=0;
	    data->LOS[d].TTFTM=0;
	    data->LOS[d].TTCLM=0;
	    data->LOS[d].TTCTM=0;
    }
	return kTRUE;
}

Bool_t R3BLosReader::Read()
{
	// Convert plain raw data to multi-dimensional array
    EXT_STR_h101_LOS_TAMEX_onion* data = (EXT_STR_h101_LOS_TAMEX_onion*)fData;
    
/*
 * For variable definition, see structure EXT_STR_h101_LOS_TAMEX_onion_t 
 * in ext_str_h101_los_tamex.h
 *** VFTX DATA ***
 * VTF = Size of the array TFv contaning fine VFTX times
 * VTFv = Array containing the actual data on the fine  times
 * VTFM = No of channels having time
 * VTFMI = Array of TFM size containing the channel numbers of each channel with data
 * VTFME = Array of TFM size containing the index of the first element of the next channel in data array TFv
 *
 * VTC = Size of the array TCv contaning coarse VFTX times
 * VTCv = Array containing the actual data on the coarse times
 * VTCM = No of channels having coarse time
 * VTCMI = Array of TCM size containing the channel numbers of each channel with data
 * VTCME = Array of TCM size containing the index of the first element of the next channel in data array TCv 
 * 
 *** TAMEX DATA *** Added by Aleksandra, Oct. 2016
 * TTFL = Size of the array TFLv contaning fine leading times
 * TTFLv = Array containing the actual data on the fine leading times
 * TTFLM = No of channels having fine leading time
 * TTFLMI = Array of TFLM size containing the channel numbers of each channel with data
 * TTFLME = Array of TFLM size containing the index of the first element of the next channel in data array TFLv
 *
 * TTCL = Size of the array TCLv contaning coarse leading times
 * TTCLv = Array containing the actual data on the coarse leading times
 * TTCLM = No of channels having coarse leading time
 * TTCLMI = Array of TCLM size containing the channel numbers of each channel with data
 * TTCLME = Array of TCLM size containing the index of the first element of the next channel in data array TCLv
 *  
 * The same logic is for trailing times: TTFT, TTFTv, ..., TTCTMI, TTCTME
*/
      
	// loop over all detectors
	for (int d=0;d<NUM_LOS_DETECTORS;d++)
	{		    
		uint32_t numChannels  = data->LOS[d].VTFM; // not necessarly number of hits! (b/c multi hit)
		uint32_t numChannelsL = data->LOS[d].TTFLM;
        uint32_t numChannelsT = data->LOS[d].TTFTM;
        
 //cout<<"LOS Reader, numChannels: "<<numChannels<<", "<<numChannelsL<<", "<<numChannelsT<<endl;


/*
 In case of small signals, all 8 of TAMEX channels do not fire always, but those VFTX do.
 Thus, temporray time ararys are firstly made separately for VFTX and TAMEX, and then they
 are merged together.  
*/ 
 
 // First, we prepare time arrays for VFTX
 
     
  // loop over channels
	 uint32_t curChannelStart=0;     // index in v for first item of current channel
	 
	for(int k=0;k<8;k++){ 
      fine_times_VFTX[k]=1000000;     // first set unreasonably high values
      coarse_times_VFTX[k]=1000000;
      fine_times_TAMEX_L[k]=1000000;     // first set unreasonably high values
      coarse_times_TAMEX_L[k]=1000000;     
      fine_times_TAMEX_T[k]=1000000;     
      coarse_times_TAMEX_T[k]=1000000;
     }
    
        
    for (int i=0;i<numChannels;i++)  // i=0,1,2,3...NUM_LOS_CHANNELS-1
	{
		uint32_t channel=data->LOS[d].VTFMI[i]; // or 1..65			
		
		uint32_t nextChannelStart=data->LOS[d].VTFME[i];  // index in v for first item of next channel

   		for (int j=curChannelStart;j<nextChannelStart;j++){
            
            fine_times_VFTX[channel-1]=data->LOS[d].VTFv[j];     // VFTX fine time
            coarse_times_VFTX[channel-1]=data->LOS[d].VTCv[j];   // VFTX coarse time
            
	    }
																   			
					
		curChannelStart=nextChannelStart;
     }
     
   
 // Now, we prepare time arrays for TAMEX, but only if leading and trailing edge same number of channels have
 if(numChannelsL == numChannelsT)
 {
            
		// loop over channels
	  uint32_t curChannelStartL=0;     // index in v for first item of current channel

		for (int i=0;i<numChannelsL;i++)  // i=0,1,2,3...NUM_LOS_CHANNELS-1
		{
			uint32_t channelL=data->LOS[d].TTFLMI[i]; // or 1..65
						
			uint32_t nextChannelStartL=data->LOS[d].TTFLME[i]; // index in v for first item of next channel


  			for (int j=curChannelStartL;j<nextChannelStartL;j++){
                                      
             fine_times_TAMEX_L[channelL-1]=data->LOS[d].TTFLv[j];
             fine_times_TAMEX_T[channelL-1]=data->LOS[d].TTFTv[j];
             coarse_times_TAMEX_L[channelL-1]=data->LOS[d].TTCLv[j];
             coarse_times_TAMEX_T[channelL-1]=data->LOS[d].TTCTv[j];
		    																								   		
		}
			     		    		
			curChannelStartL=nextChannelStartL;
		}
		
  }	
             Int_t itstart = 0;
             Int_t itstop = 3;
   if(numChannels > 0){
      for ( int k=0;k<NUM_LOS_CHANNELS;k++)  // i=0,1,2,3...NUM_LOS_CHANNELS-1
      {          	  
		  
        uint32_t fine_times[3]={fine_times_VFTX[k],fine_times_TAMEX_L[k],fine_times_TAMEX_T[k]};
        uint32_t coarse_times[3]={coarse_times_VFTX[k],coarse_times_TAMEX_L[k],coarse_times_TAMEX_T[k]};        
        
             
             for (Int_t itype=itstart ; itype<itstop; itype++){	                
								
				new ((*fArray)[fArray->GetEntriesFast()])				
					R3BLosMappedData(
						d+1,    // detector number
						k+1,      // channel number: 1-8
						itype,  // VFTX (0),TAMEX leading (1), TAMEX trailing (2)
						fine_times[itype],  
						coarse_times[itype]								
						); // det,channel,type,fine_time,coarse_time; type = 0:VFTX, 1:TAMEX leading, 2: Tamex trailing
				
		

//cout<<"R3BReader fMapped array: "<<"channel= "<<k+1<<"; Type= "<<itype<<"; Fine time= "<<fine_times[itype]<<"; Coarse time= "<<coarse_times[itype]<<endl;

            }
        }
     }  
  }          

    return kTRUE;
}
void R3BLosReader::FinishTask()
{
        	
}
void R3BLosReader::Reset()
{
    // Reset the output array
    fArray->Clear();
}

ClassImp(R3BLosReader)

