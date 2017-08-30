//
//  main.cpp
//  LearnOpengl
//
//  Created by Dzmitry Safin on 8/9/17.
//  Copyright © 2017 Dzmitry Safin. All rights reserved.
//

#include <iostream>

#include "Engine.hpp"
#include "Chapter2Sample1.hpp"
#include "Chapter2Sample2.hpp"
#include "Chapter3Sample1.hpp"
#include "Chapter3Sample2.hpp"
#include "Chapter3Sample3.hpp"
#include "Chapter3Sample4.hpp"
#include "Chapter3Sample5.hpp"
#include "Learn1_4Sample1.hpp"
#include "Learn1_4Sample2.hpp"
#include "Learn1_4Sample3.hpp"
#include "Learn1_4Sample4.hpp"
#include "Learn1_4Sample5.hpp"
#include "Learn1_5Sample1.hpp"
#include "Learn1_5Sample2.hpp"
#include "Learn1_5Sample3.hpp"
#include "Learn1_5Sample4.hpp"
#include "Learn1_5Sample5.hpp"

#define WNDMAIN_TITLE   "OpenGL SuperBible 7th Edition + Learn OpenGL"
#define WNDMAIN_WIDTH   800
#define WNDMAIN_HEIGHT  600

CEngine* CreateTest(const char *test_name)
{
    const char *p = strchr(test_name, '-');
    int sample_number = p != nullptr ? atoi(p+1) : 0;
    int part_number = sample_number > 0 ? atoi(test_name) : 0;

    switch (part_number)
    {
        case 1:
        {
            switch (sample_number)
            {
                case 1: return new Chapter2Sample1();
                case 2: return new Chapter2Sample2();
                case 3: return new Chapter3Sample1();
                case 4: return new Chapter3Sample2();
                case 5: return new Chapter3Sample3();
                case 6: return new Chapter3Sample4();
                case 7: return new Chapter3Sample5();
                case 8: return new Learn1_4Sample1();
                case 9: return new Learn1_4Sample2();
                case 10: return new Learn1_4Sample3();
                case 11: return new Learn1_4Sample4();
                case 12: return new Learn1_4Sample5();
                case 13: return new Learn1_5Sample1();
                case 14: return new Learn1_5Sample2();
                case 15: return new Learn1_5Sample3();
                case 16: return new Learn1_5Sample4();
                case 17: return new Learn1_5Sample5();
            }
            break;
        }
        //case 2:
        //{
        //    switch (sample_number)
        //    {
        //        case 1: return new Chapter2Sample1();
        //    }
        //    break;
        //}
    }

    return new Learn1_5Sample5();
}

void key_callback(GLFWwindow *window, int key, int /*scancode*/, int action, int /*mode*/)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main(int argc, const char *argv[])
{
    if (glfwInit() != GLFW_TRUE)
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    std::cout << glfwGetVersionString() << std::endl;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(WNDMAIN_WIDTH, WNDMAIN_HEIGHT, WNDMAIN_TITLE, nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    GLint ext_number = 0;
    glGetIntegerv(GL_NUM_EXTENSIONS, &ext_number);
    std::cout << "Number of extensions available: " << ext_number << std::endl;

    CEngine *engine = CreateTest(argc > 1 ? argv[1] : "");
    engine->Initialize();

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        static const GLfloat bg_color[] = { 0.0f, 0.4f, 0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, bg_color);

        engine->Render(glfwGetTime());

        glfwSwapBuffers(window);
    }

    engine->Finalize();
    delete engine;

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
