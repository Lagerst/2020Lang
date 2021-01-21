// Modules to control application life and create native browser window
const {app, BrowserWindow, BrowserView, ipcMain, contentTracing, Notification, powerMonitor, screen, systemPreferences, nativeTheme, TouchBar, Menu, Tray, MenuItem } = require('electron')
const path = require('path')
var calculator = require("./build/Release/calculator.node");

const os = require('os')

let mainWindow;

function createWindow () {

  const { width, height } = screen.getPrimaryDisplay().workAreaSize;
  console.log("screen.getPrimaryDisplay().workAreaSize = " + screen.getPrimaryDisplay().workAreaSize);

  console.log("systemPreferences.isDarkMode() = " + systemPreferences.isDarkMode())
  console.log("nativeTheme.shouldUseDarkColors = " + nativeTheme.shouldUseDarkColors);

  // Create the browser window.
  mainWindow = new BrowserWindow({
    width: width * 5 / 6,
    height: height * 5 / 6,
    show: false,
    //titleBarStyle: 'hidden',
    backgroundColor : "#B0D8FD",
    webPreferences: {
      webviewTag: true,
      preload: path.join(__dirname, 'preload.js'),
      nativeWindowOpen: true,
      nodeIntegration: true,
    }
  })

  mainWindow.once('ready-to-show', () => {
    mainWindow.show();
    mainWindow.setProgressBar(0.5)
    advanced_tools_set();
  });

  // and load the index.html of the app.
  mainWindow.loadFile('index.html')

  mainWindow.webContents.on("did-finish-load",
    () => {
      console.log("****did-finish-load");
    }
  )

  mainWindow.webContents.on("dom-ready",
    () => {
      console.log("****dom-ready");
    }
  )

  // Open the DevTools.
  // mainWindow.webContents.openDevTools()
}

// This method will be called when Electron has finished
// initialization and is ready to create browser windows.
// Some APIs can only be used after this event occurs.
app.on('ready', () => {
  createWindow();
  const { net } = require('electron');
  const request = net.request("http://baidu.com");
  request.on('response', (response) => {
    console.log(`Status: ${response.statusCode}`);
    //console.log(`Header: ${JSON.stringify(response.headers)}`);
    response.on('data', (chunk) => {
      //console.log(`Body: ${chunk}`);
    })
    response.on('end', (chunk) => {
      console.log(`No more Data in response`);
    })
  });
  request.end();

  //BrowserViewOpen
  //NewPageOpen();

  start_record();

  create_notification();

  TouchBar_configure();

  tray();
  
  MenuPopup();

  //session();
})

function tray() {
  tray = new Tray('./HeadPhoto.png')
  const contextMenu = Menu.buildFromTemplate([
    { label: 'Tray1', type: 'radio' },
    { label: 'Tray2', type: 'radio' },
    { label: 'Tray3', type: 'radio', checked: true },
    { label: 'Tray4', type: 'radio' }
  ])
  tray.setToolTip('This is my application.')
  tray.setContextMenu(contextMenu)

  // Make a change to the context menu
  contextMenu.items[1].checked = false

  // Call this again for Linux because we modified the context menu
  tray.setContextMenu(contextMenu)
}

function advanced_tools_set() {2
  console.log("<********************************");
  console.log(os.type());
  if (os.type() == "Darwin") {
    const dockMenu = Menu.buildFromTemplate([
      {
        label: 'New Window',
        click () { console.log('New Window') }
      },
      {
        label: 'New Window with Settings',
        submenu: [
          { label: 'Basic' },
          { label: 'Pro' }
        ]
      },
      {
        label: 'New Command...'
      }
    ])
    app.dock.setMenu(dockMenu)
  } else if (os.type == "Windows_NT") {
    console.log(process.execPath)
    app.setUserTasks([
      {
        program: process.execPath,
        arguments: '--new-window',
        iconPath: process.execPath,
        iconIndex: 0,
        title: 'New Window',
        description: 'Create a new window'
      }
    ])

    // To clear
    // app.setUserTasks([])

    const path = require('path')

    console.log(path.join(__dirname, 'HeadPhoto.jpg'));
    mainWindow.setThumbarButtons([
      {
        tooltip: 'button1',
        icon: path.join(__dirname, 'HeadPhoto.jpg'),
        flag: ['nobackground'],
        click: () => { console.log('button1 clicked') }
      }, {
        tooltip: 'button2',
        icon: path.join(__dirname, 'HeadPhoto.jpg'),
        flags: ['enabled', 'dismissonclick'],
        click: () => { console.log('button2 clicked.') }
      }
    ])

    // To clear
    // win.setThumbarButtons([])

    //To flashFrame 闪烁
    //win.once('focus', () => win.flashFrame(false))
    //win.flashFrame(true)

    //任务栏重叠
    //win.setOverlayIcon('path/to/overlay.png', 'Description for overlay')
  }
  console.log("********************************>");
}

