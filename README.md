# ADRO
The ADRO algorithm involves adjusting the dynamic range of audio signals based on the loudness level of an audio signal. By automatically adjusting the dynamic range of audio signals, ADRO attempts to make audio signals more clear and natural-sounding. 
The objective of this project is to develop a real-time smartphone app to enhance hearing perception by applying the Adaptive Dynamic Range Optimization (ADRO) algorithm. ADRO automatically adjusts the dynamic range of audio signals to provide a more consistent and optimal listening experience.

The ADRO algorithm involves adjusting the dynamic range of audio signals based on the loudness level of an audio signal. By automatically adjusting the dynamic range of audio signals, ADRO attempts to make audio signals more clear and natural-sounding. This is particularly useful in applications such as hearing aids, professional audio equipment, and home theater systems, where providing a better hearing experience or perception by listeners is of utmost importance.

<div align="center">

![image](https://github.com/mishra-raman/ADRO/assets/109490354/0b238169-08d2-4ff2-bd2d-2c2eeeb77272)  
  ADRO Module
</div>

In this project, the ADRO algorithm is implemented in a smartphone app in real-time. The app takes in an audio signal and applies the ADRO algorithm to adjust the dynamic range of the signal. The ADRO algorithm first decomposes the captured audio signal into a number of frequency bins or bands (in this project, 32 bins or bands). Next, the signal in each frequency band is amplified according to the gain values specified by a Gain Computation module. The Gain Computation module obtains estimates of SPL (sound pressure level) percentiles, such as high, mid, and low percentiles, and adjusts the gain values accordingly.

The Map module defines the audibility target, comfort target, and loudness discomfort level of a person. The audibility target denotes the minimum audible threshold level that a person can hear in each of the frequency bands. The comfort target denotes the level at which audio signals are most comfortably heard by a person. This level varies from person to person and from audio environment to audio environment. The loudness discomfort level denotes the sound level perceived to be uncomfortably loud by a person.

<div align="center">

![image](https://github.com/mishra-raman/ADRO/assets/109490354/98c666ce-f12f-4065-8b1a-600f355ead47)
  **Audiogram**
</div>

<div align="center">

![image](https://github.com/mishra-raman/ADRO/assets/109490354/78f5416b-b27e-4384-ac16-5c282633693d)  
  **Comfort Target**
</div>

The Maximum Power Output (MPO) parameter is used to limit the output level in each frequency band so that the signal power does not exceed a maximum value for audio safety reasons. The Max Gain (MG) parameter is used to limit a gain value when an update or adjustment is made.

The ADRO algorithm adjusts the gain values applied to the audio signal in each of the frequency bands according to the SPL percentiles and the Map module. The frequency band components are then combined in order to reconstruct the output audio signal while staying below the Maximum Power Output (MPO) level.

In this project, 32 frequency bins or bands (0Hz to 7750Hz with bandwidths of 250Hz) and two percentiles (90th and 30th) are considered. The following processing steps are carried out in ADRO:

Estimate output level for each frequency band from the current input audio signal level and the gain value applied to the last frame.
Compute the Maximum Output Level (MOL) gain for each band from the output level and the MOL time constants.
Detect "loud" bands where MOL gain is < -1 dB
Estimate 90th percentile and 30th percentile levels for selected bands.
Reduce slew rates if "loud" bin or band threshold is exceeded.
Update gain for selected bins or bands using ADRO rules.
The output of the smartphone app is a clearer and more natural-sounding audio signal, which can be particularly beneficial for people with hearing impairments. The app can be used on a daily basis to enhance the hearing experience of users.

Overall, the real-time implementation and evaluation of the ADRO algorithm for hearing enhancement is an important project that has the potential to make a significant impact on people's lives. By providing a clearer and more natural-sounding audio signal, the ADRO algorithm can improve the hearing experience of users and enhance their quality of life.
