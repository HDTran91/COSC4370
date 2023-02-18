#include <iostream>
#include "BMP.h"
#include <cmath>
#include <bits/stdc++.h>
using namespace std;

//function ellips1 to rasterize the ellip
void ellips1(int xs1,int ys1,int rx, int ry,BMP bmpNew)
{
    int x,y;
    float d1,d2,dx,dy;
    x = 0;                  // take start position as (0,ry)
    y = ry;                 // calculate decision parameter d1
    d1 = pow(ry,2) - (pow(rx,2) * ry) + (0.25 * pow(rx,2));
    dx = 2 * pow(ry,2) * x;
    dy = 2 * pow(rx,2) * y;

	// to let the point not be outside the image boundary
	// need to set the center point inside the boundary
	// center point in this case is (0,0), so when we rasterize it
	// it appears error "the point out of the boundaries", 
	// I move the point enough to fit in the image by setting it
	// up qual to radius x, y

	if((xs1 < rx) || (ys1 < ry) || xs1 < 0 || ys1 < 0){
		
			xs1 = rx ; ys1 =  ry;}
	

	  // region one
    do                       
    {
		// print points base on 4 way sysmetry
		cout << x + xs1 << " , " << y + ys1 << endl;
		cout << -x + xs1 << " , " << y + ys1 << endl;
		cout << x + xs1 << " , " << -y + ys1 << endl;
		cout << -x + xs1 << " , " << -y + ys1 << endl;

       // Plotting points based on 4 way sysmetry
        bmpNew.set_pixel(x + xs1, y + ys1, 255, 255, 255, 0);
        bmpNew.set_pixel(-x + xs1, y + ys1, 255, 255, 255, 0);
        bmpNew.set_pixel(x + xs1, -y + ys1, 255, 255, 255, 0);
        bmpNew.set_pixel(-x + xs1, -y + ys1, 255, 255, 255, 0);
        if(d1<0)
        {
            x++;
            dx = dx + (2 * (pow(ry,2)));
            d1 = d1 + dx +(pow(ry,2));
        }
        else
        {
            x++;
            y--;
            dx = dx + (2 * (pow(ry,2)));
            dy = dy - (2 * (pow(rx,2)));
            d1 = d1 + dx - dy + (pow(ry,2));
        }
    }while(dx<dy); 
    

	// region two
    do                       
    {
      
		cout << x + xs1 << " , " << y + ys1 << endl;
		cout << -x + xs1 << " , " << y + ys1 << endl;
		cout << x + xs1 << " , " << -y + ys1 << endl;
		cout << -x + xs1 << " , " << -y + ys1 << endl;

		// Plotting points based on 4 way sysmetry

        bmpNew.set_pixel(x + xs1, y + ys1, 255, 255, 255, 0);
        bmpNew.set_pixel(-x + xs1, y + ys1, 255, 255, 255, 0);
        bmpNew.set_pixel(x + xs1, -y + ys1, 255, 255, 255, 0);
        bmpNew.set_pixel(-x + xs1, -y + ys1, 255, 255, 255, 0);
        

		// checking and update the parameters
        if(d2>0)
        {
            x = x;
            y--;
            dy = dy - (2 * (pow(rx,2)));
            d2 = d2 - dy + pow(rx,2);
        }
        else
        {
            x++;
            y--;
            dy = dy - (2 * (pow(rx,2)));
            dx = dx + (2 * (pow(ry,2)));
            d2 = d2 +dx - dy + pow(rx,2);
  
        }
    }while(y>0);

	//out put file to output.bmp
    bmpNew.write("output.bmp");
}

// Driver code
int main()
{
	
	// create a new BMP with width 2000 and height 2000
    BMP bmpNew(2000,2000,true);
    bmpNew.fill_region(0, 0, 2000, 2000, 0, 0, 0, 0);
	//  call function ellips1 

    // center point(0,0) , Majoraxis Radius is 386 and Minoraxis Radius is 768 (based on function in the question)
	ellips1(0, 0, 386, 768, bmpNew);
   

	return 0;
}

