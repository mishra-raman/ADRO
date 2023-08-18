/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: firGen.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 29-Jan-2023 15:27:25
 */

/* Include Files */
#include "firGen.h"
#include "FFTImplementationCallback.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static float rt_powf_snf(float u0, float u1);

/* Function Definitions */
/*
 * Arguments    : float u0
 *                float u1
 * Return Type  : float
 */
static float rt_powf_snf(float u0, float u1)
{
  float y;
  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
    y = rtNaNF;
  } else {
    float f;
    float f1;
    f = fabsf(u0);
    f1 = fabsf(u1);
    if (rtIsInfF(u1)) {
      if (f == 1.0F) {
        y = 1.0F;
      } else if (f > 1.0F) {
        if (u1 > 0.0F) {
          y = rtInfF;
        } else {
          y = 0.0F;
        }
      } else if (u1 > 0.0F) {
        y = 0.0F;
      } else {
        y = rtInfF;
      }
    } else if (f1 == 0.0F) {
      y = 1.0F;
    } else if (f1 == 1.0F) {
      if (u1 > 0.0F) {
        y = u0;
      } else {
        y = 1.0F / u0;
      }
    } else if (u1 == 2.0F) {
      y = u0 * u0;
    } else if ((u1 == 0.5F) && (u0 >= 0.0F)) {
      y = sqrtf(u0);
    } else if ((u0 < 0.0F) && (u1 > floorf(u1))) {
      y = rtNaNF;
    } else {
      y = powf(u0, u1);
    }
  }
  return y;
}

/*
 * Calculates minimum-phase FIR filter taps from a vector of dB gains
 *    Gk is column vector of 32 gains (DC to Nyquist-1).
 *    NumberOfTaps = number of taps to return (must be L or L/2)
 *
 * Arguments    : const float Gk[32]
 *                float FiltULD[64]
 * Return Type  : void
 */
