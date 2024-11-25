#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <time.h>
#include "eightFigurePuzzles.h"
#ifdef _WIN32 // Check if the code is being compiled on a Windows system
#include <windows.h>
#endif
using namespace std;

// 用于记录当前状态是否被访问过。
map<int, int> visited;

// 深度有限搜索，用于限制深度。
#define MAX_DEPTH 25

// openList与closeList用于A*搜索。
vector<PUZZLE_NODE> closeList;
vector<PUZZLE_NODE> openList;
bool operator==(PUZZLE_NODE a, PUZZLE_NODE b)
{
    return checkObject(a, b);
}
bool searchList(vector<PUZZLE_NODE> &nodeList, PUZZLE_NODE target)
{
    for (int i = 0; i < nodeList.size(); i++)
        if (nodeList[i] == target)
            return true;
    return false;
}
int heuristicCalculate(PUZZLE_NODE NextNode)
{
    int ErrorNum = 0;
    for (int i = 0; i < 9; i++)
    {
        if (NextNode.puzzle[i].puzzleId != i)
            ErrorNum++;
    }
    return ErrorNum;
}
int ManhattonDis(PUZZLE_NODE NextNode, const PUZZLE_NODE &obj)
{
    int sum = 0;
    for (int i = 0; i < 9; i++)
    {
        int x = abs(NextNode.puzzle[i].xPosition - obj.puzzle[NextNode.puzzle[i].puzzleId].xPosition);
        int y = abs(NextNode.puzzle[i].yPosition - obj.puzzle[NextNode.puzzle[i].puzzleId].yPosition);
        sum = x + y + sum;
    }
    return sum;
}
void openListInsert(vector<PUZZLE_NODE> &openList, PUZZLE_NODE &nextNode)
{
    if (openList.empty())
        openList.push_back(nextNode);
    else if (openList[openList.size() - 1].height + openList[openList.size() - 1].depth <= nextNode.height + nextNode.depth)
        openList.push_back(nextNode);
    else
    {
        for (int i = 0; i < openList.size(); i++)
        {
            if (openList[i].height + openList[i].depth > nextNode.height + nextNode.depth)
            {
                openList.insert(openList.begin() + i, nextNode);
                break;
            }
        }
    }
}
bool operator>(PUZZLE_NODE a, PUZZLE_NODE b)
{
    return a.height + a.depth > b.height + b.depth;
}
// 广度优先搜索
vector<int> binaryFirstSearch(PUZZLE_NODE initialNode, PUZZLE_NODE objPuzzleNode)
{
    // result[0] 1:correct;0:wrong
    // result[1] 步数 steps
    vector<int> result(2, 0);
    /*
        Note that the 2023 version of the framework incorrectly writes"int result[2]={0,0};".
        Here, you need to modify it yourself.
        The same applies to each of the following places.
    */
    cout << "初始节点状态：" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << " " << initialNode.puzzle[i * 3 + 0].puzzleId << "  " << initialNode.puzzle[i * 3 + 1].puzzleId << "  " << initialNode.puzzle[i * 3 + 2].puzzleId << endl;
    }
    cout << endl;
    /*
        请在该位置完成广度优先搜索。
    */
    initialNode.depth = 0;
    queue<PUZZLE_NODE> puzzleNodeQueue;
    PUZZLE_NODE currentNode, nextNode;
    puzzleNodeQueue.push(initialNode);

    while (!puzzleNodeQueue.empty())
    {
        currentNode = puzzleNodeQueue.front();
        if (checkObject(currentNode, objPuzzleNode))
        {
            for (int i = 0; i < currentNode.precedeActionList.size(); i++)
                outputAction(currentNode.precedeActionList[i], i + 1);
            cout << "找到正确结果:" << endl;
            for (int i = 0; i < 3; i++)
            {
                cout << " " << currentNode.puzzle[i * 3 + 0].puzzleId << "  " << currentNode.puzzle[i * 3 + 1].puzzleId << "  " << currentNode.puzzle[i * 3 + 2].puzzleId << endl;
            }
            cout << endl;
            result[0] = 1;
            result[1] = currentNode.depth;
            return result;
        }

        // 弹出并记录已经check的结点
        puzzleNodeQueue.pop();
        visited[visitedNum(currentNode)] = 1;
        // 更新currentNode结点下一步的状态
        if (currentNode.nextActionList.size() == 0)
            currentNode = updatePuzzleNodeActionList(currentNode);
        // 更新结点
        for (int i = 0; i < currentNode.nextActionList.size(); i++)
        {
            nextNode = moveToPuzzleNode(currentNode.nextActionList[i], currentNode);
            if (!currentNode.precedeActionList.empty())
                for (int j = 0; j < currentNode.precedeActionList.size(); j++)
                    nextNode.precedeActionList.push_back(currentNode.precedeActionList[j]);
            nextNode.precedeActionList.push_back(currentNode.nextActionList[i]);
            if (visited[visitedNum(nextNode)] == 1)
                continue;
            nextNode.depth = currentNode.depth + 1;
            puzzleNodeQueue.push(nextNode);
        }
    }
    return result;
}
// 深度有限搜索
vector<int> depthFirstSearchRe(PUZZLE_NODE currentNode, PUZZLE_NODE objPuzzleNode)
{

    // result[0] 1:correct;0:wrong
    // result[1] 步数 steps
    vector<int> result(2, 0);
    /*
        请在该位置完成深度有限搜索，最大深度限度为25。
    */
    if (currentNode.depth >= MAX_DEPTH)
    {
        return result;
    }
    if (checkObject(currentNode, objPuzzleNode))
    {
        for (int i = 0; i < currentNode.precedeActionList.size(); i++)
            outputAction(currentNode.precedeActionList[i], i + 1);
        cout << "找到正确结果:" << endl;
        for (int i = 0; i < 3; i++)
        {
            cout << " " << currentNode.puzzle[i * 3 + 0].puzzleId << "  " << currentNode.puzzle[i * 3 + 1].puzzleId << "  " << currentNode.puzzle[i * 3 + 2].puzzleId << endl;
        }
        cout << endl;

        result[0] = 1;
        result[1] = currentNode.depth;
        return result;
    }
    visited[visitedNum(currentNode)] = 1;
    if (currentNode.nextActionList.size() == 0)
        currentNode = updatePuzzleNodeActionList(currentNode);
    for (int i = 0; i < currentNode.nextActionList.size(); i++)
    {
        auto nextNode = moveToPuzzleNode(currentNode.nextActionList[i], currentNode);
        if (!currentNode.precedeActionList.empty())
            for (int j = 0; j < currentNode.precedeActionList.size(); j++)
                nextNode.precedeActionList.push_back(currentNode.precedeActionList[j]);
        nextNode.precedeActionList.push_back(currentNode.nextActionList[i]);
        if (visited[visitedNum(nextNode)] == 1)
            continue;
        nextNode.depth = currentNode.depth + 1;
        auto searchResult = depthFirstSearchRe(nextNode, objPuzzleNode);
        if (searchResult[0] == 1)
        {
            result[0] = searchResult[0], result[1] = searchResult[1];
            return result;
        }
    }
    return result;
}
vector<int> depthFirstSearch(PUZZLE_NODE initialNode, PUZZLE_NODE objPuzzleNode)
{
    initialNode.depth = 0;
    cout << "初始节点状态：" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << " " << initialNode.puzzle[i * 3 + 0].puzzleId << "  " << initialNode.puzzle[i * 3 + 1].puzzleId << "  " << initialNode.puzzle[i * 3 + 2].puzzleId << endl;
    }
    cout << endl;
    return depthFirstSearchRe(initialNode, objPuzzleNode);
}
int heuristicFunction(PUZZLE_NODE currentPuzzleNode, PUZZLE_NODE objPuzzleNode)
{
    int incorrectCount = 0;

    // 计算不正确位置的数码个数
    for (int i = 0; i < puzzleNum + 1; i++)
    {
        if (!isEqual(currentPuzzleNode.puzzle[i], objPuzzleNode.puzzle[i]))
        {
            incorrectCount++;
        }
    }

    return incorrectCount;
}

