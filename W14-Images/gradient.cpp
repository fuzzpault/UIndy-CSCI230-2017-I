/*                                                                                                                    
  Name: Paul Talaga
  Date: Dec 1, 2017
  Desc: Program to generate a color gradient and save a png file.

  To compile this, do: g++ gradient.cpp
  To run: ./a.out 1024 768 output.png
  Which will create a 1024x768 image saved to output.png
*/

#include <iostream>
#include <vector>
#include <cmath>
#include "lodepng.cpp"

using namespace std;

int main(int argc, char* argv[]){
    
    if(argc < 4){
        cout << "I need 3 parameters, x, y, output png" << endl;
        return 1;
    }
    unsigned width = atoi(argv[1]);
    unsigned height = atoi(argv[2]);
    
    // 4 due to RGBA channels
    vector<unsigned char> image(width * height * 4);
    
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            image[(y * width + x) * 4 + 0] = sin(x/90.0) * 255/2 + 255/2;
            image[(y * width + x) * 4 + 1] = cos(x/90.0) * 255/2 + 255/2;
            image[(y * width + x) * 4 + 2] = cos(y/90.0) * 255/2 + 255/2;;
            image[(y * width + x) * 4 + 3] = 255; // No opacity
        }
    }
    
    unsigned error = lodepng::encode(argv[3], image, width, height);
    
    if(error)cout << "Error! " << lodepng_error_text(error) << endl;
    
    return 0;
}