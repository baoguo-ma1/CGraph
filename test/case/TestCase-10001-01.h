/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: TestCase-10001-01.h
@Time: 2023/7/23 17:06
@Desc: 
***************************/

#ifndef CGRAPH_TESTCASE_10001_01_H
#define CGRAPH_TESTCASE_10001_01_H

#include "TestCase.h"
#include "TestGParam-001.h"
#include "TestGNode-001.h"

using namespace CGraph;

template<GEngineType _ET, CBool _IsSync>
class TestCase_10001_01 : public TestCase {
protected:
    /**
     * 刚开始构建图的时候
     * @return
     */
    CStatus build() override {
        CGRAPH_FUNCTION_BEGIN

        // 构建一个图里套图的pipeline，暂时不加入 condition相关的内容吧
        GElementPtr a,b,c,d,e,f,g,h,i,j,k,l,m,n = nullptr;
        GElementPtr region1, region2, cluster1, cluster2 = nullptr;

        // a 必须先创建，不然的话，后面的会有依赖为空的情况
        status += pipeline_->template registerGElement<TestGNode_001>(&a, {});

        b = pipeline_->template createGNode<TestGNode_001>(GNodeInfo({}, "b"));
        c = pipeline_->template createGNode<TestGNode_001>(GNodeInfo({}, "c"));

        d = pipeline_->template createGNode<TestGNode_001>(GNodeInfo({}, "d"));
        e = pipeline_->template createGNode<TestGNode_001>(GNodeInfo("e"));
        f = pipeline_->template createGNode<TestGNode_001>(GNodeInfo("f"));
        cluster1 = pipeline_->template createGGroup<GCluster>( {e, f}, {d});

        g = pipeline_->template createGNode<TestGNode_001>(GNodeInfo({d}));
        region2 = pipeline_->template createGGroup<GRegion>({d, cluster1, g});

        region1 = pipeline_->template createGGroup<GRegion>({b, c, region2});

        i = pipeline_->template createGNode<TestGNode_001>(GNodeInfo("i"));
        j = pipeline_->template createGNode<TestGNode_001>(GNodeInfo("j"));
        k = pipeline_->template createGNode<TestGNode_001>(GNodeInfo("k"));
        cluster2 = pipeline_->template createGGroup<GCluster>({i, j, k}, {a, region1});

        status += pipeline_->template registerGElement<GRegion>(&region1, {});
        status += pipeline_->template registerGElement<TestGNode_001>(&h, {region1});
        status += pipeline_->template registerGElement<GCluster>(&cluster2, {a, region1});
        status += pipeline_->template registerGElement<TestGNode_001>(&l, {a});

        status += pipeline_->template registerGElement<TestGNode_001>(&m, {h, cluster2});
        status += pipeline_->template registerGElement<TestGNode_001>(&n, {l, cluster2});

        CGRAPH_FUNCTION_END
    }

    CStatus setup() override {
        CGRAPH_FUNCTION_BEGIN
        setConfig(_ET, _IsSync);
        status = pipeline_->createGParam<TestGParam_001>(STR_TEST_GPARAM_KEY_001);
        CGRAPH_FUNCTION_END
    }

    CStatus checkOnce() override {
        CGRAPH_FUNCTION_BEGIN
        auto param = pipeline_->getGParamWithNoEmpty<TestGParam_001>(STR_TEST_GPARAM_KEY_001);
        if (param->cur_val_ != 14) {
            // 一共10个节点信息，故判定值为10
            CGRAPH_THROW_EXCEPTION("param cur_val_ not right")
        }
        CGRAPH_FUNCTION_END
    }

    CStatus check() override {
        // 获取pipeline中的信息，判断各种参数是否正确
        CGRAPH_FUNCTION_BEGIN
        auto param = pipeline_->getGParamWithNoEmpty<TestGParam_001>(STR_TEST_GPARAM_KEY_001);
        if ((14 * getLoopTimes()) != param->total_val_) {
            CGRAPH_THROW_EXCEPTION("param total_val_ not right")
        }

        CGRAPH_FUNCTION_END
    }
};

#endif //CGRAPH_TESTCASE_10001_01_H
