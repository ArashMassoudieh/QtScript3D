#ifndef TRIANGLEGEOMETRYRENDERER_H
#define TRIANGLEGEOMETRYRENDERER_H

#include <QGeometryRenderer>
#include <QBuffer>
#include <QByteArray>
#include <QVector3D>
#include <QVector>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QGeometry>
#include <QIODevice>
#include <QNode>
#include <Qt3DCore/QAttribute>


class TriangleGeometryRenderer : public Qt3DRender::QGeometryRenderer {
public:
    TriangleGeometryRenderer(QNode *parent = nullptr) : QGeometryRenderer(parent) {
        initializeGeometry();
    }

    ~TriangleGeometryRenderer() {
        // Cleanup if necessary
    }

protected:
    void initializeGeometry() {
        // Example: Creating a simple triangle

        // Define vertex positions
        QVector<QVector3D> vertices;
        vertices << QVector3D(0.0f, 1.0f, 0.0f)
                 << QVector3D(-1.0f, -1.0f, 0.0f)
                 << QVector3D(1.0f, -1.0f, 0.0f);

        // Create a buffer and fill it with the vertex data
        Qt3DCore::QBuffer *vertexBuffer = new Qt3DCore::QBuffer(this);
        //vertexBuffer->setData(reinterpret_cast<const char*>(vertices.constData()), vertices.size() * sizeof(QVector3D));
        //vertexBuffer->open(QIODevice::ReadOnly);

        // Create geometry and set the buffer as its vertex data
        Qt3DCore::QGeometry *geometry = new Qt3DCore::QGeometry(this);
        Qt3DCore::QAttribute *positionAttribute = new Qt3DCore::QAttribute;
        positionAttribute->setName(Qt3DCore::QAttribute::defaultPositionAttributeName());
        positionAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
        positionAttribute->setVertexSize(3);
        positionAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
        positionAttribute->setBuffer(vertexBuffer);
        positionAttribute->setByteOffset(0);
        positionAttribute->setByteStride(3 * sizeof(float));
        positionAttribute->setCount(vertices.size());

        geometry->addAttribute(positionAttribute); // Add the position attribute to the geometry

        // Set the geometry to this renderer
        setGeometry(geometry);
        setPrimitiveType(QGeometryRenderer::Triangles);
    }
};


#endif // TRIANGLEGEOMETRYRENDERER_H
