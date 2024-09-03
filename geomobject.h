#ifndef GEOMOBJECT_H
#define GEOMOBJECT_H

#include <QString>
#include <QPoint>
#include <QMap>
#include <QVector>
#include <Qt3DCore/QEntity>

enum class geometry {box, sphere, tube, cone, cylinder, triangle};

class GeomObject
{
public:
    GeomObject();
    GeomObject(const GeomObject &g);
    ~GeomObject();
    GeomObject(const QString &s);
    GeomObject &operator=(const GeomObject &g);
    virtual Qt3DCore::QEntity *toEntity(Qt3DCore::QEntity*);
    bool SetType(const QString &typ);
    void SetName(const QString &_name);
    QMap<QString, QVector<double>> &Properties();
    QVector<double> &Properties(const QString &prop);
private:
    QMap<QString, QVector<double>> properties;
    geometry type;
    QString name;

};


QVector< double > toFloatVector( const QStringList& aVector );

#endif // GEOMOBJECT_H
