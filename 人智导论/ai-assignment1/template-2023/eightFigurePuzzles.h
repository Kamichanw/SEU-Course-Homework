#pragma once
#include <iostream>
#include <vector>
using namespace std;
const int puzzleNum = 8;
/*
 *描述：记录8数码九宫格内每一个格子对应的位置信息与存放的数码。
 * xPosition :行数 0 代表第一行
 * yPosition: 列数 0 代表第一行
 * puzzleId: 数码 0~8
 */
typedef struct
{
    int xPosition;
    int yPosition;
    int puzzleId;
} PUZZLE;

/*
*描述：声明一个节点，存储当前九宫格状态
*      以目标状态为例，puzzle: {{0,0,0},{0,1,1},{0,2,2},
                           {1,0,3},{1,1,4},{1,2,5},
                           {2,0,6},{2,1,7},{2,2,8},}

                  nextActionList: {[1,0]    向上移动
                                   [-1,0]   向下移动
                                   [0,1]    向左移动
                                   [0.-1]}  向右移动

                  nextAxtionList的大小<=4

                  depth： 当前状态所处深度
*/
typedef struct
{
    // vector<PUZZLE> puzzles;
    PUZZLE puzzle[9];
    vector<vector<int>> nextActionList;
    vector<vector<int>> precedeActionList;
    int depth;
    int height; // 用于计算启发式函数

} PUZZLE_NODE;

/*
 * 输入：节点状态puzzleNode
 * 输出  空格位置，二维数组。
 * 描述：找到 空格 0 所在的位置,返回1个2维数组，分别代表行数和列数;
 */
vector<int> findZeroPosition(PUZZLE_NODE puzzleNode);

/*
 *
 * 输入：节点状态puzzleNode
 * 输出：actionList初始化后的puzzleNode
 *描述：更新puzzleNode的后继可操作动作状态，其中 （1，0）代表空格向上移动，（-1，0）代表空格向下移动，（0，1）代表空格向左移动，（0，-1）代表空格向右移动。
 */
PUZZLE_NODE updatePuzzleNodeActionList(PUZZLE_NODE puzzleNode);

/*
 * 输入：给定动作数组，例如[1,0],代表空格向上移动
 * 输出：puzzleNode在执行完输入动作后得到的新的数码状态
 * 描述：给定动作action（action为二维数组）和puzzleNode,返回执行该动作后新的节点
 */
PUZZLE_NODE moveToPuzzleNode(vector<int> action, PUZZLE_NODE puzzleNode);

/*
 * 输入：puzzleNode的后继动作数量的大小
 * 输出：随机动作索引
 * 描述：用于生成PuzzleNode中随机动作索引，用于随机后退。
 */
int getRandomNumber(int actionSize);

/*
 * 输入：puzzle1:当前状态某一位置上的状态，puzzle2：目标状态某一位置上的状态
 * 输出：true:相等 false:不相等
 * 描述：判断当前节点状态和目标节点状态在同一位置上两个8数码状态是否相同。
 */
bool isEqual(PUZZLE puzzle1, PUZZLE puzzle2);

/*
 * 输入：当前数码节点状态currentNode，目标数码节点状态objNode
 * 输出：两个节点状态是否匹配，如果匹配，说明找到目标状态，返回true;
 *                             如果不匹配，说明还未找到目标状态，返回false;
 *描述：检测当前节点和目标节点状态是否相同。
 */
bool checkObject(PUZZLE_NODE currentNode, PUZZLE_NODE objNode);

/*
 * 输入：回退步数
 * 输出：给定目标状态回退backwardSteps后的初始状态
 * 描述：给定回退步数，返回初始节点状态
 */
PUZZLE_NODE initialPuzzleNode(int backwardSteps);

/*
 * 输入：动作
 * 输出：给定目标状态回退backwardSteps后的初始状态
 * 描述：输出动作
 */
void outputAction(vector<int> action, int index);

// 用于生成当前状态对应的唯一数字，用于eightFigureFramework中visited判断当前节点状态是否访问过。
int visitedNum(PUZZLE_NODE puzzleNode);