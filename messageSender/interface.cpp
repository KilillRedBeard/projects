#include "interface.h"
#include "ui_interface.h"

interface::interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::interface) {
    ui->setupUi(this);

    connect(handler, SIGNAL(addMessageToList(message)), this, SLOT(addNewMessage(message)));
}

interface::~interface() {
    delete ui;
}

void interface::on_addMessaage_clicked() {
    message mes;
    handler->setMessage(mes);
    handler->writeToFile(mes);
    on_readMessages_clicked();
}

void interface::on_readMessages_clicked() {
    emit clearList();
    handler->readFromFile();
}

void interface::addNewMessage(message mess) {
    QFrame *frame = new QFrame();
    QVBoxLayout *mainLayoyt = new QVBoxLayout();

    QHBoxLayout *headerSrcLayoyt = new QHBoxLayout();
    QHBoxLayout *headerDstLayoyt = new QHBoxLayout();
    QHBoxLayout *headerTypeLayoyt = new QHBoxLayout();
    QHBoxLayout *headerLenLayoyt = new QHBoxLayout();
    QHBoxLayout *headerCrcLayoyt = new QHBoxLayout();
    QHBoxLayout *signalDataNChanLayoyt = new QHBoxLayout();
    QHBoxLayout *signalDataStatusLayoyt = new QHBoxLayout();
    QHBoxLayout *signalDataDataSizeLayoyt = new QHBoxLayout();
    QVBoxLayout *signalDataDataLayoyt = new QVBoxLayout();
    QHBoxLayout *signalDataCrcLayoyt = new QHBoxLayout();

    QLabel *title = new QLabel("Message");
    QLabel *headerSrcLbl = new QLabel("Src: ");
    QLabel *headerDstLbl = new QLabel("Dst: ");
    QLabel *headerTypeLbl = new QLabel("Type: ");
    QLabel *headerLenLbl = new QLabel("Len: ");
    QLabel *headerCrcLbl = new QLabel("Crc: ");
    QLabel *signalDataNChanLbl = new QLabel("nChan: ");
    QLabel *signalDataStatusLbl = new QLabel("Status: ");
    QLabel *signalDataDataSizeLbl = new QLabel("DataSize: ");
    QLabel *signalDataCrcLbl = new QLabel("Crc: ");

    QLabel *headerSrcValue = new QLabel();
    QLabel *headerDstValue = new QLabel();
    QLabel *headerTypeValue = new QLabel();
    QLabel *headerLenValue = new QLabel();
    QLabel *headerCrcValue = new QLabel();
    QLabel *signalDataNChanValue = new QLabel();
    QLabel *signalDataStatusValue = new QLabel();
    QLabel *signalDataDataSizeValue = new QLabel();
    QLabel *signalDataCrcValue = new QLabel();

    headerSrcValue->setText(QString::number(mess.getHeader().getSrc()));
    headerDstValue->setText(QString::number(mess.getHeader().getDst()));
    headerTypeValue->setText(QString::number(mess.getHeader().getType()));
    headerLenValue->setText(QString::number(mess.getHeader().getLen()));
    headerCrcValue->setText(QString::number(mess.getHeader().getCrc()));
    signalDataNChanValue->setText(QString::number(mess.getData().getNChan()));
    signalDataStatusValue->setText(QString::number(mess.getData().getStatus()));
    signalDataDataSizeValue->setText(QString::number(mess.getData().getDataSize()));
    signalDataCrcValue->setText(QString::number(mess.getData().getCrc()));

    headerSrcLayoyt->addWidget(headerSrcLbl);
    headerSrcLayoyt->addWidget(headerSrcValue);

    headerDstLayoyt->addWidget(headerDstLbl);
    headerDstLayoyt->addWidget(headerDstValue);

    headerTypeLayoyt->addWidget(headerTypeLbl);
    headerTypeLayoyt->addWidget(headerTypeValue);

    headerLenLayoyt->addWidget(headerLenLbl);
    headerLenLayoyt->addWidget(headerLenValue);

    headerCrcLayoyt->addWidget(headerCrcLbl);
    headerCrcLayoyt->addWidget(headerCrcValue);

    signalDataNChanLayoyt->addWidget(signalDataNChanLbl);
    signalDataNChanLayoyt->addWidget(signalDataNChanValue);

    signalDataStatusLayoyt->addWidget(signalDataStatusLbl);
    signalDataStatusLayoyt->addWidget(signalDataStatusValue);

    signalDataDataSizeLayoyt->addWidget(signalDataDataSizeLbl);
    signalDataDataSizeLayoyt->addWidget(signalDataDataSizeValue);

    for(int i = 0; i < mess.getData().getData().size(); ++i) {
        QHBoxLayout *lay = new QHBoxLayout();
        QLabel *name = new QLabel("data " + QString::number(i + 1));
        QLabel *value = new QLabel(QString::number(mess.getData().getData().at(i)));

        lay->addWidget(name);
        lay->addWidget(value);

        signalDataDataLayoyt->addLayout(lay);
    }

    signalDataCrcLayoyt->addWidget(signalDataCrcLbl);
    signalDataCrcLayoyt->addWidget(signalDataCrcValue);

    mainLayoyt->addWidget(title);
    mainLayoyt->addLayout(headerSrcLayoyt);
    mainLayoyt->addLayout(headerDstLayoyt);
    mainLayoyt->addLayout(headerTypeLayoyt);
    mainLayoyt->addLayout(headerLenLayoyt);
    mainLayoyt->addLayout(headerCrcLayoyt);
    mainLayoyt->addLayout(signalDataNChanLayoyt);
    mainLayoyt->addLayout(signalDataStatusLayoyt);
    mainLayoyt->addLayout(signalDataDataSizeLayoyt);
    mainLayoyt->addLayout(signalDataDataLayoyt);
    mainLayoyt->addLayout(signalDataCrcLayoyt);

    frame->setLayout(mainLayoyt);
    frame->setFrameStyle(QFrame::Panel | QFrame::Plain);
//    frame->setStyleSheet("background-color: #2E3F7F");

    ui->scrollLayout->addWidget(frame);

    connect(this, SIGNAL(clearList()), headerSrcLayoyt, SLOT(deleteLater()));
    connect(this, SIGNAL(clearList()), headerDstLayoyt, SLOT(deleteLater()));
    connect(this, SIGNAL(clearList()), headerTypeLayoyt, SLOT(deleteLater()));
    connect(this, SIGNAL(clearList()), headerLenLayoyt, SLOT(deleteLater()));
    connect(this, SIGNAL(clearList()), headerCrcLayoyt, SLOT(deleteLater()));
    connect(this, SIGNAL(clearList()), signalDataNChanLayoyt, SLOT(deleteLater()));
    connect(this, SIGNAL(clearList()), signalDataStatusLayoyt, SLOT(deleteLater()));
    connect(this, SIGNAL(clearList()), signalDataDataSizeLayoyt, SLOT(deleteLater()));
    connect(this, SIGNAL(clearList()), signalDataDataLayoyt, SLOT(deleteLater()));
    connect(this, SIGNAL(clearList()), signalDataCrcLayoyt, SLOT(deleteLater()));
    connect(this, SIGNAL(clearList()), mainLayoyt, SLOT(deleteLater()));
    connect(this, SIGNAL(clearList()), frame, SLOT(deleteLater()));
    connect(this, SIGNAL(clearList()), ui->scrollArea, SLOT(update()));
}

void interface::clearMessages()
{
    QLayoutItem *frame;
    while(ui->scrollLayout->isEmpty() && (frame = ui->scrollLayout->takeAt(0)) != 0) {
        ui->scrollLayout->removeItem(frame);
        delete frame;
    }
}
