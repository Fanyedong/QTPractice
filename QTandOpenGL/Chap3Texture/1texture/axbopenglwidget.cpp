#include "axbopenglwidget.h"

unsigned int VAO;
unsigned int VBO;
unsigned int EBO;

//unsigned int shaderProgram;


float vertices[]=
{
    0.5f,0.5f,0.0f, 1.0f,0.0f,0.0f, 1.0f,1.0f, //top right
    0.5f,-0.5f,0.0f, 0.0f,1.0f,0.0f, 1.0f,0.0f,//bottom right
    -0.5f,-0.5f,0.0f, 0.0f,0.0f,1.0f, 0.0f,0.0f,//bottom left
    -0.5f,0.5f,0.0f, 0.5f,0.5f,0.5f, 0.0f,1.0f//top left
};

unsigned int indices[]=
{
    0,1,3,
    1,2,3
};



AXBOpenGLWidget::AXBOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

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

    textureWall = new QOpenGLTexture(QImage(":/pics/tex.png").mirrored());

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    //开两个属性
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    //注意最后一位指针的值
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    //颜色
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);


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

    shaderProgram.bind();
    switch(m_shape)
    {
        case Rect:
            textureWall->bind(0);
            glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,NULL);
            break;
        default:
            break;
    }

}
