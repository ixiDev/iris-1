#ifndef IRIS_SRC_RT_QUEUE_H
#define IRIS_SRC_RT_QUEUE_H

#include <stddef.h>

namespace iris {
namespace rt {

class Task;

class Queue {
public:
  virtual ~Queue() {}

  virtual bool Enqueue(Task* task) = 0;
  virtual bool Dequeue(Task** task) = 0;
  virtual size_t Size() = 0;
  virtual bool Empty() = 0;
};

} /* namespace rt */
} /* namespace iris */

#endif /* IRIS_SRC_RT_QUEUE_H */
