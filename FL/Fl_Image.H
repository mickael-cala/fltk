//
// "$Id$"
//
// Image header file for the Fast Light Tool Kit (FLTK).
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

#ifndef Fl_Image_H
#  define Fl_Image_H

#  include "Enumerations.H"

class Fl_Widget;
struct Fl_Menu_Item;
struct Fl_Label;


class Fl_Image;
class Fl_Device;

/** Fl_Image_Cache is a base class for all image caches.
 *
 * If an image class requires a cache data, a new class he cache data should be derived 
 * from this class. New class should add additional member for actual cache data. 
 */
class Fl_Image_Cache{

  friend class Fl_Device;
  Fl_Image_Cache * prev;   // for list of caches in device
  Fl_Image_Cache * next;   // for list of caches in device
  Fl_Image * image;
  Fl_Device * device;
  
protected:
  /** Protected constructor adds the cache to both image and the device cache list 
  * and derived class does not need to care about theses */
  Fl_Image_Cache(Fl_Image * im, Fl_Device * dev);
public:
  /** Fl_Image::uncache() method just calls this destructor.
  * The destructor removes also its cache pointers from image and device cache list */ 
  virtual ~Fl_Image_Cache();
};
  
   


/** Fl_Image is the base class used for caching and drawing all kinds of images in FLTK. 
 * This class keeps track of common image data such as the pixels, colormap, width, height, 
 * and depth. Virtual methods are used to provide type-specific image handling.
 *
 * Since the Fl_Image class does not support image drawing by itself, calling the
 * draw() method results in a box with an X in it being drawn instead. 
 */
class FL_EXPORT Fl_Image {
  int w_, h_, d_, ld_, count_;
  const char * const *data_;

  // Forbid use of copy contructor and assign operator
  Fl_Image & operator=(const Fl_Image &);
  Fl_Image(const Fl_Image &);

  Fl_Image_Cache * cache_; // now private because Fl_Image_Cache constructor/destructor cares about this pointer
  
  protected:
  friend class Fl_Image_Cache;
  friend class Fl_Device;
  
    /** This protected method can be used for direct access of image cache by devices in certain situations  */
  Fl_Image_Cache * cache() {return cache_;};
    /** This protected method can be used for direct setting of image cache by some devices. */
  void cache(Fl_Image_Cache * cache) {cache_ = cache;};

    /** This protected method sets the image width. */
  void w(int W) {w_ = W;}
    /** This protected method sets the image height. */
  void h(int H) {h_ = H;}
    /** This form is a protected method that sets the current image depth. */
  void d(int D) {d_ = D;}
    /** This protected method sets the current line data size in bytes. */
  void ld(int LD) {ld_ = LD;}
    /** This is a protected method that sets the current array pointer and count of pointers 
     * in the array. */
  void data(const char * const *p, int c) {data_ = p; count_ = c;}
    /** The protected method draw_empty() draws a box with an X in it. It can be used to
     * draw any image that lacks image data. */
  void draw_empty(int X, int Y);

  static void labeltype(const Fl_Label *lo, int lx, int ly, int lw, int lh, Fl_Align la);
  static void measure(const Fl_Label *lo, int &lw, int &lh);

  public:

    /** Returns the image width in pixels. */
  int w() const {return w_;}
    /** Returns the image height in pixels. */
  int h() const {return h_;}
    /** This form of the d() method returns the current image depth. The return value 
     * will be 0 for bitmaps, 1 for pixmaps, and 1 to 4 for color images. */
  int d() const {return d_;}
    /** Returns the current line data size in bytes. Line data is extra data that 
     * is included after each line of color image data and is normally not present. */
  int ld() const {return ld_;}
    /** The count() method returns the number of data values associated with the image.
     * The value will be 0 for images with no associated data, 1 for bitmap and color 
     * images, and greater than 2 for pixmap images. */
  int count() const {return count_;}
    /** This form of the data() method returns a pointer to the current image data array. 
     * Use the count() method to find the size of the data array. */
  const char * const *data() const {return data_;}
  

