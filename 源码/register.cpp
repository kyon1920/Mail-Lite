#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    setWindow();
}

Register::~Register()
{
    delete ui;
}

void Register::setWindow()
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

    ui -> icon -> setPixmap(QPixmap("../icon/Mail128px.png"));
    ui -> background -> setPixmap(QPixmap("../picture/1.jpg"));

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

    connect(closeButton, &QPushButton::pressed, this, &Register::windowclosed);
    connect(minButton, &QPushButton::pressed, this, &Register::windowmin);

    // 自定义注册按钮
    QString btnStyle1 =
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
    ui -> username -> setStyleSheet("background:transparent;border-left-width:0;"
                            "border-right-width:0;border-top-width:0;border-bottom:#666 2px solid;");
    ui -> password -> setStyleSheet("background:transparent;border-left-width:0;"
                                "border-right-width:0;border-top-width:0;border-bottom:#666 2px solid;");
    ui -> password1 -> setStyleSheet("background:transparent;border-left-width:0;"
                                "border-right-width:0;border-top-width:0;border-bottom:#666 2px solid;");
    ui -> address -> setStyleSheet("background:transparent;border-left-width:0;"
                                "border-right-width:0;border-top-width:0;border-bottom:#666 2px solid;");
    ui -> sure -> setStyleSheet(btnStyle1);
    ui -> password -> setEchoMode(QLineEdit::Password);
    ui -> password1 -> setEchoMode(QLineEdit::Password);

}
void Register::windowclosed()
{
    this -> close();
}
void Register::windowmin()
{
    this->showMinimized();
}
void Register::mousePressEvent(QMouseEvent* mEvent)
{
    if(mEvent->button()==Qt::LeftButton)
    {
        dragPosition = mEvent->globalPos()-frameGeometry().topLeft();
        mEvent->accept();
    }
}
void Register::mouseMoveEvent(QMouseEvent* mEvent)
{
    if(mEvent->buttons()& Qt::LeftButton)
    {
        move(mEvent->globalPos() - dragPosition);
        mEvent->accept();
    }
}

void Register::connectMYSQL()
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


void Register::on_sure_clicked()
{
    QRegExp regUser("^[A-Za-z0-9\u4e00-\u9fa5]+@[a-zA-Z0-9_-]+(\\.[a-zA-Z0-9_-]+)+$");
    QRegExp regPass("^[a-zA-Z]\\w{5,17}$");

    connectMYSQL();
    ui -> tips -> setText("请稍候 ...");
    QString address =ui -> address -> text();
    QString username = ui -> username -> text();
    QString passwd = ui -> password -> text();
    QString passwd1 = ui -> password1 -> text();

    if (address == "" || passwd == "" || passwd1 == "" || passwd != passwd1)
        ui -> tips -> setText("填写信息不完整~");
    else if (regUser.indexIn(address) != 0 || regPass.indexIn(passwd) != 0)
        ui -> tips -> setText("信息不符合规范，请重新填写~");
    else
    {
        QString se = QString("select name from user where address='%1'").arg(address);
        QSqlQuery sql_query;
        if(!sql_query.exec(se))
        {
            cout << sql_query.lastError();
        }
        else
        {
            if(sql_query.next())
                ui -> tips -> setText("该用户已存在~");
            else
            {
                QString se1 = QString("insert into user values('%1', '%2', '%3')").arg(address).arg(username).arg(passwd);
                QSqlQuery sql_query1;
                if(!sql_query.exec(se1))
                {
                    cout << sql_query1.lastError();
                }
                else
                    ui -> tips -> setText("注册成功，快去登录吧~");
            }
        }
    }
}
