#ifndef IRIS_SRC_RT_THREAD_H
#define IRIS_SRC_RT_THREAD_H

#include <semaphore.h>
#include <pthread.h>

namespace iris {
namespace rt {

class Thread {
public:
  Thread();
  virtual ~Thread();

  void Start();
  virtual void Stop();
  virtual void Sleep();
  virtual void Invoke();

protected:
  virtual void Run() = 0;

protected:
  static void* ThreadFunc(void* argp);

protected:
  pthread_t thread_;
  volatile bool running_;
  sem_t sem_;
};

} /* namespace rt */
} /* namespace iris */

#endif /* IRIS_SRC_RT_THREAD_H */

