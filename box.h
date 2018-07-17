#ifndef BOX_H
#define BOX_H

#include <Qt3DCore/QEntity>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DCore/QTransform>
#include <QPhongMaterial>
#include <Qt3DRender/QMesh>
#include <QUrl>
#include <Qt3DExtras/QPhongMaterial>

class Box : public QObject
{
    Q_OBJECT
public:
    explicit Box(Qt3DCore::QEntity *root);
     Qt3DExtras::QCuboidMesh *cuboid;
signals:

public slots:
    void PrintLog();
    void onCubicPositionChange();
private:
    Qt3DCore::QEntity *m_cuboidEntity;
    Qt3DCore::QTransform *cuboidTransform;
    Qt3DRender::QMesh *canMesh;
    Qt3DCore::QEntity *canEntity;
    Qt3DCore::QTransform *canTranform;
};

#endif // BOX_H
