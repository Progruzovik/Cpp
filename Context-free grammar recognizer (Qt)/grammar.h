#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <QVector>
#include "grammarstringlist.h"

class Grammar
{
public:
    Grammar();
    void setListN(const QStringList &listN);
    void setListT(const QStringList &listT);
    void setListP(const QStringList &listP);
    void setStart(int start);
    bool isDefinitionIncomplete();
    void setRules();
    QString getRandomWord(int limit = 100000);

private:
    GrammarStringList _listN;
    GrammarStringList _listT;
    GrammarStringList _listP;
    bool isDefinitionChanged = true;
    int _start = 0;
    QVector<QStringList> rules;
};

#endif // GRAMMAR_H
