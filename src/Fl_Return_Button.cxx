//
// "$Id: Fl_Return_Button.cxx,v 1.10 1999/08/16 07:31:20 bill Exp $"
//
// Return button widget for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-1999 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

#include <FL/Fl.H>
#include <FL/Fl_Return_Button.H>
#include <FL/fl_draw.H>

Fl_Return_Button::Fl_Return_Button(int x,int y,int w,int h,const char *l)
  : Fl_Button(x,y,w,h,l) {}

int fl_return_arrow(int x, int y, int w, int h, int active) {
  int size = w; if (h<size) size = h;
  int d = (size+2)/4; if (d<3) d = 3;
  int t = (size+9)/12; if (t<1) t = 1;
  int x0 = x+(w-2*d-2*t-1)/2;
  int x1 = x0+d;
  int y0 = y+h/2;
  fl_color(active ? FL_LIGHT3 : FL_LIGHT1);
  fl_line(x0, y0, x1, y0+d);
  fl_yxline(x1, y0+d, y0+t, x1+d+2*t, y0-d);
  fl_yxline(x1, y0-t, y0-d);
  fl_color(active ? FL_BLACK : FL_INACTIVE_COLOR);
  fl_line(x0, y0, x1, y0-d);
  fl_color(active ? FL_DARK3 : FL_INACTIVE_COLOR);
  fl_xyline(x1+1,y0-t,x1+d,y0-d,x1+d+2*t);
  return 1;
}

int fl_return_arrow(int x, int y, int w, int h) {
  return fl_return_arrow(x, y, w, h, 1);
}

void Fl_Return_Button::draw() {
  Fl_Color lc = draw_button();
  int W = h();
  if (w()/3 < W) W = w()/3;
  fl_return_arrow(x()+w()-W-4, y(), W, h(), active_r());
  draw_button_label(x(), y(), w()-W+4, h(), lc);
}

int Fl_Return_Button::handle(int event) {
  if (event == FL_SHORTCUT &&
      (Fl::event_key() == FL_Enter || Fl::event_key() == FL_KP_Enter)) {
    do_callback();
    return 1;
  } else
    return Fl_Button::handle(event);
}

//
// End of "$Id: Fl_Return_Button.cxx,v 1.10 1999/08/16 07:31:20 bill Exp $".
//
