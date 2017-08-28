//
//  Chapter3Sample2.hpp
//  OpenglSuperBible
//
//  Created by Dzmitry Safin on 8/18/17.
//  Copyright © 2017 Dzmitry Safin. All rights reserved.
//

#ifndef __openglsuperbible__chapter3sample2_hpp__
#define __openglsuperbible__chapter3sample2_hpp__

#include "Engine.hpp"

class Chapter3Sample2 : public CEngine
{
public:
    void Initialize() override;
    void Render(double time) override;
    void Finalize() override;
    
private:
    static GLuint CompileProgram();
    
private:
    GLuint shader_program = 0;
    GLuint vertex_array_object = 0;
};

#endif /* __openglsuperbible__chapter3sample2_hpp__ */
