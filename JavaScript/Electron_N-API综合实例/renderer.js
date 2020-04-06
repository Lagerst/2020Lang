// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process because
// `nodeIntegration` is turned off. Use `preload.js` to
// selectively enable features needed in the rendering
// process.

const webview_first = document.querySelector('webview')
const indicator = document.querySelector('.indicator')

const { screen, BrowserWindow, dialog, globalShortcut, Menu, MenuItem, BrowserView, session } = require('electron').remote;
const { ipcRenderer, clipboard } = require('electron');
var remote_import_test = require("./build/Release/calculator.node");

//console.log(ipcRenderer.sendSync('synchronous-message', 'ping'))

ipcRenderer.on('asynchronous-reply', (event, arg) => {
  if (arg == 'pong')
    console.log(arg) // prints "pong"
  else {
    document.getElementById("imported").innerText = "Status: Success";
    var obj = JSON.parse(arg);
    document.getElementById("imported").innerText = "A + B = ";
    document.getElementById("display_location").innerHTML = "&emsp;&emsp;" + obj.response;
  }
})

//ipcRenderer.send('asynchronous-message', 'ping')

function ShortcutReg() {
  const ret = globalShortcut.register('CommandOrControl+X', () => {
    console.log('CommandOrControl+X is pressed')
    document.getElementById("GlobalShortcutStatus").innerText = "CommandOrControl+X is pressed";
  })

  if (!ret) {
    console.log('registration failed')
  }

  // 检查快捷键是否注册成功
  console.log(globalShortcut.isRegistered('CommandOrControl+X'))
}

function openDialog() {
  dialog.showOpenDialog({
    title: "Select File",
    filters: [
      { name: 'Images', extensions: ['jpg', 'png', 'gif'] },
      { name: 'Movies', extensions: ['mkv', 'avi', 'mp4'] },
      { name: 'Custom File Type', extensions: ['as'] },
      { name: 'All Files', extensions: ['*'] }
    ]
  }, result => {
    console.log(result)
  });
}

function saveDialog() {
  dialog.showSaveDialog({
    title: "Save File",
    filters: [
      { name: 'Images', extensions: ['jpg', 'png', 'gif'] },
      { name: 'Movies', extensions: ['mkv', 'avi', 'mp4'] },
      { name: 'Custom File Type', extensions: ['as'] },
      { name: 'All Files', extensions: ['*'] }
    ]
  }, result => {
    console.log(result)
  });
}

function showMessageDialog() {
  dialog.showMessageBox({
    type:"warning",
    title:"Are you sure?",
    message:"Are you sure?",
    button: ["OK","Cancel"]
  }, result => {
    console.log("Your choice:", result);
  })
}

const loadstart = () => {
  document.getElementById("loadstatus").innerText = "loadstart";
  console.log('loadstart...');
}

function injectCSS() {
  webview_first.insertCSS(`
      #su {
          background-color: #999 !important;
      }
  `);
}

const loadstop = () => {
  document.getElementById("loadstatus").innerText = "loadstop";
  console.log('loadstop...');   
  /*
  console.log(document.querySelector('#su'));
  setTimeout(
  document.querySelector('#su').onclick = () => {
    alert("You click the button");
  }, 
  1000);
  */
  injectCSS();
}

window.addEventListener('message', (msg) => {
  document.getElementById("loadstatus").innerText = msg.data.message;
  CloseNewWindow();
});

console.log(webview_first);
webview_first.addEventListener('did-start-loading', loadstart);
webview_first.addEventListener('did-stop-loading', loadstop);
webview_first.addEventListener('dom-ready', e => {
  injectCSS();
});

function OpenNewWindow() {
  subwin = window.open('html/Poped_Page.html', 'Poped', 'height=200, width=800, top=0, left=0, toolbar=no, menubar=no, scrollbars=no, resizable=no, location=no, status=no');
}

function CloseNewWindow() {
  subwin.close();
}

function RefreshStatus() {
  document.getElementById("loadstatus").innerText = "Refreshed";
}

ipcRenderer.on('asynchronous-reply', (event, arg) => {
  if (arg == 'pong')
    console.log(arg) // prints "pong"
  else {
    document.getElementById("imported").innerText = "Status: Success";
    var obj = JSON.parse(arg);
    document.getElementById("imported").innerText = "A + B = ";
    document.getElementById("display_location").innerHTML = "&emsp;&emsp;" + obj.response;
  }
})

function Message_Sync(x) {
  ipcRenderer.send('asynchronous-message', x);
}

function NewPageOpen() {
  const { width, height } = screen.getPrimaryDisplay().workAreaSize
  subWindow = new BrowserWindow({
    width: width/2,
    height: height/2,
    show: false,
    //titleBarStyle: 'hidden', 
    backgroundColor : "#B0D8FD",
    webPreferences: {
      webviewTag: true,
      nativeWindowOpen: true,
      nodeIntegration: true,
    }
  })

  subWindow.loadFile('html/Poped_Page.html')
  
  subWindow.webContents.on("did-finish-load",
    () => {
      console.log("subW****did-finish-load");
    }
  )

  subWindow.webContents.on("dom-ready",
    () => {
      console.log("subW****dom-ready");
    }
  )

  subWindow.once('ready-to-show', () => {
    subWindow.show();
  });

  //subWindow.webContents.openDevTools()
  
  //Under Testing
  /*
  const _win = new BrowserWindow()
  _win.webContents.on('did-finish-load', function() {
    _win.setRepresentedFilename('/Users/pengziwei/workspace/2020Electron/Calculator/preload.js')
    _win.setDocumentEdited(true)
  })
  */
}


