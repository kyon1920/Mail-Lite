#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <QMouseEvent>
#include <QToolButton>
#include <QMovie>
#include <QBitmap>
#include <QPoint>
#include <QPainter>
#include <QStyle>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

    void setWindow();
    void windowclosed();
    void windowmin();
    void mousePressEvent(QMouseEvent* mEvent);
    void mouseMoveEvent(QMouseEvent* mEvent);
    void connectMYSQL();

private slots:
    void on_sure_clicked();

private:
    Ui::Register *ui;
    QPoint dragPosition;
    QSqlDatabase dbconn;
};

#endif // REGISTER_H
