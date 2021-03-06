//
// "$Id$"
//
// Box drawing code for the Fast Light Tool Kit (FLTK).
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

// Box drawing code for the common box types and the table of
// boxtypes.  Other box types are in seperate files so they are not
// linked in if not used.

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include <config.h>

// #include <FL/Fl_Symbol.H>

////////////////////////////////////////////////////////////////

static uchar active_ramp[24] = {
  FL_GRAY_RAMP+0, FL_GRAY_RAMP+1, FL_GRAY_RAMP+2, FL_GRAY_RAMP+3,
  FL_GRAY_RAMP+4, FL_GRAY_RAMP+5, FL_GRAY_RAMP+6, FL_GRAY_RAMP+7,
  FL_GRAY_RAMP+8, FL_GRAY_RAMP+9, FL_GRAY_RAMP+10,FL_GRAY_RAMP+11,
  FL_GRAY_RAMP+12,FL_GRAY_RAMP+13,FL_GRAY_RAMP+14,FL_GRAY_RAMP+15,
  FL_GRAY_RAMP+16,FL_GRAY_RAMP+17,FL_GRAY_RAMP+18,FL_GRAY_RAMP+19,
  FL_GRAY_RAMP+20,FL_GRAY_RAMP+21,FL_GRAY_RAMP+22,FL_GRAY_RAMP+23};
static uchar inactive_ramp[24] = {
  43, 43, 44, 44,
  44, 45, 45, 46,
  46, 46, 47, 47,
  48, 48, 48, 49,
  49, 49, 50, 50,
  51, 51, 52, 52};


int Fl_Widget::draw_box_flags_ = ~0;

void Fl_Widget::clear_draw_box_flag(int f){ draw_box_flags_ &= ~f;}
void Fl_Widget::reset_draw_box_flag(int f){ draw_box_flags_ |= f;}

int Fl::draw_box_active() { return Fl_Widget::draw_box_flags() & 1; }

int Fl_Widget::draw_box_flags() { return draw_box_flags_; }

uchar *fl_gray_ramp() {return ((Fl_Widget::DRAW_BOX_ACTIVE & Fl_Widget::draw_box_flags())?active_ramp:inactive_ramp)-'A';}

void fl_frame(const char* s, int x, int y, int w, int h) {
  uchar *g = fl_gray_ramp();
  if (h > 0 && w > 0) for (;*s;) {
    // draw top line:
    fl_color(g[*s++]);
    fl_xyline(x, y, x+w-1);
    y++; if (--h <= 0) break;
    // draw left line:
    fl_color(g[*s++]);
    fl_yxline(x, y+h-1, y);
    x++; if (--w <= 0) break;
    // draw bottom line:
    fl_color(g[*s++]);
    fl_xyline(x, y+h-1, x+w-1);
    if (--h <= 0) break;
    // draw right line:
    fl_color(g[*s++]);
    fl_yxline(x+w-1, y+h-1, y);
    if (--w <= 0) break;
  }
}

void fl_frame2(const char* s, int x, int y, int w, int h) {
  uchar *g = fl_gray_ramp();
  if (h > 0 && w > 0) for (;*s;) {
    // draw bottom line:
    fl_color(g[*s++]);
    fl_xyline(x, y+h-1, x+w-1);
    if (--h <= 0) break;
    // draw right line:
    fl_color(g[*s++]);
    fl_yxline(x+w-1, y+h-1, y);
    if (--w <= 0) break;
    // draw top line:
    fl_color(g[*s++]);
    fl_xyline(x, y, x+w-1);
    y++; if (--h <= 0) break;
    // draw left line:
    fl_color(g[*s++]);
    fl_yxline(x, y+h-1, y);
    x++; if (--w <= 0) break;
  }
}

void fl_no_box(int, int, int, int, Fl_Color) {}

void fl_thin_down_frame(int x, int y, int w, int h, Fl_Color) {
  fl_frame2("WWHH",x,y,w,h);
}

void fl_thin_down_box(int x, int y, int w, int h, Fl_Color c) {
  fl_thin_down_frame(x,y,w,h,c);
  if(!c) return;
  fl_color(Fl::draw_box_active() ? c : fl_inactive(c));
  fl_rectf(x+1, y+1, w-2, h-2);
}

