#ifndef PACMANPACKAGEFROMLIST_H
#define PACMANPACKAGEFROMLIST_H

#include <QObject>
#include <QString>
#include <QList>

class PacmanPackageFromList : public QObject
{
public:
    explicit PacmanPackageFromList(QObject *parent = nullptr);

public:
    QString name;
    QString origin;
    QString packageGroup;
    QString description;
    QString version;

public:
    uint installed;
};

#endif // PACMANPACKAGEFROMLIST_H
