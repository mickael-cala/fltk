//
// "$Id$"
//
// Valuator header file for the Fast Light Tool Kit (FLTK).
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

#ifndef Fl_Valuator_H
#define Fl_Valuator_H

#ifndef Fl_Button_H
#include "Fl_Button.H"
#endif

// shared type() values for classes that work in both directions:
#define FL_VERTICAL		0
#define FL_HORIZONTAL		1

class Fl_Valuator_Style;

/** Fl_Valuator class controls a single floating-point value and provides a consistent 
 * interface to set the value, range, and step, and insures that callbacks are done the
 * same for every object.
 *
 * There are probably more of these classes in FLTK than any others:
 *   \image html valuators.gif
 *
 * In the above diagram each box surrounds an actual subclass. These are further 
 * differentiated by setting the type() of the widget to the symbolic value labeling 
 * the widget. The ones labelled "0" are the default versions with a type(0). For 
 * consistency the symbol \c FL_VERTICAL is defined as zero. 
 */
class FL_EXPORT Fl_Valuator : public Fl_Button {

  double value_;
  double previous_value_;
  double min, max; // truncates to this range *after* rounding
  double A; int B; // rounds to multiples of A/B, or no rounding if A is zero

protected:

  int horizontal() const {return type()&1;}
    /** Creates a new Fl_Valuator widget using the given position, size, and label string.
     * The default boxtype is \c FL_NO_BOX. */
  Fl_Valuator(int X, int Y, int W, int H, const char* Label);

  double previous_value() const {return previous_value_;}
  void handle_push() {previous_value_ = value_;}
  double softclamp(double);
  void handle_drag(double newvalue);
  void handle_release(); // use drag() value
  virtual void value_damage(); // cause damage() due to value() changing
  void set_value(double v) {value_ = v;}

public:


    /** Sets the minimum (\c a) and maximum (\c b) values for the valuator widget. */
  void bounds(double a, double b) {min=a; max=b;}
    /** Gets the minimum value for the valuator. */
  double minimum() const {return min;}
    /** Sets the minimum value for the valuator. */
  void minimum(double a) {min = a;}
    /** Gets the maximum value for the valuator. */
  double maximum() const {return max;}
    /** Sets the maximum value for the valuator. */
  void maximum(double a) {max = a;}
    /** Sets the minimum and maximum values for the valuator. When the user manipulates 
     * the widget, the value is limited to this range. This clamping is done after rounding
     * to the step value (this makes a difference if the range is not a multiple of the step).
     * 
     * The minimum may be greater than the maximum. This has the effect of "reversing" the
     * object so the larger values are in the opposite direction. This also switches which 
     * end of the filled sliders is filled.
     * 
     * Some widgets consider this a "soft" range. This means they will stop at the range, 
     * but if the user releases and grabs the control again and tries to move it further, 
     * it is allowed.
     *
     * The range may affect the display. You must redraw() the widget after changing 
     * the range. */
  void range(double a, double b) {min = a; max = b;}
  void step(int a) {A = a; B = 1;}
    /** Sets the step value. For precision the step is stored as the ratio of two 
     * integers, <i>A/B</i>. You can set these integers directly. Currently setting a
     * floating point value sets the nearest A/1 or 1/B value possible. */
  void step(double a, int b) {A = a; B = b;}
    /** Sets the step value. As the user moves the mouse the value is rounded to the nearest
     * multiple of the step value. This is done beforeclamping it to the range. For most 
     * widgets the default step is zero. */
  void step(double s);
    /** Gets step value. */
  double step() const {return A/B;}
    /** Sets the step value to 1/10<sup>digits</sup>. */
  void precision(int digits);

    /** Gets the current value. */
  double value() const {return value_;}
    /** Sets the current value. The new value is not clamped or otherwise changed before
     * storing it. Use clamp() or round() to modify the value before calling value(). 
     * The widget is redrawn if the new value is different than the current one. The 
     * initial value is zero.  */
  int value(double);

    /** Format the passed value to show enough digits so that for the current step value. 
     * If the step has been set to zero then it does a <tt>%g</tt> format. The characters are 
     * written into the passed buffer. */
  virtual int format(char*);
    /** Round the passed value to the nearest step increment. Does nothing if step is zero. */
  double round(double value); 
    /** Clamps the passed value to the valuator range. */
  double clamp(double value);
    /** Adds \c n times the \c step value to the passed value. If \c step was set to zero 
     * it uses <tt>fabs(maximum() - minimum()) / 100</tt>. */
  double increment(double my_value, int n);
};

#endif

//
// End of "$Id$".
//
