//
// "$Id$"
//
// Return button header file for the Fast Light Tool Kit (FLTK).
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

#ifndef Fl_Return_Button_H
#define Fl_Return_Button_H
#include "Fl_Cancel_Button.H"

/** The Fl_Return_Button is a subclass of Fl_Button that generates a
 * callback when it is pressed or when the user presses the \a Enter key. 
 * A carriage-return symbol is drawn next to the button label.
 *   \image html Fl_Return_Button.gif
 */
class FL_EXPORT Fl_Return_Button : public Fl_Cancel_Button {

public:
  int handle(int);
  static Style * default_style();
    /** Creates a new Fl_Return_Button widget using the given \a position, 
     * \a size, and \a label string. The default boxtype is \c FL_UP_BOX . */
  Fl_Return_Button(int X, int Y, int W, int H,const char *label=0)
    : Fl_Cancel_Button(X,Y,W,H,label) {style(default_style());}
};

#endif

//
// End of "$Id$".
//
