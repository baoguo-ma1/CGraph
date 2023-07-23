/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: main.cpp
@Time: 2023/7/22 16:18
@Desc: 
***************************/

#include <vector>

#include "TestSuite-001.h"
#include "TestSuite-002.h"

CVoid testAllSuite() {
    CGRAPH_ECHO("begin run all test suite");

    TestSuiteContainer container;
    container.emplace_back(new TestSuite_001());
    container.emplace_back(new TestSuite_002());
    int i = 0;

    for (auto ts : container) {
        auto status = ts->run();
        if (!status.isOK()) {
            CGRAPH_THROW_EXCEPTION("test failed, please check ...")
        }

        CGRAPH_ECHO("test suite [%d] run success.", ++i);
        CGRAPH_DELETE_PTR(ts);
    }

    // 如果中间有异常的情况，就直接抛出了。走到这里的
    CGRAPH_ECHO("all test suite success...");
}


int main() {
    testAllSuite();
    return 0;
}
