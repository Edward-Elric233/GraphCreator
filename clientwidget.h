#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>

QT_BEGIN_NAMESPACE
namespace Ui { class ClientWidget; }
QT_END_NAMESPACE

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();

private slots:
    void on_pushButtonConnect_clicked();

    void on_pushButtonGenerate_clicked();

    void on_pushButtonSave_clicked();

private:
    Ui::ClientWidget *ui;
    QTcpSocket *tcpSocket;
};
#endif // CLIENTWIDGET_H
