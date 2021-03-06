//
// "$Id$"
//
// Round button header file for the Fast Light Tool Kit (FLTK).
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

#ifndef Fl_Round_Button_H
#define Fl_Round_Button_H

#include "Fl_Light_Button.H"

/** Buttons generate callbacks when they are clicked by the user. 
 * You control exactly when and how by changing the values for 
 * type() and when().
 *   \image html Fl_Round_Button.gif
 * The Fl_Round_Button subclass display the \a on state by turning 
 * on a light, rather than drawing pushed in. The shape of the 
 * "light" is initially set to \c FL_ROUND_DOWN_BOX. The color 
 * of the light when on is controlled with selection_color(), 
 * which defaults to \c FL_RED.
 */
class FL_EXPORT Fl_Round_Button : public Fl_Light_Button {
protected:
//  void draw();
public:
  static Style * default_style();


    /** Creates a new Fl_Round_Button widget using the given \a position, 
     * \a size, and \a label string. */
  Fl_Round_Button(int x,int y,int w,int h,const char *l = 0);
};

#endif

//
// End of "$Id$".
//
