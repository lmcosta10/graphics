Currently studying X11

To compile, run:

```
gcc window.c -lX11
```

<h2>Xephyr</h2>

Creates a nested X server, which is a separate desktop environment running inside a window on your main display

Running it:

```
Xephyr :1 -ac -screen 800x600 &
```

Using it:

Option 1:

Set DISPLAY=:1.

Option 2: in your code:

```
const char *display_name = ":1";
Display* display = XOpenDisplay(display_name);
```