#include "axbopenglwidget.h"

unsigned int VAO;
unsigned int VBO;
unsigned int EBO;

//unsigned int shaderProgram;


float vertices[]=
{
    //纹理坐标超过1.0f
    0.9f,0.9f,0.0f, 1.0f,0.0f,0.0f, 2.0f,2.0f, //top right
    0.9f,-0.9f,0.0f, 0.0f,1.0f,0.0f, 2.0f,-1.0f,//bottom right
    -0.9f,-0.9f,0.0f, 0.0f,0.0f,1.0f, -1.0f,-1.0f,//bottom left
    -0.9f,0.9f,0.0f, 0.5f,0.5f,0.5f, -1.0f,2.0f//top left
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

    //两个纹理加载
    textureWall = new QOpenGLTexture(QImage(":/pics/tex.png").mirrored());
    texturePhoto = new QOpenGLTexture(QImage(":/pics/photo.png").mirrored());
    textureSmall = new QOpenGLTexture(QImage(":/pics/small.png").mirrored());
    //BIND很重要
    shaderProgram.bind();
    shaderProgram.setUniformValue("textureWall",0);
    shaderProgram.setUniformValue("texturePhoto",1);
    shaderProgram.setUniformValue("textureSmall",2);

}

void AXBOpenGLWidget::resizeGL(int w, int h)
{

}

void AXBOpenGLWidget::paintGL()
{
    //如果没有initializeOpenGLFunctions()，程序会异常结束，缺少glad功能，为空指针
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //变量要放在这里，不能放在switch里
    float borderColor[] = {1.0f,1.0f,0.0f,1.0f};

    shaderProgram.bind();
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

            //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
            glTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_BORDER_COLOR, borderColor);

            glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,NULL);
            break;
        default:
            break;
    }

}
