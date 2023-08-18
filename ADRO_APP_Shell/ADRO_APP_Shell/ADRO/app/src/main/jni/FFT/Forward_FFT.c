/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: Forward_FFT.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 31-Mar-2023 17:35:18
 */

/* Include Files */
#include "Forward_FFT.h"
#include "ForwardFFTImplementationCallback.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static float rt_hypotf_snf(float u0, float u1);

/* Function Definitions */
/*
 * Arguments    : float u0
 *                float u1
 * Return Type  : float
 */
static float rt_hypotf_snf(float u0, float u1)
{
  float a;
  float b;
  float y;
  a = fabsf(u0);
  b = fabsf(u1);
  if (a < b) {
    a /= b;
    y = b * sqrtf(a * a + 1.0F);
  } else if (a > b) {
    b /= a;
    y = a * sqrtf(b * b + 1.0F);
  } else if (rtIsNaNF(b)) {
    y = rtNaNF;
  } else {
    y = a * 1.41421354F;
  }
  return y;
}

/*
 * Arguments    : const float xn_data[]
 *                const int xn_size[2]
 *                float Xk[64]
 * Return Type  : void
 */
void Forward_FFT(const float xn_data[], const int xn_size[2], float Xk[64])
{
  creal32_T yCol[64];
  float c_data[1024];
  int i;
  int loop_ub;
  loop_ub = xn_size[1];
  for (i = 0; i < loop_ub; i++) {
    c_data[i] = xn_data[i] / 64.0F;
  }
  if (xn_size[1] == 0) {
    memset(&yCol[0], 0, 64U * sizeof(creal32_T));
  } else {
    if (xn_size[1] < 64) {
      memset(&yCol[0], 0, 64U * sizeof(creal32_T));
    }
    c_ForwardFFTImplementationCallback_doH(c_data, xn_size[1], yCol);
  }
  for (loop_ub = 0; loop_ub < 64; loop_ub++) {
    Xk[loop_ub] = rt_hypotf_snf(yCol[loop_ub].re, yCol[loop_ub].im);
  }
}

/*
 * File trailer for Forward_FFT.c
 *
 * [EOF]
 */