void firGen(const float Gk[32], float FiltULD[64])
{
  static const float fv[64] = {
      0.999428213F, 1.9897244F,   1.97155106F,  1.94451725F,  1.90889132F,
      1.86502767F,  1.81336188F,  1.75440776F,  1.68875098F,  1.61704421F,
      1.54F,        1.45838416F,  1.37300777F,  1.28471923F,  1.19439626F,
      1.10293627F,  1.01124835F,  0.92024368F,  0.830826759F, 0.743886232F,
      0.660286188F, 0.580857456F, 0.50638938F,  0.43762213F,  0.375239104F,
      0.319860339F, 0.272036165F, 0.232241884F, 0.200873017F, 0.178241313F,
      0.164571688F, 0.16F,        0.08F,        0.0F,         0.0F,
      0.0F,         0.0F,         0.0F,         0.0F,         0.0F,
      0.0F,         0.0F,         0.0F,         0.0F,         0.0F,
      0.0F,         0.0F,         0.0F,         0.0F,         0.0F,
      0.0F,         0.0F,         0.0F,         0.0F,         0.0F,
      0.0F,         0.0F,         0.0F,         0.0F,         0.0F,
      0.0F,         0.0F,         0.0F,         0.0F};
  static const float b_sintab[33] = {
      0.0F,         0.0980171412F, 0.195090324F, 0.290284663F, 0.382683456F,
      0.471396744F, 0.555570245F,  0.634393334F, 0.707106769F, 0.773010433F,
      0.831469595F, 0.881921232F,  0.923879504F, 0.956940353F, 0.980785251F,
      0.99518472F,  1.0F,          0.99518472F,  0.980785251F, 0.956940353F,
      0.923879504F, 0.881921232F,  0.831469595F, 0.773010433F, 0.707106769F,
      0.634393334F, 0.555570245F,  0.471396744F, 0.382683456F, 0.290284663F,
      0.195090324F, 0.0980171412F, 0.0F};
  static const float costab[33] = {
      1.0F,          0.99518472F,    0.980785251F,  0.956940353F,
      0.923879504F,  0.881921232F,   0.831469595F,  0.773010433F,
      0.707106769F,  0.634393334F,   0.555570245F,  0.471396744F,
      0.382683456F,  0.290284663F,   0.195090324F,  0.0980171412F,
      0.0F,          -0.0980171412F, -0.195090324F, -0.290284663F,
      -0.382683456F, -0.471396744F,  -0.555570245F, -0.634393334F,
      -0.707106769F, -0.773010433F,  -0.831469595F, -0.881921232F,
      -0.923879504F, -0.956940353F,  -0.980785251F, -0.99518472F,
      -1.0F};
  static const float sintab[33] = {
      0.0F,          -0.0980171412F, -0.195090324F, -0.290284663F,
      -0.382683456F, -0.471396744F,  -0.555570245F, -0.634393334F,
      -0.707106769F, -0.773010433F,  -0.831469595F, -0.881921232F,
      -0.923879504F, -0.956940353F,  -0.980785251F, -0.99518472F,
      -1.0F,         -0.99518472F,   -0.980785251F, -0.956940353F,
      -0.923879504F, -0.881921232F,  -0.831469595F, -0.773010433F,
      -0.707106769F, -0.634393334F,  -0.555570245F, -0.471396744F,
      -0.382683456F, -0.290284663F,  -0.195090324F, -0.0980171412F,
      -0.0F};
  creal32_T Gceps[64];
  creal32_T Gcomp[64];
  float c_Gk[64];
  float b_Gk[33];
  float im;
  float r;
  float re;
  int i;
  /*  Set maximum FIR filter length to twice the gain vector length */
  /*  Add Nyquist bin gain = Nyquist-1 bin gain */
  memcpy(&b_Gk[0], &Gk[0], 32U * sizeof(float));
  b_Gk[32] = Gk[31];
  /*  Fill negative frequencies (by conjugate symmetry) */
  /*  Calculate real cepstrum */
  memcpy(&c_Gk[0], &b_Gk[0], 33U * sizeof(float));
  for (i = 0; i < 31; i++) {
    c_Gk[i + 33] = b_Gk[31 - i];
  }
  c_FFTImplementationCallback_doH(c_Gk, Gceps);
  /*  Apply combined folding & smoothing sequence */
  /*  Create Hamming window */
  /*  Window the real cepstrum */
  /*  Find modified log spectrum */
  /*  Calculate complex exponent (MIPS intensive approach - HA may be simpler)
   */
  for (i = 0; i < 64; i++) {
    re = 0.015625F * Gceps[i].re;
    im = 0.015625F * Gceps[i].im;
    Gceps[i].re = re;
    Gceps[i].im = im;
    r = fv[i];
    Gcomp[i].re = r * re;
    Gcomp[i].im = r * im;
  }
  c_FFTImplementationCallback_r2b(Gcomp, costab, sintab, Gceps);
  for (i = 0; i < 64; i++) {
    r = Gceps[i].re;
    im = Gceps[i].im;
    if (im == 0.0F) {
      re = r / 20.0F;
      im = 0.0F;
    } else if (r == 0.0F) {
      re = 0.0F;
      im /= 20.0F;
    } else {
      re = r / 20.0F;
      im /= 20.0F;
    }
    Gceps[i].re = re;
    Gceps[i].im = im;
    if (im == 0.0F) {
      Gcomp[i].re = rt_powf_snf(10.0F, re);
      Gcomp[i].im = 0.0F;
    } else {
      r = re * 2.30258512F - im * 0.0F;
      im = re * 0.0F + im * 2.30258512F;
      if (im == 0.0F) {
        Gcomp[i].re = expf(r);
        Gcomp[i].im = 0.0F;
      } else if (rtIsInfF(im) && rtIsInfF(r) && (r < 0.0F)) {
        Gcomp[i].re = 0.0F;
        Gcomp[i].im = 0.0F;
      } else {
        r = expf(r / 2.0F);
        Gcomp[i].re = r * (r * cosf(im));
        Gcomp[i].im = r * (r * sinf(im));
      }
    }
  }
  /*  Calculate filter impulse response */
  c_FFTImplementationCallback_r2b(Gcomp, costab, b_sintab, Gceps);
  for (i = 0; i < 64; i++) {
    FiltULD[i] = Gceps[i].re * 0.015625F;
  }
  /*  Return the desired number of filter taps */
}

/*
 * File trailer for firGen.c
 *
 * [EOF]
 */
