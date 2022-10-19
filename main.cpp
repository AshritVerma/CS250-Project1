#include <iostream>
#include <vector>
#include "image.hpp"

int main() {


    const int width = 640;
    const int height = 480;

    Image image(width,height);

    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            image.SetColor(Color((float) x / (float)width, 1.0f - ((float)x / (float)width), (float)y / (float)height), x,y);
        }
    }

    image.Export("image.bmp");

    Image copy(0,0);

    copy.Read("image.path");

    copy.Export("copy.bmp");
}


int bmp_valid(char s[]){
    FILE *fp = fopen(s, "rb");
    int check = fseek(fp, 26, 0) // seek to move pointer 
    fread() // read the block of data to compare
    
}
