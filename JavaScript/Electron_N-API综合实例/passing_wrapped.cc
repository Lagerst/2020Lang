#include "passing_wrapped.h"
#include <napi.h>
#include <uv.h>

passing_wrapped::passing_wrapped(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<passing_wrapped>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  this->val_ = info[0].As<Napi::Number>().DoubleValue();
};

Napi::FunctionReference passing_wrapped::constructor;

void passing_wrapped::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "passing_wrapped", {});

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("passing_wrapped", func);
}

Napi::Object passing_wrapped::NewInstance(Napi::Value arg) {
  Napi::Object obj = constructor.New({arg});
  return obj;
}
