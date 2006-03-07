// "$Id$"
//
// Copyright 1998-2004 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@fltk.org".

#ifndef fltk_ShapedWindow_h
#define fltk_ShapedWindow_h

#include <fltk/Window.h>
#include <fltk/xbmImage.h>

namespace fltk {

class FL_API ShapedWindow : public Window {
  public:
    ShapedWindow(int W, int H, const char *l = 0)  : Window(W,H,l) { init();}
    ShapedWindow(int X, int Y, int W, int H, const char *l = 0): Window(X,Y,W,H,l) { init();}
    void shape(xbmImage* b) { shape_ = b; changed = 1; }
    void shape(xbmImage& b) { shape_ =&b; changed = 1; }

  protected:
    void init();
    virtual void draw();
    xbmImage* shape_;
    int lw, lh;
    int changed;
};

}
#endif

//
// End of "$Id$"
//
