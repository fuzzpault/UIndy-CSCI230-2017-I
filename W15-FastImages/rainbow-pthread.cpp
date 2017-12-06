/*                                                                                                                    
  Name: Paul Talaga
  Date: Dec 1, 2017
  Desc: Program to take a png file and apply a rainbow effect.

  To compile this, do: g++ rainbow-pthread.cpp -lpthread
  To run: ./a.out input.png output.png
  Which will open input.png, mess with the colors, and save the result
  to output.png
  
  Uses multiple threads to speed to conversion.
*/

#include <iostream>
#include <vector>
#include <pthread.h>
#include "lodepng.cpp"

using namespace std;

// TODO: Refactor to remove global variables.
//unsigned width, height;
//vector<unsigned char> image;
const int NUM_THREADS = 17;

struct thread_data_t{
  int thread_id;
  unsigned char* image;
  unsigned width;
  unsigned height;
};

void manipImage(int id, int width, int height, unsigned char* image){
    for(int y = id; y < height; y+= NUM_THREADS){
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
}

void* doStuff(void* arg){
  thread_data_t* input;
  input = (thread_data_t*)arg;
  manipImage(input->thread_id, input->width, input->height, input->image);
}

int main(int argc, char* argv[]){
    
    if(argc < 3){
        cout << "I need 2 parameters, an input png and output png" << endl;
        return 1;
    }
    
    
    vector<unsigned char> image;
    unsigned width, height;
    
    unsigned error = lodepng::decode(image, width, height, argv[1]);
    
    if(error)cout << "Error! " << lodepng_error_text(error) << endl;
    
    cout << "Done loading!" << endl;
    cout << "Width: " << width << endl;
    cout << "Height: " << height << endl;
    
    thread_data_t passed[NUM_THREADS];
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    for(int i = 0; i < NUM_THREADS; i++){
        passed[i].thread_id = i;
        passed[i].width = width;
        passed[i].height = height;
        passed[i].image = image.data(); // Returns a pointer to the internal array
        pthread_create(&threads[i], &attr, doStuff, (void*)&passed[i]);
    }
    
    for(int i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
        cout << "Thread " << i << " done." << endl;  // This slows it down, so don't print!
    }
    pthread_attr_destroy(&attr);
    
    cout << "Done rainbow-ing" << endl;
    
    error = lodepng::encode(argv[2], image, width, height);
    
    if(error)cout << "Error! " << lodepng_error_text(error) << endl;
    
    return 0;
}