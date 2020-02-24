#include <mainwindow.h>
#include <ui_mainwindow.h>


MainWindow::MainWindow(Config *io_config, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    myo_config = io_config;
    Pinger::discover_network(myo_config); //other thread

    ui->setupUi(this);

    mys_checkboxes = this->findChildren <QCheckBox *>();
    modify_cb();
    mys_leds = this->findChildren <KLed *>();
    update_led();

    //Set shortcut events
    QShortcut *returnShortcut = new QShortcut(QKeySequence("Return"), ui->buttonBox);
    QShortcut *escShortcut = new QShortcut(QKeySequence("Escape"), ui->buttonBox);

    //Set shortcut event handlers
    QObject::connect(escShortcut, &QShortcut::activated, this, &MainWindow::on_buttonBox_rejected);
    QObject::connect(returnShortcut, &QShortcut::activated, this, &MainWindow::on_buttonBox_accepted);

//    QList <QObject*> children ;
//    children = this->findChildren <QObject*>();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::modify_cb()
{
    for (int i = 0; i < mys_checkboxes.count(); i++)
        mys_checkboxes[i]->setText(QString::fromStdString(myo_config->mys_config.names[i]));
}


void MainWindow::update_led()
{
    myo_config->out();

    for(int i = 0; i < mys_leds.count(); i++)
    {
        if(myo_config->mys_config.online.at(i))
            mys_leds.at(i)->setColor("green");
        else
            mys_leds.at(i)->setColor("red");
    }
}


void MainWindow::on_buttonBox_accepted()
{
    send_todo();
    qApp->exit();
}


void MainWindow::on_buttonBox_apply()
{
    std::cout << " apply was clicked " << std::endl;
//    send_todo();
}


void MainWindow::send_todo()
{
    unsigned long index = 0;
    bool mode;
    std::vector<unsigned long> todo;

    if(ui->verticalSlider->value())
        mode = 1;
    else
        mode = 0;

    foreach(QCheckBox* checkBox, mys_checkboxes)
    {
        if (checkBox->checkState()==2)
        {
            todo.push_back(index);
        }
        index++;
    }
    emit emit_todo(todo, mode);
}


void MainWindow::on_buttonBox_rejected()
{
    qApp->exit();
}
