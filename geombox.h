#ifndef GEOMBOX_H
#define GEOMBOX_H

#include "geomobject.h"

class GeomBox: public GeomObject
{
public:
    GeomBox();
    GeomBox(const GeomBox &g);
    ~GeomBox();
    GeomBox(const QString &s);
    GeomBox &operator=(const GeomBox &g);
    Qt3DCore::QEntity *toEntity(Qt3DCore::QEntity*) override;
};

#endif // GEOMBOX_H
