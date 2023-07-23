/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: TestSuite-002.h
@Time: 2023/7/23 17:50
@Desc: 
***************************/

#ifndef CGRAPH_TESTSUITE_002_H
#define CGRAPH_TESTSUITE_002_H

#include "TestSuite.h"
#include "TestCase-10001-01.h"

CGRAPH_NAMESPACE_BEGIN

class TestSuite_002 : public TestSuite {
public:
    CVoid buildTestSuite() override {
        // 这些都是固定的流程，每个 test suite 的信息都是固定的
        addTestCase(new TestCase_10001_01<GEngineType::DYNAMIC, true>());
        addTestCase(new TestCase_10001_01<GEngineType::STATIC, true>());
        addTestCase(new TestCase_10001_01<GEngineType::DYNAMIC, false>());
        addTestCase(new TestCase_10001_01<GEngineType::STATIC, false>());
    }
};

CGRAPH_NAMESPACE_END

#endif //CGRAPH_TESTSUITE_002_H