void fl_thin_up_frame(int x, int y, int w, int h, Fl_Color) {
  fl_frame2("HHWW",x,y,w,h);
}

void fl_thin_up_box(int x, int y, int w, int h, Fl_Color c) {
  fl_thin_up_frame(x,y,w,h,c);
  if(!c) return;
  fl_color(Fl::draw_box_active() ? c : fl_inactive(c));
  fl_rectf(x+1, y+1, w-2, h-2);
}

void fl_up_frame(int x, int y, int w, int h, Fl_Color) {
#if BORDER_WIDTH == 1
  fl_frame2("HHWW",x,y,w,h);
#else
#if BORDER_WIDTH == 2
  fl_frame2("AAWWMMTT",x,y,w,h);
#else
  fl_frame("AAAAWWJJUTNN",x,y,w,h);
#endif
#endif
}

#define D1 BORDER_WIDTH
#define D2 (BORDER_WIDTH+BORDER_WIDTH)

void fl_up_box(int x, int y, int w, int h, Fl_Color c) {
  fl_up_frame(x,y,w,h,c);
  if(!c) return;
  fl_color(Fl::draw_box_active() ? c : fl_inactive(c));
  fl_rectf(x+D1, y+D1, w-D2, h-D2);
}

void fl_down_frame(int x, int y, int w, int h, Fl_Color) {
#if BORDER_WIDTH == 1
  fl_frame2("WWHH",x,y,w,h);
#else
#if BORDER_WIDTH == 2
  fl_frame2("WWMMPPAA",x,y,w,h);
#else
  fl_frame("NNTUJJWWAAAA",x,y,w,h);
#endif
#endif
}

void fl_down_box(int x, int y, int w, int h, Fl_Color c) {
  fl_down_frame(x,y,w,h,c);
  if(!c) return;
  fl_color(c); fl_rectf(x+D1, y+D1, w-D2, h-D2);
}

void fl_engraved_frame(int x, int y, int w, int h, Fl_Color) {
  fl_frame("HHWWWWHH",x,y,w,h);
}

void fl_engraved_box(int x, int y, int w, int h, Fl_Color c) {
  fl_engraved_frame(x,y,w,h,c);
  if(!c)return;
  fl_color(Fl::draw_box_active() ? c : fl_inactive(c));
  fl_rectf(x+2, y+2, w-4, h-4);
}

void fl_embossed_frame(int x, int y, int w, int h, Fl_Color) {
  fl_frame("WWHHHHWW",x,y,w,h);
}

void fl_embossed_box(int x, int y, int w, int h, Fl_Color c) {
  fl_embossed_frame(x,y,w,h,c);
  if(!c) return;
  fl_color(Fl::draw_box_active() ? c : fl_inactive(c));
  fl_rectf(x+2, y+2, w-4, h-4);
}

void fl_rectbound(int x, int y, int w, int h, Fl_Color bgcolor) {
  fl_color(Fl::draw_box_active() ? FL_BLACK : fl_inactive(FL_BLACK));
  fl_rect(x, y, w, h);
  if(!bgcolor) return;
  fl_color(Fl::draw_box_active() ? bgcolor : fl_inactive(bgcolor));
  fl_rectf(x+1, y+1, w-2, h-2);
}
#define fl_border_box fl_rectbound

void fl_border_frame(int x, int y, int w, int h, Fl_Color c) {
  fl_color(Fl::draw_box_active() ? c : fl_inactive(c));
  fl_rect(x, y, w, h);
}



FL_EXPORT void fl_return_arrow(int x, int y, int w, int h, Fl_Color c) {
  int size = w; if (h<size) size = h;
  int d = (size+2)/4; if (d<3) d = 3;
  int t = (size+9)/12; if (t<1) t = 1;
  int x0 = x+(w-2*d-2*t-1)/2;
  int x1 = x0+d;
  int y0 = y+h/2;
  fl_color(FL_LIGHT3);
  fl_line(x0, y0, x1, y0+d);
  fl_yxline(x1, y0+d, y0+t, x1+d+2*t, y0-d);
  fl_yxline(x1, y0-t, y0-d);
  fl_color(fl_gray_ramp(0));
  fl_line(x0, y0, x1, y0-d);
  fl_color(FL_DARK3);
  fl_xyline(x1+1, y0-t, x1+d, y0-d, x1+d+2*t);
}





