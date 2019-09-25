/*
 * Autopilot_sf.c
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "Autopilot_sf".
 *
 * Model version              : 1.336
 * Simulink Coder version : 8.14 (R2018a) 06-Feb-2018
 * C source code generated on : Tue Sep 24 13:43:18 2019
 *
 * Target selection: rtwsfcn.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <math.h>
#include "Autopilot_sf.h"
#include "Autopilot_sf_private.h"
#include "simstruc.h"
#include "fixedpoint.h"

/* Named constants for Chart: '<S1>/Altitude Control State Machine' */
#define Autopilot_IN_Altitude_Hold_Zone ((uint8_T)1U)
#define Autopilot_IN_Climb_Zone        ((uint8_T)2U)
#define Autopilot_IN_Descend_Zone      ((uint8_T)3U)
#define Autopilot_IN_Landing_Mode      ((uint8_T)4U)
#define Autopilot_IN_Pre_Flight        ((uint8_T)5U)
#define Autopilot_IN_Take_Off_Zone     ((uint8_T)6U)
#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)

extern void *Autopilot_malloc(SimStruct *S);

#endif

#ifndef __RTW_UTFREE__
#if defined (MATLAB_MEX_FILE)

extern void * utMalloc(size_t);
extern void utFree(void *);

#endif
#endif                                 /* #ifndef __RTW_UTFREE__ */

#if defined(MATLAB_MEX_FILE)
#include "rt_nonfinite.c"
#endif

static const char_T *RT_MEMORY_ALLOCATION_ERROR =
  "memory allocation error in generated S-Function";
real_T Autopilot_look1_binlxpw(real_T u0, const real_T bp0[], const real_T
  table[], uint32_T maxIndex)
{
  real_T frac;
  uint32_T iRght;
  uint32_T iLeft;
  uint32_T bpIdx;

  /* Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex]) {
    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = (u0 - bp0[maxIndex - 1U]) / (bp0[maxIndex] - bp0[maxIndex - 1U]);
  }

  /* Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  return (table[iLeft + 1U] - table[iLeft]) * frac + table[iLeft];
}

real_T Autopilot_look2_binlxpw(real_T u0, real_T u1, const real_T bp0[], const
  real_T bp1[], const real_T table[], const uint32_T maxIndex[], uint32_T stride)
{
  real_T frac;
  uint32_T bpIndices[2];
  real_T fractions[2];
  real_T yL_1d;
  uint32_T iRght;
  uint32_T bpIdx;
  uint32_T iLeft;

  /* Lookup 2-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex[0U]]) {
    /* Binary Search */
    bpIdx = maxIndex[0U] >> 1U;
    iLeft = 0U;
    iRght = maxIndex[0U];
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex[0U] - 1U;
    frac = (u0 - bp0[maxIndex[0U] - 1U]) / (bp0[maxIndex[0U]] - bp0[maxIndex[0U]
      - 1U]);
  }

  fractions[0U] = frac;
  bpIndices[0U] = iLeft;

  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u1 <= bp1[0U]) {
    iLeft = 0U;
    frac = (u1 - bp1[0U]) / (bp1[1U] - bp1[0U]);
  } else if (u1 < bp1[maxIndex[1U]]) {
    /* Binary Search */
    bpIdx = maxIndex[1U] >> 1U;
    iLeft = 0U;
    iRght = maxIndex[1U];
    while (iRght - iLeft > 1U) {
      if (u1 < bp1[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u1 - bp1[iLeft]) / (bp1[iLeft + 1U] - bp1[iLeft]);
  } else {
    iLeft = maxIndex[1U] - 1U;
    frac = (u1 - bp1[maxIndex[1U] - 1U]) / (bp1[maxIndex[1U]] - bp1[maxIndex[1U]
      - 1U]);
  }

  /* Interpolation 2-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  bpIdx = iLeft * stride + bpIndices[0U];
  yL_1d = (table[bpIdx + 1U] - table[bpIdx]) * fractions[0U] + table[bpIdx];
  bpIdx += stride;
  return (((table[bpIdx + 1U] - table[bpIdx]) * fractions[0U] + table[bpIdx]) -
          yL_1d) * frac + yL_1d;
}

real_T Autopilot_look2_pbinlxpw(real_T u0, real_T u1, const real_T bp0[], const
  real_T bp1[], const real_T table[], uint32_T prevIndex[], const uint32_T
  maxIndex[], uint32_T stride)
{
  real_T frac;
  uint32_T bpIndices[2];
  real_T fractions[2];
  real_T yL_1d;
  uint32_T iRght;
  uint32_T iLeft;
  uint32_T found;
  uint32_T bpIdx;

  /* Lookup 2-D
     Search method: 'binary'
     Use previous index: 'on'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'on'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    bpIdx = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex[0U]]) {
    /* Binary Search using Previous Index */
    bpIdx = prevIndex[0U];
    iLeft = 0U;
    iRght = maxIndex[0U];
    found = 0U;
    while (found == 0U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx - 1U;
        bpIdx = (iRght + iLeft) >> 1U;
      } else if (u0 < bp0[bpIdx + 1U]) {
        found = 1U;
      } else {
        iLeft = bpIdx + 1U;
        bpIdx = (iRght + iLeft) >> 1U;
      }
    }

    frac = (u0 - bp0[bpIdx]) / (bp0[bpIdx + 1U] - bp0[bpIdx]);
  } else {
    bpIdx = maxIndex[0U] - 1U;
    frac = (u0 - bp0[maxIndex[0U] - 1U]) / (bp0[maxIndex[0U]] - bp0[maxIndex[0U]
      - 1U]);
  }

  prevIndex[0U] = bpIdx;
  fractions[0U] = frac;
  bpIndices[0U] = bpIdx;

  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'on'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u1 <= bp1[0U]) {
    bpIdx = 0U;
    frac = (u1 - bp1[0U]) / (bp1[1U] - bp1[0U]);
  } else if (u1 < bp1[maxIndex[1U]]) {
    /* Binary Search using Previous Index */
    bpIdx = prevIndex[1U];
    iLeft = 0U;
    iRght = maxIndex[1U];
    found = 0U;
    while (found == 0U) {
      if (u1 < bp1[bpIdx]) {
        iRght = bpIdx - 1U;
        bpIdx = (iRght + iLeft) >> 1U;
      } else if (u1 < bp1[bpIdx + 1U]) {
        found = 1U;
      } else {
        iLeft = bpIdx + 1U;
        bpIdx = (iRght + iLeft) >> 1U;
      }
    }

    frac = (u1 - bp1[bpIdx]) / (bp1[bpIdx + 1U] - bp1[bpIdx]);
  } else {
    bpIdx = maxIndex[1U] - 1U;
    frac = (u1 - bp1[maxIndex[1U] - 1U]) / (bp1[maxIndex[1U]] - bp1[maxIndex[1U]
      - 1U]);
  }

  prevIndex[1U] = bpIdx;

  /* Interpolation 2-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  iLeft = bpIdx * stride + bpIndices[0U];
  yL_1d = (table[iLeft + 1U] - table[iLeft]) * fractions[0U] + table[iLeft];
  iLeft += stride;
  return (((table[iLeft + 1U] - table[iLeft]) * fractions[0U] + table[iLeft]) -
          yL_1d) * frac + yL_1d;
}

/* System initialize for root system: '<Root>' */
#define MDL_INITIALIZE_CONDITIONS

