#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include <IconProvider.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QIcon appIcon = QIcon::fromTheme(QStringLiteral("plasmadiscover"));

    if (!appIcon.isNull()) {
        app.setWindowIcon(appIcon);
    }

    QQuickStyle::setStyle(QStringLiteral("org.kde.desktop"));

    QQmlApplicationEngine engine;
    engine.addImageProvider(QStringLiteral("icon"), new IconProvider());

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Kpacman", "Main");

    return app.exec();
}
