"""Keep standard X11 window atoms available on a bare Xvfb test display.
No window manager, audio/plugin modification or timing instrumentation.
Usage: DISPLAY=:99 python scripts/headless_realtime.py COMMAND [ARGS ...]
"""
import ctypes,ctypes.util,os,subprocess,sys
x=ctypes.CDLL(ctypes.util.find_library('X11'));x.XOpenDisplay.argtypes=[ctypes.c_char_p];x.XOpenDisplay.restype=ctypes.c_void_p
x.XInternAtom.argtypes=[ctypes.c_void_p,ctypes.c_char_p,ctypes.c_int];x.XInternAtom.restype=ctypes.c_ulong
x.XSync.argtypes=[ctypes.c_void_p,ctypes.c_int];x.XCloseDisplay.argtypes=[ctypes.c_void_p]
d=x.XOpenDisplay(os.environ.get('DISPLAY',':99').encode());assert d,'X11 display unavailable'
for name in ('WM_PROTOCOLS','WM_TAKE_FOCUS','WM_DELETE_WINDOW','WM_CHANGE_STATE','WM_STATE','_NET_WM_PING','_NET_WM_WINDOW_TYPE','_NET_WM_STATE','_NET_WM_STATE_HIDDEN','_NET_WM_WINDOW_TYPE_NORMAL','_NET_WM_WINDOW_TYPE_DIALOG','_NET_WM_WINDOW_TYPE_UTILITY','_NET_WM_STATE_FULLSCREEN','UTF8_STRING'):
 x.XInternAtom(d,name.encode(),False)
x.XSync(d,False)
try:result=subprocess.run(sys.argv[1:]);code=result.returncode
finally:x.XCloseDisplay(d)
raise SystemExit(code)
