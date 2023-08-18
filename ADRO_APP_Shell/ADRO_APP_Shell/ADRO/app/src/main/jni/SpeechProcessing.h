//
//  SpeechProcessing.h
//
//
//  Created by Abhishek Sehgal on 8/14/17.
//  Modified by Chowdhury, Tahsin on 11/02/17 for integration
//  Copyright © 2017 SIPLab. All rights reserved.
//

#ifndef __Speech_Processing_Pipeline__SpeechProcessing__
#define __Speech_Processing_Pipeline__SpeechProcessing__

#include <stdio.h>
#include <math.h>


#include "adro_Main.h"
#include "firGen/firGen.h"
#include "FFT/Forward_FFT.h"
extern "C" {
#include "FIRFilter.h"
}
//#include "Transforms.h"
//#include "SPLBuffer.h"
//#include "Settings.h"
//#include "CompressionSettingController.h"
//#include "CommonHeaders/rt_nonfinite.h"
//#include "NoiseReductionCode/wiener_ADAPTIVE_NE.h"
//#include "NoiseReductionCode/wiener_ADAPTIVE_NE_terminate.h"
//#include "NoiseReductionCode/wiener_ADAPTIVE_NE_initialize.h"
//#include "DynamicRangeMultibandCompression/DynamicRangeFiveBandCompression.h"
//#include "DynamicRangeMultibandCompression/DynamicRangeFiveBandCompression_initialize.h"
//#include "DynamicRangeMultibandCompression/DynamicRangeFiveBandCompression_terminate.h"
//#include "MelSpectrogram.h"

#define NFILT               40
#define FREQLOW             300
#define FREQHIGH            8000
#define DECIMATION_FACTOR 2
#define EPS 1.0e-7
#define S2F 3.051757812500000e-05f
#define F2S 32768







//****iOS takes short as Input buffer***//
//void doNoiseReduction_Compression_withVAD(VADNoiseReductionCompression *_ptr, short *_in, short* _out, Settings* settings);
//***SuperpoweredSDK(used in Android) handles short to float conversion input buffer***//
void doApplyGain(ADRO_Input *_ptr, ADRO_str *adrostr,float *_in, float* _out);
void destroyApplyGain(ADRO_Input** _ptr);

#endif /* defined(__Speech_Processing_Pipeline__SpeechProcessing__) */

