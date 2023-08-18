//
// Created by nelson on 1/28/2023.
#include "adro_Main.h"
#include <jni.h>

//ADRO Global param
int NFFT_bins = 32;
int framesize = 32;
int Fs = 16000;
int Use_All_FIR_taps = 1;
vector<float> Comfort_Target{35, 35, 35, 35, 35, 52.5, 70, 53.5, 37, 37};
vector<float> Audibility_Target{20, 20, 15, 15, 15, 15, 15, 25, 25, 40};
vector<float> MOLs_AudFreqs{95, 95, 95, 95, 95, 95, 95, 95 ,95, 95};
vector<float> MaxGains_AudFreqs{50, 50, 50, 50, 50, 50, 50, 50, 50, 50};
vector<float> MinGains_AudFreqs{-100, -100, -100, -100, -100, -100, -100, -100, -100, -100};
vector<float> Calibration_Adjustments(32);

int NFFT = 64;
int DF = 250;
int NCH = 33;
float OLAP = 0.5;
int NCHUNK = 32;
int DOFFT = 1;
vector<int> BOI{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
int FFTRATE = 32;


int N_FIR_taps = 64;
vector<float> firbufL(64);
vector<float> signal_path_FIR_taps_new(64);
vector<float> signal_path_FIR_taps_old(64);

float processDistance(vector<float> a, vector<float> b){
    float HighD =0;

    const int index[10] = {0,1,2,3,4,5,8,12,16,24};
    for(int i = 0; i<10;i++){
        HighD += pow(a[index[i]]-b[index[i]],2);

    }
    HighD = sqrt(HighD);
    return HighD;
}


void adrostr_init(ADRO_str& adroStr){
    adroStr.bins_N = 32;
    adroStr.Fs = 16000;
    adroStr.UpdateRate = 125;
    adroStr.FixedGainEnabled = 1;
    adroStr.DisableMOLs = 0;
    adroStr.MinimumGainEnabled = 0;
    adroStr.LoudDetectEnabled = 0;
    adroStr.GainDriftEnabled = 0;
    adroStr.AdaptiveSlewRatesEnabled = 0;
    vector<float> temp{Comfort_Target[0],Comfort_Target[0],Comfort_Target[1],Comfort_Target[2],Comfort_Target[3],Comfort_Target[4],Comfort_Target[5],Comfort_Target[6],Comfort_Target[7],Comfort_Target[8],Comfort_Target[9],Comfort_Target[9]};
    adroStr.ComfortTargets_AudFreqs = temp;
    adroStr.AudibilityTargets_AudFreqs = {Audibility_Target[0],Audibility_Target[0],Audibility_Target[1],Audibility_Target[2],Audibility_Target[3],Audibility_Target[4],Audibility_Target[5],Audibility_Target[6],Audibility_Target[7],Audibility_Target[8],Audibility_Target[9],Audibility_Target[9]};
    adroStr.MOLs_AudFreqs = {MOLs_AudFreqs[0],MOLs_AudFreqs[0],MOLs_AudFreqs[1],MOLs_AudFreqs[2],MOLs_AudFreqs[3],MOLs_AudFreqs[4],MOLs_AudFreqs[5],MOLs_AudFreqs[6],MOLs_AudFreqs[7],MOLs_AudFreqs[8],MOLs_AudFreqs[9],MOLs_AudFreqs[9]};
    adroStr.MaxGains_AudFreqs = {MaxGains_AudFreqs[0],MaxGains_AudFreqs[0],MaxGains_AudFreqs[1],MaxGains_AudFreqs[2],MaxGains_AudFreqs[3],MaxGains_AudFreqs[4],MaxGains_AudFreqs[5],MaxGains_AudFreqs[6],MaxGains_AudFreqs[7],MaxGains_AudFreqs[8],MaxGains_AudFreqs[9],MaxGains_AudFreqs[9]};
    adroStr.MinGains_AudFreqs = {MinGains_AudFreqs[0],MinGains_AudFreqs[0],MinGains_AudFreqs[1],MinGains_AudFreqs[2],MinGains_AudFreqs[3],MinGains_AudFreqs[4],MinGains_AudFreqs[5],MinGains_AudFreqs[6],MinGains_AudFreqs[7],MinGains_AudFreqs[8],MinGains_AudFreqs[9],MinGains_AudFreqs[9]};

    adroStr.NormalGainSlewRateUp = 0.048;
    adroStr.NormalGainSlewRateDown = 0.048;
    adroStr.LoudDetectThreshold = 8;
    adroStr.GainDriftUpSlewRate = 0;

    adroStr.ComfortTargets_BinFreqs = interp1(adroStr.ComfortTargets_AudFreqs);
    transform(adroStr.ComfortTargets_BinFreqs.begin(),adroStr.ComfortTargets_BinFreqs.end(), Calibration_Adjustments.begin(), adroStr.ComfortTargets_BinFreqs.begin(), plus<float>());

    adroStr.AudibilityTargets_BinFreqs = interp1(adroStr.AudibilityTargets_AudFreqs);
    transform(adroStr.AudibilityTargets_BinFreqs.begin(), adroStr.AudibilityTargets_BinFreqs.end(), Calibration_Adjustments.begin(), adroStr.AudibilityTargets_BinFreqs.begin(), plus<float>());

    adroStr.MOLs_BinFreqs = interp1(adroStr.MOLs_AudFreqs);
    transform(adroStr.MOLs_BinFreqs.begin(), adroStr.MOLs_BinFreqs.end(), Calibration_Adjustments.begin(), adroStr.MOLs_BinFreqs.begin(), plus<float>());

    adroStr.MaxGains_BinFreqs = interp1(adroStr.MaxGains_AudFreqs);
    adroStr.MinGains_BinFreqs = interp1(adroStr.MinGains_AudFreqs);

    adroStr.HighPercentile = 90;
    adroStr.MidPercentile = 30;
    adroStr.HighPercentileSlewRate = 20;
    adroStr.MidPercentileSlewRate = 20;

    adroStr.HighPercentileUpStep = adroStr.HighPercentileSlewRate * (100 / (100 - adroStr.HighPercentile)) / adroStr.UpdateRate;
    adroStr.HighPercentileDownStep = adroStr.HighPercentileSlewRate * (100 / adroStr.HighPercentile) / adroStr.UpdateRate;

    adroStr.MidPercentileUpStep = adroStr.MidPercentileSlewRate * (100 / (100 - adroStr.MidPercentile)) / adroStr.UpdateRate;
    adroStr.MidPercentileDownStep = adroStr.MidPercentileSlewRate * (100 / adroStr.MidPercentile) / adroStr.UpdateRate;

    adroStr.HighPercentiles_BinFreqs = adroStr.ComfortTargets_BinFreqs;
    adroStr.MidPercentiles_BinFreqs = adroStr.AudibilityTargets_BinFreqs;

    vector<float> ones(adroStr.bins_N,1);
    vector<float> zeros(adroStr.bins_N);

    float x=( 1 * (adroStr.bins_N/32)*(16000/Fs) );
    float y=( 0.3 * (adroStr.bins_N/32)*(16000/Fs) );

    adroStr.MOLAttackStep = vector<float>(32,x);


    adroStr.MOLAttackStep[0] = ( 3 * (adroStr.bins_N/32)*(16000/Fs) );
    adroStr.MOLReleaseStep = vector<float>(32,y);
    adroStr.MOLReleaseStep[0] = ( 0.15 * (adroStr.bins_N/32)*(16000/Fs) );
    adroStr.MOLGains_BinFreqs = zeros;

    adroStr.Gains_BinFreqs = zeros;
    for(int i = 0; i < 32; i++) {
        adroStr.Gains_BinFreqs[i] = adroStr.MaxGains_BinFreqs[i] - 10;
    }


    adroStr.XdBSPL_BinFreqs = zeros;
    adroStr.YdBSPL_BinFreqs = zeros;
    adroStr.BinsToProcessPerFrame = 31;
    adroStr.FirstBinToProcess = 0;

    adroStr.D1buffer = vector<float>(125);
    adroStr.D2buffer = vector<float>(125);
    for(int i = 0; i < 32; i++){
        adroStr.ADRO_gain[i] = adroStr.Gains_BinFreqs[i] + adroStr.MOLGains_BinFreqs[i];
    }
}




ADRO_Input* initADRO_Input(int frameSize) {
    ADRO_Input* inParam = (ADRO_Input*)malloc(sizeof(ADRO_Input));
    inParam->N = frameSize;
    inParam->adroinputbuffer = (float*)calloc(frameSize, sizeof(float));
    inParam->adrooutputbuffer = (float*)calloc(frameSize, sizeof(float));
    inParam->fftbuffer = (float*)calloc(2*frameSize, sizeof(float));
    inParam->XindB = (float*)calloc(frameSize, sizeof(float));
    inParam->gainApplyFilter = initFIR(frameSize);
    inParam->window = (float*)calloc(2*frameSize, sizeof(float));
    for(int i = 0; i<2*frameSize; i++){
        inParam->window[i] = (float)sqrt(((1.0-cos(2.0*M_PI*(i)/(2*frameSize-1)))*0.5));
    }
    //inParam->fft = newTransform(2*frameSize, 64);
    return inParam;
}

void adroMain(ADRO_str* adrostr){
    adrostr->LoudDetectBinCounter = 0;


    for (int i = 0; i < 32; i++){
        adrostr->YdBSPL_BinFreqs[i] = adrostr->XdBSPL_BinFreqs[i] + adrostr->Gains_BinFreqs[i];
    }
    //If disable MOL is not set, apply MOLs to output levels in bins.
    float MOLGainDiff, TCstep;
    if (adrostr->DisableMOLs == 0) {
        for(int i = 0; i < adrostr->bins_N; i++){
            MOLGainDiff = (adrostr->MOLs_BinFreqs[i] - adrostr->YdBSPL_BinFreqs[i]) - adrostr->MOLGains_BinFreqs[i];
            if(MOLGainDiff > 0){
                TCstep = adrostr->MOLReleaseStep[i];
            } else {
                TCstep = adrostr->MOLAttackStep[i];
            }
            if(MOLGainDiff > 6.02) {
                MOLGainDiff = 6.02;
            } else if(MOLGainDiff < -6.02) {
                MOLGainDiff = -6.02;
            }
            adrostr->MOLGains_BinFreqs[i] = (6.02*128) * ( (adrostr->MOLGains_BinFreqs[i]/(6.02*128)) + ((TCstep/(6.02*128))*(128*MOLGainDiff/(6.02*128))) );
            if (adrostr->MOLGains_BinFreqs[i] > 0){
                adrostr->MOLGains_BinFreqs[i] = 0;
            }
            if (adrostr->MOLGains_BinFreqs[i] < -1){
                adrostr->LoudDetectBinCounter = adrostr->LoudDetectBinCounter + 1;
            }
        }

        float delta_MOL = 6.02;
        for(int i = 0; i < adrostr->bins_N-1; i++) {
            if(adrostr->MOLGains_BinFreqs[i+1] > adrostr->MOLGains_BinFreqs[i] + delta_MOL){
                adrostr->MOLGains_BinFreqs[i+1] = adrostr->MOLGains_BinFreqs[i] + delta_MOL;
            }
        }
        for(int i = adrostr->bins_N-1; i>=0; i--) {
            if(adrostr->MOLGains_BinFreqs[i] > adrostr->MOLGains_BinFreqs[i+1] + delta_MOL){
                adrostr->MOLGains_BinFreqs[i] = adrostr->MOLGains_BinFreqs[i+1] + delta_MOL;
            }
        }
    }

    //Update percentiles for a sub-set of bins 
    for (int i = adrostr->FirstBinToProcess; i <= adrostr->FirstBinToProcess + adrostr->BinsToProcessPerFrame; i++)
    {
        // Add the smoothed MOL gain to the previously calculated output levels.
        // The result is the output level presented to the device user.
        adrostr->YdBSPL_BinFreqs[i] += adrostr->MOLGains_BinFreqs[i];

        // Please Complete this Percentile Update Module
        // Update high percentile (can do before or after mid percentile):


        if (adrostr->HighPercentiles_BinFreqs[i] - adrostr->HighPercentileDownStep > adrostr->YdBSPL_BinFreqs[i])
        {
            adrostr->HighPercentiles_BinFreqs[i] = adrostr->HighPercentiles_BinFreqs[i] - adrostr->HighPercentileDownStep;
        }
        else {
        adrostr->HighPercentiles_BinFreqs[i] = adrostr->HighPercentiles_BinFreqs[i] + adrostr->HighPercentileUpStep;
            if (adrostr->HighPercentiles_BinFreqs[i] > adrostr->YdBSPL_BinFreqs[i])
            {
                adrostr->HighPercentiles_BinFreqs[i] = adrostr->YdBSPL_BinFreqs[i];
            }
        }



        // Update mid percentile (in exactly same way as high percentile):
        if (adrostr->MidPercentiles_BinFreqs[i] - adrostr->MidPercentileDownStep > adrostr->YdBSPL_BinFreqs[i])
        {
        adrostr->MidPercentiles_BinFreqs[i] = adrostr->MidPercentiles_BinFreqs[i] - adrostr->MidPercentileDownStep;
        }
        else {
        adrostr->MidPercentiles_BinFreqs[i] = adrostr->MidPercentiles_BinFreqs[i] + adrostr->MidPercentileUpStep;
            if (adrostr->MidPercentiles_BinFreqs[i] > adrostr->YdBSPL_BinFreqs[i])
            {
            adrostr->MidPercentiles_BinFreqs[i] = adrostr->YdBSPL_BinFreqs[i];
            }
        }
    }


    // If NOT in fixed gain mode, update gains in bins.
    if (adrostr->FixedGainEnabled == 0) {

        // Set gain slews to normal values (by default)
        float GainUpSlew = adrostr->NormalGainSlewRateUp;
        float GainDownSlew = adrostr->NormalGainSlewRateDown;
        float GainDriftUpSlew = adrostr->GainDriftUpSlewRate;

        // If loud detect enabled and triggered, divide ALL gain slews by 8 (as
        // hardcoded in Wolverine - configurable in Ezairo but not here for simplicity)
        if (adrostr->LoudDetectEnabled != 0) {
            if (adrostr->LoudDetectBinCounter >= adrostr->LoudDetectThreshold) {
                GainUpSlew = GainUpSlew / 8;
                GainDownSlew = GainDownSlew / 8;
                GainDriftUpSlew = GainDriftUpSlew / 8;
            }
        }

        // Please Complete this Gain Update Module
        // Update gain for a sub-set of bins
        //Loop over a range of bins to process in an audio signal
        for (int i = adrostr->FirstBinToProcess; i <= adrostr->FirstBinToProcess + adrostr->BinsToProcessPerFrame; i++)
        {
            // Checking if the frequency of the current bin exceeds the comfort target, decrease the gain for that bin
            if (adrostr->HighPercentiles_BinFreqs[i] > adrostr->ComfortTargets_BinFreqs[i])
            {
                adrostr->Gains_BinFreqs[i] -= GainDownSlew;
            }
            // Checking if 30th percentile < audibility target
            else if (adrostr->MidPercentiles_BinFreqs[i] < adrostr->AudibilityTargets_BinFreqs[i])
            {
                adrostr->Gains_BinFreqs[i] += GainUpSlew;
            }
            // Else increase gain by the gain drift slew rate
            else {
                adrostr->Gains_BinFreqs[i] += GainDriftUpSlew;
            }

            // Checking if gain exceeds maximum gain, set it to the maximum gain
            if (adrostr->Gains_BinFreqs[i] > adrostr->MaxGains_BinFreqs[i])
            {
                adrostr->Gains_BinFreqs[i] = adrostr->MaxGains_BinFreqs[i];
            }
            // Checking if minimum gains enabled and gain is less than minimum gain, set it to the minimum gain
            if ((adrostr->FixedGainEnabled == adrostr->MinGains_BinFreqs[i]) && (adrostr->Gains_BinFreqs[i] < adrostr->MinGains_BinFreqs[i]))
            {
                adrostr->Gains_BinFreqs[i] = adrostr->MinGains_BinFreqs[i];
            }

        }
        
    }
    else{
        adrostr->Gains_BinFreqs = vector<float>(adrostr->bins_N);
    }

    //Update Euclidean Distance
    float D1 = processDistance(adrostr->ComfortTargets_BinFreqs, adrostr->HighPercentiles_BinFreqs);
    float D2 = processDistance(adrostr->AudibilityTargets_BinFreqs, adrostr->MidPercentiles_BinFreqs);
    for(int i = 0;i<124;i++){
        adrostr->D1buffer[i] = adrostr->D1buffer[i+1];
        adrostr->D2buffer[i] = adrostr->D2buffer[i+1];
    }
    adrostr->D1buffer[124] = D1;
    adrostr->D2buffer[124] = D2;

    if (adrostr->FirstBinToProcess > adrostr->bins_N){
        adrostr->FirstBinToProcess = 0;
    }


}

vector<float> interp1(vector<float> AudFreqs){
    vector<float> BinFreqs(32);
    BinFreqs[0] = AudFreqs[1];
    BinFreqs[1] = AudFreqs[2];
    BinFreqs[2] = AudFreqs[3];
    BinFreqs[3] = AudFreqs[4];
    BinFreqs[4] = AudFreqs[5];
    BinFreqs[5] = (AudFreqs[5]+AudFreqs[6])/2;
    BinFreqs[6] = AudFreqs[6];
    BinFreqs[7] = AudFreqs[6] + (AudFreqs[7]-AudFreqs[6])/2;
    BinFreqs[8] = AudFreqs[7];
    BinFreqs[9] = AudFreqs[7] + (AudFreqs[8]-AudFreqs[7])/4;
    BinFreqs[10] = AudFreqs[7] + 2*(AudFreqs[8]-AudFreqs[7])/4;
    BinFreqs[11] =AudFreqs[7] + 3*(AudFreqs[8]-AudFreqs[7])/4;
    BinFreqs[12] = AudFreqs[8];
    BinFreqs[13] = AudFreqs[8] + (AudFreqs[9]-AudFreqs[8])/4;
    BinFreqs[14] = AudFreqs[8] + 2*(AudFreqs[9]-AudFreqs[8])/4;
    BinFreqs[15] = AudFreqs[8] + 3*(AudFreqs[9]-AudFreqs[8])/4;
    BinFreqs[16] = AudFreqs[9];
    BinFreqs[17] = AudFreqs[9] + (AudFreqs[10]-AudFreqs[9])/8;
    BinFreqs[18] = AudFreqs[9] + 2*(AudFreqs[10]-AudFreqs[9])/8;
    BinFreqs[19] = AudFreqs[9] + 3*(AudFreqs[10]-AudFreqs[9])/8;
    BinFreqs[20] = AudFreqs[9] + 4*(AudFreqs[10]-AudFreqs[9])/8;
    BinFreqs[21] = AudFreqs[9] + 5*(AudFreqs[10]-AudFreqs[9])/8;
    BinFreqs[22] = AudFreqs[9] + 6*(AudFreqs[10]-AudFreqs[9])/8;
    BinFreqs[23] = AudFreqs[9] + 7*(AudFreqs[10]-AudFreqs[9])/8;
    BinFreqs[24] = AudFreqs[10];
    BinFreqs[25] = AudFreqs[10] + (AudFreqs[11]-AudFreqs[10])/7;
    BinFreqs[26] = AudFreqs[10] + 2*(AudFreqs[11]-AudFreqs[10])/7;
    BinFreqs[27] = AudFreqs[10] + 3*(AudFreqs[11]-AudFreqs[10])/7;
    BinFreqs[28] = AudFreqs[10] + 4*(AudFreqs[11]-AudFreqs[10])/7;
    BinFreqs[29] = AudFreqs[10] + 5*(AudFreqs[11]-AudFreqs[10])/7;
    BinFreqs[30] = AudFreqs[10] + 6*(AudFreqs[11]-AudFreqs[10])/7;
    BinFreqs[31] = AudFreqs[11];
    return BinFreqs;
}

extern "C" void
Java_utdallas_edu_adro_NativeFunction_setPreset (JNIEnv *env, jclass obj, jfloatArray presetarray){
    float *_InitialG = (*env).GetFloatArrayElements(presetarray,NULL);
    Audibility_Target[0] = _InitialG[0];
    Comfort_Target[0] = _InitialG[9];
    for (int i=1;i<10;++i){
        Audibility_Target[i] = _InitialG[i-1];
        Comfort_Target[i] = _InitialG[i+8];
    }
}

extern "C" JNIEXPORT jfloatArray
Java_utdallas_edu_adro_NativeFunction_getAudiogram (JNIEnv *env, jclass obj){
    jfloatArray AG = (*env).NewFloatArray(10);
    float Best[10];
    for(int i = 0;i<10;++i){
        Best[i] = Audibility_Target[i];
    }
    (*env).SetFloatArrayRegion(AG, 0, 10,Best);
    return AG;
}

extern "C" JNIEXPORT jfloatArray
Java_utdallas_edu_adro_NativeFunction_getComfortTarget (JNIEnv *env, jclass obj){
    jfloatArray CT = (*env).NewFloatArray(10);
    float Best[10];
    for(int i = 0;i<10;++i){
        Best[i] = Comfort_Target[i];
    }
    (*env).SetFloatArrayRegion(CT, 0, 10,Best);
    return CT;
}

extern "C" JNIEXPORT jfloatArray
Java_utdallas_edu_adro_NativeFunction_getMOL (JNIEnv *env, jclass obj){
    jfloatArray MOL = (*env).NewFloatArray(10);
    float Best[10];
    for(int i = 0;i<10;++i){
        Best[i] = MOLs_AudFreqs[i];
    }
    (*env).SetFloatArrayRegion(MOL, 0, 10,Best);
    return MOL;
}

