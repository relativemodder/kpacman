#ifndef APPSTREAM_H
#define APPSTREAM_H

#include <QObject>
#include <QList>
#include <QMap>
#include <AppstreamComponent.h>

class Appstream : public QObject
{
    Q_OBJECT
public:
    explicit Appstream(QObject *parent = nullptr);
    static Appstream* instance();
    AppstreamComponent* findComponentByPackage(QString packageName);
    void loadAppstreamData();

private:
    void parseXmlFile(const QString& filePath);
    void resetComponents();
    QMap<QString, AppstreamComponent*> m_components;
};

#endif // APPSTREAM_H
