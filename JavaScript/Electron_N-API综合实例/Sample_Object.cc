#include "Sample_Object.h"

Napi::FunctionReference Sample_Object::constructor;

Napi::Object Sample_Object::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func =
      DefineClass(env,
                  "Sample_Object",
                  {InstanceMethod("plusOne", &Sample_Object::PlusOne),
                   InstanceMethod("value", &Sample_Object::GetValue),
                   InstanceMethod("multiply", &Sample_Object::Multiply)});

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("Sample_Object", func);
  return exports;
}

Sample_Object::Sample_Object(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<Sample_Object>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  int length = info.Length();

  if (length <= 0 || !info[0].IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    return;
  }

  Napi::Number value = info[0].As<Napi::Number>();
  this->value_ = value.DoubleValue();
}

Napi::Value Sample_Object::GetValue(const Napi::CallbackInfo& info) {
  double num = this->value_;

  return Napi::Number::New(info.Env(), num);
}

Napi::Value Sample_Object::PlusOne(const Napi::CallbackInfo& info) {
  this->value_ = this->value_ + 1;

  return Sample_Object::GetValue(info);
}

Napi::Value Sample_Object::Multiply(const Napi::CallbackInfo& info) {
  Napi::Number multiple;
  if (info.Length() <= 0 || !info[0].IsNumber()) {
    multiple = Napi::Number::New(info.Env(), 1);
  } else {
    multiple = info[0].As<Napi::Number>();
  }

  Napi::Object obj = constructor.New(
      {Napi::Number::New(info.Env(), this->value_ * multiple.DoubleValue())});

  return obj;
}