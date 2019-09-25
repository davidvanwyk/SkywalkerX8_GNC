/*
 * State_sf.h
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

#ifndef RTW_HEADER_State_sf_h_
#define RTW_HEADER_State_sf_h_
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef State_sf_COMMON_INCLUDES_
# define State_sf_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME                State_sf
#define S_FUNCTION_LEVEL               2
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#if !defined(MATLAB_MEX_FILE)
#include "rt_matrx.h"
#endif

#if !defined(RTW_SFUNCTION_DEFINES)
#define RTW_SFUNCTION_DEFINES

typedef struct {
  void *blockIO;
  void *defaultParam;
  void *nonContDerivSig;
} LocalS;

#define ssSetLocalBlockIO(S, io)       ((LocalS *)ssGetUserData(S))->blockIO = ((void *)(io))
#define ssGetLocalBlockIO(S)           ((LocalS *)ssGetUserData(S))->blockIO
#define ssSetLocalDefaultParam(S, paramVector) ((LocalS *)ssGetUserData(S))->defaultParam = (paramVector)
#define ssGetLocalDefaultParam(S)      ((LocalS *)ssGetUserData(S))->defaultParam
#define ssSetLocalNonContDerivSig(S, pSig) ((LocalS *)ssGetUserData(S))->nonContDerivSig = (pSig)
#define ssGetLocalNonContDerivSig(S)   ((LocalS *)ssGetUserData(S))->nonContDerivSig
#endif
#endif                                 /* State_sf_COMMON_INCLUDES_ */

#include "State_sf_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"

/* Block signals (default storage) */
typedef struct {
  real_T RateTransition2[6];           /* '<S4>/Rate Transition2' */
  real_T OverwriteChiVariance[36];     /* '<S4>/Overwrite Chi Variance' */
  real_T RateTransition1[5];           /* '<S4>/Rate Transition1' */
  real_T Unwrap;                       /* '<S4>/Unwrap' */
  real_T DataStoreRead[7];             /* '<S25>/Data Store Read' */
  boolean_T blockOrdering;             /* '<S24>/Correct' */
} B_State_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T urho;                   /* '<S1>/Math Function2' */
  const real_T ug;                     /* '<S1>/Math Function' */
  const real_T urho_f;                 /* '<S1>/Math Function1' */
} ConstB_State_T;

/* For easy access from the SimStruct */
#define State_rtC(rts)                 ((ConstB_State_T *) _ssGetConstBlockIO(rts))

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: SkywalkerX8.Sensors.EKF.GPSSmoothing.MeasurementCovarianceMatrix
   * Referenced by: '<S4>/Constant'
   */
  real_T Constant_Value[36];

  /* Expression: p.R{1}
   * Referenced by: '<S14>/R1'
   */
  real_T R1_Value[9];

  /* Expression: p.Q
   * Referenced by: '<S14>/Q'
   */
  real_T Q_Value[4];

  /* Expression: p.Q
   * Referenced by: '<S21>/Q'
   */
  real_T Q_Value_i[49];

  /* Expression: p.InitialCovariance
   * Referenced by: '<S21>/DataStoreMemory - P'
   */
  real_T DataStoreMemoryP_InitialValue_d[49];

  /* Expression: p.InitialState
   * Referenced by: '<S21>/DataStoreMemory - x'
   */
  real_T DataStoreMemoryx_InitialValue_j[7];
} ConstP_State_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T *ynyeyh[3];                   /* '<Root>/[yn, ye, yh]' */
  real_T *yVg;                         /* '<Root>/yVg' */
  real_T *yChi;                        /* '<Root>/yChi' */
  real_T *yAccXyAccYyAccZ[3];          /* '<Root>/[yAccX, yAccY, yAccZ]' */
  real_T *ypyqyr[3];                   /* '<Root>/[yp, yq, yr]' */
  real_T *yPsi;                        /* '<Root>/yPsi' */
  real_T *ydPVa;                       /* '<Root>/ydPVa' */
  real_T *yPAbsAlt;                    /* '<Root>/yPAbsAlt' */
  real_T *yalpha;                      /* '<Root>/yalpha' */
} ExternalUPtrs_State_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T *pnpepd[3];                   /* '<Root>/[pn, pe, pd]' */
  real_T *Va;                          /* '<Root>/Va' */
  real_T *wnwe[2];                     /* '<Root>/[wn, we]' */
  real_T *PhiThetaPsi[3];              /* '<Root>/[Phi, Theta, Psi]' */
  real_T *pqr[3];                      /* '<Root>/[p, q, r]' */
  real_T *Vg;                          /* '<Root>/Vg' */
  real_T *Chi;                         /* '<Root>/Chi' */
  real_T *alpha;                       /* '<Root>/alpha' */
} ExtY_State_T;

