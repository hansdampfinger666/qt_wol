#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <vector>

class Helper{

public:
    Helper();
    static std::string del_trailing_spaces (std::string);
    static void cout_vec (std::vector< std::vector <std::string> > &);
    static void cout (std::string);
    static void cout (std::string, int &);

};

#endif // HELPER_H
