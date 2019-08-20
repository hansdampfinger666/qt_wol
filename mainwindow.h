#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractButton>
#include <QCheckBox>
#include <QObject>
#include <QString>
#include <iostream>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int &,const std::vector<std::vector<std::string>> &, QWidget *parent = nullptr);
    ~MainWindow();
    std::vector<std::vector<std::string>> v_machines;
    int no_machines;
    struct Todo_list{
    public:
        std::vector <std::vector<std::string>> machines;
        std::vector <bool> wol;
        std::vector <bool> shutdown;
    };
    Todo_list todo;

    template <typename T> void cout_vec (std::vector<std::vector<T>> &);
    template <typename T> void cout_vec (std::vector<T> &);

signals:
//    void transmit_to_object(bool);
    void emit_todo(Todo_list);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::MainWindow *ui;
    QList <QCheckBox *> cb_list;
    QList <QCheckBox *> get_cb (QWidget *);
    void modify_cb();
    const std::string id_cb = "checkBox_";
    const long id_cb_len = id_cb.length();
};

#endif // MAINWINDOW_H