// 启发式搜索1
vector<int> heuristicSearchInformedByIncorrectNum(PUZZLE_NODE initialNode, PUZZLE_NODE objPuzzleNode)
{
    // result[0] 1:correct;0:wrong
    // result[1] 步数 steps
    vector<int> result(2, 0);
    cout << "初始节点状态：" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << " " << initialNode.puzzle[i * 3 + 0].puzzleId << "  " << initialNode.puzzle[i * 3 + 1].puzzleId << "  " << initialNode.puzzle[i * 3 + 2].puzzleId << endl;
    }
    cout << endl;
    /*
        请在该位置完成启发式搜索，启发式函数使用不正确位置的数码个数。
    */
    initialNode.depth = 0;
    priority_queue<PUZZLE_NODE, vector<PUZZLE_NODE>, greater<PUZZLE_NODE>> puzzleNodePriorityQueue;
    /*
        Note that line 75 manually implements the overloading of operator >, and the same is true in heuristic search 2.
        The method of using vector to maintain monotonic sequences provided at the beginning of the 2023 version of the framework is too inefficient and is not recommended.
    */
    PUZZLE_NODE currentNode, nextNode;
    initialNode.height = heuristicFunction(initialNode, objPuzzleNode);
    puzzleNodePriorityQueue.push(initialNode);
    while (!puzzleNodePriorityQueue.empty())
    {
        currentNode = puzzleNodePriorityQueue.top();
        puzzleNodePriorityQueue.pop();
        if (checkObject(currentNode, objPuzzleNode))
        {
            for (int i = 0; i < currentNode.precedeActionList.size(); i++)
                outputAction(currentNode.precedeActionList[i], i + 1);
            cout << "找到正确结果:" << endl;
            for (int i = 0; i < 3; i++)
            {
                cout << " " << currentNode.puzzle[i * 3 + 0].puzzleId << "  " << currentNode.puzzle[i * 3 + 1].puzzleId << "  " << currentNode.puzzle[i * 3 + 2].puzzleId << endl;
            }
            cout << endl;
            result[0] = 1;
            result[1] = currentNode.depth;
            return result;
        }
        if (visited[visitedNum(currentNode)] == 1)
            continue;
        visited[visitedNum(currentNode)] = 1;
        if (currentNode.nextActionList.size() == 0)
            currentNode = updatePuzzleNodeActionList(currentNode);
        for (int i = 0; i < currentNode.nextActionList.size(); i++)
        {
            nextNode = moveToPuzzleNode(currentNode.nextActionList[i], currentNode);
            if (!currentNode.precedeActionList.empty())
                for (int j = 0; j < currentNode.precedeActionList.size(); j++)
                    nextNode.precedeActionList.push_back(currentNode.precedeActionList[j]);
            nextNode.precedeActionList.push_back(currentNode.nextActionList[i]);
            if (visited[visitedNum(nextNode)] == 1)
                continue;
            nextNode.depth = currentNode.depth + 1;
            nextNode.height = heuristicFunction(nextNode, objPuzzleNode);
            puzzleNodePriorityQueue.push(nextNode);
        }
    }

    return result;
}

