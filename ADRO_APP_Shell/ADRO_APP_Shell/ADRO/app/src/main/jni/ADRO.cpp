#include <jni.h>
#include <string>
#include <android/log.h>
#include <OpenSource/SuperpoweredAndroidAudioIO.h>
#include <Superpowered.h>
#include <SuperpoweredAdvancedAudioPlayer.h>
#include <SuperpoweredSimple.h>
#include <SuperpoweredCPU.h>
#include <malloc.h>
#include "adro_Main.h"

#include "SpeechProcessing.h"
#include <SLES/OpenSLES_AndroidConfiguration.h>
#include <SLES/OpenSLES.h>

#define log_print __android_log_print

static SuperpoweredAndroidAudioIO *audioIO,*playerIO;
static Superpowered::AdvancedAudioPlayer *player;

ADRO_str adrostr;
ADRO_Input *inParam;
static float *left, *right, *playerOutput, *out;
int mode = 0;
int datastore = 0;
const char *filename;
std::chrono::duration<double> elapsed_seconds2;
vector<float> frametimebuffer(125);
// This is called periodically by the audio engine.
static bool audioProcessing (
        void * __unused clientdata, // custom pointer
        short int *audio,           // output buffer
        int numberOfFrames,         // number of frames to process
        int samplerate              // current sample rate in Hz
) {
    auto start = std::chrono::steady_clock::now();
    Superpowered::ShortIntToFloat(audio, playerOutput, (unsigned int)numberOfFrames);
    Superpowered::DeInterleave(playerOutput,left,right,(unsigned int)numberOfFrames);

    doApplyGain(inParam, &adrostr, left, out);
    Superpowered::Interleave(out,out,playerOutput, (unsigned int)numberOfFrames);
    Superpowered::FloatToShortInt(playerOutput, audio, (unsigned int)numberOfFrames);
    auto end2 = std::chrono::steady_clock::now();
    elapsed_seconds2 = end2-start;
    for(int i = 0;i<124;i++){
        frametimebuffer[i] = frametimebuffer[i+1];
    }
    frametimebuffer[124] = float(elapsed_seconds2.count());
    return true;

}

static bool playerProcessing (
        void * __unused clientdata, // custom pointer
        short int *audio,           // output buffer
        int numberOfFrames,         // number of frames to process
        int samplerate              // current sample rate in Hz
) {
    auto start = std::chrono::steady_clock::now();
    player->outputSamplerate = (unsigned int)samplerate;
    float player_Output[numberOfFrames * 2];
    if (player->processStereo(player_Output, false, (unsigned int)numberOfFrames)) {
        Superpowered::DeInterleave(player_Output,left,right,(unsigned int)numberOfFrames);
        doApplyGain(inParam, &adrostr, left, out);
        Superpowered::Interleave(out,out,player_Output, (unsigned int)numberOfFrames);
        Superpowered::FloatToShortInt(player_Output, audio, (unsigned int)numberOfFrames);
        auto end2 = std::chrono::steady_clock::now();
        elapsed_seconds2 = end2-start;
        for(int i = 0;i<124;i++){
            frametimebuffer[i] = frametimebuffer[i+1];
        }
        frametimebuffer[124] = float(elapsed_seconds2.count());
        return true;
    } else return false;

}

// StartAudio - Start audio engine and initialize player.
extern "C" JNIEXPORT void
Java_utdallas_edu_adro_NativeFunction_NativeInit(JNIEnv *env, jclass obj, jint samplerate, jint buffersize) {
    Superpowered::Initialize("ExampleLicenseKey-WillExpire-OnNextUpdate");

    //ADRO parameter init

    adrostr_init(adrostr);
    inParam = initADRO_Input(buffersize);
    right = (float *)malloc(buffersize * sizeof(float) + 128);
    left = (float *)malloc(buffersize * sizeof(float) + 128);
    playerOutput = (float *)malloc(buffersize * sizeof(float) * 2 + 128);
    out = (float *)malloc(buffersize * sizeof(float) );


    mode = 1;
    audioIO = new SuperpoweredAndroidAudioIO (
            samplerate,                     // device native sampling rate
            buffersize,                     // device native buffer size
            true,                          // enableInput
            true,                           // enableOutput
            audioProcessing,                // process callback function
            NULL                        // clientData

    );
}

