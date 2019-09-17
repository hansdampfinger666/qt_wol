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
#include <thread>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow (std::vector<std::vector<std::string>>&, QWidget* parent = nullptr);
    ~MainWindow();
    std::vector <std::vector<std::string>> machines;
    int no_machines;

    template <typename T> void cout_vec (std::vector<std::vector<T>>&);
    template <typename T> void cout_vec (std::vector<T>&);

signals:
    void emit_todo(std::vector <std::vector<std::string>>&, bool&);
    void emit_pinger_stop();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    void wake_up_pinger();

    Ui::MainWindow *ui;
    QList <QCheckBox *> cb_list;
    QList <QCheckBox *> get_cb (QWidget *);
    void modify_cb();
    const std::string id_cb = "checkBox_";
    const long id_cb_len = id_cb.length();
};

#endif // MAINWINDOW_H
