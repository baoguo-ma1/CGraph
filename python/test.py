#!/usr/bin/env python
# -*- coding:utf-8 -*-

# under development...

from pyCGraph import GNode,CStatus,GPipelinePy

class MyNodeA(GNode):
    def init(self):
        print("MyNodeA init...")
        return CStatus()

    def run(self):
        status = CStatus()
        print("MyNodeA running...")
        return status

    def destroy(self):
        print("MyNodeA destroy...")
        return CStatus()


# class MyNodeB(GNode):

#     # @override
#     def run(self):
#         print("MyNodeB running...")
#         count = 0
#         time.sleep(2)
#         return pyCGraph.CStatus()

# class MyNodeC(GNode):

#     def run(self):
#         print("MyNodeC running...")
#         time.sleep(2)
#         count = 0
#         return pyCGraph.CStatus()

# class MyNodeD(pyCGraph.GNode):

#     def run(self):
#         print("MyNodeD running...")
#         return pyCGraph.CStatus()


# nodeB = MyNodeB()
# nodeC = MyNodeC()
# nodeD = MyNodeD()

if "__main__" == __name__:
    ppln = GPipelinePy()
    print("hellow")
    nodeA = MyNodeA()
    status = ppln.registerGElement(nodeA)
    # status = ppln.registerGElement(nodeB, {nodeA})

    status = ppln.init()
    status = ppln.run()
    status = ppln.destroy()

    # PipelineRemove(pipeline)

    # ppln.run()
    # ppln.destroy()
