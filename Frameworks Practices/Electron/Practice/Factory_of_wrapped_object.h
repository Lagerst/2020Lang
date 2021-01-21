#ifndef Factory_of_wrapped_object_H
#define Factory_of_wrapped_object_H

#include <napi.h>

class Factory_of_wrapped_object : public Napi::ObjectWrap<Factory_of_wrapped_object> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object NewInstance(Napi::Env env, Napi::Value arg);
  Factory_of_wrapped_object(const Napi::CallbackInfo& info);

 private:
  static Napi::FunctionReference constructor;
  Napi::Value PlusOne(const Napi::CallbackInfo& info);
  double counter_;
};

#endif