// 启发式搜素2
vector<int> heuristicSearchInformedByManhattonDis(PUZZLE_NODE initialNode, PUZZLE_NODE objPuzzleNode)
{
    // result[0] 1:correct;0:wrong
    // result[1] 步数 steps
    vector<int> result(2, 0);
    cout << "初始节点状态：" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << " " << initialNode.puzzle[i * 3 + 0].puzzleId << "  " << initialNode.puzzle[i * 3 + 1].puzzleId << "  " << initialNode.puzzle[i * 3 + 2].puzzleId << endl;
    }
    cout << endl;
    /*
        请在该位置完成启发式搜索，启发式函数使用不正确位置的数码个数。
    */
    initialNode.depth = 0;
    priority_queue<PUZZLE_NODE, vector<PUZZLE_NODE>, greater<PUZZLE_NODE>> puzzleNodePriorityQueue;
    PUZZLE_NODE currentNode, nextNode;
    initialNode.height = ManhattonDis(initialNode, objPuzzleNode);
    puzzleNodePriorityQueue.push(initialNode);
    while (!puzzleNodePriorityQueue.empty())
    {
        currentNode = puzzleNodePriorityQueue.top();
        puzzleNodePriorityQueue.pop();
        if (checkObject(currentNode, objPuzzleNode))
        {
            for (int i = 0; i < currentNode.precedeActionList.size(); i++)
                outputAction(currentNode.precedeActionList[i], i + 1);
            cout << "找到正确结果:" << endl;
            for (int i = 0; i < 3; i++)
            {
                cout << " " << currentNode.puzzle[i * 3 + 0].puzzleId << "  " << currentNode.puzzle[i * 3 + 1].puzzleId << "  " << currentNode.puzzle[i * 3 + 2].puzzleId << endl;
            }
            cout << endl;
            result[0] = 1;
            result[1] = currentNode.depth;
            return result;
        }
        if (visited[visitedNum(currentNode)] == 1)
            continue;
        visited[visitedNum(currentNode)] = 1;
        if (currentNode.nextActionList.size() == 0)
            currentNode = updatePuzzleNodeActionList(currentNode);
        for (int i = 0; i < currentNode.nextActionList.size(); i++)
        {
            nextNode = moveToPuzzleNode(currentNode.nextActionList[i], currentNode);
            if (!currentNode.precedeActionList.empty())
                for (int j = 0; j < currentNode.precedeActionList.size(); j++)
                    nextNode.precedeActionList.push_back(currentNode.precedeActionList[j]);
            nextNode.precedeActionList.push_back(currentNode.nextActionList[i]);
            if (visited[visitedNum(nextNode)] == 1)
                continue;
            nextNode.depth = currentNode.depth + 1;
            nextNode.height = ManhattonDis(nextNode, objPuzzleNode);
            puzzleNodePriorityQueue.push(nextNode);
        }
    }
    return result;
}

