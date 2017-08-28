//
//  Chapter2Sample2.cpp
//  OpenglSuperBible
//
//  Created by Dzmitry Safin on 8/18/17.
//  Copyright © 2017 Dzmitry Safin. All rights reserved.
//

#include "Chapter2Sample2.hpp"

static const GLchar *vs_source[] =
{
    "#version " OPENGL_VERSION_SHADER " core \n"
    "                 \n"
    "void main(void)  \n"
    "{                \n"
    "    const vec4 vertices[3] = vec4[3](vec4( 0.5, -0.5, 0.0, 1.0),   \n"
    "                                     vec4(-0.5, -0.5, 0.0, 1.0),   \n"
    "                                     vec4( 0.0,  0.5, 0.0, 1.0));  \n"
    "    gl_Position = vertices[gl_VertexID];                           \n"
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

void Chapter2Sample2::Initialize()
{
    shader_program = CompileProgram();
    
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);
}

void Chapter2Sample2::Render(double /*time*/)
{
    glUseProgram(shader_program);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Chapter2Sample2::Finalize()
{
    glDeleteVertexArrays(1, &vertex_array_object);
    
    glDeleteProgram(shader_program);
}

GLuint Chapter2Sample2::CompileProgram()
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
