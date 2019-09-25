/*
 * Autopilot.c
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "Autopilot".
 *
 * Model version              : 1.303
 * Simulink Coder version : 8.14 (R2018a) 06-Feb-2018
 * C source code generated on : Mon Sep  2 18:23:30 2019
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Autopilot.h"
#include "Autopilot_private.h"

/* Named constants for Chart: '<S1>/Altitude Control State Machine' */
#define Autopilot_IN_Altitude_Hold_Zone ((uint8_T)1U)
#define Autopilot_IN_Climb_Zone        ((uint8_T)2U)
#define Autopilot_IN_Descend_Zone      ((uint8_T)3U)
#define Autopilot_IN_Landing_Mode      ((uint8_T)4U)
#define Autopilot_IN_Pre_Flight        ((uint8_T)5U)
#define Autopilot_IN_Take_Off_Zone     ((uint8_T)6U)

/* Block signals (default storage) */
B_Autopilot_T Autopilot_B;

/* Block states (default storage) */
DW_Autopilot_T Autopilot_DW;

/* External inputs (root inport signals with default storage) */
ExtU_Autopilot_T Autopilot_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Autopilot_T Autopilot_Y;

/* Real-time model */
RT_MODEL_Autopilot_T Autopilot_M_;
RT_MODEL_Autopilot_T *const Autopilot_M = &Autopilot_M_;
static void rate_scheduler(void);
real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
                     uint32_T maxIndex)
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

