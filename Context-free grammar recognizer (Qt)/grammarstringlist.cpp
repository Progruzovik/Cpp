#include "grammarstringlist.h"

GrammarStringList::GrammarStringList() : QStringList() {}

bool GrammarStringList::operator!=(const QStringList &other)
{
    int l = this->size();
    if (l != other.size()) {
        return true;
    }
    for (int i = 0; i < l; i++) {
        if (this->at(i) != other.at(i)) {
            return true;
        }
    }
    return false;
}
