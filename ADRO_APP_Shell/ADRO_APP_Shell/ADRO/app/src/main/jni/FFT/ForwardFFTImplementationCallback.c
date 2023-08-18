/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: FFTImplementationCallback.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 31-Mar-2023 17:35:18
 */

/* Include Files */
#include "ForwardFFTImplementationCallback.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : const float x_data[]
 *                int x_size
 *                creal32_T y[64]
 * Return Type  : void
 */
void c_ForwardFFTImplementationCallback_doH(const float x_data[], int x_size,
                                     creal32_T y[64])
{
  static const creal32_T reconVar1[32] = {{
                                              1.0F, /* re */
                                              -1.0F /* im */
                                          },
                                          {
                                              0.901982844F, /* re */
                                              -0.99518472F  /* im */
                                          },
                                          {
                                              0.804909706F, /* re */
                                              -0.980785251F /* im */
                                          },
                                          {
                                              0.709715366F, /* re */
                                              -0.956940353F /* im */
                                          },
                                          {
                                              0.617316544F, /* re */
                                              -0.923879504F /* im */
                                          },
                                          {
                                              0.528603256F, /* re */
                                              -0.881921232F /* im */
                                          },
                                          {
                                              0.444429755F, /* re */
                                              -0.831469595F /* im */
                                          },
                                          {
                                              0.365606666F, /* re */
                                              -0.773010433F /* im */
                                          },
                                          {
                                              0.292893231F, /* re */
                                              -0.707106769F /* im */
                                          },
                                          {
                                              0.226989567F, /* re */
                                              -0.634393334F /* im */
                                          },
                                          {
                                              0.168530405F, /* re */
                                              -0.555570245F /* im */
                                          },
                                          {
                                              0.118078768F, /* re */
                                              -0.471396744F /* im */
                                          },
                                          {
                                              0.0761204958F, /* re */
                                              -0.382683456F  /* im */
                                          },
                                          {
                                              0.0430596471F, /* re */
                                              -0.290284663F  /* im */
                                          },
                                          {
                                              0.0192147493F, /* re */
                                              -0.195090324F  /* im */
                                          },
                                          {
                                              0.00481528044F, /* re */
                                              -0.0980171412F  /* im */
                                          },
                                          {
                                              0.0F, /* re */
                                              -0.0F /* im */
                                          },
                                          {
                                              0.00481528044F, /* re */
                                              0.0980171412F   /* im */
                                          },
                                          {
                                              0.0192147493F, /* re */
                                              0.195090324F   /* im */
                                          },
                                          {
                                              0.0430596471F, /* re */
                                              0.290284663F   /* im */
                                          },
                                          {
                                              0.0761204958F, /* re */
                                              0.382683456F   /* im */
                                          },
                                          {
                                              0.118078768F, /* re */
                                              0.471396744F  /* im */
                                          },
                                          {
                                              0.168530405F, /* re */
                                              0.555570245F  /* im */
                                          },
                                          {
                                              0.226989567F, /* re */
                                              0.634393334F  /* im */
                                          },
                                          {
                                              0.292893231F, /* re */
                                              0.707106769F  /* im */
                                          },
                                          {
                                              0.365606666F, /* re */
                                              0.773010433F  /* im */
                                          },
                                          {
                                              0.444429755F, /* re */
                                              0.831469595F  /* im */
                                          },
                                          {
                                              0.528603256F, /* re */
                                              0.881921232F  /* im */
                                          },
                                          {
                                              0.617316544F, /* re */
                                              0.923879504F  /* im */
                                          },
                                          {
                                              0.709715366F, /* re */
                                              0.956940353F  /* im */
                                          },
                                          {
                                              0.804909706F, /* re */
                                              0.980785251F  /* im */
                                          },
                                          {
                                              0.901982844F, /* re */
                                              0.99518472F   /* im */
                                          }};
  static const creal32_T reconVar2[32] = {{
                                              1.0F, /* re */
                                              1.0F  /* im */
                                          },
                                          {
                                              1.0980171F, /* re */
                                              0.99518472F /* im */
                                          },
                                          {
                                              1.19509029F, /* re */
                                              0.980785251F /* im */
                                          },
                                          {
                                              1.29028463F, /* re */
                                              0.956940353F /* im */
                                          },
                                          {
                                              1.38268352F, /* re */
                                              0.923879504F /* im */
                                          },
                                          {
                                              1.47139668F, /* re */
                                              0.881921232F /* im */
                                          },
                                          {
                                              1.55557024F, /* re */
                                              0.831469595F /* im */
                                          },
                                          {
                                              1.63439333F, /* re */
                                              0.773010433F /* im */
                                          },
                                          {
                                              1.70710683F, /* re */
                                              0.707106769F /* im */
                                          },
                                          {
                                              1.77301049F, /* re */
                                              0.634393334F /* im */
                                          },
                                          {
                                              1.83146954F, /* re */
                                              0.555570245F /* im */
                                          },
                                          {
                                              1.88192129F, /* re */
                                              0.471396744F /* im */
                                          },
                                          {
                                              1.9238795F,  /* re */
                                              0.382683456F /* im */
                                          },
                                          {
                                              1.95694041F, /* re */
                                              0.290284663F /* im */
                                          },
                                          {
                                              1.98078525F, /* re */
                                              0.195090324F /* im */
                                          },
                                          {
                                              1.99518466F,  /* re */
                                              0.0980171412F /* im */
                                          },
                                          {
                                              2.0F, /* re */
                                              0.0F  /* im */
                                          },
                                          {
                                              1.99518466F,   /* re */
                                              -0.0980171412F /* im */
                                          },
                                          {
                                              1.98078525F,  /* re */
                                              -0.195090324F /* im */
                                          },
                                          {
                                              1.95694041F,  /* re */
                                              -0.290284663F /* im */
                                          },
                                          {
                                              1.9238795F,   /* re */
                                              -0.382683456F /* im */
                                          },
                                          {
                                              1.88192129F,  /* re */
                                              -0.471396744F /* im */
                                          },
                                          {
                                              1.83146954F,  /* re */
                                              -0.555570245F /* im */
                                          },
                                          {
                                              1.77301049F,  /* re */
                                              -0.634393334F /* im */
                                          },
                                          {
                                              1.70710683F,  /* re */
                                              -0.707106769F /* im */
                                          },
                                          {
                                              1.63439333F,  /* re */
                                              -0.773010433F /* im */
                                          },
                                          {
                                              1.55557024F,  /* re */
                                              -0.831469595F /* im */
                                          },
                                          {
                                              1.47139668F,  /* re */
                                              -0.881921232F /* im */
                                          },
                                          {
                                              1.38268352F,  /* re */
                                              -0.923879504F /* im */
                                          },
                                          {
                                              1.29028463F,  /* re */
                                              -0.956940353F /* im */
                                          },
                                          {
                                              1.19509029F,  /* re */
                                              -0.980785251F /* im */
                                          },
                                          {
                                              1.0980171F,  /* re */
                                              -0.99518472F /* im */
                                          }};
  static const float fv[16] = {
      1.0F,          0.980785251F,  0.923879504F,  0.831469595F,
      0.707106769F,  0.555570245F,  0.382683456F,  0.195090324F,
      0.0F,          -0.195090324F, -0.382683456F, -0.555570245F,
      -0.707106769F, -0.831469595F, -0.923879504F, -0.980785251F};
  static const float fv1[16] = {
      0.0F,          -0.195090324F, -0.382683456F, -0.555570245F,
      -0.707106769F, -0.831469595F, -0.923879504F, -0.980785251F,
      -1.0F,         -0.980785251F, -0.923879504F, -0.831469595F,
      -0.707106769F, -0.555570245F, -0.382683456F, -0.195090324F};
  static const signed char bitrevIndex[32] = {
      1, 17, 9,  25, 5, 21, 13, 29, 3, 19, 11, 27, 7, 23, 15, 31,
      2, 18, 10, 26, 6, 22, 14, 30, 4, 20, 12, 28, 8, 24, 16, 32};
  static const signed char iv[32] = {1,  32, 31, 30, 29, 28, 27, 26, 25, 24, 23,
                                     22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12,
                                     11, 10, 9,  8,  7,  6,  5,  4,  3,  2};
  double d;
  float b_im;
  float b_re;
  float im;
  float re;
  float temp2_im;
  float temp2_re;
  float temp_im;
  float temp_re;
  float temp_re_tmp;
  int i;
  int iDelta;
  int iDelta2;
  int iheight;
  int j;
  int k;
  boolean_T nxeven;
  if ((x_size & 1) == 0) {
    nxeven = true;
    iDelta = x_size;
  } else if (x_size >= 64) {
    nxeven = true;
    iDelta = 64;
  } else {
    nxeven = false;
    iDelta = x_size - 1;
  }
  if (iDelta <= 64) {
    iDelta2 = iDelta;
  } else {
    iDelta2 = 64;
  }
  d = (double)iDelta2 / 2.0;
  if (iDelta > 64) {
    iDelta = 64;
  }
  iDelta = (int)((double)iDelta / 2.0);
  for (i = 0; i < iDelta; i++) {
    iDelta2 = i << 1;
    k = bitrevIndex[i] - 1;
    y[k].re = x_data[iDelta2];
    y[k].im = x_data[iDelta2 + 1];
  }
  if (!nxeven) {
    iDelta = bitrevIndex[(int)d] - 1;
    y[iDelta].re = x_data[(int)d << 1];
    y[iDelta].im = 0.0F;
  }
  for (i = 0; i <= 30; i += 2) {
    re = y[i + 1].re;
    im = y[i + 1].im;
    temp_re = re;
    temp_im = im;
    b_re = y[i].re;
    b_im = y[i].im;
    re = b_re - re;
    im = b_im - im;
    y[i + 1].re = re;
    y[i + 1].im = im;
    b_re += temp_re;
    b_im += temp_im;
    y[i].re = b_re;
    y[i].im = b_im;
  }
  iDelta = 2;
  iDelta2 = 4;
  k = 8;
  iheight = 29;
  while (k > 0) {
    int b_temp_re_tmp;
    int istart;
    for (i = 0; i < iheight; i += iDelta2) {
      b_temp_re_tmp = i + iDelta;
      temp_re = y[b_temp_re_tmp].re;
      temp_im = y[b_temp_re_tmp].im;
      y[b_temp_re_tmp].re = y[i].re - temp_re;
      y[b_temp_re_tmp].im = y[i].im - temp_im;
      y[i].re += temp_re;
      y[i].im += temp_im;
    }
    istart = 1;
    for (j = k; j < 16; j += k) {
      int ihi;
      temp2_re = fv[j];
      temp2_im = fv1[j];
      i = istart;
      ihi = istart + iheight;
      while (i < ihi) {
        b_temp_re_tmp = i + iDelta;
        temp_re_tmp = y[b_temp_re_tmp].im;
        im = y[b_temp_re_tmp].re;
        temp_re = temp2_re * im - temp2_im * temp_re_tmp;
        temp_im = temp2_re * temp_re_tmp + temp2_im * im;
        y[b_temp_re_tmp].re = y[i].re - temp_re;
        y[b_temp_re_tmp].im = y[i].im - temp_im;
        y[i].re += temp_re;
        y[i].im += temp_im;
        i += iDelta2;
      }
      istart++;
    }
    k /= 2;
    iDelta = iDelta2;
    iDelta2 += iDelta2;
    iheight -= iDelta;
  }
  temp_re_tmp = y[0].re;
  re = y[0].im;
  y[0].re = 0.5F * ((temp_re_tmp - (-re)) + (temp_re_tmp - (-re)));
  y[0].im = 0.5F * ((-temp_re_tmp + re) + (temp_re_tmp - re));
  im = temp_re_tmp - re;
  y[32].re = 0.5F * (im + im);
  y[32].im = 0.5F * ((temp_re_tmp + re) + (-temp_re_tmp - re));
  for (i = 0; i < 15; i++) {
    temp_re_tmp = y[i + 1].re;
    temp_re = y[i + 1].im;
    iDelta = iv[i + 1];
    temp2_re = y[iDelta - 1].re;
    temp2_im = y[iDelta - 1].im;
    re = reconVar1[i + 1].im;
    b_re = reconVar1[i + 1].re;
    b_im = reconVar2[i + 1].im;
    temp_im = reconVar2[i + 1].re;
    y[i + 1].re = 0.5F * ((temp_re_tmp * b_re - temp_re * re) +
                          (temp2_re * temp_im - -temp2_im * b_im));
    y[i + 1].im = 0.5F * ((temp_re_tmp * re + temp_re * b_re) +
                          (temp2_re * b_im + -temp2_im * temp_im));
    y[i + 33].re = 0.5F * ((temp_re_tmp * temp_im - temp_re * b_im) +
                           (temp2_re * b_re - -temp2_im * re));
    y[i + 33].im = 0.5F * ((temp_re_tmp * b_im + temp_re * temp_im) +
                           (temp2_re * re + -temp2_im * b_re));
    b_im = reconVar1[iDelta - 1].im;
    temp_im = reconVar1[iDelta - 1].re;
    im = reconVar2[iDelta - 1].im;
    re = reconVar2[iDelta - 1].re;
    y[iDelta - 1].re = 0.5F * ((temp2_re * temp_im - temp2_im * b_im) +
                               (temp_re_tmp * re - -temp_re * im));
    y[iDelta - 1].im = 0.5F * ((temp2_re * b_im + temp2_im * temp_im) +
                               (temp_re_tmp * im + -temp_re * re));
    y[iDelta + 31].re = 0.5F * ((temp2_re * re - temp2_im * im) +
                                (temp_re_tmp * temp_im - -temp_re * b_im));
    y[iDelta + 31].im = 0.5F * ((temp2_re * im + temp2_im * re) +
                                (temp_re_tmp * b_im + -temp_re * temp_im));
  }
  temp_re_tmp = y[16].re;
  temp_re = y[16].im;
  re = temp_re_tmp * 0.0F;
  b_re = temp_re * 0.0F;
  im = -temp_re * 0.0F;
  y[16].re = 0.5F * ((re - b_re) + (temp_re_tmp * 2.0F - im));
  y[16].im = 0.5F * ((re + b_re) + (temp_re_tmp * 0.0F + -temp_re * 2.0F));
  y[48].re = 0.5F * ((temp_re_tmp * 2.0F - temp_re * 0.0F) +
                     (temp_re_tmp * 0.0F - im));
  y[48].im = 0.5F * ((temp_re_tmp * 0.0F + temp_re * 2.0F) +
                     (temp_re_tmp * 0.0F + im));
}

/*
 * File trailer for FFTImplementationCallback.c
 *
 * [EOF]
 */
