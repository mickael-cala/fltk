//
// "$Id: Slider.H 7365 2010-03-30 15:18:29Z matt $"
//
// Slider header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2009 by Bill Spitzak and others.
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

/* \file
   Slider widget . */

#ifndef Fltk3_Slider_H
#define Fltk3_Slider_H

#include "Valuator.h"

// values for type(), lowest bit indicate horizontal:
#define FL_VERT_SLIDER		0
#define FL_HOR_SLIDER		1
#define FL_VERT_FILL_SLIDER	2
#define FL_HOR_FILL_SLIDER	3
#define FL_VERT_NICE_SLIDER	4
#define FL_HOR_NICE_SLIDER	5

namespace fltk3 {

/**
  The Slider widget contains a sliding knob inside a box. It if
  often used as a scrollbar.  Moving the box all the way to the
  top/left sets it to the minimum(), and to the bottom/right to the
  maximum().  The minimum() may be greater than the maximum() to
  reverse the slider direction.

  Use void fltk3::Widget::type(int) to set how the slider is drawn, 
  which can be one of the following:
  
  \li FL_VERTICAL - Draws a vertical slider (this is the default).
  \li FL_HORIZONTAL - Draws a horizontal slider.
  \li FL_VERT_FILL_SLIDER - Draws a filled vertical slider,
      useful as a progress or value meter.
  \li FL_HOR_FILL_SLIDER - Draws a filled horizontal  slider,
      useful as a progress or value meter.
  \li FL_VERT_NICE_SLIDER - Draws a vertical slider with  a nice
      looking control knob.
  \li FL_HOR_NICE_SLIDER - Draws a horizontal slider with  a
      nice looking control knob.

  \image html  slider.gif 
  \image latex slider.eps "Slider" width=4cm
*/
class FL_EXPORT Slider : public fltk3::Valuator {

  float slider_size_;
  uchar slider_;
  void _Slider();
  void draw_bg(int, int, int, int);

protected:

  // these allow subclasses to put the slider in a smaller area:
  void draw(int, int, int, int);
  int handle(int, int, int, int, int);
  void draw();

public:

  int handle(int);
  Slider(int X,int Y,int W,int H, const char *L = 0);
  Slider(uchar t,int X,int Y,int W,int H, const char *L);

  int scrollvalue(int pos,int size,int first,int total);
  void bounds(double a, double b);

  /**
    Get the dimensions of the moving piece of slider.
  */
  float slider_size() const {return slider_size_;}

  /**
    Set the dimensions of the moving piece of slider. This is
    the fraction of the size of the entire widget. If you set this
    to 1 then the slider cannot move.  The default value is .08.

    For the "fill" sliders this is the size of the area around the
    end that causes a drag effect rather than causing the slider to
    jump to the mouse.
  */
  void slider_size(double v);

  /** Gets the slider box type. */
  fltk3::Boxtype slider() const {return (fltk3::Boxtype)slider_;}

  /** Sets the slider box type. */
  void slider(fltk3::Boxtype c) {slider_ = c;}
};
  
}

#endif

//
// End of "$Id: Slider.H 7365 2010-03-30 15:18:29Z matt $".
//