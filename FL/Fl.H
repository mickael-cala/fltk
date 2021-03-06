//
// "$Id$"
//
// Main header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2005 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

#ifndef Fl_H
#  define Fl_H

#  include "Enumerations.H"
#  ifndef Fl_Object
#    define Fl_Object Fl_Widget
#  endif

#  ifdef check
#    undef check
#  endif

class Fl_Widget;
class Fl_Window;
class Fl_Image;
struct Fl_Label;
typedef void (Fl_Label_Draw_F)(const Fl_Label*, int,int,int,int, Fl_Align);
typedef void (Fl_Label_Measure_F)(const Fl_Label*, int&, int&);
//typedef void (Fl_Box_Draw_F)(int,int,int,int, Fl_Color);

typedef void (*Fl_Timeout_Handler)(void*);

/**
 * \brief Access to global information and methods.
 *
 * The Fl class is the FLTK global (static) class containing state information and
 * global methods for the current application. */
class FL_EXPORT Fl {
  Fl() {}; // no constructor!

public: // should be private!

  static int e_number;
  static int e_x;
  static int e_y;
  static int e_x_root;
  static int e_y_root;
  static int e_dx;
  static int e_dy;
  static int e_state;
  static int e_clicks;
  static int e_is_click;
  static int e_keysym;
  static char* e_text;
  static int e_length;
  static Fl_Widget* belowmouse_;
  static Fl_Widget* pushed_;
  static Fl_Widget* focus_;
  static int damage_;
  static Fl_Widget* selection_owner_;
  static Fl_Window* modal_;
  static Fl_Window* grab_;
  static int compose_state;
  static int visible_focus_;
  static int dnd_text_ops_;
  static void damage(int d) {damage_ = d;}

  static void (*idle)();

  static const char* scheme_;
  static Fl_Image* scheme_bg_;

public:

  // API version number
  static double version();

  // argument parsers:
    /** Consume a single switch from \a argv, starting at word \a i. Returns the
     * number of words eaten (1 or 2, or 0 if it is not recognized) and adds the same
     * value to \a i. You can use this function if you prefer to control the
     * incrementing through the arguments yourself. */
  static int arg(int argc, char** argv, int& i);
    /** FLTK provides an <i>entirely optional</i> command-line switch parser. You don't
     * have to call it if you don't like them! Everything it can do can be done with other
     * calls to FLTK.
     *
     * To use the switch parser, call Fl::args(...) near the start of your program. This
     * does not open the display, instead switches that need the display open are stashed
     * into static variables. Then you must display your first window by calling 
     * <tt>window->show(argc,argv)</tt>, which will do anything stored in the static
     * variables.
     *
     * \a callback lets you define your own switches. It is called with the same \a argc
     * and \a argv, and with \a i the index of each word. The callback should return
     * zero if the switch is unrecognized, and not change i. It should return non-zero
     * if the switch is recognized, and add at least 1 to i (it can add more to
     * consume words after the switch). This function is called before any other
     * tests, so you can override any FLTK switch (this is why FLTK can use very
     * short switches instead of the long ones all other toolkits force you to use).
     *
     * On return \a i is set to the index of the first non-switch. This is either:
     * \arg The first word that does not start with '-'.
     * \arg The word '-' (used by many programs to name stdin as a file)
     * \arg The first unrecognized switch (return value is 0).
     * \arg \a argc
     *
     * The return value is \a i unless an unrecognized switch is found, in which case
     * it is zero. If your program takes no arguments other than switches you should
     * produce an error if the return value is less than argc.
     *
     * All switches except -bg2 may be abbreviated one letter and case is ignored:
     * \arg \c -bg \a color or \c -background \a color : Sets the background color using Fl::background().
     * \arg \c -bg2 \a color or \c -background2 \a color : Sets the secondary background color using Fl::background2().
     * \arg \c -display \a host:n.n : Sets the X display to use; this option is silently ignored under WIN32 and MacOS.
     * \arg \c -dnd and \c -nodnd : Enables or disables drag and drop text operations using Fl::dnd_text_ops().
     * \arg \c -fg \a color or \c -foreground \a color : Sets the foreground color using Fl::foreground().
     * \arg \c -geometry \a WxH+X+Y : Sets the initial window position and size according the the standard X geometry string.
     * \arg \c -iconic : Iconifies the window using Fl_Window::iconize().
     * \arg \c -kbd and \c -nokbd : Enables or disables visible keyboard focus for non-text widgets using Fl::visible_focus().
     * \arg \c -name \a string : Sets the window class using Fl_Window::xclass().
     * \arg \c -scheme \a string : Sets the widget scheme using Fl::scheme().
     * \arg \c -title \a string : Sets the window title using Fl_Window::label().
     * \arg \c -tooltips and \c -notooltips : Enables or disables tooltips using Fl_Tooltip::enable().
     *
     * A usage string is displayed if Fl::args() detects an invalid argument on the
     * command-line. You can change the message by setting the Fl::help pointer. */
  static int args(int, char**, int&, int (*)(int,char**,int&) = 0);
  static const char* const help;
    /** The second form of Fl::args() is useful if your program does not have command
     * line switches of its own. It parses all the switches, and if any are not
     * recognized it calls Fl::abort(Fl::help); */
  static void args(int, char**);

