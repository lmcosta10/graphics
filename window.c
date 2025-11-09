#include <X11/Xlib.h>
#include <stdio.h>

int main() {
	XEvent event;
	Display* display = XOpenDisplay(NULL);
	Window w = XCreateSimpleWindow(display, DefaultRootWindow(display), 50, 50, 250, 250, 1, BlackPixel(display,0), WhitePixel(display,0));
	XMapWindow(display,w);
	XSelectInput(display,w,KeyPressMask); // what type of event the server reports to the client
	
	Window root_return;
	Window child_return;
	int root_x, root_y, mask_return;
	int win_x, win_y;
	char buffer[100];
	
	for (;;) {
		XNextEvent(display, &event);
		XQueryPointer(display, w, &root_return, &child_return, &root_x, &root_y, &win_x, &win_y, &mask_return);
        	snprintf(buffer, sizeof(buffer), "Oi %d %d", win_x, win_y);
		
		// When a key is pressed,
		// Clear area in which string is printed, then print new string
		if (event.type == KeyPress) {
			XClearArea(display,w,100,90,100,20,False);
			XDrawString(display,w,DefaultGC(display,0),100,100,buffer,100);
		}
		buffer[0] = '\0';
	}
	return 0;
}
