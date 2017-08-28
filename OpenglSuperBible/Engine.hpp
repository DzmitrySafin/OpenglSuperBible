//
//  Engine.hpp
//  OpenglSuperBible
//
//  Created by Dzmitry Safin on 8/18/17.
//  Copyright © 2017 Dzmitry Safin. All rights reserved.
//

#ifndef __openglsuperbible__engine_hpp__
#define __openglsuperbible__engine_hpp__

#include <stdio.h>
#include <iostream>

#define OPENGL_MAJOR  4
#define OPENGL_MINOR  1

#define STRINGIFY2(X) #X
#define STRINGIFY(X)  STRINGIFY2(X)
#define OPENGL_VERSION_SHADER STRINGIFY(OPENGL_MAJOR) STRINGIFY(OPENGL_MINOR) "0"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class CEngine
{
public:
    virtual ~CEngine();

public:
    virtual void Initialize() = 0;
    virtual void Render(double time) = 0;
    virtual void Finalize() = 0;
};

#endif /* __openglsuperbible__engine_hpp__ */
