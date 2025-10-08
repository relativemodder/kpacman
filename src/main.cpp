#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include <IconProvider.h>
#include <Pacman.h>
#include <Appstream.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setDesktopFileName(APP_ID);

    QIcon appIcon = QIcon::fromTheme("plasmadiscover");

    if (!appIcon.isNull()) {
        app.setWindowIcon(appIcon);
    }

    QQuickStyle::setStyle("org.kde.desktop");

    QQmlApplicationEngine engine;
    engine.addImageProvider("icon", new IconProvider());

    Pacman::instance()->loadAllPackages();
    Appstream::instance()->loadAppstreamData();

    for (auto archPackage : Pacman::instance()->getInstalledPackages()) {
        auto component = Appstream::instance()->findComponentByPackage(archPackage->name);
        if (component == nullptr) continue;
        qDebug() << component->name << ", installed by package " << component->package << ", icon is " << component->icon;
    }

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Kpacman", "Main");

    return app.exec();
}
