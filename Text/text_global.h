#ifndef TEXT_GLOBAL_H
#define TEXT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TEXT_LIBRARY)
#  define TEXTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TEXTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // TEXT_GLOBAL_H
