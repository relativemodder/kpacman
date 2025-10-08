#ifndef PACMANPACKAGEFROMLIST_H
#define PACMANPACKAGEFROMLIST_H

#include <QObject>
#include <QString>
#include <QList>

class PacmanPackageFromList : public QObject
{
    Q_OBJECT
public:
    explicit PacmanPackageFromList(QObject *parent = nullptr);

public:
    QString name;
    QString origin;
    bool installed;
    QString packageGroup;
    QString description;
    QString version;
    QString installedVersion;
};

#endif // PACMANPACKAGEFROMLIST_H
