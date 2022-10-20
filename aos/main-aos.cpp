// Main function for AOS implementation
#include "../common/progargs.h"

int main(int argc, char *argv[]){
    vector <string> a;

    const std::filesystem::path src = argv[1];
    const std::filesystem::path dst = argv[2];
    string oper = argv[3];

    if(oper == "copy"){
        copy(src, dst);
    }


    for (const auto& dirEntry : recursive_directory_iterator(argv[1]))
        a.push_back(dirEntry.path());

    for(int i=0; i < a.size(); ++i){
        is_bmp_valid(a[i]);
        
    }

    return 1;
}

