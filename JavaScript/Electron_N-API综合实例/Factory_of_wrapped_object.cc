#include "Factory_of_wrapped_object.h"
#include <napi.h>
#include <uv.h>

using namespace Napi;

Napi::FunctionReference Factory_of_wrapped_object::constructor;

Napi::Object Factory_of_wrapped_object::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(
      env, "Factory_of_wrapped_object", {
        InstanceMethod("plusOne", &Factory_of_wrapped_object::PlusOne)
      });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("Factory_of_wrapped_object", func);
  return exports;
}

Factory_of_wrapped_object::Factory_of_wrapped_object(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<Factory_of_wrapped_object>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  this->counter_ = info[0].As<Napi::Number>().DoubleValue();
};

Napi::Object Factory_of_wrapped_object::NewInstance(Napi::Env env, Napi::Value arg) {
  Napi::EscapableHandleScope scope(env);
  Napi::Object obj = constructor.New({arg});
  return scope.Escape(napi_value(obj)).ToObject();
}

Napi::Value Factory_of_wrapped_object::PlusOne(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  this->counter_ = this->counter_ + 1;

  return Napi::Number::New(env, this->counter_);
}
