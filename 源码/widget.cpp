#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    // 窗体
    setWindow();
    login = new Login;
    addfriend = new addFriend;
    login -> setWindowFlags(login->windowFlags() | Qt::WindowStaysOnTopHint);
    // 点击左边栏按钮实现页面切换
    ui -> page -> setCurrentIndex(0);
    connect(ui -> newMail, &QPushButton::released,this,[=](){ui -> page -> setCurrentIndex(0);});
    connect(ui -> head, &QPushButton::released,this,[=](){ui -> page -> setCurrentIndex(0);});
    connect(ui -> MailPeople, &QPushButton::released,this,[=](){ui -> page -> setCurrentIndex(1);});
    connect(ui -> recvBox, &QPushButton::released,this,[=](){ui -> page -> setCurrentIndex(2);});
    connect(ui -> about, &QPushButton::released,this,[=](){ui -> page -> setCurrentIndex(3);});
    connect(ui -> p2recv, &QPushButton::released,this,[=](){ui -> page -> setCurrentIndex(0);});
    connect(this,SIGNAL(send_a_signal1(QString)), addfriend, SLOT(receive_a_signal1(QString)));
    connect(ui -> listView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(itemClicked(const QModelIndex &)));
    connect(ui -> p2list, SIGNAL(clicked(const QModelIndex &)), this, SLOT(itemClicked1(const QModelIndex &)));

    time = new QTimer(this);
    connect(time, &QTimer::timeout, this, &Widget::dealTime);
}

Widget::~Widget()
{
    delete time;
    delete ui;
}

void Widget::setWindow()
{
    setWindowIcon(QIcon("../icon/Mail96px.ico"));

    setWindowTitle("Mail");
    // 设置窗体无边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    // 设置窗体背景透明
    // setAttribute(Qt::WA_TranslucentBackground);
    // 设置圆角窗口
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(), 8, 8);
    setMask(bmp);

    ui -> background -> setScaledContents(true);
    ui -> icon -> setPixmap(QPixmap("../icon/Mail96px.png"));
    //ui -> background -> setScaledContents(true);
    ui -> leftLabel -> setPixmap(QPixmap("../picture/0.jpeg"));
    QIcon myicon;
    myicon.addFile(tr("../icon/Mail96px.ico"));
    ui-> head -> setIcon(myicon);
    ui-> head -> setIconSize(QSize(100,100));
    ui -> icon -> setPixmap(QPixmap("../icon/Mail96px.png"));

    QMovie *myMovie = new QMovie("../动态/7.gif");
    ui -> p0h -> setMovie(myMovie);
    myMovie -> start();
    ui -> p0h -> setScaledContents(true);

    //resize(pi -> size());
    // 获取界面的宽度
    int wide = width();
    // 构建最小化、关闭按钮
    QToolButton *minButton = new QToolButton(this);
    QToolButton *closeButton= new QToolButton(this);
    // 获取最小化、关闭按钮图标
    QPixmap minPix  = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    // 设置最小化、关闭按钮
    minButton -> setIcon(minPix);
    closeButton -> setIcon(closePix);
    // 将最小化、关闭按钮放在界面的位置
    minButton->setGeometry(wide-65,7,20,20);
    closeButton->setGeometry(wide-35,7,20,20);
    // 设置鼠标移至按钮的提示信息
    minButton->setToolTip(tr("最小化"));
    closeButton->setToolTip(tr("关闭"));

    connect(closeButton, &QPushButton::pressed, this, &Widget::windowclosed);
    connect(minButton, &QPushButton::pressed, this, &Widget::windowmin);

    ui -> leftLabel -> hide();
    ui -> head -> hide();
    ui -> page -> hide();
    ui -> newMail -> hide();
    ui -> MailPeople -> hide();
    ui -> recvBox -> hide();
    ui -> about -> hide();
    ui -> number -> hide();
}
void Widget::windowclosed()
{
    time -> stop();
    delete addfriend;
    delete login;
    this -> close();
}
void Widget::windowmin()
{
    this->showMinimized();
}
void Widget::mousePressEvent(QMouseEvent* mEvent)
{
    if(mEvent->button()==Qt::LeftButton)
    {
        dragPosition = mEvent->globalPos()-frameGeometry().topLeft();
        mEvent->accept();
    }
}
void Widget::mouseMoveEvent(QMouseEvent* mEvent)
{
    if(mEvent->buttons()& Qt::LeftButton)
    {
        move(mEvent->globalPos() - dragPosition);
        mEvent->accept();
    }
}
void Widget::TikTok()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(500);
    animation->setKeyValueAt(0,QRect(QPoint(this->frameGeometry().x()-3,this->frameGeometry().y()),this->size()));
    animation->setKeyValueAt(0.1,QRect(QPoint(this->frameGeometry().x()+6,this->frameGeometry().y()),this->size()));
    animation->setKeyValueAt(0.2,QRect(QPoint(this->frameGeometry().x()-6,this->frameGeometry().y()),this->size()));
    animation->setKeyValueAt(0.3,QRect(QPoint(this->frameGeometry().x()+6,this->frameGeometry().y()),this->size()));
    animation->setKeyValueAt(0.4,QRect(QPoint(this->frameGeometry().x()-6,this->frameGeometry().y()),this->size()));
    animation->setKeyValueAt(0.5,QRect(QPoint(this->frameGeometry().x()+6,this->frameGeometry().y()),this->size()));
    animation->setKeyValueAt(0.6,QRect(QPoint(this->frameGeometry().x()-6,this->frameGeometry().y()),this->size()));
    animation->setKeyValueAt(0.7,QRect(QPoint(this->frameGeometry().x()+6,this->frameGeometry().y()),this->size()));
    animation->setKeyValueAt(0.8,QRect(QPoint(this->frameGeometry().x()-6,this->frameGeometry().y()),this->size()));
    animation->setKeyValueAt(0.9,QRect(QPoint(this->frameGeometry().x()+6,this->frameGeometry().y()),this->size()));
    animation->setKeyValueAt(1,QRect(QPoint(this->frameGeometry().x()-3,this->frameGeometry().y()),this->size()));
    animation->start();
}

