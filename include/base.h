#ifndef BASE_H
#define BASE_H



#include <QDebug>
#include <QString>
#include <QVector>
#include <QList>
#include <QMap>
#include <QByteArray>
#include <QTime>


// TODO : Add version control to base
#define REVNUM "nightly"


#define Property(type,name,local) \
        public: inline type& get##name() {return local;} \
        public: inline void set##name(type val) {local = val;} \
        protected: type local

#define PropertyGet(type,name,local) \
        public: inline type& get##name() {return local;} \
        protected: type local


struct Data {
    QString key;
    QString file;
    unsigned int lineNum;
    unsigned int wordNum;
};

struct File {
    QString path;
    QString name;
};

struct Summery {
    QString treeName;
    int treeSize;
    int timeTakesToBuild;
    int wordsCount;
    int filesCount;
};

#endif // BASE_H
