#include "IconProvider.h"


QPixmap IconProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    int width = requestedSize.width() > 0 ? requestedSize.width() : 22;
    int height = requestedSize.height() > 0 ? requestedSize.height() : 22;

    QIcon icon = QIcon::fromTheme(id);
    QPixmap pixmap = icon.pixmap(QSize(width, height));

    if (size)
        *size = QSize(width, height);

    return pixmap;
}
