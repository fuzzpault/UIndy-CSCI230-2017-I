/*                                                                                                                    
  Name: Paul Talaga
  Date: Nov 30, 2017
  Desc: Program to half the size of the image.

  To compile this, do: g++ resize.cpp
  To run: ./a.out input.png output.png
  Which will open input.png, shrink, and save the result to output.png.
*/
#include <iostream>
#include <vector>
#include "lodepng.cpp"

using namespace std;

int main(int argc, char* argv[]){
    
    if(argc < 3){
        cout << "I need 2 parameters, an input png and output png" << endl;
        return 1;
    }
    unsigned width, height;
    
    vector<unsigned char> image;
    
    unsigned error = lodepng::decode(image, width, height, argv[1]);
    
    vector<unsigned char> out(width/2 * height/2 * 4);
    
    if(error)cout << "Error! " << lodepng_error_text(error) << endl;
    
    cout << "Done loading!" << endl;
    cout << "Width: " << width << endl;
    cout << "Height: " << height << endl;
    
    // Resizing code which does not average pixels, just picks every other
    // in both directions.
    /*for(int y = 0; y < height; y+=2){
        for(int x = 0; x < width; x+=2){
            out[(y/2 * width/2 + x/2) * 4 + 0] = image[(y * width + x) * 4 + 0];
            out[(y/2 * width/2 + x/2) * 4 + 1] = image[(y * width + x) * 4 + 1];
            out[(y/2 * width/2 + x/2) * 4 + 2] = image[(y * width + x) * 4 + 2];
            out[(y/2 * width/2 + x/2) * 4 + 3] = image[(y * width + x) * 4 + 3];
        }
    }*/
    for(int y = 0; y < height; y+=2){
        for(int x = 0; x < width; x+=2){
            for(int c = 0; c < 4; c++){ // for each of 4 channels
                int total = 0;
                // 4 pixels is source map to 1 pixel in destination
                total += image[(y * width + x) * 4 + c];
                total += image[((y+1) * width + x) * 4 + c];
                total += image[(y * width + (x+1)) * 4 + c];
                total += image[((y+1) * width + (x+1)) * 4 + c];
                out[(y/2 * width/2 + x/2) * 4 + c] = total / 4;
            }
        }
    }
    
    error = lodepng::encode(argv[2], out, width/2, height/2);
    
    if(error)cout << "Error! " << lodepng_error_text(error) << endl;
    
    return 0;
}