void Widget::on_pushButton_clicked()
{
    //绑定子窗口向主窗口发送消息的信号与槽
    connect(login, SIGNAL(send_a_signal(QString)),this,SLOT(receive_a_signal(QString)));
    login -> show();
}
void Widget::receive_a_signal(QString recv_msg)
{
    // cout << recv_msg;
    username = recv_msg;

    mainShow();
    connectMYSQL();
    if (time -> isActive() == false)
    {
        time -> start(2000);
    }
}

void Widget::mainShow()
{
    ui -> pushButton -> hide();
    ui -> icon -> hide();
    ui -> label -> hide();
    ui -> leftLabel -> show();
    ui -> head -> show();
    ui -> page -> show();
    ui -> newMail -> show();
    ui -> MailPeople -> show();
    ui -> recvBox -> show();
    ui -> about -> show();

    ui -> MailRecv -> hide();
    ui -> theme -> hide();
    ui -> MailText -> hide();
    ui -> MailRecv0 -> hide();
    ui -> theme0 -> hide();
    ui -> MailText0 -> hide();
    ui -> send -> hide();
    ui -> newText -> hide();
    ui -> cancel -> hide();

    ui -> p0username -> hide();
    ui -> p0name -> hide();
    ui -> p0modify -> hide();
    ui -> p0exit -> hide();

    login -> close();
}

void Widget::on_newText_clicked()
{
    ui -> MailRecv -> clear();
    ui -> theme -> clear();
    ui -> MailText -> setText("你好:\n        ");
}

void Widget::on_cancel_clicked()
{
    ui -> MailRecv -> hide();
    ui -> theme -> hide();
    ui -> MailText -> hide();
    ui -> MailRecv0 -> hide();
    ui -> theme0 -> hide();
    ui -> MailText0 -> hide();
    ui -> send -> hide();
    ui -> newText -> hide();
    ui -> cancel -> hide();

    ui -> p0h -> show();
    ui -> p0L0 -> show();
    ui -> p0L1 -> show();
    ui -> p0L2 -> show();

    ui -> p0username -> hide();
    ui -> p0name -> hide();
    ui -> p0modify -> hide();
    ui -> p0exit -> hide();
}

void Widget::on_newMail_clicked()
{
    ui -> MailRecv -> show();
    ui -> theme -> show();
    ui -> MailText -> show();
    ui -> MailRecv0 -> show();
    ui -> theme0 -> show();
    ui -> MailText0 -> show();
    ui -> send -> show();
    ui -> newText -> show();
    ui -> cancel -> show();

    ui -> p0h -> hide();
    ui -> p0L0 -> hide();
    ui -> p0L1 -> hide();
    ui -> p0L2 -> hide();

    ui -> p0username -> hide();
    ui -> p0name -> hide();
    ui -> p0modify -> hide();
    ui -> p0exit -> hide();
}