static void mdlInitializeConditions(SimStruct *S)
{
  if (ssIsFirstInitCond(S)) {
    /* InitializeConditions for Memory: '<S21>/Memory' */
    ((boolean_T *)ssGetDWork(S, 21))[0] = false;

    /* InitializeConditions for Delay: '<S20>/Delay' */
    ((real_T *)ssGetDWork(S, 0))[0] = 0.504;

    /* InitializeConditions for UnitDelay: '<S1>/Unit Delay1' */
    ((real_T *)ssGetDWork(S, 1))[0] = 0.504;

    /* InitializeConditions for DiscreteIntegrator: '<S20>/Discrete-Time Integrator' */
    ((real_T *)ssGetDWork(S, 2))[0] = 0.504;

    /* InitializeConditions for DiscreteIntegrator: '<S20>/Discrete-Time Integrator1' */
    ((real_T *)ssGetDWork(S, 3))[0] = 0.0;

    /* InitializeConditions for Memory: '<S23>/Memory' */
    ((boolean_T *)ssGetDWork(S, 22))[0] = false;

    /* InitializeConditions for Delay: '<S22>/Delay' */
    ((real_T *)ssGetDWork(S, 4))[0] = -0.0288;

    /* InitializeConditions for UnitDelay: '<S1>/Unit Delay' */
    ((real_T *)ssGetDWork(S, 5))[0] = 0.0288;

    /* InitializeConditions for DiscreteIntegrator: '<S22>/Discrete-Time Integrator' */
    ((real_T *)ssGetDWork(S, 6))[0] = -0.0288;

    /* InitializeConditions for DiscreteIntegrator: '<S22>/Discrete-Time Integrator1' */
    ((real_T *)ssGetDWork(S, 7))[0] = 0.0;

    /* InitializeConditions for UnitDelay: '<S9>/Delay Input2' */
    ((real_T *)ssGetDWork(S, 8))[0] = 100.0;

    /* InitializeConditions for Memory: '<S25>/Memory' */
    ((boolean_T *)ssGetDWork(S, 23))[0] = false;

    /* InitializeConditions for Delay: '<S24>/Delay' */
    ((real_T *)ssGetDWork(S, 9))[0] = 0.0288;

    /* InitializeConditions for DiscreteIntegrator: '<S24>/Discrete-Time Integrator' */
    ((real_T *)ssGetDWork(S, 10))[0] = 0.0288;

    /* InitializeConditions for DiscreteIntegrator: '<S24>/Discrete-Time Integrator1' */
    ((real_T *)ssGetDWork(S, 11))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S17>/Discrete-Time Integrator' */
    ((real_T *)ssGetDWork(S, 12))[0] = 0.014770254596539677;

    /* InitializeConditions for Memory: '<S19>/Memory' */
    ((boolean_T *)ssGetDWork(S, 26))[0] = false;

    /* InitializeConditions for DiscreteIntegrator: '<S18>/Discrete-Time Integrator' */
    ((real_T *)ssGetDWork(S, 13))[0] = -0.12413622923378378;

    /* InitializeConditions for DiscreteIntegrator: '<S16>/Discrete-Time Integrator' */
    ((real_T *)ssGetDWork(S, 14))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S13>/Discrete-Time Integrator' */
    ((real_T *)ssGetDWork(S, 15))[0] = 0.0;

    /* InitializeConditions for Memory: '<S15>/Memory' */
    ((boolean_T *)ssGetDWork(S, 27))[0] = false;

    /* InitializeConditions for Memory: '<S11>/Memory' */
    ((boolean_T *)ssGetDWork(S, 28))[0] = false;

    /* InitializeConditions for DiscreteIntegrator: '<S10>/Discrete-Time Integrator' */
    ((real_T *)ssGetDWork(S, 16))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S14>/Discrete-Time Integrator' */
    ((real_T *)ssGetDWork(S, 17))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S12>/Discrete-Time Integrator' */
    ((real_T *)ssGetDWork(S, 18))[0] = 0.0;

    /* Chart: '<S1>/Altitude Control State Machine' */
    ((uint8_T *)ssGetDWork(S, 20))[0] = Autopilot_IN_Pre_Flight;
  } else {                             /* InitializeConditions for Memory: '<S21>/Memory' */
    ((boolean_T *)ssGetDWork(S, 21))[0] = false;

    /* InitializeConditions for Delay: '<S20>/Delay' */
    ((real_T *)ssGetDWork(S, 0))[0] = 0.504;

    /* InitializeConditions for UnitDelay: '<S1>/Unit Delay1' */
    ((real_T *)ssGetDWork(S, 1))[0] = 0.504;

    /* InitializeConditions for DiscreteIntegrator: '<S20>/Discrete-Time Integrator' */
    ((real_T *)ssGetDWork(S, 2))[0] = 0.504;

    /* InitializeConditions for DiscreteIntegrator: '<S20>/Discrete-Time Integrator1' */
    ((real_T *)ssGetDWork(S, 3))[0] = 0.0;

    /* InitializeConditions for Memory: '<S23>/Memory' */
    ((boolean_T *)ssGetDWork(S, 22))[0] = false;

    /* InitializeConditions for Delay: '<S22>/Delay' */
    ((real_T *)ssGetDWork(S, 4))[0] = -0.0288;

    /* InitializeConditions for UnitDelay: '<S1>/Unit Delay' */
    ((real_T *)ssGetDWork(S, 5))[0] = 0.0288;

    /* InitializeConditions for DiscreteIntegrator: '<S22>/Discrete-Time Integrator' */
    ((real_T *)ssGetDWork(S, 6))[0] = -0.0288;

    /* InitializeConditions for DiscreteIntegrator: '<S22>/Discrete-Time Integrator1' */
    ((real_T *)ssGetDWork(S, 7))[0] = 0.0;

    /* InitializeConditions for UnitDelay: '<S9>/Delay Input2' */
    ((real_T *)ssGetDWork(S, 8))[0] = 100.0;

    /* InitializeConditions for Memory: '<S25>/Memory' */
    ((boolean_T *)ssGetDWork(S, 23))[0] = false;

    /* InitializeConditions for Delay: '<S24>/Delay' */
    ((real_T *)ssGetDWork(S, 9))[0] = 0.0288;

    /* InitializeConditions for DiscreteIntegrator: '<S24>/Discrete-Time Integrator' */
    ((real_T *)ssGetDWork(S, 10))[0] = 0.0288;

    /* InitializeConditions for DiscreteIntegrator: '<S24>/Discrete-Time Integrator1' */
    ((real_T *)ssGetDWork(S, 11))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S17>/Discrete-Time Integrator' */
    ((real_T *)ssGetDWork(S, 12))[0] = 0.014770254596539677;

    /* InitializeConditions for Memory: '<S19>/Memory' */
    ((boolean_T *)ssGetDWork(S, 26))[0] = false;

    /* InitializeConditions for DiscreteIntegrator: '<S18>/Discrete-Time Integrator' */
    ((real_T *)ssGetDWork(S, 13))[0] = -0.12413622923378378;

    /* InitializeConditions for DiscreteIntegrator: '<S16>/Discrete-Time Integrator' */
    ((real_T *)ssGetDWork(S, 14))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S13>/Discrete-Time Integrator' */
    ((real_T *)ssGetDWork(S, 15))[0] = 0.0;

    /* InitializeConditions for Memory: '<S15>/Memory' */
    ((boolean_T *)ssGetDWork(S, 27))[0] = false;

    /* InitializeConditions for Memory: '<S11>/Memory' */
    ((boolean_T *)ssGetDWork(S, 28))[0] = false;

    /* InitializeConditions for DiscreteIntegrator: '<S10>/Discrete-Time Integrator' */
    ((real_T *)ssGetDWork(S, 16))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S14>/Discrete-Time Integrator' */
    ((real_T *)ssGetDWork(S, 17))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S12>/Discrete-Time Integrator' */
    ((real_T *)ssGetDWork(S, 18))[0] = 0.0;

    /* Chart: '<S1>/Altitude Control State Machine' */
    ((uint8_T *)ssGetDWork(S, 20))[0] = Autopilot_IN_Pre_Flight;
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

  Autopilot_malloc(S);
  if (ssGetErrorStatus(S) != (NULL) ) {
    return;
  }

#endif

  {
    /* Start for InitialCondition: '<S1>/IC' */
    ((boolean_T *)ssGetDWork(S, 24))[0] = true;

    /* Start for InitialCondition: '<S1>/IC1' */
    ((boolean_T *)ssGetDWork(S, 25))[0] = true;
  }
}

/* Outputs for root system: '<Root>' */
static void mdlOutputs(SimStruct *S, int_T tid)
{
  real_T rtb_Sum2_m;
  real_T rtb_Va_e;
  real_T rtb_PIDFControllerVa_dtKiLookup;
  real_T rtb_DiscreteTimeIntegrator1_h;
  real_T rtb_da;
  real_T rtb_Chi_e;
  real_T rtb_PIDFControllerPhiN2DLookupT;
  real_T rtb_Phi_e;
  real_T der_tmp;
  B_Autopilot_T *_rtB;
  _rtB = ((B_Autopilot_T *) ssGetLocalBlockIO(S));

  /* Sum: '<S1>/Sum4' */
  rtb_Va_e = *((const real_T **)ssGetInputPortSignalPtrs(S, 0))[0] - *((const
    real_T **)ssGetInputPortSignalPtrs(S, 3))[0];

  /* Lookup_n-D: '<S6>/PIDF Controller Va_dt Ki Lookup Table' */
  rtb_PIDFControllerVa_dtKiLookup = Autopilot_look1_binlxpw(*((const real_T **)
    ssGetInputPortSignalPtrs(S, 3))[0], Autopilot_ConstP.pooled1,
    Autopilot_ConstP.PIDFControllerVa_dtKiLookupTabl, 9U);

  /* Switch: '<S20>/Clamp Switch' incorporates:
   *  Constant: '<S20>/Constant'
   *  Memory: '<S21>/Memory'
   *  Product: '<S20>/IOut'
   */
  if (((boolean_T *)ssGetDWork(S, 21))[0]) {
    rtb_DiscreteTimeIntegrator1_h = 0.0;
  } else {
    rtb_DiscreteTimeIntegrator1_h = rtb_PIDFControllerVa_dtKiLookup * rtb_Va_e;
  }

  /* End of Switch: '<S20>/Clamp Switch' */

  /* Sum: '<S20>/Sum1' incorporates:
   *  Delay: '<S20>/Delay'
   *  Gain: '<S6>/PIDF Controller Va_dt Kt Tracking Gain Scalar'
   *  Product: '<S20>/Tracking'
   *  Sum: '<S20>/Sum3'
   *  UnitDelay: '<S1>/Unit Delay1'
   */
  _rtB->Sum1 = (((real_T *)ssGetDWork(S, 1))[0] - ((real_T *)ssGetDWork(S, 0))[0])
    * (10.0 * rtb_PIDFControllerVa_dtKiLookup) + rtb_DiscreteTimeIntegrator1_h;

  /* DiscreteIntegrator: '<S20>/Discrete-Time Integrator' */
  _rtB->DiscreteTimeIntegrator = 0.005 * _rtB->Sum1 + ((real_T *)ssGetDWork(S, 2))
    [0];

  /* Product: '<S20>/Product1' incorporates:
   *  DiscreteIntegrator: '<S20>/Discrete-Time Integrator1'
   *  Lookup_n-D: '<S6>/PIDF Controller Va_dt Kd Lookup Table'
   *  Lookup_n-D: '<S6>/PIDF Controller Va_dt N Lookup Table'
   *  Product: '<S20>/Product'
   *  Sum: '<S20>/Sum'
   */
  _rtB->Product1 = (rtb_Va_e * Autopilot_look1_binlxpw(*((const real_T **)
    ssGetInputPortSignalPtrs(S, 3))[0], Autopilot_ConstP.pooled1,
    Autopilot_ConstP.PIDFControllerVa_dtKdLookupTabl, 9U) - ((real_T *)
    ssGetDWork(S, 3))[0]) * Autopilot_look1_binlxpw(*((const real_T **)
    ssGetInputPortSignalPtrs(S, 3))[0], Autopilot_ConstP.pooled1,
    Autopilot_ConstP.PIDFControllerVa_dtNLookupTable, 9U);

  /* Sum: '<S20>/Sum2' incorporates:
   *  Lookup_n-D: '<S6>/PIDF Controller Va_dt Kp Lookup Table'
   *  Product: '<S20>/POut'
   */
  rtb_Sum2_m = (Autopilot_look1_binlxpw(*((const real_T **)
    ssGetInputPortSignalPtrs(S, 3))[0], Autopilot_ConstP.pooled1,
    Autopilot_ConstP.PIDFControllerVa_dtKpLookupTabl, 9U) * rtb_Va_e +
                _rtB->DiscreteTimeIntegrator) + _rtB->Product1;

  /* Saturate: '<S20>/Saturation' */
  if (rtb_Sum2_m > 1.0) {
    _rtB->Saturation = 1.0;
  } else if (rtb_Sum2_m < 0.0) {
    _rtB->Saturation = 0.0;
  } else {
    _rtB->Saturation = rtb_Sum2_m;
  }

  /* End of Saturate: '<S20>/Saturation' */

  /* Switch: '<S22>/Clamp Switch' incorporates:
   *  Constant: '<S22>/Constant'
   *  Delay: '<S22>/Delay'
   *  Gain: '<S7>/PIDF Controller Va_theta Kt Tracking Gain Scalar'
   *  Gain: '<S7>/Tracking Sign Inversion'
   *  Memory: '<S23>/Memory'
   *  Product: '<S22>/IOut'
   *  Product: '<S22>/Tracking'
   *  Sum: '<S22>/Sum1'
   *  Sum: '<S22>/Sum3'
   *  UnitDelay: '<S1>/Unit Delay'
   */
  if (((boolean_T *)ssGetDWork(S, 22))[0]) {
    _rtB->ClampSwitch = 0.0;
  } else {
    /* Lookup_n-D: '<S7>/PIDF Controller Va_theta Ki 2D Lookup Table' */
    rtb_PIDFControllerVa_dtKiLookup = Autopilot_look2_binlxpw(*((const real_T **)
      ssGetInputPortSignalPtrs(S, 3))[0], *((const real_T **)
      ssGetInputPortSignalPtrs(S, 6))[0], Autopilot_ConstP.pooled1,
      Autopilot_ConstP.pooled2, Autopilot_ConstP.PIDFControllerVa_thetaKi2DLooku,
      Autopilot_ConstP.pooled14, 10U);
    _rtB->ClampSwitch = (-((real_T *)ssGetDWork(S, 5))[0] - ((real_T *)
      ssGetDWork(S, 4))[0]) * (10.0 * rtb_PIDFControllerVa_dtKiLookup) +
      rtb_PIDFControllerVa_dtKiLookup * rtb_Va_e;
  }

  /* End of Switch: '<S22>/Clamp Switch' */

  /* DiscreteIntegrator: '<S22>/Discrete-Time Integrator' */
  _rtB->DiscreteTimeIntegrator_k = 0.005 * _rtB->ClampSwitch + ((real_T *)
    ssGetDWork(S, 6))[0];

  /* Product: '<S22>/Product1' incorporates:
   *  DiscreteIntegrator: '<S22>/Discrete-Time Integrator1'
   *  Lookup_n-D: '<S7>/PIDF Controller Va_theta Kd 2D Lookup Table'
   *  Lookup_n-D: '<S7>/PIDF Controller Va_theta N 2D Lookup Table'
   *  Product: '<S22>/Product'
   *  Sum: '<S22>/Sum'
   */
  _rtB->Product1_c = (rtb_Va_e * Autopilot_look2_binlxpw(*((const real_T **)
    ssGetInputPortSignalPtrs(S, 3))[0], *((const real_T **)
    ssGetInputPortSignalPtrs(S, 6))[0], Autopilot_ConstP.pooled1,
    Autopilot_ConstP.pooled2, Autopilot_ConstP.PIDFControllerVa_thetaKd2DLooku,
    Autopilot_ConstP.pooled14, 10U) - ((real_T *)ssGetDWork(S, 7))[0]) *
    Autopilot_look2_binlxpw(*((const real_T **)ssGetInputPortSignalPtrs(S, 3))[0],
    *((const real_T **)ssGetInputPortSignalPtrs(S, 6))[0],
    Autopilot_ConstP.pooled1, Autopilot_ConstP.pooled2,
    Autopilot_ConstP.PIDFControllerVa_thetaN2DLookup, Autopilot_ConstP.pooled14,
    10U);

  /* Sum: '<S22>/Sum2' incorporates:
   *  Lookup_n-D: '<S7>/PIDF Controller Va_theta Kp 2D Lookup Table'
   *  Product: '<S22>/POut'
   */
  _rtB->Sum2 = (Autopilot_look2_binlxpw(*((const real_T **)
    ssGetInputPortSignalPtrs(S, 3))[0], *((const real_T **)
    ssGetInputPortSignalPtrs(S, 6))[0], Autopilot_ConstP.pooled1,
    Autopilot_ConstP.pooled2, Autopilot_ConstP.PIDFControllerVa_thetaKp2DLooku,
    Autopilot_ConstP.pooled14, 10U) * rtb_Va_e + _rtB->DiscreteTimeIntegrator_k)
    + _rtB->Product1_c;

  /* Product: '<S9>/delta rise limit' incorporates:
   *  Gain: '<S1>/Gain1'
   *  SampleTimeMath: '<S9>/sample time'
   *
   * About '<S9>/sample time':
   *  y = K where K = ( w * Ts )
   */
  rtb_DiscreteTimeIntegrator1_h = 0.49999999999999994 * *((const real_T **)
    ssGetInputPortSignalPtrs(S, 3))[0] * 0.01;

  /* Sum: '<S9>/Difference Inputs1' incorporates:
   *  UnitDelay: '<S9>/Delay Input2'
   */
  rtb_Va_e = *((const real_T **)ssGetInputPortSignalPtrs(S, 1))[0] - ((real_T *)
    ssGetDWork(S, 8))[0];

  /* Switch: '<S26>/Switch2' incorporates:
   *  RelationalOperator: '<S26>/LowerRelop1'
   */
  if (!(rtb_Va_e > rtb_DiscreteTimeIntegrator1_h)) {
    /* Product: '<S9>/delta fall limit' incorporates:
     *  Gain: '<S1>/Gain'
     *  SampleTimeMath: '<S9>/sample time'
     *
     * About '<S9>/sample time':
     *  y = K where K = ( w * Ts )
     */
    rtb_DiscreteTimeIntegrator1_h = -0.49999999999999994 * *((const real_T **)
      ssGetInputPortSignalPtrs(S, 3))[0] * 0.01;

    /* Switch: '<S26>/Switch' incorporates:
     *  RelationalOperator: '<S26>/UpperRelop'
     */
    if (!(rtb_Va_e < rtb_DiscreteTimeIntegrator1_h)) {
      rtb_DiscreteTimeIntegrator1_h = rtb_Va_e;
    }

    /* End of Switch: '<S26>/Switch' */
  }

  /* End of Switch: '<S26>/Switch2' */

  /* Sum: '<S9>/Difference Inputs2' incorporates:
   *  UnitDelay: '<S9>/Delay Input2'
   */
  _rtB->DifferenceInputs2 = rtb_DiscreteTimeIntegrator1_h + ((real_T *)
    ssGetDWork(S, 8))[0];

  /* Sum: '<S1>/Sum3' */
  rtb_Va_e = _rtB->DifferenceInputs2 - *((const real_T **)
    ssGetInputPortSignalPtrs(S, 4))[0];

  /* Switch: '<S24>/Clamp Switch' incorporates:
   *  Constant: '<S24>/Constant'
   *  Constant: '<S8>/Ki'
   *  Constant: '<S8>/Kt'
   *  Delay: '<S24>/Delay'
   *  Memory: '<S25>/Memory'
   *  Product: '<S24>/IOut'
   *  Product: '<S24>/Tracking'
   *  Sum: '<S24>/Sum1'
   *  Sum: '<S24>/Sum3'
   *  UnitDelay: '<S1>/Unit Delay'
   */
  if (((boolean_T *)ssGetDWork(S, 23))[0]) {
    _rtB->ClampSwitch_p = 0.0;
  } else {
    _rtB->ClampSwitch_p = (((real_T *)ssGetDWork(S, 5))[0] - ((real_T *)
      ssGetDWork(S, 9))[0]) * 0.20506663686066096 + 0.020506663686066094 *
      rtb_Va_e;
  }

  /* End of Switch: '<S24>/Clamp Switch' */

  /* DiscreteIntegrator: '<S24>/Discrete-Time Integrator' */
  _rtB->DiscreteTimeIntegrator_g = 0.005 * _rtB->ClampSwitch_p + ((real_T *)
    ssGetDWork(S, 10))[0];

  /* Product: '<S24>/Product1' incorporates:
   *  Constant: '<S8>/Kd'
   *  Constant: '<S8>/N'
   *  DiscreteIntegrator: '<S24>/Discrete-Time Integrator1'
   *  Product: '<S24>/Product'
   *  Sum: '<S24>/Sum'
   */
  _rtB->theta_c = (rtb_Va_e * 0.056480531489874995 - ((real_T *)ssGetDWork(S, 11))
                   [0]) * 0.2725332771388489;

  /* Sum: '<S24>/Sum2' incorporates:
   *  Constant: '<S8>/Kp'
   *  Product: '<S24>/POut'
   */
  rtb_Va_e = (0.10293969697280446 * rtb_Va_e + _rtB->DiscreteTimeIntegrator_g) +
    _rtB->theta_c;

  /* Saturate: '<S24>/Saturation' */
  if (rtb_Va_e > 1.0471975511965976) {
    _rtB->Saturation_c = 1.0471975511965976;
  } else if (rtb_Va_e < -1.0471975511965976) {
    _rtB->Saturation_c = -1.0471975511965976;
  } else {
    _rtB->Saturation_c = rtb_Va_e;
  }

  /* End of Saturate: '<S24>/Saturation' */

  /* Chart: '<S1>/Altitude Control State Machine' incorporates:
   *  Gain: '<S7>/Sign Inversion'
   */
  switch (((uint8_T *)ssGetDWork(S, 20))[0]) {
   case Autopilot_IN_Altitude_Hold_Zone:
    if (*((const real_T **)ssGetInputPortSignalPtrs(S, 4))[0] <
        _rtB->DifferenceInputs2 - 95.0) {
      ((uint8_T *)ssGetDWork(S, 20))[0] = Autopilot_IN_Climb_Zone;
    } else if (*((const real_T **)ssGetInputPortSignalPtrs(S, 4))[0] >=
               _rtB->DifferenceInputs2 + 105.0) {
      ((uint8_T *)ssGetDWork(S, 20))[0] = Autopilot_IN_Descend_Zone;
    } else if (_rtB->DifferenceInputs2 == 0.0) {
      ((uint8_T *)ssGetDWork(S, 20))[0] = Autopilot_IN_Landing_Mode;
    } else {
      _rtB->dt = _rtB->Saturation;
      _rtB->theta_c_f = _rtB->Saturation_c;
    }
    break;

   case Autopilot_IN_Climb_Zone:
    if (*((const real_T **)ssGetInputPortSignalPtrs(S, 4))[0] < 9.5) {
      ((uint8_T *)ssGetDWork(S, 20))[0] = Autopilot_IN_Take_Off_Zone;
    } else if (*((const real_T **)ssGetInputPortSignalPtrs(S, 4))[0] >=
               _rtB->DifferenceInputs2 - 105.0) {
      ((uint8_T *)ssGetDWork(S, 20))[0] = Autopilot_IN_Altitude_Hold_Zone;
    } else if (_rtB->DifferenceInputs2 == 0.0) {
      ((uint8_T *)ssGetDWork(S, 20))[0] = Autopilot_IN_Landing_Mode;
    } else {
      _rtB->dt = 1.0;
      _rtB->theta_c_f = -_rtB->Sum2;
    }
    break;

   case Autopilot_IN_Descend_Zone:
    if (*((const real_T **)ssGetInputPortSignalPtrs(S, 4))[0] <
        _rtB->DifferenceInputs2 + 95.0) {
      ((uint8_T *)ssGetDWork(S, 20))[0] = Autopilot_IN_Altitude_Hold_Zone;
    } else if (_rtB->DifferenceInputs2 == 0.0) {
      ((uint8_T *)ssGetDWork(S, 20))[0] = Autopilot_IN_Landing_Mode;
    } else {
      _rtB->dt = 0.0;
      _rtB->theta_c_f = -_rtB->Sum2;
    }
    break;

   case Autopilot_IN_Landing_Mode:
    if (*((const real_T **)ssGetInputPortSignalPtrs(S, 4))[0] == 0.0) {
      ((uint8_T *)ssGetDWork(S, 20))[0] = Autopilot_IN_Pre_Flight;
    } else {
      _rtB->dt = 0.0;
      _rtB->theta_c_f = _rtB->Saturation_c;
    }
    break;

   case Autopilot_IN_Pre_Flight:
    ((uint8_T *)ssGetDWork(S, 20))[0] = Autopilot_IN_Altitude_Hold_Zone;
    break;

   default:
    if (*((const real_T **)ssGetInputPortSignalPtrs(S, 4))[0] >= 10.5) {
      ((uint8_T *)ssGetDWork(S, 20))[0] = Autopilot_IN_Climb_Zone;
    } else if (_rtB->DifferenceInputs2 == 0.0) {
      ((uint8_T *)ssGetDWork(S, 20))[0] = Autopilot_IN_Landing_Mode;
    } else {
      _rtB->dt = 1.0;
      _rtB->theta_c_f = 0.52359877559829882;
    }
    break;
  }

  /* End of Chart: '<S1>/Altitude Control State Machine' */

  /* InitialCondition: '<S1>/IC' */
  if (((boolean_T *)ssGetDWork(S, 24))[0]) {
    ((boolean_T *)ssGetDWork(S, 24))[0] = false;
    _rtB->IC = 0.504;
  } else {
    _rtB->IC = _rtB->dt;
  }

  /* End of InitialCondition: '<S1>/IC' */

  /* Outport: '<Root>/dt' */
  ((real_T *)ssGetOutputPortSignal(S, 0))[0] = _rtB->IC;

  /* InitialCondition: '<S1>/IC1' */
  if (((boolean_T *)ssGetDWork(S, 25))[0]) {
    ((boolean_T *)ssGetDWork(S, 25))[0] = false;
    _rtB->theta_c_m = 0.0288;
  } else {
    _rtB->theta_c_m = _rtB->theta_c_f;
  }

  /* End of InitialCondition: '<S1>/IC1' */

  /* Lookup_n-D: '<S5>/PDF Controller theta 2DOF Kd 2D Lookup Table' */
  rtb_PIDFControllerVa_dtKiLookup = Autopilot_look2_pbinlxpw(*((const real_T **)
    ssGetInputPortSignalPtrs(S, 3))[0], *((const real_T **)
    ssGetInputPortSignalPtrs(S, 6))[0], Autopilot_ConstP.pooled1,
    Autopilot_ConstP.pooled2, Autopilot_ConstP.PDFControllertheta2DOFKd2DLooku,
    &((uint32_T *)ssGetDWork(S, 19))[0], Autopilot_ConstP.pooled14, 10U);

  /* Product: '<S17>/Product1' incorporates:
   *  DiscreteIntegrator: '<S17>/Discrete-Time Integrator'
   *  Lookup_n-D: '<S5>/PDF Controller theta 2DOF N 2D Lookup Table'
   *  Product: '<S17>/Product'
   *  Sum: '<S17>/Sum'
   */
  _rtB->Product1_k = (_rtB->theta_c_m * rtb_PIDFControllerVa_dtKiLookup -
                      ((real_T *)ssGetDWork(S, 12))[0]) *
    Autopilot_look2_binlxpw(*((const real_T **)ssGetInputPortSignalPtrs(S, 3))[0],
    *((const real_T **)ssGetInputPortSignalPtrs(S, 6))[0],
    Autopilot_ConstP.pooled1, Autopilot_ConstP.pooled2,
    Autopilot_ConstP.PDFControllertheta2DOFN2DLookup, Autopilot_ConstP.pooled14,
    10U);

  /* Switch: '<S1>/Switch2' incorporates:
   *  Abs: '<S1>/Abs2'
   *  Constant: '<S1>/Constant4'
   */
  if (fabs(*((const real_T **)ssGetInputPortSignalPtrs(S, 5))[0]) >
      0.0017453292519943296) {
    rtb_DiscreteTimeIntegrator1_h = *((const real_T **)ssGetInputPortSignalPtrs
      (S, 5))[0];
  } else {
    rtb_DiscreteTimeIntegrator1_h = 0.0;
  }

  /* End of Switch: '<S1>/Switch2' */

  /* Sum: '<S1>/Sum1' */
  rtb_PIDFControllerVa_dtKiLookup = _rtB->theta_c_m -
    rtb_DiscreteTimeIntegrator1_h;

  /* Switch: '<S18>/Clamp Switch' incorporates:
   *  Constant: '<S18>/Constant'
   *  Lookup_n-D: '<S5>/PIDF Controller theta Ki 2D Lookup Table'
   *  Memory: '<S19>/Memory'
   *  Product: '<S18>/IOut'
   */
  if (((boolean_T *)ssGetDWork(S, 26))[0]) {
    _rtB->ClampSwitch_c = 0.0;
  } else {
    _rtB->ClampSwitch_c = Autopilot_look2_binlxpw(*((const real_T **)
      ssGetInputPortSignalPtrs(S, 3))[0], *((const real_T **)
      ssGetInputPortSignalPtrs(S, 6))[0], Autopilot_ConstP.pooled1,
      Autopilot_ConstP.pooled2, Autopilot_ConstP.PIDFControllerthetaKi2DLookupTa,
      Autopilot_ConstP.pooled14, 10U) * rtb_PIDFControllerVa_dtKiLookup;
  }

  /* End of Switch: '<S18>/Clamp Switch' */

  /* DiscreteIntegrator: '<S18>/Discrete-Time Integrator' */
  _rtB->DiscreteTimeIntegrator_f = 0.005 * _rtB->ClampSwitch_c + ((real_T *)
    ssGetDWork(S, 13))[0];

  /* Sum: '<S5>/Sum1' incorporates:
   *  DiscreteIntegrator: '<S16>/Discrete-Time Integrator'
   *  Lookup_n-D: '<S5>/PDF Controller theta 2DOF Kp 2D Lookup Table'
   *  Lookup_n-D: '<S5>/PIDF Controller theta Kp 2D Lookup Table'
   *  Product: '<S17>/POut'
   *  Product: '<S18>/POut'
   *  Sum: '<S17>/Sum2'
   *  Sum: '<S18>/Sum2'
   */
  rtb_PIDFControllerVa_dtKiLookup = ((Autopilot_look2_binlxpw(*((const real_T **)
    ssGetInputPortSignalPtrs(S, 3))[0], *((const real_T **)
    ssGetInputPortSignalPtrs(S, 6))[0], Autopilot_ConstP.pooled1,
    Autopilot_ConstP.pooled2, Autopilot_ConstP.PDFControllertheta2DOFKp2DLooku,
    Autopilot_ConstP.pooled14, 10U) * _rtB->theta_c_m + _rtB->Product1_k) +
    (rtb_PIDFControllerVa_dtKiLookup * Autopilot_look2_binlxpw(*((const real_T **)
    ssGetInputPortSignalPtrs(S, 3))[0], *((const real_T **)
    ssGetInputPortSignalPtrs(S, 6))[0], Autopilot_ConstP.pooled1,
    Autopilot_ConstP.pooled2, Autopilot_ConstP.PIDFControllerthetaKp2DLookupTa,
    Autopilot_ConstP.pooled14, 10U) + _rtB->DiscreteTimeIntegrator_f)) +
    ((real_T *)ssGetDWork(S, 14))[0];

  /* Saturate: '<S5>/Saturation' */
  if (rtb_PIDFControllerVa_dtKiLookup > 0.52359877559829882) {
    rtb_DiscreteTimeIntegrator1_h = 0.52359877559829882;
  } else if (rtb_PIDFControllerVa_dtKiLookup < -0.52359877559829882) {
    rtb_DiscreteTimeIntegrator1_h = -0.52359877559829882;
  } else {
    rtb_DiscreteTimeIntegrator1_h = rtb_PIDFControllerVa_dtKiLookup;
  }

  /* End of Saturate: '<S5>/Saturation' */

  /* Switch: '<S1>/Switch1' incorporates:
   *  Abs: '<S1>/Abs1'
   *  Constant: '<S1>/Constant3'
   */
  if (fabs(*((const real_T **)ssGetInputPortSignalPtrs(S, 9))[0]) >
      0.0017453292519943296) {
    rtb_da = *((const real_T **)ssGetInputPortSignalPtrs(S, 9))[0];
  } else {
    rtb_da = 0.0;
  }

  /* End of Switch: '<S1>/Switch1' */

  /* Product: '<S13>/Product1' incorporates:
   *  DiscreteIntegrator: '<S13>/Discrete-Time Integrator'
   *  Lookup_n-D: '<S4>/PDF Controller Phi 2DOF Kd 2D Lookup Table'
   *  Lookup_n-D: '<S4>/PDF Controller Phi 2DOF N 2D Lookup Table'
   *  Product: '<S13>/Product'
   *  Sum: '<S13>/Sum'
   */
  _rtB->Product1_n = (rtb_da * Autopilot_look1_binlxpw(*((const real_T **)
    ssGetInputPortSignalPtrs(S, 3))[0], Autopilot_ConstP.pooled1,
    Autopilot_ConstP.PDFControllerPhi2DOFKd2DLookupT, 9U) - ((real_T *)
    ssGetDWork(S, 15))[0]) * Autopilot_look1_binlxpw(*((const real_T **)
    ssGetInputPortSignalPtrs(S, 3))[0], Autopilot_ConstP.pooled1,
    Autopilot_ConstP.PDFControllerPhi2DOFN2DLookupTa, 9U);

  /* Sum: '<S1>/Sum2' */
  rtb_Chi_e = *((const real_T **)ssGetInputPortSignalPtrs(S, 2))[0] - *((const
    real_T **)ssGetInputPortSignalPtrs(S, 8))[0];

  /* Switch: '<S10>/Clamp Switch' incorporates:
   *  Constant: '<S10>/Constant'
   *  Lookup_n-D: '<S3>/PIDF Controller Chi Ki 2D Lookup Table'
   *  Memory: '<S11>/Memory'
   *  Product: '<S10>/IOut'
   */
  if (((boolean_T *)ssGetDWork(S, 28))[0]) {
    _rtB->ClampSwitch_m = 0.0;
  } else {
    _rtB->ClampSwitch_m = Autopilot_look1_binlxpw(*((const real_T **)
      ssGetInputPortSignalPtrs(S, 3))[0], Autopilot_ConstP.pooled1,
      Autopilot_ConstP.PIDFControllerChiKi2DLookupTabl, 9U) * rtb_Chi_e;
  }

  /* End of Switch: '<S10>/Clamp Switch' */

  /* DiscreteIntegrator: '<S10>/Discrete-Time Integrator' */
  _rtB->DiscreteTimeIntegrator_h = 0.005 * _rtB->ClampSwitch_m + ((real_T *)
    ssGetDWork(S, 16))[0];

  /* Sum: '<S10>/Sum2' incorporates:
   *  Lookup_n-D: '<S3>/PIDF Controller Chi Kp 2D Lookup Table'
   *  Product: '<S10>/POut'
   */
  rtb_Chi_e = Autopilot_look1_binlxpw(*((const real_T **)
    ssGetInputPortSignalPtrs(S, 3))[0], Autopilot_ConstP.pooled1,
    Autopilot_ConstP.PIDFControllerChiKp2DLookupTabl, 9U) * rtb_Chi_e +
    _rtB->DiscreteTimeIntegrator_h;

  /* Saturate: '<S3>/Saturation' */
  if (rtb_Chi_e > 0.52359877559829882) {
    rtb_PIDFControllerPhiN2DLookupT = 0.52359877559829882;
  } else if (rtb_Chi_e < -0.52359877559829882) {
    rtb_PIDFControllerPhiN2DLookupT = -0.52359877559829882;
  } else {
    rtb_PIDFControllerPhiN2DLookupT = rtb_Chi_e;
  }

  /* End of Saturate: '<S3>/Saturation' */

  /* Sum: '<S1>/Sum' */
  rtb_Phi_e = rtb_PIDFControllerPhiN2DLookupT - rtb_da;

  /* Switch: '<S14>/Clamp Switch' incorporates:
   *  Constant: '<S14>/Constant'
   *  Lookup_n-D: '<S4>/PIDF Controller Phi Ki 2D Lookup Table'
   *  Memory: '<S15>/Memory'
   *  Product: '<S14>/IOut'
   */
  if (((boolean_T *)ssGetDWork(S, 27))[0]) {
    _rtB->ClampSwitch_n = 0.0;
  } else {
    _rtB->ClampSwitch_n = Autopilot_look1_binlxpw(*((const real_T **)
      ssGetInputPortSignalPtrs(S, 3))[0], Autopilot_ConstP.pooled1,
      Autopilot_ConstP.PIDFControllerPhiKi2DLookupTabl, 9U) * rtb_Phi_e;
  }

  /* End of Switch: '<S14>/Clamp Switch' */

  /* DiscreteIntegrator: '<S14>/Discrete-Time Integrator' */
  _rtB->DiscreteTimeIntegrator_n = 0.005 * _rtB->ClampSwitch_n + ((real_T *)
    ssGetDWork(S, 17))[0];

  /* Sum: '<S4>/Sum1' incorporates:
   *  DiscreteIntegrator: '<S12>/Discrete-Time Integrator'
   *  Lookup_n-D: '<S4>/PDF Controller Phi 2DOF Kp 2D Lookup Table'
   *  Lookup_n-D: '<S4>/PIDF Controller Phi Kp 2D Lookup Table'
   *  Product: '<S13>/POut'
   *  Product: '<S14>/POut'
   *  Sum: '<S13>/Sum2'
   *  Sum: '<S14>/Sum2'
   */
  rtb_da = ((Autopilot_look1_binlxpw(*((const real_T **)ssGetInputPortSignalPtrs
    (S, 3))[0], Autopilot_ConstP.pooled1,
              Autopilot_ConstP.PDFControllerPhi2DOFKp2DLookupT, 9U) * rtb_da +
             _rtB->Product1_n) + (rtb_Phi_e * Autopilot_look1_binlxpw(*((const
    real_T **)ssGetInputPortSignalPtrs(S, 3))[0], Autopilot_ConstP.pooled1,
              Autopilot_ConstP.PIDFControllerPhiKp2DLookupTabl, 9U) +
             _rtB->DiscreteTimeIntegrator_n)) + ((real_T *)ssGetDWork(S, 18))[0];

  /* Saturate: '<S4>/Saturation' */
  if (rtb_da > 0.52359877559829882) {
    rtb_Phi_e = 0.52359877559829882;
  } else if (rtb_da < -0.52359877559829882) {
    rtb_Phi_e = -0.52359877559829882;
  } else {
    rtb_Phi_e = rtb_da;
  }

  /* End of Saturate: '<S4>/Saturation' */

  /* Gain: '<S1>/Mixing Matrix' incorporates:
   *  Gain: '<S5>/Sign Inversion'
   */
  der_tmp = 0.5 * -rtb_DiscreteTimeIntegrator1_h;

  /* Outport: '<Root>/der' incorporates:
   *  Gain: '<S1>/Mixing Matrix'
   *  SignalConversion: '<S1>/TmpSignal ConversionAtMixing MatrixInport1'
   */
  ((real_T *)ssGetOutputPortSignal(S, 1))[0] = der_tmp + -0.5 * rtb_Phi_e;

  /* Outport: '<Root>/del' incorporates:
   *  Gain: '<S1>/Mixing Matrix'
   *  SignalConversion: '<S1>/TmpSignal ConversionAtMixing MatrixInport1'
   */
  ((real_T *)ssGetOutputPortSignal(S, 2))[0] = der_tmp + 0.5 * rtb_Phi_e;

  /* RelationalOperator: '<S11>/NotEqual' */
  _rtB->NotEqual = (rtb_Chi_e != rtb_PIDFControllerPhiN2DLookupT);

  /* Product: '<S12>/Product1' incorporates:
   *  DiscreteIntegrator: '<S12>/Discrete-Time Integrator'
   *  Lookup_n-D: '<S4>/PIDF Controller Phi Kd 2D Lookup Table'
   *  Lookup_n-D: '<S4>/PIDF Controller Phi N 2D Lookup Table'
   *  Product: '<S12>/Product'
   *  Sum: '<S12>/Sum'
   */
  _rtB->Nda_e = (Autopilot_look1_binlxpw(*((const real_T **)
    ssGetInputPortSignalPtrs(S, 3))[0], Autopilot_ConstP.pooled1,
    Autopilot_ConstP.PIDFControllerPhiKd2DLookupTabl, 9U) * *((const real_T **)
    ssGetInputPortSignalPtrs(S, 10))[0] - ((real_T *)ssGetDWork(S, 18))[0]) *
    Autopilot_look1_binlxpw(*((const real_T **)ssGetInputPortSignalPtrs(S, 3))[0],
    Autopilot_ConstP.pooled1, Autopilot_ConstP.PIDFControllerPhiN2DLookupTable,
    9U);

  /* RelationalOperator: '<S15>/NotEqual' */
  _rtB->NotEqual_g = (rtb_da != rtb_Phi_e);

  /* Product: '<S16>/Product1' incorporates:
   *  DiscreteIntegrator: '<S16>/Discrete-Time Integrator'
   *  Lookup_n-D: '<S5>/PIDF Controller theta Kd 2D Lookup Table'
   *  Lookup_n-D: '<S5>/PIDF Controller theta N 2D Lookup Table'
   *  Product: '<S16>/Product'
   *  Sum: '<S16>/Sum'
   */
  _rtB->Nde_e = (Autopilot_look2_binlxpw(*((const real_T **)
    ssGetInputPortSignalPtrs(S, 3))[0], *((const real_T **)
    ssGetInputPortSignalPtrs(S, 6))[0], Autopilot_ConstP.pooled1,
    Autopilot_ConstP.pooled2, Autopilot_ConstP.PIDFControllerthetaKd2DLookupTa,
    Autopilot_ConstP.pooled14, 10U) * *((const real_T **)
    ssGetInputPortSignalPtrs(S, 7))[0] - ((real_T *)ssGetDWork(S, 14))[0]) *
    Autopilot_look2_binlxpw(*((const real_T **)ssGetInputPortSignalPtrs(S, 3))[0],
    *((const real_T **)ssGetInputPortSignalPtrs(S, 6))[0],
    Autopilot_ConstP.pooled1, Autopilot_ConstP.pooled2,
    Autopilot_ConstP.PIDFControllerthetaN2DLookupTab, Autopilot_ConstP.pooled14,
    10U);

  /* RelationalOperator: '<S19>/NotEqual' */
  _rtB->NotEqual_j = (rtb_PIDFControllerVa_dtKiLookup !=
                      rtb_DiscreteTimeIntegrator1_h);

  /* RelationalOperator: '<S21>/NotEqual' */
  _rtB->NotEqual_h = (rtb_Sum2_m != _rtB->Saturation);

  /* RelationalOperator: '<S23>/NotEqual' */
  _rtB->NotEqual_a = (_rtB->Sum2 != _rtB->Sum2);

  /* RelationalOperator: '<S25>/NotEqual' */
  _rtB->NotEqual_n = (rtb_Va_e != _rtB->Saturation_c);
  UNUSED_PARAMETER(tid);
}

/* Update for root system: '<Root>' */
#define MDL_UPDATE

static void mdlUpdate(SimStruct *S, int_T tid)
{
  B_Autopilot_T *_rtB;
  _rtB = ((B_Autopilot_T *) ssGetLocalBlockIO(S));

  /* Update for Memory: '<S21>/Memory' */
  ((boolean_T *)ssGetDWork(S, 21))[0] = _rtB->NotEqual_h;

  /* Update for Delay: '<S20>/Delay' */
  ((real_T *)ssGetDWork(S, 0))[0] = _rtB->Saturation;

  /* Update for UnitDelay: '<S1>/Unit Delay1' */
  ((real_T *)ssGetDWork(S, 1))[0] = _rtB->IC;

  /* Update for DiscreteIntegrator: '<S20>/Discrete-Time Integrator' */
  ((real_T *)ssGetDWork(S, 2))[0] = 0.005 * _rtB->Sum1 +
    _rtB->DiscreteTimeIntegrator;

  /* Update for DiscreteIntegrator: '<S20>/Discrete-Time Integrator1' */
  ((real_T *)ssGetDWork(S, 3))[0] = 0.01 * _rtB->Product1 + ((real_T *)
    ssGetDWork(S, 3))[0];

  /* Update for Memory: '<S23>/Memory' */
  ((boolean_T *)ssGetDWork(S, 22))[0] = _rtB->NotEqual_a;

  /* Update for Delay: '<S22>/Delay' */
  ((real_T *)ssGetDWork(S, 4))[0] = _rtB->Sum2;

  /* Update for UnitDelay: '<S1>/Unit Delay' */
  ((real_T *)ssGetDWork(S, 5))[0] = _rtB->theta_c_m;

  /* Update for DiscreteIntegrator: '<S22>/Discrete-Time Integrator' */
  ((real_T *)ssGetDWork(S, 6))[0] = 0.005 * _rtB->ClampSwitch +
    _rtB->DiscreteTimeIntegrator_k;

  /* Update for DiscreteIntegrator: '<S22>/Discrete-Time Integrator1' */
  ((real_T *)ssGetDWork(S, 7))[0] = 0.01 * _rtB->Product1_c + ((real_T *)
    ssGetDWork(S, 7))[0];

  /* Update for UnitDelay: '<S9>/Delay Input2' */
  ((real_T *)ssGetDWork(S, 8))[0] = _rtB->DifferenceInputs2;

  /* Update for Memory: '<S25>/Memory' */
  ((boolean_T *)ssGetDWork(S, 23))[0] = _rtB->NotEqual_n;

  /* Update for Delay: '<S24>/Delay' */
  ((real_T *)ssGetDWork(S, 9))[0] = _rtB->Saturation_c;

  /* Update for DiscreteIntegrator: '<S24>/Discrete-Time Integrator' */
  ((real_T *)ssGetDWork(S, 10))[0] = 0.005 * _rtB->ClampSwitch_p +
    _rtB->DiscreteTimeIntegrator_g;

  /* Update for DiscreteIntegrator: '<S24>/Discrete-Time Integrator1' */
  ((real_T *)ssGetDWork(S, 11))[0] = 0.01 * _rtB->theta_c + ((real_T *)
    ssGetDWork(S, 11))[0];

  /* Update for DiscreteIntegrator: '<S17>/Discrete-Time Integrator' */
  ((real_T *)ssGetDWork(S, 12))[0] = 0.01 * _rtB->Product1_k + ((real_T *)
    ssGetDWork(S, 12))[0];

  /* Update for Memory: '<S19>/Memory' */
  ((boolean_T *)ssGetDWork(S, 26))[0] = _rtB->NotEqual_j;

  /* Update for DiscreteIntegrator: '<S18>/Discrete-Time Integrator' */
  ((real_T *)ssGetDWork(S, 13))[0] = 0.005 * _rtB->ClampSwitch_c +
    _rtB->DiscreteTimeIntegrator_f;

  /* Update for DiscreteIntegrator: '<S16>/Discrete-Time Integrator' */
  ((real_T *)ssGetDWork(S, 14))[0] = 0.01 * _rtB->Nde_e + ((real_T *)ssGetDWork
    (S, 14))[0];

  /* Update for DiscreteIntegrator: '<S13>/Discrete-Time Integrator' */
  ((real_T *)ssGetDWork(S, 15))[0] = 0.01 * _rtB->Product1_n + ((real_T *)
    ssGetDWork(S, 15))[0];

  /* Update for Memory: '<S15>/Memory' */
  ((boolean_T *)ssGetDWork(S, 27))[0] = _rtB->NotEqual_g;

  /* Update for Memory: '<S11>/Memory' */
  ((boolean_T *)ssGetDWork(S, 28))[0] = _rtB->NotEqual;

  /* Update for DiscreteIntegrator: '<S10>/Discrete-Time Integrator' */
  ((real_T *)ssGetDWork(S, 16))[0] = 0.005 * _rtB->ClampSwitch_m +
    _rtB->DiscreteTimeIntegrator_h;

  /* Update for DiscreteIntegrator: '<S14>/Discrete-Time Integrator' */
  ((real_T *)ssGetDWork(S, 17))[0] = 0.005 * _rtB->ClampSwitch_n +
    _rtB->DiscreteTimeIntegrator_n;

  /* Update for DiscreteIntegrator: '<S12>/Discrete-Time Integrator' */
  ((real_T *)ssGetDWork(S, 18))[0] = 0.01 * _rtB->Nda_e + ((real_T *)ssGetDWork
    (S, 18))[0];
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
#  include "Autopilot_mid.h"
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
  if (!ssSetNumInputPorts(S, 11))
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
    if (!ssSetInputPortVectorDimension(S, 1, 1))
      return;
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
    if (!ssSetInputPortVectorDimension(S, 2, 1))
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
    if (!ssSetInputPortVectorDimension(S, 4, 1))
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

  /* inport number: 6 */
  {
    if (!ssSetInputPortMatrixDimensions(S, 6, 1, 1))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 6, SS_DOUBLE);
    }

    ssSetInputPortDirectFeedThrough(S, 6, 1);
    ssSetInputPortSampleTime(S, 6, 0.01);
    ssSetInputPortOffsetTime(S, 6, 0.0);
    ssSetInputPortOverWritable(S, 6, 0);
    ssSetInputPortOptimOpts(S, 6, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  /* inport number: 7 */
  {
    if (!ssSetInputPortVectorDimension(S, 7, 1))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 7, SS_DOUBLE);
    }

    ssSetInputPortDirectFeedThrough(S, 7, 1);
    ssSetInputPortSampleTime(S, 7, 0.01);
    ssSetInputPortOffsetTime(S, 7, 0.0);
    ssSetInputPortOverWritable(S, 7, 0);
    ssSetInputPortOptimOpts(S, 7, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  /* inport number: 8 */
  {
    if (!ssSetInputPortVectorDimension(S, 8, 1))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 8, SS_DOUBLE);
    }

    ssSetInputPortDirectFeedThrough(S, 8, 1);
    ssSetInputPortSampleTime(S, 8, 0.01);
    ssSetInputPortOffsetTime(S, 8, 0.0);
    ssSetInputPortOverWritable(S, 8, 0);
    ssSetInputPortOptimOpts(S, 8, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  /* inport number: 9 */
  {
    if (!ssSetInputPortVectorDimension(S, 9, 1))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 9, SS_DOUBLE);
    }

    ssSetInputPortDirectFeedThrough(S, 9, 1);
    ssSetInputPortSampleTime(S, 9, 0.01);
    ssSetInputPortOffsetTime(S, 9, 0.0);
    ssSetInputPortOverWritable(S, 9, 0);
    ssSetInputPortOptimOpts(S, 9, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  /* inport number: 10 */
  {
    if (!ssSetInputPortVectorDimension(S, 10, 1))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 10, SS_DOUBLE);
    }

    ssSetInputPortDirectFeedThrough(S, 10, 1);
    ssSetInputPortSampleTime(S, 10, 0.01);
    ssSetInputPortOffsetTime(S, 10, 0.0);
    ssSetInputPortOverWritable(S, 10, 0);
    ssSetInputPortOptimOpts(S, 10, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  ssSetRTWGeneratedSFcn(S, 1);         /* Generated S-function */

  /* DWork */
  if (!ssSetNumDWork(S, 29)) {
    return;
  }

  /* '<S20>/Delay': DSTATE */
  ssSetDWorkName(S, 0, "DWORK0");
  ssSetDWorkWidth(S, 0, 1);
  ssSetDWorkUsedAsDState(S, 0, 1);

  /* '<S1>/Unit Delay1': DSTATE */
  ssSetDWorkName(S, 1, "DWORK1");
  ssSetDWorkWidth(S, 1, 1);
  ssSetDWorkUsedAsDState(S, 1, 1);

  /* '<S20>/Discrete-Time Integrator': DSTATE */
  ssSetDWorkName(S, 2, "DWORK2");
  ssSetDWorkWidth(S, 2, 1);
  ssSetDWorkUsedAsDState(S, 2, 1);

  /* '<S20>/Discrete-Time Integrator1': DSTATE */
  ssSetDWorkName(S, 3, "DWORK3");
  ssSetDWorkWidth(S, 3, 1);
  ssSetDWorkUsedAsDState(S, 3, 1);

  /* '<S22>/Delay': DSTATE */
  ssSetDWorkName(S, 4, "DWORK4");
  ssSetDWorkWidth(S, 4, 1);
  ssSetDWorkUsedAsDState(S, 4, 1);

  /* '<S1>/Unit Delay': DSTATE */
  ssSetDWorkName(S, 5, "DWORK5");
  ssSetDWorkWidth(S, 5, 1);
  ssSetDWorkUsedAsDState(S, 5, 1);

  /* '<S22>/Discrete-Time Integrator': DSTATE */
  ssSetDWorkName(S, 6, "DWORK6");
  ssSetDWorkWidth(S, 6, 1);
  ssSetDWorkUsedAsDState(S, 6, 1);

  /* '<S22>/Discrete-Time Integrator1': DSTATE */
  ssSetDWorkName(S, 7, "DWORK7");
  ssSetDWorkWidth(S, 7, 1);
  ssSetDWorkUsedAsDState(S, 7, 1);

  /* '<S9>/Delay Input2': DSTATE */
  ssSetDWorkName(S, 8, "DWORK8");
  ssSetDWorkWidth(S, 8, 1);
  ssSetDWorkUsedAsDState(S, 8, 1);

  /* '<S24>/Delay': DSTATE */
  ssSetDWorkName(S, 9, "DWORK9");
  ssSetDWorkWidth(S, 9, 1);
  ssSetDWorkUsedAsDState(S, 9, 1);

  /* '<S24>/Discrete-Time Integrator': DSTATE */
  ssSetDWorkName(S, 10, "DWORK10");
  ssSetDWorkWidth(S, 10, 1);
  ssSetDWorkUsedAsDState(S, 10, 1);

  /* '<S24>/Discrete-Time Integrator1': DSTATE */
  ssSetDWorkName(S, 11, "DWORK11");
  ssSetDWorkWidth(S, 11, 1);
  ssSetDWorkUsedAsDState(S, 11, 1);

  /* '<S17>/Discrete-Time Integrator': DSTATE */
  ssSetDWorkName(S, 12, "DWORK12");
  ssSetDWorkWidth(S, 12, 1);
  ssSetDWorkUsedAsDState(S, 12, 1);

  /* '<S18>/Discrete-Time Integrator': DSTATE */
  ssSetDWorkName(S, 13, "DWORK13");
  ssSetDWorkWidth(S, 13, 1);
  ssSetDWorkUsedAsDState(S, 13, 1);

  /* '<S16>/Discrete-Time Integrator': DSTATE */
  ssSetDWorkName(S, 14, "DWORK14");
  ssSetDWorkWidth(S, 14, 1);
  ssSetDWorkUsedAsDState(S, 14, 1);

  /* '<S13>/Discrete-Time Integrator': DSTATE */
  ssSetDWorkName(S, 15, "DWORK15");
  ssSetDWorkWidth(S, 15, 1);
  ssSetDWorkUsedAsDState(S, 15, 1);

  /* '<S10>/Discrete-Time Integrator': DSTATE */
  ssSetDWorkName(S, 16, "DWORK16");
  ssSetDWorkWidth(S, 16, 1);
  ssSetDWorkUsedAsDState(S, 16, 1);

  /* '<S14>/Discrete-Time Integrator': DSTATE */
  ssSetDWorkName(S, 17, "DWORK17");
  ssSetDWorkWidth(S, 17, 1);
  ssSetDWorkUsedAsDState(S, 17, 1);

  /* '<S12>/Discrete-Time Integrator': DSTATE */
  ssSetDWorkName(S, 18, "DWORK18");
  ssSetDWorkWidth(S, 18, 1);
  ssSetDWorkUsedAsDState(S, 18, 1);

  /* '<S5>/PDF Controller theta 2DOF Kd 2D Lookup Table': m_bpIndex */
  ssSetDWorkName(S, 19, "DWORK19");
  ssSetDWorkWidth(S, 19, 2);
  ssSetDWorkDataType(S, 19, SS_UINT32);

  /* '<S1>/Altitude Control State Machine': DWORK1 */
  ssSetDWorkName(S, 20, "DWORK20");
  ssSetDWorkWidth(S, 20, 1);
  ssSetDWorkDataType(S, 20, SS_UINT8);

  /* '<S21>/Memory': PreviousInput */
  ssSetDWorkName(S, 21, "DWORK21");
  ssSetDWorkWidth(S, 21, 1);
  ssSetDWorkDataType(S, 21, SS_BOOLEAN);

  /* '<S23>/Memory': PreviousInput */
  ssSetDWorkName(S, 22, "DWORK22");
  ssSetDWorkWidth(S, 22, 1);
  ssSetDWorkDataType(S, 22, SS_BOOLEAN);

  /* '<S25>/Memory': PreviousInput */
  ssSetDWorkName(S, 23, "DWORK23");
  ssSetDWorkWidth(S, 23, 1);
  ssSetDWorkDataType(S, 23, SS_BOOLEAN);

  /* '<S1>/IC': FirstOutputTime */
  ssSetDWorkName(S, 24, "DWORK24");
  ssSetDWorkWidth(S, 24, 1);
  ssSetDWorkDataType(S, 24, SS_BOOLEAN);

  /* '<S1>/IC1': FirstOutputTime */
  ssSetDWorkName(S, 25, "DWORK25");
  ssSetDWorkWidth(S, 25, 1);
  ssSetDWorkDataType(S, 25, SS_BOOLEAN);

  /* '<S19>/Memory': PreviousInput */
  ssSetDWorkName(S, 26, "DWORK26");
  ssSetDWorkWidth(S, 26, 1);
  ssSetDWorkDataType(S, 26, SS_BOOLEAN);

  /* '<S15>/Memory': PreviousInput */
  ssSetDWorkName(S, 27, "DWORK27");
  ssSetDWorkWidth(S, 27, 1);
  ssSetDWorkDataType(S, 27, SS_BOOLEAN);

  /* '<S11>/Memory': PreviousInput */
  ssSetDWorkName(S, 28, "DWORK28");
  ssSetDWorkWidth(S, 28, 1);
  ssSetDWorkDataType(S, 28, SS_BOOLEAN);

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
# define S_FUNCTION_NAME               Autopilot_sf
# include "cg_sfun.h"
#endif                                 /* defined(MATLAB_MEX_FILE) */
