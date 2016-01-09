#ifndef _INSPIRE_THREAD_TASK_MANAGER_H_
#define _INSPIRE_THREAD_TASK_MANAGER_H_

#include "util/inspire.h"
#include "util/container/map.h"
#include "util/container/deque.h"

namespace inspire {

   class threadMgr;
   class thdTask;
   class ITaskProductor;
   class thdTaskMgr
   {
   public:
      static thdTaskMgr* instance();
      void registerTask(thdTask* task);
      void over(thdTask* task);
      thdTask* get(const int64& id, ITaskProductor* factory);

   protected:
      void clean();

   private:
      thdTaskMgr() {};
      thdTaskMgr(const thdTaskMgr& rhs);
      thdTaskMgr& operator= (const thdTaskMgr& rhs);
      ~thdTaskMgr() { clean(); }

   private:
      deque<thdTask*>      _overQueue;
      map<int64, thdTask*> _taskMap;
   };
}
#endif