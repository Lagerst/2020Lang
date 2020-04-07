#ifndef Sample_Object_H
#define Sample_Object_H

#include <napi.h>

class Sample_Object : public Napi::ObjectWrap<Sample_Object> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  Sample_Object(const Napi::CallbackInfo& info);

 private:
  static Napi::FunctionReference constructor;

  Napi::Value GetValue(const Napi::CallbackInfo& info);
  Napi::Value PlusOne(const Napi::CallbackInfo& info);
  Napi::Value Multiply(const Napi::CallbackInfo& info);

  double value_;
};

#endif