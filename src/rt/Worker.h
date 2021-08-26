#ifndef IRIS_SRC_RT_WORKER_H
#define IRIS_SRC_RT_WORKER_H

#include "Thread.h"

namespace iris {
namespace rt {

class Device;
class Platform;
class Queue;
class ReadyQueue;
class Scheduler;
class Task;

class Worker : public Thread {
public:
  Worker(Device* dev, Platform* platform);
  virtual ~Worker();

  void Enqueue(Task* task);
  void TaskComplete(Task* task);

  bool busy() { return busy_; }
  unsigned long ntasks();
  Device* device() { return dev_; }

private:
  void Execute(Task* task);
  virtual void Run();

private:
  Platform* platform_;
  Queue* queue_;
  Device* dev_;
  Scheduler* scheduler_;
  bool busy_;
};

} /* namespace rt */
} /* namespace iris */

#endif /* IRIS_SRC_RT_WORKER_H */

