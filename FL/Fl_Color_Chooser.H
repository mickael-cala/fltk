//
// "$Id$"
//
// Color chooser header file for the Fast Light Tool Kit (FLTK).
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

// The color chooser object and the color chooser popup.  The popup
// is just a window containing a single color chooser and some boxes
// to indicate the current and cancelled color.

#ifndef Fl_Color_Chooser_H
#define Fl_Color_Chooser_H

#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Value_Input.H>

/**
 * \brief Support widget for the RGB color chooser
 */
class FL_EXPORT Flcc_HueBox : public Fl_Widget {
  int px, py;
protected:
  void draw();
  int handle_key(int);
public:
  int handle(int);
  Flcc_HueBox(int X, int Y, int W, int H) : Fl_Widget(X,Y,W,H) {
  px = py = 0;}
};

/**
 * \brief Support widget for the RGB color chooser
 */
class FL_EXPORT Flcc_ValueBox : public Fl_Widget {
  int py;
protected:
  void draw();
  int handle_key(int);
public:
  int handle(int);
  Flcc_ValueBox(int X, int Y, int W, int H) : Fl_Widget(X,Y,W,H) {
  py = 0;}
};

/**
 * \brief Support widget for the RGB color chooser
 */
class FL_EXPORT Flcc_Value_Input : public Fl_Value_Input {
public:
  int format(char*);
  Flcc_Value_Input(int X, int Y, int W, int H) : Fl_Value_Input(X,Y,W,H) {}
};

/** 
 * \brief RGB or YUV color chooser.
 *
 * The Fl_Color_Chooser widget provides a standard RGB color chooser. 
 * You can place any number of these into a panel of your own design. 
 * This widget contains the hue box, value slider, and rgb input fields 
 * from the above diagram (it does not have the color chips or the Cancel
 * or OK buttons). The callback is done every time the user changes the
 * rgb value. It is not done if they move the hue control in a way that 
 * produces the same rgb value, such as when saturation or value is zero. 
 */
class FL_EXPORT Fl_Color_Chooser : public Fl_Group {
  Flcc_HueBox huebox;
  Flcc_ValueBox valuebox;
  Fl_Choice choice;
  Flcc_Value_Input rvalue;
  Flcc_Value_Input gvalue;
  Flcc_Value_Input bvalue;
  Fl_Box resize_box;
  double hue_, saturation_, value_;
  double r_, g_, b_;
  void set_valuators();
  static void rgb_cb(Fl_Widget*, void*);
  static void mode_cb(Fl_Widget*, void*);
public:
  int mode() {return choice.value();}
    /** Return the current hue. 0 <= hue < 6. Zero is red, one is yellow, 
     * two is green, etc. This value is convienent for the internal 
     * calculations - some other systems consider hue to run from zero to 
     * one, or from 0 to 360.*/
  double hue() const {return hue_;}
    /** Returns the saturation. 0 <= saturation <= 1. */
  double saturation() const {return saturation_;}
    /** Returns the value/brightness. 0 <= value <= 1. */
  double value() const {return value_;}
    /** Returns the current red value. 0 <= r <= 1. */
  double r() const {return r_;}
    /** Returns the current green value. 0 <= r <= 1. */
  double g() const {return g_;}
    /** Returns the current blue value. 0 <= r <= 1. */
  double b() const {return b_;}
    /** Set the hsv values. The passed values are clamped (or for hue, 
     * modulus 6 is used) to get legal values. Does not do the callback. */
  int hsv(double hue,double saturation,double value);
    /** Sets the current rgb color values. Does not do the callback. Does
     * not clamp (but out of range values will produce psychedelic effects
     * in the hue selector). */
  int rgb(double red,double green,double blue);
    /** This \a static method converts HSV colors to RGB colorspace. */
  static void hsv2rgb(double h, double s, double v,double &r,double &g,double &b);
    /** This \a static method converts RGB colors to HSV colorspace. */
  static void rgb2hsv(double r, double g, double b,double &h,double &s,double &v);
    /** Creates a new Fl_Color_Chooser widget using the given position, 
     * size, and label string. The recommended dimensions are 200x95. The
     * color is initialized to black. */
  Fl_Color_Chooser(int x,int y,int width,int height,const char *label = 0);
};

FL_EXPORT int fl_color_chooser(const char* name, double& r, double& g, double& b);
FL_EXPORT int fl_color_chooser(const char* name, uchar& r, uchar& g, uchar& b);

#endif

//
// End of "$Id$".
//
