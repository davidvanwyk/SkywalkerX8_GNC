

    /*
  * rt_nonfinite.h
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


  #ifndef RTW_HEADER_rt_nonfinite_h_
  #define RTW_HEADER_rt_nonfinite_h_
  
    

  
#include <stddef.h>
  #include "rtwtypes.h"



  

  

  

  

  

  

  

  

  

  

  

  

  

     
  


  extern real_T rtInf;


  


  extern real_T rtMinusInf;


  


  extern real_T rtNaN;


  


  extern real32_T rtInfF;


  


  extern real32_T rtMinusInfF;


  


  extern real32_T rtNaNF;



    extern void rt_InitInfAndNaN(size_t realSize);
      extern boolean_T rtIsInf(real_T value);
      extern boolean_T rtIsInfF(real32_T value);
      extern boolean_T rtIsNaN(real_T value);
      extern boolean_T rtIsNaNF(real32_T value);
    
  typedef struct {
    struct {
        uint32_T wordH;
        uint32_T wordL;
    } words;
  } BigEndianIEEEDouble;
  

  typedef struct {
    struct {
        uint32_T wordL;
        uint32_T wordH;
    } words;
  } LittleEndianIEEEDouble;

  
  typedef struct {
    union {
      real32_T wordLreal;
      uint32_T wordLuint;
    } wordL;
  } IEEESingle;
  
   


  

  

  

  

  

    #endif /* RTW_HEADER_rt_nonfinite_h_ */
