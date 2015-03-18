#ifndef LIBSERIALCTRL_GLOBAL_H
#define LIBSERIALCTRL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBSERIALCTRL_LIBRARY)
#  define LIBSERIALCTRLSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBSERIALCTRLSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBSERIALCTRL_GLOBAL_H