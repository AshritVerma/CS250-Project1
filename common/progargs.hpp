#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>



void get_dimensions(std::string name, int &start, int &width, int &height, int &padding); 

int is_bmp_valid(std::string s);

void copy(std::string src, std::string dst);

void write_array(std::ofstream &hst, int arr[256]);

void histo(std::string name, std::string src, std::string dst);


