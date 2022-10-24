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

vector <color> colors;

void guass(string file_name){
    unsigned char header[54];
    FILE *fp = fopen(file_name.c_str(), "rb");                  // open file
    fread(header, sizeof(header), 1, fp);                       // read file 1 byte at a time and store in header array

    fclose(fp);                                                 // done using file here
}

void mono(string file_name){
    unsigned char header[54];
    FILE *fp = fopen(file_name.c_str(), "rb");                  // open file
    fread(header, sizeof(header), 1, fp);                       // read file 1 byte at a time and store in header array
    fclose(fp);                                                 // done using file here

}