// StartAudio - Start audio engine and initialize player.
extern "C" void
Java_utdallas_edu_adro_NativeFunction_NativePlayerInit(JNIEnv *env, jclass obj, jint samplerate, jint buffersize) {
    Superpowered::Initialize("ExampleLicenseKey-WillExpire-OnNextUpdate");

    //ADRO parameter init

    adrostr_init(adrostr);
    inParam = initADRO_Input(buffersize);
    right = (float *)malloc(buffersize * sizeof(float) + 128);
    left = (float *)malloc(buffersize * sizeof(float) + 128);
    playerOutput = (float *)malloc(buffersize * sizeof(float) * 2 + 128);
    out = (float *)malloc(buffersize * sizeof(float) );

    mode = 0;
    player = new Superpowered::AdvancedAudioPlayer((unsigned int)samplerate, 0);
    playerIO = new SuperpoweredAndroidAudioIO (
            samplerate,                     // device native sampling rate
            buffersize,                     // device native buffer size
            false,                          // enableInput
            true,                           // enableOutput
            playerProcessing,                // process callback function
            NULL,                        // clientData
            -1,                             // inputStreamType (-1 = default)
            SL_ANDROID_STREAM_MEDIA

    );
}

// OpenFile - Open file in player, specifying offset and length.
extern "C" JNIEXPORT void
Java_utdallas_edu_adro_NativeFunction_OpenFile (
        JNIEnv *env,
        jclass obj,
        jstring path       // path to APK file

) {
    const char *str = env->GetStringUTFChars(path, 0);
    player->open(str);
    player->play();
    env->ReleaseStringUTFChars(path, str);


    // open file from any path: player->open("file system path to file");
    // open file from network (progressive download): player->open("http://example.com/music.mp3");
    // open HLS stream: player->openHLS("http://example.com/stream");
}

extern "C" JNIEXPORT jboolean
Java_utdallas_edu_adro_NativeFunction_isplaying(JNIEnv * __unused env, jclass obj) {
    if(player == NULL){
        return true;
    }else{
        return (jboolean)player->isPlaying();
    }
}




// onBackground - Put audio processing to sleep if no audio is playing.
extern "C" JNIEXPORT void
Java_utdallas_edu_adro_NativeFunction_onBackground(JNIEnv * __unused env, jclass obj) {
    audioIO->onBackground();
}

// onForeground - Resume audio processing.
extern "C" JNIEXPORT void
Java_utdallas_edu_adro_NativeFunction_onForeground(JNIEnv * __unused env, jclass obj) {
    audioIO->onForeground();
}

// Cleanup - Free resources.
extern "C" JNIEXPORT void
Java_utdallas_edu_adro_NativeFunction_Cleanup(JNIEnv * __unused env, jclass obj) {
    if(mode){
        delete audioIO;
    }else{
        delete playerIO;
        delete player;
    }



    destroyApplyGain(&inParam);
    free(playerOutput);
    free(left);
    free(out);
    free(right);

}

extern "C" JNIEXPORT jfloatArray
Java_utdallas_edu_adro_NativeFunction_getHighPercentile (JNIEnv *env, jclass obj){
    jfloatArray HighPercentile = (*env).NewFloatArray(10);
    float Best[10];
    Best[0] = adrostr.HighPercentiles_BinFreqs[0];
    Best[1] = adrostr.HighPercentiles_BinFreqs[1];
    Best[2] = adrostr.HighPercentiles_BinFreqs[2];
    Best[3] = adrostr.HighPercentiles_BinFreqs[3];
    Best[4] = adrostr.HighPercentiles_BinFreqs[5];
    Best[5] = adrostr.HighPercentiles_BinFreqs[6];
    Best[6] = adrostr.HighPercentiles_BinFreqs[8];
    Best[7] = adrostr.HighPercentiles_BinFreqs[12];
    Best[8] = adrostr.HighPercentiles_BinFreqs[16];
    Best[9] = adrostr.HighPercentiles_BinFreqs[24];

    (*env).SetFloatArrayRegion(HighPercentile, 0, 10,Best);
    return HighPercentile;
}