// 广度优先搜索
vector<int> binaryFirstSearchDemo(PUZZLE_NODE initialNode, PUZZLE_NODE objPuzzleNode)
{
    // result[0] 1:correct;0:wrong
    // result[1] 步数 steps
    vector<int> result(2, 0);

    cout << "初始节点状态：" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << " " << initialNode.puzzle[i * 3 + 0].puzzleId << "  " << initialNode.puzzle[i * 3 + 1].puzzleId << "  " << initialNode.puzzle[i * 3 + 2].puzzleId << endl;
    }
    cout << endl;
    /*
        请在该位置完成广度优先搜索函数。
    */
    PUZZLE_NODE puzzleNode = initialNode;
    queue<PUZZLE_NODE> puzzleNodeQueue;
    puzzleNode.depth = 0;
    int depth = 0;
    puzzleNodeQueue.push(puzzleNode);
    while (puzzleNodeQueue.size())
    {
        PUZZLE_NODE currentPuzzleNode = puzzleNodeQueue.front();
        if (checkObject(currentPuzzleNode, objPuzzleNode))
        {

            for (int i = 0; i < currentPuzzleNode.precedeActionList.size(); i++)
            {
                outputAction(currentPuzzleNode.precedeActionList[i], i + 1);
            }
            cout << "找到正确结果:" << endl;
            for (int i = 0; i < 3; i++)
            {
                cout << " " << currentPuzzleNode.puzzle[i * 3 + 0].puzzleId << "  " << currentPuzzleNode.puzzle[i * 3 + 1].puzzleId << "  " << currentPuzzleNode.puzzle[i * 3 + 2].puzzleId << endl;
            }
            cout << endl;

            result[0] = 1;
            result[1] = currentPuzzleNode.depth;
            return result;
        }
        else
        {
            visited[visitedNum(currentPuzzleNode)] = 1;
            if (currentPuzzleNode.nextActionList.size() == 0)
            {
                currentPuzzleNode = updatePuzzleNodeActionList(currentPuzzleNode);
            }
            puzzleNodeQueue.pop();
            for (int i = 0; i < currentPuzzleNode.nextActionList.size(); i++)
            {
                PUZZLE_NODE nextPuzzleNode = moveToPuzzleNode(currentPuzzleNode.nextActionList[i], currentPuzzleNode);
                if (!currentPuzzleNode.precedeActionList.empty())
                {
                    for (int actionIndex = 0; actionIndex < currentPuzzleNode.precedeActionList.size(); actionIndex++)
                    {
                        nextPuzzleNode.precedeActionList.push_back(currentPuzzleNode.precedeActionList[actionIndex]);
                    }
                }
                nextPuzzleNode.precedeActionList.push_back(currentPuzzleNode.nextActionList[i]);
                if (visited[visitedNum(nextPuzzleNode)] == 1)
                {
                    continue;
                }
                nextPuzzleNode.depth = currentPuzzleNode.depth + 1;
                puzzleNodeQueue.push(nextPuzzleNode);
            }
        }
    }
    return result;
}

