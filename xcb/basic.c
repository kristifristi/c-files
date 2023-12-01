#include <unistd.h>      /* pause() */

#include <xcb/xcb.h>

int main ()
{
        /* Open the connection to the X server */
        xcb_connection_t *connection = xcb_connect (NULL, NULL);


        /* Get the first screen */
        const xcb_setup_t      *setup  = xcb_get_setup (connection);
        xcb_screen_iterator_t   iter   = xcb_setup_roots_iterator (setup);
        xcb_screen_t           *screen = iter.data;


        /* Create the window */
        xcb_window_t window = xcb_generate_id (connection);
        xcb_create_window (connection,                    /* Connection          */
                           XCB_COPY_FROM_PARENT,          /* depth (same as root)*/
                           window,                        /* window Id           */
                           screen->root,                  /* parent window       */
                           0, 0,                          /* x, y                */
                           512, 512,                      /* width, height       */
                           10,                            /* border_width        */
                           XCB_WINDOW_CLASS_INPUT_OUTPUT, /* class               */
                           screen->root_visual,           /* visual              */
                           0, NULL );                     /* masks, not used yet */

   	//gc creation
   	xcb_drawable_t  drWindow   = screen->root;
        xcb_gcontext_t  black    = xcb_generate_id (connection);
        uint32_t        mask     = XCB_GC_FOREGROUND;
        uint32_t        value[]  = { screen->white_pixel };
        xcb_create_gc (connection, black, drWindow, mask, value);
        /* Map the window on the screen */
        xcb_map_window (connection, window);
        xcb_arc_t myArc = { 400, 400, 300, 150, 0, 180 << 6 };  
        /* Make sure commands are sent before we pause so that the window gets shown */
        xcb_flush (connection);

	while(1){
		xcb_poly_arc(connection, drWindow, black, 1, &myArc);
		usleep(100000);
		}
       

        return 0;
}
