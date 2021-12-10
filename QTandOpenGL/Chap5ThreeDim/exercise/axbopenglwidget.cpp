#include "axbopenglwidget.h"

unsigned int VAO;
unsigned int VBO;
unsigned int EBO;

//unsigned int shaderProgram;


float vertices[]=
{
        -0.5f,-0.5f,-0.5f, 0.0f,0.0f,
        0.5f,-0.5f,-0.5f, 1.0f,0.0f,
        0.5f,0.5f,-0.5f, 1.0f,1.0f,
        0.5f,0.5f,-0.5f, 1.0f,1.0f,
        -0.5f,0.5f,-0.5f, 0.0f,1.0f,
        -0.5f,-0.5f,-0.5f, 0.0f,0.0f,

        -0.5f,-0.5f,0.5f, 0.0f,0.0f,
        0.5f,-0.5f,0.5f, 1.0f,0.0f,
        0.5f,0.5f,0.5f, 1.0f,1.0f,
        0.5f,0.5f,0.5f, 1.0f,1.0f,
        -0.5f,0.5f,0.5f, 0.0f,1.0f,
        -0.5f,-0.5f,0.5f, 0.0f,0.0f,

        -0.5f,0.5f,0.5f, 1.0f,1.0f,
        -0.5f,0.5f,-0.5f, 1.0f,0.0f,
        -0.5f,-0.5f,-0.5f, 0.0f,0.0f,
        -0.5f,-0.5f,-0.5f, 0.0f,0.0f,
        -0.5f,-0.5f,0.5f, 0.0f,1.0f,
        -0.5f,0.5f,0.5f, 1.0f,1.0f,

        0.5f,0.5f,0.5f, 1.0f,1.0f,
        0.5f,0.5f,-0.5f, 1.0f,0.0f,
        0.5f,-0.5f,-0.5f, 0.0f,0.0f,
        0.5f,-0.5f,-0.5f, 0.0f,0.0f,
        0.5f,-0.5f,0.5f, 0.0f,1.0f,
        0.5f,0.5f,0.5f, 1.0f,1.0f,

        -0.5f,-0.5f,-0.5f, 0.0f,0.0f,
        0.5f,-0.5f,-0.5f, 1.0f,0.0f,
        0.5f,-0.5f,0.5f, 1.0f,1.0f,
        0.5f,-0.5f,0.5f, 1.0f,1.0f,
        -0.5f,-0.5f,0.5f, 0.0f,1.0f,
        -0.5f,-0.5f,-0.5f, 0.0f,0.0f,

        -0.5f,0.5f,-0.5f, 0.0f,0.0f,
        0.5f,0.5f,-0.5f, 1.0f,0.0f,
        0.5f,0.5f,0.5f, 1.0f,1.0f,
        0.5f,0.5f,0.5f, 1.0f,1.0f,
        -0.5f,0.5f,0.5f, 0.0f,1.0f,
        -0.5f,0.5f,-0.5f, 0.0f,0.0f,
};

QVector<QVector3D>cubePositions=
{
    QVector3D(0.0f,0.0f,0.0f),
    QVector3D(2.0f,5.0f,-15.0f),
    QVector3D(-1.5f,-2.2f,-2.5f),
    QVector3D(-3.8f,-2.0f,-12.3f),
    QVector3D(2.4f,-0.4f,-3.5f),
    QVector3D(-1.7f,3.0f,-7.5f),
    QVector3D(1.3f,-2.0f,-2.5f),
    QVector3D(1.5f,2.0f,-2.5f),
    QVector3D(1.5f,0.2f,-1.5f),
    QVector3D(-1.3f,1.0f,-1.5f)
};

unsigned int indices[]=
{
    0,1,3,
    1,2,3
};

float ratio = 0.5;

AXBOpenGLWidget::AXBOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    connect(&timer,SIGNAL(timeout()),this,SLOT(on_timeout()));
    timer.start(100);
}