int main()
{
    srand((unsigned)time(0)); // time()用系统时间初始化种。为rand()生成不同的随机种子。
    PUZZLE_NODE objPuzzleNode;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            objPuzzleNode.puzzle[i * 3 + j].puzzleId = i * 3 + j;
            objPuzzleNode.puzzle[i * 3 + j].xPosition = i;
            objPuzzleNode.puzzle[i * 3 + j].yPosition = j;
        }
    }
    objPuzzleNode = updatePuzzleNodeActionList(objPuzzleNode);

    int setup = 0;
    while (setup != -1)
    {

        visited.clear();

        cout << "请输入调试设置(-1:退出; 0:广度优先搜索示例;1:广度优先搜索;2：深度有限搜索;3:启发式搜索1;4:启发式搜索2):" << endl;
        cin >> setup;
        int backwardSteps;
        cout << "请输入大于等于5小于等于20的回退步数" << endl;
        cin >> backwardSteps;
        while (backwardSteps < 5 || backwardSteps > 20)
        {
            cout << "输入错误，请输入大于等于5小于等于20的回退步数" << endl;
            cin >> backwardSteps;
        }

        PUZZLE_NODE initialNode = initialPuzzleNode(backwardSteps);

        vector<int> result;
        if (setup == 1)
        {
            result = binaryFirstSearch(initialNode, objPuzzleNode);
        }
        else if (setup == 2)
        {
            result = depthFirstSearch(initialNode, objPuzzleNode);
        }
        else if (setup == 3)
        {
            result = heuristicSearchInformedByIncorrectNum(initialNode, objPuzzleNode);
        }
        else if (setup == 4)
        {
            result = heuristicSearchInformedByManhattonDis(initialNode, objPuzzleNode);
        }
        else if (setup == 0)
        {
            cout << "广度优先搜索示例程序" << endl;
            result = binaryFirstSearchDemo(initialNode, objPuzzleNode);
        }
        else
        {
            cout << "输入设置有误，请重新运行" << endl;
            return 0;
        }

        if (result[0] == 1)
        {
            cout << "结果为correct,步数为" << result[1] << endl;
        }
        else
        {
            cout << "结果为wrong" << endl;
        }
    }
    return 0;
}