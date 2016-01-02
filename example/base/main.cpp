#include "../../include/serialization.h"
#include <QDebug>

class employee{

public:
    employee(QString const& name=""):name_(name){}
    void add_tag(QString const& tag){ tags_.insert(tag); }
    void info() const {
        qDebug()<<"name:"<<name_;
        qDebug()<<"tags:"<<tags_;
    }
private:
    QString name_;
    QSet<QString> tags_;

    friend QJsonObject _Serialize2Json(employee const& e);
    friend employee _Unserialize4String(QJsonValue const& json, employee const& type_traits);
};

inline QJsonObject _Serialize2Json(employee const& e) {
    QJsonObject obj;
    obj["tags"] = serialization::_Serialize2Json(e.tags_);
    obj["name"] = e.name_;
    return obj;
}

inline employee _Unserialize4String(QJsonValue const& json, employee const& type_traits) {
    QJsonObject obj = json.toObject();
    employee e(obj["name"].toString());
    e.tags_ = serialization::_Unserialize4String(obj["tags"], QSet<QString>());
    return e;
}

class employer{
public:
    employer(QString const& name=""):name_(name){}
    void add_employee(employee const& e){ employees_.append(e);}
    void info() const {
        qDebug()<<"name:"<<name_;
        for(const employee &e:employees_) {
            e.info();
        }
    }

private:
    QVector<employee> employees_;
    QString name_;

    friend QJsonObject _Serialize2Json(employer const& e);
    friend employer _Unserialize4String(QJsonValue const& json, employer const& type_traits);
};

inline QJsonObject _Serialize2Json(employer const& e) {
    QJsonObject obj;
    obj["emplyees"] = serialization::_Serialize2Json(e.employees_);
    obj["name"] = e.name_;
    return obj;
}

inline employer _Unserialize4String(QJsonValue const& json, employer const& type_traits) {
    QJsonObject obj = json.toObject();
    employer e(obj["name"].toString());
    e.employees_ = serialization::_Unserialize4String(obj["emplyees"], QVector<employee>());
    return e;
}

int main(int argc, char *argv[])
{
    employee Mike("Mike"), Jack("Jack");
    Mike.add_tag("man");
    Jack.add_tag("engineer");
    employer Miles("Miles");
    Miles.add_employee(Mike);
    Miles.add_employee(Jack);
    QJsonDocument doc = serialization::Serialize2Json(Miles);
    QByteArray bytes = doc.toJson(QJsonDocument::Compact);
    qDebug()<<bytes;
    employer er = serialization::Unserialize4String<employer>(bytes);
    er.info();

}
