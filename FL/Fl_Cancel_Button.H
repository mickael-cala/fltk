//
// "$Id:$"
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
// Please report all bugs and problems to "fltk-bugs@fltk.org".
//


#ifndef Fl_Cancel_Button_H
#define Fl_Cancel_Button_H
#include "Fl_Tool_Button.H"

/**
 * \brief A button with a built-in shortcut for the ESC key.
 *
 * The Fl_Cancel_Button is a subclass of Fl_Button that generates a
 * callback when it is pressed or when the user presses the \a Escape key. 
 */
class FL_EXPORT Fl_Cancel_Button : public Fl_Tool_Button {

public:

  static Style * default_style();

    /** Creates a new Fl_Return_Button widget using the given \a position, 
     * \a size, and \a label string. The default boxtype is \c FL_UP_BOX . */
  Fl_Cancel_Button(int X, int Y, int W, int H,const char *label=0)
    : Fl_Tool_Button(X,Y,W,H,label){style(default_style());}
};

#endif

//
// End of "$Id $".
//
