{
  "targets": [
    {
      "target_name": "Cam",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [ "./src/putText.cc","./src/addon.cc", "./src/Cam.cc"],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "C:\\Modules\\OPENCV\\opencv\\build\\include"
      ],
      "libraries": [
        "C:\\Modules\\OPENCV\\opencv\\build\\x86\\lib\\Release\\opencv_world430.lib"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}