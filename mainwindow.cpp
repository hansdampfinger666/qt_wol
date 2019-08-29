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

    QShortcut *returnShortcut = new QShortcut(QKeySequence("Return"), ui->buttonBox);
    QObject::connect(returnShortcut, &QShortcut::activated, this, &MainWindow::on_buttonBox_accepted);
    QShortcut *escShortcut = new QShortcut(QKeySequence("Escape"), ui->buttonBox);
    QObject::connect(escShortcut, &QShortcut::activated, this, &MainWindow::on_buttonBox_rejected);

}


MainWindow::~MainWindow()
{
    delete ui;
}


QList <QCheckBox *> MainWindow::get_cb(QWidget *obj){

    cb_list = obj->findChildren <QCheckBox *>();        // find all checkboxes in widget
    return cb_list;
}


void MainWindow::modify_cb(){

    for (int i = 0; i < no_machines; i++){

        cb_list[i]->setText (QString::fromStdString(todo.machines[i][0]));      // rename all checkboxes according to machine list from config
    }
}


void MainWindow::on_buttonBox_accepted(){

    todo.wol.clear();

    foreach (QCheckBox *checkBox, cb_list){     // if OK was pressed -> check all checkbox states and set bool for wol/shutdown command

        if ( checkBox->checkState() == 2 && ui->verticalSlider->value() )
            todo.wol.push_back(1);
        else if ( !(checkBox->checkState() == 2) && ui->verticalSlider->value() )
            todo.wol.push_back(0);
        if ( checkBox->checkState() == 2 && !ui->verticalSlider->value() )
            todo.shutdown.push_back(1);
        else if ( !(checkBox->checkState() == 2) && !ui->verticalSlider->value() )
            todo.shutdown.push_back(0);
    }

    cout_vec(todo.wol);
    cout_vec(todo.shutdown);

    int i = 0;

    if (ui->verticalSlider->value()){

    for (auto it = todo.machines.begin(); it != todo.machines.end();) {     // delete all entries without WOL bool = 1

        if (todo.wol[i] == 0) {
            it = todo.machines.erase(it);
        }
        if (todo.wol[i] == 1) {
            ++it;
        }
        i++;
    }
    i = 0;
    }

    else if (!ui->verticalSlider->value()){

    for (auto it = todo.machines.begin(); it != todo.machines.end();) {     // delete all entries without shutdown bool = 1

        if (todo.shutdown[i] == 0) {
            it = todo.machines.erase(it);
        }
        else if (todo.shutdown[i] == 1) {
            ++it;
        }
        i++;
    }
    }

    int sliderpos;
    sliderpos = ui->verticalSlider->value();
    std::cout << "Slider position at: " << sliderpos << std::endl;

    emit emit_todo(todo);
    qApp->exit();
}





void MainWindow::on_buttonBox_rejected(){

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

