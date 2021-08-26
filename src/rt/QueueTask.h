#ifndef IRIS_SRC_RT_QUEUE_TASK_H
#define IRIS_SRC_RT_QUEUE_TASK_H

#include "Task.h"
#include "Queue.h"
#include <pthread.h>
#include <list>

namespace iris {
namespace rt {

class Platform;

class QueueTask : public Queue {
public:
  QueueTask(Platform* platform);
  ~QueueTask();

  bool Enqueue(Task* task);
  bool Dequeue(Task** task);
  size_t Size();
  bool Empty();

private:
  Platform* platform_;
  std::list<Task*> tasks_;
  pthread_mutex_t mutex_;
};

} /* namespace rt */
} /* namespace iris */

#endif /* IRIS_SRC_RT_QUEUE_TASK_H */

