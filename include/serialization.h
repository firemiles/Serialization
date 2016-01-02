#ifndef SERIALIZATION_H
#define SERIALIZATION_H


#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtCore/QMap>
#include <QtCore/QSet>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <assert.h>

namespace serialization {

inline int _Serialize2Json(int i) {
    return i;
}

inline QString _Serialize2Json(QString const& str) {
    return str;
}

template<typename T>
QJsonArray _Serialize2Json(const QSet<T>& set);
template<typename T1, typename T2>
QJsonObject _Serialize2Json(const QMap<T1, T2>& m);
template<typename T>
QJsonArray _Serialize2Json(const QVector<T>& v);

template<typename T>
QJsonArray _Serialize2Json(const QVector<T>& v) {
    QJsonArray array;
    for(const T &t:v){
        array.push_back(_Serialize2Json(t));
    }
    return array;
}

template<typename T>
QJsonArray _Serialize2Json(const QSet<T>& set) {
    QJsonArray array;
    for(const T &t:set){
        array.push_back(_Serialize2Json(t));
    }
    return array;
}

template<typename T1, typename T2>
QJsonObject _Serialize2Json(const QMap<T1, T2>& m) {
    QJsonObject parent;
    for(T1 &key:m.keys()){
        parent.insert(QString::number(key), _Serialize2Json(m.value(key)));
    }
    return parent;
}



template<typename T1, typename T2>
QMap<T1, T2> _Unserialize4String(QJsonValue const& json, QMap<T1, T2> const& type_traits);
template<typename T>
QSet<T> _Unserialize4String(QJsonValue const& json, QSet<T> const& type_traits);
template<typename T>
QVector<T> _Unserialize4String(QJsonValue const& json, QVector<T> const& type_traits);

inline int _Unserialize4String(QJsonValue const& json, int) {
    return json.toInt();
}

inline int _Unserialize4String(QJsonValue const& json, short) {
    return json.toInt();
}

inline int _Unserialize4String(QJsonValue const& json, char) {
    return json.toInt();
}

inline int _Unserialize4String(QJsonValue const& json, unsigned char) {
    return json.toInt();
}

inline QString _Unserialize4String(QJsonValue const& json, QString const&) {
    return json.toString();
}

inline int _Unserialize4String(QString const& json, int) {
    return json.toInt();
}

inline int _Unserialize4String(QString const& json, short) {
    return json.toInt();
}

inline int _Unserialize4String(QString const& json, char) {
    return json.toInt();
}

inline int _Unserialize4String(QString const& json, unsigned char) {
    return json.toInt();
}

inline QString _Unserialize4String(QString const& json, QString const&) {
    return json;
}

template<typename T>
QVector<T> _Unserialize4String(QJsonValue const& json, QVector<T> const&) {
    QVector<T> v;
    QJsonArray li = json.toArray();
    for(auto l:li){
        v.push_back(_Unserialize4String(l, T()));
    }
    return v;

}

template<typename T1, typename T2>
QMap<T1, T2> _Unserialize4String(QJsonValue const& json, QMap<T1, T2> const&) {
    QMap<T1, T2> m;
    QJsonObject ma = json.toObject();
    for(QString &key:ma.keys()) {
        m.insert(_Unserialize4String(key, T1()), _Unserialize4String(ma[key], T2()));
    }
    return m;
}

template<typename T>
QSet<T> _Unserialize4String(QJsonValue const& json, QSet<T> const&) {
    QSet<T> set;
    QJsonArray array = json.toArray();
    for(auto a:array) {
        set.insert(_Unserialize4String(a, T()));
    }
    return set;
}


template<typename T>
QJsonDocument Serialize2Json(T const& t) {
    return QJsonDocument(_Serialize2Json(t));
}

template<typename T>
inline T Unserialize4String(QByteArray const& bytes) {
    QJsonDocument doc = QJsonDocument::fromJson(bytes);
    if(doc.isArray())
        return _Unserialize4String(QJsonValue(doc.array()), T());
    else if(doc.isObject())
        return _Unserialize4String(QJsonValue(doc.object()), T());
    else if(doc.isEmpty())
        return T();
    else
        assert(0);
}

}

#endif // SERIALIZATION_H
