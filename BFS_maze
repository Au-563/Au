#include<iostream>
#include<queue>
using namespace std;

// 定义方向常量
enum Dir{E,S,W,N};

// 定义一个结构体 Offsets 来存储方向的位移
struct Offsets{
    int dx; // x方向的位移
    int dy; // y方向的位移
};

// 动态分配 Offsets 数组，用于存储四个方向的位移
Offsets* moves=new Offsets[4];

// 设置每个方向的位移
void SetMoves(){
    moves[E].dx=0, moves[E].dy=1;   // 东：x不变，y增加
    moves[S].dx=1, moves[S].dy=0;   // 南：x增加，y不变
    moves[W].dx=0, moves[W].dy=-1;  // 西：x不变，y减少
    moves[N].dx=-1, moves[N].dy=0;  // 北：x减少，y不变
}

// 定义一个类 Item 用于表示队列中的节点
class Item{
public:
    int x;              // 节点的 x 坐标
    int y;              // 节点的 y 坐标
    int dir = E;        // 当前方向，初始为东
    // 默认构造函数，初始化坐标为 (0, 0)
    Item() : x(0), y(0) {}                             
    // 带参构造函数
    Item(int x, int y, int dir) : x(x), y(y), dir(dir) {} 
};

// 主路径查找函数，寻找从起点 'S' 到终点 'G' 的最短路径
int path(const int rows, const int cols, char **maze) {
    // 定位起点 S
    int start_x = 0, start_y = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] == 'S') { 
                start_x = i; 
                start_y = j;
            }
        }
    }
    
    // 引入队列进行广度优先搜索
    queue<Item> Q; 
    Item temp(start_x, start_y, E); 
    Q.push(temp); 

    // 记录当前层搜索的节点数和下一层的节点数
    int count = 1, n_count = 0;
    // 记录搜索步数
    int steps = 0;
    // 将起点标记为已访问
    maze[start_x][start_y] = '#'; 

    // 当队列不为空时进行循环
    while (!Q.empty()) {
        temp = Q.front();   // 获取队首元素
        Q.pop();            // 弹出队首元素
        count--;            // 当前层节点数减一

        int x = temp.x;     // 当前节点的 x 坐标
        int y = temp.y;     // 当前节点的 y 坐标
        int d = temp.dir;   // 当前方向

        // 遍历四个方向
        while (d < 4) {
            // 计算下一个节点的坐标
            int n_x = x + moves[d].dx; 
            int n_y = y + moves[d].dy; 
            
            // 检查下一个节点是否在迷宫范围内且不是墙
            if ((n_x >= 0 && n_x < rows && n_y >= 0 && n_y < cols) && maze[n_x][n_y] != '#') {
                if (maze[n_x][n_y] == 'G') {    // 如果找到目标 G，返回步数
                    return ++steps;             
                }
                n_count++;                  // 更新下一层节点数
                Q.push(Item(n_x, n_y, E));  // 将新节点加入队列
                maze[n_x][n_y] = '#';       // 将新节点标记为已访问
            }
            d++;    // 转向下一个方向
        }
        
        // 如果当前层搜索完成
        if (count == 0) {
            steps++;            // 增加步数
            count = n_count;    // 当前层节点数变为下一层的节点数
            n_count = 0;        // 重置下一层节点数
        }
    }
    return -1; // 如果无法到达终点，返回 -1
}

int main() {
    // 初始化方向偏移
    SetMoves();

    // 设置迷宫的布局
    int rows = 0, cols = 0; 
    cin >> rows >> cols; 
    char** maze = new char*[rows];
    for (int i = 0; i < rows; i++) {
        maze[i] = new char[cols]; 
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> maze[i][j];
        }
    }

    // 输出从起点 S 到终点 G 的最短路径长度
    cout << path(rows, cols, maze);

    // 释放动态分配的内存
    for (int i = 0; i < rows; i++) {
        delete[] maze[i]; 
    }
    delete[] maze; 
    return 0; 
}