// Quit when all windows are closed.
app.on('window-all-closed', function () {
  // On macOS it is common for applications and their menu bar
  // to stay active until the user quits explicitly with Cmd + Q
  console.log("****window-all-closed");
  app.quit()
})

app.on('activate', function () {
  // On macOS it's common to re-create a window in the app when the
  // dock icon is clicked and there are no other windows open.
  console.log("****activate");

  //create_BrowserWindow();

  if (BrowserWindow.getAllWindows().length === 0) createWindow();
})

// In this file you can include the rest of your app's specific main process
// code. You can also put them in separate files and require them here.

app.on('before-quit',function() {
    console.log("****before-quit");
  }
)

app.on('will-quit',function() {
    console.log("****will-quit");
  }
)

ipcMain.on('asynchronous-message', (event, arg) => {
  console.log(arg); // prints "ping"
  if (arg == 'ping')
    event.reply('asynchronous-reply', 'pong');
  else {
    console.log("Receive Request Message");
    console.log(arg);
    event.reply('asynchronous-reply', _calculator(arg));
  }
})

ipcMain.on('synchronous-message', (event, arg) => {
  console.log(arg); // prints "ping"
  if (arg == 'ping')
    event.returnValue = 'pong';
  else {
    console.log("Receive Request Message");
    console.log(arg);
    event.returnValue = _calculator(arg);
  }
})

//NAPI Test
console.log(calculator.hello())
function _calculator(x) {
  Content = JSON.parse(x);
  var obj = {response: calculator.Calculate(Number(Content['a']), Number(Content['b'])).toString()};
  return JSON.stringify(obj);
}

//主进程Menu
function MenuPopup() {
  const template =  [
    {
      label: "",
      role: 'TODO'
    },
    
    {
        label: "File",
    
        submenu: [
          {
            label: 'Add Item',
          },
          {
          label: 'Clear Items'
          }
        ]
    }
    
    ];
  if (process.platform == 'darwin') {
    template.unshift({label: ''});
}
  const menu = Menu.buildFromTemplate(template);

  //Sets menu as the application menu on macOS. On Windows and Linux, the menu will be set as each window's top menu.
  Menu.setApplicationMenu(menu);
  
  menu.popup();
}

//主进程BrowserView
function NewPageOpen() {
  const view = new BrowserView();
  view.setBounds({
    x: 1000, y: 0,
    width: 400,
    height:200
  })
  view.webContents.loadURL("https://www.baidu.com");
  mainWindow.setBrowserView(view);
  /*
  setTimeout(() => {
    view.destroy();
  },5000);
  */
}

function start_record() {
  const options = {
    categoryFilter: '*',
    traceOptions: 'record-until-full,enable-sampling'
  }
  contentTracing.startRecording(options, () => {
    console.log('Tracing started')
    setTimeout(() => {
      contentTracing.stopRecording('', (path) => {
        console.log('Tracing data recorded to ' + path)
      })
    }, 5000)
  })
}

function create_notification() {
  if (Notification.isSupported()) {
    let notification = new Notification({
      title: "Calculator",
      substring: "Hello Electron",
      body: "A calculator is implemented",
      hasReply: true,
      closeButtonText: "Ahhh!!!Don't close me!",
    });
    notification.show()
  }
}

function create_BrowserWindow() {
  let child = new BrowserWindow({
    width: 800,
    height: 600,
    parent: mainWindow,
    //modal: true,
    //titleBarStyle: 'hidden',
    //transparent: true,
    //frame: false,
    show: false,
    silent: false
  });
  child.loadURL('https://www.baidu.com');
  child.show();
  child.once('ready-to-show', () => {
    child.show();
  });
}

