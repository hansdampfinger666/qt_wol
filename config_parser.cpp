#include <config_parser.h>

Machines::Machines(){

    read_file();
//    cout_vec(vtable);

}

void Machines::read_file(){

    std::ifstream file("/home/al/Documents/QtCreatorProjects/wolqt/config");   // turn into variable (option in application)
    std::string str;
    int r = -1;

   std::vector<std::string> entry(no_config_params);

    while (getline(file, str) && r < no_machines){

            if (str.substr(0,len_id_machine)==id_machine){
                r = r + 1;
                no_machines++;
                entry[0] = (del_trailing_spaces(str.substr(len_id_machine)));
            }
            if (str.substr(0,len_id_mac)==id_mac){
                entry[1] = (del_trailing_spaces(str.substr(len_id_mac)));
            }
            if (str.substr(0,len_id_os)==id_os){
                entry[2] = (del_trailing_spaces(str.substr(len_id_os)));
                vtable.push_back(entry);
            }
        }
}

std::string Machines::del_trailing_spaces (std::string str){

        str = str.substr(0, str.find_last_not_of(" ")+1);
        return str;
}




void Machines::cout_vec (std::vector< std::vector<std::string> > &vec){

unsigned long rows = 1;
rows = vec.size();

    for (unsigned long r = 0; r < rows; r++){

        for (std::string elem : vec[r] ){
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}



