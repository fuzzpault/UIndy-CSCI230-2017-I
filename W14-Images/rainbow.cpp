/*                                                                                                                    
  Name: Paul Talaga
  Date: Dec 1, 2017
  Desc: Program to take a png file and apply a rainbow effect.

  To compile this, do: g++ rainbow.cpp
  To run: ./a.out input.png output.png
  Which will open input.png, mess with the colors, and save the result
  to output.png
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
    
    if(error)cout << "Error! " << lodepng_error_text(error) << endl;
    
    cout << "Done loading!" << endl;
    cout << "Width: " << width << endl;
    cout << "Height: " << height << endl;
    
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            // First convert the pixel to grayscale
            float total = 0;
            // 0.21 R + 0.72 G + 0.07 B
            total += image[(y * width + x) * 4 + 0] * 0.21;
            total += image[(y * width + x) * 4 + 1] * 0.72;
            total += image[(y * width + x) * 4 + 2] * 0.07;

            // Now map the grayscale value to a RGB value
            // This is very arbitrary
            image[(y * width + x) * 4 + 0] = total;
            if(total < 255/2){
                image[(y * width + x) * 4 + 1] = total * 2;
            }else{
                image[(y * width + x) * 4 + 1] = 255 - total * 2;
            }
            
            image[(y * width + x) * 4 + 2] = 255 - total;
            //image[(y * width + x) * 4 + 3] = 255; // Leave opacity alone
        }
    }
    
    error = lodepng::encode(argv[2], image, width, height);
    
    if(error)cout << "Error! " << lodepng_error_text(error) << endl;
    
    return 0;
}