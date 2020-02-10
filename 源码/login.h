#ifndef LOGIN_H
#define LOGIN_H

#include "Register.h"

#include <QWidget>
#include <QWidget>
#include <QPainter>
#include <QMovie>
#include <QDebug>
#include <QToolButton>
#include <QStyle>
#include <QPushButton>
#include <QBitmap>
#include <QPen>
#include <QBrush>
#include <QTcpSocket>
#include <QHostAddress>
#include <QPropertyAnimation>
#include <QFile>
#include <QMouseEvent>
#include <QDesktopServices>
#include <QLineEdit>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    void setWindow();
    void windowclosed();
    void windowmin();
    void mouseMoveEvent(QMouseEvent* mEvent);
    void mousePressEvent(QMouseEvent* mEvent);
    void TikTok();
    void connectMYSQL();

private slots:
    void on_sure_clicked();

    void on_registered_clicked();

signals:
    //定义子窗口向主窗口发送数据的信号
    void send_a_signal(QString send_msg);

private:
    Ui::Login *ui;
    QPoint dragPosition;
    QSqlDatabase dbconn;
    QString username;
    QString password;
    QString passwd;
    Register r;
};

#endif // LOGIN_H