  // things called by initialization:
  static void display(const char*);
  static int visual(int);
  static int gl_visual(int, int *alist=0);
  static void own_colormap();
  static void get_system_colors();
  static void foreground(uchar, uchar, uchar);
  static void background(uchar, uchar, uchar);
  static void background2(uchar, uchar, uchar);

  // schemes:
  static int scheme(const char*);
  static const char* scheme() {return scheme_;}
  static int reload_scheme();

  // execution:
  static int wait();
  static double wait(double time);
  static int check();
  static int ready();
  static int run();
  static Fl_Widget* readqueue();
    /** Add a one-shot timeout callback. The function will be called by Fl::wait() at
     * \a t seconds after this function is called. The optional void* argument is passed
     * to the callback. */
  static void add_timeout(double t, Fl_Timeout_Handler,void* = 0);
  static void repeat_timeout(double t, Fl_Timeout_Handler,void* = 0);
  static int  has_timeout(Fl_Timeout_Handler, void* = 0);
  static void remove_timeout(Fl_Timeout_Handler, void* = 0);
    /** FLTK will call this callback just before it flushes the display and waits for
     * events. This is different than an idle callback because it is only called once, 
     * then FLTK calls the system and tells it not to return until an event happens.
     *
     * This can be used by code that wants to monitor the application's state, such as
     * to keep a display up to date. The advantage of using a check callback is that
     * it is called only when no events are pending. If events are coming in quickly,
     * whole blocks of them will be processed before this is called once. This can
     * save significant time and avoid the application falling behind the events.
     *
     * \code
        bool state_changed; // anything that changes the display turns this on
        
        void callback(void*) {
          if (!state_changed) return;
          state_changed = false;
          do_expensive_calculation();
          widget->redraw();
        }
        
        main() {
          Fl::add_check(callback);
          return Fl::run();
        }
    * \endcode
    */
  static void add_check(Fl_Timeout_Handler, void* = 0);
  static int  has_check(Fl_Timeout_Handler, void* = 0);
  static void remove_check(Fl_Timeout_Handler, void* = 0);
    /** Add file descriptor fd to listen to. When the fd becomes ready for reading
     * Fl::wait() will call the callback and then return. The callback is passed the
     * fd and the arbitrary void* argument.
     *
     * The second version takes a when bitfield, with the bits \c FL_READ, \c FL_WRITE,
     * and \c FL_EXCEPT defined, to indicate when the callback should be done.
     *
     * There can only be one callback of each type for a file descriptor. 
     * Fl::remove_fd() gets rid of all the callbacks for a given file descriptor.
     *
     * Under UNIX any file descriptor can be monitored (files, devices, pipes, sockets,
     * etc.) Due to limitations in Microsoft Windows, WIN32 applications can only
     * monitor sockets. */
  static void add_fd(int fd, int when, void (*cb)(int,void*),void* =0);
  static void add_fd(int fd, void (*cb)(int, void*), void* = 0);
  static void remove_fd(int, int when);
  static void remove_fd(int);
    /** Adds a callback function that is called every time by Fl::wait() and also makes
     * it act as though the timeout is zero (this makes Fl::wait() return immediately,
     * so if it is in a loop it is called repeatedly, and thus the idle fucntion is called
     * repeatedly). The idle function can be used to get background processing done.
     * 
     * You can have multiple idle callbacks. To remove an idle callback use Fl::remove_idle().
     *
     * Fl::wait() and Fl::check() call idle callbacks, but Fl::ready() does not.
     * 
     * The idle callback can call any FLTK functions, including Fl::wait(), Fl::check(), 
     * and Fl::ready(). FLTK will not recursively call the idle callback. */
  static void add_idle(void (*cb)(void*), void* = 0);
  static int  has_idle(void (*cb)(void*), void* = 0);
  static void remove_idle(void (*cb)(void*), void* = 0);
  static int damage() {return damage_;}
  static void redraw();
  static void flush();
  static void (*warning)(const char*, ...);
  static void (*error)(const char*, ...);
  static void (*fatal)(const char*, ...);
  static Fl_Window* first_window();
  static void first_window(Fl_Window*);
  static Fl_Window* next_window(const Fl_Window*);
  static Fl_Window* modal() {return modal_;}
  static Fl_Window* grab() {return grab_;}
  static void grab(Fl_Window*);