////////////////////////////////////////////////////////////////
/*
static struct {
  Fl_Box_Draw_F *f;
  uchar dx, dy, dw, dh;
  int set; //set is now used also to describe down_box
} fl_box_table[256] = {
// must match list in Enumerations.H!!!
  {fl_no_box,		0,0,0,0,1},		
  {fl_rectf,		0,0,0,0,1}, // FL_FLAT_BOX
  {fl_up_box,		D1,D1,D2,D2,1},
  {fl_down_box,		D1,D1,D2,D2,1},
  {fl_up_frame,		D1,D1,D2,D2,1},
  {fl_down_frame,	D1,D1,D2,D2,1},
  {fl_thin_up_box,	1,1,2,2,1},
  {fl_thin_down_box,	1,1,2,2,1},
  {fl_thin_up_frame,	1,1,2,2,1},
  {fl_thin_down_frame,	1,1,2,2,1},
  {fl_engraved_box,	2,2,4,4,1},
  {fl_embossed_box,	2,2,4,4,1},
  {fl_engraved_frame,	2,2,4,4,1},
  {fl_embossed_frame,	2,2,4,4,1},
  {fl_border_box,	1,1,2,2,1},
  {fl_border_box,	1,1,5,5,0}, // _FL_SHADOW_BOX,
  {fl_border_frame,	1,1,2,2,1},
  {fl_border_frame,	1,1,5,5,0}, // _FL_SHADOW_FRAME,
  {fl_border_box,	1,1,2,2,0}, // _FL_ROUNDED_BOX,
  {fl_border_box,	1,1,2,2,0}, // _FL_RSHADOW_BOX,
  {fl_border_frame,	1,1,2,2,0}, // _FL_ROUNDED_FRAME
  {fl_rectf,		0,0,0,0,0}, // _FL_RFLAT_BOX,
  {fl_up_box,		3,3,6,6,0}, // _FL_ROUND_UP_BOX
  {fl_down_box,		3,3,6,6,0}, // _FL_ROUND_DOWN_BOX,
  {fl_up_box,		0,0,0,0,0}, // _FL_DIAMOND_UP_BOX
  {fl_down_box,		0,0,0,0,0}, // _FL_DIAMOND_DOWN_BOX
  {fl_border_box,	1,1,2,2,0}, // _FL_OVAL_BOX,
  {fl_border_box,	1,1,2,2,0}, // _FL_OVAL_SHADOW_BOX,
  {fl_border_frame,	1,1,2,2,0}, // _FL_OVAL_FRAME
  {fl_rectf,		0,0,0,0,0}, // _FL_OVAL_FLAT_BOX,
  {fl_up_box,		4,4,8,8,0}, // _FL_PLASTIC_UP_BOX,
  {fl_down_box,		2,2,4,4,0}, // _FL_PLASTIC_DOWN_BOX,
  {fl_up_frame,		2,2,4,4,0}, // _FL_PLASTIC_UP_FRAME,
  {fl_down_frame,	2,2,4,4,0}, // _FL_PLASTIC_DOWN_FRAME,
  {fl_up_box,		2,2,4,4,0}, // _FL_PLASTIC_THIN_UP_BOX,
  {fl_down_box,		2,2,4,4,0}, // _FL_PLASTIC_THIN_DOWN_BOX,
  {fl_up_box,		3,3,6,6,0}, // FL_FREE_BOX+0
  {fl_down_box,		3,3,6,6,0}, // FL_FREE_BOX+1
  {fl_up_box,		3,3,6,6,0}, // FL_FREE_BOX+2
  {fl_down_box,		3,3,6,6,0}, // FL_FREE_BOX+3
  {fl_up_box,		3,3,6,6,0}, // FL_FREE_BOX+4
  {fl_down_box,		3,3,6,6,0}, // FL_FREE_BOX+5
  {fl_up_box,		3,3,6,6,0}, // FL_FREE_BOX+6
  {fl_down_box,		3,3,6,6,0}, // FL_FREE_BOX+7
};

*/

