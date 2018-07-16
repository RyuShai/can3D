#include "box.h"

#include <QUrl>
Box::Box(Qt3DCore::QEntity *root)
{

    // Cuboid shape data
    Qt3DExtras::QCuboidMesh *cuboid = new Qt3DExtras::QCuboidMesh();
    cuboid->setXExtent(3);
    cuboid->setYExtent(1);
    cuboid->setZExtent(1);
    // CuboidMesh Transform
    cuboidTransform = new Qt3DCore::QTransform();
//    cuboidTransform->setScale(3.0f);
    cuboidTransform->setTranslation(QVector3D(-2.05f, 0.5f, 1.45f));
    cuboidTransform->setRotationY(-10);

    Qt3DExtras::QPhongMaterial *cuboidMaterial = new Qt3DExtras::QPhongMaterial();
    cuboidMaterial->setDiffuse(QColor(132,37,147));



    //////////////////////
    canMesh = new Qt3DRender::QMesh(root);
    canMesh->setSource(QUrl::fromLocalFile("/home/ryu/Documents/Project/Qt/can3D/Can_3D.obj"));

    Qt3DExtras::QPhongMaterial *canMaterial = new Qt3DExtras::QPhongMaterial();
    canMaterial->setDiffuse(QColor(57,82,72));


    // CuboidMesh Transform
    canTranform = new Qt3DCore::QTransform();
    canTranform->setScale(0.01f);
    canTranform->setTranslation(QVector3D(0.0f, -2.0f, 0.0f));
    canTranform->setRotationY(-5);

    canEntity = new Qt3DCore::QEntity(root);
    canEntity->addComponent(canMesh);
    canEntity->addComponent(canMaterial);
    canEntity->addComponent(canTranform);

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
