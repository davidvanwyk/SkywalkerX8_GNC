

    /*
  * rt_nonfinite.c
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


    

    /*
  * Abstract:
  *      Function to initialize non-finites,
  *      (Inf, NaN and -Inf).
  */
    #include "rt_nonfinite.h"

          #include "rtGetNaN.h"
        #include "rtGetInf.h"
    

    


  

  

  

  

  

  

  

  

  

  

  

  

  

    
  
  


  real_T rtInf;


  


  real_T rtMinusInf;


  


  real_T rtNaN;


  


  real32_T rtInfF;


  


  real32_T rtMinusInfF;


  


  real32_T rtNaNF;


  


    
  /* 
 * Initialize the rtInf, rtMinusInf, and rtNaN needed by the
 * generated code. NaN is initialized as non-signaling. Assumes IEEE.
 */

    void rt_InitInfAndNaN(size_t realSize) {

    (void) (realSize); 
    rtNaN = rtGetNaN();
    rtNaNF = rtGetNaNF();
    rtInf = rtGetInf();
    rtInfF = rtGetInfF();
    rtMinusInf = rtGetMinusInf();
    rtMinusInfF = rtGetMinusInfF();
  }
    
  /* Test if value is infinite */
    boolean_T rtIsInf(real_T value) {
    return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
  }
    
  /* Test if single-precision value is infinite */
    boolean_T rtIsInfF(real32_T value) {
    return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
  }
    
  /* Test if value is not a number */
    boolean_T rtIsNaN(real_T value) {
      return (boolean_T)((value!=value) ? 1U : 0U);
  }
    
  /* Test if single-precision value is not a number */
    boolean_T rtIsNaNF(real32_T value) {
      return (boolean_T)(((value!=value) ? 1U : 0U));
  }
    


  

  

  

  