FL_EXPORT Fl_Symbol fl_symbol_table[256]={ 
  Fl_Symbol(fl_no_box,		0,0,0,0),		
  Fl_Symbol(fl_rectf,		0,0,0,0), // FL_FLAT_BOX
  Fl_Symbol(fl_up_box,		D1,D1,D2,D2),
  Fl_Symbol(fl_down_box,		D1,D1,D2,D2),
  Fl_Symbol(fl_up_frame,		D1,D1,D2,D2),
  Fl_Symbol(fl_down_frame,	D1,D1,D2,D2),
  Fl_Symbol(fl_thin_up_box,	1,1,2,2),
  Fl_Symbol(fl_thin_down_box,	1,1,2,2),
  Fl_Symbol(fl_thin_up_frame,	1,1,2,2),
  Fl_Symbol(fl_thin_down_frame,	1,1,2,2),
  Fl_Symbol(fl_engraved_box,	2,2,4,4),
  Fl_Symbol(fl_embossed_box,	2,2,4,4),
  Fl_Symbol(fl_engraved_frame,	2,2,4,4),
  Fl_Symbol(fl_embossed_frame,	2,2,4,4),
  Fl_Symbol(fl_border_box,	1,1,2,2),
  Fl_Symbol(fl_border_box,	1,1,2,2), // _FL_SHADOW_BOX,
  Fl_Symbol(fl_border_frame,	1,1,2,2),
  Fl_Symbol(fl_border_frame,	1,1,2,2), // _FL_SHADOW_FRAME,
  Fl_Symbol(fl_border_box,	1,1,2,2), // _FL_ROUNDED_BOX,
  Fl_Symbol(fl_border_box,	1,1,2,2), // _FL_RSHADOW_BOX,
  Fl_Symbol(fl_border_frame,	1,1,2,2), // _FL_ROUNDED_FRAME
  Fl_Symbol(fl_rectf,		0,0,0,0), // _FL_RFLAT_BOX,
  Fl_Symbol(fl_up_box,		3,3,6,6), // _FL_ROUND_UP_BOX
  Fl_Symbol(fl_down_box,		3,3,6,6), // _FL_ROUND_DOWN_BOX,
  Fl_Symbol(fl_up_box,		0,0,0,0), // _FL_DIAMOND_UP_BOX
  Fl_Symbol(fl_down_box,		0,0,0,0), // _FL_DIAMOND_DOWN_BOX
  Fl_Symbol(fl_border_box,	1,1,2,2), // _FL_OVAL_BOX,
  Fl_Symbol(fl_border_box,	1,1,2,2), // _FL_OVAL_SHADOW_BOX,
  Fl_Symbol(fl_border_frame,	1,1,2,2), // _FL_OVAL_FRAME
  Fl_Symbol(fl_rectf,		0,0,0,0), // _FL_OVAL_FLAT_BOX,
  Fl_Symbol(fl_up_box,		4,4,8,8), // _FL_PLASTIC_UP_BOX,
  Fl_Symbol(fl_down_box,		2,2,4,4), // _FL_PLASTIC_DOWN_BOX,
  Fl_Symbol(fl_up_frame,		2,2,4,4), // _FL_PLASTIC_UP_FRAME,
  Fl_Symbol(fl_down_frame,	2,2,4,4), // _FL_PLASTIC_DOWN_FRAME,
  Fl_Symbol(fl_up_box,		2,2,4,4), // _FL_PLASTIC_THIN_UP_BOX,
  Fl_Symbol(fl_down_box,	2,2,4,4), // _FL_PLASTIC_THIN_DOWN_BOX,
  Fl_Symbol(fl_up_box,		2,2,4,4), // _FL_PLASTIC_ROUND_UP_BOX,
  Fl_Symbol(fl_down_box,	2,2,4,4), // _FL_PLASTIC_ROUND_DOWN_BOX,



  Fl_Symbol(fl_up_box,		3,3,6,6), // FL_FREE_BOX+0
  Fl_Symbol(fl_down_box,		3,3,6,6), // FL_FREE_BOX+1
  Fl_Symbol(fl_up_box,		3,3,6,6), // FL_FREE_BOX+2
  Fl_Symbol(fl_down_box,		3,3,6,6), // FL_FREE_BOX+3
  Fl_Symbol(fl_up_box,		3,3,6,6), // FL_FREE_BOX+4
  Fl_Symbol(fl_down_box,		3,3,6,6), // FL_FREE_BOX+5
  Fl_Symbol(fl_up_box,		3,3,6,6), // FL_FREE_BOX+6
  Fl_Symbol(fl_down_box,		3,3,6,6), // FL_FREE_BOX+7
  };

