/*
 * State_sid.h
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
 *
 * SOURCES: State_sf.c
 */

/* statically allocated instance data for model: State */
{
  extern const ConstB_State_T State_Invariant;

  {
    /* Local SimStruct for the generated S-Function */
    static LocalS slS;
    LocalS *lS = &slS;
    ssSetUserData(rts, lS);

    /* block I/O */
    {
      static B_State_T sfcnB;
      void *b = (real_T *) &sfcnB;
      ssSetLocalBlockIO(rts, b);
      (void) memset(b, 0,
                    sizeof(B_State_T));
    }

    _ssSetConstBlockIO(rts, &State_Invariant);

    /* model checksums */
    ssSetChecksumVal(rts, 0, 3287421937U);
    ssSetChecksumVal(rts, 1, 4065762404U);
    ssSetChecksumVal(rts, 2, 2629293183U);
    ssSetChecksumVal(rts, 3, 3003530344U);
  }
}
