// Image Handling with SOA implementation
#include "../common/progargs.hpp"
#include "../soa/imagesoa.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

using namespace std;


// unsure of how to initialize the size of the arrays within the struct color, 
// so I created this global variable (not allowed in project requirements) as a placeholder for now
const int color_size = 1000;

struct color{
    uint8_t r[color_size];
    uint8_t g[color_size];
    uint8_t b[color_size];
};

void guass(string file_name){
    unsigned char header[54];
    FILE *fp = fopen(file_name.c_str(), "rb");                  // open file
    fread(header, sizeof(header), 1, fp);                       // read file 1 byte at a time and store in header array

    fclose(fp);                                                 // done using file here
}

void mono(string file_name, string src, string dst){
    unsigned char header[54];
    FILE *fp = fopen(file_name.c_str(), "rb");                  // open file
    fread(header, sizeof(header), 1, fp);                       // read file 1 byte at a time and store in header array
    fclose(fp);                                                 // done using file here
    cout << src << dst << endl;
}
