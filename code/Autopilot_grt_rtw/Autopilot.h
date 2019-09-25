/*
 * Autopilot.h
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

#ifndef RTW_HEADER_Autopilot_h_
#define RTW_HEADER_Autopilot_h_
#include <math.h>
#include <string.h>
#include <float.h>
#include <stddef.h>
#ifndef Autopilot_COMMON_INCLUDES_
# define Autopilot_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#endif                                 /* Autopilot_COMMON_INCLUDES_ */

#include "Autopilot_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWLogInfo
# define rtmGetRTWLogInfo(rtm)         ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               (&(rtm)->Timing.taskTime0)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T PIDFControllerVa_dtKpLookupTabl;/* '<S6>/PIDF Controller Va_dt Kp Lookup Table' */
  real_T PIDFControllerVa_dtKiLookupTabl;/* '<S6>/PIDF Controller Va_dt Ki Lookup Table' */
  real_T Tracking;                     /* '<S21>/Tracking' */
  real_T Sum1;                         /* '<S21>/Sum1' */
  real_T DiscreteTimeIntegrator;       /* '<S21>/Discrete-Time Integrator' */
  real_T PIDFControllerVa_dtNLookupTable;/* '<S6>/PIDF Controller Va_dt N Lookup Table' */
  real_T PIDFControllerVa_dtKdLookupTabl;/* '<S6>/PIDF Controller Va_dt Kd Lookup Table' */
  real_T DiscreteTimeIntegrator1;      /* '<S21>/Discrete-Time Integrator1' */
  real_T Product1;                     /* '<S21>/Product1' */
  real_T Saturation;                   /* '<S21>/Saturation' */
  real_T PIDFControllerVa_thetaKp2DLooku;/* '<S7>/PIDF Controller Va_theta Kp 2D Lookup Table' */
  real_T PIDFControllerVa_thetaKi2DLooku;/* '<S7>/PIDF Controller Va_theta Ki 2D Lookup Table' */
  real_T Tracking_c;                   /* '<S23>/Tracking' */
  real_T ClampSwitch;                  /* '<S23>/Clamp Switch' */
  real_T DiscreteTimeIntegrator_o;     /* '<S23>/Discrete-Time Integrator' */
  real_T PIDFControllerVa_thetaN2DLookup;/* '<S7>/PIDF Controller Va_theta N 2D Lookup Table' */
  real_T PIDFControllerVa_thetaKd2DLooku;/* '<S7>/PIDF Controller Va_theta Kd 2D Lookup Table' */
  real_T DiscreteTimeIntegrator1_g;    /* '<S23>/Discrete-Time Integrator1' */
  real_T Product1_o;                   /* '<S23>/Product1' */
  real_T Saturation_a;                 /* '<S23>/Saturation' */
  real_T DifferenceInputs2;            /* '<S10>/Difference Inputs2' */
  real_T Sum1_n;                       /* '<S25>/Sum1' */
  real_T ClampSwitch_e;                /* '<S25>/Clamp Switch' */
  real_T DiscreteTimeIntegrator_o0;    /* '<S25>/Discrete-Time Integrator' */
  real_T Saturation_h;                 /* '<S25>/Saturation' */
  real_T PDFControllertheta2DOFKp2DLooku;/* '<S5>/PDF Controller theta 2DOF Kp 2D Lookup Table' */
  real_T theta_c;                      /* '<S1>/IC1' */
  real_T PDFControllertheta2DOFN2DLookup;/* '<S5>/PDF Controller theta 2DOF N 2D Lookup Table' */
  real_T PDFControllertheta2DOFKd2DLooku;/* '<S5>/PDF Controller theta 2DOF Kd 2D Lookup Table' */
  real_T DiscreteTimeIntegrator_m;     /* '<S18>/Discrete-Time Integrator' */
  real_T Product1_oo;                  /* '<S18>/Product1' */
  real_T PIDFControllerthetaKi2DLookupTa;/* '<S5>/PIDF Controller theta Ki 2D Lookup Table' */
  real_T Switch2;                      /* '<S1>/Switch2' */
  real_T ClampSwitch_b;                /* '<S19>/Clamp Switch' */
  real_T DiscreteTimeIntegrator_d;     /* '<S19>/Discrete-Time Integrator' */
  real_T PIDFControllerthetaKp2DLookupTa;/* '<S5>/PIDF Controller theta Kp 2D Lookup Table' */
  real_T de;                           /* '<S17>/Discrete-Time Integrator' */
  real_T IOut;                         /* '<S11>/IOut' */
  real_T ClampSwitch_c;                /* '<S11>/Clamp Switch' */
  real_T DiscreteTimeIntegrator_e;     /* '<S11>/Discrete-Time Integrator' */
  real_T IOut_m;                       /* '<S15>/IOut' */
  real_T ClampSwitch_ck;               /* '<S15>/Clamp Switch' */
  real_T DiscreteTimeIntegrator_oy;    /* '<S15>/Discrete-Time Integrator' */
  real_T Saturation_g;                 /* '<S4>/Saturation' */
  real_T dt;                           /* '<S1>/Altitude Control State Machine' */
  real_T theta_c_f;                    /* '<S1>/Altitude Control State Machine' */
  boolean_T NotEqual;                  /* '<S12>/NotEqual' */
  boolean_T NotEqual_e;                /* '<S16>/NotEqual' */
  boolean_T NotEqual_e0;               /* '<S26>/NotEqual' */
} B_Autopilot_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T DelayInput2_DSTATE;           /* '<S9>/Delay Input2' */
  real_T Delay_DSTATE;                 /* '<S21>/Delay' */
  real_T UnitDelay1_DSTATE;            /* '<S1>/Unit Delay1' */
  real_T DiscreteTimeIntegrator_DSTATE;/* '<S21>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator1_DSTATE;/* '<S21>/Discrete-Time Integrator1' */
  real_T Delay_DSTATE_b;               /* '<S23>/Delay' */
  real_T UnitDelay_DSTATE;             /* '<S1>/Unit Delay' */
  real_T DiscreteTimeIntegrator_DSTATE_d;/* '<S23>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator1_DSTAT_d;/* '<S23>/Discrete-Time Integrator1' */
  real_T DelayInput2_DSTATE_n;         /* '<S10>/Delay Input2' */
  real_T Delay_DSTATE_a;               /* '<S25>/Delay' */
  real_T DiscreteTimeIntegrator_DSTATE_k;/* '<S25>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator1_DSTAT_g;/* '<S25>/Discrete-Time Integrator1' */
  real_T DiscreteTimeIntegrator_DSTATE_f;/* '<S18>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator_DSTATE_a;/* '<S19>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator_DSTATE_j;/* '<S17>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator_DSTATE_h;/* '<S14>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator_DSTAT_hv;/* '<S11>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator_DSTAT_f2;/* '<S15>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator_DSTATE_b;/* '<S13>/Discrete-Time Integrator' */
  boolean_T Delay_DSTATE_j;            /* '<S22>/Delay' */
  uint8_T is_c3_Autopilot;             /* '<S1>/Altitude Control State Machine' */
  boolean_T Memory_PreviousInput;      /* '<S24>/Memory' */
  boolean_T IC_FirstOutputTime;        /* '<S1>/IC' */
  boolean_T IC1_FirstOutputTime;       /* '<S1>/IC1' */
  boolean_T Memory_PreviousInput_o;    /* '<S20>/Memory' */
} DW_Autopilot_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T Va_c;                         /* '<Root>/Va_c' */
  real_T h_c;                          /* '<Root>/h_c' */
  real_T Chi_c;                        /* '<Root>/Chi_c' */
  real_T Va;                           /* '<Root>/Va' */
  real_T h;                            /* '<Root>/h' */
  real_T theta;                        /* '<Root>/theta' */
  real_T alpha;                        /* '<Root>/alpha' */
  real_T q;                            /* '<Root>/q' */
  real_T Chi;                          /* '<Root>/Chi' */
  real_T Phi;                          /* '<Root>/Phi' */
  real_T p;                            /* '<Root>/p' */
} ExtU_Autopilot_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T dt;                           /* '<Root>/dt' */
  real_T der;                          /* '<Root>/der' */
  real_T del;                          /* '<Root>/del' */
} ExtY_Autopilot_T;

