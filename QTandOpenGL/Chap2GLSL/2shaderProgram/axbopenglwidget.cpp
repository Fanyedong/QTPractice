#include "axbopenglwidget.h"

unsigned int VAO;
unsigned int VBO;
unsigned int EBO;

//unsigned int shaderProgram;


float vertices[]=
{
    0.5f,0.5f,0.0f,
    0.5f,-0.5f,0.0f,
    -0.5f,-0.5f,0.0f,
    -0.5f,0.5f,0.0f
};

unsigned int indices[]=
{
    0,1,3,
    1,2,3
};

//着色器未进行封装
//const char *vertexShaderSource = "#version 330 core\n"
//        "layout (location = 0) in vec3 aPos;\n"
//        "void main()\n"
//        "{\n"
//        "gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
//        "}\0";

//const char *fragmentShaderSource = "#version 330 core\n"
//        "out vec4 FragColor;\n"
//        "void main()\n"
//        "{\n"
//        "FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
//        "}\n\0";

AXBOpenGLWidget::AXBOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

AXBOpenGLWidget::~AXBOpenGLWidget()
{
    makeCurrent();
    glDeleteBuffers(1,&VBO);
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&EBO);
    //glDeleteProgram(shaderProgram);
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

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),0);
    glEnableVertexAttribArray(0);

    //此部分着色器的编译相对繁琐
//    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
//    glCompileShader(vertexShader);

//    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
//    glCompileShader(fragmentShader);

//    shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram,vertexShader);
//    glAttachShader(shaderProgram,fragmentShader);
//    glLinkProgram(shaderProgram);

//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);

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