//<script type="text/javascript">
function update(status) {
  document.getElementById("imported").innerHTML = status;
  document.getElementById("display_location").innerHTML = "&emsp;&emsp;Result will be displayed here";
}

function submit_call() {
  document.getElementById("imported").innerText = "Submitted";
  //console.log(document.getElementById('left').value);
  result = {a : document.getElementById('left').value , b : document.getElementById("right").value};
  var obj = JSON.stringify(result);
  console.log(obj);
  Message_Sync(obj);
  /*
  $.ajax({
  //几个参数需要注意一下
      type: "Get",
      dataType: "text",
      url: "http://127.0.0.1:8080/" ,
      data: $('#form1').serialize(),
      success: function (result) {
          //alert(result);
          //if (result.resultCode == 200) {
              document.getElementById("imported").innerText = "Status: Success";
              var obj = JSON.parse(result);
              document.getElementById("imported").innerText = "A + B = ";
              document.getElementById("display_location").innerHTML = "&emsp;&emsp;" + obj.response;
          //};
      },
      error : function() {
          document.getElementById("imported").innerText = "Status: Fail";
      }
  });
  */
}
//</script>

function submit_call_direct() {
  document.getElementById("imported").innerText = "Submitted";
  //console.log(document.getElementById('left').value);
  document.getElementById("imported").innerText = "A + B = ";
  document.getElementById("display_location").innerHTML = "&emsp;&emsp;" + remote_import_test.Calculate(Number(document.getElementById('left').value), Number(document.getElementById('right').value));
}

function MenuPopup() {
  const template =  [
    {label: "label1"},
    {label: "click_test_here", click : () => {
        console.log("100 click_test_emit");
        document.getElementById("click_test").innerHTML = "100 click_test_emit";
      }
    },
    {role:   "undo"},
    {role:   "redo"},
    {label:  "checkbox", type: "checkbox", checked: true},
    {type:   "separator"},
    new MenuItem(
      {label: "new menu", click: () => {
        console.log("200 menu_clicked");
        document.getElementById("click_test").innerHTML = "200 menu_clicked";
      }}
    ),
    new MenuItem(
      {label: "new menu-2", click: () => {
        console.log("200 menu_clicked");
        document.getElementById("click_test").innerHTML = "200 menu_clicked";
      }}
    ),
    {label: "submenu", submenu : [
      {label: "submenu-1",  click : () => {
        console.log("300 sub_label_emit");
        document.getElementById("click_test").innerHTML = "300 sub_label_emit";
      }
    }
    ]}
  ];
  const menu = Menu.buildFromTemplate(template);

  //Sets menu as the application menu on macOS. On Windows and Linux, the menu will be set as each window's top menu.
  //Menu.setApplicationMenu(menu);
  
  menu.popup();
}

function CookieTest() {

  // Query all cookies.
  session.defaultSession.cookies.get({}, (error, cookies) => {
    console.log(error, cookies)
  })

  // Query all cookies associated with a specific url.
  session.defaultSession.cookies.get({url: 'http://www.baidu.com'}, (error, cookies) => {
    console.log(error, cookies)
  })

  /*
  // Set a cookie with the given cookie data;
  // may overwrite equivalent cookies if they exist.
  const cookie = {url: 'http://www.baidu.com', name: 'dummy_name', value: 'dummy'}
  session.defaultSession.cookies.set(cookie, (error) => {
    if (error) console.error(error)
  })
  */
}

function DesktopCapturer() {
  // In the renderer process.
  const { desktopCapturer } = require('electron')

  desktopCapturer.getSources({ types: ['window', 'screen'] }).then(async sources => {
    for (const source of sources) {
      if (source.name === 'Calculator') {
        try {
          const stream = await navigator.mediaDevices.getUserMedia({
            audio: false,
            video: {
              mandatory: {
                chromeMediaSource: 'desktop',
                chromeMediaSourceId: source.id,
                minWidth: 1280,
                maxWidth: 1280,
                minHeight: 720,
                maxHeight: 720
              }
            }
          })
          handleStream(stream)
        } catch (e) {
          handleError(e)
        }
        return
      }
    }
  })

  function handleStream (stream) {
    const video = document.querySelector('video')
    video.srcObject = stream
    video.onloadedmetadata = (e) => video.play()
  }

  function handleError (e) {
    console.log(e)
  }
}

function notification(x){
  let myNotification = new Notification('Header', {
    body: x,
  })
  myNotification.onclick = () => {
    console.log('Notification Clicked')
  }
}

function remote_import() {
  console.log(remote_import_test.hello())
}

function clipboard_write() {
  clipboard.writeText(document.getElementById("clipboard").value, 'clipboard')
  console.log('clipboard 已写入 :' + clipboard.readText('clipboard'))
}

function clipboard_read() {
  document.getElementById("clipboardStatus").innerText = clipboard.readText();
}