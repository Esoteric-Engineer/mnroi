typedef double f64;
typedef float f32;

// No PSVEC/C_VEC function is linked, so nothing here is referenced; 
// force_active keeps this unit's .sdata2 literal pool from being dead-stripped.
#pragma force_active on

const f64 VecZeroConst = 0.0;
const f64 VecHalfConst = 0.5;
const f64 VecThreeConst = 3.0;
const f32 VecOneFConst = 1.0f;
const f32 VecHalfFConst = 0.5f;
const f32 VecThreeFConst = 3.0f;
const f32 VecTwoFConst = 2.0f;
