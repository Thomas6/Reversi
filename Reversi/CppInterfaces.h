
/**************CppInterfaces***************************************************************
* This pre-compiled header file uses macros to implement interfaces in C++, more or less.
*
**************************************************************************************/
 
#define Interface class
 
#define DeclareInterface(name) Interface name { \
          public: \
          virtual ~name() {}
 
#define DeclareBasedInterface(name, base) class name : public base { \
           public: \
           virtual ~name() {}
 
#define EndInterface };
 
#define implements public