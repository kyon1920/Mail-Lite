#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    setWindow();
    connectMYSQL();
    passwd = "";
    ui -> user -> setStyleSheet("background:transparent;border-left-width:0;border-right-width:0;border-top-width:0;border-bottom:#666 2px solid;");
    ui -> password -> setStyleSheet("background:transparent;border-left-width:0;border-right-width:0;border-top-width:0;border-bottom:#666 2px solid;");
}

Login::~Login()
{
    delete ui;
}

void Login::setWindow()
{
    setWindowTitle("Login");
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
    p.drawRoundedRect(bmp.rect(),8,8);
    setMask(bmp);

    QMovie *myMovie = new QMovie("../动态/login.gif");
    // 设置动画
    ui -> background -> setMovie(myMovie);
    // 启动动画
    myMovie -> start();
    ui -> background -> setScaledContents(true);
    ui -> icon -> setPixmap(QPixmap("../icon/Mail48px.png"));

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
    closeButton->setGeometry(wide-35,10,20,20);
    // 设置鼠标移至按钮的提示信息
    minButton->setToolTip(tr("最小化"));
    closeButton->setToolTip(tr("关闭"));
    // 设置最小化、关闭按钮风格
    minButton->setStyleSheet("background-color:transparent;");
    closeButton->setStyleSheet("background-color:transparent;");

    connect(closeButton, &QPushButton::pressed, this, &Login::windowclosed);
    connect(minButton, &QPushButton::pressed, this, &Login::windowmin);

    // 自定义注册按钮
    QString btnStyle1 = "\
            QPushButton{\
                color: rgb(255, 0, 0);\
                border:1px;\
            }\
            QPushButton:hover{\
                color: rgb(38, 133, 227);\
            }\
            QPushButton:pressed{\
                color: rgb(255, 0, 0);\
            }";
    ui -> registered -> setStyleSheet(btnStyle1);
    // 自定义登录按钮
    QString btnStyle2 =
            "QPushButton{\
                color: rgb(255, 255, 0);\
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(4,186,251), stop:0.3 rgb(4,186,251), stop:1 rgb(4,186,251));\
                border:1px;\
                border-radius:5px; /*border-radius控制圆角大小*/\
                padding:2px 4px;  \
            }\
            QPushButton:hover{\
                color: rgb(255, 255, 255); \
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(4,186,251), stop:0.3 rgb(4,186,251), stop:1 rgb(4,186,251));\
                border:1px;  \
                border-radius:5px; /*border-radius控制圆角大小*/\
                padding:2px 4px; \
            }\
            QPushButton:pressed{    \
                color: rgb(255, 255, 0); \
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(0,0,200), stop:0.3 rgb(0,0,230), stop:1 rgb(0,0,255));  \
                border:1px;  \
                border-radius:5px; /*border-radius控制圆角大小*/\
                padding:2px 4px; \
            }";
    ui -> sure -> setStyleSheet(btnStyle2);
    // 设置密码模式
    ui -> password -> setEchoMode(QLineEdit::Password);
    ui -> user -> setStyleSheet("background:transparent;border-left-width:0;"
                                "border-right-width:0;border-top-width:0;border-bottom:#666 2px solid;");
    ui -> password -> setStyleSheet("background:transparent;border-left-width:0;"
                                    "border-right-width:0;border-top-width:0;border-bottom:#666 2px solid;");
    ui -> user -> setPlaceholderText("XXX@lightmail.com");
}
void Login::windowclosed()
{
    this->close();
}
void Login::windowmin()
{
    this->showMinimized();
}
void Login::mousePressEvent(QMouseEvent* mEvent)
{
    if(mEvent->button()==Qt::LeftButton)
    {
        dragPosition = mEvent->globalPos()-frameGeometry().topLeft();
        mEvent->accept();
    }
}
void Login::mouseMoveEvent(QMouseEvent* mEvent)
{
    if(mEvent->buttons()& Qt::LeftButton)
    {
        move(mEvent->globalPos() - dragPosition);
        mEvent->accept();
    }
}
void Login::TikTok()
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

void Login::on_sure_clicked()
{
    username = ui -> user -> text();
    password = ui -> password -> text();

    QString se = QString("select password from user where address='%1'").arg(username);
    QSqlQuery sql_query;
    sql_query.exec(se);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        if(sql_query.next())
            passwd = sql_query.value(0).toString();
    }

    if (username == nullptr || password == nullptr || password != passwd)
        TikTok();
    //if (username == nullptr)
        //TikTok();
    else
    {

        emit send_a_signal(ui->user->text());

        dbconn.close();
    }
}
void Login::on_registered_clicked()
{
    // dbconn.close();
    this -> close();
    r.show();
    // QDesktopServices::openUrl(QUrl(QLatin1String("https://www.baidu.com/")));
}

void Login::connectMYSQL()
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
