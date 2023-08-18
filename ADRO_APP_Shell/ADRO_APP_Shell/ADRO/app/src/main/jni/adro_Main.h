//
// Created by nelson on 1/28/2023.
//

#ifndef ADRO_ADRO_MAIN_H
#define ADRO_ADRO_MAIN_H

#include <vector>
#include <algorithm>


extern "C" {
#include "FIRFilter.h"
}

using namespace std;
const float HanningW[] = {0,	0.0490676743274178,	0.0980171403295607,	0.146730474455362,	0.195090322016128,	0.242980179903264,	0.290284677254462,	0.336889853392220,	0.382683432365090,	0.427555093430282,	0.471396736825998,	0.514102744193222,	0.555570233019602,	0.595699304492433,	0.634393284163646,	0.671558954847018,	0.707106781186548,	0.740951125354959,	0.773010453362737,	0.803207531480645,	0.831469612302545,	0.857728610000272,	0.881921264348355,	0.903989293123443,	0.923879532511287,	0.941544065183021,	0.956940335732209,	0.970031253194544,	0.980785280403230,	0.989176509964781,	0.995184726672197,	0.998795456205172,	1,	0.998795456205172,	0.995184726672197,	0.989176509964781,	0.980785280403230,	0.970031253194544,	0.956940335732209,	0.941544065183021,	0.923879532511287,	0.903989293123443,	0.881921264348355,	0.857728610000272,	0.831469612302545,	0.803207531480645,	0.773010453362737,	0.740951125354959,	0.707106781186548,	0.671558954847018,	0.634393284163646,	0.595699304492433,	0.555570233019602,	0.514102744193222,	0.471396736825998,	0.427555093430282,	0.382683432365090,	0.336889853392220,	0.290284677254462,	0.242980179903264,	0.195090322016128,	0.146730474455362,	0.0980171403295607,	0.0490676743274178};
const float dBSPL = 100.8986;
struct ADRO_str{
    int bins_N;
    float Fs;
    float UpdateRate;

    int FixedGainEnabled = 0;
    int DisableMOLs = 0;
    int MinimumGainEnabled = 0;
    int LoudDetectEnabled = 0;
    int GainDriftEnabled = 0;
    int AdaptiveSlewRatesEnabled = 0;

    vector<float> ComfortTargets_AudFreqs;
    vector<float> AudibilityTargets_AudFreqs;
    vector<float> MOLs_AudFreqs;
    vector<float> MaxGains_AudFreqs;
    vector<float> MinGains_AudFreqs;


    float NormalGainSlewRateUp;
    float NormalGainSlewRateDown;
    int LoudDetectThreshold;
    int LoudDetectBinCounter;
    float GainDriftUpSlewRate;

    vector<float> ComfortTargets_BinFreqs;
    vector<float> AudibilityTargets_BinFreqs;
    vector<float> MOLs_BinFreqs;
    vector<float> MaxGains_BinFreqs;
    vector<float> MinGains_BinFreqs;

    float HighPercentile;
    float MidPercentile;
    float HighPercentileSlewRate;
    float MidPercentileSlewRate;

    float HighPercentileUpStep;
    float HighPercentileDownStep;
    float MidPercentileUpStep;
    float MidPercentileDownStep;

    vector<float> HighPercentiles_BinFreqs;
    vector<float> MidPercentiles_BinFreqs;
    vector<float> MOLAttackStep;
    vector<float> MOLReleaseStep;
    vector<float> MOLGains_BinFreqs;

    vector<float> Gains_BinFreqs;

    vector<float> XdBSPL_BinFreqs;
    vector<float> YdBSPL_BinFreqs;

    int BinsToProcessPerFrame;
    int FirstBinToProcess;

    vector<float> D1buffer;
    vector<float> D2buffer;
    float ADRO_gain[32];

};

struct ADRO_Input {
    int N;
    float* adroinputbuffer;
    float* adrooutputbuffer;
    float* fftbuffer;
    float* XindB;
    float* window;
    FIR* gainApplyFilter;

};
void adrostr_init(ADRO_str& adroStr);
ADRO_Input* initADRO_Input(int frameSize);
void adroMain(ADRO_str* adrostr);
vector<float> interp1(vector<float> AudFreqs);
#endif //ADRO_ADRO_MAIN_H
