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
    int r,g,b;
};


void write(ofstream &file_path, vector <color> &colors, string file_name){
    unsigned char header[58];
    FILE *fp = fopen(file_name.c_str(), "rb");                  // open file
    fread(header, sizeof(header), 1, fp);                       // read file 1 byte at a time and store i

    int start,width, height;

    get_dimensions(file_name, start, width, height);

    int padding = (4 - (width * 3) % 4) % 4;

    for(int h = 0; h < 58; h++)
        file_path << header[h];

    for(int i = 0; i < start - 58; i++)
        file_path << static_cast<char>(0x00);

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++)
            file_path << static_cast<char>(colors[y*width + x].b) << static_cast<char>(colors[y*width + x].g) << static_cast<char>(colors[y*width + x].r);

        for(int i = 0; i < padding; i++)
            file_path << static_cast<char>(0x00);
    }
    file_path.close();
}


void guass(string file_name){
    unsigned char header[54];
    FILE *fp = fopen(file_name.c_str(), "rb");                  // open file
    fread(header, sizeof(header), 1, fp);                       // read file 1 byte at a time and store in header array

    fclose(fp);                                                 // done using file here
}

void mono(string file_name, string src, string dst){
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
            float n[3]; 
            for(int i = 0; i < 3; i++){
                n[i] = c[i] / 255.0;
                if(n[i] > 0.04045){
                    n[i] = pow((n[i] + 0.055)/(1.055),2.4);
                }
                else{
                    n[i] = n[i] / 12.92;
                }
            }
            float g = (0.2126 * n[2] + 0.7152 * n[1] + 0.0722 * n[0]);
            if (g <= 0.0031308)
                g = 12.92 * g;
            else
                g = (1.055*pow(g,(1/2.4)))-0.055;

            g = floor(g * 255);

            color clr;
            clr.b = clr.g = clr.r = g;
            colors.push_back(clr);
        }

        fseek(fp,padding,SEEK_CUR);
    }

    ofstream hst(dst + "/" + file_name.substr(src.size()+1,file_name.size()-src.size()-4)+"bmp");

    write(hst,colors, file_name);

    fclose(fp);
}
