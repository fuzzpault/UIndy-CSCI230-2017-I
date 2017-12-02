/*                                                                                                                    
  Name: Paul Talaga
  Date: Dec 1, 2017
  Desc: Program to take a png file and put black bars over top..

  To compile this, do: g++ bars.cpp
  To run: ./a.out 
  Loads 'Cat-PNG-2.png' and save the result to 'Cat-PNG-2-2.png'.
*/
#include <iostream>
#include <vector>
#include "lodepng.cpp"

using namespace std;

int main(void){
    unsigned width, height;
    
    vector<unsigned char> image;
    
    unsigned error = lodepng::decode(image, width, height, "Cat-PNG-2.png");
    
    if(error)cout << "Error! " << lodepng_error_text(error) << endl;
    
    cout << "Done loading!" << endl;
    cout << "Width: " << width << endl;
    cout << "Height: " << height << endl;
    
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            // When x or y is a multiple of 10, change it to black.
            if(x % 10 == 0 || y % 10 == 0){
                image[(y * width + x) * 4 + 0] = 0;
                image[(y * width + x) * 4 + 1] = 0;
                image[(y * width + x) * 4 + 2] = 0;
                image[(y * width + x) * 4 + 3] = 255;
            }
        }
    }
    
    error = lodepng::encode("Cat-PNG-2-2.png", image, width, height);
    
    if(error)cout << "Error! " << lodepng_error_text(error) << endl;
    
    return 0;
}