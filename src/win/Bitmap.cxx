//
// "$Id$"
//
// Bitmap drawing routines for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2003 by Bill Spitzak and others.
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

#include "Fl_Win_Display.H"


// 'fl_create_bitmap()' - Create a 1-bit bitmap for drawing...

static Fl_Bitmask fl_create_bitmap(int w, int h, const uchar *data) {
  // we need to pad the lines out to words & swap the bits
  // in each byte.
  int w1 = (w+7)/8;
  int w2 = ((w+15)/16)*2;
  uchar* newarray = new uchar[w2*h];
  const uchar* src = data;
  uchar* dest = newarray;
  Fl_Bitmask id;
  static uchar reverse[16] =	// Bit reversal lookup table
  	      { 0x00, 0x88, 0x44, 0xcc, 0x22, 0xaa, 0x66, 0xee,
		0x11, 0x99, 0x55, 0xdd, 0x33, 0xbb, 0x77, 0xff };

  for (int y=0; y < h; y++) {
    for (int n = 0; n < w1; n++, src++)
      *dest++ = (uchar)((reverse[*src & 0x0f] & 0xf0) |
	                (reverse[(*src >> 4) & 0x0f] & 0x0f));
    dest += w2-w1;
  }

  id = CreateBitmap(w, h, 1, 1, newarray);

  delete[] newarray;

  return id;
}

// 'fl_create_bitmask()' - Create an N-bit bitmap for masking...
Fl_Bitmask fl_create_bitmask(int w, int h, const uchar *data) {
  // this won't work when the user changes display mode during run or
  // has two screens with differnet depths
  Fl_Bitmask id;
  static uchar hiNibble[16] =
  { 0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
    0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0 };
  static uchar loNibble[16] =
  { 0x00, 0x08, 0x04, 0x0c, 0x02, 0x0a, 0x06, 0x0e,
    0x01, 0x09, 0x05, 0x0d, 0x03, 0x0b, 0x07, 0x0f };
  int np  = GetDeviceCaps(fl_gc, PLANES);	//: was always one on sample machines
  int bpp = GetDeviceCaps(fl_gc, BITSPIXEL);//: 1,4,8,16,24,32 and more odd stuff?
  int Bpr = (bpp*w+7)/8;			//: bytes per row
  int pad = Bpr&1, w1 = (w+7)/8, shr = ((w-1)&7)+1;
  if (bpp==4) shr = (shr+1)/2;
  uchar *newarray = new uchar[(Bpr+pad)*h];
  uchar *dst = newarray;
  const uchar *src = data;

  for (int i=0; i<h; i++) {
    // This is slooow, but we do it only once per pixmap
    for (int j=w1; j>0; j--) {
      uchar b = *src++;
      if (bpp==1) {
        *dst++ = (uchar)( hiNibble[b&15] ) | ( loNibble[(b>>4)&15] );
      } else if (bpp==4) {
        for (int k=(j==1)?shr:4; k>0; k--) {
          *dst++ = (uchar)("\377\360\017\000"[b&3]);
          b = b >> 2;
        }
      } else {
        for (int k=(j==1)?shr:8; k>0; k--) {
          if (b&1) {
            *dst++=0;
	    if (bpp>8) *dst++=0;
            if (bpp>16) *dst++=0;
	    if (bpp>24) *dst++=0;
	  } else {
	    *dst++=0xff;
	    if (bpp>8) *dst++=0xff;
	    if (bpp>16) *dst++=0xff;
	    if (bpp>24) *dst++=0xff;
	  }

	  b = b >> 1;
        }
      }
    }

    dst += pad;
  }

  id = CreateBitmap(w, h, np, bpp, newarray);
  delete[] newarray;

  return id;
}

void fl_delete_bitmask(Fl_Bitmask bm) {
  DeleteObject((HGDIOBJ)bm);
}



class Fl_Win_Bitmap_Cache: public Fl_Image_Cache{
public:
  void * id; // for internal use
  Fl_Win_Bitmap_Cache(Fl_Image * im, Fl_Device * dev):Fl_Image_Cache(im,dev){};
  ~Fl_Win_Bitmap_Cache(){fl_delete_bitmask((Fl_Offscreen)(id));}
};



void Fl_Win_Display::draw(Fl_Bitmap * img, int X, int Y, int W, int H, int cx, int cy) {
    
  Fl_Win_Bitmap_Cache *cache = (Fl_Win_Bitmap_Cache *) check_image_cache(img);
  if (!cache){ // building one
    cache = new Fl_Win_Bitmap_Cache(img,this);
    cache->id = fl_create_bitmap(img->w(), img->h(), img->array);
  }

  HDC tempdc = CreateCompatibleDC(fl_gc);
  SelectObject(tempdc, (HGDIOBJ)(cache->id));
  //SelectObject(fl_gc, fl_brush());
  fl_brush();
  // secret bitblt code found in old MSWindows reference manual:
  BitBlt(fl_gc, X, Y, W, H, tempdc, cx, cy, 0xE20746L);
  DeleteDC(tempdc);
}



//
// End of "$Id$".
//
