#ifndef GRAMMARSTRINGLIST_H
#define GRAMMARSTRINGLIST_H

#include <QStringList>

class GrammarStringList : public QStringList
{
public:
    GrammarStringList();
    bool operator!=(const QStringList &other);
};

#endif //GRAMMARSTRINGLIST_H
