#include <napi.h>
#include "Cam.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return Cam::Init(env, exports);
}

NODE_API_MODULE(addon, InitAll)
