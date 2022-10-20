#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

using namespace std;

int is_bmp_valid(string s){

    unsigned char header[54];
    const char * b = s.c_str();

    FILE *fp = fopen(b, "rb");                                  // open file
    fread(header, sizeof(header), 1, fp);                       // read file 1 byte at a time and store in header array
    fclose(fp);                                                 // done using file here

    int num_planes = header[26] + (header[27] << 8);            // read number of planes
    int size_point = header[28]; + (header[29] << 8);            // read size of each point
    int compression = header[30]; + (header[31] << 8) + (header[32] << 16) + (header[33] << 24);

    if(header[0] != 'B' || header[1] != 'M'|| num_planes != 1 || size_point != 24 || compression != 0){
        return 0;           // bmp file is not valid, return 0
    }
    return 1;               // bmp file is valid 
}

void copy(string src, string dst){
    filesystem::copy(src, dst);
}





