/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: Forward_FFT.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 31-Mar-2023 17:35:18
 */

#ifndef FORWARD_FFT_H
#define FORWARD_FFT_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void Forward_FFT(const float xn_data[], const int xn_size[2],
                        float Xk[64]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for Forward_FFT.h
 *
 * [EOF]
 */
