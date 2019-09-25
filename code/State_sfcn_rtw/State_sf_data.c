/*
 * State_sf_data.c
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

#include "State_sf.h"
#include "State_sf_private.h"

/* Invariant block signals (default storage) */
const ConstB_State_T State_Invariant = {
  0.81632653061224481,                 /* '<S1>/Math Function2' */
  0.1019367991845056,                  /* '<S1>/Math Function' */
  0.81632653061224481                  /* '<S1>/Math Function1' */
};

/* Constant parameters (default storage) */
const ConstP_State_T State_ConstP = {
  /* Expression: SkywalkerX8.Sensors.EKF.GPSSmoothing.MeasurementCovarianceMatrix
   * Referenced by: '<S4>/Constant'
   */
  { 0.044099999999999993, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.044099999999999993,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.00015625000000000003, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.5625E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0E-12, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0E-12 },

  /* Expression: p.R{1}
   * Referenced by: '<S14>/R1'
   */
  { 0.0015397775999999998, 0.0, 0.0, 0.0, 0.0015397775999999998, 0.0, 0.0, 0.0,
    0.0015397775999999998 },

  /* Expression: p.Q
   * Referenced by: '<S14>/Q'
   */
  { 1.0E-10, 0.0, 0.0, 1.0E-10 },

  /* Expression: p.Q
   * Referenced by: '<S21>/Q'
   */
  { 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0E-5, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0E-5 },

  /* Expression: p.InitialCovariance
   * Referenced by: '<S21>/DataStoreMemory - P'
   */
  { 1.0E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0E-6, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0E-6, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 1.0E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0E-6, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0E-6 },

  /* Expression: p.InitialState
   * Referenced by: '<S21>/DataStoreMemory - x'
   */
  { 0.0, 0.0, 17.307195064481132, 0.0, 0.0, 0.0, 0.0 }
};