    /** The constructor creates an empty image with the specified width, height, and depth. 
     * The width and height are in pixels. The depth is 0 for bitmaps, 1 for pixmap (colormap) 
     * images, and 1 to 4 for color images. */
  Fl_Image(int W, int H, int D) {w_ = W; h_ = H; d_ = D; ld_ = 0; count_ = 0; data_ = 0; cache_ = 0;}
    /** The destructor is a virtual method that frees all memory used by the image. */
  virtual ~Fl_Image();
    /** The copy() method creates a copy of the specified image. The image is resized to
     * the specified size. */
  virtual Fl_Image *copy(int W, int H);
    /** The copy() method creates a copy of the specified image. If the width and height 
     * are provided, the image is resized to the specified size. */
  Fl_Image *copy() { return copy(w(), h()); }
    /** The color_average() method averages the colors in the image with the FLTK color 
     * value c. The i argument specifies the amount of the original image to combine with
     * the color, so a value of 1.0 results in no color blend, and a value of 0.0 results 
     * in a constant image of the specified color. The original image data is not altered 
     * by this method. */
  virtual void color_average(Fl_Color c, float i);
    /** The inactive() method calls color_average(FL_GRAY, 0.33f) to produce an image that
     * appears grayed out. This method does not alter the original image data. */
  void inactive() { color_average(FL_GRAY, .33f); }
    /** The desaturate() method converts an image to grayscale. If the image contains an
     * alpha channel (depth = 4), the alpha channel is preserved. This method does not alter
     * the original image data. */
  virtual void desaturate();
    /** \deprecated The label() methods are an obsolete way to set the image attribute of 
     * a widget or menu item. Use the image() or deimage() methods of the Fl_Widget and 
     * Fl_Menu_Item classes instead. */
  virtual void label(Fl_Widget*w);
  virtual void label(Fl_Menu_Item*m);
    /** The draw() methods draw the image. This form specifies a bounding box for the image, 
     * with the origin (upper-lefthand corner) of the image offset by the cx and cy arguments. */
  virtual void draw(int X, int Y, int W, int H, int cx=0, int cy=0);
    /** The draw() methods draw the image. This form specifies the upper-lefthand corner of 
     * the image. */
  void draw(int X, int Y) {draw(X, Y, w(), h(), 0, 0);}


    /** If the image has been cached for display, delete the cache data. This allows you to 
     * change the data used for the image and then redraw it without recreating an 
     * image object. */
     // TODO uncache does not need to be virtual any more... ?
  virtual void uncache(){delete cache_;}; 
};

/** The Fl_RGB_Image class supports caching and drawing of full-color images with 1 to 4 
 * channels of color information. Images with an even number of channels are assumed to
 * contain alpha information, which is used to blend the image with the contents 
 * of the screen. 
 */
class FL_EXPORT Fl_RGB_Image : public Fl_Image {
  public:
  const uchar *array;
  int alloc_array; // Non-zero if array was allocated

    /** The constructor creates a new image from the specified data. */
  Fl_RGB_Image(const uchar *bits, int W, int H, int D=3, int LD=0) :
    Fl_Image(W,H,D), array(bits), alloc_array(0){data((const char **)&array, 1); ld(LD);}
  virtual ~Fl_RGB_Image();
  virtual Fl_Image *copy(int W, int H);
  Fl_Image *copy() { return copy(w(), h()); }
  virtual void color_average(Fl_Color c, float i);
  virtual void desaturate();
  virtual void draw(int X, int Y, int W, int H, int cx=0, int cy=0);
  void draw(int X, int Y) {draw(X, Y, w(), h(), 0, 0);}
  virtual void label(Fl_Widget*w);
  virtual void label(Fl_Menu_Item*m);

};

#endif // !Fl_Image_H

//
// End of "$Id$".
//
