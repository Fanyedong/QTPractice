#ifndef AXBOPENGLWIDGET_H
#define AXBOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

class AXBOpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit AXBOpenGLWidget(QWidget *parent = nullptr);
    ~AXBOpenGLWidget();

    enum Shape
    {
        None,
        Rect,
        Circle,
        Triangle
    };
    void drawShape(Shape shape);
    void setWireFrame(bool wireframe);

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

private:
    Shape m_shape;

signals:

};

#endif // AXBOPENGLWIDGET_H