static uchar fl_table_set[256] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


Fl_Boxtype  FL_NO_BOX = 0;	
Fl_Boxtype  FL_FLAT_BOX = fl_symbol_table +1;
Fl_Boxtype  FL_UP_BOX = fl_symbol_table + 2;
Fl_Boxtype  FL_DOWN_BOX = fl_symbol_table + 3;
Fl_Boxtype  FL_UP_FRAME = fl_symbol_table + 4;
Fl_Boxtype  FL_DOWN_FRAME = fl_symbol_table + 5;
Fl_Boxtype  FL_THIN_UP_BOX = fl_symbol_table + 6;
Fl_Boxtype  FL_THIN_DOWN_BOX = fl_symbol_table + 7;
Fl_Boxtype  FL_THIN_UP_FRAME = fl_symbol_table + 8;
Fl_Boxtype  FL_THIN_DOWN_FRAME = fl_symbol_table + 9;
Fl_Boxtype  FL_ENGRAVED_BOX = fl_symbol_table + 10;
Fl_Boxtype  FL_EMBOSSED_BOX = fl_symbol_table + 11;
Fl_Boxtype  FL_ENGRAVED_FRAME = fl_symbol_table + 12;
Fl_Boxtype  FL_EMBOSSED_FRAME = fl_symbol_table + 13;
Fl_Boxtype  FL_BORDER_BOX = fl_symbol_table + 14;
Fl_Boxtype  _FL_SHADOW_BOX = fl_symbol_table + 15;
Fl_Boxtype  FL_BORDER_FRAME = fl_symbol_table + 16;
Fl_Boxtype  _FL_SHADOW_FRAME = fl_symbol_table + 17;
Fl_Boxtype  _FL_ROUNDED_BOX = fl_symbol_table + 18;
Fl_Boxtype  _FL_RSHADOW_BOX = fl_symbol_table + 19;
Fl_Boxtype  _FL_ROUNDED_FRAME = fl_symbol_table + 20;
Fl_Boxtype  _FL_RFLAT_BOX = fl_symbol_table + 21;
Fl_Boxtype  _FL_ROUND_UP_BOX = fl_symbol_table + 22;
Fl_Boxtype  _FL_ROUND_DOWN_BOX = fl_symbol_table + 23;
Fl_Boxtype  _FL_DIAMOND_UP_BOX = fl_symbol_table + 24;
Fl_Boxtype  _FL_DIAMOND_DOWN_BOX = fl_symbol_table + 25;
Fl_Boxtype  _FL_OVAL_BOX = fl_symbol_table + 26;
Fl_Boxtype  _FL_OSHADOW_BOX = fl_symbol_table + 27;
Fl_Boxtype  _FL_OVAL_FRAME = fl_symbol_table + 28;
Fl_Boxtype  _FL_OFLAT_BOX = fl_symbol_table + 29;
Fl_Boxtype  _FL_PLASTIC_UP_BOX = fl_symbol_table + 30;
Fl_Boxtype  _FL_PLASTIC_DOWN_BOX = fl_symbol_table + 31;
Fl_Boxtype  _FL_PLASTIC_UP_FRAME = fl_symbol_table + 32;
Fl_Boxtype  _FL_PLASTIC_DOWN_FRAME = fl_symbol_table + 33;
Fl_Boxtype  _FL_PLASTIC_THIN_UP_BOX = fl_symbol_table + 34;
Fl_Boxtype  _FL_PLASTIC_THIN_DOWN_BOX = fl_symbol_table + 35;
Fl_Boxtype  _FL_PLASTIC_ROUND_UP_BOX = fl_symbol_table + 36;
Fl_Boxtype  _FL_PLASTIC_ROUND_DOWN_BOX = fl_symbol_table + 37;

