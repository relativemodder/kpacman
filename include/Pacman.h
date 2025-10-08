#ifndef PACMAN_H
#define PACMAN_H

#include <QObject>
#include <QList>
#include <QString>
#include <PacmanPackageFromList.h>

class Pacman : public QObject
{
    Q_OBJECT
public:
    explicit Pacman(QObject *parent = nullptr);
    static Pacman* instance();

    QList<PacmanPackageFromList*> getAllPackages();
    QList<PacmanPackageFromList*> getInstalledPackages();

    void loadAllPackages();
    void resetPackageList();
signals:

private:
    QList<PacmanPackageFromList*> allPackages = {};
};

#endif // PACMAN_H
