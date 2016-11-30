#ifndef BASE_H
#define BASE_H



#include <QDebug>
#include <QString>
#include <QVector>
#include <QList>
#include <QMap>


// TODO : Add version control to base
#define REVNUM "0.01"


#define Property(type,name,local) \
        public: inline type& get##name() {return local;} \
        public: inline void set##name(type val) {local = val;} \
        protected: type local

#define PropertyGet(type,name,local) \
        public: inline type& get##name() {return local;} \
        protected: type local


#endif // BASE_H
