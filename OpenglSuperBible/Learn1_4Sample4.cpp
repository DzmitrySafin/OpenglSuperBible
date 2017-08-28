//
//  Learn1_4Sample4.cpp
//  OpenglSuperBible
//
//  Created by Dzmitry Safin on 8/19/17.
//  Copyright © 2017 Dzmitry Safin. All rights reserved.
//

#include "Learn1_4Sample4.hpp"

static const GLchar *vs_source[] =
{
    "#version " OPENGL_VERSION_SHADER " core  \n"
    "                                         \n"
    "layout (location = 0) in vec4 position;  \n"
    "                                         \n"
    "void main(void)                          \n"
    "{                                        \n"
    "    gl_Position = position;              \n"
    "}"
};

static const GLchar *fs_source[] =
{
    "#version " OPENGL_VERSION_SHADER " core \n"
    "                                       \n"
    "out vec4 color;                        \n"
    "                                       \n"
    "void main(void)                        \n"
    "{                                      \n"
    "    color = vec4(1.0, 1.0, 0.0, 1.0);  \n"
    "}"
};

void Learn1_4Sample4::Initialize()
{
    shader_program = CompileProgram();
    
    GLfloat vertices[] =
    {
         0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 1.0f,
         0.0f,  0.5f, 0.0f, 1.0f,
    };

    GLfloat vertices2[] =
    {
        0.5f, -0.5f, 0.0f, 1.0f,
        0.0f,  0.5f, 0.0f, 1.0f,
        1.0f,  0.5f, 0.0f, 1.0f,
    };

    glGenVertexArrays(2, vertex_array_object);
    glGenBuffers(2, vertex_buffer_object);

    glBindVertexArray(vertex_array_object[0]);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), static_cast<GLvoid*>(nullptr));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    glBindVertexArray(vertex_array_object[1]);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), static_cast<GLvoid*>(nullptr));
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Learn1_4Sample4::Render(double /*time*/)
{
    glUseProgram(shader_program);
    
    glBindVertexArray(vertex_array_object[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(vertex_array_object[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void Learn1_4Sample4::Finalize()
{
    glDeleteBuffers(2, vertex_buffer_object);
    glDeleteVertexArrays(2, vertex_array_object);
    
    glDeleteProgram(shader_program);
}

GLuint Learn1_4Sample4::CompileProgram()
{
    GLint success;
    GLchar info_log[512];
    
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, vs_source, nullptr);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
        std::cout << "ERROR:SHADER:VERTEX:COMPILE" << std::endl << info_log << std::endl;
    }
    
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, fs_source, nullptr);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
        std::cout << "ERROR:SHADER:FRAGMENT:COMPILE" << std::endl << info_log << std::endl;
    }
    
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, nullptr, info_log);
        std::cout << "ERROR:SHADER:PROGRAM:LINK" << std::endl << info_log << std::endl;
    }
    
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    
    return program;
}