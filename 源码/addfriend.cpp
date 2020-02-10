#include "addfriend.h"
#include "ui_addfriend.h"

addFriend::addFriend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addFriend)
{
    ui->setupUi(this);
    this -> setWindowTitle("Add friend");
    this -> setWindowIcon(QIcon("../icon/Mail48px.ico"));
}

addFriend::~addFriend()
{
    dbconn.close();
    delete ui;
}

void addFriend::receive_a_signal1(QString recv_msg)
{
    username = recv_msg;
    connectMYSQL();
}

void addFriend::on_pushButton_clicked()
{
    QString address = ui -> lineEdit -> text();
    QString se = QString("select address from user where address='%1'").arg(address);
    QSqlQuery sql_query;
    sql_query.exec(se);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
        QMessageBox message(QMessageBox::NoIcon, "Add friend", "添加失败，请检查address?");
        message.setWindowFlags(Qt::Drawer);
        message.setIconPixmap(QPixmap("../icon/Mail64px.png"));
        message.exec();
    }
    else
    {
        if(sql_query.next())
        {
            QString se = QString("insert into mail_list values('%1', '%2')").arg(username).arg(address);
            QSqlQuery sql_query;
            if(!sql_query.exec(se))
            {
                qDebug()<<sql_query.lastError();
                QMessageBox message(QMessageBox::NoIcon, "Add friend", "添加失败，请稍后重试!");
                message.setWindowFlags(Qt::Drawer);
                message.setIconPixmap(QPixmap("../icon/Mail64px.png"));
                message.exec();
            }
            else
            {
                QMessageBox message(QMessageBox::NoIcon, "Add friend", "添加成功，快去聊天吧~");
                message.setWindowFlags(Qt::Drawer);
                message.setIconPixmap(QPixmap("../icon/Mail64px.png"));
                message.exec();
            }
        }
        else
        {
            QMessageBox message(QMessageBox::NoIcon, "Add friend", "添加失败，请检查address?");
            message.setWindowFlags(Qt::Drawer);
            message.setIconPixmap(QPixmap("../icon/Mail64px.png"));
            message.exec();
        }
    }
}

void addFriend::connectMYSQL()
{
    QString hostName = "106.12.68.247";
    QString dbName = "oubc";
    QString userName = "root";
    QString Passwd = "mysql1234";
    dbconn = QSqlDatabase::addDatabase("QMYSQL");
    dbconn.setHostName(hostName);
    dbconn.setDatabaseName(dbName);
    dbconn.setUserName(userName);
    dbconn.setPassword(Passwd);
    if (!dbconn.open())
    {
        QSqlError error = dbconn.lastError();
        qDebug() << error.text();
    }
}
