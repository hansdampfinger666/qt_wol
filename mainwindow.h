#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractButton>
#include <QCheckBox>
#include <QObject>
#include <QString>
#include <QShortcut>
#include <iostream>
#include <vector>
#include <config_parser.h>
#include <kled.h>
#include <pinger.h>
#include <QColor>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    //Methods
    MainWindow (Config *io_config = nullptr, QWidget *parent = nullptr);
    ~MainWindow();
    int my_no_machines;

    //Events
    signals:
        void emit_todo(std::vector<unsigned long>&, bool&);

    //Event handlers
    private slots:
        void on_buttonBox_accepted();
        void on_buttonBox_rejected();
        void on_buttonBox_apply();

private:

    //Methods
    void modify_cb();
    void update_led();
    void send_todo();

    //Variables
    Config *myo_config;
    Pinger *myo_pinger;
    Ui::MainWindow *ui;
    QList <QCheckBox *> mys_checkboxes;
    QList <KLed *> mys_leds;

    //Constants
    const std::string id_cb = "checkBox_";
    const long id_cb_len = id_cb.length();

protected:

//#ifndef QT_NO_CONTEXTMENU
//    void contextMenuEvent(QContextMenuEvent *event) override;
//#endif // QT_NO_CONTEXTMENU

};

#endif // MAINWINDOW_H
