//
//  Chapter2Sample1.cpp
//  OpenglSuperBible
//
//  Created by Dzmitry Safin on 8/18/17.
//  Copyright © 2017 Dzmitry Safin. All rights reserved.
//

#include "Chapter2Sample1.hpp"

static const GLchar *vs_source[] =
{
    "#version " OPENGL_VERSION_SHADER " core \n"
    "                                             \n"
    "void main(void)                              \n"
    "{                                            \n"
    "    gl_Position = vec4(0.0, 0.0, 0.0, 1.0);  \n"
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
    "    color = vec4(1.0, 0.0, 0.0, 1.0);  \n"
    "}"
};

void Chapter2Sample1::Initialize()
{
    shader_program = CompileProgram();

    //glCreateVertexArrays(1, &vertex_array_object); // OpenGL 4.5
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    glPointSize(16.0f);
}

void Chapter2Sample1::Render(double /*time*/)
{
    glUseProgram(shader_program);

    glDrawArrays(GL_POINTS, 0, 1);
}

void Chapter2Sample1::Finalize()
{
    glDeleteVertexArrays(1, &vertex_array_object);

    glDeleteProgram(shader_program);
}

GLuint Chapter2Sample1::CompileProgram()
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
