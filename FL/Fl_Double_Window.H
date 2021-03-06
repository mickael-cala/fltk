//
// "$Id$"
//
// Double-buffered window header file for the Fast Light Tool Kit (FLTK).
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

#ifndef Fl_Double_Window_H
#define Fl_Double_Window_H

#include "Fl_Window.H"

/** The Fl_Double_Window class provides a double-buffered window. If
 * possible this will use the X double buffering extension (Xdbe). If not,
 * it will draw the window data into an off-screen pixmap, and then copy it
 * to the on-screen window.
 *
 * It is highly recommended that you put the following code before the first
 * show() of anywindow in your program:
 *
 * <tt>Fl::visual(FL_DOUBLE|FL_INDEX)</tt>
 *
 * This makes sure you can use Xdbe on servers where double buffering does
 * not exist for every visual.
 */
class FL_EXPORT Fl_Double_Window : public Fl_Window {
protected:
  void flush(int eraseoverlay);
  char force_doublebuffering_; // force db, even if the OS already buffers windows (overlays need that on MacOS and Windows2000)
public:
  void show();
  void show(int a, char **b) {Fl_Window::show(a,b);}
  void flush();
  void resize(int,int,int,int);
  void hide();
  ~Fl_Double_Window();
  Fl_Double_Window(int W, int H, const char *l = 0) 
    : Fl_Window(W,H,l), force_doublebuffering_(0) { type(FL_DOUBLE_WINDOW); }
    /** Creates a new Fl_Double_Window widget using the given position,
     * size, and label (title) string. */
  Fl_Double_Window(int X, int Y, int W, int H, const char *l = 0)
    : Fl_Window(X,Y,W,H,l), force_doublebuffering_(0) { type(FL_DOUBLE_WINDOW); }
};

#endif

//
// End of "$Id$".
//
