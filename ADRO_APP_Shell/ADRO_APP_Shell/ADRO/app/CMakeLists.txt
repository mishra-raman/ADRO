cmake_minimum_required(VERSION 3.4.1)

# convert SDK path to forward slashes on Windows
file(TO_CMAKE_PATH ${PATH_TO_SUPERPOWERED} PATH_TO_SUPERPOWERED)

include_directories(src/main/jni)
include_directories(${PATH_TO_SUPERPOWERED})

# compile player example to a native library
add_library (
        ADRO
        SHARED
        src/main/jni/adro.cpp
        src/main/jni/adro_Main.cpp
        src/main/jni/adro_Main.h

        src/main/jni/FIRFilter.c
        src/main/jni/FIRFilter.h

        src/main/jni/SpeechProcessing.cpp
        src/main/jni/SpeechProcessing.h
        src/main/jni/tmwtypes.h

        src/main/jni/firGen/FFTImplementationCallback.c
        src/main/jni/firGen/FFTImplementationCallback.h
        src/main/jni/firGen/firGen.c
        src/main/jni/firGen/firGen.h
        src/main/jni/firGen/firGen_data.c
        src/main/jni/firGen/firGen_data.h
        src/main/jni/firGen/firGen_initialize.c
        src/main/jni/firGen/firGen_initialize.h
        src/main/jni/firGen/firGen_terminate.c
        src/main/jni/firGen/firGen_terminate.h
        src/main/jni/firGen/firGen_types.h

        src/main/jni/rt_nonfinite.c
        src/main/jni/rt_nonfinite.h
        src/main/jni/rtGetInf.c
        src/main/jni/rtGetInf.h
        src/main/jni/rtGetNaN.c
        src/main/jni/rtGetNaN.h
        src/main/jni/rtwtypes.h

        src/main/jni/FFT/Forward_FFT.c
        src/main/jni/FFT/Forward_FFT.h
        src/main/jni/FFT/Forward_FFT_data.c
        src/main/jni/FFT/Forward_FFT_data.h
        src/main/jni/FFT/Forward_FFT_initialize.c
        src/main/jni/FFT/Forward_FFT_initialize.h
        src/main/jni/FFT/Forward_FFT_terminate.c
        src/main/jni/FFT/Forward_FFT_terminate.h
        src/main/jni/FFT/Forward_FFT_types.h
        src/main/jni/FFT/ForwardFFTImplementationCallback.c
        src/main/jni/FFT/ForwardFFTImplementationCallback.h






        ${PATH_TO_SUPERPOWERED}/OpenSource/SuperpoweredAndroidAudioIO.cpp
)

# link the native library against the following libraries
target_link_libraries (
        ADRO
        log
        android
        OpenSLES
        ${PATH_TO_SUPERPOWERED}/libSuperpoweredAndroid${ANDROID_ABI}.a
)