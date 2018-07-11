#include "box.h"


Box::Box(Qt3DCore::QEntity *root)
{

    // Cuboid shape data
    Qt3DExtras::QCuboidMesh *cuboid = new Qt3DExtras::QCuboidMesh();
    cuboid->setXExtent(1);
    cuboid->setYExtent(1);
    // CuboidMesh Transform
    cuboidTransform = new Qt3DCore::QTransform();
    cuboidTransform->setScale(3.0f);
    cuboidTransform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));

    Qt3DExtras::QPhongMaterial *cuboidMaterial = new Qt3DExtras::QPhongMaterial();
    cuboidMaterial->setDiffuse(QColor(QRgb(0x665423)));

    //Cuboid
    m_cuboidEntity = new Qt3DCore::QEntity(root);
    m_cuboidEntity->addComponent(cuboid);
    m_cuboidEntity->addComponent(cuboidMaterial);
    m_cuboidEntity->addComponent(cuboidTransform);

    connect(cuboidTransform,&Qt3DCore::QTransform::rotationChanged,this,&Box::PrintLog);
}

void Box::PrintLog()
{

        qDebug()<<cuboidTransform->rotationX() <<" "<<cuboidTransform->rotationY()<<" "<<cuboidTransform->rotationZ();

}
