#include "geomobject.h"

GeomObject::GeomObject()
{

}

GeomObject::GeomObject(const GeomObject &g)
{
    properties = g.properties;
    type = g.type;
    name = g.name;
}
GeomObject::~GeomObject()
{

}
GeomObject::GeomObject(const QString &s)
{
    QStringList Props = s.split(";");
    for (unsigned int i=0; i<Props.size(); i++)
    {

        QString argument = Props[i].split("=")[0];
        if (argument.toLower() == "type")
            SetType(Props[i].split("=")[1]);
        else if (argument.toLower() == "name")
            SetName(Props[i].split("=")[1]);
        else
        {
            QVector<double> value = toFloatVector(Props[i].split("=")[1].split(","));
            properties.insert(argument,value);
        }
    }
}
GeomObject &GeomObject::operator=(const GeomObject &g)
{
    properties = g.properties;
    type = g.type;
    name = g.name;
}
Qt3DCore::QEntity *GeomObject::toEntity(Qt3DCore::QEntity*)
{
    return nullptr;
}

QMap<QString, QVector<double>> &GeomObject::Properties()
{
    return properties;
}


QVector<double> &GeomObject::Properties(const QString &prop)
{
    if (properties.count(prop)==1)
        return properties[prop];
    else
    {   QVector<double> m;
        return m;
    }
}


bool GeomObject::SetType(const QString &typ)
{
    bool out = true;
    if (typ.toLower()=="box")
        type = geometry::box;
    else if (typ.toLower()=="sphere")
        type = geometry::sphere;
    else if (typ.toLower()=="tube")
        type = geometry::tube;
    else if (typ.toLower()=="cone")
        type = geometry::cone;
    else
        out = false;
    return out;
}
void GeomObject::SetName(const QString &_name)
{
    name = _name;
}


QVector< double > toFloatVector( const QStringList& aVector )
{
    QVector<double> vector;
    for (const QString& item : aVector )
    {
        bool ok = true;
        const double value = item.toDouble(&ok);
        if ( ok )
        {
            vector << value;
        }

    }
    return vector;
}
