#include "thdEntity.h"
#include <process.h>
namespace inspire {

   threadEntity::threadEntity(thdType t) : _type(t)
   {
   }

   threadEntity::~threadEntity()
   {
      if (_hThread && _state != THREAD_STOPPED)
      {
         deactive();
         destroy();
      }
   }

   int threadEntity::initialize()
   {
      int rc = 0;
      _state = THREAD_CREATING;
      unsigned threadId = 0;
      _hThread = (HANDLE)_beginthreadex(NULL, 0, threadEntity::ENTRY_POINT, this, CREATE_SUSPENDED, &threadId);
      if (INVALID_HANDLE_VALUE == _hThread)
      {
         rc = -1; // system error
         _state = THREAD_INVALID;
         return rc;
      }
      _state = THREAD_IDLE;
      _tid = threadId;
      return rc;
   }

   int threadEntity::active()
   {
      ::ResumeThread(_hThread);
   }

   int threadEntity::deactive()
   {
      if (THREAD_STOPPED != _state)
      {
         _state = THREAD_STOPPING;
         if (WAIT_TIMEOUT == ::WaitForSingleObject(_hThread, 10000))
         {
            destroy();
         }
      }
   }

   int threadEntity::destroy()
   {
      ::_endthreadex(-11);
      _state = THREAD_STOPPED;
   }

   int threadEntity::_run()
   {
      while ( THREAD_STOPPED != _state )
      {
         //TODO:
      }
   }

   unsigned __stdcall threadEntity::ENTRY_POINT(void* arg)
   {
      threadEntity* entity = static_cast<threadEntity*>(arg);
      if (entity)
      {
         entity->_run();
      }
   }

}