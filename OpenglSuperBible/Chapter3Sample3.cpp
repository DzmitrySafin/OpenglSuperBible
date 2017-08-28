//
//  Chapter3Sample3.cpp
//  OpenglSuperBible
//
//  Created by Dzmitry Safin on 8/19/17.
//  Copyright © 2017 Dzmitry Safin. All rights reserved.
//

#include "Chapter3Sample3.hpp"

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

static const GLchar *tcs_source[] =
{
    "#version " OPENGL_VERSION_SHADER " core \n"
    "                                     \n"
    "layout (vertices = 3) out;           \n"
    "                                     \n"
    "void main(void)                      \n"
    "{                                    \n"
    "    if (gl_InvocationID == 0)        \n"
    "    {                                \n"
    "        gl_TessLevelInner[0] = 8.0;  \n"
    "        gl_TessLevelOuter[0] = 8.0;  \n"
    "        gl_TessLevelOuter[1] = 8.0;  \n"
    "        gl_TessLevelOuter[2] = 8.0;  \n"
    "    }                                \n"
    "                                     \n"
    "    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;  \n"
    "}"
};

static const GLchar *tes_source[] =
{
    "#version " OPENGL_VERSION_SHADER " core    \n"
    "                                           \n"
    "layout (triangles, equal_spacing, cw) in;  \n"
    "                                           \n"
    "void main(void)                            \n"
    "{                                          \n"
    "    gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position + gl_TessCoord.y * gl_in[1].gl_Position + gl_TessCoord.z * gl_in[2].gl_Position);  \n"
    "}"
};

static const GLchar *gs_source[] =
{
    "#version " OPENGL_VERSION_SHADER " core      \n"
    "                                             \n"
    "layout (triangles) in;                       \n"
    "layout (points, max_vertices = 3) out;       \n"
    "                                             \n"
    "void main(void)                              \n"
    "{                                            \n"
    "    int i;                                   \n"
    "    for (i = 0; i < gl_in.length(); ++i)     \n"
    "    {                                        \n"
    "        gl_Position = gl_in[i].gl_Position;  \n"
    "        EmitVertex();                        \n"
    "    }                                        \n"
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

void Chapter3Sample3::Initialize()
{
    shader_program = CompileProgram();
    
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);
    
    glPointSize(8.0f);
}

void Chapter3Sample3::Render(double /*time*/)
{
    glUseProgram(shader_program);
    
    glDrawArrays(GL_PATCHES, 0, 3);
}

void Chapter3Sample3::Finalize()
{
    glDeleteVertexArrays(1, &vertex_array_object);
    
    glDeleteProgram(shader_program);
}

GLuint Chapter3Sample3::CompileProgram()
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
    
    GLuint tess_control_shader = glCreateShader(GL_TESS_CONTROL_SHADER);
    glShaderSource(tess_control_shader, 1, tcs_source, nullptr);
    glCompileShader(tess_control_shader);
    glGetShaderiv(tess_control_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(tess_control_shader, 512, nullptr, info_log);
        std::cout << "ERROR:SHADER:TESS_CONTROL:COMPILE" << std::endl << info_log << std::endl;
    }
    
    GLuint tess_evaluation_shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
    glShaderSource(tess_evaluation_shader, 1, tes_source, nullptr);
    glCompileShader(tess_evaluation_shader);
    glGetShaderiv(tess_evaluation_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(tess_evaluation_shader, 512, nullptr, info_log);
        std::cout << "ERROR:SHADER:TESS_EVALUATION:COMPILE" << std::endl << info_log << std::endl;
    }
    
    GLuint geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometry_shader, 1, gs_source, nullptr);
    glCompileShader(geometry_shader);
    glGetShaderiv(geometry_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(geometry_shader, 512, nullptr, info_log);
        std::cout << "ERROR:SHADER:GEOMETRY:COMPILE" << std::endl << info_log << std::endl;
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
    glAttachShader(program, tess_control_shader);
    glAttachShader(program, tess_evaluation_shader);
    glAttachShader(program, geometry_shader);
    glAttachShader(program, fragment_shader);
    
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, nullptr, info_log);
        std::cout << "ERROR:SHADER:PROGRAM:LINK" << std::endl << info_log << std::endl;
    }
    
    glDeleteShader(vertex_shader);
    glDeleteShader(tess_control_shader);
    glDeleteShader(tess_evaluation_shader);
    glDeleteShader(geometry_shader);
    glDeleteShader(fragment_shader);
    
    return program;
}
