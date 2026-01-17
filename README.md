Currently studying X11

To compile, run:

```
gcc window_manager.c -lX11
```

<h2>Xephyr</h2>

Creates a nested X server, which is a separate desktop environment running inside a window on your main display

Running it:

```
Xephyr :1 -ac -screen 800x600 &
```

If you receive an error saying "Server is already active for display 1", you can change ":1" to something else (such as ":2"). Remember to change this on the following steps too.

Using it:

Option 1:

Set DISPLAY=:1.

Option 2: in your code:

```
const char *display_name = ":1";
Display* display = XOpenDisplay(display_name);
```
