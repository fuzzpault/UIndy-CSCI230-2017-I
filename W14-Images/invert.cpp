/*                                                                                                                    
  Name: Paul Talaga
  Date: Nov 30, 2017
  Desc: Program to invert the colors of a png file.

  To compile this, do: g++ invert.cpp
  To run: ./a.out input.png output.png
  Which will open input.png, flip the colors, and save the result
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
            image[(y * width + x) * 4 + 0] = 255 - image[(y * width + x) * 4 + 0];
            image[(y * width + x) * 4 + 1] = 255 - image[(y * width + x) * 4 + 1];
            image[(y * width + x) * 4 + 2] = 255 - image[(y * width + x) * 4 + 2];
            //image[(y * width + x) * 4 + 3] = 255; // Leave opacity alone.
        }
    }
    
    error = lodepng::encode(argv[2], image, width, height);
    
    if(error)cout << "Error! " << lodepng_error_text(error) << endl;
    
    return 0;
}