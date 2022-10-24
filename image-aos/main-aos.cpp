// Main function for AOS implementation
#include "../common/progargs.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <chrono>

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
            // should add a method of how to not perform operation on the invalid files (ie removing from files vector)
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


