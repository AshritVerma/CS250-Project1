#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>


using namespace std;

int print_error();

void write(string file_name, vector <color> &colors);

int error_check(int argc, string src, string dst, string oper);

void get_dimensions(std::string name, int &start, int &width, int &height); 

int is_bmp_valid(std::string s);

void copy(std::string src, std::string dst);

void write_array(std::ofstream &hst, int (&arr)[256]);

void histo(std::string name, std::string src, std::string dst);

void guass(std::string file_name);

void mono(std::string file_name);

