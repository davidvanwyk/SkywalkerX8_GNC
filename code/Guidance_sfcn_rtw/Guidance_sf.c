/*
 * Guidance_sf.c
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "Guidance_sf".
 *
 * Model version              : 1.336
 * Simulink Coder version : 8.14 (R2018a) 06-Feb-2018
 * C source code generated on : Tue Sep 24 11:29:46 2019
 *
 * Target selection: rtwsfcn.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <math.h>
#include "Guidance_sf.h"
#include "Guidance_sf_private.h"
#include "simstruc.h"
#include "fixedpoint.h"
#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)

extern void *Guidance_malloc(SimStruct *S);

#endif

#ifndef __RTW_UTFREE__
#if defined (MATLAB_MEX_FILE)

extern void * utMalloc(size_t);
extern void utFree(void *);

#endif
#endif                                 /* #ifndef __RTW_UTFREE__ */

/* Forward declaration for local functions */
static real_T Guidance_norm(const real_T x[3]);
static real_T Guidance_rt_atan2d_snf(real_T u0, real_T u1);

#if defined(MATLAB_MEX_FILE)
#include "rt_nonfinite.c"
#endif

static const char_T *RT_MEMORY_ALLOCATION_ERROR =
  "memory allocation error in generated S-Function";

/* Function for MATLAB Function: '<S3>/Path Manager Follow Waypoints Fillet' */
static real_T Guidance_norm(const real_T x[3])
{
  real_T y;
  real_T scale;
  real_T absxk;
  real_T t;
  scale = 3.3121686421112381E-170;
  absxk = fabs(x[0]);
  if (absxk > 3.3121686421112381E-170) {
    y = 1.0;
    scale = absxk;
  } else {
    t = absxk / 3.3121686421112381E-170;
    y = t * t;
  }

  absxk = fabs(x[1]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  absxk = fabs(x[2]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  return scale * sqrt(y);
}

static real_T Guidance_rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int32_T u0_0;
  int32_T u1_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = atan2(u0_0, u1_0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/* System initialize for root system: '<Root>' */
#define MDL_INITIALIZE_CONDITIONS

static void mdlInitializeConditions(SimStruct *S)
{
  if (ssIsFirstInitCond(S)) {
    int32_T i;

    /* InitializeConditions for UnitDelay: '<S3>/Unit Delay3' */
    for (i = 0; i < 36; i++) {
      ((real_T *)ssGetDWork(S, 0))[i] =
        Guidance_ConstP.UnitDelay3_InitialCondition[i];
    }

    /* End of InitializeConditions for UnitDelay: '<S3>/Unit Delay3' */

    /* InitializeConditions for UnitDelay: '<S3>/Unit Delay1' */
    ((real_T *)ssGetDWork(S, 1))[0] = 1.0;

    /* InitializeConditions for UnitDelay: '<S3>/Unit Delay' */
    ((real_T *)ssGetDWork(S, 2))[0] = 2.0;
  } else {
    int32_T i;

    /* InitializeConditions for UnitDelay: '<S3>/Unit Delay3' */
    for (i = 0; i < 36; i++) {
      ((real_T *)ssGetDWork(S, 0))[i] =
        Guidance_ConstP.UnitDelay3_InitialCondition[i];
    }

    /* End of InitializeConditions for UnitDelay: '<S3>/Unit Delay3' */

    /* InitializeConditions for UnitDelay: '<S3>/Unit Delay1' */
    ((real_T *)ssGetDWork(S, 1))[0] = 1.0;

    /* InitializeConditions for UnitDelay: '<S3>/Unit Delay' */
    ((real_T *)ssGetDWork(S, 2))[0] = 2.0;
  }
}

/* Start for root system: '<Root>' */
#define MDL_START

static void mdlStart(SimStruct *S)
{
  /* instance underlying S-Function data */
#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)
#  if defined(MATLAB_MEX_FILE)

  /* non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

#  endif

  Guidance_malloc(S);
  if (ssGetErrorStatus(S) != (NULL) ) {
    return;
  }

#endif

  {
  }
}

/* Outputs for root system: '<Root>' */
static void mdlOutputs(SimStruct *S, int_T tid)
{
  real_T rho;
  real_T lambda;
  real_T q[36];
  real_T lengths[12];
  real_T iPlusOne;
  boolean_T y;
  int32_T k;
  int32_T b_k;
  real_T absxk;
  real_T t;
  real_T rtb_R;
  boolean_T rtb_Equal[36];
  int32_T i;
  real_T q_0[3];
  int32_T tmp;
  int32_T tmp_0;
  int32_T tmp_1;
  real_T tmp_2[9];
  real_T travPlaneNormal_idx_2;
  real_T rtb_c_idx_2;
  real_T rtb_q_idx_1;
  real_T rtb_q_idx_2;
  real_T rtb_q_idx_0;
  real_T rtb_r_idx_2;
  real_T rtb_c_idx_0;
  real_T rtb_c_idx_1;
  real_T rtb_r_idx_0;
  real_T rtb_r_idx_1;
  real_T absxk_tmp;
  real_T absxk_tmp_0;
  B_Guidance_T *_rtB;
  boolean_T exitg1;
  _rtB = ((B_Guidance_T *) ssGetLocalBlockIO(S));

  /* Outport: '<Root>/Va_c' */
  ((real_T *)ssGetOutputPortSignal(S, 0))[0] = *((const real_T **)
    ssGetInputPortSignalPtrs(S, 0))[0];

  /* RelationalOperator: '<S3>/Equal' incorporates:
   *  Inport: '<Root>/W'
   *  UnitDelay: '<S3>/Unit Delay3'
   */
  for (i = 0; i < 36; i++) {
    rtb_Equal[i] = (*((const real_T **)ssGetInputPortSignalPtrs(S, 1))[i] ==
                    ((real_T *)ssGetDWork(S, 0))[i]);
  }

  /* End of RelationalOperator: '<S3>/Equal' */

  /* Switch: '<S1>/Switch2' incorporates:
   *  Abs: '<S1>/Abs2'
   *  Constant: '<S1>/Constant4'
   */
  if (fabs(*((const real_T **)ssGetInputPortSignalPtrs(S, 3))[0]) >
      0.0017453292519943296) {
    absxk = *((const real_T **)ssGetInputPortSignalPtrs(S, 3))[0];
  } else {
    absxk = 0.0;
  }

  /* End of Switch: '<S1>/Switch2' */

  /* MATLAB Function: '<S1>/Banked Turn Turn Radius Calculation' */
  rtb_R = *((const real_T **)ssGetInputPortSignalPtrs(S, 0))[0] * *((const
    real_T **)ssGetInputPortSignalPtrs(S, 0))[0] * 1.2 * cos(absxk - *((const
    real_T **)ssGetInputPortSignalPtrs(S, 4))[0]) / 2.6285815777493138;

  /* MATLAB Function: '<S3>/Path Manager Follow Waypoints Fillet' incorporates:
   *  UnitDelay: '<S3>/Unit Delay'
   *  UnitDelay: '<S3>/Unit Delay1'
   */
  _rtB->i = ((real_T *)ssGetDWork(S, 2))[0];
  rtb_r_idx_0 = 0.0;
  rtb_q_idx_0 = 0.0;
  rtb_c_idx_0 = 0.0;
  rtb_r_idx_1 = 0.0;
  rtb_q_idx_1 = 0.0;
  rtb_c_idx_1 = 0.0;
  rtb_r_idx_2 = 0.0;
  rtb_q_idx_2 = 0.0;
  rtb_c_idx_2 = 0.0;
  rho = 0.0;
  lambda = 0.0;
  i = 0;
  memset(&q[0], 0, 36U * sizeof(real_T));
  memset(&lengths[0], 0, 12U * sizeof(real_T));
  if (((real_T *)ssGetDWork(S, 2))[0] + 1.0 > 12.0) {
    iPlusOne = ((((real_T *)ssGetDWork(S, 2))[0] + 1.0) - 12.0) + 1.0;
  } else {
    iPlusOne = ((real_T *)ssGetDWork(S, 2))[0] + 1.0;
  }

  y = true;
  k = 1;
  exitg1 = false;
  while ((!exitg1) && (k < 37)) {
    if (rtb_Equal[k - 1]) {
      y = false;
      exitg1 = true;
    } else {
      k++;
    }
  }

  if (y) {
    q_0[0] = *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[0] - *((const
      real_T **)ssGetInputPortSignalPtrs(S, 2))[0];
    q_0[1] = *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[1] - *((const
      real_T **)ssGetInputPortSignalPtrs(S, 2))[1];
    q_0[2] = *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[2] - *((const
      real_T **)ssGetInputPortSignalPtrs(S, 2))[2];
    lengths[0] = Guidance_norm(q_0);
    if (!rtIsNaN(lengths[0])) {
      k = 1;
    } else {
      k = 0;
      b_k = 2;
      exitg1 = false;
      while ((!exitg1) && (b_k < 13)) {
        if (!rtIsNaN(lengths[b_k - 1])) {
          k = b_k;
          exitg1 = true;
        } else {
          b_k++;
        }
      }
    }

    if (k == 0) {
      k = 1;
    } else {
      rtb_R = lengths[k - 1];
      for (b_k = k; b_k + 1 < 13; b_k++) {
        if (rtb_R > lengths[b_k]) {
          rtb_R = lengths[b_k];
          k = b_k + 1;
        }
      }
    }

    _rtB->i = (real_T)k - 1.0;
  } else {
    k = ((int32_T)((real_T *)ssGetDWork(S, 2))[0] - 1) * 3;
    b_k = ((int32_T)(((real_T *)ssGetDWork(S, 2))[0] - 1.0) - 1) * 3;
    q_0[0] = *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[k] - *((const
      real_T **)ssGetInputPortSignalPtrs(S, 1))[b_k];
    q_0[1] = *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[k + 1] - *((
      const real_T **)ssGetInputPortSignalPtrs(S, 1))[b_k + 1];
    q_0[2] = *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[k + 2] - *((
      const real_T **)ssGetInputPortSignalPtrs(S, 1))[b_k + 2];
    if (Guidance_norm(q_0) >= 1.0E-6) {
      k = (int32_T)((real_T *)ssGetDWork(S, 2))[0];
      b_k = (int32_T)(((real_T *)ssGetDWork(S, 2))[0] - 1.0);
      q_0[0] = *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[(k - 1) * 3] -
        *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[(b_k - 1) * 3];
      q_0[1] = *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[(k - 1) * 3 +
        1] - *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[(b_k - 1) * 3 +
        1];
      q_0[2] = *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[(k - 1) * 3 +
        2] - *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[(b_k - 1) * 3 +
        2];
      absxk = Guidance_norm(q_0);
      k = (int32_T)((real_T *)ssGetDWork(S, 2))[0];
      b_k = (int32_T)(((real_T *)ssGetDWork(S, 2))[0] - 1.0);
      tmp = (int32_T)(((real_T *)ssGetDWork(S, 2))[0] - 1.0);
      q[3 * (tmp - 1)] = (*((const real_T **)ssGetInputPortSignalPtrs(S, 1))[(k
        - 1) * 3] - *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[(b_k - 1)
                          * 3]) / absxk;
      q[1 + 3 * (tmp - 1)] = (*((const real_T **)ssGetInputPortSignalPtrs(S, 1))
        [(k - 1) * 3 + 1] - *((const real_T **)ssGetInputPortSignalPtrs(S, 1))
        [(b_k - 1) * 3 + 1]) / absxk;
      q[2 + 3 * (tmp - 1)] = (*((const real_T **)ssGetInputPortSignalPtrs(S, 1))
        [(k - 1) * 3 + 2] - *((const real_T **)ssGetInputPortSignalPtrs(S, 1))
        [(b_k - 1) * 3 + 2]) / absxk;
    } else {
      i = 3 * ((int32_T)(((real_T *)ssGetDWork(S, 2))[0] - 1.0) - 1);
      q[i] = 0.0;
      q[1 + i] = 0.0;
      q[2 + i] = 0.0;
    }

    k = (int32_T)((real_T *)ssGetDWork(S, 2))[0];
    b_k = ((int32_T)iPlusOne - 1) * 3;
    q_0[0] = *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[b_k] - *((const
      real_T **)ssGetInputPortSignalPtrs(S, 1))[(k - 1) * 3];
    q_0[1] = *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[b_k + 1] - *((
      const real_T **)ssGetInputPortSignalPtrs(S, 1))[(k - 1) * 3 + 1];
    q_0[2] = *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[b_k + 2] - *((
      const real_T **)ssGetInputPortSignalPtrs(S, 1))[(k - 1) * 3 + 2];
    if (Guidance_norm(q_0) >= 1.0E-6) {
      i = (int32_T)iPlusOne;
      k = (int32_T)((real_T *)ssGetDWork(S, 2))[0];
      q_0[0] = *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[(i - 1) * 3] -
        *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[(k - 1) * 3];
      q_0[1] = *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[(i - 1) * 3 +
        1] - *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[(k - 1) * 3 + 1];
      q_0[2] = *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[(i - 1) * 3 +
        2] - *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[(k - 1) * 3 + 2];
      absxk = Guidance_norm(q_0);
      i = (int32_T)iPlusOne;
      k = (int32_T)((real_T *)ssGetDWork(S, 2))[0];
      b_k = (int32_T)((real_T *)ssGetDWork(S, 2))[0];
      q[3 * (b_k - 1)] = (*((const real_T **)ssGetInputPortSignalPtrs(S, 1))[(i
        - 1) * 3] - *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[(k - 1) *
                          3]) / absxk;
      q[1 + 3 * (b_k - 1)] = (*((const real_T **)ssGetInputPortSignalPtrs(S, 1))
        [(i - 1) * 3 + 1] - *((const real_T **)ssGetInputPortSignalPtrs(S, 1))
        [(k - 1) * 3 + 1]) / absxk;
      q[2 + 3 * (b_k - 1)] = (*((const real_T **)ssGetInputPortSignalPtrs(S, 1))
        [(i - 1) * 3 + 2] - *((const real_T **)ssGetInputPortSignalPtrs(S, 1))
        [(k - 1) * 3 + 2]) / absxk;
    } else {
      i = 3 * ((int32_T)((real_T *)ssGetDWork(S, 2))[0] - 1);
      q[i] = 0.0;
      q[1 + i] = 0.0;
      q[2 + i] = 0.0;
    }

    k = (int32_T)(((real_T *)ssGetDWork(S, 2))[0] - 1.0);
    b_k = (int32_T)((real_T *)ssGetDWork(S, 2))[0];
    iPlusOne = acos((-q[(k - 1) * 3 + 1] * q[(b_k - 1) * 3 + 1] + -q[(k - 1) * 3]
                     * q[(b_k - 1) * 3]) + -q[(k - 1) * 3 + 2] * q[(b_k - 1) * 3
                    + 2]);
    if (((real_T *)ssGetDWork(S, 1))[0] == 1.0) {
      i = 1;
      k = (int32_T)(((real_T *)ssGetDWork(S, 2))[0] - 1.0);
      b_k = (int32_T)(((real_T *)ssGetDWork(S, 2))[0] - 1.0);
      rtb_R /= tan(iPlusOne / 2.0);
      tmp = (int32_T)((real_T *)ssGetDWork(S, 2))[0];
      tmp_0 = (int32_T)(((real_T *)ssGetDWork(S, 2))[0] - 1.0);
      tmp_1 = (int32_T)(((real_T *)ssGetDWork(S, 2))[0] - 1.0);
      rtb_r_idx_0 = *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[(k - 1) *
        3];
      rtb_q_idx_0 = q[(b_k - 1) * 3];
      rtb_r_idx_1 = *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[(k - 1) *
        3 + 1];
      rtb_q_idx_1 = q[(b_k - 1) * 3 + 1];
      rtb_r_idx_2 = *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[(k - 1) *
        3 + 2];
      rtb_q_idx_2 = q[(b_k - 1) * 3 + 2];
      if (((*((const real_T **)ssGetInputPortSignalPtrs(S, 2))[1] - (real_T)(*((
               const real_T **)ssGetInputPortSignalPtrs(S, 1))[(tmp - 1) * 3 + 1]
             - q[(tmp_0 - 1) * 3 + 1] * rtb_R)) * q[(tmp_1 - 1) * 3 + 1] + (*((
              const real_T **)ssGetInputPortSignalPtrs(S, 2))[0] - (real_T)(*((
               const real_T **)ssGetInputPortSignalPtrs(S, 1))[(tmp - 1) * 3] -
             q[(tmp_0 - 1) * 3] * rtb_R)) * q[(tmp_1 - 1) * 3]) + (*((const
             real_T **)ssGetInputPortSignalPtrs(S, 2))[2] - (real_T)(*((const
              real_T **)ssGetInputPortSignalPtrs(S, 1))[(tmp - 1) * 3 + 2] - q
            [(tmp_0 - 1) * 3 + 2] * rtb_R)) * q[(tmp_1 - 1) * 3 + 2] >= 0.0) {
        i = 2;
      }
    } else {
      i = 2;
      k = (int32_T)(((real_T *)ssGetDWork(S, 2))[0] - 1.0);
      b_k = (int32_T)((real_T *)ssGetDWork(S, 2))[0];
      q_0[0] = q[(k - 1) * 3] - q[(b_k - 1) * 3];
      q_0[1] = q[(k - 1) * 3 + 1] - q[(b_k - 1) * 3 + 1];
      q_0[2] = q[(k - 1) * 3 + 2] - q[(b_k - 1) * 3 + 2];
      if (Guidance_norm(q_0) >= 1.0E-6) {
        rho = rtb_R / sin(iPlusOne / 2.0);
        k = (int32_T)(((real_T *)ssGetDWork(S, 2))[0] - 1.0);
        b_k = (int32_T)((real_T *)ssGetDWork(S, 2))[0];
        q_0[0] = q[(k - 1) * 3] - q[(b_k - 1) * 3];
        q_0[1] = q[(k - 1) * 3 + 1] - q[(b_k - 1) * 3 + 1];
        q_0[2] = q[(k - 1) * 3 + 2] - q[(b_k - 1) * 3 + 2];
        lambda = Guidance_norm(q_0);
        k = (int32_T)((real_T *)ssGetDWork(S, 2))[0];
        b_k = (int32_T)(((real_T *)ssGetDWork(S, 2))[0] - 1.0);
        tmp = (int32_T)((real_T *)ssGetDWork(S, 2))[0];
        rtb_c_idx_0 = *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[(k - 1)
          * 3] - (q[(b_k - 1) * 3] - q[(tmp - 1) * 3]) * rho / lambda;
        rtb_c_idx_1 = *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[(k - 1)
          * 3 + 1] - (q[(b_k - 1) * 3 + 1] - q[(tmp - 1) * 3 + 1]) * rho /
          lambda;
      } else {
        k = (int32_T)((real_T *)ssGetDWork(S, 2))[0];
        rtb_c_idx_0 = *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[(k - 1)
          * 3];
        rtb_c_idx_1 = *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[(k - 1)
          * 3 + 1];
      }

      lambda = q[((int32_T)(((real_T *)ssGetDWork(S, 2))[0] - 1.0) - 1) * 3 + 1]
        * q[((int32_T)((real_T *)ssGetDWork(S, 2))[0] - 1) * 3];
      rtb_c_idx_2 = ((q[((int32_T)(((real_T *)ssGetDWork(S, 2))[0] - 1.0) - 1) *
                      3 + 2] * q[((int32_T)((real_T *)ssGetDWork(S, 2))[0] - 1) *
                      3 + 1] - q[((int32_T)(((real_T *)ssGetDWork(S, 2))[0] -
        1.0) - 1) * 3 + 1] * q[((int32_T)((real_T *)ssGetDWork(S, 2))[0] - 1) *
                      3 + 2]) * (*((const real_T **)ssGetInputPortSignalPtrs(S,
        1))[((int32_T)((real_T *)ssGetDWork(S, 2))[0] - 1) * 3] - *((const
        real_T **)ssGetInputPortSignalPtrs(S, 2))[0]) + (q[((int32_T)((real_T *)
        ssGetDWork(S, 2))[0] - 1) * 3 + 2] * q[((int32_T)(((real_T *)ssGetDWork
        (S, 2))[0] - 1.0) - 1) * 3] - q[((int32_T)(((real_T *)ssGetDWork(S, 2))
        [0] - 1.0) - 1) * 3 + 2] * q[((int32_T)((real_T *)ssGetDWork(S, 2))[0] -
        1) * 3]) * (*((const real_T **)ssGetInputPortSignalPtrs(S, 1))[((int32_T)
        ((real_T *)ssGetDWork(S, 2))[0] - 1) * 3 + 1] - *((const real_T **)
        ssGetInputPortSignalPtrs(S, 2))[1])) / (lambda - q[((int32_T)((real_T *)
        ssGetDWork(S, 2))[0] - 1) * 3 + 1] * q[((int32_T)(((real_T *)ssGetDWork
        (S, 2))[0] - 1.0) - 1) * 3]) + *((const real_T **)
        ssGetInputPortSignalPtrs(S, 1))[((int32_T)((real_T *)ssGetDWork(S, 2))[0]
        - 1) * 3 + 2];
      if ((q[((int32_T)(((real_T *)ssGetDWork(S, 2))[0] - 1.0) - 1) * 3 + 2] >
           0.0) && (rtb_c_idx_2 >= *((const real_T **)ssGetInputPortSignalPtrs(S,
             1))[((int32_T)((real_T *)ssGetDWork(S, 2))[0] - 1) * 3 + 2]) && (q
           [((int32_T)((real_T *)ssGetDWork(S, 2))[0] - 1) * 3 + 2] == 0.0)) {
        rtb_c_idx_2 = *((const real_T **)ssGetInputPortSignalPtrs(S, 1))
          [((int32_T)((real_T *)ssGetDWork(S, 2))[0] - 1) * 3 + 2];
      }

      if ((q[((int32_T)(((real_T *)ssGetDWork(S, 2))[0] - 1.0) - 1) * 3 + 2] <
           0.0) && (rtb_c_idx_2 <= *((const real_T **)ssGetInputPortSignalPtrs(S,
             1))[((int32_T)((real_T *)ssGetDWork(S, 2))[0] - 1) * 3 + 2]) && (q
           [((int32_T)((real_T *)ssGetDWork(S, 2))[0] - 1) * 3 + 2] == 0.0)) {
        rtb_c_idx_2 = *((const real_T **)ssGetInputPortSignalPtrs(S, 1))
          [((int32_T)((real_T *)ssGetDWork(S, 2))[0] - 1) * 3 + 2];
      }

      rho = rtb_R;
      lambda = q[((int32_T)(((real_T *)ssGetDWork(S, 2))[0] - 1.0) - 1) * 3] *
        q[((int32_T)((real_T *)ssGetDWork(S, 2))[0] - 1) * 3 + 1] - lambda;
      if (lambda < 0.0) {
        lambda = -1.0;
      } else if (lambda > 0.0) {
        lambda = 1.0;
      } else if (lambda == 0.0) {
        lambda = 0.0;
      } else {
        lambda = (rtNaN);
      }

      rtb_R /= tan(iPlusOne / 2.0);
      k = (int32_T)((real_T *)ssGetDWork(S, 2))[0];
      b_k = (int32_T)((real_T *)ssGetDWork(S, 2))[0];
      tmp = (int32_T)((real_T *)ssGetDWork(S, 2))[0];
      if (((*((const real_T **)ssGetInputPortSignalPtrs(S, 2))[1] - (q[(b_k - 1)
             * 3 + 1] * rtb_R + *((const real_T **)ssGetInputPortSignalPtrs(S, 1))
             [(k - 1) * 3 + 1])) * q[(tmp - 1) * 3 + 1] + (*((const real_T **)
             ssGetInputPortSignalPtrs(S, 2))[0] - (q[(b_k - 1) * 3] * rtb_R +
             *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[(k - 1) * 3])) *
           q[(tmp - 1) * 3]) + (*((const real_T **)ssGetInputPortSignalPtrs(S, 2))
           [2] - (q[(b_k - 1) * 3 + 2] * rtb_R + *((const real_T **)
             ssGetInputPortSignalPtrs(S, 1))[(k - 1) * 3 + 2])) * q[(tmp - 1) *
          3 + 2] >= 0.0) {
        _rtB->i = ((real_T *)ssGetDWork(S, 2))[0] + 1.0;
        if (((real_T *)ssGetDWork(S, 2))[0] + 1.0 > 12.0) {
          _rtB->i = 2.0;
        }

        i = 1;
      }
    }
  }

  _rtB->flag = i;

  /* MATLAB Function: '<S4>/Straight Line Path Following' */
  iPlusOne = 3.3121686421112381E-170;
  rtb_r_idx_0 = *((const real_T **)ssGetInputPortSignalPtrs(S, 2))[0] -
    rtb_r_idx_0;
  absxk_tmp = rtb_q_idx_1 - rtb_q_idx_2 * 0.0;
  absxk = fabs(absxk_tmp);
  if (absxk > 3.3121686421112381E-170) {
    rtb_R = 1.0;
    iPlusOne = absxk;
  } else {
    t = absxk / 3.3121686421112381E-170;
    rtb_R = t * t;
  }

  rtb_r_idx_1 = *((const real_T **)ssGetInputPortSignalPtrs(S, 2))[1] -
    rtb_r_idx_1;
  absxk_tmp_0 = rtb_q_idx_2 * 0.0 - rtb_q_idx_0;
  absxk = fabs(absxk_tmp_0);
  if (absxk > iPlusOne) {
    t = iPlusOne / absxk;
    rtb_R = rtb_R * t * t + 1.0;
    iPlusOne = absxk;
  } else {
    t = absxk / iPlusOne;
    rtb_R += t * t;
  }

  travPlaneNormal_idx_2 = *((const real_T **)ssGetInputPortSignalPtrs(S, 2))[2]
    - rtb_r_idx_2;
  absxk = rtb_q_idx_0 * 0.0 - rtb_q_idx_1 * 0.0;
  t = absxk / iPlusOne;
  rtb_R += t * t;
  rtb_R = iPlusOne * sqrt(rtb_R);
  iPlusOne = absxk_tmp / rtb_R;
  t = absxk_tmp_0 / rtb_R;
  rtb_R = absxk / rtb_R * travPlaneNormal_idx_2 + (rtb_r_idx_0 * iPlusOne +
    rtb_r_idx_1 * t);
  iPlusOne = rtb_r_idx_0 - rtb_R * iPlusOne;
  rtb_R = rtb_r_idx_1 - rtb_R * t;
  absxk = sqrt(rtb_q_idx_0 * rtb_q_idx_0 + rtb_q_idx_1 * rtb_q_idx_1);
  if (absxk >= 1.0E-6) {
    rtb_R = -rtb_r_idx_2 - rtb_q_idx_2 / absxk * sqrt(iPlusOne * iPlusOne +
      rtb_R * rtb_R);
  } else {
    rtb_R = -rtb_r_idx_2;
  }

  for (iPlusOne = Guidance_rt_atan2d_snf(rtb_q_idx_1, rtb_q_idx_0); iPlusOne -
       *((const real_T **)ssGetInputPortSignalPtrs(S, 5))[0] <
       -3.1415926535897931; iPlusOne += 6.2831853071795862) {
  }

  while (iPlusOne - *((const real_T **)ssGetInputPortSignalPtrs(S, 5))[0] >
         3.1415926535897931) {
    iPlusOne -= 6.2831853071795862;
  }

  /* MATLAB Function: '<S4>/Orbit Following' */
  absxk = *((const real_T **)ssGetInputPortSignalPtrs(S, 2))[0] - rtb_c_idx_0;
  t = *((const real_T **)ssGetInputPortSignalPtrs(S, 2))[1] - rtb_c_idx_1;
  for (rtb_q_idx_0 = Guidance_rt_atan2d_snf((real_T)(*((const real_T **)
          ssGetInputPortSignalPtrs(S, 2))[1] - rtb_c_idx_1), (real_T)(*((const
           real_T **)ssGetInputPortSignalPtrs(S, 2))[0] - rtb_c_idx_0));
       rtb_q_idx_0 - *((const real_T **)ssGetInputPortSignalPtrs(S, 5))[0] <
       -3.1415926535897931; rtb_q_idx_0 += 6.2831853071795862) {
  }

  while (rtb_q_idx_0 - *((const real_T **)ssGetInputPortSignalPtrs(S, 5))[0] >
         3.1415926535897931) {
    rtb_q_idx_0 -= 6.2831853071795862;
  }

  /* MultiPortSwitch: '<S8>/Multiport Switch' */
  if ((int32_T)_rtB->flag == 1) {
    /* MATLAB Function: '<S4>/Straight Line Path Following' */
    absxk = cos(iPlusOne);
    tmp_2[0] = absxk;
    rtb_c_idx_2 = sin(iPlusOne);
    tmp_2[3] = rtb_c_idx_2;
    tmp_2[6] = 0.0;
    tmp_2[1] = -rtb_c_idx_2;
    tmp_2[4] = absxk;
    tmp_2[7] = 0.0;
    tmp_2[2] = 0.0;
    tmp_2[5] = 0.0;
    tmp_2[8] = 1.0;
    for (k = 0; k < 3; k++) {
      q_0[k] = tmp_2[k + 6] * travPlaneNormal_idx_2 + (tmp_2[k + 3] *
        rtb_r_idx_1 + tmp_2[k] * rtb_r_idx_0);
    }

    /* Outport: '<Root>/h_c' incorporates:
     *  MATLAB Function: '<S4>/Straight Line Path Following'
     */
    ((real_T *)ssGetOutputPortSignal(S, 1))[0] = rtb_R;

    /* Outport: '<Root>/Chi_c' incorporates:
     *  MATLAB Function: '<S4>/Straight Line Path Following'
     */
    ((real_T *)ssGetOutputPortSignal(S, 2))[0] = iPlusOne - atan(0.01 * q_0[1]);
  } else {
    /* Outport: '<Root>/h_c' incorporates:
     *  MATLAB Function: '<S4>/Orbit Following'
     */
    ((real_T *)ssGetOutputPortSignal(S, 1))[0] = -rtb_c_idx_2;

    /* Outport: '<Root>/Chi_c' incorporates:
     *  MATLAB Function: '<S3>/Path Manager Follow Waypoints Fillet'
     *  MATLAB Function: '<S4>/Orbit Following'
     */
    ((real_T *)ssGetOutputPortSignal(S, 2))[0] = (atan((sqrt(absxk * absxk + t *
      t) - rho) * 0.08 / rho) + 1.5707963267948966) * lambda + rtb_q_idx_0;
  }

  /* End of MultiPortSwitch: '<S8>/Multiport Switch' */
  UNUSED_PARAMETER(tid);
}

/* Update for root system: '<Root>' */
#define MDL_UPDATE

static void mdlUpdate(SimStruct *S, int_T tid)
{
  int32_T i;
  B_Guidance_T *_rtB;
  _rtB = ((B_Guidance_T *) ssGetLocalBlockIO(S));

  /* Update for UnitDelay: '<S3>/Unit Delay3' incorporates:
   *  Inport: '<Root>/W'
   */
  for (i = 0; i < 36; i++) {
    ((real_T *)ssGetDWork(S, 0))[i] = *((const real_T **)
      ssGetInputPortSignalPtrs(S, 1))[i];
  }

  /* End of Update for UnitDelay: '<S3>/Unit Delay3' */

  /* Update for UnitDelay: '<S3>/Unit Delay1' */
  ((real_T *)ssGetDWork(S, 1))[0] = _rtB->flag;

  /* Update for UnitDelay: '<S3>/Unit Delay' */
  ((real_T *)ssGetDWork(S, 2))[0] = _rtB->i;
  UNUSED_PARAMETER(tid);
}

/* Termination for root system: '<Root>' */
static void mdlTerminate(SimStruct *S)
{

#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)

  if (ssGetUserData(S) != (NULL) ) {
    rt_FREE(ssGetLocalBlockIO(S));
  }

  rt_FREE(ssGetUserData(S));

#endif

}

#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)
#  include "Guidance_mid.h"
#endif

/* Function to initialize sizes. */
static void mdlInitializeSizes(SimStruct *S)
{
  ssSetNumSampleTimes(S, 1);           /* Number of sample times */
  ssSetNumContStates(S, 0);            /* Number of continuous states */
  ssSetNumNonsampledZCs(S, 0);         /* Number of nonsampled ZCs */

  /* Number of output ports */
  if (!ssSetNumOutputPorts(S, 3))
    return;

  /* outport number: 0 */
  if (!ssSetOutputPortVectorDimension(S, 0, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 0, SS_DOUBLE);
  }

  ssSetOutputPortSampleTime(S, 0, 0.01);
  ssSetOutputPortOffsetTime(S, 0, 0.0);
  ssSetOutputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);

  /* outport number: 1 */
  if (!ssSetOutputPortVectorDimension(S, 1, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 1, SS_DOUBLE);
  }

  ssSetOutputPortSampleTime(S, 1, 0.01);
  ssSetOutputPortOffsetTime(S, 1, 0.0);
  ssSetOutputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);

  /* outport number: 2 */
  if (!ssSetOutputPortVectorDimension(S, 2, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 2, SS_DOUBLE);
  }

  ssSetOutputPortSampleTime(S, 2, 0.01);
  ssSetOutputPortOffsetTime(S, 2, 0.0);
  ssSetOutputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);

  /* Number of input ports */
  if (!ssSetNumInputPorts(S, 6))
    return;

  /* inport number: 0 */
  {
    if (!ssSetInputPortVectorDimension(S, 0, 1))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 0, SS_DOUBLE);
    }

    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortSampleTime(S, 0, 0.01);
    ssSetInputPortOffsetTime(S, 0, 0.0);
    ssSetInputPortOverWritable(S, 0, 0);
    ssSetInputPortOptimOpts(S, 0, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  /* inport number: 1 */
  {
    {
      DimsInfo_T inpDims;
      int_T inpDimsVals[3] = { 3, 1, 12 };

      inpDims.width = 36;
      inpDims.numDims = 3;
      inpDims.dims = inpDimsVals;
      inpDims.nextSigDims = (NULL);
      if (!ssSetInputPortDimensionInfo(S, 1, &inpDims))
        return;
    }

    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 1, SS_DOUBLE);
    }

    ssSetInputPortDirectFeedThrough(S, 1, 1);
    ssSetInputPortSampleTime(S, 1, 0.01);
    ssSetInputPortOffsetTime(S, 1, 0.0);
    ssSetInputPortOverWritable(S, 1, 0);
    ssSetInputPortOptimOpts(S, 1, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  /* inport number: 2 */
  {
    if (!ssSetInputPortVectorDimension(S, 2, 3))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 2, SS_DOUBLE);
    }

    ssSetInputPortDirectFeedThrough(S, 2, 1);
    ssSetInputPortSampleTime(S, 2, 0.01);
    ssSetInputPortOffsetTime(S, 2, 0.0);
    ssSetInputPortOverWritable(S, 2, 0);
    ssSetInputPortOptimOpts(S, 2, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  /* inport number: 3 */
  {
    if (!ssSetInputPortVectorDimension(S, 3, 1))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 3, SS_DOUBLE);
    }

    ssSetInputPortDirectFeedThrough(S, 3, 1);
    ssSetInputPortSampleTime(S, 3, 0.01);
    ssSetInputPortOffsetTime(S, 3, 0.0);
    ssSetInputPortOverWritable(S, 3, 0);
    ssSetInputPortOptimOpts(S, 3, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  /* inport number: 4 */
  {
    if (!ssSetInputPortMatrixDimensions(S, 4, 1, 1))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 4, SS_DOUBLE);
    }

    ssSetInputPortDirectFeedThrough(S, 4, 1);
    ssSetInputPortSampleTime(S, 4, 0.01);
    ssSetInputPortOffsetTime(S, 4, 0.0);
    ssSetInputPortOverWritable(S, 4, 0);
    ssSetInputPortOptimOpts(S, 4, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  /* inport number: 5 */
  {
    if (!ssSetInputPortVectorDimension(S, 5, 1))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 5, SS_DOUBLE);
    }

    ssSetInputPortDirectFeedThrough(S, 5, 1);
    ssSetInputPortSampleTime(S, 5, 0.01);
    ssSetInputPortOffsetTime(S, 5, 0.0);
    ssSetInputPortOverWritable(S, 5, 0);
    ssSetInputPortOptimOpts(S, 5, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  ssSetRTWGeneratedSFcn(S, 1);         /* Generated S-function */

  /* DWork */
  if (!ssSetNumDWork(S, 3)) {
    return;
  }

  /* '<S3>/Unit Delay3': DSTATE */
  ssSetDWorkName(S, 0, "DWORK0");
  ssSetDWorkWidth(S, 0, 36);
  ssSetDWorkUsedAsDState(S, 0, 1);

  /* '<S3>/Unit Delay1': DSTATE */
  ssSetDWorkName(S, 1, "DWORK1");
  ssSetDWorkWidth(S, 1, 1);
  ssSetDWorkUsedAsDState(S, 1, 1);

  /* '<S3>/Unit Delay': DSTATE */
  ssSetDWorkName(S, 2, "DWORK2");
  ssSetDWorkWidth(S, 2, 1);
  ssSetDWorkUsedAsDState(S, 2, 1);

  /* Tunable Parameters */
  ssSetNumSFcnParams(S, 0);

  /* Number of expected parameters */
#if defined(MATLAB_MEX_FILE)

  if (ssGetNumSFcnParams(S) == ssGetSFcnParamsCount(S)) {

#if defined(MDL_CHECK_PARAMETERS)

    mdlCheckParameters(S);

#endif                                 /* MDL_CHECK_PARAMETERS */

    if (ssGetErrorStatus(S) != (NULL) ) {
      return;
    }
  } else {
    return;                            /* Parameter mismatch will be reported by Simulink */
  }

#endif                                 /* MATLAB_MEX_FILE */

  /* Options */
  ssSetOptions(S, (SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE |
                   SS_OPTION_PORT_SAMPLE_TIMES_ASSIGNED ));

#if SS_SFCN_FOR_SIM

  {
    ssSupportsMultipleExecInstances(S, true);
    ssHasStateInsideForEachSS(S, false);
  }

#endif

}

/* Function to initialize sample times. */
static void mdlInitializeSampleTimes(SimStruct *S)
{
  /* task periods */
  ssSetSampleTime(S, 0, 0.01);

  /* task offsets */
  ssSetOffsetTime(S, 0, 0.0);
}

#if defined(MATLAB_MEX_FILE)
# include "fixedpoint.c"
# include "simulink.c"
#else
# undef S_FUNCTION_NAME
# define S_FUNCTION_NAME               Guidance_sf
# include "cg_sfun.h"
#endif                                 /* defined(MATLAB_MEX_FILE) */
