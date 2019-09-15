#include "keyenterreceiver.h"

bool keyEnterReceiver::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type()==QEvent::KeyPress) {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ) {
            //Enter or return was pressed
        } else {
            return this->eventFilter(obj, event);
//            return false;
        }
        return true;
    } else {
        return this->eventFilter(obj, event);
//        return false;
    }
    return false;
}
