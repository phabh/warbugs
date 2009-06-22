 /*
 * ThreadJC.h
 *
 *  Created on: 08/12/2008
 *      Author: kurumim
 */

#ifndef THREADJC_H_
#define THREADJC_H_
#include <string>
#include <windows.h>
#include <process.h>


class CThread 
{
   public:
	  CRITICAL_SECTION sessaoCritica;

	  CThread();
	  ~CThread();
      int Start(void * arg);

   protected:
     void Run(void * arg);
     static void EntryPoint(void*);
      virtual void Setup();
      virtual void Execute();
      void * Arg() const {return Arg_;}
      void Arg(void* a){Arg_ = a;}
	  void EndThread();
   private:

      void * Arg_;

};


#endif /* THREADJC_H_ */
