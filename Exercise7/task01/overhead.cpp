#include <iostream>
#include <typeinfo>
#include "classes.cpp"
#include "stopwatch.hpp"


int main(int argc, char const *argv[]) {

  PureBase pure;
  VirtBase vbase;
  VirtDer vder;
  PureBase *ppure  = new PureBase();
  VirtBase *pvbase  = new VirtBase();
  VirtDer *pvder  = new VirtDer();
  VirtBase *pvbaseder = pvder;

// TASK01-a
// All calls wich are possible without a cast.
// I count 15... Did I fail?

// >Static member function: baseline
  StaticBase::myFunc();   //call 01
// >Non virtual member function: +implicit this parameter
  pure.myFunc();          //call 02
  vbase.nvFunc();         //call 03
  vder.nvFunc();          //call 04
  vder.myFunc();          //call 05
  ppure->myFunc();        //call 06
  pvbase->nvFunc();       //call 07
  pvder->myFunc();        //call 08
  pvder->nvFunc();        //call 09
  pvbaseder->nvFunc();    //call 10
// >Virtual member: +indirect access via vtable lookup
  vbase.virtFunc();       //call 11
  vder.virtFunc();        //call 12
  pvbase->virtFunc();     //call 13
  pvder->virtFunc();      //call 14
  pvbaseder->virtFunc();  //call 15

// No non-member functions were called!
// Also no virtual member functions with multiple inheritance!
/* I'm aware that these are 15 function calls but as I discribed in my Post on the
 * discussion-forum all tests I ran suggest that call 15 and 14  call the same
 * function on the same object as call 09 and 10. Making 13 distinct function calls.
 * I'm still not sure what I forgot.
 */


// TASK01-b
// Performance test for all calls of TASK01-a above
#ifdef TASK02
  /* The commented numbers provides the measurement(s) in second for the corresponding
   * call following it.   */

   // >Static member function: baseline
    // 0.22
    MEASURETIME( "StaticBase::myFunc()", 50000000, StaticBase::myFunc();)
  // >Non virtual member function: +implicit this parameter
    // 0.33
    MEASURETIME( "pure.myFunc()", 50000000, pure.myFunc();)
    MEASURETIME( "vbase.nvFunc()", 50000000, vbase.nvFunc();)
    MEASURETIME( "vder.nvFunc()", 50000000, vder.nvFunc();)
    MEASURETIME( "vder.myFunc()", 50000000, vder.myFunc();)
    // 0.37
    MEASURETIME( "ppure->myFunc()", 50000000, ppure->myFunc();)
    MEASURETIME( "pvbase->nvFunc()", 50000000, pvbase->nvFunc();)
    MEASURETIME( "pvder->nvFunc()", 50000000, pvder->nvFunc();)
    MEASURETIME( "pvder->myFunc()", 50000000, pvder->myFunc();)
    MEASURETIME( "pvbaseder->nvFunc()", 50000000, pvbaseder->nvFunc();)
  // >Virtual member: +indirect access via vtable lookup
    // 0.33
    MEASURETIME( "vbase.virtFunc()", 50000000, vbase.virtFunc();)
    MEASURETIME( "vder.virtFunc()", 50000000, vder.virtFunc();)
    // 0.50
    MEASURETIME( "pvbase->virtFunc()", 50000000, pvbase->virtFunc();)
    MEASURETIME( "pvder->virtFunc()", 50000000, pvder->virtFunc();)
    MEASURETIME( "pvbaseder->virtFunc()", 50000000, pvbaseder->virtFunc();) // >points to object of VirtDer!
#endif

// TASK01-c
/* Performance test for the call of myFunc() usign two different casting methods
 * on pvbaseder.  */
#ifdef TASK03

  /* Measurement using a dynamic_cast which needs Run-Time Type Information (RTTI)
   * and ensures that the cast is valid.  */
  MEASURETIME("dynamic_cast", 50000000,
    VirtDer* v = (dynamic_cast<VirtDer*> (pvbaseder));
    if(typeid(v) == typeid(pvder))
      v->myFunc();
  );

  /* Measurement using a static_cast which does not need RTTI but neither provides
   * an esurance. Therefore it's faster.*/
  MEASURETIME("static_cast", 50000000,
    VirtDer* v = (static_cast<VirtDer*> (pvbaseder));
    if(typeid(v) == typeid(pvder))
      v->myFunc();
  );


#endif

  return 0;
}
