#ifndef KPACMAND_GLOBAL_H
#define KPACMAND_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(KPACMAND_LIBRARY)
#define KPACMAND_EXPORT Q_DECL_EXPORT
#else
#define KPACMAND_EXPORT Q_DECL_IMPORT
#endif

#endif // KPACMAND_GLOBAL_H
