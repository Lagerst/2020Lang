#include "Cam.h"

Napi::FunctionReference Cam::constructor;

Napi::Object Cam::Init(Napi::Env env, Napi::Object exports){
    Napi::HandleScope scope(env);

    Napi::Function func =
        DefineClass(
            env,
            "Cam",
            {
                InstanceMethod("RefreshCameraNum", &Cam::RefreshCameraNum),
                InstanceMethod("SetCam", &Cam::SetCam),
                InstanceMethod("UpdateImage", &Cam::UpdateImage),
                InstanceMethod("Stop", &Cam::Stop),
            }
        );

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("Cam", func);
    return exports;
}

class MapStorage {
public:
    Mat color_map;
    int getWidth() {
        return color_map.cols;
    }
    int getHeight() {
        return color_map.rows;
    }
    double getvalue();
};

double MapStorage::getvalue() {
    int i;
    int j;
    int middleValue;
    int width = getWidth();
    int height = getHeight();
    int boxWidth = (width * 2) / 5;
    int boxHeight = height / 2;
    int boxTotalPixel = boxWidth * boxHeight;
    int blackPixel = 0;
    int min = 255;
    int max = 0;
    int sum = 0;
    int hist[256] = {0};
    double histSmooth[6][256] = {0.0};
    int minR = 255;
    int minG = 255;
    int minB = 255;
    int maxR = 0;
    int maxG = 0;
    int maxB = 0;
    int left = (width * 3) / 10;
    int right = left + boxWidth;
    int top = height / 4;
    int bottom = top + boxHeight;
    //cout<<width<<" "<<height<<" "<<top<<" "<<bottom<<" "<<left<<" "<<right<<endl;
    for (i = top; i < bottom; i++) {
        for (j = left; j < right; j++) {
            Vec3b col = color_map.at<Vec3b>(i, j);
            int red = col[2];
            int green = col[1];
            int blue = col[0];
            if (red > maxR) {
                maxR = red;
            }
            if (green > maxG) {
                maxG = green;
            }
            if (blue > maxB) {
                maxB = blue;
            }
            if (red < minR) {
                minR = red;
            }
            if (green < minG) {
                minG = green;
            }
            if (blue < minB) {
                minB = blue;
            }
            int gray = (int)(((((double)((float)red)) * 0.3) + (((double)((float)green)) * 0.59)) + (((double)((float)blue)) * 0.11));
            hist[gray] = hist[gray] + 1;
            histSmooth[0][gray] = (double)hist[gray];
            sum += gray;
            if (gray < min) {
                min = gray;
            }
            if (gray > max) {
                max = gray;
            }
        }
    }
    int minDot = 0;
    for (i = 0; i < 255; i++) {
        min = i;
        minDot += hist[i];
        if (minDot > boxTotalPixel / 800) {
            break;
        }
    }
    int maxDot = 0;
    for (i = 255; i > 0; i--) {
        max = i;
        maxDot += hist[i];
        if (maxDot > boxTotalPixel / 800) {
            break;
        }
    }
    i = 0;
    while (i < 256) {
        if (i <= min || i >= max) {
            histSmooth[0][i] = 0.0;
        }
        i++;
    }
    for (i = 1; i < 4; i++) {
        for (j = 2; j < 254; j++) {
            histSmooth[i][j] = ((((histSmooth[i - 1][j - 2] + histSmooth[i - 1][j - 1]) + histSmooth[i - 1][j]) + histSmooth[i - 1][j + 1]) + histSmooth[i - 1][j + 2]) / 5.0;
        }
    }
    for (i = 1; i < 256; i++) {
        histSmooth[4][i] = histSmooth[3][i] - histSmooth[3][i - 1];
    }
    bool isRise = true;
    i = min;
    while (i < max + 1) {
        if (isRise && histSmooth[4][i] >= 0.0 && histSmooth[4][i + 1] < 0.0 && histSmooth[4][i + 2] < 0.0 && histSmooth[4][i + 3] < 0.0) {
            histSmooth[5][i] = 1.0;
            isRise = false;
        }
        if (!isRise && histSmooth[4][i] < 0.0 && histSmooth[4][i + 1] >= 0.0 && histSmooth[4][i + 2] >= 0.0 && histSmooth[4][i + 3] >= 0.0) {
            histSmooth[5][i] = -1.0;
            isRise = true;
        }
        i++;
    }
    if (!isRise && histSmooth[5][max - 1] == 0.0 && histSmooth[5][max] == 0.0) {
        histSmooth[5][max] = -1.0;
    }
    int histMode = 0;
    int histHigh = 0;
    int histLow = 0;
    int histWave[10][2];
    int histWaveRow = 0;
    int firstMaxIndex = min;
    for (i = min; i < max + 1; i++) {
        if (histSmooth[5][i] > 0.0) {
            histMode++;
            histHigh++;
            if (histWaveRow == 0) {
                firstMaxIndex = i;
            }
            histWave[histWaveRow][0] = i;
        }
        if (histSmooth[5][i] < 0.0) {
            histLow++;
            histWave[histWaveRow][1] = i;
            histWaveRow++;
        }
    }
    int lastMaxIndex = max;
    for (i = max; i > min - 1; i--) {
        if (histSmooth[5][i] > 0.0) {
            lastMaxIndex = i;
            if (max - lastMaxIndex > 10) {
                break;
            }
        }
    }
    if (lastMaxIndex - min < 10) {
        histMode = 10;
    }
    int middleSimple = (max + min) / 2;
    int sumMiddle = sum / ((width * height) / 4);
    switch (histMode) {
    case 0:
        middleValue = middleSimple;
        break;
    case 1:
        if (lastMaxIndex - firstMaxIndex < 20) {
            if (firstMaxIndex - middleSimple <= 0) {
                middleValue = firstMaxIndex + ((max - firstMaxIndex) / 2);
                break;
            }
            middleValue = min + ((firstMaxIndex - min) / 2);
            break;
        }
        middleValue = middleSimple;
        break;
    case 2:
        middleValue = histWave[0][1];
        break;
    case 3:
        middleValue = histWave[1][0];
        break;
    case 4:
        middleValue = histWave[1][1];
        break;
    default:
        middleValue = (firstMaxIndex + lastMaxIndex) / 2;
        break;
    }
    int col;
    for (i = top; i < bottom; i++) {
        for (j = left; j < right; j++) {
            Vec3b col = color_map.at<Vec3b>(i, j);
            int red = col[2];
            int green = col[1];
            int blue = col[0];
            if (((int)(((((double)((float)red)) * 0.3) + (((double)((float)green)) * 0.59)) + (((double)((float)blue)) * 0.11))) < middleValue) {
                blackPixel++;
            }
        }
    }
    //cout<<"blackPixel="<<blackPixel<<" ,TotalPixel="<<boxTotalPixel<<endl;
    double dotPercent = (((double)blackPixel) / ((double)boxTotalPixel)) * 100.0;
    return dotPercent;
}

