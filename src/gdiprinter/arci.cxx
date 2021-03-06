//
// "$Id$"
//
// Arc WIN32 GDI printing  for the Fast Light Tool Kit (FLTK).
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
// Please report all bugs and problems to http://www.fltk.org/str.php
//

#include <FL/Fl_GDI_Printer.H>
#include <FL/Fl_Device.H>

#include "../win/Fl_Win_Display.H"
extern Fl_Win_Display fl_disp;


void Fl_GDI_Printer::arc(int x, int y, int w, int h, double a1, double a2){
  set_subpixel();
  fl_disp.arc((int)(max_res_ * (x)),(int)(max_res_ * (y)),(int)(max_res_*(w-1)), (int)(max_res_*(h-1)), a1, a2);
  set_normal();
};
void Fl_GDI_Printer::pie(int x, int y, int w, int h, double a1, double a2){
  set_subpixel();
  fl_disp.pie((int)(max_res_ * (x)),(int)(max_res_ * (y)),(int)(max_res_*(w-1)), (int)(max_res_*(h-1)), a1, a2);
  set_normal();
};

//
// End of "$Id$"
//

