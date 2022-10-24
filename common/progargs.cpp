#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <chrono>
#include "progargs.hpp"

using namespace std;

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;


int print_error(){
    cout << "\t" << "./build/image-aos in_path out_path oper\n";
    cout << "\t\t" << "operation: copy, histo, mono, guass\n";
    return 1;
}

int error_check(int argc, string src, string dst, string oper){
    if(argc != 4){
        cout << "Wrong format:\n";
        return print_error();
    }

    if(oper != "copy" && oper != "histo" && oper != "mono" && oper != "guass"){
        cout << "Unexpected operation: " << oper << endl;
        return print_error();
    }

    cout << "Input path: " << src << endl;
    cout << "Output path: " << dst << endl;

    if(!filesystem::exists(src)){
        cout << "Cannot open directory: [" << src << "]\n";
        return print_error();
    }
    if(!filesystem::exists(dst)){
        cout << "Output directory [" << dst << "] does not exist\n";
        return print_error();
    }
    return 0;
}

void get_dimensions(string name, int &start, int &width, int &height, int &padding){
    unsigned char header[54];               // define header
    FILE *fp = fopen(name.c_str(), "rb");   // open file

    fread(header, sizeof(header), 1, fp);   // read header
    fclose(fp);

    // calculate the following values based on chart
    start = header[10]+ (header[11] << 8) + (header[12] << 16) + (header[13] << 24);
    width = header[18] + (header[19] << 8) + (header[20] << 16) + (header[21] << 24);
    height = header[22] + (header[23] << 8) + (header[24] << 16) + (header[25] << 24);
    padding = (4 - (width * 3) % 4) % 4;

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
        hst << arr[i] << " ";
    hst << endl;
}

// 23 lines without any blank lines
void histo(string name, string src, string dst){

    int r_vals[256], g_vals[256], b_vals[256], start, width, height, padding;
    unsigned char c[3];

    for(int r=0; r < 256; r++)
        r_vals[r] = g_vals[r] = b_vals[r] = 0;

    get_dimensions(name, start, width, height, padding);

    FILE *fp = fopen(name.c_str(), "rb");

    fseek(fp, start, SEEK_SET);

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            fread(c, 1, 3, fp);    
            b_vals[static_cast<uint8_t>(c[0])]++;   // iterate value 
            g_vals[static_cast<uint8_t>(c[1])]++;
            r_vals[static_cast<uint8_t>(c[2])]++;
        }
        fseek(fp,padding,SEEK_CUR);             // skip padding
    }
    fclose(fp);

    ofstream hst(dst + "/" + name.substr(src.size()+1,name.size()-src.size()-4)+"hst");      // create ofstream called hst

    write_array(hst, r_vals);
    write_array(hst, g_vals);
    write_array(hst, b_vals);   

    hst.close();

}