int GetCameraNum() {
    int i = 0;
    while (true) {
        VideoCapture capture(i);
        if (!capture.isOpened())
            return i;
        i++;
        capture.release();
    }
}

Cam::Cam(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<Cam>(info) {
    this->now = -1;
    this->total = GetCameraNum();
    this->running = false;
    if (info.Length() == 1 && info[0].IsNumber()) {
        this->now = info[0].As<Napi::Number>().Int32Value();
    }
    if (this->now >= this->total) {
        this->now = -1;
    }
}

Napi::Value Cam::SetCam(const Napi::CallbackInfo& info) {
    if (info.Length() == 1 && info[0].IsNumber()) {
        this->now = info[0].As<Napi::Number>();
    }
    return Napi::Number::New(info.Env(), 0);
}

Napi::Value Cam::RefreshCameraNum(const Napi::CallbackInfo& info) {
    this->total = GetCameraNum();
    return Napi::Number::New(info.Env(), GetCameraNum());
}

Napi::Value Cam::Stop(const Napi::CallbackInfo& info) {
    mut.lock();
    this->running = false;
    mut.unlock();
    return Napi::Number::New(info.Env(), 0);
}

Napi::Value Cam::UpdateImage(const Napi::CallbackInfo& info) {
    if (now == -1 || now >= total) {
        return Napi::Number::New(info.Env(), -1);
    }
    bool DebugMode = false, DotNetMode = false;
    if (info.Length() == 2 && info[0].IsBoolean() && info[1].IsBoolean()) {
        DebugMode = info[0].As<Napi::Boolean>();
        DotNetMode = info[1].As<Napi::Boolean>();
    } else {
        return Napi::Number::New(info.Env(), -2);
    }

    mut.lock();
    if (this->running == true){
        this->running = false;
		waitKey(100);
    }
    this->running = true;
    mut.unlock();

	VideoCapture capture(now);
	if (!capture.isOpened())
		return Napi::Number::New(info.Env(), -3);

	while (1)
	{
        MapStorage* x = new MapStorage();
		capture >> x->color_map;
		if ((x->color_map).empty())
		{
            delete x;
			break;
		}
		else
		{
            if (DebugMode) {
                imwrite("dump.jpg", x->color_map);
            }

            if (DotNetMode) {
                std::string text = std::to_string(x->getvalue());

                int font_face = cv::FONT_HERSHEY_COMPLEX;
                double font_scale = 2;
                int thickness = 1;
                int baseline;

                cv::Size text_size = cv::getTextSize(text, font_face, font_scale, thickness, &baseline);

                cv::Point origin;
                origin.x = (x->color_map).cols - text_size.width;
                origin.y = (x->color_map).rows - text_size.height;
                cv::putText((x->color_map), text, origin, font_face, font_scale, cv::Scalar(0, 255, 255), thickness, 8, 0);
            }

            imshow("Camera_Video", (x->color_map));
		}
        delete x;
        if (this->running == false) {
            break;
        }
		waitKey(30);
	}
    destroyWindow("Camera_Video");
	capture.release();

    return Napi::Number::New(info.Env(), 0);
}
