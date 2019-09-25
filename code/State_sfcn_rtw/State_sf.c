/*
 * State_sf.c
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "State_sf".
 *
 * Model version              : 1.336
 * Simulink Coder version : 8.14 (R2018a) 06-Feb-2018
 * C source code generated on : Tue Sep 24 11:29:13 2019
 *
 * Target selection: rtwsfcn.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <math.h>
#include "State_sf.h"
#include "State_sf_private.h"
#include "simstruc.h"
#include "fixedpoint.h"
#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)

extern void *State_malloc(SimStruct *S);

#endif

#ifndef __RTW_UTFREE__
#if defined (MATLAB_MEX_FILE)

extern void * utMalloc(size_t);
extern void utFree(void *);

#endif
#endif                                 /* #ifndef __RTW_UTFREE__ */

/* Forward declaration for local functions */
static void State_mrdivide(real_T A[42], const real_T B[36]);

#if defined(MATLAB_MEX_FILE)
#include "rt_nonfinite.c"
#endif

static const char_T *RT_MEMORY_ALLOCATION_ERROR =
  "memory allocation error in generated S-Function";

/* Function for MATLAB Function: '<S24>/Correct' */
static void State_mrdivide(real_T A[42], const real_T B[36])
{
  real_T b_A[36];
  int8_T ipiv[6];
  int32_T j;
  int32_T ix;
  real_T smax;
  real_T s;
  int32_T iy;
  int32_T c_ix;
  int32_T d;
  int32_T ijA;
  int32_T jBcol;
  int32_T kBcol;
  for (d = 0; d < 36; d++) {
    b_A[d] = B[d];
  }

  for (d = 0; d < 6; d++) {
    ipiv[d] = (int8_T)(1 + d);
  }

  for (j = 0; j < 5; j++) {
    jBcol = j * 7;
    iy = 0;
    ix = jBcol;
    smax = fabs(b_A[jBcol]);
    for (kBcol = 2; kBcol <= 6 - j; kBcol++) {
      ix++;
      s = fabs(b_A[ix]);
      if (s > smax) {
        iy = kBcol - 1;
        smax = s;
      }
    }

    if (b_A[jBcol + iy] != 0.0) {
      if (iy != 0) {
        iy += j;
        ipiv[j] = (int8_T)(iy + 1);
        ix = j;
        for (kBcol = 0; kBcol < 6; kBcol++) {
          smax = b_A[ix];
          b_A[ix] = b_A[iy];
          b_A[iy] = smax;
          ix += 6;
          iy += 6;
        }
      }

      iy = (jBcol - j) + 6;
      for (ix = jBcol + 1; ix < iy; ix++) {
        b_A[ix] /= b_A[jBcol];
      }
    }

    iy = jBcol;
    ix = jBcol + 6;
    for (kBcol = 1; kBcol <= 5 - j; kBcol++) {
      smax = b_A[ix];
      if (b_A[ix] != 0.0) {
        c_ix = jBcol + 1;
        d = (iy - j) + 12;
        for (ijA = 7 + iy; ijA < d; ijA++) {
          b_A[ijA] += b_A[c_ix] * -smax;
          c_ix++;
        }
      }

      ix += 6;
      iy += 6;
    }
  }

  for (j = 0; j < 6; j++) {
    jBcol = 7 * j;
    iy = 6 * j;
    for (ix = 1; ix <= j; ix++) {
      kBcol = (ix - 1) * 7;
      if (b_A[(ix + iy) - 1] != 0.0) {
        for (c_ix = 0; c_ix < 7; c_ix++) {
          d = c_ix + jBcol;
          A[d] -= b_A[(ix + iy) - 1] * A[c_ix + kBcol];
        }
      }
    }

    smax = 1.0 / b_A[j + iy];
    for (iy = 0; iy < 7; iy++) {
      d = iy + jBcol;
      A[d] *= smax;
    }
  }

  for (j = 5; j >= 0; j--) {
    jBcol = 7 * j;
    iy = 6 * j - 1;
    for (ix = j + 2; ix < 7; ix++) {
      kBcol = (ix - 1) * 7;
      if (b_A[ix + iy] != 0.0) {
        for (c_ix = 0; c_ix < 7; c_ix++) {
          A[c_ix + jBcol] -= b_A[ix + iy] * A[c_ix + kBcol];
        }
      }
    }
  }

  for (j = 4; j >= 0; j--) {
    if (j + 1 != ipiv[j]) {
      jBcol = ipiv[j] - 1;
      for (iy = 0; iy < 7; iy++) {
        smax = A[7 * j + iy];
        A[iy + 7 * j] = A[7 * jBcol + iy];
        A[iy + 7 * jBcol] = smax;
      }
    }
  }
}

/* System initialize for root system: '<Root>' */
#define MDL_INITIALIZE_CONDITIONS

