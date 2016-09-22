#include "grammar.h"

Grammar::Grammar() {}

void Grammar::setListN(const QStringList &listN)
{
    if (_listN != listN) {
        _listN.clear();
        _listN << listN;
        isDefinitionChanged = true;
        _start = 0;
    }
}

void Grammar::setListT(const QStringList &listT)
{
    if (_listT != listT) {
        _listT.clear();
        _listT << listT;
        isDefinitionChanged = true;
    }
}

void Grammar::setListP(const QStringList &listP)
{
    if (_listP != listP) {
        _listP.clear();
        _listP << listP;
        isDefinitionChanged = true;
    }
}

void Grammar::setStart(int start)
{
    if (start < _listN.size()) {
        _start = start;
    } else {
        _start = 0;
    }
}

bool Grammar::isDefinitionIncomplete()
{
    return _listN.isEmpty() || QString(_listN[0]).isEmpty() || _listT.isEmpty() || QString(_listT[0]).isEmpty() || _listP.isEmpty() || QString(_listP[0]).isEmpty();
}

void Grammar::setRules()
{
    if (isDefinitionChanged) {
        rules.clear();
        for (int i = 0, l = _listN.size(); i < l; i++) {
            QStringList list;
            rules << list;
        }
        foreach (QString s, _listP) {
            QStringList list = s.split(QRegExp("->"));
            int index = _listN.indexOf(list[0]);
            if (list.size() > 1 && index != -1) {
                list = list[1].split(QRegExp("[|]"));
                foreach (QString r, list) {
                    rules[index] << r;
                }
            }
        }
    }
}

QString Grammar::getRandomWord(int limit)
{
    QString result, word = _listN[_start];
    QStringList symbolsN;
    symbolsN << word;
    while (!symbolsN.isEmpty()) {
        result += word + " -> ";
        QString wordNew, symbol = symbolsN.takeFirst();
        int index = _listN.indexOf(symbol);
        QStringList transformation = QString(rules[index][qrand() % rules[index].size()]).split("&");
        foreach (QString s, transformation) {
            if (_listN.contains(s)) {
                symbolsN << s;
                wordNew += s + ' ';
            } else if (_listT.contains(s)) {
                wordNew += s + ' ';
            }
        }
        wordNew.chop(1);
        int symbolIndex = word.indexOf(symbol);
        wordNew = word.left(symbolIndex) + wordNew + word.right(word.size() - symbolIndex - symbol.size());
        result += wordNew + '\n';
        word = wordNew;
        if (result.size() > limit) {
            return result + "==========\nThe output length is too high!\n";
        }
    }
    result.chop(1);
    return result;
}
