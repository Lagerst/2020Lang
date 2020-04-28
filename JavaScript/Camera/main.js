const { app, BrowserWindow, Menu } = require('electron')
const addon = require('./build/Release/Cam.node')

const camera = new addon.Cam();

function createWindow () {
  // 创建浏览器窗口
  const win = new BrowserWindow({
    width: 800,
    height: 600,
    webPreferences: {
        nodeIntegration: true
    }
  })
  var menu;
  setMenu(camera.RefreshCameraNum());

  function get_function(x) {
    return function() {
      console.log("Camera Switched to " + x);
      camera.SetCam(x);
      camera.UpdateImage();
      /*
      win.loadFile('image.html');
      setInterval(() => {
        camera.UpdateImage();
        win.loadFile('image.html')
      }, 1000);
      */
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
    menu = [
      {
        label: "刷新摄像头",
        click: function() {
          var num = camera.RefreshCameraNum();
          console.log("RefreshCameraNum : " + num);
          setMenu(num);
          Menu.setApplicationMenu(Menu.buildFromTemplate(menu))
        }
      },
      {
        label:"开始",
        submenu: submenu
      },{
        label:"停止",
        click: () => {
          camera.Stop();
        }
      }
    ]
  }

  Menu.setApplicationMenu(Menu.buildFromTemplate(menu))

  // 并且为你的应用加载index.html
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