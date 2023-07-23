/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: TestSuite.h
@Time: 2023/7/22 21:44
@Desc: 
***************************/

#ifndef CGRAPH_TESTSUITE_H
#define CGRAPH_TESTSUITE_H

#include <vector>

#include "CGraph.h"
#include "TestCase-10000-01.h"

CGRAPH_NAMESPACE_BEGIN

class TestSuite : public CObject {
public:
    CStatus run() final {
        CGRAPH_FUNCTION_BEGIN
        buildTestSuite();

        for (TestCasePtr ptr : suite_) {
            status += ptr->process(10000);
            CGRAPH_FUNCTION_CHECK_STATUS
        }

        CGRAPH_FUNCTION_END
    }

    ~TestSuite() override {
        for (auto ptr : suite_) {
            CGRAPH_DELETE_PTR(ptr);
        }
    }

protected:
    virtual CVoid buildTestSuite() = 0;

    CVoid addTestCase(TestCasePtr ptr) {
        CGRAPH_ASSERT_NOT_NULL_THROW_ERROR(ptr)
        suite_.push_back(ptr);
    }

private:
    std::vector<TestCasePtr> suite_;
};

using TestSuitePtr = TestSuite *;
using TestSuiteContainer = std::vector<TestSuitePtr>;

CGRAPH_NAMESPACE_END

#endif //CGRAPH_TESTSUITE_H
