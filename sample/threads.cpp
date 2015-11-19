#include "logger/logger.h"
#include "thdTask.h"
#include "util/mutex.h"
#include "util/spinlock.h"
#include "util/condition.h"
#include "logger/logger.h"
#include "thdMgr.h"
#include <iostream>

struct mtxnumber
{
   inspire::mutex_t _spin;
   //inspire::spinlock_t _spin;
   int index = 0;
};

static mtxnumber no;
static int taskId = 0;

class taskA : public inspire::thdTask
{
public:
   taskA() : thdTask(taskId, "A task") { ++taskId; }
   ~taskA() {}

   virtual int run()
   {
      inspire::condition_t cond(&no._spin);
      int tmp = no.index;
      ++no.index;
      LogEvent("from %d ---> %d", tmp, no.index);
      std::cout << " ---> " << no.index << std::endl;
      return 0;
   }

private:
   const char* _name;
};

int main(int argc, char** argv)
{
   inspire::thdMgr* mgr = inspire::thdMgr::instance();
   mgr->setIdleCount(3);
   for (int idx = 0; idx < 20; ++idx)
   {
      inspire::thdTask* t = new taskA();
      mgr->assign(t);
   }

   bool exit = false;
   while (!exit)
   {
      mgr->process();
   }

   return 0;
}