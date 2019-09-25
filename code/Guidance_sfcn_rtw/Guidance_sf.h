/*
 * Guidance_sf.h
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

#ifndef RTW_HEADER_Guidance_sf_h_
#define RTW_HEADER_Guidance_sf_h_
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef Guidance_sf_COMMON_INCLUDES_
# define Guidance_sf_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME                Guidance_sf
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
#endif                                 /* Guidance_sf_COMMON_INCLUDES_ */

#include "Guidance_sf_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"
#include "rtGetInf.h"

/* Block signals (default storage) */
typedef struct {
  real_T flag;                         /* '<S3>/Path Manager Follow Waypoints Fillet' */
  real_T i;                            /* '<S3>/Path Manager Follow Waypoints Fillet' */
} B_Guidance_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: SkywalkerX8.Test.Waypoints
   * Referenced by: '<S3>/Unit Delay3'
   */
  real_T UnitDelay3_InitialCondition[36];
} ConstP_Guidance_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T *Va_c;                        /* '<Root>/Va_c+' */
  real_T *W[36];                       /* '<Root>/W' */
  real_T *pInertial[3];                /* '<Root>/p' */
  real_T *theta;                       /* '<Root>/theta' */
  real_T *alpha;                       /* '<Root>/alpha' */
  real_T *Chi;                         /* '<Root>/Chi' */
} ExternalUPtrs_Guidance_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T *Va_c;                        /* '<Root>/Va_c' */
  real_T *h_c;                         /* '<Root>/h_c' */
  real_T *Chi_c;                       /* '<Root>/Chi_c' */
} ExtY_Guidance_T;

/* Constant parameters (default storage) */
extern const ConstP_Guidance_T Guidance_ConstP;

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
 * hilite_system('SkywalkerX8_GuidanceAndNavigation_Verification/Guidance and Navigation')    - opens subsystem SkywalkerX8_GuidanceAndNavigation_Verification/Guidance and Navigation
 * hilite_system('SkywalkerX8_GuidanceAndNavigation_Verification/Guidance and Navigation/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'SkywalkerX8_GuidanceAndNavigation_Verification'
 * '<S1>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/Guidance and Navigation'
 * '<S2>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/Guidance and Navigation/Banked Turn Turn Radius Calculation'
 * '<S3>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/Guidance and Navigation/Fillet Path Manager'
 * '<S4>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/Guidance and Navigation/Path Following Algorithm'
 * '<S5>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/Guidance and Navigation/Fillet Path Manager/Path Manager Follow Waypoints Fillet'
 * '<S6>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/Guidance and Navigation/Path Following Algorithm/Orbit Following'
 * '<S7>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/Guidance and Navigation/Path Following Algorithm/Straight Line Path Following'
 * '<S8>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/Guidance and Navigation/Path Following Algorithm/Straight Line//Orbit Following Selection'
 */
#endif                                 /* RTW_HEADER_Guidance_sf_h_ */
