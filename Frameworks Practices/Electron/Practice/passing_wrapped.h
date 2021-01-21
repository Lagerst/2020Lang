#ifndef passing_wrapped_H
#define passing_wrapped_H

#include <napi.h>

class passing_wrapped : public Napi::ObjectWrap<passing_wrapped> {
 public:
  static void Init(Napi::Env env, Napi::Object exports);
  static Napi::Object NewInstance(Napi::Value arg);
  double Val() const { return val_; }
  passing_wrapped(const Napi::CallbackInfo& info);

 private:
  static Napi::FunctionReference constructor;
  double val_;
};

#endif
