const { app, BrowserWindow, Menu } = require('electron')
const addon = require('./build/Release/Cam.node')
const log = require('electron-log');
const camera = new addon.Cam();

var CamId = -1;
var Debug = false;
var DotNet = false;
var is_running = false;

function camera_set(x) {
  log.info("Camera Switched to " + x);
  CamId = x;
  camera.SetCam(x);
}

function camera_stop() {
  log.info("Camera Stop Recording");
  is_running =false;
  camera.Stop();
}

function camera_start(){
  if (is_running) {
    camera_stop();
  }
  log.info("Start fetching Image from Camera " + CamId + ", Mode = " + Debug + " + " + DotNet);
  is_running = true;
  camera.UpdateImage(Debug, DotNet);
}

function camera_restart() {
  log.info("ReStart fetching Image");
  camera_start();
}

function createWindow () {
  // 创建浏览器窗口
  const win = new BrowserWindow({
    width: 800,
    height: 600,
    webPreferences: {
        nodeIntegration: true
    }
  })

  log.info("********************************************");
  log.info("A new program instance started");

  var menu;
  setMenu(camera.RefreshCameraNum());

  function get_function(x) {
    return function() {
      camera_set(x);
      camera_start();
    }
  }

  function setMenu(x) {
    submenu = [];
    for (var i=0; i<x; i++) {
      submenu.push(
        {
          label: "摄像头" + String(i),
          click: get_function(i)
        }
      )
    }
    submenu.push(
      {
        label: "刷新摄像头",
        click: function() {
          var num = camera.RefreshCameraNum();
          log.info("RefreshCameraNum : " + num);
          setMenu(num);
          Menu.setApplicationMenu(Menu.buildFromTemplate(menu))
        }
      }
    );
    submenu.push(
      {
        label: "显示标准",
        click: function() {
          log.info("standard page has been loaded.");
          win.loadFile('standard.html')
        }
      }
    );
    menu = [
      {
        label:"开始",
        submenu: submenu
      }, {
        label:"停止",
        click: camera_stop
      }, {
        label:"设置",
        submenu: [
          {
            label: "Debug Mode ON",
            click: () => {
              log.info("DebugMode set to TRUE");
              Debug = true;
              camera_restart();
            }
          },
          {
            label: "Debug Mode OFF",
            click: () => {
              log.info("DebugMode set to FALSE");
              Debug = false;
              camera_restart();
            }
          },
          {
            label: "DotNet Mode ON",
            click: () => {
              log.info("DotNet set to TRUE");
              DotNet = true;
              camera_restart();
            }
          },
          {
            label: "DotNet Mode OFF",
            click: () => {
              log.info("DotNet set to FALSE");
              DotNet = false;
              camera_restart();
            }
          }
        ]
      }
    ]
  }

  Menu.setApplicationMenu(Menu.buildFromTemplate(menu))

  // 并且为你的应用加载index.html
  log.info("index page has been loaded.");
  win.loadFile('index.html')

  // 打开开发者工具
  // win.webContents.openDevTools()
}

// This method will be called when Electron has finished
// initialization and is ready to create browser windows.
// 部分 API 在 ready 事件触发后才能使用。
app.whenReady().then(createWindow)

// Quit when all windows are closed.
app.on('window-all-closed', () => {
  camera_stop();
  // 在 macOS 上，除非用户用 Cmd + Q 确定地退出，
  // 否则绝大部分应用及其菜单栏会保持激活。
  if (process.platform !== 'darwin') {
    app.quit()
  }
})

app.on('activate', () => {
  // 在macOS上，当单击dock图标并且没有其他窗口打开时，
  // 通常在应用程序中重新创建一个窗口。
  if (BrowserWindow.getAllWindows().length === 0) {
    createWindow()
  }
})

// In this file you can include the rest of your app's specific main process
// code. 也可以拆分成几个文件，然后用 require 导入。