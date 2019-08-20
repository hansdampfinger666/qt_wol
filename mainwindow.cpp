#include <mainwindow.h>
#include <ui_mainwindow.h>


MainWindow::MainWindow(int &i_no_machines, const std::vector< std::vector<std::string>> &i_vtable, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    todo.machines = i_vtable;
    no_machines = i_no_machines;
    cb_list = get_cb(centralWidget());
    modify_cb();
}


MainWindow::~MainWindow()
{
    delete ui;
}


QList <QCheckBox *> MainWindow::get_cb(QWidget *obj){

    cb_list = obj->findChildren <QCheckBox *>();
    return cb_list;
}


void MainWindow::modify_cb(){

    for (int i = 0; i < no_machines; i++){

        cb_list[i]->setText (QString::fromStdString(todo.machines[i][0]));
    }
}


void MainWindow::on_buttonBox_accepted(){

    todo.wol.clear();

    foreach (QCheckBox *checkBox, cb_list){

        if ( checkBox->checkState() == 2 )
            todo.wol.push_back(1);

        if ( !(checkBox->checkState() == 2))
            todo.wol.push_back(0);
    }

    int i = 0;
    for (auto it = todo.machines.begin(); it != todo.machines.end();) {
        if (todo.wol[i] == 0) {
            it = todo.machines.erase(it);
        } if (todo.wol[i] == 1) {
            ++it;
        }
        i++;
    }
    emit emit_todo(todo);
    qApp->exit();
}


void MainWindow::on_buttonBox_rejected()
{
        qApp->exit();
}








template <typename T> void MainWindow::cout_vec (std::vector<std::vector<T>> &vec){

unsigned long rows = 1;
rows = vec.size();

    for (unsigned long r = 0; r < rows; r++){

        for (std::string elem : vec[r] ){
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

template <typename T> void MainWindow::cout_vec (std::vector<T> &vec){

        for (bool elem : vec ){
            std::cout << elem << " ";
        }
        std::cout << std::endl;
}

