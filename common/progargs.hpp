#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>


using namespace std;

int print_error();

int error_check(int argc, string src, string dst, string oper);

void get_dimensions(std::string name, int &start, int &width, int &height); 

int is_bmp_valid(std::string s);

void histo_helper(std::ofstream &hst, int (&arr)[256]);

void histo(std::string name, std::string src, std::string dst);
