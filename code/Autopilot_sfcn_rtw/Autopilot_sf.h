/*
 * Autopilot_sf.h
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

#ifndef RTW_HEADER_Autopilot_sf_h_
#define RTW_HEADER_Autopilot_sf_h_
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef Autopilot_sf_COMMON_INCLUDES_
# define Autopilot_sf_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME                Autopilot_sf
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
#endif                                 /* Autopilot_sf_COMMON_INCLUDES_ */

#include "Autopilot_sf_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"

/* Block signals (default storage) */
typedef struct {
  real_T Sum1;                         /* '<S20>/Sum1' */
  real_T DiscreteTimeIntegrator;       /* '<S20>/Discrete-Time Integrator' */
  real_T Product1;                     /* '<S20>/Product1' */
  real_T Saturation;                   /* '<S20>/Saturation' */
  real_T ClampSwitch;                  /* '<S22>/Clamp Switch' */
  real_T DiscreteTimeIntegrator_k;     /* '<S22>/Discrete-Time Integrator' */
  real_T Product1_c;                   /* '<S22>/Product1' */
  real_T Sum2;                         /* '<S22>/Sum2' */
  real_T DifferenceInputs2;            /* '<S9>/Difference Inputs2' */
  real_T ClampSwitch_p;                /* '<S24>/Clamp Switch' */
  real_T DiscreteTimeIntegrator_g;     /* '<S24>/Discrete-Time Integrator' */
  real_T theta_c;                      /* '<S24>/Product1' */
  real_T Saturation_c;                 /* '<S24>/Saturation' */
  real_T IC;                           /* '<S1>/IC' */
  real_T theta_c_m;                    /* '<S1>/IC1' */
  real_T Product1_k;                   /* '<S17>/Product1' */
  real_T ClampSwitch_c;                /* '<S18>/Clamp Switch' */
  real_T DiscreteTimeIntegrator_f;     /* '<S18>/Discrete-Time Integrator' */
  real_T Product1_n;                   /* '<S13>/Product1' */
  real_T ClampSwitch_m;                /* '<S10>/Clamp Switch' */
  real_T DiscreteTimeIntegrator_h;     /* '<S10>/Discrete-Time Integrator' */
  real_T ClampSwitch_n;                /* '<S14>/Clamp Switch' */
  real_T DiscreteTimeIntegrator_n;     /* '<S14>/Discrete-Time Integrator' */
  real_T Nda_e;                        /* '<S12>/Product1' */
  real_T Nde_e;                        /* '<S16>/Product1' */
  real_T dt;                           /* '<S1>/Altitude Control State Machine' */
  real_T theta_c_f;                    /* '<S1>/Altitude Control State Machine' */
  boolean_T NotEqual;                  /* '<S11>/NotEqual' */
  boolean_T NotEqual_g;                /* '<S15>/NotEqual' */
  boolean_T NotEqual_j;                /* '<S19>/NotEqual' */
  boolean_T NotEqual_h;                /* '<S21>/NotEqual' */
  boolean_T NotEqual_a;                /* '<S23>/NotEqual' */
  boolean_T NotEqual_n;                /* '<S25>/NotEqual' */
} B_Autopilot_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: SkywalkerX8.Control.Lateral.ChiController.Digital.KiChi
   * Referenced by: '<S3>/PIDF Controller Chi Ki 2D Lookup Table'
   */
  real_T PIDFControllerChiKi2DLookupTabl[10];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S3>/PIDF Controller Chi Ki 2D Lookup Table'
   *   '<S3>/PIDF Controller Chi Kp 2D Lookup Table'
   *   '<S4>/PDF Controller Phi 2DOF Kd 2D Lookup Table'
   *   '<S4>/PDF Controller Phi 2DOF Kp 2D Lookup Table'
   *   '<S4>/PDF Controller Phi 2DOF N 2D Lookup Table'
   *   '<S4>/PIDF Controller Phi Kd 2D Lookup Table'
   *   '<S4>/PIDF Controller Phi Ki 2D Lookup Table'
   *   '<S4>/PIDF Controller Phi Kp 2D Lookup Table'
   *   '<S4>/PIDF Controller Phi N 2D Lookup Table'
   *   '<S5>/PDF Controller theta 2DOF Kd 2D Lookup Table'
   *   '<S5>/PDF Controller theta 2DOF Kp 2D Lookup Table'
   *   '<S5>/PDF Controller theta 2DOF N 2D Lookup Table'
   *   '<S5>/PIDF Controller theta Kd 2D Lookup Table'
   *   '<S5>/PIDF Controller theta Ki 2D Lookup Table'
   *   '<S5>/PIDF Controller theta Kp 2D Lookup Table'
   *   '<S5>/PIDF Controller theta N 2D Lookup Table'
   *   '<S6>/PIDF Controller Va_dt Kd Lookup Table'
   *   '<S6>/PIDF Controller Va_dt Ki Lookup Table'
   *   '<S6>/PIDF Controller Va_dt Kp Lookup Table'
   *   '<S6>/PIDF Controller Va_dt N Lookup Table'
   *   '<S7>/PIDF Controller Va_theta Kd 2D Lookup Table'
   *   '<S7>/PIDF Controller Va_theta Ki 2D Lookup Table'
   *   '<S7>/PIDF Controller Va_theta Kp 2D Lookup Table'
   *   '<S7>/PIDF Controller Va_theta N 2D Lookup Table'
   */
  real_T pooled1[10];

  /* Expression: SkywalkerX8.Control.Lateral.PhiController.Digital.KiPhi
   * Referenced by: '<S4>/PIDF Controller Phi Ki 2D Lookup Table'
   */
  real_T PIDFControllerPhiKi2DLookupTabl[10];

  /* Expression: SkywalkerX8.Control.Longitudinal.thetaController.Digital.KiTheta
   * Referenced by: '<S5>/PIDF Controller theta Ki 2D Lookup Table'
   */
  real_T PIDFControllerthetaKi2DLookupTa[60];

  /* Pooled Parameter (Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray)
   * Referenced by:
   *   '<S5>/PDF Controller theta 2DOF Kd 2D Lookup Table'
   *   '<S5>/PDF Controller theta 2DOF Kp 2D Lookup Table'
   *   '<S5>/PDF Controller theta 2DOF N 2D Lookup Table'
   *   '<S5>/PIDF Controller theta Kd 2D Lookup Table'
   *   '<S5>/PIDF Controller theta Ki 2D Lookup Table'
   *   '<S5>/PIDF Controller theta Kp 2D Lookup Table'
   *   '<S5>/PIDF Controller theta N 2D Lookup Table'
   *   '<S7>/PIDF Controller Va_theta Kd 2D Lookup Table'
   *   '<S7>/PIDF Controller Va_theta Ki 2D Lookup Table'
   *   '<S7>/PIDF Controller Va_theta Kp 2D Lookup Table'
   *   '<S7>/PIDF Controller Va_theta N 2D Lookup Table'
   */
  real_T pooled2[6];

  /* Expression: SkywalkerX8.Control.Longitudinal.VaThetaController.Digital.KiVaTheta
   * Referenced by: '<S7>/PIDF Controller Va_theta Ki 2D Lookup Table'
   */
  real_T PIDFControllerVa_thetaKi2DLooku[60];

  /* Expression: SkywalkerX8.Control.Longitudinal.VaDtController.Digital.KpVaDt
   * Referenced by: '<S6>/PIDF Controller Va_dt Kp Lookup Table'
   */
  real_T PIDFControllerVa_dtKpLookupTabl[10];

  /* Expression: SkywalkerX8.Control.Longitudinal.VaDtController.Digital.KiVaDt
   * Referenced by: '<S6>/PIDF Controller Va_dt Ki Lookup Table'
   */
  real_T PIDFControllerVa_dtKiLookupTabl[10];

  /* Expression: SkywalkerX8.Control.Longitudinal.VaDtController.Digital.NVaDt
   * Referenced by: '<S6>/PIDF Controller Va_dt N Lookup Table'
   */
  real_T PIDFControllerVa_dtNLookupTable[10];

  /* Expression: SkywalkerX8.Control.Longitudinal.VaDtController.Digital.KdVaDt
   * Referenced by: '<S6>/PIDF Controller Va_dt Kd Lookup Table'
   */
  real_T PIDFControllerVa_dtKdLookupTabl[10];

  /* Expression: SkywalkerX8.Control.Longitudinal.VaThetaController.Digital.KpVaTheta
   * Referenced by: '<S7>/PIDF Controller Va_theta Kp 2D Lookup Table'
   */
  real_T PIDFControllerVa_thetaKp2DLooku[60];

  /* Expression: SkywalkerX8.Control.Longitudinal.VaThetaController.Digital.NVaTheta
   * Referenced by: '<S7>/PIDF Controller Va_theta N 2D Lookup Table'
   */
  real_T PIDFControllerVa_thetaN2DLookup[60];

  /* Expression: SkywalkerX8.Control.Longitudinal.VaThetaController.Digital.KdVaTheta
   * Referenced by: '<S7>/PIDF Controller Va_theta Kd 2D Lookup Table'
   */
  real_T PIDFControllerVa_thetaKd2DLooku[60];

  /* Expression: SkywalkerX8.Control.Longitudinal.thetaController.Digital.KpTheta2DOF
   * Referenced by: '<S5>/PDF Controller theta 2DOF Kp 2D Lookup Table'
   */
  real_T PDFControllertheta2DOFKp2DLooku[60];

  /* Expression: SkywalkerX8.Control.Longitudinal.thetaController.Digital.NTheta2DOF
   * Referenced by: '<S5>/PDF Controller theta 2DOF N 2D Lookup Table'
   */
  real_T PDFControllertheta2DOFN2DLookup[60];

  /* Expression: SkywalkerX8.Control.Longitudinal.thetaController.Digital.KdTheta2DOF
   * Referenced by: '<S5>/PDF Controller theta 2DOF Kd 2D Lookup Table'
   */
  real_T PDFControllertheta2DOFKd2DLooku[60];

  /* Expression: SkywalkerX8.Control.Longitudinal.thetaController.Digital.KpTheta
   * Referenced by: '<S5>/PIDF Controller theta Kp 2D Lookup Table'
   */
  real_T PIDFControllerthetaKp2DLookupTa[60];

  /* Expression: SkywalkerX8.Control.Lateral.PhiController.Digital.KpPhi2DOF
   * Referenced by: '<S4>/PDF Controller Phi 2DOF Kp 2D Lookup Table'
   */
  real_T PDFControllerPhi2DOFKp2DLookupT[10];

  /* Expression: SkywalkerX8.Control.Lateral.PhiController.Digital.NPhi2DOF
   * Referenced by: '<S4>/PDF Controller Phi 2DOF N 2D Lookup Table'
   */
  real_T PDFControllerPhi2DOFN2DLookupTa[10];

  /* Expression: SkywalkerX8.Control.Lateral.PhiController.Digital.KdPhi2DOF
   * Referenced by: '<S4>/PDF Controller Phi 2DOF Kd 2D Lookup Table'
   */
  real_T PDFControllerPhi2DOFKd2DLookupT[10];

  /* Expression: SkywalkerX8.Control.Lateral.ChiController.Digital.KpChi
   * Referenced by: '<S3>/PIDF Controller Chi Kp 2D Lookup Table'
   */
  real_T PIDFControllerChiKp2DLookupTabl[10];

  /* Expression: SkywalkerX8.Control.Lateral.PhiController.Digital.KpPhi
   * Referenced by: '<S4>/PIDF Controller Phi Kp 2D Lookup Table'
   */
  real_T PIDFControllerPhiKp2DLookupTabl[10];

  /* Expression: SkywalkerX8.Control.Lateral.PhiController.Digital.KdPhi
   * Referenced by: '<S4>/PIDF Controller Phi Kd 2D Lookup Table'
   */
  real_T PIDFControllerPhiKd2DLookupTabl[10];

  /* Expression: SkywalkerX8.Control.Lateral.PhiController.Digital.NPhi
   * Referenced by: '<S4>/PIDF Controller Phi N 2D Lookup Table'
   */
  real_T PIDFControllerPhiN2DLookupTable[10];

  /* Expression: SkywalkerX8.Control.Longitudinal.thetaController.Digital.KdTheta
   * Referenced by: '<S5>/PIDF Controller theta Kd 2D Lookup Table'
   */
  real_T PIDFControllerthetaKd2DLookupTa[60];

  /* Expression: SkywalkerX8.Control.Longitudinal.thetaController.Digital.NTheta
   * Referenced by: '<S5>/PIDF Controller theta N 2D Lookup Table'
   */
  real_T PIDFControllerthetaN2DLookupTab[60];

  /* Pooled Parameter (Expression: )
   * Referenced by:
   *   '<S5>/PDF Controller theta 2DOF Kd 2D Lookup Table'
   *   '<S5>/PDF Controller theta 2DOF Kp 2D Lookup Table'
   *   '<S5>/PDF Controller theta 2DOF N 2D Lookup Table'
   *   '<S5>/PIDF Controller theta Kd 2D Lookup Table'
   *   '<S5>/PIDF Controller theta Ki 2D Lookup Table'
   *   '<S5>/PIDF Controller theta Kp 2D Lookup Table'
   *   '<S5>/PIDF Controller theta N 2D Lookup Table'
   *   '<S7>/PIDF Controller Va_theta Kd 2D Lookup Table'
   *   '<S7>/PIDF Controller Va_theta Ki 2D Lookup Table'
   *   '<S7>/PIDF Controller Va_theta Kp 2D Lookup Table'
   *   '<S7>/PIDF Controller Va_theta N 2D Lookup Table'
   */
  uint32_T pooled14[2];
} ConstP_Autopilot_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T *Va_c;                        /* '<Root>/Va_c' */
  real_T *h_c;                         /* '<Root>/h_c' */
  real_T *Chi_c;                       /* '<Root>/Chi_c' */
  real_T *Va;                          /* '<Root>/Va' */
  real_T *h;                           /* '<Root>/h' */
  real_T *Theta;                       /* '<Root>/theta' */
  real_T *alpha;                       /* '<Root>/alpha' */
  real_T *q;                           /* '<Root>/q' */
  real_T *Chi;                         /* '<Root>/Chi' */
  real_T *Phi;                         /* '<Root>/Phi' */
  real_T *p;                           /* '<Root>/p' */
} ExternalUPtrs_Autopilot_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T *dt;                          /* '<Root>/dt' */
  real_T *der;                         /* '<Root>/der' */
  real_T *del;                         /* '<Root>/del' */
} ExtY_Autopilot_T;

