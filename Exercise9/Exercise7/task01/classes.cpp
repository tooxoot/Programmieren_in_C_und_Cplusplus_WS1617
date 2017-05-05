/**
 * This file contains classes with different member structures.
 * All member functions increment the classe's integer variable.
 * Also all functions provide a print out that can be activated by defining the
 * VERBOSE preprocessor variable.
 */

/**
 * Class with static int variable and static member function.
 */
class StaticBase {
public:
  static int var;

  static void myFunc(){
    StaticBase::var++;
    #ifdef VERBOSE
      std::cout << "Called " << typeid(StaticBase).name() << "::" << __func__ << std::endl;
    #endif
  }
};
//Initialiyation of the static variable from StaticBase.
int StaticBase::var = 0;

/**
 * Class with constructor, private int variable and public member function.
 */
class PureBase {
private:
  int var;
public:
  PureBase (){ this->var = 0; };

  void myFunc(){
    this->var++;
    #ifdef VERBOSE
      std::cout << "Called " << typeid(*this).name() << "::" << __func__ << std::endl;
    #endif
  }
};

/**
  * Class with constructor, public int variable, public member function and
  * public virtual member function.
 */
class VirtBase {
public:
  int var;

  VirtBase (){ this->var = 0; };

  void nvFunc(){
    this->var++;
    #ifdef VERBOSE
      std::cout << "Called " << typeid(*this).name() << "::" << __func__ << std::endl;
    #endif
  }
  virtual void virtFunc(){
    this->var++;
    #ifdef VERBOSE
      std::cout << "Called " << typeid(*this).name() << "::" << __func__ << std::endl;
    #endif
  }
};

/**
  * Class derived from VirtBase with constructor, public int variable, public member function and
  * public virtual member function.
  * Inherits nvFunc() from VirtBase.
  * Overrides virtFunc() from VirtBase.
  * Overrides var from VirtBase.
  */
class VirtDer: public VirtBase {
public:
  int varDer;

  VirtDer (){ this->var = 0; };

  void myFunc(){
    this->varDer++;
    #ifdef VERBOSE
      std::cout << "Called " << typeid(*this).name() << "::" << __func__ << std::endl;
    #endif
  }
  virtual void virtFunc(){
    this->varDer++;
    #ifdef VERBOSE
      std::cout << "Called " << typeid(*this).name() << "::" << __func__ << std::endl;
    #endif
  }
};
