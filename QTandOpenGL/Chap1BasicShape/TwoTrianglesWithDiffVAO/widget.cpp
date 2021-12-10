#include "widget.h"

unsigned int VAOs[2];
unsigned int VBOs[2];

unsigned int shaderProgram;
unsigned int shaderProgram2;

float vertices1[]=
{
    -0.9f,-0.5f,0.0f,
    -0.0f,-0.5f,0.0f,
    -0.45f,0.5f,0.0f,
};

float vertices2[]=
{
    0.0f,-0.5f,0.0f,
    0.9f,-0.5f,0.0f,
    0.45f,0.5f,0.0f
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

const char *fragmentShaderSource2 = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "FragColor = vec4(1.0f,0.0f,0.0f,1.0f);\n"
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

    glGenVertexArrays(3,VAOs);
    glGenBuffers(2,VBOs);

    // First Tri
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[0]);

    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),0);
    glEnableVertexAttribArray(0);

    //glBindBuffer(GL_ARRAY_BUFFER,0);
    //glBindVertexArray(0);

    // Second Tri
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[1]);

    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices2),vertices2,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),0);
    glEnableVertexAttribArray(0);

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);

    unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2,1,&fragmentShaderSource2,NULL);
    glCompileShader(fragmentShader2);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2,vertexShader);
    glAttachShader(shaderProgram2,fragmentShader2);
    glLinkProgram(shaderProgram2);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShader2);

}

void Widget::resizeGL(int w, int h)
{

}

void Widget::paintGL()
{
    glClearColor(0.2f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    //Paint Separately
    glUseProgram(shaderProgram);
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES,0,3);

    glUseProgram(shaderProgram2);
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES,0,3);
}

