## 人工智能课程作业1 -- 搜索问题

#### 简介

本作业基于8-puzzle问题，目标是基于广度优先搜索（breadth first search）、深度有限搜索（depth limit search）、启发式搜索（A*）搜索该问题的解。该部分内容对应《Artificial Intelligence: A Modern Approach 3rd》中的第三章内容：Solving Problems by Searching。

##### 8-puzzle

该问题为一个九宫格，只有0可以和其上、下、左、右的数码交换位置。

该问题的目标状态为

```shell
0 1 2
3 4 5
6 7 8
```

随机的初始状态可能为

```shell
1 2 0
3 4 5
6 7 8
```

对应该初始状态，动作序列[LEFT, LEFT]可以将该状态恢复为目标状态，也就是把0和其左边的数码交换两次。



#### 作业目标

完成Assignement1项目中的五个函数

Search.cpp中

```c++
std::vector<Action> bfs(Problem& problem);
std::vector<Action> recursiveDLS(Node& node, Problem& problem, int limit);
std::vector<Action> aStar(Problem& problem, heuristicFunc heuristicFunc);
```

Heuristic.cpp中

```c++
int misplace(std::vector<int>& state, std::vector<int>& goalState);
int manhattan(std::vector<int>& state, std::vector<int>& goalState);
```

##### 项目启动说明

使用Visual Studio 2019打开Assignment1.sln。



#### Tips

1. main.cpp中的main函数为该项目的主入口。
2. void doExperiment(int iteration, int problemSize, int suffleSteps, searchFunc searchFunc)函数可用于调试和检验算法的效率。
3. void testSearchFunction(searchFunc searchFunc)函数用于检验搜索算法的正确性。



#### 评估标准

##### 代码部分（8分）

1. 搜索算法的正确性：算法得出的结果可以通过testSearchFunction函数的验证。
2. 搜索算法的搜索时间：每个搜索算法都可以在2分钟内跑出结果。
3. 内存管理：算法的内存消耗需要符合该算法应有的空间复杂度。

##### 文档部分（2分）

1. 算法、实验结果分析：根据实验结果分析、对比三种搜索算法以及启发式搜索的启发函数，完成“人工智能-第一次课程作业报告”。



#### 作业提交

##### 提交截止时间

第九周下午上课时间

##### 提交方式

将`Search.cpp`、`Heuristic.cpp`和`人工智能-第一次课程作业报告`打包为.zip文件，命名为`学号_姓名_Assignment1`，发送至邮箱`chuanqi_shi@163.com`。
