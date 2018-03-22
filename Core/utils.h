#ifndef UTILS_H
#define UTILS_H

#include <QString>

#define QStrToCStr(str) \
    ((char*)((str).toStdString().c_str()))

#endif // UTILS_H
