#include "axbopenglwidget.h"

unsigned int VAO;
unsigned int VBO;
unsigned int EBO;

//引入颜色
float vertices[]=
{
    0.5f,0.5f,0.0f,1.0f,0.0f,0.0f,
    0.5f,-0.5f,0.0f,0.0f,1.0f,0.0f,
    -0.5f,-0.5f,0.0f,0.0f,0.0f,1.0f,
    -0.5f,0.5f,0.0f,0.5f,0.5f,0.5f
};

unsigned int indices[]=
{
    0,1,3,
    1,2,3
};

AXBOpenGLWidget::AXBOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    timer.start(50);
    connect(&timer,SIGNAL(timeout()),this,SLOT(on_timeout()));
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
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),0);
    glEnableVertexAttribArray(1);

    bool success;
    //shaderProgram.addShaderFromSourceCode(QOpenGLShader::Vertex,vertexShaderSource);
    //shaderProgram.addShaderFromSourceCode(QOpenGLShader::Fragment,fragmentShaderSource);
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/shapes.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/shapes.frag");
    success = shaderProgram.link();
    if(!success)
        qDebug()<<"ERR: "<<shaderProgram.log();
}

void AXBOpenGLWidget::resizeGL(int w, int h)
{

}

void AXBOpenGLWidget::paintGL()
{
    //如果没有initializeOpenGLFunctions()，程序会异常结束，缺少glad功能，为空指针
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //glUseProgram(shaderProgram);
    shaderProgram.bind();

    //glBindVertexArray(VAO);

    switch(m_shape)
    {
        case Rect:
            glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,NULL);
            break;
        default:
            break;
    }

}

#include <QTime>
#include <QtMath>
void AXBOpenGLWidget::on_timeout()
{
    makeCurrent();
    int timeValue = QTime::currentTime().msec();
    float greenValue = (sin(timeValue)/2.0f)+0.5f;
    qDebug()<<greenValue;
    shaderProgram.setUniformValue("ourColor",0.0f,greenValue,0.0f,1.0f);
    doneCurrent();
    update();
}
