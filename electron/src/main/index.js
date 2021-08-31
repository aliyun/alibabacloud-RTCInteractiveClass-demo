import { app, BrowserWindow, ipcMain, Menu } from 'electron'
import '../renderer/store'

/**
 * Set `__static` path to static files in production
 * https://simulatedgreg.gitbooks.io/electron-vue/content/en/using-static-assets.html
 */
if (process.env.NODE_ENV !== 'development') {
  global.__static = require('path').join(__dirname, '/static').replace(/\\/g, '\\\\')
}

let mainWindow
let isInClass = false
const winURL = process.env.NODE_ENV === 'development'
  ? `http://localhost:80`
  : `file://${__dirname}/index.html`

function createWindow() {
  /**
   * Initial window options
   */
  // Menu.setApplicationMenu(null)
  mainWindow = new BrowserWindow({
    height: 706,
    useContentSize: true,
    width: 900,
    webPreferences: {
      nodeIntegration: true,
      nodeIntegrationInWorker: true
    }
  })

  mainWindow.loadURL(winURL)

  mainWindow.on('close', (e) => {
    if (isInClass) {
      mainWindow && mainWindow.webContents.send('app-close')
      e.preventDefault()
    } else {
      mainWindow = null;
    }
  })

  mainWindow.on('closed', () => {
    mainWindow = null
  })
}

app.on('ready', createWindow)

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit()
  }
})

app.on('activate', () => {
  if (mainWindow === null) {
    createWindow()
  }
})

ipcMain.on('enterClass', () => {
  isInClass = true
})

ipcMain.on('leaveClass', () => {
  isInClass = false
})

/**
 * Auto Updater
 *
 * Uncomment the following code below and install `electron-updater` to
 * support auto updating. Code Signing with a valid certificate is required.
 * https://simulatedgreg.gitbooks.io/electron-vue/content/en/using-electron-builder.html#auto-updating
 */

/*
import { autoUpdater } from 'electron-updater'

autoUpdater.on('update-downloaded', () => {
  autoUpdater.quitAndInstall()
})

app.on('ready', () => {
  if (process.env.NODE_ENV === 'production') autoUpdater.checkForUpdates()
})
 */