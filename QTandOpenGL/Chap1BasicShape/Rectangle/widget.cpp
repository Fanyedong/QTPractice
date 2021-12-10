#include "widget.h"

unsigned int VAO;
unsigned int VBO;
unsigned int EBO;

unsigned int shaderProgram;

//高开销方式：
//float vertices[]=
//{
//    0.5f,0.5f,0.0f,
//    0.5f,-0.5f,0.0f,
//    -0.5f,0.5f,0.0f,

//    0.5f,-0.5f,0.0f,
//    -0.5f,-0.5f,0.0f,
//    -0.5f,0.5f,0.0f
//};

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

const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
        "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
        "}\n\0";


Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{

}

Widget::~Widget()
{
}

void Widget::initializeGL()
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

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

//    glBindBuffer(GL_ARRAY_BUFFER,0);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
//    glBindVertexArray(0);

    //用线条填充
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

}

void Widget::resizeGL(int w, int h)
{

}

void Widget::paintGL()
{
    glClearColor(0.2f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES,0,6);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

}

