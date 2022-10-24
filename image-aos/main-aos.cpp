// Main function for AOS implementation
#include "../common/progargs.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <chrono>

using namespace std;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

int main(int argc, char *argv[]){
    const std::filesystem::path src = argv[1];
    const std::filesystem::path dst = argv[2];
    string oper = argv[3];

    if(error_check(argc,src,dst,oper))
        return -1;

    vector <string> files;

    for (const auto& dirEntry : recursive_directory_iterator(argv[1]))
        files.push_back(dirEntry.path());

    for(int i=0; i < static_cast<int>(files.size()); ++i)
        if(!is_bmp_valid(files[i])){
            cout << "Invalid BMP File: " << files[i] << endl;
            // HOW TO HANDLE AN INVALID BMP FILE HERE
        }

    auto start = chrono::high_resolution_clock::now(); 

    if(oper == "copy")
        copy(src, dst);

    else if(oper == "histo"){
        for(int i=0; i < static_cast<int>(files.size()); ++i)
            histo(files[i], argv[1], argv[2]);
    }

    else if(oper == "mono"){
       for(int i=0; i < static_cast<int>(files.size()); ++i)
            mono(files[i]);
    }

    else if(oper == "guass"){
       for(int i=0; i < static_cast<int>(files.size()); ++i)
            guass(files[i]);
    }

    auto stop = chrono::high_resolution_clock::now(); 
    auto duration = duration_cast<chrono::microseconds>(stop - start);
    std::cout << duration.count() << endl;

    return 0;
}


