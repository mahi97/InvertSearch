#ifndef BASE_H
#define BASE_H



#include <QDebug>
#include <QString>
#include <QVector>
#include <QList>
#include <QMap>
#include <QByteArray>
#include <QTime>
#include <QColor>

// TODO : Add version control to base
#define REVNUM "phase 2.0.0 BETA"


#define Property(type,name,local) \
        public: inline type& get##name() {return local;} \
        public: inline void set##name(type val) {local = val;} \
        protected: type local

#define PropertyGet(type,name,local) \
        public: inline type& get##name() {return local;} \
        protected: type local


struct Data {

    Data() = default;
    Data(const Data& _other) {
        this->file = _other.file;
        this->key  = _other.key;
        this->lineNum = _other.lineNum;
        this->wordNum = _other.wordNum;
    }

    Data(const Data* _other) {
        if (_other == NULL) return;
        this->file = _other->file;
        this->key  = _other->key;
        this->lineNum = _other->lineNum;
        this->wordNum = _other->wordNum;
    }

    bool operator ==(const Data& _other) {
        if (this->file    == _other.file
        &&  this->key     == _other.key
        &&  this->lineNum == _other.lineNum
        &&  this->wordNum == _other.wordNum) {
            return true;
        } else {
            return false;
        }

    }

    QString key;
    QString file;
    unsigned int lineNum;
    unsigned int wordNum;

};

struct File {
    File() {
        del = false;
    }

    QString path;
    QString name;
    bool del;
};

struct Summery {
    QString treeName;
    int treeSize;
    int timeTakesToBuild;
    int wordsCount;
    int filesCount;
};

struct SearchResult {

    SearchResult() = default;
    SearchResult(QList<QList<Data> > _l, QStringList _w) {
        result.append(_l);
        words.append(_w);
    }

    QList<QList<Data> > result;
    QStringList words;
    int time;
};

struct ShowMaterial {

    ShowMaterial() {
        line = "";
        color = Qt::black;
    }

    ShowMaterial(QString _line, QColor _color)
        : line(_line),
          color(_color) {

    }

    QString line;
    QColor color;
};

#endif // BASE_H
