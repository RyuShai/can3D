#include "box.h"


Box::Box(Qt3DCore::QEntity *root)
{

    // Cuboid shape data
    cuboid = new Qt3DExtras::QCuboidMesh();

    // CuboidMesh Transform
    cuboidTransform = new Qt3DCore::QTransform();
//    cuboidTransform->setScale(3.0f);
//    cuboidTransform->setTranslation(QVector3D(0.8f, 0.4f, 0.8f));
    cuboid->setXExtent(4.5);
    cuboid->setYExtent(7.5);
    cuboid->setZExtent(2);
    cuboidTransform->setTranslation(QVector3D(0.85+(cuboid->xExtent()-1)*0.5,1.5+(cuboid->yExtent()-1)*0.5, 0.8+(cuboid->zExtent()-1)*0.5));
    connect(cuboid,&Qt3DExtras::QCuboidMesh::xExtentChanged,this,&Box::onCubicPositionChange);
    connect(cuboid,&Qt3DExtras::QCuboidMesh::yExtentChanged,this,&Box::onCubicPositionChange);
    connect(cuboid,&Qt3DExtras::QCuboidMesh::zExtentChanged,this,&Box::onCubicPositionChange);
//    cuboidTransform->setRotationY(-0);
    //1-1.4,2-2.0,3-2.6,5-3.5

    Qt3DExtras::QPhongMaterial *cuboidMaterial = new Qt3DExtras::QPhongMaterial();
    cuboidMaterial->setDiffuse(QColor(132,37,147));



    //////////////////////
    canMesh = new Qt3DRender::QMesh(root);
    canMesh->setSource(QUrl::fromLocalFile("/home/ryu/Documents/Project/Qt/can3D/Can_3D.obj"));

    Qt3DExtras::QPhongMaterial *canMaterial = new Qt3DExtras::QPhongMaterial();
    canMaterial->setDiffuse(QColor(57,82,72));


    // CuboidMesh Transform
    canTranform = new Qt3DCore::QTransform();
    canTranform->setScale(0.011f);
    canTranform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));
//    canTranform->setRotationY(0);

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

void Box::onCubicPositionChange()
{
    qDebug()<<"extent:"<<cuboid->xExtent() <<" "<<cuboid->yExtent()<<" "<<cuboid->zExtent();
    cuboidTransform->setTranslation(QVector3D(0.85+(cuboid->xExtent()-1)*0.5,1.5+(cuboid->yExtent()-1)*0.5, 0.8+(cuboid->zExtent()-1)*0.5));
}