AXBOpenGLWidget::~AXBOpenGLWidget()
{
    makeCurrent();
    glDeleteBuffers(1,&VBO);
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&EBO);
    doneCurrent();
}

void AXBOpenGLWidget::drawShape(AXBOpenGLWidget::Shape shape)
{
    m_shape = shape;
    update();
}

void AXBOpenGLWidget::setWireFrame(bool wireframe)
{
    makeCurrent();
    if(wireframe)
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    doneCurrent();
    update();
}

void AXBOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    //开两个属性
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    //注意最后一位指针的值
//    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
//    glEnableVertexAttribArray(1);

    //颜色
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    bool success;
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/shapes.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/shapes.frag");
    success = shaderProgram.link();
    if(!success)
        qDebug()<<"ERR: "<<shaderProgram.log();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    //两个纹理加载
    textureWall = new QOpenGLTexture(QImage(":/pics/tex.png").mirrored());
    texturePhoto = new QOpenGLTexture(QImage(":/pics/photo.png").mirrored());
    textureSmall = new QOpenGLTexture(QImage(":/pics/sit.png").mirrored());
    //BIND很重要
    shaderProgram.bind();
    shaderProgram.setUniformValue("textureWall",0);
    shaderProgram.setUniformValue("texturePhoto",1);
    shaderProgram.setUniformValue("textureSmall",2);

    QMatrix4x4 projection;
    projection.perspective(45,(float)width()/height(),0.1,100);
    shaderProgram.setUniformValue("projection",projection);

    //生成mipmap
    //textureSmall->generateMipMaps();

    textureSmall->bind(2);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
}

void AXBOpenGLWidget::resizeGL(int w, int h)
{

}

void AXBOpenGLWidget::paintGL()
{
    QMatrix4x4 model;
    QMatrix4x4 view;
    QMatrix4x4 projection;

    model.rotate(-45,1.0f,0.0f,0.0f);
    view.translate(-3.0,0.0,-3);
    projection.perspective(60,(float)width()/height(),0.1,100);
    //projection.perspective(60,(float)width()/(2*height()),0.1,100);
    //glViewport(0,0,width()/2,height());
    shaderProgram.setUniformValue("projection",projection);

    unsigned int time = QTime::currentTime().msec();

    //如果没有initializeOpenGLFunctions()，程序会异常结束，缺少glad功能，为空指针
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    //glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram.bind();
    //shaderProgram.setUniformValue("ratio",ratio);

    int i=0;

    switch(m_shape)
    {
        case Rect:
            //默认激活的是0，其他的手动需要激活
            //glActiveTexture(GL_TEXTURE0);
            textureWall->bind(0);
            glActiveTexture(GL_TEXTURE1);
            texturePhoto->bind(1);
            glActiveTexture(GL_TEXTURE2);
            textureSmall->bind(2);
            //第一个偏移旋转
            //shaderProgram.setUniformValue("theMatrix",matrix);
            shaderProgram.setUniformValue("model",model);
            shaderProgram.setUniformValue("view",view);
            //shaderProgram.setUniformValue("projection",projection);
            //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,NULL);


            foreach (auto item, cubePositions)
            {
                //注意清零
                model.setToIdentity();
                model.translate(item);
                if(i%3==0)
                    model.rotate(time,1.0f,5.0f,0.5f);
                shaderProgram.setUniformValue("model",model);
                glDrawArrays(GL_TRIANGLES,0,36);
                i++;
            }

            break;
        default:
            break;
    }
}

#include <QKeyEvent>
void AXBOpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Up:
        ratio+=0.1;
        break;
    case Qt::Key_Down:
        ratio-=0.1;
        break;
    case Qt::Key_0:
        ratio=0;
        break;
    default:
        break;
    }
    if(ratio>1) ratio =1;
    if(ratio<0) ratio=0;

    makeCurrent();
    shaderProgram.bind();
    shaderProgram.setUniformValue("ratio",ratio);
    update();
    doneCurrent();
    qDebug()<<ratio;
}

void AXBOpenGLWidget::on_timeout()
{
    update();
}


