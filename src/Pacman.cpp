#include <Pacman.h>
#include <QProcess>
#include <PacmanPackageFromList.h>
#include <QStringList>
#include <exception>
#include <string>

Pacman::Pacman(QObject *parent)
    : QObject{parent}
{}

Pacman* Pacman::instance() {
    static Pacman p;
    return &p;
}

void Pacman::resetPackageList() {
    for (auto package : allPackages) {
        delete package;
    }
    allPackages.clear();
}

void Pacman::loadAllPackages() {
    resetPackageList();

    QProcess process;
    process.start("pacman", QStringList() << "-Ss");
    process.waitForFinished();

    QString stderr = QString::fromUtf8(process.readAllStandardError());

    if (process.exitCode() != 0) {
        throw std::runtime_error("Can't get packages for some reason: " + stderr.toUtf8().toStdString());
    }

    QString stdout = QString::fromUtf8(process.readAllStandardOutput());

    QStringList pacmanOutput = stdout.split("\n");

    for (int line = 0; line < pacmanOutput.length() - 2; line += 2) {
        QStringList mainInfoLine = pacmanOutput[line].split(" ");
        QString description = pacmanOutput[line + 1].trimmed();

        QStringList originAndName = mainInfoLine[0].split("/");
        if (originAndName[0] == "") {
            line -= 1;
            continue;
        }
        PacmanPackageFromList *package = new PacmanPackageFromList();

        package->origin = originAndName[0];
        package->name = originAndName[1];
        package->version = mainInfoLine[1];

        if (originAndName.length() > 2) {
            bool isInstalled = mainInfoLine[0].contains("[installed]");
            package->installed = isInstalled;
        }

        package->description = description;

        if (pacmanOutput[line].contains('(')) {
            package->packageGroup = pacmanOutput[line].split('(')[1].split(")")[0];
        }

        allPackages.push_back(package);
    }
}

QList<PacmanPackageFromList*> Pacman::getAllPackages() {
    return allPackages;
}
