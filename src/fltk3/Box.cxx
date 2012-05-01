//
// "$Id$"
//
// Box widget for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2010 by Bill Spitzak and others.
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

#include <fltk3/Widget.h>
#include <fltk3/Box.h>
#include <fltk3/Wrapper.h>


fltk3::Box::Box(int X, int Y, int W, int H, const char *l)
: fltk3::Widget(X,Y,W,H,l) 
{
  set_group_relative(); // FIXME: remove
}


fltk3::Box::Box(fltk3::Boxtype b, int X, int Y, int W, int H, const char *l)
: fltk3::Widget(X,Y,W,H,l) 
{
  set_group_relative(); // FIXME: remove
  box(b);
}


void fltk3::Box::draw() {
  draw_box();
  draw_label();
}


int fltk3::Box::handle(int event) {
  if (event == fltk3::ENTER || event == fltk3::LEAVE) return 1;
  else return 0;
}


//
// End of "$Id$".
//
