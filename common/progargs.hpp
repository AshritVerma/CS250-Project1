#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>


using namespace std;

// checks for correct formatting or any other errors
int error_check(int argc, string src, string dst, string oper);

// gets the files within the directory src and pushes them into the vector files
void get_files(string src, vector <string> &files);

// gets the dimensions of the given file name
void get_dimensions(std::string name, int &start, int &width, int &height); 

// checks if the .bmp file is valid, returns 1 if file is valid and 0 otherwise
int is_bmp_valid(std::string s);

// main handling for histo operation
void main_histo(string file_name, string src, string dst);
