#ifndef BOX_H
#define BOX_H

#include <Qt3DCore/QEntity>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DCore/QTransform>
#include <QPhongMaterial>
#include <Qt3DRender/QMesh>

class Box : public QObject
{
    Q_OBJECT
public:
    explicit Box(Qt3DCore::QEntity *root);

signals:

public slots:
    void PrintLog();
private:
    Qt3DCore::QEntity *m_cuboidEntity;
    Qt3DCore::QTransform *cuboidTransform;
    Qt3DRender::QMesh *canMesh;
    Qt3DCore::QEntity *canEntity;
    Qt3DCore::QTransform *canTranform;
};

#endif // BOX_H
