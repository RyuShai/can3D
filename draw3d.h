#ifndef DRAW3D_H
#define DRAW3D_H

#include <QOpenGLBuffer>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

class Draw3D :public QOpenGLWidget,  protected QOpenGLFunctions
{
    Q_OBJECT
public:
    Draw3D();
    virtual ~Draw3D();

    void DrawCubeGeometry(QOpenGLShaderProgram *program);
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initShaders();
    void initTextures();
private:
    void initCubeGeometry();
    QOpenGLShaderProgram program;
    QOpenGLTexture *texture;
    QMatrix4x4 projection;
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
};

#endif // DRAW3D_H
