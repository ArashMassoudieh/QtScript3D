#include "geombox.h"
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DCore/qtransform.h>
#include <Qt3DExtras/QPhongMaterial>

GeomBox::GeomBox()
{

}


GeomBox::GeomBox(const GeomBox &g):GeomObject(g)
{

}
GeomBox::~GeomBox()
{

}
GeomBox::GeomBox(const QString &s):GeomObject(s)
{

}

GeomBox &GeomBox::operator=(const GeomBox &g)
{
    GeomObject::operator=(g);
}
Qt3DCore::QEntity* GeomBox::toEntity(Qt3DCore::QEntity* rootentity)
{
    Qt3DCore::QEntity *Box = new Qt3DCore::QEntity(rootentity);
    Qt3DExtras::QCuboidMesh *cuboid = new Qt3DExtras::QCuboidMesh();
    cuboid->setXExtent(Properties("size")[0]);
    cuboid->setYExtent(Properties("size")[1]);
    cuboid->setZExtent(Properties("size")[2]);
    // CuboidMesh Transform
    Qt3DCore::QTransform *cuboidTransform = new Qt3DCore::QTransform();

    cuboidTransform->setScale(1.0f);
    cuboidTransform->setTranslation(QVector3D(Properties("origin")[0],Properties("origin")[1],Properties("origin")[2] ));

    Qt3DExtras::QPhongMaterial *cuboidMaterial = new Qt3DExtras::QPhongMaterial();
    cuboidMaterial->setDiffuse(QColor(QRgb(0x665423)));

    Box->addComponent(cuboid);
    Box->addComponent(cuboidMaterial);
    Box->addComponent(cuboidTransform);

    return Box;

}
