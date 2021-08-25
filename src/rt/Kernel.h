#ifndef IRIS_SRC_RT_KERNEL_H
#define IRIS_SRC_RT_KERNEL_H

#include "Config.h"
#include "Releasable.h"
#include <map>

namespace iris {
namespace rt {

typedef struct _KernelArg {
  size_t size;
  char value[256];
  Mem* mem;
  size_t mem_off;
  size_t mem_size;
  size_t off;
  int mode;
} KernelArg;

class Device;
class Platform;

class Kernel: public Releasable<struct _iris_kernel, Kernel> {
public:
  Kernel(const char* name, Platform* platform);
  virtual ~Kernel();

  void SetArg(int idx, size_t size, void* value);
  void SetMem(int idx, Mem* mem, size_t off, int mode);
  std::map<int, KernelArg*>* ExportArgs();

  char* name() { return name_; }

  Platform* platform() { return platform_; }

  void** archs() { return archs_; }
  void* arch(Device* dev);

private:
  char name_[256];
  std::map<int, KernelArg*> args_;
  void* archs_[IRIS_MAX_NDEVS];
  Device* archs_devs_[IRIS_MAX_NDEVS];

  Platform* platform_;
};

} /* namespace rt */
} /* namespace iris */

#endif /* IRIS_SRC_RT_KERNEL_H */

