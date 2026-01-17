#include <X11/Xlib.h>
#include <stdio.h>
#include <X11/cursorfont.h>

int main() {
	const char *display_name = ":1";
	Display* display = XOpenDisplay(display_name);
	XSelectInput( // intercept requests from apps to X server
		display,
		DefaultRootWindow(display),
		SubstructureRedirectMask | SubstructureNotifyMask);
	XSync(display, 0); // flush request
	
	XEvent event;
	
	// Create root window
	Window root_w = XCreateSimpleWindow(display, DefaultRootWindow(display), 50, 50, 500, 500, 1, WhitePixel(display,0), BlackPixel(display,0));
	XMapWindow(display,root_w);
	Cursor root_window_cursor = XCreateFontCursor(display, 1);
	XDefineCursor(display, root_w, root_window_cursor);
	
	// Create window 1
	// TODO: window creation conditional to an event (click on an icon)
	Window w = XCreateSimpleWindow(display, root_w, 100, 100, 250, 250, 1, BlackPixel(display,0), WhitePixel(display,0));
	XMapWindow(display,w);
	XSelectInput(display,w,KeyPressMask); // what type of event the server reports to the client
	
	Cursor window1_cursor = XCreateFontCursor(display, 2);
	XDefineCursor(display, w, window1_cursor);
	
	// Interesting: after creating a child of the root window, a cursor is shown when it is outside the root window
	
	Window root_return;
	Window child_return;
	int root_x, root_y, mask_return;
	int win_x, win_y;
	char buffer[100];
	
	for (;;) {
		XNextEvent(display, &event);
		XQueryPointer(display, w, &root_return, &child_return, &root_x, &root_y, &win_x, &win_y, &mask_return);
                snprintf(buffer, sizeof(buffer), "Oi %d %d", win_x, win_y);
                
                int string_size = 3 + 1 + (win_x >= 10) + (win_x >= 100) + 1 + (win_y >= 10) + (win_y >= 100);
		
		// When a key is pressed,
		// Clear area in which string is printed, then print new string
		if (event.type == KeyPress) {
			XClearArea(display,w,100,90,100,20,False);
			XDrawString(display,w,DefaultGC(display,0),100,100,buffer,string_size);
		}
		buffer[0] = '\0';
	}
	return 0;
}