/* Parameters (default storage) */
struct P_Autopilot_T_ {
  real_T AltitudeControlStateMachine_h_h;/* Mask Parameter: AltitudeControlStateMachine_h_h
                                          * Referenced by: '<S1>/Altitude Control State Machine'
                                          */
  real_T AltitudeControlStateMachine_h_t;/* Mask Parameter: AltitudeControlStateMachine_h_t
                                          * Referenced by: '<S1>/Altitude Control State Machine'
                                          */
  real_T AltitudeControlStateMachine_hys;/* Mask Parameter: AltitudeControlStateMachine_hys
                                          * Referenced by: '<S1>/Altitude Control State Machine'
                                          */
  real_T VaRateLimiter_initOutput;     /* Mask Parameter: VaRateLimiter_initOutput
                                        * Referenced by: '<S9>/Delay Input2'
                                        */
  real_T hRateLimiterDynamic_initOutput;/* Mask Parameter: hRateLimiterDynamic_initOutput
                                         * Referenced by: '<S10>/Delay Input2'
                                         */
  real_T AltitudeControlStateMachine_the;/* Mask Parameter: AltitudeControlStateMachine_the
                                          * Referenced by: '<S1>/Altitude Control State Machine'
                                          */
  boolean_T AltitudeControlStateMachine_Pre;/* Mask Parameter: AltitudeControlStateMachine_Pre
                                             * Referenced by: '<S1>/Altitude Control State Machine'
                                             */
  real_T Constant5_Value;              /* Expression: 0
                                        * Referenced by: '<S1>/Constant5'
                                        */
  real_T Constant4_Value;              /* Expression: 0
                                        * Referenced by: '<S1>/Constant4'
                                        */
  real_T Constant3_Value;              /* Expression: 0
                                        * Referenced by: '<S1>/Constant3'
                                        */
  real_T Constant2_Value;              /* Expression: 0
                                        * Referenced by: '<S1>/Constant2'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S11>/Constant'
                                        */
  real_T Constant_Value_g;             /* Expression: 0
                                        * Referenced by: '<S15>/Constant'
                                        */
  real_T Constant_Value_p;             /* Expression: 0
                                        * Referenced by: '<S19>/Constant'
                                        */
  real_T Constant_Value_pv;            /* Expression: 0
                                        * Referenced by: '<S21>/Constant'
                                        */
  real_T Constant_Value_a;             /* Expression: 0
                                        * Referenced by: '<S23>/Constant'
                                        */
  real_T Constant_Value_gg;            /* Expression: 0
                                        * Referenced by: '<S25>/Constant'
                                        */
  real_T Constant1_Value;              /* Expression: -1.5*SkywalkerX8.System.Gravity
                                        * Referenced by: '<S1>/Constant1'
                                        */
  real_T Gain_Gain;                    /* Expression: sin(0.5*SkywalkerX8.Control.Longitudinal.altController.lowerSaturationThetaC)
                                        * Referenced by: '<S1>/Gain'
                                        */
  real_T PIDFControllerVa_dtKpLookupTabl[10];/* Expression: SkywalkerX8.Control.Longitudinal.VaDtController.Digital.KpVaDt
                                              * Referenced by: '<S6>/PIDF Controller Va_dt Kp Lookup Table'
                                              */
  real_T PIDFControllerVa_dtKpLookupTa_m[10];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray
                                              * Referenced by: '<S6>/PIDF Controller Va_dt Kp Lookup Table'
                                              */
  real_T Constant_Value_h;             /* Expression: 1.5*SkywalkerX8.System.Gravity
                                        * Referenced by: '<S1>/Constant'
                                        */
  real_T sampletime_WtEt;              /* Computed Parameter: sampletime_WtEt
                                        * Referenced by: '<S9>/sample time'
                                        */
  real_T PIDFControllerVa_dtKiLookupTabl[10];/* Expression: SkywalkerX8.Control.Longitudinal.VaDtController.Digital.KiVaDt
                                              * Referenced by: '<S6>/PIDF Controller Va_dt Ki Lookup Table'
                                              */
  real_T PIDFControllerVa_dtKiLookupTa_c[10];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray
                                              * Referenced by: '<S6>/PIDF Controller Va_dt Ki Lookup Table'
                                              */
  real_T Delay_InitialCondition;       /* Expression: SkywalkerX8.InitialConditions.dt
                                        * Referenced by: '<S21>/Delay'
                                        */
  real_T UnitDelay1_InitialCondition;  /* Expression: SkywalkerX8.InitialConditions.dt
                                        * Referenced by: '<S1>/Unit Delay1'
                                        */
  real_T PIDFControllerVa_dtKtTrackingGa;/* Expression: SkywalkerX8.Control.Longitudinal.VaDtController.KtScalar
                                          * Referenced by: '<S6>/PIDF Controller Va_dt Kt Tracking Gain Scalar'
                                          */
  real_T DiscreteTimeIntegrator_gainval;/* Computed Parameter: DiscreteTimeIntegrator_gainval
                                         * Referenced by: '<S21>/Discrete-Time Integrator'
                                         */
  real_T DiscreteTimeIntegrator_IC;    /* Expression: SkywalkerX8.InitialConditions.dt
                                        * Referenced by: '<S21>/Discrete-Time Integrator'
                                        */
  real_T PIDFControllerVa_dtNLookupTable[10];/* Expression: SkywalkerX8.Control.Longitudinal.VaDtController.Digital.NVaDt
                                              * Referenced by: '<S6>/PIDF Controller Va_dt N Lookup Table'
                                              */
  real_T PIDFControllerVa_dtNLookupTab_o[10];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray
                                              * Referenced by: '<S6>/PIDF Controller Va_dt N Lookup Table'
                                              */
  real_T PIDFControllerVa_dtKdLookupTabl[10];/* Expression: SkywalkerX8.Control.Longitudinal.VaDtController.Digital.KdVaDt
                                              * Referenced by: '<S6>/PIDF Controller Va_dt Kd Lookup Table'
                                              */
  real_T PIDFControllerVa_dtKdLookupTa_b[10];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray
                                              * Referenced by: '<S6>/PIDF Controller Va_dt Kd Lookup Table'
                                              */
  real_T DiscreteTimeIntegrator1_gainval;/* Computed Parameter: DiscreteTimeIntegrator1_gainval
                                          * Referenced by: '<S21>/Discrete-Time Integrator1'
                                          */
  real_T DiscreteTimeIntegrator1_IC;   /* Expression: 0
                                        * Referenced by: '<S21>/Discrete-Time Integrator1'
                                        */
  real_T Saturation_UpperSat;          /* Expression: SkywalkerX8.Control.Longitudinal.VaDtController.upperSaturationDt
                                        * Referenced by: '<S21>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: SkywalkerX8.Control.Longitudinal.VaDtController.lowerSaturationDt
                                        * Referenced by: '<S21>/Saturation'
                                        */
  real_T PIDFControllerVa_thetaKp2DLooku[60];/* Expression: SkywalkerX8.Control.Longitudinal.VaThetaController.Digital.KpVaTheta
                                              * Referenced by: '<S7>/PIDF Controller Va_theta Kp 2D Lookup Table'
                                              */
  real_T PIDFControllerVa_thetaKp2DLoo_k[10];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray
                                              * Referenced by: '<S7>/PIDF Controller Va_theta Kp 2D Lookup Table'
                                              */
  real_T PIDFControllerVa_thetaKp2DLoo_b[6];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray
                                             * Referenced by: '<S7>/PIDF Controller Va_theta Kp 2D Lookup Table'
                                             */
  real_T PIDFControllerVa_thetaKi2DLooku[60];/* Expression: SkywalkerX8.Control.Longitudinal.VaThetaController.Digital.KiVaTheta
                                              * Referenced by: '<S7>/PIDF Controller Va_theta Ki 2D Lookup Table'
                                              */
  real_T PIDFControllerVa_thetaKi2DLoo_f[10];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray
                                              * Referenced by: '<S7>/PIDF Controller Va_theta Ki 2D Lookup Table'
                                              */
  real_T PIDFControllerVa_thetaKi2DLoo_k[6];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray
                                             * Referenced by: '<S7>/PIDF Controller Va_theta Ki 2D Lookup Table'
                                             */
  real_T Delay_InitialCondition_i;     /* Expression: -SkywalkerX8.InitialConditions.PhiThetaPsi(2)
                                        * Referenced by: '<S23>/Delay'
                                        */
  real_T UnitDelay_InitialCondition;   /* Expression: SkywalkerX8.InitialConditions.PhiThetaPsi(2)
                                        * Referenced by: '<S1>/Unit Delay'
                                        */
  real_T TrackingSignInversion_Gain;   /* Expression: -1
                                        * Referenced by: '<S7>/Tracking Sign Inversion'
                                        */
  real_T PIDFControllerVa_thetaKtTrackin;/* Expression: SkywalkerX8.Control.Longitudinal.VaThetaController.KtScalar
                                          * Referenced by: '<S7>/PIDF Controller Va_theta Kt Tracking Gain Scalar'
                                          */
  real_T DiscreteTimeIntegrator_gainva_k;/* Computed Parameter: DiscreteTimeIntegrator_gainva_k
                                          * Referenced by: '<S23>/Discrete-Time Integrator'
                                          */
  real_T DiscreteTimeIntegrator_IC_h;  /* Expression: -SkywalkerX8.InitialConditions.PhiThetaPsi(2)
                                        * Referenced by: '<S23>/Discrete-Time Integrator'
                                        */
  real_T PIDFControllerVa_thetaN2DLookup[60];/* Expression: SkywalkerX8.Control.Longitudinal.VaThetaController.Digital.NVaTheta
                                              * Referenced by: '<S7>/PIDF Controller Va_theta N 2D Lookup Table'
                                              */
  real_T PIDFControllerVa_thetaN2DLook_l[10];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray
                                              * Referenced by: '<S7>/PIDF Controller Va_theta N 2D Lookup Table'
                                              */
  real_T PIDFControllerVa_thetaN2DLook_c[6];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray
                                             * Referenced by: '<S7>/PIDF Controller Va_theta N 2D Lookup Table'
                                             */
  real_T PIDFControllerVa_thetaKd2DLooku[60];/* Expression: SkywalkerX8.Control.Longitudinal.VaThetaController.Digital.KdVaTheta
                                              * Referenced by: '<S7>/PIDF Controller Va_theta Kd 2D Lookup Table'
                                              */
  real_T PIDFControllerVa_thetaKd2DLoo_f[10];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray
                                              * Referenced by: '<S7>/PIDF Controller Va_theta Kd 2D Lookup Table'
                                              */
  real_T PIDFControllerVa_thetaKd2DLoo_i[6];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray
                                             * Referenced by: '<S7>/PIDF Controller Va_theta Kd 2D Lookup Table'
                                             */
  real_T DiscreteTimeIntegrator1_gainv_b;/* Computed Parameter: DiscreteTimeIntegrator1_gainv_b
                                          * Referenced by: '<S23>/Discrete-Time Integrator1'
                                          */
  real_T DiscreteTimeIntegrator1_IC_p; /* Expression: 0
                                        * Referenced by: '<S23>/Discrete-Time Integrator1'
                                        */
  real_T Saturation_UpperSat_c;        /* Expression: SkywalkerX8.Control.Longitudinal.VaThetaController.upperSaturationThetaC
                                        * Referenced by: '<S23>/Saturation'
                                        */
  real_T Saturation_LowerSat_d;        /* Expression: SkywalkerX8.Control.Longitudinal.VaThetaController.lowerSaturationThetaC
                                        * Referenced by: '<S23>/Saturation'
                                        */
  real_T SignInversion_Gain;           /* Expression: -1
                                        * Referenced by: '<S7>/Sign Inversion'
                                        */
  real_T PIDFControllerh_thetaKp2DLookup[60];/* Expression: SkywalkerX8.Control.Longitudinal.altController.Digital.KpAlt
                                              * Referenced by: '<S8>/PIDF Controller h_theta Kp 2D Lookup Table'
                                              */
  real_T PIDFControllerh_thetaKp2DLook_g[10];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray
                                              * Referenced by: '<S8>/PIDF Controller h_theta Kp 2D Lookup Table'
                                              */
  real_T PIDFControllerh_thetaKp2DLook_j[6];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray
                                             * Referenced by: '<S8>/PIDF Controller h_theta Kp 2D Lookup Table'
                                             */
  real_T Gain1_Gain;                   /* Expression: sin(0.5*SkywalkerX8.Control.Longitudinal.altController.upperSaturationThetaC)
                                        * Referenced by: '<S1>/Gain1'
                                        */
  real_T sampletime_WtEt_k;            /* Computed Parameter: sampletime_WtEt_k
                                        * Referenced by: '<S10>/sample time'
                                        */
  real_T PIDFControllerh_thetaKi2DLookup[60];/* Expression: SkywalkerX8.Control.Longitudinal.altController.Digital.KiAlt
                                              * Referenced by: '<S8>/PIDF Controller h_theta Ki 2D Lookup Table'
                                              */
  real_T PIDFControllerh_thetaKi2DLook_m[10];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray
                                              * Referenced by: '<S8>/PIDF Controller h_theta Ki 2D Lookup Table'
                                              */
  real_T PIDFControllerh_thetaKi2DLook_b[6];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray
                                             * Referenced by: '<S8>/PIDF Controller h_theta Ki 2D Lookup Table'
                                             */
  real_T Delay_InitialCondition_in;    /* Expression: SkywalkerX8.InitialConditions.PhiThetaPsi(2)
                                        * Referenced by: '<S25>/Delay'
                                        */
  real_T PIDFControllerh_thetaKtTracking;/* Expression: SkywalkerX8.Control.Longitudinal.altController.KtScalar
                                          * Referenced by: '<S8>/PIDF Controller h_theta Kt Tracking Gain Scalar'
                                          */
  real_T DiscreteTimeIntegrator_gainva_p;/* Computed Parameter: DiscreteTimeIntegrator_gainva_p
                                          * Referenced by: '<S25>/Discrete-Time Integrator'
                                          */
  real_T DiscreteTimeIntegrator_IC_o;  /* Expression: SkywalkerX8.InitialConditions.PhiThetaPsi(2)
                                        * Referenced by: '<S25>/Discrete-Time Integrator'
                                        */
  real_T PIDFControllerh_thetaN2DLookupT[60];/* Expression: SkywalkerX8.Control.Longitudinal.altController.Digital.NAlt
                                              * Referenced by: '<S8>/PIDF Controller h_theta N 2D Lookup Table'
                                              */
  real_T PIDFControllerh_thetaN2DLooku_b[10];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray
                                              * Referenced by: '<S8>/PIDF Controller h_theta N 2D Lookup Table'
                                              */
  real_T PIDFControllerh_thetaN2DLooku_a[6];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray
                                             * Referenced by: '<S8>/PIDF Controller h_theta N 2D Lookup Table'
                                             */
  real_T PIDFControllerh_thetaKd2DLookup[60];/* Expression: SkywalkerX8.Control.Longitudinal.altController.Digital.KdAlt
                                              * Referenced by: '<S8>/PIDF Controller h_theta Kd 2D Lookup Table'
                                              */
  real_T PIDFControllerh_thetaKd2DLook_f[10];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray
                                              * Referenced by: '<S8>/PIDF Controller h_theta Kd 2D Lookup Table'
                                              */
  real_T PIDFControllerh_thetaKd2DLook_j[6];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray
                                             * Referenced by: '<S8>/PIDF Controller h_theta Kd 2D Lookup Table'
                                             */
  real_T DiscreteTimeIntegrator1_gainv_d;/* Computed Parameter: DiscreteTimeIntegrator1_gainv_d
                                          * Referenced by: '<S25>/Discrete-Time Integrator1'
                                          */
  real_T DiscreteTimeIntegrator1_IC_i; /* Expression: 0
                                        * Referenced by: '<S25>/Discrete-Time Integrator1'
                                        */
  real_T Saturation_UpperSat_k;        /* Expression: SkywalkerX8.Control.Longitudinal.altController.upperSaturationThetaC
                                        * Referenced by: '<S25>/Saturation'
                                        */
  real_T Saturation_LowerSat_o;        /* Expression: SkywalkerX8.Control.Longitudinal.altController.lowerSaturationThetaC
                                        * Referenced by: '<S25>/Saturation'
                                        */
  real_T IC_Value;                     /* Expression: SkywalkerX8.InitialConditions.dt
                                        * Referenced by: '<S1>/IC'
                                        */
  real_T PDFControllertheta2DOFKp2DLooku[60];/* Expression: SkywalkerX8.Control.Longitudinal.thetaController.Digital.KpTheta2DOF
                                              * Referenced by: '<S5>/PDF Controller theta 2DOF Kp 2D Lookup Table'
                                              */
  real_T PDFControllertheta2DOFKp2DLoo_l[10];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray
                                              * Referenced by: '<S5>/PDF Controller theta 2DOF Kp 2D Lookup Table'
                                              */
  real_T PDFControllertheta2DOFKp2DLoo_b[6];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray
                                             * Referenced by: '<S5>/PDF Controller theta 2DOF Kp 2D Lookup Table'
                                             */
  real_T IC1_Value;                    /* Expression: SkywalkerX8.InitialConditions.PhiThetaPsi(2)
                                        * Referenced by: '<S1>/IC1'
                                        */
  real_T PDFControllertheta2DOFN2DLookup[60];/* Expression: SkywalkerX8.Control.Longitudinal.thetaController.Digital.NTheta2DOF
                                              * Referenced by: '<S5>/PDF Controller theta 2DOF N 2D Lookup Table'
                                              */
  real_T PDFControllertheta2DOFN2DLook_i[10];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray
                                              * Referenced by: '<S5>/PDF Controller theta 2DOF N 2D Lookup Table'
                                              */
  real_T PDFControllertheta2DOFN2DLook_d[6];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray
                                             * Referenced by: '<S5>/PDF Controller theta 2DOF N 2D Lookup Table'
                                             */
  real_T PDFControllertheta2DOFKd2DLooku[60];/* Expression: SkywalkerX8.Control.Longitudinal.thetaController.Digital.KdTheta2DOF
                                              * Referenced by: '<S5>/PDF Controller theta 2DOF Kd 2D Lookup Table'
                                              */
  real_T PDFControllertheta2DOFKd2DLoo_n[10];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray
                                              * Referenced by: '<S5>/PDF Controller theta 2DOF Kd 2D Lookup Table'
                                              */
  real_T PDFControllertheta2DOFKd2DLoo_h[6];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray
                                             * Referenced by: '<S5>/PDF Controller theta 2DOF Kd 2D Lookup Table'
                                             */
  real_T DiscreteTimeIntegrator_gainva_f;/* Computed Parameter: DiscreteTimeIntegrator_gainva_f
                                          * Referenced by: '<S18>/Discrete-Time Integrator'
                                          */
  real_T DiscreteTimeIntegrator_IC_b;  /* Expression: 0
                                        * Referenced by: '<S18>/Discrete-Time Integrator'
                                        */
  real_T PIDFControllerthetaKi2DLookupTa[60];/* Expression: SkywalkerX8.Control.Longitudinal.thetaController.Digital.KiTheta
                                              * Referenced by: '<S5>/PIDF Controller theta Ki 2D Lookup Table'
                                              */
  real_T PIDFControllerthetaKi2DLookup_b[10];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray
                                              * Referenced by: '<S5>/PIDF Controller theta Ki 2D Lookup Table'
                                              */
  real_T PIDFControllerthetaKi2DLookup_m[6];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray
                                             * Referenced by: '<S5>/PIDF Controller theta Ki 2D Lookup Table'
                                             */
  real_T Switch2_Threshold;            /* Expression: deg2rad(1)
                                        * Referenced by: '<S1>/Switch2'
                                        */
  real_T DiscreteTimeIntegrator_gainv_p4;/* Computed Parameter: DiscreteTimeIntegrator_gainv_p4
                                          * Referenced by: '<S19>/Discrete-Time Integrator'
                                          */
  real_T DiscreteTimeIntegrator_IC_of; /* Expression: SkywalkerX8.InitialConditions.ThetaController.Integrator
                                        * Referenced by: '<S19>/Discrete-Time Integrator'
                                        */
  real_T PIDFControllerthetaKp2DLookupTa[60];/* Expression: SkywalkerX8.Control.Longitudinal.thetaController.Digital.KpTheta
                                              * Referenced by: '<S5>/PIDF Controller theta Kp 2D Lookup Table'
                                              */
  real_T PIDFControllerthetaKp2DLookup_n[10];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray
                                              * Referenced by: '<S5>/PIDF Controller theta Kp 2D Lookup Table'
                                              */
  real_T PIDFControllerthetaKp2DLookup_i[6];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray
                                             * Referenced by: '<S5>/PIDF Controller theta Kp 2D Lookup Table'
                                             */
  real_T DiscreteTimeIntegrator_gainva_o;/* Computed Parameter: DiscreteTimeIntegrator_gainva_o
                                          * Referenced by: '<S17>/Discrete-Time Integrator'
                                          */
  real_T DiscreteTimeIntegrator_IC_m;  /* Expression: 0
                                        * Referenced by: '<S17>/Discrete-Time Integrator'
                                        */
  real_T Saturation_UpperSat_i;        /* Expression: SkywalkerX8.Control.Longitudinal.thetaController.Digital.upperSaturationNegativeDe
                                        * Referenced by: '<S5>/Saturation'
                                        */
  real_T Saturation_LowerSat_om;       /* Expression: SkywalkerX8.Control.Longitudinal.thetaController.Digital.lowerSaturationNegativeDe
                                        * Referenced by: '<S5>/Saturation'
                                        */
  real_T SignInversion_Gain_f;         /* Expression: -1
                                        * Referenced by: '<S5>/Sign Inversion'
                                        */
  real_T PDFControllerPhi2DOFKp2DLookupT[10];/* Expression: SkywalkerX8.Control.Lateral.PhiController.Digital.KpPhi2DOF
                                              * Referenced by: '<S4>/PDF Controller Phi 2DOF Kp 2D Lookup Table'
                                              */
  real_T PDFControllerPhi2DOFKp2DLooku_l[10];/* Expression: SkywalkerX8.Control.Lateral.SchedulingVariables.VaArray
                                              * Referenced by: '<S4>/PDF Controller Phi 2DOF Kp 2D Lookup Table'
                                              */
  real_T Switch1_Threshold;            /* Expression: deg2rad(1)
                                        * Referenced by: '<S1>/Switch1'
                                        */
  real_T PDFControllerPhi2DOFN2DLookupTa[10];/* Expression: SkywalkerX8.Control.Lateral.PhiController.Digital.NPhi2DOF
                                              * Referenced by: '<S4>/PDF Controller Phi 2DOF N 2D Lookup Table'
                                              */
  real_T PDFControllerPhi2DOFN2DLookup_c[10];/* Expression: SkywalkerX8.Control.Lateral.SchedulingVariables.VaArray
                                              * Referenced by: '<S4>/PDF Controller Phi 2DOF N 2D Lookup Table'
                                              */
  real_T PDFControllerPhi2DOFKd2DLookupT[10];/* Expression: SkywalkerX8.Control.Lateral.PhiController.Digital.KdPhi2DOF
                                              * Referenced by: '<S4>/PDF Controller Phi 2DOF Kd 2D Lookup Table'
                                              */
  real_T PDFControllerPhi2DOFKd2DLooku_p[10];/* Expression: SkywalkerX8.Control.Lateral.SchedulingVariables.VaArray
                                              * Referenced by: '<S4>/PDF Controller Phi 2DOF Kd 2D Lookup Table'
                                              */
  real_T DiscreteTimeIntegrator_gainv_pv;/* Computed Parameter: DiscreteTimeIntegrator_gainv_pv
                                          * Referenced by: '<S14>/Discrete-Time Integrator'
                                          */
  real_T DiscreteTimeIntegrator_IC_a;  /* Expression: 0
                                        * Referenced by: '<S14>/Discrete-Time Integrator'
                                        */
  real_T PIDFControllerPhiKi2DLookupTabl[10];/* Expression: SkywalkerX8.Control.Lateral.PhiController.Digital.KiPhi
                                              * Referenced by: '<S4>/PIDF Controller Phi Ki 2D Lookup Table'
                                              */
  real_T PIDFControllerPhiKi2DLookupTa_j[10];/* Expression: SkywalkerX8.Control.Lateral.SchedulingVariables.VaArray
                                              * Referenced by: '<S4>/PIDF Controller Phi Ki 2D Lookup Table'
                                              */
  real_T PIDFControllerChiKp2DLookupTabl[10];/* Expression: SkywalkerX8.Control.Lateral.ChiController.Digital.KpChi
                                              * Referenced by: '<S3>/PIDF Controller Chi Kp 2D Lookup Table'
                                              */
  real_T PIDFControllerChiKp2DLookupTa_c[10];/* Expression: SkywalkerX8.Control.Lateral.SchedulingVariables.VaArray
                                              * Referenced by: '<S3>/PIDF Controller Chi Kp 2D Lookup Table'
                                              */
  real_T Switch3_Threshold;            /* Expression: deg2rad(1)
                                        * Referenced by: '<S1>/Switch3'
                                        */
  real_T Switch_Threshold;             /* Expression: deg2rad(1)
                                        * Referenced by: '<S1>/Switch'
                                        */
  real_T PIDFControllerChiKi2DLookupTabl[10];/* Expression: SkywalkerX8.Control.Lateral.ChiController.Digital.KiChi
                                              * Referenced by: '<S3>/PIDF Controller Chi Ki 2D Lookup Table'
                                              */
  real_T PIDFControllerChiKi2DLookupTa_o[10];/* Expression: SkywalkerX8.Control.Lateral.SchedulingVariables.VaArray
                                              * Referenced by: '<S3>/PIDF Controller Chi Ki 2D Lookup Table'
                                              */
  real_T DiscreteTimeIntegrator_gainv_on;/* Computed Parameter: DiscreteTimeIntegrator_gainv_on
                                          * Referenced by: '<S11>/Discrete-Time Integrator'
                                          */
  real_T DiscreteTimeIntegrator_IC_n;  /* Expression: SkywalkerX8.InitialConditions.PhiThetaPsi(1)
                                        * Referenced by: '<S11>/Discrete-Time Integrator'
                                        */
  real_T Saturation_UpperSat_e;        /* Expression: SkywalkerX8.Control.Lateral.ChiController.upperSaturationPhiC
                                        * Referenced by: '<S3>/Saturation'
                                        */
  real_T Saturation_LowerSat_l;        /* Expression: SkywalkerX8.Control.Lateral.ChiController.lowerSaturationPhiC
                                        * Referenced by: '<S3>/Saturation'
                                        */
  real_T DiscreteTimeIntegrator_gainva_e;/* Computed Parameter: DiscreteTimeIntegrator_gainva_e
                                          * Referenced by: '<S15>/Discrete-Time Integrator'
                                          */
  real_T DiscreteTimeIntegrator_IC_f;  /* Expression: SkywalkerX8.InitialConditions.da
                                        * Referenced by: '<S15>/Discrete-Time Integrator'
                                        */
  real_T PIDFControllerPhiKp2DLookupTabl[10];/* Expression: SkywalkerX8.Control.Lateral.PhiController.Digital.KpPhi
                                              * Referenced by: '<S4>/PIDF Controller Phi Kp 2D Lookup Table'
                                              */
  real_T PIDFControllerPhiKp2DLookupTa_i[10];/* Expression: SkywalkerX8.Control.Lateral.SchedulingVariables.VaArray
                                              * Referenced by: '<S4>/PIDF Controller Phi Kp 2D Lookup Table'
                                              */
  real_T DiscreteTimeIntegrator_gainva_h;/* Computed Parameter: DiscreteTimeIntegrator_gainva_h
                                          * Referenced by: '<S13>/Discrete-Time Integrator'
                                          */
  real_T DiscreteTimeIntegrator_IC_g;  /* Expression: 0
                                        * Referenced by: '<S13>/Discrete-Time Integrator'
                                        */
  real_T Saturation_UpperSat_d;        /* Expression: SkywalkerX8.Control.Lateral.PhiController.upperSaturationDa
                                        * Referenced by: '<S4>/Saturation'
                                        */
  real_T Saturation_LowerSat_ld;       /* Expression: SkywalkerX8.Control.Lateral.PhiController.lowerSaturationDa
                                        * Referenced by: '<S4>/Saturation'
                                        */
  real_T MixingMatrix_Gain[4];         /* Expression: [0.5 -0.5;0.5 0.5]
                                        * Referenced by: '<S1>/Mixing Matrix'
                                        */
  real_T PIDFControllerPhiKd2DLookupTabl[10];/* Expression: SkywalkerX8.Control.Lateral.PhiController.Digital.KdPhi
                                              * Referenced by: '<S4>/PIDF Controller Phi Kd 2D Lookup Table'
                                              */
  real_T PIDFControllerPhiKd2DLookupTa_f[10];/* Expression: SkywalkerX8.Control.Lateral.SchedulingVariables.VaArray
                                              * Referenced by: '<S4>/PIDF Controller Phi Kd 2D Lookup Table'
                                              */
  real_T PIDFControllerPhiN2DLookupTable[10];/* Expression: SkywalkerX8.Control.Lateral.PhiController.Digital.NPhi
                                              * Referenced by: '<S4>/PIDF Controller Phi N 2D Lookup Table'
                                              */
  real_T PIDFControllerPhiN2DLookupTab_a[10];/* Expression: SkywalkerX8.Control.Lateral.SchedulingVariables.VaArray
                                              * Referenced by: '<S4>/PIDF Controller Phi N 2D Lookup Table'
                                              */
  real_T PIDFControllerthetaKd2DLookupTa[60];/* Expression: SkywalkerX8.Control.Longitudinal.thetaController.Digital.KdTheta
                                              * Referenced by: '<S5>/PIDF Controller theta Kd 2D Lookup Table'
                                              */
  real_T PIDFControllerthetaKd2DLookup_a[10];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray
                                              * Referenced by: '<S5>/PIDF Controller theta Kd 2D Lookup Table'
                                              */
  real_T PIDFControllerthetaKd2DLookup_g[6];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray
                                             * Referenced by: '<S5>/PIDF Controller theta Kd 2D Lookup Table'
                                             */
  real_T PIDFControllerthetaN2DLookupTab[60];/* Expression: SkywalkerX8.Control.Longitudinal.thetaController.Digital.NTheta
                                              * Referenced by: '<S5>/PIDF Controller theta N 2D Lookup Table'
                                              */
  real_T PIDFControllerthetaN2DLookupT_l[10];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray
                                              * Referenced by: '<S5>/PIDF Controller theta N 2D Lookup Table'
                                              */
  real_T PIDFControllerthetaN2DLookupT_i[6];/* Expression: SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray
                                             * Referenced by: '<S5>/PIDF Controller theta N 2D Lookup Table'
                                             */
  uint32_T Delay_DelayLength;          /* Computed Parameter: Delay_DelayLength
                                        * Referenced by: '<S22>/Delay'
                                        */
  uint32_T Delay_DelayLength_b;        /* Computed Parameter: Delay_DelayLength_b
                                        * Referenced by: '<S21>/Delay'
                                        */
  uint32_T PIDFControllerVa_thetaKp2DLoo_e[2];/* Computed Parameter: PIDFControllerVa_thetaKp2DLoo_e
                                               * Referenced by: '<S7>/PIDF Controller Va_theta Kp 2D Lookup Table'
                                               */
  uint32_T PIDFControllerVa_thetaKi2DLoo_j[2];/* Computed Parameter: PIDFControllerVa_thetaKi2DLoo_j
                                               * Referenced by: '<S7>/PIDF Controller Va_theta Ki 2D Lookup Table'
                                               */
  uint32_T Delay_DelayLength_l;        /* Computed Parameter: Delay_DelayLength_l
                                        * Referenced by: '<S23>/Delay'
                                        */
  uint32_T PIDFControllerVa_thetaN2DLoo_lz[2];/* Computed Parameter: PIDFControllerVa_thetaN2DLoo_lz
                                               * Referenced by: '<S7>/PIDF Controller Va_theta N 2D Lookup Table'
                                               */
  uint32_T PIDFControllerVa_thetaKd2DLoo_a[2];/* Computed Parameter: PIDFControllerVa_thetaKd2DLoo_a
                                               * Referenced by: '<S7>/PIDF Controller Va_theta Kd 2D Lookup Table'
                                               */
  uint32_T PIDFControllerh_thetaKp2DLook_e[2];/* Computed Parameter: PIDFControllerh_thetaKp2DLook_e
                                               * Referenced by: '<S8>/PIDF Controller h_theta Kp 2D Lookup Table'
                                               */
  uint32_T PIDFControllerh_thetaKi2DLook_d[2];/* Computed Parameter: PIDFControllerh_thetaKi2DLook_d
                                               * Referenced by: '<S8>/PIDF Controller h_theta Ki 2D Lookup Table'
                                               */
  uint32_T Delay_DelayLength_g;        /* Computed Parameter: Delay_DelayLength_g
                                        * Referenced by: '<S25>/Delay'
                                        */
  uint32_T PIDFControllerh_thetaN2DLooku_o[2];/* Computed Parameter: PIDFControllerh_thetaN2DLooku_o
                                               * Referenced by: '<S8>/PIDF Controller h_theta N 2D Lookup Table'
                                               */
  uint32_T PIDFControllerh_thetaKd2DLook_b[2];/* Computed Parameter: PIDFControllerh_thetaKd2DLook_b
                                               * Referenced by: '<S8>/PIDF Controller h_theta Kd 2D Lookup Table'
                                               */
  uint32_T PDFControllertheta2DOFKp2DLoo_n[2];/* Computed Parameter: PDFControllertheta2DOFKp2DLoo_n
                                               * Referenced by: '<S5>/PDF Controller theta 2DOF Kp 2D Lookup Table'
                                               */
  uint32_T PDFControllertheta2DOFN2DLoo_dz[2];/* Computed Parameter: PDFControllertheta2DOFN2DLoo_dz
                                               * Referenced by: '<S5>/PDF Controller theta 2DOF N 2D Lookup Table'
                                               */
  uint32_T PDFControllertheta2DOFKd2DLoo_p[2];/* Computed Parameter: PDFControllertheta2DOFKd2DLoo_p
                                               * Referenced by: '<S5>/PDF Controller theta 2DOF Kd 2D Lookup Table'
                                               */
  uint32_T PIDFControllerthetaKi2DLookup_k[2];/* Computed Parameter: PIDFControllerthetaKi2DLookup_k
                                               * Referenced by: '<S5>/PIDF Controller theta Ki 2D Lookup Table'
                                               */
  uint32_T PIDFControllerthetaKp2DLookup_p[2];/* Computed Parameter: PIDFControllerthetaKp2DLookup_p
                                               * Referenced by: '<S5>/PIDF Controller theta Kp 2D Lookup Table'
                                               */
  uint32_T PIDFControllerthetaKd2DLookup_i[2];/* Computed Parameter: PIDFControllerthetaKd2DLookup_i
                                               * Referenced by: '<S5>/PIDF Controller theta Kd 2D Lookup Table'
                                               */
  uint32_T PIDFControllerthetaN2DLookupT_k[2];/* Computed Parameter: PIDFControllerthetaN2DLookupT_k
                                               * Referenced by: '<S5>/PIDF Controller theta N 2D Lookup Table'
                                               */
  boolean_T Delay_InitialCondition_l;  /* Computed Parameter: Delay_InitialCondition_l
                                        * Referenced by: '<S22>/Delay'
                                        */
  boolean_T Memory_InitialCondition;   /* Computed Parameter: Memory_InitialCondition
                                        * Referenced by: '<S24>/Memory'
                                        */
  boolean_T Memory_InitialCondition_i; /* Computed Parameter: Memory_InitialCondition_i
                                        * Referenced by: '<S26>/Memory'
                                        */
  boolean_T Memory_InitialCondition_c; /* Computed Parameter: Memory_InitialCondition_c
                                        * Referenced by: '<S20>/Memory'
                                        */
  boolean_T Memory_InitialCondition_m; /* Computed Parameter: Memory_InitialCondition_m
                                        * Referenced by: '<S16>/Memory'
                                        */
  boolean_T Memory_InitialCondition_b; /* Computed Parameter: Memory_InitialCondition_b
                                        * Referenced by: '<S12>/Memory'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Autopilot_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    struct {
      uint8_T TID[2];
    } TaskCounters;

    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (default storage) */
extern P_Autopilot_T Autopilot_P;

/* Block signals (default storage) */
extern B_Autopilot_T Autopilot_B;

/* Block states (default storage) */
extern DW_Autopilot_T Autopilot_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_Autopilot_T Autopilot_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_Autopilot_T Autopilot_Y;

/* Model entry point functions */
extern void Autopilot_initialize(void);
extern void Autopilot_step(void);
extern void Autopilot_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Autopilot_T *const Autopilot_M;

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
 * '<S3>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Chi'
 * '<S4>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Phi'
 * '<S5>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Theta'
 * '<S6>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Va_dt'
 * '<S7>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Va_theta'
 * '<S8>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller h_theta'
 * '<S9>'   : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Va Rate Limiter'
 * '<S10>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/h Rate Limiter Dynamic'
 * '<S11>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Chi/PIDF Controller Va_theta'
 * '<S12>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Chi/PIDF Controller Va_theta/Clamping circuit'
 * '<S13>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Phi/DF Controller Phi'
 * '<S14>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Phi/PDF Controller Phi 2DOF'
 * '<S15>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Phi/PI Controller Phi'
 * '<S16>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Phi/PI Controller Phi/Clamping circuit'
 * '<S17>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Theta/DF Controller Theta'
 * '<S18>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Theta/PDF Controller Theta 2DOF'
 * '<S19>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Theta/PI Controller Theta'
 * '<S20>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Theta/PI Controller Theta/Clamping circuit'
 * '<S21>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Va_dt/PIDF Controller Va_dt'
 * '<S22>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Va_dt/PIDF Controller Va_dt/Clamping circuit'
 * '<S23>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Va_theta/PIDF Controller Va_theta'
 * '<S24>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller Va_theta/PIDF Controller Va_theta/Clamping circuit'
 * '<S25>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller h_theta/PIDF Controller h_theta'
 * '<S26>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Gain Scheduled Controller h_theta/PIDF Controller h_theta/Clamping circuit'
 * '<S27>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/Va Rate Limiter/Saturation Dynamic'
 * '<S28>'  : 'SkywalkerX8_GuidanceAndNavigation_Verification/Autopilot Digital/h Rate Limiter Dynamic/Saturation Dynamic'
 */
#endif                                 /* RTW_HEADER_Autopilot_h_ */
