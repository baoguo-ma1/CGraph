/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: TestGParam-001.h
@Time: 2023/7/22 18:29
@Desc: 
***************************/

#ifndef CGRAPH_TESTGPARAM_001_H
#define CGRAPH_TESTGPARAM_001_H

#include "CGraph.h"

using namespace CGraph;

class TestGParam_001 : public GParam {
public:
    int cur_val_ = 0;
    int total_val_ = 0;

public:
    CStatus setup() override {
        CGRAPH_FUNCTION_BEGIN
        cur_val_ = 0;
        CGRAPH_FUNCTION_END
    }
};


#endif //CGRAPH_TESTGPARAM_001_H
