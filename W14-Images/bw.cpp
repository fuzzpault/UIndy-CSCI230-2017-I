/*                                                                                                                    
  Name: Paul Talaga
  Date: Nov 30, 2017
  Desc: Program to take a png file and convert it to grayscale

  To compile this, do: g++ bw.cpp
  To run: ./a.out 
  Loads 'Cat-PNG-2.png' and save the result to 'Cat-PNG-2-2.png'.
*/
#include <iostream>
#include <vector>
#include "lodepng.cpp"

using namespace std;

int main(int argc, char* argv[]){
    unsigned width, height;
    
    vector<unsigned char> image;
    
    unsigned error = lodepng::decode(image, width, height, "Cat-PNG-2.png");
    
    if(error)cout << "Error! " << lodepng_error_text(error) << endl;
    
    cout << "Done loading!" << endl;
    cout << "Width: " << width << endl;
    cout << "Height: " << height << endl;
    
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            float total = 0;
            // https://www.johndcook.com/blog/2009/08/24/algorithms-convert-color-grayscale/
            // 0.21 R + 0.72 G + 0.07 B
            total += image[(y * width + x) * 4 + 0] * 0.21;
            total += image[(y * width + x) * 4 + 1] * 0.72;
            total += image[(y * width + x) * 4 + 2] * 0.07;

            image[(y * width + x) * 4 + 0] = total;
            image[(y * width + x) * 4 + 1] = total;
            image[(y * width + x) * 4 + 2] = total;
            //image[(y * width + x) * 4 + 3] = 255; // Leave opacity alone.
        }
    }
    
    error = lodepng::encode("Cat-PNG-2-2.png", image, width, height);
    
    if(error)cout << "Error! " << lodepng_error_text(error) << endl;
    
    return 0;
}