/* Constant parameters (default storage) */
extern const ConstP_Autopilot_T Autopilot_ConstP;

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
 * hilite_system('SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital')    - opens subsystem SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital
 * hilite_system('SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'SkywalkerX8_GuidanceAndNavigation_Verification'
 * '<S1>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital'
 * '<S2>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Altitude Control State Machine'
 * '<S3>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Chi Digital'
 * '<S4>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Phi Digital'
 * '<S5>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Theta  Digital'
 * '<S6>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Va_dt Digital'
 * '<S7>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Va_theta Digital'
 * '<S8>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller h_theta Digital'
 * '<S9>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/h Rate Limiter Dynamic'
 * '<S10>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Chi Digital/PIDF Controller Va_theta'
 * '<S11>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Chi Digital/PIDF Controller Va_theta/Clamping circuit'
 * '<S12>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Phi Digital/DF Controller Phi'
 * '<S13>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Phi Digital/PDF Controller Phi 2DOF'
 * '<S14>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Phi Digital/PI Controller Phi'
 * '<S15>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Phi Digital/PI Controller Phi/Clamping circuit'
 * '<S16>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Theta  Digital/DF Controller Theta'
 * '<S17>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Theta  Digital/PDF Controller Theta 2DOF'
 * '<S18>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Theta  Digital/PI Controller Theta'
 * '<S19>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Theta  Digital/PI Controller Theta/Clamping circuit'
 * '<S20>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Va_dt Digital/PIDF Controller Va_dt'
 * '<S21>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Va_dt Digital/PIDF Controller Va_dt/Clamping circuit'
 * '<S22>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Va_theta Digital/PIDF Controller Va_theta'
 * '<S23>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Va_theta Digital/PIDF Controller Va_theta/Clamping circuit'
 * '<S24>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller h_theta Digital/PIDF Controller h_theta'
 * '<S25>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller h_theta Digital/PIDF Controller h_theta/Clamping circuit'
 * '<S26>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/h Rate Limiter Dynamic/Saturation Dynamic'
 */
#endif                                 /* RTW_HEADER_Autopilot_sf_h_ */
