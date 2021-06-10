#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <fstream>
#include <QDebug>

ClientWidget::ClientWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    tcpSocket = new QTcpSocket(this);
    ui->lineEditIp->setText("121.4.32.143");
    ui->lineEditPort->setText("12345");
    constexpr int MAXN = 1e6;
    ui->spinBoxNode->setMaximum(MAXN);
    ui->spinBoxEdge->setMaximum(MAXN);
    connect(tcpSocket, &QTcpSocket::connected, [=](){
        ui->textEdit->setText("connect sucess");
    });
    connect(tcpSocket, &QTcpSocket::readyRead, [=](){
        QByteArray buf = tcpSocket->readAll();
        QString origin_buf = ui->textEdit->toPlainText();
        ui->textEdit->setText(origin_buf + QString(buf));
    });
}

ClientWidget::~ClientWidget()
{
    delete ui;
}


void ClientWidget::on_pushButtonConnect_clicked()
{
    QString ip = ui->lineEditIp->text();
    qint16 port = ui->lineEditPort->text().toInt();

    tcpSocket->connectToHost(QHostAddress(ip), port);
}

void ClientWidget::on_pushButtonGenerate_clicked()
{
    ui->textEdit->clear();
    QString node_num = ui->spinBoxNode->text();
    QString edge_num = ui->spinBoxEdge->text();
    ui->lineEdit->setText("Case" + node_num + ".json");

    QString buf = node_num + " " + edge_num;
    tcpSocket->write(buf.toUtf8().data());
}

void ClientWidget::on_pushButtonSave_clicked()
{
//    qDebug() << "ready to write";
    QString file_name = ui->lineEdit->text();
    std::ofstream os(file_name.toUtf8());
    os << ui->textEdit->toPlainText().toUtf8().data();
    os.close();
}
