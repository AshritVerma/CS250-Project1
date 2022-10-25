// Image Handling with SOA implementation
#include "../common/progargs.hpp"
#include "../soa/imagesoa.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <cmath>

using namespace std;


// unsure of how to initialize the size of the arrays within the struct color, 
// so I created this global variable (not allowed in project requirements) as a placeholder for now


struct colors{
    vector<uint8_t> b;
    vector<uint8_t> g;
    vector<uint8_t> r;
};

void write(ofstream &file_path, colors &clrs, string file_name){

    unsigned char header[58];                                   // define variables to be used.
    int start, width, height, padding;

    FILE *fp = fopen(file_name.c_str(), "rb");                  // open file
    fread(header, sizeof(header), 1, fp);                       // read file elements into header
    fclose(fp);                                                 // close file

    get_dimensions(file_name, start, width, height);            // get dimensions of file   
    padding = (4 - (width * 3) % 4) % 4;                        // calculate padding

    for(int h = 0; h < 58; h++)                                 // write header to output file
        file_path << header[h];

    for(int i = 0; i < start - 58; i++)                         // write blank characters before start
        file_path << static_cast<char>(0x00);

    for(int y = 0; y < height; y++){                            // begin to write each colors byte
        for(int x = 0; x < width; x++)
            file_path << clrs.b[y*width + x] << clrs.g[y*width + x] << clrs.r[y*width + x];

        for(int i = 0; i < padding; i++)    
            file_path << static_cast<char>(0x00);               // write padding bytes
    }
    file_path.close();                                          // close file path
}

void guass(string file_name){
    unsigned char header[54];
    FILE *fp = fopen(file_name.c_str(), "rb");                  // open file
    fread(header, sizeof(header), 1, fp);                       // read file 1 byte at a time and store in header array

    fclose(fp);                                                 // done using file here
}

// helper function to calculate g
void mono_helper(unsigned char (&color_bytes)[3], double (&norm)[3], double &g){
    for(int i = 0; i < 3; i++){
        norm[i] = color_bytes[i] / 255.0;
        if (norm[i] > 0.04045) {norm[i] = pow((norm[i] + 0.055)/(1.055),2.4);}
        else {norm[i] = norm[i] / 12.92;}
        }

    g = (0.2126 * norm[2] + 0.7152 * norm[1] + 0.0722 * norm[0]);
    if (g <= 0.0031308) g = 12.92 * g;
    else g = (1.055*pow(g,(1.0/2.4)))-0.055;

    g = floor(g * 255);
}

void mono(string file_name, string src, string dst){
    int start, width, height, padding;
    double g_val, norm[3];
    unsigned char color_bytes[3];
    struct colors clrs;
    uint8_t b, g, r;

    get_dimensions(file_name, start, width, height);
    padding = (4 - (width * 3) % 4) % 4;

    FILE *fp = fopen(file_name.c_str(), "rb");

    fseek(fp, start, SEEK_SET);

    // reads all data in array of structs, called colors
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            fread(color_bytes, 1, 3, fp);           // read each set of color bytes
            mono_helper(color_bytes,norm,g_val);        // calculate g value using helper

            b = g = r = g_val;
            clrs.b.push_back(b);  
            clrs.g.push_back(g);
            clrs.r.push_back(r); 
        }
        fseek(fp,padding,SEEK_CUR);                 
    }
    fclose(fp);
    ofstream hst(dst + "/" + file_name.substr(src.size()+1,file_name.size()-src.size()-4)+"bmp");

    write(hst,clrs, file_name);

}
