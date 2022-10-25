// Image Handling with AOS implementation
#include "../common/progargs.hpp"
#include "../aos/imageaos.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <cmath>

using namespace std;

struct color{
    uint8_t b,g,r;
};

void write(ofstream &file_path, vector <color> &colors, string file_name){

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
            file_path << static_cast<char>(colors[y*width + x].b) << static_cast<char>(colors[y*width + x].g) << static_cast<char>(colors[y*width + x].r);

        for(int i = 0; i < padding; i++)    
            file_path << static_cast<char>(0x00);               // write padding bytes
    }
    file_path.close();                                          // close file path
}

void copy(string file_name, string src, string dst){
    int start, width, height, padding;
    unsigned char color_bytes[3];
    vector <color> clrs;

    get_dimensions(file_name, start, width, height);
    padding = (4 - (width * 3) % 4) % 4;

    FILE *fp = fopen(file_name.c_str(), "rb");

    fseek(fp, start, SEEK_SET);

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            fread(color_bytes, 1, 3, fp);           // read each set of color bytes
            color clr;
            clr.b = color_bytes[0];
            clr.g = color_bytes[1];
            clr.r = color_bytes[2];
            clrs.push_back(clr);
        }
        fseek(fp,padding,SEEK_CUR);                 
    }
    fclose(fp);
    
    ofstream hst(dst + "/" + file_name.substr(src.size(),file_name.size()));

    write(hst,clrs, file_name);
    hst.close();
}


void guass(string file_name, string src, string dst){
    int start, width, height, padding;
    unsigned char header[54], color_bytes[3];
    FILE *fp = fopen(file_name.c_str(), "rb");                  // open file
    fread(header, sizeof(header), 1, fp);                       // read file 1 byte at a time and store in header array

    get_dimensions(file_name, start, width, height);
    padding = (4 - (width * 3) % 4) % 4;                                            

    vector<color> clrs;

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            fread(color_bytes, 1, 3, fp);                       // read each set of color bytes
            
        }
    }
    ofstream hst(dst + "/" + file_name.substr(src.size(),file_name.size()));

    write(hst,clrs, file_name);
    hst.close();
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
    double g, norm[3];
    unsigned char color_bytes[3];
    vector <color> colors;

    get_dimensions(file_name, start, width, height);
    padding = (4 - (width * 3) % 4) % 4;

    FILE *fp = fopen(file_name.c_str(), "rb");

    fseek(fp, start, SEEK_SET);

    // reads all data in array of structs, called colors
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            fread(color_bytes, 1, 3, fp);           // read each set of color bytes
            mono_helper(color_bytes,norm,g);        // calculate g value using helper

            color clr;                              // create struct of color
            clr.b = clr.g = clr.r = g;              // set values
            colors.push_back(clr);                  // push to vector
        }
        fseek(fp,padding,SEEK_CUR);                 
    }
    fclose(fp);
    ofstream hst(dst + "/" + file_name.substr(src.size(),file_name.size()));
    write(hst,colors, file_name);
    hst.close();
}
