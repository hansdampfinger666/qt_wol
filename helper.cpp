#include <helper.h>

Helper::Helper(){};

std::string Helper::del_trailing_spaces (std::string str){

        str = str.substr(0, str.find_last_not_of(" ")+1);
        return str;
}

void Helper::cout_vec (std::vector< std::vector<std::string> > &vec){

unsigned long rows = 1;
rows = vec.size();

    for (unsigned long r = 0; r < rows; r++){

        for (std::string elem : vec[r] ){
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

void Helper::cout (std::string str, int &i){

    str =+ i;
    std::cout << str << " " << std::endl;
}

void Helper::cout (std::string str){

    std::cout << str << " " << std::endl;
}



