/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: TestGNode-001.h
@Time: 2023/7/22 18:27
@Desc: 
***************************/

#ifndef CGRAPH_TESTGNODE_001_H
#define CGRAPH_TESTGNODE_001_H

#include "TestGNode.h"
#include "TestGParam-001.h"

using namespace CGraph;

class TestGNode_001 : public TestGNode {
public:
    CStatus run() override {
        CGRAPH_FUNCTION_BEGIN
        auto param = CGRAPH_GET_GPARAM_WITH_NO_EMPTY(TestGParam_001, STR_TEST_GPARAM_KEY_001);
        {
            CGRAPH_PARAM_WRITE_CODE_BLOCK(param);
            param->cur_val_++;    // 通过i++来进行各种dag调度逻辑的测试
            param->total_val_++;
        }
        CGRAPH_FUNCTION_END
    }
};

#endif //CGRAPH_TESTGNODE_001_H