real_T look2_binlxpw(real_T u0, real_T u1, const real_T bp0[], const real_T bp1[],
                     const real_T table[], const uint32_T maxIndex[], uint32_T
                     stride)
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

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (Autopilot_M->Timing.TaskCounters.TID[1])++;
  if ((Autopilot_M->Timing.TaskCounters.TID[1]) > 9) {/* Sample time: [0.01s, 0.0s] */
    Autopilot_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/* Model step function */
void Autopilot_step(void)
{
  real_T rtb_Sum2_e;
  real_T rtb_UkYk1;
  real_T rtb_Va_e;
  real_T rtb_UnitDelay;
  real_T rtb_Sum2_n;
  real_T rtb_UkYk1_n;
  real_T rtb_POut_f;
  real_T rtb_Product1;
  real_T rtb_Sum1_h;
  real_T rtb_Product1_i;
  real_T rtb_Saturation_g;
  real_T rtb_PIDFControllerthetaN2DLooku;
  real_T rtb_da;
  real_T rtb_POut_ob;
  real_T rtb_Sum2_j;
  real_T rtb_Nda_e;
  real_T rtb_Nde_e;
  real_T SignInversion;
  if (Autopilot_M->Timing.TaskCounters.TID[1] == 0) {
    /* Lookup_n-D: '<S6>/PIDF Controller Va_dt Kp Lookup Table' incorporates:
     *  Inport: '<Root>/Va'
     */
    Autopilot_B.PIDFControllerVa_dtKpLookupTabl = look1_binlxpw(Autopilot_U.Va,
      Autopilot_P.PIDFControllerVa_dtKpLookupTa_m,
      Autopilot_P.PIDFControllerVa_dtKpLookupTabl, 9U);
  }

  /* Product: '<S9>/delta rise limit' incorporates:
   *  Constant: '<S1>/Constant'
   *  SampleTimeMath: '<S9>/sample time'
   *
   * About '<S9>/sample time':
   *  y = K where K = ( w * Ts )
   */
  rtb_Sum2_e = Autopilot_P.Constant_Value_h * Autopilot_P.sampletime_WtEt;

  /* Sum: '<S9>/Difference Inputs1' incorporates:
   *  Inport: '<Root>/Va_c'
   *  UnitDelay: '<S9>/Delay Input2'
   */
  rtb_UkYk1 = Autopilot_U.Va_c - Autopilot_DW.DelayInput2_DSTATE;

  /* Switch: '<S27>/Switch2' incorporates:
   *  RelationalOperator: '<S27>/LowerRelop1'
   */
  if (!(rtb_UkYk1 > rtb_Sum2_e)) {
    /* Product: '<S9>/delta fall limit' incorporates:
     *  Constant: '<S1>/Constant1'
     *  SampleTimeMath: '<S9>/sample time'
     *
     * About '<S9>/sample time':
     *  y = K where K = ( w * Ts )
     */
    rtb_Sum2_e = Autopilot_P.Constant1_Value * Autopilot_P.sampletime_WtEt;

    /* Switch: '<S27>/Switch' incorporates:
     *  RelationalOperator: '<S27>/UpperRelop'
     */
    if (!(rtb_UkYk1 < rtb_Sum2_e)) {
      rtb_Sum2_e = rtb_UkYk1;
    }

    /* End of Switch: '<S27>/Switch' */
  }

  /* End of Switch: '<S27>/Switch2' */

  /* Sum: '<S9>/Difference Inputs2' incorporates:
   *  UnitDelay: '<S9>/Delay Input2'
   */
  rtb_UkYk1 = rtb_Sum2_e + Autopilot_DW.DelayInput2_DSTATE;

  /* Sum: '<S1>/Sum4' incorporates:
   *  Inport: '<Root>/Va'
   */
  rtb_Va_e = rtb_UkYk1 - Autopilot_U.Va;
  if (Autopilot_M->Timing.TaskCounters.TID[1] == 0) {
    /* Lookup_n-D: '<S6>/PIDF Controller Va_dt Ki Lookup Table' incorporates:
     *  Inport: '<Root>/Va'
     */
    Autopilot_B.PIDFControllerVa_dtKiLookupTabl = look1_binlxpw(Autopilot_U.Va,
      Autopilot_P.PIDFControllerVa_dtKiLookupTa_c,
      Autopilot_P.PIDFControllerVa_dtKiLookupTabl, 9U);

    /* Product: '<S21>/Tracking' incorporates:
     *  Delay: '<S21>/Delay'
     *  Gain: '<S6>/PIDF Controller Va_dt Kt Tracking Gain Scalar'
     *  Sum: '<S21>/Sum3'
     *  UnitDelay: '<S1>/Unit Delay1'
     */
    Autopilot_B.Tracking = (Autopilot_DW.UnitDelay1_DSTATE -
      Autopilot_DW.Delay_DSTATE) * (Autopilot_P.PIDFControllerVa_dtKtTrackingGa *
      Autopilot_B.PIDFControllerVa_dtKiLookupTabl);
  }

  /* Switch: '<S21>/Clamp Switch' incorporates:
   *  Constant: '<S21>/Constant'
   *  Delay: '<S22>/Delay'
   *  Product: '<S21>/IOut'
   */
  if (Autopilot_DW.Delay_DSTATE_j) {
    SignInversion = Autopilot_P.Constant_Value_pv;
  } else {
    SignInversion = Autopilot_B.PIDFControllerVa_dtKiLookupTabl * rtb_Va_e;
  }

  /* End of Switch: '<S21>/Clamp Switch' */

  /* Sum: '<S21>/Sum1' */
  Autopilot_B.Sum1 = SignInversion + Autopilot_B.Tracking;
  if (Autopilot_M->Timing.TaskCounters.TID[1] == 0) {
    /* DiscreteIntegrator: '<S21>/Discrete-Time Integrator' */
    Autopilot_B.DiscreteTimeIntegrator =
      Autopilot_P.DiscreteTimeIntegrator_gainval * Autopilot_B.Sum1 +
      Autopilot_DW.DiscreteTimeIntegrator_DSTATE;

    /* Lookup_n-D: '<S6>/PIDF Controller Va_dt N Lookup Table' incorporates:
     *  Inport: '<Root>/Va'
     */
    Autopilot_B.PIDFControllerVa_dtNLookupTable = look1_binlxpw(Autopilot_U.Va,
      Autopilot_P.PIDFControllerVa_dtNLookupTab_o,
      Autopilot_P.PIDFControllerVa_dtNLookupTable, 9U);

    /* Lookup_n-D: '<S6>/PIDF Controller Va_dt Kd Lookup Table' incorporates:
     *  Inport: '<Root>/Va'
     */
    Autopilot_B.PIDFControllerVa_dtKdLookupTabl = look1_binlxpw(Autopilot_U.Va,
      Autopilot_P.PIDFControllerVa_dtKdLookupTa_b,
      Autopilot_P.PIDFControllerVa_dtKdLookupTabl, 9U);

    /* DiscreteIntegrator: '<S21>/Discrete-Time Integrator1' */
    Autopilot_B.DiscreteTimeIntegrator1 =
      Autopilot_DW.DiscreteTimeIntegrator1_DSTATE;
  }

  /* Product: '<S21>/Product1' incorporates:
   *  Product: '<S21>/Product'
   *  Sum: '<S21>/Sum'
   */
  Autopilot_B.Product1 = (rtb_Va_e * Autopilot_B.PIDFControllerVa_dtKdLookupTabl
    - Autopilot_B.DiscreteTimeIntegrator1) *
    Autopilot_B.PIDFControllerVa_dtNLookupTable;

  /* Sum: '<S21>/Sum2' incorporates:
   *  Product: '<S21>/POut'
   */
  rtb_Sum2_e = (Autopilot_B.PIDFControllerVa_dtKpLookupTabl * rtb_Va_e +
                Autopilot_B.DiscreteTimeIntegrator) + Autopilot_B.Product1;

  /* Saturate: '<S21>/Saturation' */
  if (rtb_Sum2_e > Autopilot_P.Saturation_UpperSat) {
    Autopilot_B.Saturation = Autopilot_P.Saturation_UpperSat;
  } else if (rtb_Sum2_e < Autopilot_P.Saturation_LowerSat) {
    Autopilot_B.Saturation = Autopilot_P.Saturation_LowerSat;
  } else {
    Autopilot_B.Saturation = rtb_Sum2_e;
  }

  /* End of Saturate: '<S21>/Saturation' */
  if (Autopilot_M->Timing.TaskCounters.TID[1] == 0) {
    /* Lookup_n-D: '<S7>/PIDF Controller Va_theta Kp 2D Lookup Table' incorporates:
     *  Inport: '<Root>/Va'
     *  Inport: '<Root>/alpha'
     */
    Autopilot_B.PIDFControllerVa_thetaKp2DLooku = look2_binlxpw(Autopilot_U.Va,
      Autopilot_U.alpha, Autopilot_P.PIDFControllerVa_thetaKp2DLoo_k,
      Autopilot_P.PIDFControllerVa_thetaKp2DLoo_b,
      Autopilot_P.PIDFControllerVa_thetaKp2DLooku,
      Autopilot_P.PIDFControllerVa_thetaKp2DLoo_e, 10U);

    /* Lookup_n-D: '<S7>/PIDF Controller Va_theta Ki 2D Lookup Table' incorporates:
     *  Inport: '<Root>/Va'
     *  Inport: '<Root>/alpha'
     */
    Autopilot_B.PIDFControllerVa_thetaKi2DLooku = look2_binlxpw(Autopilot_U.Va,
      Autopilot_U.alpha, Autopilot_P.PIDFControllerVa_thetaKi2DLoo_f,
      Autopilot_P.PIDFControllerVa_thetaKi2DLoo_k,
      Autopilot_P.PIDFControllerVa_thetaKi2DLooku,
      Autopilot_P.PIDFControllerVa_thetaKi2DLoo_j, 10U);

    /* UnitDelay: '<S1>/Unit Delay' */
    rtb_UnitDelay = Autopilot_DW.UnitDelay_DSTATE;

    /* Product: '<S23>/Tracking' incorporates:
     *  Delay: '<S23>/Delay'
     *  Gain: '<S7>/PIDF Controller Va_theta Kt Tracking Gain Scalar'
     *  Gain: '<S7>/Tracking Sign Inversion'
     *  Sum: '<S23>/Sum3'
     *  UnitDelay: '<S1>/Unit Delay'
     */
    Autopilot_B.Tracking_c = (Autopilot_P.TrackingSignInversion_Gain *
      Autopilot_DW.UnitDelay_DSTATE - Autopilot_DW.Delay_DSTATE_b) *
      (Autopilot_P.PIDFControllerVa_thetaKtTrackin *
       Autopilot_B.PIDFControllerVa_thetaKi2DLooku);
  }

  /* Switch: '<S23>/Clamp Switch' incorporates:
   *  Constant: '<S23>/Constant'
   *  Memory: '<S24>/Memory'
   *  Product: '<S23>/IOut'
   *  Sum: '<S23>/Sum1'
   */
  if (Autopilot_DW.Memory_PreviousInput) {
    Autopilot_B.ClampSwitch = Autopilot_P.Constant_Value_a;
  } else {
    Autopilot_B.ClampSwitch = Autopilot_B.PIDFControllerVa_thetaKi2DLooku *
      rtb_Va_e + Autopilot_B.Tracking_c;
  }

  /* End of Switch: '<S23>/Clamp Switch' */
  if (Autopilot_M->Timing.TaskCounters.TID[1] == 0) {
    /* DiscreteIntegrator: '<S23>/Discrete-Time Integrator' */
    Autopilot_B.DiscreteTimeIntegrator_o =
      Autopilot_P.DiscreteTimeIntegrator_gainva_k * Autopilot_B.ClampSwitch +
      Autopilot_DW.DiscreteTimeIntegrator_DSTATE_d;

    /* Lookup_n-D: '<S7>/PIDF Controller Va_theta N 2D Lookup Table' incorporates:
     *  Inport: '<Root>/Va'
     *  Inport: '<Root>/alpha'
     */
    Autopilot_B.PIDFControllerVa_thetaN2DLookup = look2_binlxpw(Autopilot_U.Va,
      Autopilot_U.alpha, Autopilot_P.PIDFControllerVa_thetaN2DLook_l,
      Autopilot_P.PIDFControllerVa_thetaN2DLook_c,
      Autopilot_P.PIDFControllerVa_thetaN2DLookup,
      Autopilot_P.PIDFControllerVa_thetaN2DLoo_lz, 10U);

    /* Lookup_n-D: '<S7>/PIDF Controller Va_theta Kd 2D Lookup Table' incorporates:
     *  Inport: '<Root>/Va'
     *  Inport: '<Root>/alpha'
     */
    Autopilot_B.PIDFControllerVa_thetaKd2DLooku = look2_binlxpw(Autopilot_U.Va,
      Autopilot_U.alpha, Autopilot_P.PIDFControllerVa_thetaKd2DLoo_f,
      Autopilot_P.PIDFControllerVa_thetaKd2DLoo_i,
      Autopilot_P.PIDFControllerVa_thetaKd2DLooku,
      Autopilot_P.PIDFControllerVa_thetaKd2DLoo_a, 10U);

    /* DiscreteIntegrator: '<S23>/Discrete-Time Integrator1' */
    Autopilot_B.DiscreteTimeIntegrator1_g =
      Autopilot_DW.DiscreteTimeIntegrator1_DSTAT_d;
  }

  /* Product: '<S23>/Product1' incorporates:
   *  Product: '<S23>/Product'
   *  Sum: '<S23>/Sum'
   */
  Autopilot_B.Product1_o = (rtb_Va_e *
    Autopilot_B.PIDFControllerVa_thetaKd2DLooku -
    Autopilot_B.DiscreteTimeIntegrator1_g) *
    Autopilot_B.PIDFControllerVa_thetaN2DLookup;

  /* Sum: '<S23>/Sum2' incorporates:
   *  Product: '<S23>/POut'
   */
  rtb_Va_e = (Autopilot_B.PIDFControllerVa_thetaKp2DLooku * rtb_Va_e +
              Autopilot_B.DiscreteTimeIntegrator_o) + Autopilot_B.Product1_o;

  /* Saturate: '<S23>/Saturation' */
  if (rtb_Va_e > Autopilot_P.Saturation_UpperSat_c) {
    Autopilot_B.Saturation_a = Autopilot_P.Saturation_UpperSat_c;
  } else if (rtb_Va_e < Autopilot_P.Saturation_LowerSat_d) {
    Autopilot_B.Saturation_a = Autopilot_P.Saturation_LowerSat_d;
  } else {
    Autopilot_B.Saturation_a = rtb_Va_e;
  }

  /* End of Saturate: '<S23>/Saturation' */

  /* Gain: '<S7>/Sign Inversion' */
  SignInversion = Autopilot_P.SignInversion_Gain * Autopilot_B.Saturation_a;
  if (Autopilot_M->Timing.TaskCounters.TID[1] == 0) {
    /* Product: '<S10>/delta rise limit' incorporates:
     *  Gain: '<S1>/Gain1'
     *  Inport: '<Root>/Va'
     *  SampleTimeMath: '<S10>/sample time'
     *
     * About '<S10>/sample time':
     *  y = K where K = ( w * Ts )
     */
    rtb_Sum2_n = Autopilot_P.Gain1_Gain * Autopilot_U.Va *
      Autopilot_P.sampletime_WtEt_k;

    /* Sum: '<S10>/Difference Inputs1' incorporates:
     *  Inport: '<Root>/h_c'
     *  UnitDelay: '<S10>/Delay Input2'
     */
    rtb_UkYk1_n = Autopilot_U.h_c - Autopilot_DW.DelayInput2_DSTATE_n;

    /* Switch: '<S28>/Switch2' incorporates:
     *  RelationalOperator: '<S28>/LowerRelop1'
     */
    if (!(rtb_UkYk1_n > rtb_Sum2_n)) {
      /* Product: '<S10>/delta fall limit' incorporates:
       *  Gain: '<S1>/Gain'
       *  Inport: '<Root>/Va'
       *  SampleTimeMath: '<S10>/sample time'
       *
       * About '<S10>/sample time':
       *  y = K where K = ( w * Ts )
       */
      rtb_Sum2_n = Autopilot_P.Gain_Gain * Autopilot_U.Va *
        Autopilot_P.sampletime_WtEt_k;

      /* Switch: '<S28>/Switch' incorporates:
       *  RelationalOperator: '<S28>/UpperRelop'
       */
      if (!(rtb_UkYk1_n < rtb_Sum2_n)) {
        rtb_Sum2_n = rtb_UkYk1_n;
      }

      /* End of Switch: '<S28>/Switch' */
    }

    /* End of Switch: '<S28>/Switch2' */

    /* Sum: '<S10>/Difference Inputs2' incorporates:
     *  UnitDelay: '<S10>/Delay Input2'
     */
    Autopilot_B.DifferenceInputs2 = rtb_Sum2_n +
      Autopilot_DW.DelayInput2_DSTATE_n;

    /* Sum: '<S1>/Sum3' incorporates:
     *  Inport: '<Root>/h'
     */
    rtb_Sum2_n = Autopilot_B.DifferenceInputs2 - Autopilot_U.h;

    /* Product: '<S25>/POut' incorporates:
     *  Inport: '<Root>/Va'
     *  Inport: '<Root>/alpha'
     *  Lookup_n-D: '<S8>/PIDF Controller h_theta Kp 2D Lookup Table'
     */
    rtb_POut_f = look2_binlxpw(Autopilot_U.Va, Autopilot_U.alpha,
      Autopilot_P.PIDFControllerh_thetaKp2DLook_g,
      Autopilot_P.PIDFControllerh_thetaKp2DLook_j,
      Autopilot_P.PIDFControllerh_thetaKp2DLookup,
      Autopilot_P.PIDFControllerh_thetaKp2DLook_e, 10U) * rtb_Sum2_n;

    /* Lookup_n-D: '<S8>/PIDF Controller h_theta Ki 2D Lookup Table' incorporates:
     *  Inport: '<Root>/Va'
     *  Inport: '<Root>/alpha'
     */
    rtb_UkYk1_n = look2_binlxpw(Autopilot_U.Va, Autopilot_U.alpha,
      Autopilot_P.PIDFControllerh_thetaKi2DLook_m,
      Autopilot_P.PIDFControllerh_thetaKi2DLook_b,
      Autopilot_P.PIDFControllerh_thetaKi2DLookup,
      Autopilot_P.PIDFControllerh_thetaKi2DLook_d, 10U);

    /* Sum: '<S25>/Sum1' incorporates:
     *  Delay: '<S25>/Delay'
     *  Gain: '<S8>/PIDF Controller h_theta Kt Tracking Gain Scalar'
     *  Product: '<S25>/IOut'
     *  Product: '<S25>/Tracking'
     *  Sum: '<S25>/Sum3'
     */
    Autopilot_B.Sum1_n = (rtb_UnitDelay - Autopilot_DW.Delay_DSTATE_a) *
      (Autopilot_P.PIDFControllerh_thetaKtTracking * rtb_UkYk1_n) + rtb_UkYk1_n *
      rtb_Sum2_n;
  }

  /* Switch: '<S25>/Clamp Switch' incorporates:
   *  Constant: '<S25>/Constant'
   *  Memory: '<S26>/Memory'
   */
  if (Autopilot_B.NotEqual_e0) {
    Autopilot_B.ClampSwitch_e = Autopilot_P.Constant_Value_gg;
  } else {
    Autopilot_B.ClampSwitch_e = Autopilot_B.Sum1_n;
  }

  /* End of Switch: '<S25>/Clamp Switch' */
  if (Autopilot_M->Timing.TaskCounters.TID[1] == 0) {
    /* DiscreteIntegrator: '<S25>/Discrete-Time Integrator' */
    Autopilot_B.DiscreteTimeIntegrator_o0 =
      Autopilot_P.DiscreteTimeIntegrator_gainva_p * Autopilot_B.ClampSwitch_e +
      Autopilot_DW.DiscreteTimeIntegrator_DSTATE_k;

    /* Lookup_n-D: '<S8>/PIDF Controller h_theta N 2D Lookup Table' incorporates:
     *  Inport: '<Root>/Va'
     *  Inport: '<Root>/alpha'
     */
    rtb_UkYk1_n = look2_binlxpw(Autopilot_U.Va, Autopilot_U.alpha,
      Autopilot_P.PIDFControllerh_thetaN2DLooku_b,
      Autopilot_P.PIDFControllerh_thetaN2DLooku_a,
      Autopilot_P.PIDFControllerh_thetaN2DLookupT,
      Autopilot_P.PIDFControllerh_thetaN2DLooku_o, 10U);

    /* Product: '<S25>/Product1' incorporates:
     *  DiscreteIntegrator: '<S25>/Discrete-Time Integrator1'
     *  Inport: '<Root>/Va'
     *  Inport: '<Root>/alpha'
     *  Lookup_n-D: '<S8>/PIDF Controller h_theta Kd 2D Lookup Table'
     *  Product: '<S25>/Product'
     *  Sum: '<S25>/Sum'
     */
    rtb_Product1 = (rtb_Sum2_n * look2_binlxpw(Autopilot_U.Va, Autopilot_U.alpha,
      Autopilot_P.PIDFControllerh_thetaKd2DLook_f,
      Autopilot_P.PIDFControllerh_thetaKd2DLook_j,
      Autopilot_P.PIDFControllerh_thetaKd2DLookup,
      Autopilot_P.PIDFControllerh_thetaKd2DLook_b, 10U) -
                    Autopilot_DW.DiscreteTimeIntegrator1_DSTAT_g) * rtb_UkYk1_n;

    /* Sum: '<S25>/Sum2' */
    rtb_Sum2_n = (rtb_POut_f + Autopilot_B.DiscreteTimeIntegrator_o0) +
      rtb_Product1;

    /* Saturate: '<S25>/Saturation' */
    if (rtb_Sum2_n > Autopilot_P.Saturation_UpperSat_k) {
      Autopilot_B.Saturation_h = Autopilot_P.Saturation_UpperSat_k;
    } else if (rtb_Sum2_n < Autopilot_P.Saturation_LowerSat_o) {
      Autopilot_B.Saturation_h = Autopilot_P.Saturation_LowerSat_o;
    } else {
      Autopilot_B.Saturation_h = rtb_Sum2_n;
    }

    /* End of Saturate: '<S25>/Saturation' */
  }

  /* Chart: '<S1>/Altitude Control State Machine' incorporates:
   *  Inport: '<Root>/h'
   */
  switch (Autopilot_DW.is_c3_Autopilot) {
   case Autopilot_IN_Altitude_Hold_Zone:
    if (Autopilot_U.h < Autopilot_B.DifferenceInputs2 - (1.0 -
         Autopilot_P.AltitudeControlStateMachine_hys) *
        Autopilot_P.AltitudeControlStateMachine_h_h) {
      Autopilot_DW.is_c3_Autopilot = Autopilot_IN_Climb_Zone;
    } else if (Autopilot_U.h >= (1.0 +
                Autopilot_P.AltitudeControlStateMachine_hys) *
               Autopilot_P.AltitudeControlStateMachine_h_h +
               Autopilot_B.DifferenceInputs2) {
      Autopilot_DW.is_c3_Autopilot = Autopilot_IN_Descend_Zone;
    } else if (Autopilot_B.DifferenceInputs2 == 0.0) {
      Autopilot_DW.is_c3_Autopilot = Autopilot_IN_Landing_Mode;
    } else {
      Autopilot_B.dt = Autopilot_B.Saturation;
      Autopilot_B.theta_c_f = Autopilot_B.Saturation_h;
    }
    break;

   case Autopilot_IN_Climb_Zone:
    if (Autopilot_U.h < (1.0 - Autopilot_P.AltitudeControlStateMachine_hys) *
        Autopilot_P.AltitudeControlStateMachine_h_t) {
      Autopilot_DW.is_c3_Autopilot = Autopilot_IN_Take_Off_Zone;
    } else if (Autopilot_U.h >= Autopilot_B.DifferenceInputs2 - (1.0 +
                Autopilot_P.AltitudeControlStateMachine_hys) *
               Autopilot_P.AltitudeControlStateMachine_h_h) {
      Autopilot_DW.is_c3_Autopilot = Autopilot_IN_Altitude_Hold_Zone;
    } else if (Autopilot_B.DifferenceInputs2 == 0.0) {
      Autopilot_DW.is_c3_Autopilot = Autopilot_IN_Landing_Mode;
    } else {
      Autopilot_B.dt = 1.0;
      Autopilot_B.theta_c_f = SignInversion;
    }
    break;

   case Autopilot_IN_Descend_Zone:
    if (Autopilot_U.h < (1.0 - Autopilot_P.AltitudeControlStateMachine_hys) *
        Autopilot_P.AltitudeControlStateMachine_h_h +
        Autopilot_B.DifferenceInputs2) {
      Autopilot_DW.is_c3_Autopilot = Autopilot_IN_Altitude_Hold_Zone;
    } else if (Autopilot_B.DifferenceInputs2 == 0.0) {
      Autopilot_DW.is_c3_Autopilot = Autopilot_IN_Landing_Mode;
    } else {
      Autopilot_B.dt = 0.0;
      Autopilot_B.theta_c_f = SignInversion;
    }
    break;

   case Autopilot_IN_Landing_Mode:
    if (Autopilot_U.h == 0.0) {
      Autopilot_DW.is_c3_Autopilot = Autopilot_IN_Pre_Flight;
    } else {
      Autopilot_B.dt = 0.0;
      Autopilot_B.theta_c_f = Autopilot_B.Saturation_h;
    }
    break;

   case Autopilot_IN_Pre_Flight:
    if (Autopilot_P.AltitudeControlStateMachine_Pre) {
      Autopilot_DW.is_c3_Autopilot = Autopilot_IN_Altitude_Hold_Zone;
    } else if (Autopilot_B.DifferenceInputs2 > 0.0) {
      Autopilot_DW.is_c3_Autopilot = Autopilot_IN_Take_Off_Zone;
    } else {
      Autopilot_B.dt = Autopilot_B.Saturation;
      Autopilot_B.theta_c_f = Autopilot_B.Saturation_h;
    }
    break;

   default:
    if (Autopilot_U.h >= (1.0 + Autopilot_P.AltitudeControlStateMachine_hys) *
        Autopilot_P.AltitudeControlStateMachine_h_t) {
      Autopilot_DW.is_c3_Autopilot = Autopilot_IN_Climb_Zone;
    } else if (Autopilot_B.DifferenceInputs2 == 0.0) {
      Autopilot_DW.is_c3_Autopilot = Autopilot_IN_Landing_Mode;
    } else {
      Autopilot_B.dt = 1.0;
      Autopilot_B.theta_c_f = Autopilot_P.AltitudeControlStateMachine_the;
    }
    break;
  }

  /* End of Chart: '<S1>/Altitude Control State Machine' */

  /* InitialCondition: '<S1>/IC' */
  if (Autopilot_DW.IC_FirstOutputTime) {
    Autopilot_DW.IC_FirstOutputTime = false;

    /* Outport: '<Root>/dt' */
    Autopilot_Y.dt = Autopilot_P.IC_Value;
  } else {
    /* Outport: '<Root>/dt' */
    Autopilot_Y.dt = Autopilot_B.dt;
  }

  /* End of InitialCondition: '<S1>/IC' */
  if (Autopilot_M->Timing.TaskCounters.TID[1] == 0) {
    /* Lookup_n-D: '<S5>/PDF Controller theta 2DOF Kp 2D Lookup Table' incorporates:
     *  Inport: '<Root>/Va'
     *  Inport: '<Root>/alpha'
     */
    Autopilot_B.PDFControllertheta2DOFKp2DLooku = look2_binlxpw(Autopilot_U.Va,
      Autopilot_U.alpha, Autopilot_P.PDFControllertheta2DOFKp2DLoo_l,
      Autopilot_P.PDFControllertheta2DOFKp2DLoo_b,
      Autopilot_P.PDFControllertheta2DOFKp2DLooku,
      Autopilot_P.PDFControllertheta2DOFKp2DLoo_n, 10U);

    /* Lookup_n-D: '<S5>/PDF Controller theta 2DOF N 2D Lookup Table' incorporates:
     *  Inport: '<Root>/Va'
     *  Inport: '<Root>/alpha'
     */
    Autopilot_B.PDFControllertheta2DOFN2DLookup = look2_binlxpw(Autopilot_U.Va,
      Autopilot_U.alpha, Autopilot_P.PDFControllertheta2DOFN2DLook_i,
      Autopilot_P.PDFControllertheta2DOFN2DLook_d,
      Autopilot_P.PDFControllertheta2DOFN2DLookup,
      Autopilot_P.PDFControllertheta2DOFN2DLoo_dz, 10U);

    /* Lookup_n-D: '<S5>/PDF Controller theta 2DOF Kd 2D Lookup Table' incorporates:
     *  Inport: '<Root>/Va'
     *  Inport: '<Root>/alpha'
     */
    Autopilot_B.PDFControllertheta2DOFKd2DLooku = look2_binlxpw(Autopilot_U.Va,
      Autopilot_U.alpha, Autopilot_P.PDFControllertheta2DOFKd2DLoo_n,
      Autopilot_P.PDFControllertheta2DOFKd2DLoo_h,
      Autopilot_P.PDFControllertheta2DOFKd2DLooku,
      Autopilot_P.PDFControllertheta2DOFKd2DLoo_p, 10U);

    /* DiscreteIntegrator: '<S18>/Discrete-Time Integrator' */
    Autopilot_B.DiscreteTimeIntegrator_m =
      Autopilot_DW.DiscreteTimeIntegrator_DSTATE_f;
  }

  /* InitialCondition: '<S1>/IC1' */
  if (Autopilot_DW.IC1_FirstOutputTime) {
    Autopilot_DW.IC1_FirstOutputTime = false;
    Autopilot_B.theta_c = Autopilot_P.IC1_Value;
  } else {
    Autopilot_B.theta_c = Autopilot_B.theta_c_f;
  }

  /* End of InitialCondition: '<S1>/IC1' */

  /* Product: '<S18>/Product1' incorporates:
   *  Product: '<S18>/Product'
   *  Sum: '<S18>/Sum'
   */
  Autopilot_B.Product1_oo = (Autopilot_B.theta_c *
    Autopilot_B.PDFControllertheta2DOFKd2DLooku -
    Autopilot_B.DiscreteTimeIntegrator_m) *
    Autopilot_B.PDFControllertheta2DOFN2DLookup;
  if (Autopilot_M->Timing.TaskCounters.TID[1] == 0) {
    /* Lookup_n-D: '<S5>/PIDF Controller theta Ki 2D Lookup Table' incorporates:
     *  Inport: '<Root>/Va'
     *  Inport: '<Root>/alpha'
     */
    Autopilot_B.PIDFControllerthetaKi2DLookupTa = look2_binlxpw(Autopilot_U.Va,
      Autopilot_U.alpha, Autopilot_P.PIDFControllerthetaKi2DLookup_b,
      Autopilot_P.PIDFControllerthetaKi2DLookup_m,
      Autopilot_P.PIDFControllerthetaKi2DLookupTa,
      Autopilot_P.PIDFControllerthetaKi2DLookup_k, 10U);

    /* Abs: '<S1>/Abs2' incorporates:
     *  Inport: '<Root>/theta'
     */
    rtb_UkYk1_n = fabs(Autopilot_U.theta);

    /* Switch: '<S1>/Switch2' incorporates:
     *  Constant: '<S1>/Constant4'
     *  Inport: '<Root>/theta'
     */
    if (rtb_UkYk1_n > Autopilot_P.Switch2_Threshold) {
      Autopilot_B.Switch2 = Autopilot_U.theta;
    } else {
      Autopilot_B.Switch2 = Autopilot_P.Constant4_Value;
    }

    /* End of Switch: '<S1>/Switch2' */
  }

  /* Sum: '<S1>/Sum1' */
  rtb_UnitDelay = Autopilot_B.theta_c - Autopilot_B.Switch2;

  /* Switch: '<S19>/Clamp Switch' incorporates:
   *  Constant: '<S19>/Constant'
   *  Memory: '<S20>/Memory'
   *  Product: '<S19>/IOut'
   */
  if (Autopilot_DW.Memory_PreviousInput_o) {
    Autopilot_B.ClampSwitch_b = Autopilot_P.Constant_Value_p;
  } else {
    Autopilot_B.ClampSwitch_b = Autopilot_B.PIDFControllerthetaKi2DLookupTa *
      rtb_UnitDelay;
  }

  /* End of Switch: '<S19>/Clamp Switch' */
  if (Autopilot_M->Timing.TaskCounters.TID[1] == 0) {
    /* DiscreteIntegrator: '<S19>/Discrete-Time Integrator' */
    Autopilot_B.DiscreteTimeIntegrator_d =
      Autopilot_P.DiscreteTimeIntegrator_gainv_p4 * Autopilot_B.ClampSwitch_b +
      Autopilot_DW.DiscreteTimeIntegrator_DSTATE_a;

    /* Lookup_n-D: '<S5>/PIDF Controller theta Kp 2D Lookup Table' incorporates:
     *  Inport: '<Root>/Va'
     *  Inport: '<Root>/alpha'
     */
    Autopilot_B.PIDFControllerthetaKp2DLookupTa = look2_binlxpw(Autopilot_U.Va,
      Autopilot_U.alpha, Autopilot_P.PIDFControllerthetaKp2DLookup_n,
      Autopilot_P.PIDFControllerthetaKp2DLookup_i,
      Autopilot_P.PIDFControllerthetaKp2DLookupTa,
      Autopilot_P.PIDFControllerthetaKp2DLookup_p, 10U);

    /* DiscreteIntegrator: '<S17>/Discrete-Time Integrator' */
    Autopilot_B.de = Autopilot_DW.DiscreteTimeIntegrator_DSTATE_j;
  }

  /* Sum: '<S5>/Sum1' incorporates:
   *  Product: '<S18>/POut'
   *  Product: '<S19>/POut'
   *  Sum: '<S18>/Sum2'
   *  Sum: '<S19>/Sum2'
   */
  rtb_UnitDelay = ((Autopilot_B.PDFControllertheta2DOFKp2DLooku *
                    Autopilot_B.theta_c + Autopilot_B.Product1_oo) +
                   (rtb_UnitDelay * Autopilot_B.PIDFControllerthetaKp2DLookupTa
                    + Autopilot_B.DiscreteTimeIntegrator_d)) + Autopilot_B.de;

  /* Saturate: '<S5>/Saturation' */
  if (rtb_UnitDelay > Autopilot_P.Saturation_UpperSat_i) {
    rtb_POut_f = Autopilot_P.Saturation_UpperSat_i;
  } else if (rtb_UnitDelay < Autopilot_P.Saturation_LowerSat_om) {
    rtb_POut_f = Autopilot_P.Saturation_LowerSat_om;
  } else {
    rtb_POut_f = rtb_UnitDelay;
  }

  /* End of Saturate: '<S5>/Saturation' */
  if (Autopilot_M->Timing.TaskCounters.TID[1] == 0) {
    /* Switch: '<S1>/Switch1' incorporates:
     *  Abs: '<S1>/Abs1'
     *  Constant: '<S1>/Constant3'
     *  Inport: '<Root>/Phi'
     */
    if (fabs(Autopilot_U.Phi) > Autopilot_P.Switch1_Threshold) {
      rtb_Sum1_h = Autopilot_U.Phi;
    } else {
      rtb_Sum1_h = Autopilot_P.Constant3_Value;
    }

    /* End of Switch: '<S1>/Switch1' */

    /* Product: '<S14>/Product1' incorporates:
     *  DiscreteIntegrator: '<S14>/Discrete-Time Integrator'
     *  Inport: '<Root>/Va'
     *  Lookup_n-D: '<S4>/PDF Controller Phi 2DOF Kd 2D Lookup Table'
     *  Lookup_n-D: '<S4>/PDF Controller Phi 2DOF N 2D Lookup Table'
     *  Product: '<S14>/Product'
     *  Sum: '<S14>/Sum'
     */
    rtb_Product1_i = (rtb_Sum1_h * look1_binlxpw(Autopilot_U.Va,
      Autopilot_P.PDFControllerPhi2DOFKd2DLooku_p,
      Autopilot_P.PDFControllerPhi2DOFKd2DLookupT, 9U) -
                      Autopilot_DW.DiscreteTimeIntegrator_DSTATE_h) *
      look1_binlxpw(Autopilot_U.Va, Autopilot_P.PDFControllerPhi2DOFN2DLookup_c,
                    Autopilot_P.PDFControllerPhi2DOFN2DLookupTa, 9U);

    /* Sum: '<S14>/Sum2' incorporates:
     *  Inport: '<Root>/Va'
     *  Lookup_n-D: '<S4>/PDF Controller Phi 2DOF Kp 2D Lookup Table'
     *  Product: '<S14>/POut'
     */
    rtb_Sum2_j = look1_binlxpw(Autopilot_U.Va,
      Autopilot_P.PDFControllerPhi2DOFKp2DLooku_l,
      Autopilot_P.PDFControllerPhi2DOFKp2DLookupT, 9U) * rtb_Sum1_h +
      rtb_Product1_i;

    /* Lookup_n-D: '<S4>/PIDF Controller Phi Ki 2D Lookup Table' incorporates:
     *  Inport: '<Root>/Va'
     */
    rtb_UkYk1_n = look1_binlxpw(Autopilot_U.Va,
      Autopilot_P.PIDFControllerPhiKi2DLookupTa_j,
      Autopilot_P.PIDFControllerPhiKi2DLookupTabl, 9U);

    /* Lookup_n-D: '<S3>/PIDF Controller Chi Kp 2D Lookup Table' incorporates:
     *  Inport: '<Root>/Va'
     */
    rtb_da = look1_binlxpw(Autopilot_U.Va,
      Autopilot_P.PIDFControllerChiKp2DLookupTa_c,
      Autopilot_P.PIDFControllerChiKp2DLookupTabl, 9U);

    /* Switch: '<S1>/Switch3' incorporates:
     *  Abs: '<S1>/Abs3'
     *  Constant: '<S1>/Constant5'
     *  Inport: '<Root>/Chi_c'
     */
    if (fabs(Autopilot_U.Chi_c) > Autopilot_P.Switch3_Threshold) {
      SignInversion = Autopilot_U.Chi_c;
    } else {
      SignInversion = Autopilot_P.Constant5_Value;
    }

    /* End of Switch: '<S1>/Switch3' */

    /* Switch: '<S1>/Switch' incorporates:
     *  Abs: '<S1>/Abs'
     *  Constant: '<S1>/Constant2'
     *  Inport: '<Root>/Chi'
     */
    if (fabs(Autopilot_U.Chi) > Autopilot_P.Switch_Threshold) {
      rtb_Saturation_g = Autopilot_U.Chi;
    } else {
      rtb_Saturation_g = Autopilot_P.Constant2_Value;
    }

    /* End of Switch: '<S1>/Switch' */

    /* Sum: '<S1>/Sum2' */
    rtb_Saturation_g = SignInversion - rtb_Saturation_g;

    /* Product: '<S11>/POut' */
    rtb_POut_ob = rtb_da * rtb_Saturation_g;

    /* Lookup_n-D: '<S3>/PIDF Controller Chi Ki 2D Lookup Table' incorporates:
     *  Inport: '<Root>/Va'
     */
    rtb_PIDFControllerthetaN2DLooku = look1_binlxpw(Autopilot_U.Va,
      Autopilot_P.PIDFControllerChiKi2DLookupTa_o,
      Autopilot_P.PIDFControllerChiKi2DLookupTabl, 9U);

    /* Product: '<S11>/IOut' */
    Autopilot_B.IOut = rtb_PIDFControllerthetaN2DLooku * rtb_Saturation_g;
  }

  /* Switch: '<S11>/Clamp Switch' incorporates:
   *  Constant: '<S11>/Constant'
   *  Memory: '<S12>/Memory'
   */
  if (Autopilot_B.NotEqual) {
    Autopilot_B.ClampSwitch_c = Autopilot_P.Constant_Value;
  } else {
    Autopilot_B.ClampSwitch_c = Autopilot_B.IOut;
  }

  /* End of Switch: '<S11>/Clamp Switch' */
  if (Autopilot_M->Timing.TaskCounters.TID[1] == 0) {
    /* DiscreteIntegrator: '<S11>/Discrete-Time Integrator' */
    Autopilot_B.DiscreteTimeIntegrator_e =
      Autopilot_P.DiscreteTimeIntegrator_gainv_on * Autopilot_B.ClampSwitch_c +
      Autopilot_DW.DiscreteTimeIntegrator_DSTAT_hv;

    /* Sum: '<S11>/Sum2' */
    rtb_PIDFControllerthetaN2DLooku = rtb_POut_ob +
      Autopilot_B.DiscreteTimeIntegrator_e;

    /* Saturate: '<S3>/Saturation' */
    if (rtb_PIDFControllerthetaN2DLooku > Autopilot_P.Saturation_UpperSat_e) {
      rtb_Saturation_g = Autopilot_P.Saturation_UpperSat_e;
    } else if (rtb_PIDFControllerthetaN2DLooku <
               Autopilot_P.Saturation_LowerSat_l) {
      rtb_Saturation_g = Autopilot_P.Saturation_LowerSat_l;
    } else {
      rtb_Saturation_g = rtb_PIDFControllerthetaN2DLooku;
    }

    /* End of Saturate: '<S3>/Saturation' */

    /* Sum: '<S1>/Sum' */
    rtb_Sum1_h = rtb_Saturation_g - rtb_Sum1_h;

    /* Product: '<S15>/IOut' */
    Autopilot_B.IOut_m = rtb_UkYk1_n * rtb_Sum1_h;
  }

  /* Switch: '<S15>/Clamp Switch' incorporates:
   *  Constant: '<S15>/Constant'
   *  Memory: '<S16>/Memory'
   */
  if (Autopilot_B.NotEqual_e) {
    Autopilot_B.ClampSwitch_ck = Autopilot_P.Constant_Value_g;
  } else {
    Autopilot_B.ClampSwitch_ck = Autopilot_B.IOut_m;
  }

  /* End of Switch: '<S15>/Clamp Switch' */
  if (Autopilot_M->Timing.TaskCounters.TID[1] == 0) {
    /* DiscreteIntegrator: '<S15>/Discrete-Time Integrator' */
    Autopilot_B.DiscreteTimeIntegrator_oy =
      Autopilot_P.DiscreteTimeIntegrator_gainva_e * Autopilot_B.ClampSwitch_ck +
      Autopilot_DW.DiscreteTimeIntegrator_DSTAT_f2;

    /* DiscreteIntegrator: '<S13>/Discrete-Time Integrator' */
    rtb_da = Autopilot_DW.DiscreteTimeIntegrator_DSTATE_b;

    /* Sum: '<S4>/Sum1' incorporates:
     *  DiscreteIntegrator: '<S13>/Discrete-Time Integrator'
     *  Inport: '<Root>/Va'
     *  Lookup_n-D: '<S4>/PIDF Controller Phi Kp 2D Lookup Table'
     *  Product: '<S15>/POut'
     *  Sum: '<S15>/Sum2'
     */
    rtb_Sum1_h = ((rtb_Sum1_h * look1_binlxpw(Autopilot_U.Va,
      Autopilot_P.PIDFControllerPhiKp2DLookupTa_i,
      Autopilot_P.PIDFControllerPhiKp2DLookupTabl, 9U) +
                   Autopilot_B.DiscreteTimeIntegrator_oy) + rtb_Sum2_j) +
      Autopilot_DW.DiscreteTimeIntegrator_DSTATE_b;

    /* Saturate: '<S4>/Saturation' */
    if (rtb_Sum1_h > Autopilot_P.Saturation_UpperSat_d) {
      Autopilot_B.Saturation_g = Autopilot_P.Saturation_UpperSat_d;
    } else if (rtb_Sum1_h < Autopilot_P.Saturation_LowerSat_ld) {
      Autopilot_B.Saturation_g = Autopilot_P.Saturation_LowerSat_ld;
    } else {
      Autopilot_B.Saturation_g = rtb_Sum1_h;
    }

    /* End of Saturate: '<S4>/Saturation' */
  }

  /* SignalConversion: '<S1>/TmpSignal ConversionAtMixing MatrixInport1' incorporates:
   *  Gain: '<S5>/Sign Inversion'
   */
  rtb_UkYk1_n = Autopilot_P.SignInversion_Gain_f * rtb_POut_f;

  /* Outport: '<Root>/der' incorporates:
   *  Gain: '<S1>/Mixing Matrix'
   *  SignalConversion: '<S1>/TmpSignal ConversionAtMixing MatrixInport1'
   */
  Autopilot_Y.der = Autopilot_P.MixingMatrix_Gain[0] * rtb_UkYk1_n +
    Autopilot_P.MixingMatrix_Gain[2] * Autopilot_B.Saturation_g;

  /* Outport: '<Root>/del' incorporates:
   *  Gain: '<S1>/Mixing Matrix'
   *  SignalConversion: '<S1>/TmpSignal ConversionAtMixing MatrixInport1'
   */
  Autopilot_Y.del = Autopilot_P.MixingMatrix_Gain[1] * rtb_UkYk1_n +
    Autopilot_P.MixingMatrix_Gain[3] * Autopilot_B.Saturation_g;

  /* Update for UnitDelay: '<S9>/Delay Input2' */
  Autopilot_DW.DelayInput2_DSTATE = rtb_UkYk1;

  /* Update for Delay: '<S22>/Delay' incorporates:
   *  RelationalOperator: '<S22>/NotEqual'
   */
  Autopilot_DW.Delay_DSTATE_j = (rtb_Sum2_e != Autopilot_B.Saturation);
  if (Autopilot_M->Timing.TaskCounters.TID[1] == 0) {
    /* RelationalOperator: '<S12>/NotEqual' */
    Autopilot_B.NotEqual = (rtb_PIDFControllerthetaN2DLooku != rtb_Saturation_g);

    /* Product: '<S13>/Product1' incorporates:
     *  Inport: '<Root>/Va'
     *  Inport: '<Root>/p'
     *  Lookup_n-D: '<S4>/PIDF Controller Phi Kd 2D Lookup Table'
     *  Lookup_n-D: '<S4>/PIDF Controller Phi N 2D Lookup Table'
     *  Product: '<S13>/Product'
     *  Sum: '<S13>/Sum'
     */
    rtb_Nda_e = (look1_binlxpw(Autopilot_U.Va,
      Autopilot_P.PIDFControllerPhiKd2DLookupTa_f,
      Autopilot_P.PIDFControllerPhiKd2DLookupTabl, 9U) * Autopilot_U.p - rtb_da)
      * look1_binlxpw(Autopilot_U.Va,
                      Autopilot_P.PIDFControllerPhiN2DLookupTab_a,
                      Autopilot_P.PIDFControllerPhiN2DLookupTable, 9U);

    /* RelationalOperator: '<S16>/NotEqual' */
    Autopilot_B.NotEqual_e = (rtb_Sum1_h != Autopilot_B.Saturation_g);

    /* Product: '<S17>/Product1' incorporates:
     *  Inport: '<Root>/Va'
     *  Inport: '<Root>/alpha'
     *  Inport: '<Root>/q'
     *  Lookup_n-D: '<S5>/PIDF Controller theta Kd 2D Lookup Table'
     *  Lookup_n-D: '<S5>/PIDF Controller theta N 2D Lookup Table'
     *  Product: '<S17>/Product'
     *  Sum: '<S17>/Sum'
     */
    rtb_Nde_e = (look2_binlxpw(Autopilot_U.Va, Autopilot_U.alpha,
      Autopilot_P.PIDFControllerthetaKd2DLookup_a,
      Autopilot_P.PIDFControllerthetaKd2DLookup_g,
      Autopilot_P.PIDFControllerthetaKd2DLookupTa,
      Autopilot_P.PIDFControllerthetaKd2DLookup_i, 10U) * Autopilot_U.q -
                 Autopilot_B.de) * look2_binlxpw(Autopilot_U.Va,
      Autopilot_U.alpha, Autopilot_P.PIDFControllerthetaN2DLookupT_l,
      Autopilot_P.PIDFControllerthetaN2DLookupT_i,
      Autopilot_P.PIDFControllerthetaN2DLookupTab,
      Autopilot_P.PIDFControllerthetaN2DLookupT_k, 10U);

    /* RelationalOperator: '<S26>/NotEqual' */
    Autopilot_B.NotEqual_e0 = (rtb_Sum2_n != Autopilot_B.Saturation_h);
  }

  /* Update for Memory: '<S24>/Memory' incorporates:
   *  RelationalOperator: '<S24>/NotEqual'
   */
  Autopilot_DW.Memory_PreviousInput = (rtb_Va_e != Autopilot_B.Saturation_a);
  if (Autopilot_M->Timing.TaskCounters.TID[1] == 0) {
    /* Update for Delay: '<S21>/Delay' */
    Autopilot_DW.Delay_DSTATE = Autopilot_B.Saturation;

    /* Update for UnitDelay: '<S1>/Unit Delay1' incorporates:
     *  Outport: '<Root>/dt'
     */
    Autopilot_DW.UnitDelay1_DSTATE = Autopilot_Y.dt;

    /* Update for DiscreteIntegrator: '<S21>/Discrete-Time Integrator' */
    Autopilot_DW.DiscreteTimeIntegrator_DSTATE =
      Autopilot_P.DiscreteTimeIntegrator_gainval * Autopilot_B.Sum1 +
      Autopilot_B.DiscreteTimeIntegrator;

    /* Update for DiscreteIntegrator: '<S21>/Discrete-Time Integrator1' */
    Autopilot_DW.DiscreteTimeIntegrator1_DSTATE +=
      Autopilot_P.DiscreteTimeIntegrator1_gainval * Autopilot_B.Product1;

    /* Update for Delay: '<S23>/Delay' */
    Autopilot_DW.Delay_DSTATE_b = Autopilot_B.Saturation_a;

    /* Update for UnitDelay: '<S1>/Unit Delay' */
    Autopilot_DW.UnitDelay_DSTATE = Autopilot_B.theta_c;

    /* Update for DiscreteIntegrator: '<S23>/Discrete-Time Integrator' */
    Autopilot_DW.DiscreteTimeIntegrator_DSTATE_d =
      Autopilot_P.DiscreteTimeIntegrator_gainva_k * Autopilot_B.ClampSwitch +
      Autopilot_B.DiscreteTimeIntegrator_o;

    /* Update for DiscreteIntegrator: '<S23>/Discrete-Time Integrator1' */
    Autopilot_DW.DiscreteTimeIntegrator1_DSTAT_d +=
      Autopilot_P.DiscreteTimeIntegrator1_gainv_b * Autopilot_B.Product1_o;

    /* Update for UnitDelay: '<S10>/Delay Input2' */
    Autopilot_DW.DelayInput2_DSTATE_n = Autopilot_B.DifferenceInputs2;

    /* Update for Delay: '<S25>/Delay' */
    Autopilot_DW.Delay_DSTATE_a = Autopilot_B.Saturation_h;

    /* Update for DiscreteIntegrator: '<S25>/Discrete-Time Integrator' */
    Autopilot_DW.DiscreteTimeIntegrator_DSTATE_k =
      Autopilot_P.DiscreteTimeIntegrator_gainva_p * Autopilot_B.ClampSwitch_e +
      Autopilot_B.DiscreteTimeIntegrator_o0;

    /* Update for DiscreteIntegrator: '<S25>/Discrete-Time Integrator1' */
    Autopilot_DW.DiscreteTimeIntegrator1_DSTAT_g +=
      Autopilot_P.DiscreteTimeIntegrator1_gainv_d * rtb_Product1;

    /* Update for DiscreteIntegrator: '<S18>/Discrete-Time Integrator' */
    Autopilot_DW.DiscreteTimeIntegrator_DSTATE_f +=
      Autopilot_P.DiscreteTimeIntegrator_gainva_f * Autopilot_B.Product1_oo;

    /* Update for DiscreteIntegrator: '<S19>/Discrete-Time Integrator' */
    Autopilot_DW.DiscreteTimeIntegrator_DSTATE_a =
      Autopilot_P.DiscreteTimeIntegrator_gainv_p4 * Autopilot_B.ClampSwitch_b +
      Autopilot_B.DiscreteTimeIntegrator_d;

    /* Update for DiscreteIntegrator: '<S17>/Discrete-Time Integrator' */
    Autopilot_DW.DiscreteTimeIntegrator_DSTATE_j +=
      Autopilot_P.DiscreteTimeIntegrator_gainva_o * rtb_Nde_e;

    /* Update for DiscreteIntegrator: '<S14>/Discrete-Time Integrator' */
    Autopilot_DW.DiscreteTimeIntegrator_DSTATE_h +=
      Autopilot_P.DiscreteTimeIntegrator_gainv_pv * rtb_Product1_i;

    /* Update for DiscreteIntegrator: '<S11>/Discrete-Time Integrator' */
    Autopilot_DW.DiscreteTimeIntegrator_DSTAT_hv =
      Autopilot_P.DiscreteTimeIntegrator_gainv_on * Autopilot_B.ClampSwitch_c +
      Autopilot_B.DiscreteTimeIntegrator_e;

    /* Update for DiscreteIntegrator: '<S15>/Discrete-Time Integrator' */
    Autopilot_DW.DiscreteTimeIntegrator_DSTAT_f2 =
      Autopilot_P.DiscreteTimeIntegrator_gainva_e * Autopilot_B.ClampSwitch_ck +
      Autopilot_B.DiscreteTimeIntegrator_oy;

    /* Update for DiscreteIntegrator: '<S13>/Discrete-Time Integrator' */
    Autopilot_DW.DiscreteTimeIntegrator_DSTATE_b +=
      Autopilot_P.DiscreteTimeIntegrator_gainva_h * rtb_Nda_e;
  }

  /* Update for Memory: '<S20>/Memory' incorporates:
   *  RelationalOperator: '<S20>/NotEqual'
   */
  Autopilot_DW.Memory_PreviousInput_o = (rtb_UnitDelay != rtb_POut_f);

  /* Matfile logging */
  rt_UpdateTXYLogVars(Autopilot_M->rtwLogInfo, (&Autopilot_M->Timing.taskTime0));

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.001s, 0.0s] */
    if ((rtmGetTFinal(Autopilot_M)!=-1) &&
        !((rtmGetTFinal(Autopilot_M)-Autopilot_M->Timing.taskTime0) >
          Autopilot_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(Autopilot_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Autopilot_M->Timing.clockTick0)) {
    ++Autopilot_M->Timing.clockTickH0;
  }

  Autopilot_M->Timing.taskTime0 = Autopilot_M->Timing.clockTick0 *
    Autopilot_M->Timing.stepSize0 + Autopilot_M->Timing.clockTickH0 *
    Autopilot_M->Timing.stepSize0 * 4294967296.0;
  rate_scheduler();
}

/* Model initialize function */
void Autopilot_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  Autopilot_P.Saturation_UpperSat_c = rtInf;
  Autopilot_P.Saturation_LowerSat_d = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)Autopilot_M, 0,
                sizeof(RT_MODEL_Autopilot_T));
  rtmSetTFinal(Autopilot_M, 375.0);
  Autopilot_M->Timing.stepSize0 = 0.001;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = NULL;
    Autopilot_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(Autopilot_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(Autopilot_M->rtwLogInfo, (NULL));
    rtliSetLogT(Autopilot_M->rtwLogInfo, "tout");
    rtliSetLogX(Autopilot_M->rtwLogInfo, "");
    rtliSetLogXFinal(Autopilot_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(Autopilot_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(Autopilot_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(Autopilot_M->rtwLogInfo, 0);
    rtliSetLogDecimation(Autopilot_M->rtwLogInfo, 1);
    rtliSetLogY(Autopilot_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(Autopilot_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(Autopilot_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &Autopilot_B), 0,
                sizeof(B_Autopilot_T));

  /* states (dwork) */
  (void) memset((void *)&Autopilot_DW, 0,
                sizeof(DW_Autopilot_T));

  /* external inputs */
  (void)memset((void *)&Autopilot_U, 0, sizeof(ExtU_Autopilot_T));

  /* external outputs */
  (void) memset((void *)&Autopilot_Y, 0,
                sizeof(ExtY_Autopilot_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(Autopilot_M->rtwLogInfo, 0.0, rtmGetTFinal
    (Autopilot_M), Autopilot_M->Timing.stepSize0, (&rtmGetErrorStatus
    (Autopilot_M)));

  /* Start for InitialCondition: '<S1>/IC' */
  Autopilot_DW.IC_FirstOutputTime = true;

  /* Start for InitialCondition: '<S1>/IC1' */
  Autopilot_DW.IC1_FirstOutputTime = true;

  /* InitializeConditions for UnitDelay: '<S9>/Delay Input2' */
  Autopilot_DW.DelayInput2_DSTATE = Autopilot_P.VaRateLimiter_initOutput;

  /* InitializeConditions for Delay: '<S22>/Delay' */
  Autopilot_DW.Delay_DSTATE_j = Autopilot_P.Delay_InitialCondition_l;

  /* InitializeConditions for Delay: '<S21>/Delay' */
  Autopilot_DW.Delay_DSTATE = Autopilot_P.Delay_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S1>/Unit Delay1' */
  Autopilot_DW.UnitDelay1_DSTATE = Autopilot_P.UnitDelay1_InitialCondition;

  /* InitializeConditions for DiscreteIntegrator: '<S21>/Discrete-Time Integrator' */
  Autopilot_DW.DiscreteTimeIntegrator_DSTATE =
    Autopilot_P.DiscreteTimeIntegrator_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S21>/Discrete-Time Integrator1' */
  Autopilot_DW.DiscreteTimeIntegrator1_DSTATE =
    Autopilot_P.DiscreteTimeIntegrator1_IC;

  /* InitializeConditions for Memory: '<S24>/Memory' */
  Autopilot_DW.Memory_PreviousInput = Autopilot_P.Memory_InitialCondition;

  /* InitializeConditions for Delay: '<S23>/Delay' */
  Autopilot_DW.Delay_DSTATE_b = Autopilot_P.Delay_InitialCondition_i;

  /* InitializeConditions for UnitDelay: '<S1>/Unit Delay' */
  Autopilot_DW.UnitDelay_DSTATE = Autopilot_P.UnitDelay_InitialCondition;

  /* InitializeConditions for DiscreteIntegrator: '<S23>/Discrete-Time Integrator' */
  Autopilot_DW.DiscreteTimeIntegrator_DSTATE_d =
    Autopilot_P.DiscreteTimeIntegrator_IC_h;

  /* InitializeConditions for DiscreteIntegrator: '<S23>/Discrete-Time Integrator1' */
  Autopilot_DW.DiscreteTimeIntegrator1_DSTAT_d =
    Autopilot_P.DiscreteTimeIntegrator1_IC_p;

  /* InitializeConditions for UnitDelay: '<S10>/Delay Input2' */
  Autopilot_DW.DelayInput2_DSTATE_n = Autopilot_P.hRateLimiterDynamic_initOutput;

  /* InitializeConditions for Memory: '<S26>/Memory' */
  Autopilot_B.NotEqual_e0 = Autopilot_P.Memory_InitialCondition_i;

  /* InitializeConditions for Delay: '<S25>/Delay' */
  Autopilot_DW.Delay_DSTATE_a = Autopilot_P.Delay_InitialCondition_in;

  /* InitializeConditions for DiscreteIntegrator: '<S25>/Discrete-Time Integrator' */
  Autopilot_DW.DiscreteTimeIntegrator_DSTATE_k =
    Autopilot_P.DiscreteTimeIntegrator_IC_o;

  /* InitializeConditions for DiscreteIntegrator: '<S25>/Discrete-Time Integrator1' */
  Autopilot_DW.DiscreteTimeIntegrator1_DSTAT_g =
    Autopilot_P.DiscreteTimeIntegrator1_IC_i;

  /* InitializeConditions for DiscreteIntegrator: '<S18>/Discrete-Time Integrator' */
  Autopilot_DW.DiscreteTimeIntegrator_DSTATE_f =
    Autopilot_P.DiscreteTimeIntegrator_IC_b;

  /* InitializeConditions for Memory: '<S20>/Memory' */
  Autopilot_DW.Memory_PreviousInput_o = Autopilot_P.Memory_InitialCondition_c;

  /* InitializeConditions for DiscreteIntegrator: '<S19>/Discrete-Time Integrator' */
  Autopilot_DW.DiscreteTimeIntegrator_DSTATE_a =
    Autopilot_P.DiscreteTimeIntegrator_IC_of;

  /* InitializeConditions for DiscreteIntegrator: '<S17>/Discrete-Time Integrator' */
  Autopilot_DW.DiscreteTimeIntegrator_DSTATE_j =
    Autopilot_P.DiscreteTimeIntegrator_IC_m;

  /* InitializeConditions for DiscreteIntegrator: '<S14>/Discrete-Time Integrator' */
  Autopilot_DW.DiscreteTimeIntegrator_DSTATE_h =
    Autopilot_P.DiscreteTimeIntegrator_IC_a;

  /* InitializeConditions for Memory: '<S16>/Memory' */
  Autopilot_B.NotEqual_e = Autopilot_P.Memory_InitialCondition_m;

  /* InitializeConditions for Memory: '<S12>/Memory' */
  Autopilot_B.NotEqual = Autopilot_P.Memory_InitialCondition_b;

  /* InitializeConditions for DiscreteIntegrator: '<S11>/Discrete-Time Integrator' */
  Autopilot_DW.DiscreteTimeIntegrator_DSTAT_hv =
    Autopilot_P.DiscreteTimeIntegrator_IC_n;

  /* InitializeConditions for DiscreteIntegrator: '<S15>/Discrete-Time Integrator' */
  Autopilot_DW.DiscreteTimeIntegrator_DSTAT_f2 =
    Autopilot_P.DiscreteTimeIntegrator_IC_f;

  /* InitializeConditions for DiscreteIntegrator: '<S13>/Discrete-Time Integrator' */
  Autopilot_DW.DiscreteTimeIntegrator_DSTATE_b =
    Autopilot_P.DiscreteTimeIntegrator_IC_g;

  /* Chart: '<S1>/Altitude Control State Machine' */
  Autopilot_DW.is_c3_Autopilot = Autopilot_IN_Pre_Flight;
}

/* Model terminate function */
void Autopilot_terminate(void)
{
  /* (no terminate code required) */
}