  // event information:
  static int event()		{return e_number;}
  static int event_x()	{return e_x;}
  static int event_y()	{return e_y;}
  static int event_x_root()	{return e_x_root;}
  static int event_y_root()	{return e_y_root;}
  static int event_dx()	{return e_dx;}
  static int event_dy()	{return e_dy;}
  static void get_mouse(int &,int &);
  static int event_clicks()	{return e_clicks;}
  static void event_clicks(int i) {e_clicks = i;}
  static int event_is_click()	{return e_is_click;}
  static void event_is_click(int i) {e_is_click = i;} // only 0 works!
  static int event_button()	{return e_keysym-FL_Button;}
  static int event_state()	{return e_state;}
  static int event_state(int i) {return e_state&i;}
  /** Function returns which key on the keyboard was last pushed. It returns zero if the last event was not a key press or release. */
  static int event_key()	{return e_keysym;} 
  static int event_key(int);
  static int get_key(int);
  static const char* event_text() {return e_text;}
  static int event_length() {return e_length;}
  static int compose(int &del);
  static void compose_reset() {compose_state = 0;}
  static int event_inside(int,int,int,int);
  static int event_inside(const Fl_Widget*);
  static int test_shortcut(int);

  // event destinations:
  static int handle(int, Fl_Window*);
  static Fl_Widget* belowmouse() {return belowmouse_;}
  static void belowmouse(Fl_Widget*);
  static Fl_Widget* pushed()	{return pushed_;}
  static void pushed(Fl_Widget*);
  static Fl_Widget* focus()	{return focus_;}
  static void focus(Fl_Widget*);
    /** Install a function to parse unrecognized events. If FLTK cannot figure out what
     * to do with an event, it calls each of these functions (most recent first) until
     * one of them returns non-zero. If none of them returns non zero then the event is
     * ignored. Events that cause this to be called are:
     * \arg \c FL_SHORTCUT events that are not recognized by any widget. This lets you
     *      provide global shortcut keys.
     * \arg System events that FLTK does not recognize. See fl_xevent.
     * \arg \a Some other events when the widget FLTK selected returns zero from its
     *       handle() method. Exactly which ones may change in future versions, however. */
  static void add_handler(int (*h)(int));
  static void remove_handler(int (*h)(int));

  // cut/paste:
  static void copy(const char* stuff, int len, int clipboard = 0);
  static void paste(Fl_Widget &receiver, int clipboard /*=0*/);
  static int dnd();
  // These are for back-compatability only:
  static Fl_Widget* selection_owner() {return selection_owner_;}
  static void selection_owner(Fl_Widget*);
  static void selection(Fl_Widget &owner, const char*, int len);
  static void paste(Fl_Widget &receiver);

