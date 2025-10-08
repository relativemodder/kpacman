#include "Appstream.h"
#include <QProcess>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QXmlStreamReader>
#include <QLocale>
#include <zlib.h>

Appstream::Appstream(QObject *parent)
    : QObject{parent}
{}

Appstream* Appstream::instance()
{
    static Appstream a;
    return &a;
}

AppstreamComponent* Appstream::findComponentByPackage(QString packageName)
{
    return m_components.value(packageName, nullptr);
}

void Appstream::loadAppstreamData()
{
    QDir catalogDir("/usr/share/swcatalog/xml/");

    if (!catalogDir.exists()) {
        qWarning() << "AppStream catalog directory does not exist:" << catalogDir.path();
        throw std::runtime_error("AppStream catalog directory does not exist.");
    }

    QStringList filters;
    filters << "*.xml.gz";
    QFileInfoList files = catalogDir.entryInfoList(filters, QDir::Files);

    qDebug() << "Found" << files.count() << "AppStream catalog files";

    for (const QFileInfo& fileInfo : files) {
        parseXmlFile(fileInfo.absoluteFilePath());
    }

    qDebug() << "Loaded" << m_components.count() << "AppStream components";
}

void Appstream::parseXmlFile(const QString& filePath)
{
    gzFile gzfile = gzopen(filePath.toUtf8().constData(), "rb");

    if (!gzfile) {
        qWarning() << "Failed to open gzip file:" << filePath;
        throw std::runtime_error("Failed to open gzip file.");
    }

    QFileInfo fileInfo(filePath);
    qint64 compressedSize = fileInfo.size();

    if (compressedSize <= 0) {
        qWarning() << "Invalid file size:" << filePath;
        gzclose(gzfile);
        throw std::runtime_error("Invalid file size.");
    }

    qint64 estimatedSize = compressedSize * 7;

    qDebug() << "Reading" << filePath << "compressed size:" << compressedSize
             << "bytes, estimated uncompressed:" << estimatedSize << "bytes";

    QByteArray xmlData;
    xmlData.reserve(estimatedSize);

    QVector<char> buffer(compressedSize);
    int bytesRead;

    while ((bytesRead = gzread(gzfile, buffer.data(), buffer.size())) > 0) {
        xmlData.append(buffer.data(), bytesRead);
    }

    gzclose(gzfile);

    if (xmlData.isEmpty()) {
        qWarning() << "Empty data after decompression:" << filePath;
        throw std::runtime_error("Empty data after decompression.");
    }

    qDebug() << "Actual uncompressed size:" << xmlData.size() << "bytes";

    QXmlStreamReader xml(xmlData);

    QLocale userLocale = QLocale::system();
    QString userLang = userLocale.name();
    QString userLangShort = userLocale.language() == QLocale::C ? "en" : userLocale.bcp47Name().split('-').first();

    qDebug() << "User locale:" << userLang << "Short:" << userLangShort;

    AppstreamComponent* currentComponent = nullptr;
    QString currentElement;
    bool insideDeveloper = false;

    QMap<QString, QString> names;
    QMap<QString, QString> summaries;

    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement()) {
            currentElement = xml.name().toString();

            if (currentElement == "component") {
                currentComponent = new AppstreamComponent(this);
                insideDeveloper = false;
                names.clear();
                summaries.clear();
            }
            else if (currentElement == "developer") {
                insideDeveloper = true;
            }
            else if (currentComponent && !insideDeveloper) {
                if (currentElement == "id") {
                    currentComponent->id = xml.readElementText();
                }
                else if (currentElement == "name") {
                    QString lang = xml.attributes().value("xml:lang").toString();
                    QString value = xml.readElementText();

                    if (lang.isEmpty()) {
                        names["default"] = value;
                    } else {
                        names[lang] = value;
                    }
                }
                else if (currentElement == "summary") {
                    QString lang = xml.attributes().value("xml:lang").toString();
                    QString value = xml.readElementText();

                    if (lang.isEmpty()) {
                        summaries["default"] = value;
                    } else {
                        summaries[lang] = value;
                    }
                }
                else if (currentElement == "pkgname") {
                    currentComponent->package = xml.readElementText();
                }
                else if (currentElement == "launchable") {
                    currentComponent->launchable = xml.readElementText();
                }
                else if (currentElement == "icon") {
                    QString type = xml.attributes().value("type").toString();
                    QString iconValue = xml.readElementText();

                    if (currentComponent->icon.isEmpty() || type == "cached") {
                        currentComponent->icon = iconValue;
                    }
                }
            }
        }
        else if (xml.isEndElement()) {
            if (xml.name() == "developer") {
                insideDeveloper = false;
            }
            else if (xml.name() == "component") {
                if (currentComponent) {
                    if (names.contains(userLang)) {
                        currentComponent->name = names[userLang];
                    } else if (names.contains(userLangShort)) {
                        currentComponent->name = names[userLangShort];
                    } else if (names.contains("en")) {
                        currentComponent->name = names["en"];
                    } else if (names.contains("default")) {
                        currentComponent->name = names["default"];
                    } else if (!names.isEmpty()) {
                        currentComponent->name = names.first();
                    }

                    if (summaries.contains(userLang)) {
                        currentComponent->summary = summaries[userLang];
                    } else if (summaries.contains(userLangShort)) {
                        currentComponent->summary = summaries[userLangShort];
                    } else if (summaries.contains("en")) {
                        currentComponent->summary = summaries["en"];
                    } else if (summaries.contains("default")) {
                        currentComponent->summary = summaries["default"];
                    } else if (!summaries.isEmpty()) {
                        currentComponent->summary = summaries.first();
                    }

                    if (!currentComponent->package.isEmpty()) {
                        m_components.insert(currentComponent->package, currentComponent);
                    } else {
                        delete currentComponent;
                    }
                }
                currentComponent = nullptr;
                names.clear();
                summaries.clear();
            }
        }
    }

    delete currentComponent;

    if (xml.hasError()) {
        qWarning() << "XML parsing error in" << filePath << ":" << xml.errorString();
    }
}