void Widget::on_head_clicked()
{
    QString se = QString("select name from user where address='%1'").arg(username);
    QSqlQuery sql_query;
    if(!sql_query.exec(se))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        if(sql_query.next())
            name = sql_query.value(0).toString();
    }
    ui -> p0username -> setText(username);
    ui -> p0name -> setText(name);

    on_cancel_clicked();
    ui -> p0username -> show();
    ui -> p0name -> show();
    ui -> p0modify -> show();
    ui -> p0exit -> show();
}

void Widget::on_p0exit_clicked()
{
    this -> close();
}

void Widget::connectMYSQL()
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

void Widget::on_p0modify_clicked()
{
    login -> show();
}

void Widget::listFriends()
{
    int n = 0;
    pModel -> clear();
    MuItemData itemData;

    QString se = QString("select address2 from mail_list where address1='%1'").arg(username);
    QSqlQuery sql_query;
    if(!sql_query.exec(se))
    {
        cout << sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            pItem = new QStandardItem;
            QSqlQuery sql_query1;
            QString str = sql_query.value(0).toString();
            if(!sql_query1.exec(QString("select name from user where address='%1'").arg(str)))
            {
                cout <<sql_query.lastError();
            }
            else
            {
                if(sql_query1.next())
                    itemData.userName = sql_query1.value(0).toString();
            }
            itemData.address = sql_query.value(0).toString();
            n++;
            n = n % 9;
            switch(n)
            {
            case 0:
                itemData.iconPath = "../head/h0.jpg";
                break;
            case 1:
                itemData.iconPath = "../head/h1.jpg";
                break;
            case 2:
                itemData.iconPath = "../head/h2.jpg";
                break;
            case 3:
                itemData.iconPath = "../head/h3.jpg";
                break;
            case 4:
                itemData.iconPath = "../head/h4.jpg";
                break;
            case 5:
                itemData.iconPath = "../head/h5.jpg";
                break;
            case 6:
                itemData.iconPath = "../head/h6.jpg";
                break;
            case 7:
                itemData.iconPath = "../head/h7.jpg";
                break;
            case 8:
                itemData.iconPath = "../head/h8.jpg";
                break;
            }
            pItem -> setData(QVariant::fromValue(itemData), Qt::UserRole + 1);
            pModel -> appendRow(pItem);
        }
    }

    MuItemDelegate *pItemDelegate = new MuItemDelegate(this);
    ui-> listView -> setItemDelegate(pItemDelegate);
    ui-> listView -> setModel(pModel);

}

void Widget::itemClicked(const QModelIndex &index)
{
    ui -> p1Text -> show();
    ui -> p1Textsend -> show();
    ui -> recv -> show();
    ui -> p1L0 -> hide();

    QVariant var = index.data(Qt::UserRole+1);
    MuItemData itemData = var.value<MuItemData>();

    clickName = itemData.address;
    ui -> p1Text -> clear();
    ui -> p1Textsend -> clear();
    QString se = QString("select title, content, sender from mail where (receiver='%1' and sender='%2') or (sender='%3' and receiver='%4')").arg(username).arg(clickName).arg(username).arg(clickName);
    QSqlQuery sql_query;
    if(!sql_query.exec(se))
    {
        cout << sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            if (sql_query.value(2).toString() == username)
            {
                QString str = username + "(我): \nTitle: " + sql_query.value(0).toString() + "\nContent: " + sql_query.value(1).toString() + "\n\n";
                ui -> p1Text -> append(str);
            }
            else
            {
                QString str = clickName + ": \nTitle: " + sql_query.value(0).toString() + "\nContent: " + sql_query.value(1).toString() + "\n\n";
                ui -> p1Text -> append(str);
            }
        }
    }
}

void Widget::on_MailPeople_clicked()
{
    ui -> listView -> setFrameShape(QListWidget::NoFrame);
    listFriends();
    ui -> p1Text -> hide();
    ui -> p1Textsend -> hide();
    ui -> recv -> hide();
    ui -> p1L0 -> show();
}