  // screen size:
#if defined(WIN32) || defined(__APPLE__)
  static int x();
  static int y();
#else
  static int x() {return 0;}
  static int y() {return 0;}
#endif /* WIN32 || __APPLE__ */
  static int w();
  static int h();

  // multi-head support:
  static int screen_count();
  static void screen_xywh(int &x, int &y, int &w, int &h) {
    screen_xywh(x, y, w, h, e_x_root, e_y_root);
  }
  static void screen_xywh(int &x, int &y, int &w, int &h, int mx, int my);
  static void screen_xywh(int &x, int &y, int &w, int &h, int n);

  // color map:
  static void	set_color(Fl_Color, uchar, uchar, uchar);
  static void	set_color(Fl_Color, unsigned);
  static unsigned get_color(Fl_Color);
  static void	get_color(Fl_Color, uchar&, uchar&, uchar&);
  static void	free_color(Fl_Color, int overlay = 0);

  // fonts:
  static const char* get_font(Fl_Font);
  static const char* get_font_name(Fl_Font, int* attributes = 0);
  static int get_font_sizes(Fl_Font, int*& sizep);
  static void set_font(Fl_Font, const char*);
  static void set_font(Fl_Font, Fl_Font);
  static Fl_Font set_fonts(const char* = 0);

  // labeltypes:
  static void set_labeltype(Fl_Labeltype,Fl_Label_Draw_F*,Fl_Label_Measure_F*);
  static void set_labeltype(Fl_Labeltype, Fl_Labeltype from);

  // boxtypes:
  static Fl_Box_Draw_F *get_boxtype(Fl_Boxtype);
  static void set_boxtype(Fl_Boxtype, Fl_Box_Draw_F*,uchar,uchar,uchar,uchar);
  static void set_boxtype(Fl_Boxtype, Fl_Boxtype from);
  //static Fl_Boxtype add_boxtype(Fl_Box_Draw_F*,uchar,uchar,uchar,uchar);
  //static Fl_Boxtype add_boxtype(Fl_Box_Draw_F* f, uchar a, uchar b, uchar c, uchar d, Fl_Boxtype down_box);

  static int box_dx(Fl_Boxtype);
  static int box_dy(Fl_Boxtype);
  static int box_dw(Fl_Boxtype);
  static int box_dh(Fl_Boxtype);
  static int draw_box_active();
  static int draw_box_value();
  static int box_index(Fl_Boxtype);
  static Fl_Boxtype box(int index);

  // back compatability:
  static void set_abort(void (*f)(const char*,...)) {fatal = f;}
  static void (*atclose)(Fl_Window*,void*);
  static void default_atclose(Fl_Window*,void*);
  static void set_atclose(void (*f)(Fl_Window*,void*)) {atclose = f;}
  static int event_shift() {return e_state&FL_SHIFT;}
  static int event_ctrl() {return e_state&FL_CTRL;}
  static int event_alt() {return e_state&FL_ALT;}
  static int event_buttons() {return e_state&0x7f000000;}
  static int event_button1() {return e_state&FL_BUTTON1;}
  static int event_button2() {return e_state&FL_BUTTON2;}
  static int event_button3() {return e_state&FL_BUTTON3;}
  static void set_idle(void (*cb)()) {idle = cb;}
  static void grab(Fl_Window&win) {grab(&win);}
  static void release() {grab(0);}

  // Visible focus methods...
  static void visible_focus(int v) { visible_focus_ = v; }
  static int  visible_focus() { return visible_focus_; }

  // Drag-n-drop text operation methods...
  static void dnd_text_ops(int v) { dnd_text_ops_ = v; }
  static int  dnd_text_ops() { return dnd_text_ops_; }

  // Multithreading support:
  static void lock();
  static void unlock();
  static void awake(void* message = 0);
  static void* thread_message();
  
  // Widget deletion:
  static void delete_widget(Fl_Widget *w);
  static void do_widget_deletion();


  //static void redraw_scheme();
};

#endif // !Fl_H

//
// End of "$Id$".
//
