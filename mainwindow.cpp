#include <mainwindow.h>
#include <ui_mainwindow.h>


MainWindow::MainWindow(std::vector< std::vector<std::string>>& i_machines, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cb_list = get_cb(centralWidget());
    machines = i_machines;
    modify_cb();

    QShortcut *returnShortcut = new QShortcut(QKeySequence("Return"), ui->buttonBox);
    QObject::connect(returnShortcut, &QShortcut::activated, this, &MainWindow::on_buttonBox_accepted);
    QShortcut *escShortcut = new QShortcut(QKeySequence("Escape"), ui->buttonBox);
    QObject::connect(escShortcut, &QShortcut::activated, this, &MainWindow::on_buttonBox_rejected);
}


MainWindow::~MainWindow()
{
    delete ui;
}


QList <QCheckBox *> MainWindow::get_cb(QWidget *obj)
{
    cb_list = obj->findChildren <QCheckBox *>();
    return cb_list;
}


void MainWindow::modify_cb(){

    for (unsigned long i = 0; i < machines.size(); i++)
    {
        cb_list[i]->setText(QString::fromStdString(machines[i][0]));
    }
}


void MainWindow::on_buttonBox_accepted()
{
    unsigned int i = 0;
    bool mode;

    foreach (QCheckBox* checkBox, cb_list){

        switch (ui->verticalSlider->value()){

        case true:
            if (checkBox->checkState()==0){
                machines.erase(machines.begin() + i);
                i--;
            }
            mode = 1;
            break;

        case false:
            if (checkBox->checkState()==0){
                machines.erase(machines.begin() + i);
                i--;
            }
            mode = 0;
            break;
        }
        i++;
    }
    emit emit_pinger_stop();
    emit emit_todo(machines, mode);
    qApp->exit();
}


void MainWindow::on_buttonBox_rejected()
{
    emit emit_pinger_stop();
    qApp->exit();
}








template <typename T> void MainWindow::cout_vec (std::vector<std::vector<T>> &vec)
{
unsigned long rows = 1;
rows = vec.size();

    for (unsigned long r = 0; r < rows; r++)
    {
        for (std::string elem : vec[r] ){
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

template <typename T> void MainWindow::cout_vec (std::vector<T> &vec)
{
        for (bool elem : vec ){
            std::cout << elem << " ";
        }
        std::cout << std::endl;
}

