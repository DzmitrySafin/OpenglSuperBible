//
//  Learn1_5Sample4.hpp
//  OpenglSuperBible
//
//  Created by Dzmitry Safin on 8/22/17.
//  Copyright © 2017 Dzmitry Safin. All rights reserved.
//

#ifndef __openglsuperbible__learn1_5sample4_hpp__
#define __openglsuperbible__learn1_5sample4_hpp__

#include "Engine.hpp"

class Learn1_5Sample4 : public CEngine
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
    GLuint vertex_buffer_object = 0;
};

#endif /* __openglsuperbible__learn1_5sample4_hpp__ */
