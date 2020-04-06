#include <napi.h>
#include <iostream>
#include <string>
#include "Sample_Object.h"
#include "passing_wrapped.h"
#include "Factory_of_wrapped_object.h"

using namespace std;
using namespace Napi;

String Hello(const CallbackInfo& info) {
  return String::New(info.Env(), "hello world");
}

Napi::Value Calculate(const CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 2) {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsNumber() || !info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  double arg0 = info[0].As<Napi::Number>();
  double arg1 = info[1].As<Napi::Number>();
  Napi::Number num = Napi::Number::New(env, arg0 + arg1);
  return num;
}

Napi::Value Calculate_callback(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 3) {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsNumber() || !info[2].IsNumber()) {
    Napi::TypeError::New(env, "Wrong arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Function callback_function = info[0].As<Napi::Function>();

  double arg0 = info[1].As<Napi::Number>();
  double arg1 = info[2].As<Napi::Number>();

  return callback_function.Call(env.Global(), {Napi::Number::New(env, arg0), Napi::Number::New(env, arg1)});
}

Napi::Object Create_Object(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "msg"), info[0].ToString());
  return obj;
}

Napi::Function Create_Function(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Function function = Napi::Function::New(env, Hello, "theFunction");
  return function;
}

Napi::Object Create_Object_2(const Napi::CallbackInfo& info) {
  return Factory_of_wrapped_object::NewInstance(info.Env(), info[0]);
}

Napi::Object CreateObject_3(const Napi::CallbackInfo& info) {
  return passing_wrapped::NewInstance(info[0]);
}

Napi::Number Add_passing_wrapped(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  passing_wrapped* obj1 =
      Napi::ObjectWrap<passing_wrapped>::Unwrap(info[0].As<Napi::Object>());
  passing_wrapped* obj2 =
      Napi::ObjectWrap<passing_wrapped>::Unwrap(info[1].As<Napi::Object>());
  double sum = obj1->Val() + obj2->Val();
  return Napi::Number::New(env, sum);
}

Napi::Object Init(Env env, Object exports) {
  exports.Set("hello", Function::New(env, Hello));
  exports.Set("Calculate", Function::New(env, Calculate));
  exports.Set("func_process", Function::New(env, Calculate_callback));
  exports.Set("Create_Object", Function::New(env, Create_Object));
  exports.Set("Create_Function", Function::New(env, Create_Function));
  exports = Sample_Object::Init(env, exports);
  //exports.Set("Object_Init", Function::New(env, Sample_Object::Init(env, exports)));
  exports = Factory_of_wrapped_object::Init(env, exports);
  passing_wrapped::Init(env, exports);
  exports.Set(Napi::String::New(env, "Add_passing_wrapped"), Napi::Function::New(env, Add_passing_wrapped));
  return exports;
}

NODE_API_MODULE(addon, Init)
