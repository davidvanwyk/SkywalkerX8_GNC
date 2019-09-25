/*
 * Autopilot_sf_private.h
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

#ifndef RTW_HEADER_Autopilot_sf_private_h_
#define RTW_HEADER_Autopilot_sf_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#if !defined(ss_VALIDATE_MEMORY)
#define ss_VALIDATE_MEMORY(S, ptr)     if(!(ptr)) {\
 ssSetErrorStatus(S, RT_MEMORY_ALLOCATION_ERROR);\
 }
#endif

#if !defined(rt_FREE)
#if !defined(_WIN32)
#define rt_FREE(ptr)                   if((ptr) != (NULL)) {\
 free((ptr));\
 (ptr) = (NULL);\
 }
#else

/* Visual and other windows compilers declare free without const */
#define rt_FREE(ptr)                   if((ptr) != (NULL)) {\
 free((void *)(ptr));\
 (ptr) = (NULL);\
 }
#endif
#endif

extern real_T Autopilot_look1_binlxpw(real_T u0, const real_T bp0[], const
  real_T table[], uint32_T maxIndex);
extern real_T Autopilot_look2_binlxpw(real_T u0, real_T u1, const real_T bp0[],
  const real_T bp1[], const real_T table[], const uint32_T maxIndex[], uint32_T
  stride);
extern real_T Autopilot_look2_pbinlxpw(real_T u0, real_T u1, const real_T bp0[],
  const real_T bp1[], const real_T table[], uint32_T prevIndex[], const uint32_T
  maxIndex[], uint32_T stride);

#endif                                 /* RTW_HEADER_Autopilot_sf_private_h_ */
