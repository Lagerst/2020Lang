#ifndef CAM_H_
#define CAM_H_

#include <napi.h>
#include <iostream>
#include <opencv2\opencv.hpp>
#include <mutex>
#include <thread>

using namespace cv;
using namespace std;

class Cam: public Napi::ObjectWrap<Cam> {
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    Cam(const Napi::CallbackInfo& info);

private:
    static Napi::FunctionReference constructor;
    Napi::Value RefreshCameraNum(const Napi::CallbackInfo& info);
    Napi::Value UpdateImage(const Napi::CallbackInfo& info);
    Napi::Value SetCam(const Napi::CallbackInfo& info);
    Napi::Value Stop(const Napi::CallbackInfo& info);
    void show();

    int now, total;
    bool running;
    mutex mut;
};

#endif