function powermonitor() {
  powerMonitor.on('suspend', () => {
    console.log('The system is awake!')
  })
}

let window

function TouchBar_configure() {
  const { TouchBarLabel, TouchBarButton, TouchBarSpacer } = TouchBar

  let spinning = false

  // Reel labels
  const reel1 = new TouchBarLabel()
  const reel2 = new TouchBarLabel()
  const reel3 = new TouchBarLabel()

  // Spin result label
  const result = new TouchBarLabel()
  // Spin button
  const spin = new TouchBarButton({
    label: '🎰 Spin',
    backgroundColor: '#7851A9',
    click: () => {
      // Ignore clicks if already spinning
      if (spinning) {
        return
      }

      spinning = true
      result.label = ''

      let timeout = 10
      const spinLength = 4 * 1000 // 4 seconds
      const startTime = Date.now()

      const spinReels = () => {
        updateReels()

        if ((Date.now() - startTime) >= spinLength) {
          finishSpin()
        } else {
          // Slow down a bit on each spin
          timeout *= 1.1
          setTimeout(spinReels, timeout)
        }
      }

      spinReels()
    }
  })

  const getRandomValue = () => {
    const values = ['🍒', '💎', '7️⃣', '🍊', '🔔', '⭐', '🍇', '🍀']
    return values[Math.floor(Math.random() * values.length)]
  }

  const updateReels = () => {
    reel1.label = getRandomValue()
    reel2.label = getRandomValue()
    reel3.label = getRandomValue()
  }

  const finishSpin = () => {
    const uniqueValues = new Set([reel1.label, reel2.label, reel3.label]).size
    if (uniqueValues === 1) {
      // All 3 values are the same
      result.label = '💰 Jackpot!'
      result.textColor = '#FDFF00'
    } else if (uniqueValues === 2) {
      // 2 values are the same
      result.label = '😍 Winner!'
      result.textColor = '#FDFF00'
    } else {
      // No values are the same
      result.label = '🙁 Spin Again'
      result.textColor = null
    }
    spinning = false
  }

  const touchBar = new TouchBar({
    items: [
      spin,
      new TouchBarSpacer({ size: 'large' }),
      reel1,
      new TouchBarSpacer({ size: 'small' }),
      reel2,
      new TouchBarSpacer({ size: 'small' }),
      reel3,
      new TouchBarSpacer({ size: 'large' }),
      result
    ]
  })

  mainWindow.setTouchBar(touchBar)
}

console.log("<********************************");

let func = function add(a, b) {
  return a + b;
}

console.log(calculator.func_process(func, 2, 3))
console.log(calculator.Create_Object('message'))
console.log(calculator.Create_Function()())

var obj = new calculator.Sample_Object(10)

console.log( obj.plusOne() ); // 11
console.log( obj.plusOne() ); // 12
console.log( obj.plusOne() ); // 13

console.log( obj.multiply().value() ); // 13
console.log( obj.multiply(10).value() ); // 130

var newobj = obj.multiply(-1);
console.log( newobj.value() ); // -13
console.log( obj === newobj ); // false

var obj = new calculator.Factory_of_wrapped_object(10);
console.log( obj.plusOne() ); // 11
console.log( obj.plusOne() ); // 12
console.log( obj.plusOne() ); // 13

var obj1 = new calculator.passing_wrapped(10);
var obj2 = new calculator.passing_wrapped(20);
var result = calculator.Add_passing_wrapped(obj1, obj2);

console.log(result); // 30

console.log("********************************>");

function session() {
  console.log("<********************************");
  let win = new BrowserWindow({ width: 800, height: 600 })
  win.loadURL('http://github.com')

  const ses = win.webContents.session
  console.log(ses.getUserAgent())
  console.log("********************************>");
}

nativeTheme.on('updated', function theThemeHasChanged () {
  updateMyAppTheme(nativeTheme.shouldUseDarkColors)
})

ipcMain.on('ondragstart', (event, filePath) => {
  console.log('ondragstart, send file ' + filePath)
  event.sender.startDrag({
    file: filePath,
    icon: './HeadPhoto.png'
  })
})

app.addRecentDocument('/Users/pengziwei/Desktop/ByteWorkSpace/input.txt')

//app.clearRecentDocuments()
