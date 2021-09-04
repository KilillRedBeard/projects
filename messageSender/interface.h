#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <filehandler.h>

namespace Ui {
class interface;
}

class interface : public QMainWindow
{
    Q_OBJECT

    fileHandler *handler = new fileHandler();

public:
    explicit interface(QWidget *parent = 0);
    ~interface();

private slots:
    void on_addMessaage_clicked();
    void on_readMessages_clicked();
    void addNewMessage(message mess);
    void clearMessages();

private:
    Ui::interface *ui;

signals:
    void clearList();
};

#endif // INTERFACE_H
