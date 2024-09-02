#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Qt3DExtras/qforwardrenderer.h"
#include "qcamera.h"
#include "qscreen.h"
#include "qpointlight.h"

#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>

#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QConeMesh>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>

#include "geombox.h"


MainWindow::MainWindow(QWidget *parent)
    : Qt3DExtras::Qt3DWindow()
    , ui(new Ui::MainWindow)
{
    defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));
    //QWidget *container = QWidget::createWindowContainer(this);
    //QSize screenSize = this->screen()->size();
    //container->setMinimumSize(QSize(200, 100));
    //container->setMaximumSize(screenSize);
    // Root entity
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();

    // Camera
    Qt3DRender::QCamera *cameraEntity = camera();

    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(0, 0, 20.0f));
    cameraEntity->setUpVector(QVector3D(0, 1, 0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(cameraEntity->position());
    lightEntity->addComponent(lightTransform);

    Qt3DExtras::QTorusMesh *m_torus;
    Qt3DCore::QEntity *m_coneEntity;
    Qt3DCore::QEntity *m_cylinderEntity;
    Qt3DCore::QEntity *m_torusEntity;
    Qt3DCore::QEntity *m_cuboidEntity;
    Qt3DCore::QEntity *m_planeEntity;
    Qt3DCore::QEntity *m_sphereEntity;

    Qt3DExtras::QConeMesh *cone = new Qt3DExtras::QConeMesh();
    cone->setTopRadius(0.5);
    cone->setBottomRadius(1);
    cone->setLength(3);
    cone->setRings(50);
    cone->setSlices(20);

    // ConeMesh Transform
    Qt3DCore::QTransform *coneTransform = new Qt3DCore::QTransform();
    coneTransform->setScale(1.5f);
    coneTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 45.0f));
    coneTransform->setTranslation(QVector3D(0.0f, 4.0f, -1.5));

    Qt3DExtras::QPhongMaterial *coneMaterial = new Qt3DExtras::QPhongMaterial();
    coneMaterial->setDiffuse(QColor(QRgb(0x928327)));

    // Cone
    {
        m_coneEntity = new Qt3DCore::QEntity(rootEntity);
        m_coneEntity->addComponent(cone);
        m_coneEntity->addComponent(coneMaterial);
        m_coneEntity->addComponent(coneTransform);
    }

    GeomBox box1;
    box1.Properties()["size"].append(1);
    box1.Properties()["size"].append(2);
    box1.Properties()["size"].append(3);
    box1.Properties()["origin"].append(0.5);
    box1.Properties()["origin"].append(0);
    box1.Properties()["origin"].append(0);

    box1.toEntity(rootEntity);

    GeomBox box2;
    box2.Properties()["size"].append(3);
    box2.Properties()["size"].append(1);
    box2.Properties()["size"].append(2);
    box2.Properties()["origin"].append(1);
    box2.Properties()["origin"].append(2);
    box2.Properties()["origin"].append(3);

    box2.toEntity(rootEntity);

    GeomBox box3;
    box3.Properties()["size"].append(0.1);
    box3.Properties()["size"].append(0.1);
    box3.Properties()["size"].append(0.1);
    box3.Properties()["origin"].append(0);
    box3.Properties()["origin"].append(0);
    box3.Properties()["origin"].append(0);

    box3.toEntity(rootEntity);

    setRootEntity(rootEntity);
}

MainWindow::~MainWindow()
{
    delete ui;
}

