//
//  SpeechProcessing.c
// Signal Processing Pipeline:
//  Voice Activity Detection with NoiseReduction and compression
//
//  Created by Abhishek Sehgal on 8/14/17.
//  Modified by Chowdhury, Tahsin on 11/02/17 for integration
//  Copyright © 2017 SIPLab. All rights reserved.
//

#include <sys/time.h>
#include "SpeechProcessing.h"
#include <android/log.h>




//Notes:
//1. Here, 50% overlapping is performed after downsampling the audio signal and stored in 'inParam->inputBuffer'.
//   This is used for FFT calculation (Transform section) to calculate power, which is the input to the VAD module.
//
//2. Noise Reduction code is converted from MATLAB to C using MATLAB Coder, and it uses its own fft with 50%
//   overlapping inside noise reduction module. So, 'inParam->decimated' is used as input to it. If users want to
//   change the module or replace with another Noise reduction that requires input with overlap, they can use
//   'inParam->inputBuffer'.
//
//3. Compression module is placed after noise reduction module so that it can use the processed output from noise
//   reduction for compression as its input. This can also be used with Noise Reduction is turned off.
//

void doApplyGain(ADRO_Input *_ptr,ADRO_str *adrostr ,float *_in, float* _out){

    ADRO_Input *inParam = _ptr;
    for (int i = 0; i < inParam->N; i++) {
        inParam->adroinputbuffer[i] = _in[i];
    }

    for (int i = 0; i < inParam->N; i++) {
        inParam->fftbuffer[i] = inParam->fftbuffer[inParam->N + i];
        inParam->fftbuffer[inParam->N + i] = _in[i];
    }
    for (int i = 0; i < inParam->N; i++) {
        inParam->fftbuffer[i] *= inParam->window[i];
    }
    int xn_size[2] = {1, inParam->N};
    float Xk[64];
    Forward_FFT(inParam->fftbuffer, xn_size, Xk);

    for(int i = 0; i < 64; i++){
        inParam->XindB[i] = 10*log10(pow(Xk[i],2))+92.62;// + dBSPL;
        // if (inParam->XindB[i] < 0) {
        //     inParam->XindB[i] = 0;
        // }
    }

    for(int i = 0; i < 32; i++){
        adrostr->XdBSPL_BinFreqs[i] = inParam->XindB[i];
    }
    adroMain(adrostr);
    

    float Filter[64];

    // Downsample the audio
//    processFIRFilter(inParam->downsampleFilter, inParam->input, inParam->downsampled);
//    for (i = 0, j = 0; i < inParam->decimatedStepSize; i++, j+= DECIMATION_FACTOR) {
//        inParam->decimated[i] = inParam->downsampled[j];
//    }
    //float ADRO_gain[32];
    for(int i = 0; i < 32; i++){
        adrostr->ADRO_gain[i] = adrostr->Gains_BinFreqs[i] + adrostr->MOLGains_BinFreqs[i];
    }
    firGen(adrostr->ADRO_gain,Filter);
    processGainFIRFilter(inParam->gainApplyFilter,Filter,inParam->adroinputbuffer,inParam->adrooutputbuffer);

    //Interpolate the Audio
//    for (i = 0, j = 0; i < inParam->decimatedStepSize; i++, j+=DECIMATION_FACTOR) {
//        inParam->interpolated[j] = inParam->gainapplied[i];
//    }
//    processFIRFilter(inParam->interpolationFilter, inParam->interpolated, inParam->output);

    for (int i = 0; i < inParam->N; i++) {
        _out[i] = (inParam->adrooutputbuffer[i]);
    }

}

void destroyApplyGain(ADRO_Input** _ptr) {
    if (*_ptr != NULL) {
        
//        wiener_ADAPTIVE_NE_terminate();
//        DynamicRangeFiveBandCompression_terminate();
        
        if ((*_ptr)->adroinputbuffer != NULL){
            free((*_ptr)->adroinputbuffer);
            (*_ptr)->adroinputbuffer = NULL;
        }
        if ((*_ptr)->adrooutputbuffer != NULL){
            free((*_ptr)->adrooutputbuffer);
            (*_ptr)->adrooutputbuffer = NULL;
        }
        if ((*_ptr)->fftbuffer != NULL){
            free((*_ptr)->fftbuffer);
            (*_ptr)->fftbuffer = NULL;
        }
        if ((*_ptr)->XindB != NULL){
            free((*_ptr)->XindB);
            (*_ptr)->XindB = NULL;
        }

        
        destroyFIR(&(*_ptr)->gainApplyFilter);


        
        free(*_ptr);
        *_ptr = NULL;
    }
}

