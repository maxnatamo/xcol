#ifndef _XCOL_H
#define _XCOL_H

#include <X11/Xlib.h>

typedef struct {
    Display *dsp;
    Window root;
    int screen;
    XEvent event;

    struct {
        int hex;
    } options;
} xcol_t;

// xcol.c
void  usage(char *);
int   xcol_setup(xcol_t *);
int   xcol_handle_event(xcol_t *);
void  xcol_get_color(xcol_t *, int, int, XColor *);
void  xcol_handle_click(xcol_t *);

// util.c
char *xcol_util_dectohex(unsigned char);

#endif /* _XCOL_H */
