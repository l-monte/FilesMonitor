#ifndef MONITORDEFS_H
#define MONITORDEFS_H

#include <QHash>

using FileNameToWasChangedMap = QHash<QString, bool>;
using AllFilesMap = QHash<QString, bool>;

#endif // MONITORDEFS_H