extern "C" JNIEXPORT jfloatArray
Java_utdallas_edu_adro_NativeFunction_getMidPercentile (JNIEnv *env, jclass obj){
    jfloatArray MidPercentile = (*env).NewFloatArray(10);
    float Best[10];
    Best[0] = adrostr.MidPercentiles_BinFreqs[0];
    Best[1] = adrostr.MidPercentiles_BinFreqs[1];
    Best[2] = adrostr.MidPercentiles_BinFreqs[2];
    Best[3] = adrostr.MidPercentiles_BinFreqs[3];
    Best[4] = adrostr.MidPercentiles_BinFreqs[5];
    Best[5] = adrostr.MidPercentiles_BinFreqs[6];
    Best[6] = adrostr.MidPercentiles_BinFreqs[8];
    Best[7] = adrostr.MidPercentiles_BinFreqs[12];
    Best[8] = adrostr.MidPercentiles_BinFreqs[16];
    Best[9] = adrostr.MidPercentiles_BinFreqs[24];

    (*env).SetFloatArrayRegion(MidPercentile, 0, 10,Best);
    return MidPercentile;
}
extern "C" JNIEXPORT void
Java_utdallas_edu_adro_NativeFunction_EnableADRO(JNIEnv * __unused env, jclass obj, jint onoff) {
    unsigned int fixedgain = onoff;
    if(!fixedgain){
        adrostr.FixedGainEnabled = 0;
    }else{
        adrostr.FixedGainEnabled = 1;
    }
}
float average(std::vector<float> v) {
    float sum = 0;
    for (int i = 0; i < v.size(); i++) {
        sum += v[i];
    }
    return sum / v.size();
}

extern "C" JNIEXPORT jfloatArray
Java_utdallas_edu_adro_NativeFunction_EuDistance (JNIEnv *env, jclass obj){
    jfloatArray EuD = (*env).NewFloatArray(2);
    float HighD = average(adrostr.D1buffer);
    float MidD = average(adrostr.D2buffer);

    float EuDistance[2] = {HighD,MidD};
    (*env).SetFloatArrayRegion(EuD, 0, 2,EuDistance );
    return EuD;
}

extern "C" JNIEXPORT jfloatArray
Java_utdallas_edu_adro_NativeFunction_ADROGain (JNIEnv *env, jclass obj){
    jfloatArray adroG = (*env).NewFloatArray(32);


    float adroGain[32];

    for(int i = 0; i < 32; i++){
        adroGain[i] = adrostr.ADRO_gain[i];
    }
    (*env).SetFloatArrayRegion(adroG, 0, 32,adroGain );
    return adroG;
}

extern "C" JNIEXPORT void
Java_utdallas_edu_adro_NativeFunction_EnableDataStore(JNIEnv * __unused env, jclass obj, jint onoff) {
    datastore = onoff;
}

extern "C" JNIEXPORT jboolean
Java_utdallas_edu_adro_NativeFunction_getEnableData(JNIEnv * __unused env, jclass obj) {
    return datastore==1?true:false;
}

extern "C" JNIEXPORT void
Java_utdallas_edu_adro_NativeFunction_setDataName (
        JNIEnv *env,
        jclass __unused obj,
        jstring fileName
) {
    filename = (*env).GetStringUTFChars(fileName,JNI_FALSE);
}
extern "C" JNIEXPORT jstring
Java_utdallas_edu_adro_NativeFunction_getDataName (
        JNIEnv *env,
        jclass __unused obj
) {
    jstring result;
    result = (*env).NewStringUTF(filename);
    return result;
}
extern "C" JNIEXPORT jfloat
Java_utdallas_edu_adro_NativeFunction_getframetime(JNIEnv * __unused env, jclass __unused obj) {
    float averageframetime = average(frametimebuffer);
    return averageframetime;
}