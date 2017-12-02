/*    @file fractal.cpp  
      @author Paul Talaga
      @date Dec 1, 2017

			@description Creates a BW Newton fractal, using the MyComplex
			  complex number manipulation class from CSCI 156.
			  Will save a fractal.png file to the current folder.
			  
			  To compile:  g++ fractal.cpp MyComplex.cpp -O3 -o fractal
*/

#include <iostream>
#include <string>
#include <vector>
#include "lodepng.cpp"
#include "MyComplex.h"

// https://en.wikipedia.org/wiki/Newton's_method
void doNewton(MyComplex &point, unsigned &itter, unsigned max_itter){
  MyComplex old(1000,1000);
  itter = 0;
  while(point.dist2(old) > 0.001 && itter < max_itter){
    old = point;
    point = point - (point * point * point - MyComplex(1,0)) /
    (MyComplex(3,0) * point * point);
    itter++;
  }
}

int main(){
  unsigned width = 1024;
  unsigned height = 768;
  string filename = "fractal.png";
  
  vector<unsigned char> image(width * height * 4);
  
  double xmin = -10.0;
  double xmax = 10.0;
  double ymin = -10.0;
  double ymax = 10.0;
  
  for(unsigned x = 0; x < width; x++){
    for(unsigned y = 0; y < height; y++){
      MyComplex start((double)x/width * (xmax - xmin) +xmin,
                      ymax - (double)y/height * (ymax - ymin));
      unsigned itter = 0;
      doNewton(start, itter, 25);  // 25 is chosen since 25 * 10 = 250, 
                      // which is just less than 256
      //cout << "Itter: " << itter << " ";  // Useful in finding roots
      //cout << "Start: " << start.getAsString() << endl;
      image[(y * width + x) * 4 + 0] = itter * 10;   // Red value  (char has max value 255)
      image[(y * width + x) * 4 + 1] = itter * 10;   // Green value
      image[(y * width + x) * 4 + 2] = itter * 10; // Blue value
      image[(y * width + x) * 4 + 3] = 255;
    }
  }
  
  cout << "Done rendering...\nSaving.. " << filename << endl;
  
  unsigned error = lodepng::encode(filename.c_str(), image, width, height);
    
  if(error)cout << "Error! " << lodepng_error_text(error) << endl;
  
  cout << "File written.  DONE" << endl;
  
  return 0;
}
