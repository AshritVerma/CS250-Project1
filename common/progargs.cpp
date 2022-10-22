#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

#include "../common/progargs.hpp"

using namespace std;

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

void get_dimensions(string name, int &start, int &width, int &height, int &padding){
    unsigned char header[54];               // define header
    FILE *fp = fopen(name.c_str(), "rb");   // open file

    fread(header, sizeof(header), 1, fp);   // read header
    fclose(fp);

    // calculate the following values
    start = header[10] + (header[11] << 8) + (header[12] << 16) + (header[13] << 24);
    width = header[18] + (header[19] << 8) + (header[20] << 16) + (header[21] << 24);
    height = header[22] + (header[23] << 8) + (header[24] << 16) + (header[25] << 24);
    padding = ((4 - (width * 3) % 4) % 4);

}

int is_bmp_valid(string name){

    unsigned char header[54];
    FILE *fp = fopen(name.c_str(), "rb");                       // open file
    fread(header, sizeof(header), 1, fp);                       // read file 1 byte at a time and store in header array
    fclose(fp);                                                 // done using file here

    int num_planes = header[26] + (header[27] << 8);            // read number of planes
    int size_point = header[28] + (header[29] << 8);            // read size of each point
    int compression = header[30] + (header[31] << 8) + (header[32] << 16) + (header[33] << 24);

    if(header[0] != 'B' || header[1] != 'M'|| num_planes != 1 || size_point != 24 || compression != 0){
        return 0;           // bmp file is not valid, return 0
    }
    return 1;               // bmp file is valid 
}

void copy(string src, string dst){
    std::filesystem::copy(src, dst);
}

void write_array(ofstream &hst, int arr[256]){
    for(int i = 0; i < 256; i++)
        hst << arr[i] << endl;
}


// 24 lines without any blank lines
void histo(string name, string src, string dst){
    int r_vals[256], g_vals[256], b_vals[256], start, width, height, padding;
    unsigned char c[3];
    for(int r=0; r < 256; r++)
        r_vals[r] = g_vals[r] = b_vals[r] = 0;
    get_dimensions(name, start, width, height, padding);
    FILE *fp = fopen(name.c_str(), "rb");
    fseek(fp, start, 0);
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            fread(c, sizeof(c), 1, fp);         // read color's rgb values
            b_vals[c[0]]++;                     // iterate value 
            g_vals[c[1]]++;                     
            r_vals[c[2]]++; 
            fseek(fp,3,SEEK_CUR);               // move fp
        }
        fseek(fp,padding,SEEK_CUR);             // skip padding
    }
    fclose(fp);

    ofstream hst(dst + "/" + name.substr(src.size()+1,name.size()-src.size()-4)+"hst");                     // create ofstream called hst

    write_array(hst, r_vals);
    write_array(hst, g_vals);
    write_array(hst, b_vals);   

    hst.close();

}


/*
int main(){
    histo("images/balloon.bmp", "images", "test_out");

    
    vector <string> files;


    for (const auto& dirEntry : recursive_directory_iterator("images"))
        files.push_back(dirEntry.path());

    for(int i=0; i < files.size(); ++i){
        cout << files[i] << endl;
    }
    return 0;
    
} 
*/



