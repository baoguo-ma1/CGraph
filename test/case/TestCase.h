/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: testcase.h
@Time: 2023/7/22 16:58
@Desc: 
***************************/

#ifndef CGRAPH_TESTCASE_H
#define CGRAPH_TESTCASE_H

#include <thread>

#include "CGraph.h"
#include "../TestDefine.h"

CGRAPH_NAMESPACE_BEGIN

class TestCase : public CObject {
/**
 * 一个 testcase，是由一个pipeline组成的
 * 其中包含了创建pipeline，配置pipeline，构建pipeline等方面的内容
 * 多个testcase，组成了一个 testsuite
 */
public:
    /**
     * @param times
     * @return
     */
    CStatus process(int times = 1) {
        loop_times_ = times;
        CGRAPH_FUNCTION_BEGIN
        status = init();
        CGRAPH_FUNCTION_CHECK_STATUS

        for (int i = 0; i < loop_times_; i++) {
            status = run();
            CGRAPH_FUNCTION_CHECK_STATUS

            if (!is_sync_) {
                asyncAfterRun();    // 异步的情况
                status = waitRunFinished();
                CGRAPH_FUNCTION_CHECK_STATUS
            }

            status = checkOnce();    // 单次执行校验，可选择实现
            CGRAPH_FUNCTION_CHECK_STATUS
        }

        status = check();    // 整体校验一下
        CGRAPH_FUNCTION_CHECK_STATUS

        status = destroy();
        CGRAPH_FUNCTION_CHECK_STATUS
        CGRAPH_FUNCTION_END
    }


protected:
    /**
     * 构造 pipeline
     * @return
     */
    virtual CStatus build() = 0;

    /**
     * 设置一些 param，aspect 等信息
     * @return
     */
    virtual CStatus setup() {
        CGRAPH_EMPTY_FUNCTION
    }

    /**
     * 设置相关信息
     * @param et
     * @param isSync
     * @return
     */
    CVoidPtr setConfig(GEngineType et, CBool isSync) {
        et_ = et;
        is_sync_ = isSync;
        return this;
    }

    /**
     * 校验单次执行的逻辑
     * @return
     */
    virtual CStatus checkOnce() {
        CGRAPH_EMPTY_FUNCTION
    }

    /**
     * 校验最终的逻辑
     * @return
     */
    virtual CStatus check() = 0;

    /**
     * 用于在异步执行的场景下，执行一些自定义逻辑
     * @return
     */
    virtual CVoid asyncAfterRun() {}

    /**
     * 获取单独执行的次数信息
     * @return
     */
    int getLoopTimes() const {
        return loop_times_;
    }

    CStatus init() final {
        CGRAPH_FUNCTION_BEGIN
        pipeline_ = GPipelineFactory::create();
        CGRAPH_ASSERT_NOT_NULL_THROW_ERROR(pipeline_)

        status = build();
        CGRAPH_FUNCTION_CHECK_STATUS

        status = setup();
        CGRAPH_FUNCTION_CHECK_STATUS

        status = pipeline_->init();
        CGRAPH_FUNCTION_CHECK_STATUS
        CGRAPH_FUNCTION_END
    }


    CStatus run() final {
        CGRAPH_FUNCTION_BEGIN

        if (is_sync_) {
            status = pipeline_->run();
            CGRAPH_FUNCTION_CHECK_STATUS
        } else {
            fut_ = pipeline_->asyncRun();
        }

        CGRAPH_FUNCTION_END
    }


    CStatus waitRunFinished() {
        CGRAPH_FUNCTION_BEGIN

        if (!is_sync_) {
            status = fut_.get();
            CGRAPH_FUNCTION_CHECK_STATUS
        }

        CGRAPH_FUNCTION_END
    }


    CStatus destroy() final {
        CGRAPH_FUNCTION_BEGIN

        status = pipeline_->destroy();
        CGRAPH_FUNCTION_CHECK_STATUS

        GPipelineFactory::remove(pipeline_);
        CGRAPH_FUNCTION_END
    }

protected:
    GPipelinePtr pipeline_ = nullptr;

private:
    std::future<CStatus> fut_;
    GEngineType et_ = GEngineType::DYNAMIC;
    CBool is_sync_ = true;
    int loop_times_ = 1;
};

using TestCasePtr = TestCase*;

CGRAPH_NAMESPACE_END

#endif //CGRAPH_TESTCASE_H
