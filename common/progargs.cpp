#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include "../common/progargs.hpp"

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
    std::filesystem::copy(src, dst);
}

void histo(string name){
    int r_vals[256], g_vals[256], b_vals[256];          // array of values to store counts in
    for(int r=0; r < 256; r++){
        r_vals[r] = 0;
        g_vals[r] = 0;
        b_vals[r] = 0;
    }

    unsigned char header[54];
    const char * b = name.c_str();

    FILE *fp = fopen(b, "rb");              // open file
    fread(header, sizeof(header), 1, fp);

    int start_val = header[10] + (header[11] << 8) + (header[12] << 16) + (header[13] << 24);
    fseek(fp,start_val,0);

    int width = header[18] + (header[19] << 8) + (header[20] << 16) + (header[21] << 24);
    int height = header[22] + (header[23] << 8) + (header[24] << 16) + (header[25] << 24);
    
    int padding = ((4 - (width * 3) % 4) % 4);

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            unsigned char c[3];
            fread(c, sizeof(c), 1, fp);         // read color's rgb values
            b_vals[int(c[0])]++;                     // iterate value 
            g_vals[c[1]]++;                     
            r_vals[c[2]]++; 
            fseek(fp,3,SEEK_CUR);               // move fp
        }
        fseek(fp,padding,SEEK_CUR);             // skip padding
    }
    int sum = 0;
    for(int i = 0; i < 256; i++){
        sum += b_vals[i] + g_vals[i] + r_vals[i];
    }
    cout << sum << endl;
    cout << width * height << endl;
    fclose(fp);
}





