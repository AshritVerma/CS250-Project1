// Image Handling with AOS implementation
#include "../common/progargs.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

using namespace std;

struct color{
    int r,g,b;
};


void guass(string file_name){
    unsigned char header[54];
    FILE *fp = fopen(file_name.c_str(), "rb");                  // open file
    fread(header, sizeof(header), 1, fp);                       // read file 1 byte at a time and store in header array

    fclose(fp);                                                 // done using file here
}

void mono(string file_name){
    int start, width, height, padding;
    unsigned char c[3];
    vector <color> colors;

    get_dimensions(file_name, start, width, height);
    padding = (4 - (width * 3) % 4) % 4;

    FILE *fp = fopen(file_name.c_str(), "rb");

    fseek(fp, start, SEEK_SET);

    // reads all data in array of structs, called colors
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            fread(c, 1, 3, fp);    
            color clr;
            clr.b = c[0];
            clr.g = c[1];
            clr.r = c[2];
            colors.push_back(clr);
        }
        fseek(fp,padding,SEEK_CUR);
    }

    // perfrom color corrections here

    fclose(fp);
}
