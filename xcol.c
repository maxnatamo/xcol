#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "./xcol.h"

void usage(char *argv0) {
    printf("usage: %s [-h] [-v]\n", argv0);
}

int xcol_setup(xcol_t *e) {
    e->dsp = XOpenDisplay(NULL);

    if(!e->dsp || e->dsp == NULL) {
        fprintf(stderr, "failed to open display\n");
        return 1;
    }

    e->root   = XDefaultRootWindow(e->dsp);
    e->screen = DefaultScreen(e->dsp);

    XGrabPointer(e->dsp, e->root, False, ButtonReleaseMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
    XSelectInput(e->dsp, e->root, ButtonReleaseMask);

    return 0;
}

int xcol_handle_event(xcol_t *e) {
    XNextEvent(e->dsp, &(e->event));
    switch(e->event.type) {
        case ButtonRelease:
            if(e->event.xbutton.button == Button1) {
                xcol_handle_click(e);
                return 0;
            }
            break;

        default:
            break;
    }

    return 0;
}

void xcol_get_color(xcol_t *e, int x, int y, XColor *color) {
    XImage *img  = XGetImage(e->dsp, e->root, e->event.xbutton.x, e->event.xbutton.y, 1, 1, AllPlanes, XYPixmap);
    color->pixel = XGetPixel(img, 0, 0);

    XQueryColor(e->dsp, DefaultColormap(e->dsp, e->screen), color);
    XFree(img);
}

void xcol_handle_click(xcol_t *e) {
    XColor col;
    xcol_get_color(e, e->event.xbutton.x, e->event.xbutton.y, &col);

    int r = col.red   / 256;
    int g = col.green / 256;
    int b = col.blue  / 256;

    if(e->options.hex == 1) {
        char *rh = xcol_util_dectohex(r);
        char *gh = xcol_util_dectohex(g);
        char *bh = xcol_util_dectohex(b);

        printf("#%s%s%s\n", rh, gh, bh);
    } else {
        printf("%d, %d, %d\n", r, g, b);
    }
}

int main(int argc, char *argv[]) {
    int c;
    xcol_t *e = calloc(1, sizeof(xcol_t));

    while((c = getopt(argc, argv, "hv")) != -1) {
        switch(c) {
            case 'v':
                printf("%s " VERSION "\n", argv[0]);
                usage(argv[0]);
                return 1;
            case 'h':
                e->options.hex = 1;
                break;
            case '?':
                usage(argv[0]);
                return 1;
        }
    }

    if(xcol_setup(e) == 0) {
        return xcol_handle_event(e);
    }
    return 1;
}
