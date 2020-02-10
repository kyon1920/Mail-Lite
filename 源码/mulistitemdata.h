#ifndef MULISTITEMDATA_H
#define MULISTITEMDATA_H

#include <QMetaType>
#include <QString>

typedef struct {
    QString iconPath;
    QString userName;
    QString address;
} MuItemData;

Q_DECLARE_METATYPE(MuItemData)

#endif // MULISTITEMDATA_H
