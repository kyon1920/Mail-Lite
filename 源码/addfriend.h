#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QWidget>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"

namespace Ui {
class addFriend;
}

class addFriend : public QWidget
{
    Q_OBJECT

public:
    explicit addFriend(QWidget *parent = nullptr);
    ~addFriend();

    void connectMYSQL();

private slots:
    void on_pushButton_clicked();

public slots:
    void receive_a_signal1(QString recv_msg);

private:
    Ui::addFriend *ui;
    QString username;
    QSqlDatabase dbconn;
};

#endif // ADDFRIEND_H
