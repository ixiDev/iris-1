#include "Kernel.h"
#include "Debug.h"
#include "Device.h"
#include <string.h>

namespace iris {
namespace rt {

Kernel::Kernel(const char* name, Platform* platform) {
  size_t len = strlen(name);
  strncpy(name_, name, len);
  name_[len] = 0;
  platform_ = platform;
  for (int i = 0; i < IRIS_MAX_NDEVS; i++) {
    archs_[i] = nullptr;
    archs_devs_[i] = nullptr;
  }
}

Kernel::~Kernel() {
  for (auto I = args_.begin(), E = args_.end(); I != E; ++I) delete I->second;
}

void Kernel::SetArg(int idx, size_t size, void* value) {
  KernelArg* arg = new KernelArg;
  arg->size = size;
  if (value) memcpy(arg->value, value, size);
  arg->mem = nullptr;
  arg->off = 0;
  args_[idx] = arg;
}

void Kernel::SetMem(int idx, Mem* mem, size_t off, int mode) {
  KernelArg* arg = new KernelArg;
  arg->mem = mem;
  arg->off = off;
  arg->mode = mode;
  args_[idx] = arg;
}

std::map<int, KernelArg*>* Kernel::ExportArgs() {
  std::map<int, KernelArg*>* new_args = new std::map<int, KernelArg*>();
  for (auto I = args_.begin(), E = args_.end(); I != E; ++I) {
    KernelArg* arg = I->second;
    KernelArg* new_arg = new KernelArg;
    if (arg->mem) {
      new_arg->mem = arg->mem;
      new_arg->off = arg->off;
      new_arg->mode = arg->mode;
    } else {
      new_arg->size = arg->size; 
      memcpy(new_arg->value, arg->value, arg->size);
      new_arg->mem = nullptr;
      new_arg->off = 0;
    }
    (*new_args)[I->first] = new_arg;
  }
  return new_args;
}

void* Kernel::arch(Device* dev) {
  int devno = dev->devno();
  if (archs_[devno] == nullptr) dev->KernelGet(archs_ + devno, (const char*) name_);
  return archs_[devno];
}

} /* namespace rt */
} /* namespace iris */

