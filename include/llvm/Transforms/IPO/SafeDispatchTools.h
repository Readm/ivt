#ifndef LLVM_TRANSFORMS_IPO_SAFEDISPATCH_TOOLS_H
#define LLVM_TRANSFORMS_IPO_SAFEDISPATCH_TOOLS_H

#include "llvm/ADT/StringRef.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"

#include <string>

#include "SafeDispatchLog.h"

static bool sd_isVtableName_ref(const llvm::StringRef& name) {
  if (name.size() <= 4) {
    // name is too short, cannot be a vtable name
    return false;
  } else if (name.startswith("_ZTV") || name.startswith("_ZTC")) {
    llvm::StringRef rest = name.drop_front(4); // drop the _ZT(C|V) part

    return  (! rest.startswith("S")) &&      // but not from std namespace
        (! rest.startswith("N10__cxxabiv")); // or from __cxxabiv
  }

  return false;
}

static bool sd_isVtableName(std::string& className) {
  llvm::StringRef name(className);

  return sd_isVtableName_ref(name);
}
#endif

