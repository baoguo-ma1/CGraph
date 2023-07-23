/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: testcase-10000-01.h
@Time: 2023/7/22 16:56
@Desc: 1* 开头的测例，主要负责测试调度和执行等核心逻辑
***************************/

#ifndef CGRAPH_TESTCASE_10000_01_H
#define CGRAPH_TESTCASE_10000_01_H

#include "TestCase.h"
#include "TestGParam-001.h"
#include "TestGNode-001.h"

using namespace CGraph;

template<GEngineType _ET, CBool _IsSync>
class TestCase_10000_01 : public TestCase {
protected:
    /**
     * 刚开始构建图的时候
     * @return
     */
    CStatus build() override {
        CGRAPH_FUNCTION_BEGIN

        GElementPtr a, b, c, d, e, f, g, h, i, j = nullptr;
        status += pipeline_->registerGElement<TestGNode_001>(&a, {});
        status += pipeline_->registerGElement<TestGNode_001>(&b, {});
        status += pipeline_->registerGElement<TestGNode_001>(&c, {a});
        status += pipeline_->registerGElement<TestGNode_001>(&d, {b});
        status += pipeline_->registerGElement<TestGNode_001>(&e, {b, c});
        status += pipeline_->registerGElement<TestGNode_001>(&f, {c});
        status += pipeline_->registerGElement<TestGNode_001>(&g, {d, e, f});
        status += pipeline_->registerGElement<TestGNode_001>(&h, {f});
        status += pipeline_->registerGElement<TestGNode_001>(&i, {g, h});
        status += pipeline_->registerGElement<TestGNode_001>(&j, {h});
        CGRAPH_FUNCTION_END
    }

    /**
     * 用于创建param，aspect的信息，在 build之后被执行
     * @return
     */
    CStatus setup() override {
        CGRAPH_FUNCTION_BEGIN
        status = pipeline_->createGParam<TestGParam_001>(STR_TEST_GPARAM_KEY_001);
        setConfig(_ET, _IsSync);
        CGRAPH_FUNCTION_END
    }

    /**
     * 单独check一次执行的内容，可选实现
     */
    CStatus checkOnce() override {
        CGRAPH_FUNCTION_BEGIN
        auto param = pipeline_->getGParamWithNoEmpty<TestGParam_001>(STR_TEST_GPARAM_KEY_001);
        if (param->cur_val_ != 10) {
            // 一共10个节点信息，故判定值为10
            CGRAPH_THROW_EXCEPTION("param cur_val_ not right")
        }
        CGRAPH_FUNCTION_END
    }

    /**
     * 针对最终结果的校验
     * @return
     */
    CStatus check() override {
        // 获取pipeline中的信息，判断各种参数是否正确
        CGRAPH_FUNCTION_BEGIN
        auto param = pipeline_->getGParamWithNoEmpty<TestGParam_001>(STR_TEST_GPARAM_KEY_001);
        if ((10 * getLoopTimes()) != param->total_val_) {
            CGRAPH_THROW_EXCEPTION("param total_val_ not right")
        }

        CGRAPH_FUNCTION_END
    }
};

#endif //CGRAPH_TESTCASE_10000_01_H
