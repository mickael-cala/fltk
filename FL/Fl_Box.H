//
// "$Id$"
//
// Box header file for the Fast Light Tool Kit (FLTK).
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

#ifndef Fl_Box_H
#define Fl_Box_H

#ifndef Fl_Widget_H
#include "Fl_Widget.H"
#endif

/**
 * \brief Simple widget rendering a box.
 *
 * This widget simply draws its box, and possibly it's label. Putting it before some other
 * widgets and making it big enough to surround them will let you draw a frame around them.
 */
class FL_EXPORT Fl_Box : public Fl_Widget {
protected:
  void draw();
public:
    /** The constructor sets box() to \c FL_NO_BOX, which means it is invisible. However such
     * widgets are useful as placeholders or Fl_Group::resizable() values. To change the box 
     * to something visible, use box(n). */
  Fl_Box(int X, int Y, int W, int H, const char *l=0)
	: Fl_Widget(X,Y,W,H,l) {}
    /** This form of the constructor sets the box to the specified box type. */
  Fl_Box(Fl_Boxtype boxtype, int X, int Y, int W, int H, const char *l)
	: Fl_Widget(X,Y,W,H,l) {box(boxtype);}

  virtual int handle(int);
};

#endif

//
// End of "$Id$".
//
