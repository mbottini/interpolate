#include "interpolate.h"
#include <iostream>
#include  "FPToolkit.c"

/*
    FPToolkit.c : A simple set of graphical tools.
    FPToolkitDemo.c 
    Copyright (C) 2018  Ely

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License (version 3)
    as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/





/*

This code assumes an underlying X11 environment.

       Most freshly installed unbuntu environments do not have
       the X11 developr stuff they'll need to do graphics.
       To download X11 developer stuff, connect to the internet and 
       issue the following two commands.  Each will ask for your password
       and each will take a few minutes.  At some point it might even
       look like nothing is happening....be patient :
       
sudo  apt-get  install  libx11-dev     

sudo  apt-get  install  xorg-dev

*/




/*
If this file and the file, FPToolkit.c, are in the
same directory that you are trying to compile in,  
do the following :

cc  FPToolkitDemo.c   -lm  -lX11

*/

int main()
{
   int    swidth, sheight ;
   int num_points;
   std::cout << "Input the number of points you want to click. ";
   std::cin >> num_points;

   // must do this before you do 'almost' any other graphical tasks 
   swidth = 800 ;  sheight = 800 ;
   G_init_graphics (swidth,sheight) ;  // interactive graphics

   
   // clear the screen in a given color
   G_rgb (0.3, 0.3, 0.3) ; // dark gray
   G_clear () ;
   
   std::vector<myPoint> point_vec;

   G_rgb(1,0,0) ;

   // Await clicking of the points.
   for(int i = 0; i < num_points; i++) {
      myPoint next_point = G_wait_point();
      point_vec.push_back(next_point);
      G_fill_circle(next_point.x, next_point.y, 2);
   }

   // Generate the function from the interpolation of the points.
   std::function<double(double)> f = lagrange_interpolate(point_vec).eval();

   // And draw lines connecting each point in the function.
   // We draw lines in case the person picked some wonky-ass points
   // and would end up with a super steep pattern.
   G_rgb(0.0,1.0,0.0) ;
   myPoint prev_point = myPoint(0, f(0));
   myPoint next_point = myPoint(0, 0);
   for(int i = 1; i < swidth; i++) {
       next_point = myPoint(i, f(i));
       G_line(prev_point.x, prev_point.y, next_point.x, next_point.y);
       prev_point = next_point;
   }
   

   int key ;   
   key =  G_wait_key() ; // pause so user can see results

   G_save_image_to_file("demo.xwd") ;
}




