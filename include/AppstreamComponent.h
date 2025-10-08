#ifndef APPSTREAMCOMPONENT_H
#define APPSTREAMCOMPONENT_H

#include <QObject>
#include <QString>

class AppstreamComponent : public QObject
{
public:
    explicit AppstreamComponent(QObject *parent = nullptr);
public:
    QString id;
    QString name;
    QString summary;
    QString package;
    QString icon;
    QString launchable;
};

#endif // APPSTREAMCOMPONENT_H
