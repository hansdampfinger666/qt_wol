#ifndef KEYENTERRECEIVER_H
#define KEYENTERRECEIVER_H

#include <QObject>
#include <QEvent>
#include <QKeyEvent>

class keyEnterReceiver
{
    Q_OBJECT

protected:
    bool eventFilter(QObject* obj, QEvent* event);
};

#endif // KEYENTERRECEIVER_H