extern const ConstB_State_T State_Invariant;

/* Constant parameters (default storage) */
extern const ConstP_State_T State_ConstP;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation')    - opens subsystem SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation
 * hilite_system('SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'SkywalkerX8_GuidanceAndNavigation_Verification'
 * '<S1>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation'
 * '<S2>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/Altitude Pressure  Low Pass Filter'
 * '<S3>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/Attitude Estimation Extended Kalman Filter with Filtering'
 * '<S4>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/GPS Smoothing Extended Kalman Filter'
 * '<S5>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/Pitch Rate  Low Pass Filter'
 * '<S6>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/Roll Rate  Low Pass Filter'
 * '<S7>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/Va Pressure  Low Pass Filter'
 * '<S8>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/Yaw Rate  Low Pass Filter'
 * '<S9>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/alpha  Low Pass Filter'
 * '<S10>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/ax  Low Pass Filter'
 * '<S11>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/ay  Low Pass Filter'
 * '<S12>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/az  Low Pass Filter'
 * '<S13>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/Attitude Estimation Extended Kalman Filter with Filtering/Attitude Estimation Extended Kalman Filter'
 * '<S14>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/Attitude Estimation Extended Kalman Filter with Filtering/Attitude Estimation Extended Kalman Filter/Attitude Estimation Extended Kalman Filter'
 * '<S15>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/Attitude Estimation Extended Kalman Filter with Filtering/Attitude Estimation Extended Kalman Filter/Attitude Estimation Extended Kalman Filter/Correct1'
 * '<S16>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/Attitude Estimation Extended Kalman Filter with Filtering/Attitude Estimation Extended Kalman Filter/Attitude Estimation Extended Kalman Filter/Output'
 * '<S17>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/Attitude Estimation Extended Kalman Filter with Filtering/Attitude Estimation Extended Kalman Filter/Attitude Estimation Extended Kalman Filter/Predict'
 * '<S18>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/Attitude Estimation Extended Kalman Filter with Filtering/Attitude Estimation Extended Kalman Filter/Attitude Estimation Extended Kalman Filter/Correct1/Correct'
 * '<S19>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/Attitude Estimation Extended Kalman Filter with Filtering/Attitude Estimation Extended Kalman Filter/Attitude Estimation Extended Kalman Filter/Predict/Predict'
 * '<S20>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/GPS Smoothing Extended Kalman Filter/Chi  Low Pass Filter'
 * '<S21>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/GPS Smoothing Extended Kalman Filter/GPS Smoothing Extended Kalman Filter'
 * '<S22>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/GPS Smoothing Extended Kalman Filter/MATLAB Function'
 * '<S23>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/GPS Smoothing Extended Kalman Filter/Reciprocal'
 * '<S24>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/GPS Smoothing Extended Kalman Filter/GPS Smoothing Extended Kalman Filter/Correct1'
 * '<S25>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/GPS Smoothing Extended Kalman Filter/GPS Smoothing Extended Kalman Filter/Output'
 * '<S26>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/GPS Smoothing Extended Kalman Filter/GPS Smoothing Extended Kalman Filter/Predict'
 * '<S27>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/GPS Smoothing Extended Kalman Filter/GPS Smoothing Extended Kalman Filter/Correct1/Correct'
 * '<S28>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/State Estimation/GPS Smoothing Extended Kalman Filter/GPS Smoothing Extended Kalman Filter/Predict/Predict'
 */
#endif                                 /* RTW_HEADER_State_sf_h_ */
