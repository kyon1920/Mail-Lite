#ifndef WIDGET_H
#define WIDGET_H

#include "login.h"
#include "muitemdelegate.h"
#include "mulistitemdata.h"
#include "addfriend.h"

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QDateTime>
#include <QPainter>
#include <QMovie>
#include <QDebug>
#include <QToolButton>
#include <QStyle>
#include <QPixmap>
#include <QIcon>
#include <QMouseEvent>
#include <QPushButton>
#include <QBitmap>
#include <QPen>
#include <QBrush>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QTcpSocket>
#include <QStringList>
#include <QThread>
#include <QIcon>
#include <QMessageBox>
#include <QTextDocumentFragment>
#include <QFile>
#include <QFileDialog>
#include <QDate>
#include <QUdpSocket>
#include <QHostAddress>
#include <QMap>
#include <QTcpServer>
#include <QFileInfo>
#include <QWidget>
#include <QPainter>
#include <QMovie>
#include <QDebug>
#include <QToolButton>
#include <QStyle>
#include <QPushButton>
#include <QBitmap>
#include <QPropertyAnimation>
#include <QFile>
#include <QSql>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStandardItemModel>
#include <QListWidget>
#include <QListView>
#include <QMetaType>
#include <QModelIndex>
#include <ctime>
#include <QThread>
#include <QMetaType>
#include <QTimer>

#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void setWindow();
    void TikTok();
    void windowclosed();
    void windowmin();
    void mouseMoveEvent(QMouseEvent* mEvent);
    void mousePressEvent(QMouseEvent* mEvent);

    void mainShow();
    void connectMYSQL();
    void listFriends();

    void dealTime();

private slots:
    void on_pushButton_clicked();

    void on_newText_clicked();

    void on_cancel_clicked();

    void on_newMail_clicked();

    void on_head_clicked();

    void on_p0exit_clicked();

    void on_p0modify_clicked();

    void on_MailPeople_clicked();


    void on_recv_clicked();

    void on_send_clicked();

    void on_sendsuggestion_clicked();

    void on_recvBox_clicked();

    void on_p2recv_clicked();

    void on_p2return_clicked();

    void on_p2noread_clicked();

    void on_newMail_2_clicked();

public slots:
    //定义接收Dialog窗口发来信号的槽函数
    void receive_a_signal(QString recv_msg);

    void itemClicked(const QModelIndex &index);
    void itemClicked1(const QModelIndex &index);

signals:
    void send_a_signal1(QString send_msg);

private:
    Ui::Widget *ui;
    QPoint dragPosition;
    Login *login;
    addFriend *addfriend;
    QString username;
    QString name;
    QSqlDatabase dbconn;
    QStandardItem *pItem;
    QStandardItemModel *pModel = new QStandardItemModel();
    QString clickName;
    QString clickName2;
    QString content;
    QTimer *time;
};

#endif // WIDGET_H