static void mdlInitializeConditions(SimStruct *S)
{
  if (ssIsFirstInitCond(S)) {
    B_State_T *_rtB;
    _rtB = ((B_State_T *) ssGetLocalBlockIO(S));

    /* InitializeConditions for UnitDelay: '<S4>/Unit Delay' */
    ((real_T *)ssGetDWork(S, 0))[0] = 17.307195064481132;

    /* InitializeConditions for DiscreteStateSpace: '<S7>/Discrete State Space' */
    ((real_T*) ssGetDWork(S, 1))[0] = (2524.2267473563752);
    ((real_T*) ssGetDWork(S, 1))[1] = (2524.2267473563743);

    /* InitializeConditions for DiscreteStateSpace: '<S5>/Discrete State Space' */
    ((real_T*) ssGetDWork(S, 2))[0] = 0.0;

    /* InitializeConditions for DiscreteStateSpace: '<S8>/Discrete State Space' */
    ((real_T*) ssGetDWork(S, 3))[0] = 0.0;

    /* InitializeConditions for DiscreteStateSpace: '<S10>/Discrete State Space' */
    ((real_T*) ssGetDWork(S, 4))[0] = (0.30858283062531705);
    ((real_T*) ssGetDWork(S, 4))[1] = (0.30858283062531705);

    /* InitializeConditions for DiscreteStateSpace: '<S11>/Discrete State Space' */
    ((real_T*) ssGetDWork(S, 5))[0] = (0.0);
    ((real_T*) ssGetDWork(S, 5))[1] = (0.0);

    /* InitializeConditions for DiscreteStateSpace: '<S12>/Discrete State Space' */
    ((real_T*) ssGetDWork(S, 6))[0] = (-10.711719059939073);
    ((real_T*) ssGetDWork(S, 6))[1] = (-10.711719059939073);

    /* InitializeConditions for DiscreteStateSpace: '<S6>/Discrete State Space' */
    ((real_T*) ssGetDWork(S, 7))[0] = 0.0;

    /* InitializeConditions for DiscreteStateSpace: '<S9>/Discrete State Space' */
    ((real_T*) ssGetDWork(S, 8))[0] = (0.028943936860675427);
    ((real_T*) ssGetDWork(S, 8))[1] = (0.028943936860675437);

    /* InitializeConditions for DiscreteStateSpace: '<S2>/Discrete State Space' */
    ((real_T*) ssGetDWork(S, 9))[0] = (330.67699777186652);
    ((real_T*) ssGetDWork(S, 9))[1] = (330.67699777186652);

    /* InitializeConditions for DiscreteStateSpace: '<S20>/Discrete State Space' */
    ((real_T*) ssGetDWork(S, 10))[0] = 0.0;

    /* InitializeConditions for S-Function (sdspunwrap2): '<S4>/Unwrap' */
    ((boolean_T *)ssGetDWork(S, 17))[0] = true;
    ((real_T *)ssGetDWork(S, 16))[0] = 0.0;

    /* SystemInitialize for Enabled SubSystem: '<S21>/Correct1' */
    /* SystemInitialize for Outport: '<S24>/yBlockOrdering' */
    _rtB->blockOrdering = false;

    /* End of SystemInitialize for SubSystem: '<S21>/Correct1' */
  } else {
    B_State_T *_rtB;
    _rtB = ((B_State_T *) ssGetLocalBlockIO(S));

    /* InitializeConditions for UnitDelay: '<S4>/Unit Delay' */
    ((real_T *)ssGetDWork(S, 0))[0] = 17.307195064481132;

    /* InitializeConditions for DiscreteStateSpace: '<S7>/Discrete State Space' */
    ((real_T*) ssGetDWork(S, 1))[0] = (2524.2267473563752);
    ((real_T*) ssGetDWork(S, 1))[1] = (2524.2267473563743);

    /* InitializeConditions for DiscreteStateSpace: '<S5>/Discrete State Space' */
    ((real_T*) ssGetDWork(S, 2))[0] = 0.0;

    /* InitializeConditions for DiscreteStateSpace: '<S8>/Discrete State Space' */
    ((real_T*) ssGetDWork(S, 3))[0] = 0.0;

    /* InitializeConditions for DiscreteStateSpace: '<S10>/Discrete State Space' */
    ((real_T*) ssGetDWork(S, 4))[0] = (0.30858283062531705);
    ((real_T*) ssGetDWork(S, 4))[1] = (0.30858283062531705);

    /* InitializeConditions for DiscreteStateSpace: '<S11>/Discrete State Space' */
    ((real_T*) ssGetDWork(S, 5))[0] = (0.0);
    ((real_T*) ssGetDWork(S, 5))[1] = (0.0);

    /* InitializeConditions for DiscreteStateSpace: '<S12>/Discrete State Space' */
    ((real_T*) ssGetDWork(S, 6))[0] = (-10.711719059939073);
    ((real_T*) ssGetDWork(S, 6))[1] = (-10.711719059939073);

    /* InitializeConditions for DiscreteStateSpace: '<S6>/Discrete State Space' */
    ((real_T*) ssGetDWork(S, 7))[0] = 0.0;

    /* InitializeConditions for DiscreteStateSpace: '<S9>/Discrete State Space' */
    ((real_T*) ssGetDWork(S, 8))[0] = (0.028943936860675427);
    ((real_T*) ssGetDWork(S, 8))[1] = (0.028943936860675437);

    /* InitializeConditions for DiscreteStateSpace: '<S2>/Discrete State Space' */
    ((real_T*) ssGetDWork(S, 9))[0] = (330.67699777186652);
    ((real_T*) ssGetDWork(S, 9))[1] = (330.67699777186652);

    /* InitializeConditions for DiscreteStateSpace: '<S20>/Discrete State Space' */
    ((real_T*) ssGetDWork(S, 10))[0] = 0.0;

    /* InitializeConditions for S-Function (sdspunwrap2): '<S4>/Unwrap' */
    ((boolean_T *)ssGetDWork(S, 17))[0] = true;
    ((real_T *)ssGetDWork(S, 16))[0] = 0.0;
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
  if (ssGetSolverMode(S) == SOLVER_MODE_MULTITASKING) {
    ssSetErrorStatus(S, "This Simulink Coder generated "
                     "S-Function cannot be used in a simulation with "
                     "solver mode set to auto or multitasking "
                     "because this S-Function was created from a model with "
                     "solver mode set to singletasking. "
                     "See the Solver page of the simulation parameters dialog.");
    return;
  }

#  endif

  State_malloc(S);
  if (ssGetErrorStatus(S) != (NULL) ) {
    return;
  }

#endif

  {
    int32_T i;

    /* Start for DataStoreMemory: '<S14>/DataStoreMemory - P' */
    ((real_T *)ssGetDWork(S, 11))[0] = 1.0E-6;
    ((real_T *)ssGetDWork(S, 11))[1] = 0.0;
    ((real_T *)ssGetDWork(S, 11))[2] = 0.0;
    ((real_T *)ssGetDWork(S, 11))[3] = 1.0E-6;

    /* Start for DataStoreMemory: '<S14>/DataStoreMemory - x' */
    ((real_T *)ssGetDWork(S, 12))[0] = 0.0;
    ((real_T *)ssGetDWork(S, 12))[1] = 0.0288;

    /* Start for DataStoreMemory: '<S21>/DataStoreMemory - P' */
    for (i = 0; i < 49; i++) {
      ((real_T *)ssGetDWork(S, 13))[i] =
        State_ConstP.DataStoreMemoryP_InitialValue_d[i];
    }

    /* End of Start for DataStoreMemory: '<S21>/DataStoreMemory - P' */

    /* Start for DataStoreMemory: '<S21>/DataStoreMemory - x' */
    for (i = 0; i < 7; i++) {
      ((real_T *)ssGetDWork(S, 14))[i] =
        State_ConstP.DataStoreMemoryx_InitialValue_j[i];
    }

    /* End of Start for DataStoreMemory: '<S21>/DataStoreMemory - x' */
  }
}

/* Outputs for root system: '<Root>' */
static void mdlOutputs(SimStruct *S, int_T tid)
{
  /* local block i/o variables */
  real_T rtb_DiscreteStateSpace;
  real_T rtb_DiscreteStateSpace_c;
  real_T rtb_DiscreteStateSpace_l;
  real_T rtb_DiscreteStateSpace_ld;
  real_T rtb_DiscreteStateSpace_i;
  real_T rtb_DiscreteStateSpace_j;
  real_T rtb_DiscreteStateSpace_p;
  real_T rtb_DiscreteStateSpace_j3;
  real_T rtb_Gain1;
  real_T dHdx[6];
  real_T Pxy[6];
  real_T Pyy[9];
  real_T gain[6];
  int32_T r2;
  int32_T r3;
  real_T a21;
  int32_T rtemp;
  real_T dHdx_0[42];
  real_T gain_0[42];
  static const int8_T b[7] = { 1, 0, 0, 0, 0, 0, 0 };

  static const int8_T c[7] = { 0, 1, 0, 0, 0, 0, 0 };

  static const int8_T d[7] = { 0, 0, 1, 0, 0, 0, 0 };

  static const int8_T e[7] = { 0, 0, 0, 1, 0, 0, 0 };

  real_T Jacobian[49];
  int8_T I[49];
  real_T rtb_y;
  int32_T colIdx;
  real_T rtb_Sqrt;
  real_T rtb_DataStoreRead[2];
  real_T rtb_xNew_m[2];
  int32_T i;
  real_T dHdx_1[36];
  real_T gain_1[4];
  real_T tmp[4];
  real_T dHdx_2[42];
  real_T dHdx_3[49];
  real_T dHdx_4[7];
  real_T dHdx_idx_1;
  real_T dHdx_tmp;
  real_T dHdx_tmp_0;
  real_T dHdx_tmp_1;
  real_T dHdx_tmp_tmp;
  real_T dHdx_idx_2_tmp;
  B_State_T *_rtB;
  _rtB = ((B_State_T *) ssGetLocalBlockIO(S));

  /* RateTransition: '<S4>/Rate Transition2' incorporates:
   *  Constant: '<S1>/Constant3'
   *  Constant: '<S1>/Constant4'
   */
  if (ssIsSampleHit(S, 1, 0)) {
    _rtB->RateTransition2[0] = *((const real_T **)ssGetInputPortSignalPtrs(S, 0))
      [0];
    _rtB->RateTransition2[1] = *((const real_T **)ssGetInputPortSignalPtrs(S, 0))
      [1];
    _rtB->RateTransition2[2] = *((const real_T **)ssGetInputPortSignalPtrs(S, 1))
      [0];
    _rtB->RateTransition2[3] = *((const real_T **)ssGetInputPortSignalPtrs(S, 2))
      [0];
    _rtB->RateTransition2[4] = 0.0;
    _rtB->RateTransition2[5] = 0.0;

    /* MATLAB Function: '<S4>/Reciprocal' incorporates:
     *  Constant: '<S1>/Constant3'
     *  Constant: '<S1>/Constant4'
     *  UnitDelay: '<S4>/Unit Delay'
     */
    if (((real_T *)ssGetDWork(S, 0))[0] != 0.0) {
      rtb_y = 1.0 / ((real_T *)ssGetDWork(S, 0))[0];
    } else {
      rtb_y = 1.0E+6;
    }

    /* End of MATLAB Function: '<S4>/Reciprocal' */

    /* Gain: '<S4>/Gain' */
    rtb_y *= 0.0125;

    /* Math: '<S4>/Math Function1'
     *
     * About '<S4>/Math Function1':
     *  Operator: magnitude^2
     */
    rtb_y *= rtb_y;

    /* S-Function (sdspoverwrite): '<S4>/Overwrite Chi Variance' incorporates:
     *  Constant: '<S4>/Constant'
     */
    for (i = 0; i < 36; i++) {
      _rtB->OverwriteChiVariance[i] = State_ConstP.Constant_Value[i];
    }

    _rtB->OverwriteChiVariance[3] = rtb_y;

    /* End of S-Function (sdspoverwrite): '<S4>/Overwrite Chi Variance' */
  }

  /* End of RateTransition: '<S4>/Rate Transition2' */
  if (ssIsSampleHit(S, 0, 0)) {
    /* DiscreteStateSpace: '<S7>/Discrete State Space' */
    {
      rtb_Gain1 = 0.040134536115290324*((real_T*) ssGetDWork(S, 1))[0] +
        0.0325481728785217*((real_T*) ssGetDWork(S, 1))[1];
    }

    /* Product: '<S1>/Product1' incorporates:
     *  Gain: '<S1>/Gain'
     */
    rtb_Gain1 = 2.0 * rtb_Gain1 * State_rtC(S)->urho;

    /* Sqrt: '<S1>/Sqrt' */
    rtb_Sqrt = sqrt(rtb_Gain1);

    /* DiscreteStateSpace: '<S5>/Discrete State Space' */
    {
      rtb_DiscreteStateSpace = 0.99813255726829231*((real_T*) ssGetDWork(S, 2))
        [0];
    }

    /* DiscreteStateSpace: '<S8>/Discrete State Space' */
    {
      rtb_DiscreteStateSpace_c = 0.99813255726829231*((real_T*) ssGetDWork(S, 3))
        [0];
    }

    /* DiscreteStateSpace: '<S10>/Discrete State Space' */
    {
      rtb_DiscreteStateSpace_l = 0.8210255535859311*((real_T*) ssGetDWork(S, 4))
        [0] + 0.094414052618232353*((real_T*) ssGetDWork(S, 4))[1];
    }

    /* DiscreteStateSpace: '<S11>/Discrete State Space' */
    {
      rtb_DiscreteStateSpace_ld = 0.8210255535859311*((real_T*) ssGetDWork(S, 5))
        [0] + 0.094414052618232353*((real_T*) ssGetDWork(S, 5))[1];
    }

    /* DiscreteStateSpace: '<S12>/Discrete State Space' */
    {
      rtb_DiscreteStateSpace_i = 0.8210255535859311*((real_T*) ssGetDWork(S, 6))
        [0] + 0.094414052618232353*((real_T*) ssGetDWork(S, 6))[1];
    }

    /* DiscreteStateSpace: '<S6>/Discrete State Space' */
    {
      rtb_DiscreteStateSpace_j = 0.99813255726829231*((real_T*) ssGetDWork(S, 7))
        [0];
    }

    /* DiscreteStateSpace: '<S9>/Discrete State Space' */
    {
      rtb_DiscreteStateSpace_p = 0.98639906853442472*((real_T*) ssGetDWork(S, 8))
        [0] + 0.0098695333445151575*((real_T*) ssGetDWork(S, 8))[1];
    }

    /* Outputs for Enabled SubSystem: '<S14>/Correct1' incorporates:
     *  EnablePort: '<S15>/Enable'
     */
    /* MATLAB Function: '<S15>/Correct' incorporates:
     *  Constant: '<S14>/R1'
     *  DataStoreRead: '<S15>/Data Store ReadP'
     *  DataStoreRead: '<S15>/Data Store ReadX'
     *  DataStoreWrite: '<S15>/Data Store WriteP'
     */
    dHdx[0] = 0.0;
    rtb_y = cos(((real_T *)ssGetDWork(S, 12))[1]);
    dHdx_tmp_1 = 9.81 * rtb_y;
    dHdx[3] = dHdx_tmp_1;
    dHdx_tmp = cos(((real_T *)ssGetDWork(S, 12))[0]);
    dHdx[1] = -9.81 * dHdx_tmp * rtb_y;
    dHdx_tmp_tmp = sin(((real_T *)ssGetDWork(S, 12))[0]);
    a21 = 9.81 * dHdx_tmp_tmp;
    dHdx_tmp_0 = sin(((real_T *)ssGetDWork(S, 12))[1]);
    dHdx[4] = a21 * dHdx_tmp_0;
    dHdx[2] = a21 * rtb_y;
    dHdx[5] = 9.81 * dHdx_tmp * dHdx_tmp_0;
    for (i = 0; i < 2; i++) {
      for (colIdx = 0; colIdx < 3; colIdx++) {
        Pxy[i + (colIdx << 1)] = 0.0;
        Pxy[i + (colIdx << 1)] += ((real_T *)ssGetDWork(S, 11))[i] * dHdx[colIdx];
        Pxy[i + (colIdx << 1)] += ((real_T *)ssGetDWork(S, 11))[i + 2] *
          dHdx[colIdx + 3];
      }
    }

    for (i = 0; i < 3; i++) {
      gain[i] = 0.0;
      gain[i] += dHdx[i] * ((real_T *)ssGetDWork(S, 11))[0];
      gain[i] += dHdx[i + 3] * ((real_T *)ssGetDWork(S, 11))[1];
      gain[i + 3] = 0.0;
      gain[i + 3] += dHdx[i] * ((real_T *)ssGetDWork(S, 11))[2];
      gain[i + 3] += dHdx[i + 3] * ((real_T *)ssGetDWork(S, 11))[3];
      for (colIdx = 0; colIdx < 3; colIdx++) {
        Pyy[i + 3 * colIdx] = (gain[i + 3] * dHdx[colIdx + 3] + gain[i] *
          dHdx[colIdx]) + State_ConstP.R1_Value[3 * colIdx + i];
      }
    }

    colIdx = 0;
    r2 = 1;
    r3 = 2;
    rtb_y = fabs(Pyy[0]);
    a21 = fabs(Pyy[1]);
    if (a21 > rtb_y) {
      rtb_y = a21;
      colIdx = 1;
      r2 = 0;
    }

    if (fabs(Pyy[2]) > rtb_y) {
      colIdx = 2;
      r2 = 1;
      r3 = 0;
    }

    Pyy[r2] /= Pyy[colIdx];
    Pyy[r3] /= Pyy[colIdx];
    Pyy[3 + r2] -= Pyy[3 + colIdx] * Pyy[r2];
    Pyy[3 + r3] -= Pyy[3 + colIdx] * Pyy[r3];
    Pyy[6 + r2] -= Pyy[6 + colIdx] * Pyy[r2];
    Pyy[6 + r3] -= Pyy[6 + colIdx] * Pyy[r3];
    if (fabs(Pyy[3 + r3]) > fabs(Pyy[3 + r2])) {
      rtemp = r2;
      r2 = r3;
      r3 = rtemp;
    }

    Pyy[3 + r3] /= Pyy[3 + r2];
    Pyy[6 + r3] -= Pyy[3 + r3] * Pyy[6 + r2];
    for (rtemp = 0; rtemp < 2; rtemp++) {
      gain[rtemp + (colIdx << 1)] = Pxy[rtemp] / Pyy[colIdx];
      gain[rtemp + (r2 << 1)] = Pxy[2 + rtemp] - gain[(colIdx << 1) + rtemp] *
        Pyy[3 + colIdx];
      gain[rtemp + (r3 << 1)] = Pxy[4 + rtemp] - gain[(colIdx << 1) + rtemp] *
        Pyy[6 + colIdx];
      gain[rtemp + (r2 << 1)] /= Pyy[3 + r2];
      gain[rtemp + (r3 << 1)] -= gain[(r2 << 1) + rtemp] * Pyy[6 + r2];
      gain[rtemp + (r3 << 1)] /= Pyy[6 + r3];
      gain[rtemp + (r2 << 1)] -= gain[(r3 << 1) + rtemp] * Pyy[3 + r3];
      gain[rtemp + (colIdx << 1)] -= gain[(r3 << 1) + rtemp] * Pyy[r3];
      gain[rtemp + (colIdx << 1)] -= gain[(r2 << 1) + rtemp] * Pyy[r2];
      for (i = 0; i < 2; i++) {
        gain_1[rtemp + (i << 1)] = 0.0;
        gain_1[rtemp + (i << 1)] += dHdx[3 * i] * gain[rtemp];
        gain_1[rtemp + (i << 1)] += dHdx[3 * i + 1] * gain[rtemp + 2];
        gain_1[rtemp + (i << 1)] += dHdx[3 * i + 2] * gain[rtemp + 4];
      }

      tmp[rtemp] = ((real_T *)ssGetDWork(S, 11))[rtemp] - (gain_1[rtemp + 2] *
        ((real_T *)ssGetDWork(S, 11))[1] + gain_1[rtemp] * ((real_T *)ssGetDWork
        (S, 11))[0]);
      tmp[rtemp + 2] = ((real_T *)ssGetDWork(S, 11))[rtemp + 2] - (gain_1[rtemp
        + 2] * ((real_T *)ssGetDWork(S, 11))[3] + gain_1[rtemp] * ((real_T *)
        ssGetDWork(S, 11))[2]);
    }

    /* DataStoreWrite: '<S15>/Data Store WriteP' incorporates:
     *  MATLAB Function: '<S15>/Correct'
     */
    ((real_T *)ssGetDWork(S, 11))[0] = tmp[0];
    ((real_T *)ssGetDWork(S, 11))[1] = tmp[1];
    ((real_T *)ssGetDWork(S, 11))[2] = tmp[2];
    ((real_T *)ssGetDWork(S, 11))[3] = tmp[3];

    /* MATLAB Function: '<S15>/Correct' incorporates:
     *  SignalConversion: '<S18>/TmpSignal ConversionAt SFunction Inport3'
     *  SignalConversion: '<S18>/TmpSignal ConversionAt SFunction Inport5'
     */
    a21 = sin(rtb_DiscreteStateSpace_p);
    rtb_y = rtb_DiscreteStateSpace_l - (rtb_DiscreteStateSpace * rtb_Sqrt * a21
      + 9.81 * dHdx_tmp_0);
    dHdx_tmp_0 = cos(rtb_DiscreteStateSpace_p);
    dHdx_tmp_tmp = rtb_DiscreteStateSpace_ld - ((rtb_DiscreteStateSpace_c *
      rtb_Sqrt * dHdx_tmp_0 - rtb_DiscreteStateSpace_j * rtb_Sqrt * a21) -
      dHdx_tmp_1 * dHdx_tmp_tmp);
    dHdx_tmp_1 = rtb_DiscreteStateSpace_i - (-rtb_DiscreteStateSpace * rtb_Sqrt *
      dHdx_tmp_0 - dHdx_tmp_1 * dHdx_tmp);

    /* Outputs for Atomic SubSystem: '<S14>/Output' */
    for (i = 0; i < 2; i++) {
      /* DataStoreWrite: '<S15>/Data Store WriteX' incorporates:
       *  DataStoreRead: '<S15>/Data Store ReadX'
       *  MATLAB Function: '<S15>/Correct'
       */
      ((real_T *)ssGetDWork(S, 12))[i] = ((gain[i + 2] * dHdx_tmp_tmp + gain[i] *
        rtb_y) + gain[i + 4] * dHdx_tmp_1) + ((real_T *)ssGetDWork(S, 12))[i];

      /* DataStoreRead: '<S16>/Data Store Read' */
      rtb_DataStoreRead[i] = ((real_T *)ssGetDWork(S, 12))[i];
    }

    /* End of Outputs for SubSystem: '<S14>/Output' */
    /* End of Outputs for SubSystem: '<S14>/Correct1' */

    /* RateTransition: '<S4>/Rate Transition1' incorporates:
     *  DataStoreRead: '<S16>/Data Store Read'
     */
    if (ssIsSampleHit(S, 1, 0)) {
      _rtB->RateTransition1[0] = rtb_Sqrt;
      _rtB->RateTransition1[1] = rtb_DiscreteStateSpace;
      _rtB->RateTransition1[2] = rtb_DiscreteStateSpace_c;

      /* Outputs for Atomic SubSystem: '<S14>/Output' */
      _rtB->RateTransition1[3] = ((real_T *)ssGetDWork(S, 12))[0];
      _rtB->RateTransition1[4] = ((real_T *)ssGetDWork(S, 12))[1];

      /* End of Outputs for SubSystem: '<S14>/Output' */
    }

    /* End of RateTransition: '<S4>/Rate Transition1' */
  }

  if (ssIsSampleHit(S, 1, 0)) {
    /* Outputs for Enabled SubSystem: '<S21>/Correct1' incorporates:
     *  EnablePort: '<S24>/Enable'
     */
    /* MATLAB Function: '<S24>/Correct' incorporates:
     *  Constant: '<S21>/BlockOrdering'
     *  DataStoreRead: '<S24>/Data Store ReadP'
     *  DataStoreRead: '<S24>/Data Store ReadX'
     *  DataStoreWrite: '<S24>/Data Store WriteP'
     */
    _rtB->blockOrdering = true;
    for (i = 0; i < 7; i++) {
      dHdx_0[6 * i] = b[i];
      dHdx_0[1 + 6 * i] = c[i];
      dHdx_0[2 + 6 * i] = d[i];
      dHdx_0[3 + 6 * i] = e[i];
    }

    dHdx_0[4] = 0.0;
    dHdx_0[10] = 0.0;
    rtb_y = cos(((real_T *)ssGetDWork(S, 14))[3]);
    dHdx_0[16] = -rtb_y;
    dHdx_tmp_1 = sin(((real_T *)ssGetDWork(S, 14))[3]);
    dHdx_tmp = ((real_T *)ssGetDWork(S, 14))[2] * dHdx_tmp_1;
    dHdx_0[22] = dHdx_tmp;
    dHdx_0[28] = 1.0;
    dHdx_0[34] = 0.0;
    a21 = sin(((real_T *)ssGetDWork(S, 14))[6]);
    dHdx_0[40] = -_rtB->RateTransition1[0] * a21;
    dHdx_0[5] = 0.0;
    dHdx_0[11] = 0.0;
    dHdx_0[17] = -dHdx_tmp_1;
    dHdx_0[23] = -((real_T *)ssGetDWork(S, 14))[2] * rtb_y;
    dHdx_0[29] = 0.0;
    dHdx_0[35] = 1.0;
    dHdx_tmp_1 = _rtB->RateTransition1[0] * cos(((real_T *)ssGetDWork(S, 14))[6]);
    dHdx_0[41] = dHdx_tmp_1;
    for (i = 0; i < 7; i++) {
      for (colIdx = 0; colIdx < 6; colIdx++) {
        r3 = i + 7 * colIdx;
        gain_0[r3] = 0.0;
        for (r2 = 0; r2 < 7; r2++) {
          gain_0[r3] = ((real_T *)ssGetDWork(S, 13))[7 * r2 + i] * dHdx_0[6 * r2
            + colIdx] + gain_0[7 * colIdx + i];
        }
      }
    }

    for (i = 0; i < 6; i++) {
      for (colIdx = 0; colIdx < 7; colIdx++) {
        r3 = i + 6 * colIdx;
        dHdx_2[r3] = 0.0;
        for (r2 = 0; r2 < 7; r2++) {
          dHdx_2[r3] = dHdx_0[6 * r2 + i] * ((real_T *)ssGetDWork(S, 13))[7 *
            colIdx + r2] + dHdx_2[6 * colIdx + i];
        }
      }

      for (colIdx = 0; colIdx < 6; colIdx++) {
        dHdx_tmp_tmp = 0.0;
        for (r2 = 0; r2 < 7; r2++) {
          dHdx_tmp_tmp += dHdx_2[6 * r2 + i] * dHdx_0[6 * r2 + colIdx];
        }

        dHdx_1[i + 6 * colIdx] = _rtB->OverwriteChiVariance[6 * colIdx + i] +
          dHdx_tmp_tmp;
      }
    }

    State_mrdivide(gain_0, dHdx_1);
    for (i = 0; i < 7; i++) {
      for (colIdx = 0; colIdx < 7; colIdx++) {
        r3 = i + 7 * colIdx;
        Jacobian[r3] = 0.0;
        for (r2 = 0; r2 < 6; r2++) {
          Jacobian[r3] = gain_0[7 * r2 + i] * dHdx_0[6 * colIdx + r2] +
            Jacobian[7 * colIdx + i];
        }
      }

      for (colIdx = 0; colIdx < 7; colIdx++) {
        dHdx_tmp_tmp = 0.0;
        for (r2 = 0; r2 < 7; r2++) {
          dHdx_tmp_tmp += Jacobian[7 * r2 + i] * ((real_T *)ssGetDWork(S, 13))[7
            * colIdx + r2];
        }

        dHdx_3[i + 7 * colIdx] = ((real_T *)ssGetDWork(S, 13))[7 * colIdx + i] -
          dHdx_tmp_tmp;
      }
    }

    /* DataStoreWrite: '<S24>/Data Store WriteP' incorporates:
     *  MATLAB Function: '<S24>/Correct'
     */
    for (i = 0; i < 7; i++) {
      for (colIdx = 0; colIdx < 7; colIdx++) {
        ((real_T *)ssGetDWork(S, 13))[colIdx + 7 * i] = dHdx_3[7 * i + colIdx];
      }
    }

    /* MATLAB Function: '<S24>/Correct' incorporates:
     *  DataStoreRead: '<S24>/Data Store ReadX'
     */
    Pxy[0] = ((real_T *)ssGetDWork(S, 14))[0];
    Pxy[1] = ((real_T *)ssGetDWork(S, 14))[1];
    Pxy[2] = ((real_T *)ssGetDWork(S, 14))[2];
    Pxy[3] = ((real_T *)ssGetDWork(S, 14))[3];
    Pxy[4] = (dHdx_tmp_1 + ((real_T *)ssGetDWork(S, 14))[4]) - ((real_T *)
      ssGetDWork(S, 14))[2] * rtb_y;
    Pxy[5] = (_rtB->RateTransition1[0] * a21 + ((real_T *)ssGetDWork(S, 14))[5])
      - dHdx_tmp;
    for (i = 0; i < 6; i++) {
      gain[i] = _rtB->RateTransition2[i] - Pxy[i];
    }

    /* DataStoreWrite: '<S24>/Data Store WriteX' incorporates:
     *  DataStoreRead: '<S24>/Data Store ReadX'
     *  MATLAB Function: '<S24>/Correct'
     */
    for (i = 0; i < 7; i++) {
      dHdx_tmp_tmp = 0.0;
      for (colIdx = 0; colIdx < 6; colIdx++) {
        dHdx_tmp_tmp += gain_0[7 * colIdx + i] * gain[colIdx];
      }

      ((real_T *)ssGetDWork(S, 14))[i] = ((real_T *)ssGetDWork(S, 14))[i] +
        dHdx_tmp_tmp;
    }

    /* End of DataStoreWrite: '<S24>/Data Store WriteX' */
    /* End of Outputs for SubSystem: '<S21>/Correct1' */
  }

  if (ssIsSampleHit(S, 0, 0)) {
    /* Outputs for Atomic SubSystem: '<S21>/Output' */
    /* DataStoreRead: '<S25>/Data Store Read' */
    for (i = 0; i < 7; i++) {
      _rtB->DataStoreRead[i] = ((real_T *)ssGetDWork(S, 14))[i];
    }

    /* End of DataStoreRead: '<S25>/Data Store Read' */
    /* End of Outputs for SubSystem: '<S21>/Output' */

    /* DiscreteStateSpace: '<S2>/Discrete State Space' */
    {
      rtb_Gain1 = 0.040134536115290324*((real_T*) ssGetDWork(S, 9))[0] +
        0.0325481728785217*((real_T*) ssGetDWork(S, 9))[1];
    }

    /* Gain: '<S1>/Gain1' incorporates:
     *  Product: '<S1>/Product'
     */
    rtb_Gain1 = -(rtb_Gain1 * State_rtC(S)->ug * State_rtC(S)->urho_f);

    /* Outport: '<Root>/[pn, pe, pd]' */
    ((real_T *)ssGetOutputPortSignal(S, 0))[2] = rtb_Gain1;

    /* Outport: '<Root>/Va' */
    ((real_T *)ssGetOutputPortSignal(S, 1))[0] = rtb_Sqrt;

    /* Outport: '<Root>/[pn, pe, pd]' */
    ((real_T *)ssGetOutputPortSignal(S, 0))[0] = _rtB->DataStoreRead[0];

    /* Outport: '<Root>/[wn, we]' */
    ((real_T *)ssGetOutputPortSignal(S, 2))[0] = _rtB->DataStoreRead[4];

    /* Outport: '<Root>/[Phi, Theta, Psi]' */
    ((real_T *)ssGetOutputPortSignal(S, 3))[0] = rtb_DataStoreRead[0];

    /* Outport: '<Root>/[pn, pe, pd]' */
    ((real_T *)ssGetOutputPortSignal(S, 0))[1] = _rtB->DataStoreRead[1];

    /* Outport: '<Root>/[wn, we]' */
    ((real_T *)ssGetOutputPortSignal(S, 2))[1] = _rtB->DataStoreRead[5];

    /* Outport: '<Root>/[Phi, Theta, Psi]' */
    ((real_T *)ssGetOutputPortSignal(S, 3))[1] = rtb_DataStoreRead[1];
    ((real_T *)ssGetOutputPortSignal(S, 3))[2] = _rtB->DataStoreRead[6];

    /* Outport: '<Root>/[p, q, r]' */
    ((real_T *)ssGetOutputPortSignal(S, 4))[0] = rtb_DiscreteStateSpace_j;
    ((real_T *)ssGetOutputPortSignal(S, 4))[1] = rtb_DiscreteStateSpace;
    ((real_T *)ssGetOutputPortSignal(S, 4))[2] = rtb_DiscreteStateSpace_c;

    /* Outport: '<Root>/Vg' */
    ((real_T *)ssGetOutputPortSignal(S, 5))[0] = _rtB->DataStoreRead[2];

    /* DiscreteStateSpace: '<S20>/Discrete State Space' */
    {
      rtb_DiscreteStateSpace_j3 = 0.030927573695189354*((real_T*) ssGetDWork(S,
        10))[0];
    }

    /* MATLAB Function: '<S4>/MATLAB Function' */
    for (rtb_y = rtb_DiscreteStateSpace_j3; rtb_y < -3.1415926535897931; rtb_y +=
         6.2831853071795862) {
    }

    while (rtb_y > 3.1415926535897931) {
      rtb_y -= 6.2831853071795862;
    }

    /* End of MATLAB Function: '<S4>/MATLAB Function' */

    /* Outport: '<Root>/Chi' */
    ((real_T *)ssGetOutputPortSignal(S, 6))[0] = rtb_y;

    /* Outport: '<Root>/alpha' */
    ((real_T *)ssGetOutputPortSignal(S, 7))[0] = rtb_DiscreteStateSpace_p;

    /* DataTypeConversion: '<S14>/DataTypeConversion_uState' */
    dHdx[3] = rtb_Sqrt;
    dHdx[4] = rtb_DiscreteStateSpace_p;

    /* Outputs for Atomic SubSystem: '<S14>/Predict' */
    /* MATLAB Function: '<S17>/Predict' incorporates:
     *  DataStoreRead: '<S17>/Data Store ReadP'
     *  DataStoreRead: '<S17>/Data Store ReadX'
     *  DataTypeConversion: '<S14>/DataTypeConversion_uState'
     */
    rtb_y = cos(((real_T *)ssGetDWork(S, 12))[1]);
    dHdx_tmp_1 = tan(((real_T *)ssGetDWork(S, 12))[1]);
    dHdx_tmp = rtb_DiscreteStateSpace * cos(((real_T *)ssGetDWork(S, 12))[0]);
    dHdx_tmp_tmp = rtb_DiscreteStateSpace_c * sin(((real_T *)ssGetDWork(S, 12))
      [0]);
    dHdx_tmp_0 = (dHdx_tmp * dHdx_tmp_1 - dHdx_tmp_tmp * dHdx_tmp_1) * 0.01;
    a21 = rtb_DiscreteStateSpace_c * cos(((real_T *)ssGetDWork(S, 12))[0]);
    dHdx_idx_2_tmp = rtb_DiscreteStateSpace * sin(((real_T *)ssGetDWork(S, 12))
      [0]);
    rtb_y = (dHdx_idx_2_tmp + a21) / (rtb_y * rtb_y) * 0.01;
    dHdx_idx_1 = (-rtb_DiscreteStateSpace * sin(((real_T *)ssGetDWork(S, 12))[0])
                  - a21) * 0.01;
    rtb_xNew_m[0] = asin(sin(((dHdx_idx_2_tmp * dHdx_tmp_1 +
      rtb_DiscreteStateSpace_j) + a21 * dHdx_tmp_1) * 0.01 + ((real_T *)
      ssGetDWork(S, 12))[0]));
    rtb_xNew_m[1] = asin(sin((dHdx_tmp - dHdx_tmp_tmp) * 0.01 + ((real_T *)
      ssGetDWork(S, 12))[1]));
    for (i = 0; i < 2; i++) {
      gain_1[i << 1] = 0.0;
      gain_1[i << 1] += (1.0 + dHdx_tmp_0) * ((real_T *)ssGetDWork(S, 11))[i <<
        1];
      gain_1[i << 1] += ((real_T *)ssGetDWork(S, 11))[(i << 1) + 1] * rtb_y;
      gain_1[1 + (i << 1)] = 0.0;
      gain_1[1 + (i << 1)] += ((real_T *)ssGetDWork(S, 11))[i << 1] * dHdx_idx_1;
      gain_1[1 + (i << 1)] += ((real_T *)ssGetDWork(S, 11))[(i << 1) + 1];
    }

    /* End of Outputs for SubSystem: '<S14>/Predict' */

    /* DataTypeConversion: '<S21>/DataTypeConversion_uState' */
    dHdx[0] = rtb_Sqrt;
    dHdx[1] = rtb_DiscreteStateSpace;
    dHdx[2] = rtb_DiscreteStateSpace_c;

    /* Outputs for Atomic SubSystem: '<S14>/Predict' */
    for (i = 0; i < 2; i++) {
      /* DataStoreWrite: '<S17>/Data Store WriteP' incorporates:
       *  Constant: '<S14>/Q'
       *  MATLAB Function: '<S17>/Predict'
       */
      ((real_T *)ssGetDWork(S, 11))[i] = (gain_1[i + 2] * rtb_y + gain_1[i] *
        (dHdx_tmp_0 + 1.0)) + State_ConstP.Q_Value[i];
      ((real_T *)ssGetDWork(S, 11))[i + 2] = (gain_1[i] * dHdx_idx_1 + gain_1[i
        + 2]) + State_ConstP.Q_Value[i + 2];

      /* DataStoreWrite: '<S17>/Data Store WriteX' */
      ((real_T *)ssGetDWork(S, 12))[i] = rtb_xNew_m[i];

      /* DataTypeConversion: '<S21>/DataTypeConversion_uState' */
      dHdx[i + 3] = rtb_DataStoreRead[i];
    }

    /* End of Outputs for SubSystem: '<S14>/Predict' */

    /* Outputs for Atomic SubSystem: '<S21>/Predict' */
    /* MATLAB Function: '<S26>/Predict' incorporates:
     *  DataStoreRead: '<S26>/Data Store ReadP'
     *  DataStoreRead: '<S26>/Data Store ReadX'
     */
    rtb_Sqrt = ((real_T *)ssGetDWork(S, 14))[2];
    dHdx_tmp_0 = cos(dHdx[4]);
    dHdx_tmp_0 = dHdx[1] * sin(dHdx[3]) / dHdx_tmp_0 + dHdx[2] * cos(dHdx[3]) /
      dHdx_tmp_0;
    dHdx_tmp_tmp = sqrt(((real_T *)ssGetDWork(S, 14))[2] * ((real_T *)ssGetDWork
      (S, 14))[2]);
    if (dHdx_tmp_tmp < 0.001) {
      rtb_Sqrt = 0.001;
    }

    for (i = 0; i < 49; i++) {
      I[i] = 0;
    }

    dHdx_3[0] = 0.0;
    dHdx_3[7] = 0.0;
    dHdx_3[14] = 0.01 * cos(((real_T *)ssGetDWork(S, 14))[3]);
    dHdx_3[21] = -rtb_Sqrt * sin(((real_T *)ssGetDWork(S, 14))[3]) * 0.01;
    dHdx_3[28] = 0.0;
    dHdx_3[35] = 0.0;
    dHdx_3[42] = 0.0;
    dHdx_3[1] = 0.0;
    dHdx_3[8] = 0.0;
    dHdx_3[15] = 0.01 * sin(((real_T *)ssGetDWork(S, 14))[3]);
    dHdx_3[22] = rtb_Sqrt * cos(((real_T *)ssGetDWork(S, 14))[3]) * 0.01;
    dHdx_3[29] = 0.0;
    dHdx_3[36] = 0.0;
    dHdx_3[43] = 0.0;
    dHdx_3[2] = 0.0;
    dHdx_3[9] = 0.0;
    dHdx_3[16] = -(((dHdx[0] * cos(((real_T *)ssGetDWork(S, 14))[6]) + ((real_T *)
      ssGetDWork(S, 14))[4]) * (-dHdx[0] * dHdx_tmp_0 * sin(((real_T *)
      ssGetDWork(S, 14))[6])) + (dHdx[0] * sin(((real_T *)ssGetDWork(S, 14))[6])
      + ((real_T *)ssGetDWork(S, 14))[5]) * (dHdx[0] * dHdx_tmp_0 * cos(((real_T
      *)ssGetDWork(S, 14))[6]))) / rtb_Sqrt) / rtb_Sqrt * 0.01;
    dHdx_3[23] = 0.0;
    rtb_y = -dHdx_tmp_0 * dHdx[0];
    dHdx_3[30] = rtb_y * sin(((real_T *)ssGetDWork(S, 14))[6]) * 0.01;
    dHdx_3[37] = dHdx_tmp_0 * dHdx[0] * cos(((real_T *)ssGetDWork(S, 14))[6]) *
      0.01;
    dHdx_3[44] = (((real_T *)ssGetDWork(S, 14))[4] * cos(((real_T *)ssGetDWork(S,
      14))[6]) + ((real_T *)ssGetDWork(S, 14))[5] * sin(((real_T *)ssGetDWork(S,
      14))[6])) * rtb_y / rtb_Sqrt * 0.01;
    dHdx_3[3] = 0.0;
    dHdx_3[10] = 0.0;
    rtb_y = tan(dHdx[3]);
    dHdx_tmp_1 = ((real_T *)ssGetDWork(S, 14))[3] - ((real_T *)ssGetDWork(S, 14))
      [6];
    dHdx_tmp = cos(dHdx_tmp_1);
    dHdx_3[17] = -(9.81 / (rtb_Sqrt * rtb_Sqrt)) * rtb_y * dHdx_tmp * 0.01;
    dHdx_tmp_1 = sin(dHdx_tmp_1);
    dHdx_3[24] = -(9.81 / rtb_Sqrt) * rtb_y * dHdx_tmp_1 * 0.01;
    dHdx_3[31] = 0.0;
    dHdx_3[38] = 0.0;
    dHdx_3[45] = 9.81 / rtb_Sqrt * rtb_y * dHdx_tmp_1 * 0.01;
    for (rtemp = 0; rtemp < 7; rtemp++) {
      I[rtemp + 7 * rtemp] = 1;
      dHdx_3[4 + 7 * rtemp] = 0.0;
      dHdx_3[5 + 7 * rtemp] = 0.0;
      dHdx_3[6 + 7 * rtemp] = 0.0;
    }

    for (i = 0; i < 7; i++) {
      for (colIdx = 0; colIdx < 7; colIdx++) {
        r3 = 7 * i + colIdx;
        Jacobian[colIdx + 7 * i] = (real_T)I[r3] + dHdx_3[r3];
      }
    }

    rtb_Sqrt = ((real_T *)ssGetDWork(S, 14))[2];
    if (dHdx_tmp_tmp < 0.001) {
      rtb_Sqrt = 0.001;
    }

    for (i = 0; i < 7; i++) {
      for (colIdx = 0; colIdx < 7; colIdx++) {
        r3 = colIdx + 7 * i;
        dHdx_3[r3] = 0.0;
        for (r2 = 0; r2 < 7; r2++) {
          dHdx_3[r3] = Jacobian[7 * r2 + colIdx] * ((real_T *)ssGetDWork(S, 13))
            [7 * i + r2] + dHdx_3[7 * i + colIdx];
        }
      }
    }

    dHdx_4[0] = rtb_Sqrt * cos(((real_T *)ssGetDWork(S, 14))[3]) * 0.01;
    dHdx_4[1] = rtb_Sqrt * sin(((real_T *)ssGetDWork(S, 14))[3]) * 0.01;
    dHdx_4[2] = ((dHdx[0] * cos(((real_T *)ssGetDWork(S, 14))[6]) + ((real_T *)
      ssGetDWork(S, 14))[4]) * (-dHdx[0] * dHdx_tmp_0 * sin(((real_T *)
      ssGetDWork(S, 14))[6])) + (dHdx[0] * sin(((real_T *)ssGetDWork(S, 14))[6])
      + ((real_T *)ssGetDWork(S, 14))[5]) * (dHdx[0] * dHdx_tmp_0 * cos(((real_T
      *)ssGetDWork(S, 14))[6]))) / rtb_Sqrt * 0.01;
    dHdx_4[3] = 9.81 / rtb_Sqrt * rtb_y * dHdx_tmp * 0.01;
    dHdx_4[4] = 0.0;
    dHdx_4[5] = 0.0;
    dHdx_4[6] = 0.01 * dHdx_tmp_0;
    for (i = 0; i < 7; i++) {
      /* DataStoreWrite: '<S26>/Data Store WriteP' incorporates:
       *  Constant: '<S21>/Q'
       *  MATLAB Function: '<S26>/Predict'
       */
      for (colIdx = 0; colIdx < 7; colIdx++) {
        dHdx_tmp_tmp = 0.0;
        for (r2 = 0; r2 < 7; r2++) {
          dHdx_tmp_tmp += dHdx_3[7 * r2 + i] * Jacobian[7 * r2 + colIdx];
        }

        ((real_T *)ssGetDWork(S, 13))[i + 7 * colIdx] = State_ConstP.Q_Value_i[7
          * colIdx + i] + dHdx_tmp_tmp;
      }

      /* End of DataStoreWrite: '<S26>/Data Store WriteP' */

      /* DataStoreWrite: '<S26>/Data Store WriteX' incorporates:
       *  DataStoreRead: '<S26>/Data Store ReadX'
       *  MATLAB Function: '<S26>/Predict'
       */
      ((real_T *)ssGetDWork(S, 14))[i] = ((real_T *)ssGetDWork(S, 14))[i] +
        dHdx_4[i];
    }

    /* End of Outputs for SubSystem: '<S21>/Predict' */

    /* S-Function (sdspunwrap2): '<S4>/Unwrap' */
    if (((boolean_T *)ssGetDWork(S, 17))[0]) {
      ((real_T *)ssGetDWork(S, 15))[0] = _rtB->DataStoreRead[3];
      ((boolean_T *)ssGetDWork(S, 17))[0] = false;
    }

    rtb_Sqrt = ((real_T *)ssGetDWork(S, 16))[0];
    rtb_y = _rtB->DataStoreRead[3] - ((real_T *)ssGetDWork(S, 15))[0];
    a21 = rtb_y - floor((rtb_y + 3.1415926535897931) / 6.2831853071795862) *
      6.2831853071795862;
    if ((a21 == -3.1415926535897931) && (rtb_y > 0.0)) {
      a21 = 3.1415926535897931;
    }

    rtb_y = a21 - rtb_y;
    if (fabs(rtb_y) > 3.1415926535897931) {
      rtb_Sqrt = ((real_T *)ssGetDWork(S, 16))[0] + rtb_y;
    }

    _rtB->Unwrap = _rtB->DataStoreRead[3] + rtb_Sqrt;
    ((real_T *)ssGetDWork(S, 15))[0] = _rtB->DataStoreRead[3];
    ((real_T *)ssGetDWork(S, 16))[0] = rtb_Sqrt;

    /* End of S-Function (sdspunwrap2): '<S4>/Unwrap' */
  }

  UNUSED_PARAMETER(tid);
}

/* Update for root system: '<Root>' */
#define MDL_UPDATE

static void mdlUpdate(SimStruct *S, int_T tid)
{
  B_State_T *_rtB;
  _rtB = ((B_State_T *) ssGetLocalBlockIO(S));
  if (ssIsSampleHit(S, 1, 0)) {
    /* Update for UnitDelay: '<S4>/Unit Delay' */
    ((real_T *)ssGetDWork(S, 0))[0] = _rtB->DataStoreRead[2];
  }

  if (ssIsSampleHit(S, 0, 0)) {
    /* Update for DiscreteStateSpace: '<S7>/Discrete State Space' */
    {
      real_T xtmp = (*((const real_T**)ssGetInputPortSignalPtrs(S, 6)))[0];
      xtmp += (1.4608053820972908)*((real_T*) ssGetDWork(S, 1))[0] +
        (-0.533488091091103)*((real_T*) ssGetDWork(S, 1))[1];
      ((real_T*) ssGetDWork(S, 1))[1] = ((real_T*) ssGetDWork(S, 1))[0];
      ((real_T*) ssGetDWork(S, 1))[0] = xtmp;
    }

    /* Update for DiscreteStateSpace: '<S5>/Discrete State Space' */
    {
      ((real_T*) ssGetDWork(S, 2))[0] = (*((const real_T**)
        ssGetInputPortSignalPtrs(S, 4)))[1] + 0.0018674427317079893*((real_T*)
        ssGetDWork(S, 2))[0];
    }

    /* Update for DiscreteStateSpace: '<S8>/Discrete State Space' */
    {
      ((real_T*) ssGetDWork(S, 3))[0] = (*((const real_T**)
        ssGetInputPortSignalPtrs(S, 4)))[2] + 0.0018674427317079893*((real_T*)
        ssGetDWork(S, 3))[0];
    }

    /* Update for DiscreteStateSpace: '<S10>/Discrete State Space' */
    {
      real_T xtmp = (*((const real_T**)ssGetInputPortSignalPtrs(S, 3)))[0];
      xtmp += (0.086427836527544571)*((real_T*) ssGetDWork(S, 4))[0] +
        (-0.0018674427317079824)*((real_T*) ssGetDWork(S, 4))[1];
      ((real_T*) ssGetDWork(S, 4))[1] = ((real_T*) ssGetDWork(S, 4))[0];
      ((real_T*) ssGetDWork(S, 4))[0] = xtmp;
    }

    /* Update for DiscreteStateSpace: '<S11>/Discrete State Space' */
    {
      real_T xtmp = (*((const real_T**)ssGetInputPortSignalPtrs(S, 3)))[1];
      xtmp += (0.086427836527544571)*((real_T*) ssGetDWork(S, 5))[0] +
        (-0.0018674427317079824)*((real_T*) ssGetDWork(S, 5))[1];
      ((real_T*) ssGetDWork(S, 5))[1] = ((real_T*) ssGetDWork(S, 5))[0];
      ((real_T*) ssGetDWork(S, 5))[0] = xtmp;
    }

    /* Update for DiscreteStateSpace: '<S12>/Discrete State Space' */
    {
      real_T xtmp = (*((const real_T**)ssGetInputPortSignalPtrs(S, 3)))[2];
      xtmp += (0.086427836527544571)*((real_T*) ssGetDWork(S, 6))[0] +
        (-0.0018674427317079824)*((real_T*) ssGetDWork(S, 6))[1];
      ((real_T*) ssGetDWork(S, 6))[1] = ((real_T*) ssGetDWork(S, 6))[0];
      ((real_T*) ssGetDWork(S, 6))[0] = xtmp;
    }

    /* Update for DiscreteStateSpace: '<S6>/Discrete State Space' */
    {
      ((real_T*) ssGetDWork(S, 7))[0] = (*((const real_T**)
        ssGetInputPortSignalPtrs(S, 4)))[0] + 0.0018674427317079893*((real_T*)
        ssGetDWork(S, 7))[0];
    }

    /* Update for DiscreteStateSpace: '<S9>/Discrete State Space' */
    {
      real_T xtmp = (*((const real_T**)ssGetInputPortSignalPtrs(S, 8)))[0];
      xtmp += (0.003734885463416)*((real_T*) ssGetDWork(S, 8))[0] +
        (-3.4873423562089693E-6)*((real_T*) ssGetDWork(S, 8))[1];
      ((real_T*) ssGetDWork(S, 8))[1] = ((real_T*) ssGetDWork(S, 8))[0];
      ((real_T*) ssGetDWork(S, 8))[0] = xtmp;
    }

    /* Update for DiscreteStateSpace: '<S2>/Discrete State Space' */
    {
      real_T xtmp = (*((const real_T**)ssGetInputPortSignalPtrs(S, 7)))[0];
      xtmp += (1.4608053820972908)*((real_T*) ssGetDWork(S, 9))[0] +
        (-0.533488091091103)*((real_T*) ssGetDWork(S, 9))[1];
      ((real_T*) ssGetDWork(S, 9))[1] = ((real_T*) ssGetDWork(S, 9))[0];
      ((real_T*) ssGetDWork(S, 9))[0] = xtmp;
    }

    /* Update for DiscreteStateSpace: '<S20>/Discrete State Space' */
    {
      ((real_T*) ssGetDWork(S, 10))[0] = _rtB->Unwrap + 0.96907242630481061*
        ((real_T*) ssGetDWork(S, 10))[0];
    }
  }

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
#  include "State_mid.h"
#endif

/* Function to initialize sizes. */
static void mdlInitializeSizes(SimStruct *S)
{
  ssSetNumSampleTimes(S, 2);           /* Number of sample times */
  ssSetNumContStates(S, 0);            /* Number of continuous states */
  ssSetNumNonsampledZCs(S, 0);         /* Number of nonsampled ZCs */

  /* Number of output ports */
  if (!ssSetNumOutputPorts(S, 8))
    return;

  /* outport number: 0 */
  if (!ssSetOutputPortVectorDimension(S, 0, 3))
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
  if (!ssSetOutputPortVectorDimension(S, 2, 2))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 2, SS_DOUBLE);
  }

  ssSetOutputPortSampleTime(S, 2, 0.01);
  ssSetOutputPortOffsetTime(S, 2, 0.0);
  ssSetOutputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);

  /* outport number: 3 */
  if (!ssSetOutputPortVectorDimension(S, 3, 3))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 3, SS_DOUBLE);
  }

  ssSetOutputPortSampleTime(S, 3, 0.01);
  ssSetOutputPortOffsetTime(S, 3, 0.0);
  ssSetOutputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);

  /* outport number: 4 */
  if (!ssSetOutputPortVectorDimension(S, 4, 3))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 4, SS_DOUBLE);
  }

  ssSetOutputPortSampleTime(S, 4, 0.01);
  ssSetOutputPortOffsetTime(S, 4, 0.0);
  ssSetOutputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);

  /* outport number: 5 */
  if (!ssSetOutputPortVectorDimension(S, 5, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 5, SS_DOUBLE);
  }

  ssSetOutputPortSampleTime(S, 5, 0.01);
  ssSetOutputPortOffsetTime(S, 5, 0.0);
  ssSetOutputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);

  /* outport number: 6 */
  if (!ssSetOutputPortVectorDimension(S, 6, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 6, SS_DOUBLE);
  }

  ssSetOutputPortSampleTime(S, 6, 0.01);
  ssSetOutputPortOffsetTime(S, 6, 0.0);
  ssSetOutputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);

  /* outport number: 7 */
  if (!ssSetOutputPortMatrixDimensions(S, 7, 1, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 7, SS_DOUBLE);
  }

  ssSetOutputPortSampleTime(S, 7, 0.01);
  ssSetOutputPortOffsetTime(S, 7, 0.0);
  ssSetOutputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);

  /* Number of input ports */
  if (!ssSetNumInputPorts(S, 9))
    return;

  /* inport number: 0 */
  {
    if (!ssSetInputPortVectorDimension(S, 0, 3))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 0, SS_DOUBLE);
    }

    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortSampleTime(S, 0, 0.2);
    ssSetInputPortOffsetTime(S, 0, 0.0);
    ssSetInputPortOverWritable(S, 0, 0);
    ssSetInputPortOptimOpts(S, 0, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  /* inport number: 1 */
  {
    if (!ssSetInputPortVectorDimension(S, 1, 1))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 1, SS_DOUBLE);
    }

    ssSetInputPortDirectFeedThrough(S, 1, 1);
    ssSetInputPortSampleTime(S, 1, 0.2);
    ssSetInputPortOffsetTime(S, 1, 0.0);
    ssSetInputPortOverWritable(S, 1, 0);
    ssSetInputPortOptimOpts(S, 1, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  /* inport number: 2 */
  {
    if (!ssSetInputPortMatrixDimensions(S, 2, 1, 1))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 2, SS_DOUBLE);
    }

    ssSetInputPortDirectFeedThrough(S, 2, 1);
    ssSetInputPortSampleTime(S, 2, 0.2);
    ssSetInputPortOffsetTime(S, 2, 0.0);
    ssSetInputPortOverWritable(S, 2, 0);
    ssSetInputPortOptimOpts(S, 2, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  /* inport number: 3 */
  {
    if (!ssSetInputPortVectorDimension(S, 3, 3))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 3, SS_DOUBLE);
    }

    ssSetInputPortSampleTime(S, 3, 0.01);
    ssSetInputPortOffsetTime(S, 3, 0.0);
    ssSetInputPortOverWritable(S, 3, 0);
    ssSetInputPortOptimOpts(S, 3, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  /* inport number: 4 */
  {
    if (!ssSetInputPortVectorDimension(S, 4, 3))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 4, SS_DOUBLE);
    }

    ssSetInputPortSampleTime(S, 4, 0.01);
    ssSetInputPortOffsetTime(S, 4, 0.0);
    ssSetInputPortOverWritable(S, 4, 0);
    ssSetInputPortOptimOpts(S, 4, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  /* inport number: 5 */
  {
    if (!ssSetInputPortMatrixDimensions(S, 5, 1, 1))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 5, SS_DOUBLE);
    }

    ssSetInputPortSampleTime(S, 5, 0.01);
    ssSetInputPortOffsetTime(S, 5, 0.0);
    ssSetInputPortOverWritable(S, 5, 0);
    ssSetInputPortOptimOpts(S, 5, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  /* inport number: 6 */
  {
    if (!ssSetInputPortVectorDimension(S, 6, 1))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 6, SS_DOUBLE);
    }

    ssSetInputPortSampleTime(S, 6, 0.01);
    ssSetInputPortOffsetTime(S, 6, 0.0);
    ssSetInputPortOverWritable(S, 6, 0);
    ssSetInputPortOptimOpts(S, 6, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  /* inport number: 7 */
  {
    if (!ssSetInputPortMatrixDimensions(S, 7, 1, 1))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 7, SS_DOUBLE);
    }

    ssSetInputPortSampleTime(S, 7, 0.01);
    ssSetInputPortOffsetTime(S, 7, 0.0);
    ssSetInputPortOverWritable(S, 7, 0);
    ssSetInputPortOptimOpts(S, 7, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  /* inport number: 8 */
  {
    if (!ssSetInputPortMatrixDimensions(S, 8, 1, 1))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 8, SS_DOUBLE);
    }

    ssSetInputPortSampleTime(S, 8, 0.01);
    ssSetInputPortOffsetTime(S, 8, 0.0);
    ssSetInputPortOverWritable(S, 8, 0);
    ssSetInputPortOptimOpts(S, 8, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  ssSetRTWGeneratedSFcn(S, 1);         /* Generated S-function */

  /* DWork */
  if (!ssSetNumDWork(S, 18)) {
    return;
  }

  /* '<S4>/Unit Delay': DSTATE */
  ssSetDWorkName(S, 0, "DWORK0");
  ssSetDWorkWidth(S, 0, 1);
  ssSetDWorkUsedAsDState(S, 0, 1);

  /* '<S7>/Discrete State Space': DSTATE */
  ssSetDWorkName(S, 1, "DWORK1");
  ssSetDWorkWidth(S, 1, 2);
  ssSetDWorkUsedAsDState(S, 1, 1);

  /* '<S5>/Discrete State Space': DSTATE */
  ssSetDWorkName(S, 2, "DWORK2");
  ssSetDWorkWidth(S, 2, 1);
  ssSetDWorkUsedAsDState(S, 2, 1);

  /* '<S8>/Discrete State Space': DSTATE */
  ssSetDWorkName(S, 3, "DWORK3");
  ssSetDWorkWidth(S, 3, 1);
  ssSetDWorkUsedAsDState(S, 3, 1);

  /* '<S10>/Discrete State Space': DSTATE */
  ssSetDWorkName(S, 4, "DWORK4");
  ssSetDWorkWidth(S, 4, 2);
  ssSetDWorkUsedAsDState(S, 4, 1);

  /* '<S11>/Discrete State Space': DSTATE */
  ssSetDWorkName(S, 5, "DWORK5");
  ssSetDWorkWidth(S, 5, 2);
  ssSetDWorkUsedAsDState(S, 5, 1);

  /* '<S12>/Discrete State Space': DSTATE */
  ssSetDWorkName(S, 6, "DWORK6");
  ssSetDWorkWidth(S, 6, 2);
  ssSetDWorkUsedAsDState(S, 6, 1);

  /* '<S6>/Discrete State Space': DSTATE */
  ssSetDWorkName(S, 7, "DWORK7");
  ssSetDWorkWidth(S, 7, 1);
  ssSetDWorkUsedAsDState(S, 7, 1);

  /* '<S9>/Discrete State Space': DSTATE */
  ssSetDWorkName(S, 8, "DWORK8");
  ssSetDWorkWidth(S, 8, 2);
  ssSetDWorkUsedAsDState(S, 8, 1);

  /* '<S2>/Discrete State Space': DSTATE */
  ssSetDWorkName(S, 9, "DWORK9");
  ssSetDWorkWidth(S, 9, 2);
  ssSetDWorkUsedAsDState(S, 9, 1);

  /* '<S20>/Discrete State Space': DSTATE */
  ssSetDWorkName(S, 10, "DWORK10");
  ssSetDWorkWidth(S, 10, 1);
  ssSetDWorkUsedAsDState(S, 10, 1);

  /* '<S14>/DataStoreMemory - P': dsmMem */
  ssSetDWorkName(S, 11, "DWORK11");
  ssSetDWorkWidth(S, 11, 4);

  /* '<S14>/DataStoreMemory - x': dsmMem */
  ssSetDWorkName(S, 12, "DWORK12");
  ssSetDWorkWidth(S, 12, 2);

  /* '<S21>/DataStoreMemory - P': dsmMem */
  ssSetDWorkName(S, 13, "DWORK13");
  ssSetDWorkWidth(S, 13, 49);

  /* '<S21>/DataStoreMemory - x': dsmMem */
  ssSetDWorkName(S, 14, "DWORK14");
  ssSetDWorkWidth(S, 14, 7);

  /* '<S4>/Unwrap': Prev */
  ssSetDWorkName(S, 15, "DWORK15");
  ssSetDWorkWidth(S, 15, 1);

  /* '<S4>/Unwrap': Cumsum */
  ssSetDWorkName(S, 16, "DWORK16");
  ssSetDWorkWidth(S, 16, 1);

  /* '<S4>/Unwrap': FirstStep */
  ssSetDWorkName(S, 17, "DWORK17");
  ssSetDWorkWidth(S, 17, 1);
  ssSetDWorkDataType(S, 17, SS_BOOLEAN);

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
    ssSupportsMultipleExecInstances(S, false);
    ssRegisterMsgForNotSupportingMultiExecInst(S,
      "<diag_root><diag id=\"Simulink:blocks:BlockDoesNotSupportMultiExecInstances\" pr=\"d\"><arguments><arg type=\"encoded\">UwB0AGEAdABlAC8AUwB0AGEAdABlACAARQBzAHQAaQBtAGEAdABpAG8AbgAvAEEAdAB0AGkAdAB1AGQAZQAgAEUAcwB0AGkAbQBhAHQAaQBvAG4AIABFAHgAdABlAG4AZABlAGQAIABLAGEAbABtAGEAbgAgAEYAaQBsAHQAZQByACAAdwBpAHQAaAAgAEYAaQBsAHQAZQByAGkAbgBnAC8AQQB0AHQAaQB0AHUAZABlACAARQBzAHQAaQBtAGEAdABpAG8AbgAgAEUAeAB0AGUAbgBkAGUAZAAgAEsAYQBsAG0AYQBuACAARgBpAGwAdABlAHIALwBBAHQAdABpAHQAdQBkAGUAIABFAHMAdABpAG0AYQB0AGkAbwBuACAARQB4AHQAZQBuAGQAZQBkACAASwBhAGwAbQBhAG4AIABGAGkAbAB0AGUAcgAvAEMAbwByAHIAZQBjAHQAMQAvAEQAYQB0AGEAIABTAHQAbwByAGUAIABSAGUAYQBkAFgAAAA=</arg><arg type=\"encoded\">PABfAF8AaQBpAFMAUwBfAF8APgA8AC8AXwBfAGkAaQBTAFMAXwBfAD4AAAA=</arg><arg type=\"encoded\">PABfAF8AaQB0AGUAcgBCAGwAawBfAF8APgA8AC8AXwBfAGkAdABlAHIAQgBsAGsAXwBfAD4AAAA=</arg></arguments><hs><h>AAAAsACLs0D+</h></hs></diag></diag_root>");
    ssHasStateInsideForEachSS(S, false);
  }

#endif

}

/* Function to initialize sample times. */
static void mdlInitializeSampleTimes(SimStruct *S)
{
  /* task periods */
  ssSetSampleTime(S, 0, 0.01);
  ssSetSampleTime(S, 1, 0.2);

  /* task offsets */
  ssSetOffsetTime(S, 0, 0.0);
  ssSetOffsetTime(S, 1, 0.0);
}

#if defined(MATLAB_MEX_FILE)
# include "fixedpoint.c"
# include "simulink.c"
#else
# undef S_FUNCTION_NAME
# define S_FUNCTION_NAME               State_sf
# include "cg_sfun.h"
#endif                                 /* defined(MATLAB_MEX_FILE) */
