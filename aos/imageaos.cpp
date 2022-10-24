// Image Handling with AOS implementation
#include "../common/progargs.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <cmath>

using namespace std;

struct color{
    int r,g,b;
};

void write(string file_name, vector <color> &colors){


    
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
    cout << "width: " << width << endl;
    // reads all data in array of structs, called colors
    for(int y = 0; y < 1; y++){
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
            cout << x << ": " << g << endl; 
        }

        fseek(fp,padding,SEEK_CUR);
    }

    ofstream hst(dst + "/" + file_name.substr(src.size()+1,file_name.size()-src.size()-4)+"hst");

    write(hst,colors);

    fclose(fp);
}