Fl_Boxtype  FL_FREE_BOXTYPE = fl_symbol_table + 38;

Fl_Symbol FL_RETURN_ARROW_(fl_return_arrow, 0,0,0,0); // FL_RETURN_ARROW
Fl_Boxtype FL_RETURN_ARROW = &FL_RETURN_ARROW_;




int Fl::box_dx(Fl_Boxtype t) {if (t) return t->dx(); else return 0;}
int Fl::box_dy(Fl_Boxtype t) {if (t) return t->dy(); else return 0;}
int Fl::box_dw(Fl_Boxtype t) {if (t) return t->dw(); else return 0;}
int Fl::box_dh(Fl_Boxtype t) {if (t) return t->dh(); else return 0;}



void fl_internal_boxtype(Fl_Boxtype t, Fl_Box_Draw_F* f) {
  if(! t) return;
  int i = Fl::box_index(t);
  if(i && !fl_table_set[i]) {
    fl_table_set[i] = 1;
    t->set(f,t->dx(), t->dy(), t->dw(), t->dh());
  }
}


Fl_Symbol * Fl_Symbol::down() {
  if (down_) return down_;
  unsigned index = this - fl_symbol_table;

  if(index >=0 && index < 256){
    index |= 1;
    return fl_symbol_table + index;
  }else
    return this;
}


int Fl::box_index(Fl_Boxtype t){
  if(!t) return 0;

  int index = t - fl_symbol_table;
  if(index >=0 && index < 256)
    return index;
  return 0;

}

Fl_Boxtype Fl::box(int index){ 
  if(index<=0 || index >256)  return 0;
  return fl_symbol_table + index;
}





Fl_Box_Draw_F *Fl::get_boxtype(Fl_Boxtype t) {
  if(t) return t->function(); else return fl_no_box;
}


Fl_Boxtype fl_down(Fl_Boxtype b) {
  if(b)
    return b->down();
  else return FL_FLAT_BOX;
}



//static Fl_Boxtype last_free_boxtype = (Fl_Boxtype)0xFF; //first possible free place, it speeds up searching
//static Fl_Boxtype last_free_double_boxtype = (Fl_Boxtype)0xFE;  

void Fl::set_boxtype(Fl_Boxtype t, Fl_Box_Draw_F* f, uchar a, uchar b, uchar c, uchar d) {
  if(! t) return;
  t->set(f, a, b, c, d);
  int i = Fl::box_index(t);
  if(i) fl_table_set[i] = 1;
}

//Fl_Boxtype Fl::add_boxtype(Fl_Box_Draw_F* f, uchar a, uchar b, uchar c, uchar d){
//  return add_boxtype(f, a, b, c, d, (Fl_Boxtype)(-1));
//};



void Fl::set_boxtype(Fl_Symbol * t, Fl_Symbol * f) {
  if(! t)return;
  t->set(f);
}





void fl_draw_box(Fl_Symbol * t, int x, int y, int w, int h, Fl_Color c) {
  if(t) t->draw(x,y,w,h,c);
}


//extern Fl_Widget *fl_boxcheat; // hack set by Fl_Window.cxx


void Fl_Widget::draw_box() const {
  Fl_Boxtype t = box();
  if (!t) return;
//   if (this == fl_boxcheat) {
//     fl_boxcheat = 0;
//     if (t == FL_FLAT_BOX) return;
//     t += 2; // convert box to frame
//   }
  draw_box(t, x_, y_, w_, h_, color());
}



void Fl_Widget::draw_box(Fl_Boxtype b, Fl_Color c) const {
  draw_box(b, x_, y_, w_, h_, c);
}


void Fl_Widget::draw_box_(Fl_Boxtype b, int X, int Y, int W, int H, Fl_Color c)
const {

  if(b){
    if(!active_r())
      draw_box_flags_ &= ~1;
    b->draw(X, Y, W, H, c);
  }
  draw_box_flags_ = ~0;
}




//
// End of "$Id$".
//