void Widget::on_recv_clicked()
{
    QString str = username + "(我):\nTitle: 默认\nContent: " + ui -> p1Textsend -> toPlainText() + "\n\n";
    QString content = ui -> p1Textsend -> toPlainText();
    ui -> p1Text -> append(str);
    ui -> p1Textsend -> clear();
    QString se = QString("insert into mail(sender, receiver, title, content) values('%1', '%2', '默认', '%3')").arg(username).arg(clickName).arg(content);
    QSqlQuery sql_query;
    if(!sql_query.exec(se))
    {
        cout << sql_query.lastError();

        QMessageBox message(QMessageBox::NoIcon, "L-Mail", "发送失败，请重试~\t");
        message.setWindowFlags(Qt::Drawer);
        message.setIconPixmap(QPixmap("../icon/Mail64px.png"));
        message.exec();
    }
    else
    {
        QMessageBox message(QMessageBox::NoIcon, "L-Mail", "发送成功!\t");
        message.setWindowFlags(Qt::Drawer);
        message.setIconPixmap(QPixmap("../icon/Mail64px.png"));
        message.exec();
    }
}

void Widget::on_send_clicked()
{
    QString recv = ui -> MailRecv -> text();
    QString them = ui -> theme -> text();
    QString content = ui -> MailText -> toPlainText();

    if (them == "")
    {
        QMessageBox message(QMessageBox::Information, "L-Mail", "主题不能为空~\t");
        message.setWindowFlags(Qt::Drawer);
        message.setIconPixmap(QPixmap("../icon/Mail64px.png"));
        message.exec();
    }
    else
    {
        QString se1 = QString("select address from user where address='%1'").arg(recv);
        QSqlQuery sql_query1;
        if(!sql_query1.exec(se1))
        {
            cout << sql_query1.lastError();
            QMessageBox message(QMessageBox::Information, "l-Mail", "发送失败，请重试!\t");
            message.setWindowFlags(Qt::Drawer);
            message.setIconPixmap(QPixmap("../icon/Mail64px.png"));
            message.exec();
        }
        else if (!sql_query1.first())
        {
            QMessageBox message(QMessageBox::Information, "l-Mail", "您输入的邮箱不存在，请重新输入~");
            message.setWindowFlags(Qt::Drawer);
            message.setIconPixmap(QPixmap("../icon/Mail64px.png"));
            message.exec();
        }
        else
        {
            QString se = QString("insert into mail(sender, receiver, title, content) values('%1', '%2', '%3', '%4')").arg(username).arg(recv).arg(them).arg(content);
            QSqlQuery sql_query;
            if(!sql_query.exec(se))
            {
                cout << sql_query.lastError();
                QMessageBox message(QMessageBox::Information, "L-Mail", "发送失败，请重试!\t");
                message.setWindowFlags(Qt::Drawer);
                message.setIconPixmap(QPixmap("../icon/Mail64px.png"));
                message.exec();
            }
            else
            {
                QMessageBox message(QMessageBox::Information, "L-Mail", "发送成功!\t");
                message.setWindowFlags(Qt::Drawer);
                message.setIconPixmap(QPixmap("../icon/Mail64px.png"));
                message.exec();
            }
        }
    }
}

void Widget::on_sendsuggestion_clicked()
{
    QString them = "反馈";
    QString content = ui -> suggestion -> toPlainText();
    QString se = QString("insert into mail(sender, receiver, title, content) values('%1', oubc, '%2', '%3')").arg(username).arg(them).arg(content);
    QSqlQuery sql_query;
    if(!sql_query.exec(se))
    {
        cout << sql_query.lastError();
        QMessageBox message(QMessageBox::NoIcon, "L-Mail", "发送失败，请重试!\t");
        message.setWindowFlags(Qt::Drawer);
        message.setIconPixmap(QPixmap("../icon/Mail64px.png"));
        message.exec();
    }
    else
    {
        QMessageBox message(QMessageBox::NoIcon, "L-Mail", "我们已经收到您的反馈，谢谢");
        message.setWindowFlags(Qt::Drawer);
        message.setIconPixmap(QPixmap("../icon/Mail64px.png"));
        message.exec();
    }
}

