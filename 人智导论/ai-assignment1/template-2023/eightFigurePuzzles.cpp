#include "eightFigurePuzzles.h"
#include <chrono>
#include <thread>
#include <time.h>
#ifdef _WIN32  // Check if the code is being compiled on a Windows system
#include <windows.h>
#endif

// 找到 空格 0 所在的位置
vector<int> findZeroPosition(PUZZLE_NODE puzzleNode) {
    vector<int> res(2, 0);
    for (int i = 0; i < puzzleNum + 1; i++) {
        if (puzzleNode.puzzle[i].puzzleId == 0) {
            res[0] = puzzleNode.puzzle[i].xPosition;
            res[1] = puzzleNode.puzzle[i].yPosition;
            return res;
        }
    }
    return res;
}

// 更新puzzleNode的后继可操作动作状态，其中
// （1，0）代表空格向上移动，（-1，0）代表空格向下移动，（0，1）代表空格向左移动，（0，-1）代表空格向右移动。
PUZZLE_NODE updatePuzzleNodeActionList(PUZZLE_NODE puzzleNode) {
    auto xyPosition = findZeroPosition(puzzleNode);
    int x = xyPosition[0];
    int y = xyPosition[1];
    if (x >= 1)
        puzzleNode.nextActionList.push_back({1, 0});
    if (x <= 1) 
        puzzleNode.nextActionList.push_back({-1, 0});
    if (y >= 1) 
        puzzleNode.nextActionList.push_back({0, 1});
    if (y <= 1) 
        puzzleNode.nextActionList.push_back({0, -1});
    return puzzleNode;
}

void outputAction(vector<int> action, int index) {
    /*cout << action[0] << " " << action[1] << endl;*/
    if (action[0] == 1 && action[1] == 0) {
        cout << "步数 " << index << ":向上移动" << endl;
        cout << endl;
    }
    else if (action[0] == -1 && action[1] == 0) {
        cout << "步数 " << index << "向下移动" << endl;
        cout << endl;
    }
    else if (action[0] == 0 && action[1] == 1) {
        cout << "步数 " << index << "向左移动" << endl;
        cout << endl;
    }
    else {
        cout << "步数 " << index << "向右移动" << endl;
        cout << endl;
    }
}

// 给定动作action（action为二维数组）和puzzleNode,返回执行该动作后新的节点
PUZZLE_NODE moveToPuzzleNode(vector<int> action, PUZZLE_NODE puzzleNode) {
    // cout << action[0] << " " << action[1] << endl;
    // if (action[0] == 1 && action[1] == 0) {
    //	cout << "向上移动" << endl;
    // }
    // else if (action[0] == -1 && action[1] == 0) {
    //	cout << "向下移动" << endl;
    // }
    // else if (action[0] == 0 && action[1] == 1) {
    //	cout << "向左移动" << endl;
    // }
    // else {
    //	cout << "向右移动" << endl;
    // }

    auto xyPosition = findZeroPosition(puzzleNode);
    int x = xyPosition[0];
    int y = xyPosition[1];
    PUZZLE_NODE nextPuzzleNode;
    for (int xPos = 0; xPos < 3; xPos++) {
        for (int yPos = 0; yPos < 3; yPos++) {
            nextPuzzleNode.puzzle[xPos * 3 + yPos].xPosition = xPos;
            nextPuzzleNode.puzzle[xPos * 3 + yPos].yPosition = yPos;
            if (xPos == x && yPos == y) {
                nextPuzzleNode.puzzle[xPos * 3 + yPos].puzzleId =
                    puzzleNode.puzzle[((x - action[0]) * 3 + (y - action[1]))].puzzleId;
            }
            else if (xPos == (x - action[0]) && yPos == (y - action[1])) {
                nextPuzzleNode.puzzle[xPos * 3 + yPos].puzzleId = puzzleNode.puzzle[(x * 3 + y)].puzzleId;
            }
            else {
                nextPuzzleNode.puzzle[xPos * 3 + yPos].puzzleId = puzzleNode.puzzle[xPos * 3 + yPos].puzzleId;
            }
        }
    }
    return nextPuzzleNode;
}

// 用于生成PuzzleNode中随机动作索引
int getRandomNumber(int actionSize) {
    return rand() % actionSize;  // 生成1~100随机数
}

// 给定回退步数，返回初始状态
PUZZLE_NODE initialPuzzleNode(int backwordSteps) {
    PUZZLE_NODE objNode;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            objNode.puzzle[i * 3 + j].puzzleId = i * 3 + j;
            objNode.puzzle[i * 3 + j].xPosition = i;
            objNode.puzzle[i * 3 + j].yPosition = j;
        }
    }
    PUZZLE_NODE initialPuzzleNode = updatePuzzleNodeActionList(objNode);

    for (int i = 0; i < backwordSteps; i++) {
        PUZZLE_NODE precedePuzzleNode = initialPuzzleNode;
        // 代替 Sleep(100)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        int action = getRandomNumber(initialPuzzleNode.nextActionList.size());
        initialPuzzleNode = moveToPuzzleNode(initialPuzzleNode.nextActionList[action], initialPuzzleNode);
        initialPuzzleNode = updatePuzzleNodeActionList(initialPuzzleNode);
    }
    initialPuzzleNode = updatePuzzleNodeActionList(initialPuzzleNode);
    return initialPuzzleNode;
}

// 判断两个8数码状态是否相同
bool isEqual(PUZZLE puzzle1, PUZZLE puzzle2) {
    if (puzzle1.xPosition == puzzle2.xPosition && puzzle1.yPosition == puzzle2.yPosition
        && puzzle1.puzzleId == puzzle2.puzzleId)
        return true;
    else
        return false;
}

// 检测当前节点和目标节点状态是否相同
bool checkObject(PUZZLE_NODE currentNode, PUZZLE_NODE objNode) {
    for (int i = 0; i < puzzleNum + 1; i++) {
        if (!isEqual(currentNode.puzzle[i], objNode.puzzle[i]))
            return false;
    }
    return true;
}

// 判断当前节点状态是否被访问过。
int visitedNum(PUZZLE_NODE puzzleNode) {
    int mapValue = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mapValue = mapValue * 10 + puzzleNode.puzzle[i * 3 + j].puzzleId;
        }
    }
    return mapValue;
}