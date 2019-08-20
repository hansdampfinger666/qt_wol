#include <mainwindow.h>
#include <config_parser.h>
#include <sender.h>

#include <QApplication>


//#include <QSignalSpy>


void cout_vec (std::vector< std::vector<std::string> > &vec){

unsigned long rows = 1;
rows = vec.size();

    for (unsigned long r = 0; r < rows; r++){

        for (std::string elem : vec[r] ){
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}




int main(int argc, char *argv[])
{
    void cout_vec (std::vector<std::vector<std::string>> &vec);

        Machines m;
        QApplication a(argc, argv);
        MainWindow w (m.no_machines, m.vtable);
        w.show();

        Sender s (w);





        a.exec();

}