void Widget::on_recvBox_clicked()
{
    int i = 0;
    ui -> p2list -> setFrameShape(QListWidget::NoFrame);
    ui -> p2list -> show();
    ui -> p2recvmessage -> hide();
    ui -> p2recv -> hide();
    ui -> p2return -> hide();
    ui -> p2noread -> hide();

    pModel -> clear();
    MuItemData itemData;

    QString se = QString("select sender, content from mail where receiver='%1' and `read`=0").arg(username);
    QSqlQuery sql_query;
    if(!sql_query.exec(se))
    {
        cout << sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            pItem = new QStandardItem;
            QString str = sql_query.value(0).toString();
            itemData.userName = sql_query.value(1).toString();

            itemData.address = sql_query.value(0).toString();
            itemData.iconPath = "../icon/未读96px.png";
            pItem -> setData(QVariant::fromValue(itemData), Qt::UserRole + 1);
            pModel -> appendRow(pItem);
            i ++;
        }
    }

    QString str1 = QString("当前未读邮件有 %1 封，赶快拆开它们吧~").arg(i);
    if (i != 0)
        ui -> p2message -> setText(str1);
    else
        ui -> p2message -> setText("当前没有未读邮件呢，下次再来吧~");

    QString se1 = QString("select sender, content from mail where receiver='%1' and `read`=1").arg(username);
    QSqlQuery sql_query1;
    if(!sql_query1.exec(se1))
    {
        cout << sql_query1.lastError();
    }
    else
    {
        while(sql_query1.next())
        {
            pItem = new QStandardItem;
            QString str = sql_query1.value(0).toString();
            itemData.userName = sql_query1.value(1).toString();

            itemData.address = sql_query1.value(0).toString();
            itemData.iconPath = "../icon/已读96px.png";
            pItem -> setData(QVariant::fromValue(itemData), Qt::UserRole + 1);
            pModel -> appendRow(pItem);
        }
    }

    MuItemDelegate *pItemDelegate = new MuItemDelegate(this);
    ui-> p2list -> setItemDelegate(pItemDelegate);
    ui-> p2list -> setModel(pModel);
}

void Widget::itemClicked1(const QModelIndex &index)
{
    ui -> p2recvmessage -> clear();
    ui -> p2list -> hide();
    ui -> p2recvmessage -> show();
    ui -> p2recv -> show();
    ui -> p2return -> show();
    ui -> p2noread -> show();

    QVariant var = index.data(Qt::UserRole+1);
    MuItemData itemData = var.value<MuItemData>();
    clickName2 = itemData.address;
    content = itemData.userName;

    QString se = QString("select title, content from mail where sender='%1' and receiver='%2'").arg(clickName2).arg(username);
    QSqlQuery sql_query;
    if(!sql_query.exec(se))
    {
        cout << sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            QString str = "Title: " + sql_query.value(0).toString() + "\n\nContent: " + sql_query.value(1).toString() + "\n\n";
            ui -> p2recvmessage -> append(str);
        }
    }

    se = QString("update mail set `read`=1 where sender='%1' and receiver='%2' and content='%3'").arg(clickName2).arg(username).arg(content);
    QSqlQuery sql_query1;
    if(!sql_query1.exec(se))
    {
        cout << sql_query1.lastError();
    }
}
void Widget::on_p2recv_clicked()
{
    ui -> MailRecv -> setText(clickName2);
    ui -> theme -> setText("回复");

    ui -> MailRecv -> show();
    ui -> theme -> show();
    ui -> MailText -> show();
    ui -> MailRecv0 -> show();
    ui -> theme0 -> show();
    ui -> MailText0 -> show();
    ui -> send -> show();
    ui -> newText -> show();
    ui -> cancel -> show();

    ui -> p0h -> hide();
    ui -> p0L0 -> hide();
    ui -> p0L1 -> hide();
    ui -> p0L2 -> hide();

    ui -> p0username -> hide();
    ui -> p0name -> hide();
    ui -> p0modify -> hide();
    ui -> p0exit -> hide();
}

void Widget::on_p2return_clicked()
{
    ui -> p2list -> show();
    ui -> p2recvmessage -> hide();
    ui -> p2recv -> hide();
    ui -> p2return -> hide();
    ui -> p2noread -> hide();
}

void Widget::on_p2noread_clicked()
{
    QString se = QString("update mail set `read`=0 where sender='%1' and receiver='%2' and content='%3'").arg(clickName2).arg(username).arg(content);
    QSqlQuery sql_query1;
    if(!sql_query1.exec(se))
    {
        cout << sql_query1.lastError();
    }
}

void Widget::on_newMail_2_clicked()
{
    emit send_a_signal1(username);
    addfriend -> show();
}

void Widget::dealTime()
{
    int n = 0;
    QString se = QString("select sender, content from mail where receiver='%1' and `read`=0").arg(username);
    QSqlQuery sql_query;
    if(!sql_query.exec(se))
    {
        cout << sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            n++;
        }
    }
    if (n == 0)
        ui -> number -> hide();
    else
    {
        ui -> number -> show();
        QString str = QString("当前未读邮件数量：%1").arg(n);
        ui -> number -> setText(str);
    }
}
