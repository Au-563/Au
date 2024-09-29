#include<iostream>
using namespace std;

// 栈类
template<class T>
class Stack {
private:
    T* stack;          // 动态数组，存储栈的元素
    int top;           // 栈顶索引
    int capacity;      // 栈的容量
public:
    Stack():capacity(0),top(-1){};      // 默认构造函数
    Stack(int capacity);                // 带参数的构造函数
    T& operator[](int idx);             // 重载[]运算符，用于访问栈中的元素
    bool IsEmpty() const;               // 检查栈是否为空
    int Size() const;                   // 获取栈的当前大小
    T& Top() const;                     // 获取栈顶元素
    void Push(const T& item);           // 压入栈元素
    void Pop();                         // 弹出栈顶元素
};

// 定义一个移动方向的枚举，以便于每次移动后位置的修改
enum Directions{N,NE,E,SE,S,SW,W,NW};

// 定义坐标偏移结构，用于描述八个方向的偏移
struct Offsets
{
    int a; // x方向的偏移量
    int b; // y方向的偏移量
};

// 定义一个指针数组，用于存储方向偏移
Offsets* moves = new Offsets[8];

// 初始化方向偏移
void setmoves()
{
    moves[0].a=0, moves[0].b=-1;   // 北
    moves[1].a=1, moves[1].b=-1;   // 东北
    moves[2].a=1, moves[2].b=0;    // 东
    moves[3].a=1, moves[3].b=1;    // 东南
    moves[4].a=0, moves[4].b=1;    // 南
    moves[5].a=-1, moves[5].b=1;   // 西南
    moves[6].a=-1, moves[6].b=0;   // 西
    moves[7].a=-1, moves[7].b=-1;  // 西北
}

// 表示迷宫中的一个点
class Item
{
public:
    int x;                          // x坐标
    int y;                          // y坐标
    int dir = 0;                    // 当前方向（初始化为北）
    Item():x(0),y(0){}              // 默认构造函数
    Item(int x, int y):x(x),y(y){}  // 带参数构造函数
};

// 重载<<运算符，用于输出Item对象
ostream& operator<<(ostream& os, Item& t) {    
    os << t.x << "\t" << t.y << endl;   
    return os;
}

// m*p的矩阵的迷宫，入口坐标（start_x，start_y），出口坐标（end_x,end_y），起始方向start_dir
void path(const int m, const int p, int start_x, int start_y, int start_dir, int end_x, int end_y, int** maze)
{
    // 创建并初始化mark数组用于标记，已走过或墙壁为1，其余为0
    int** mark = new int*[m];
    for(int i = 0; i < m; i++) {
        mark[i] = new int[p];
        for(int j = 0; j < p; j++) {
            mark[i][j] = maze[i][j];    // 将迷宫信息复制到mark中
        }
    }

    // 标记起点为已走过
    mark[start_x][start_y] = 1;
    Stack<Item> stack((m - 2) * (p - 2));   // 创建一个足够大的栈用于存储走过路径
    Item temp(start_x + moves[start_dir].a, start_y + moves[start_dir].b);  // 计算起始位置
    stack.Push(temp);   // 压入起始位置

    while(!stack.IsEmpty()) {   // 当栈不为空时
        temp = stack.Top();     // 获取栈顶元素
        stack.Pop();            // 弹出栈顶元素
        int x = temp.x, y = temp.y, d = temp.dir; // 解构坐标和方向

        while(d < 8) { // 遍历所有方向
            // 获取下一次移动后位置（g，h）
            int g = x + moves[d].a, h = y + moves[d].b;

            if(g == end_x && h == end_y) {  // 如果到达出口
                stack.Push(Item(x, y));     // 将当前坐标入栈
                stack.Push(Item(g, h));     // 将出口坐标入栈
                for(int i = 0; i < stack.Size(); i++) {
                    cout << stack[i];       // 输出栈中的所有坐标
                }
                return;                     // 找到路径，返回
            }

            if(!mark[g][h]) {               // 如果新方向可行
                mark[g][h] = 1;             // 标记为已走过
                temp.x = x, temp.y = y, temp.dir = d + 1;   // 保存坐标，更新方向
                stack.Push(temp);           
                x = g, y = h, d = N;        // 更新临时坐标与方向
            } else {
                d++;    // 如果不可行，检查下一个方向
            }
        }
    }
}

int main()
{
    setmoves(); // 初始化方向偏移
    int** maze = new int*[8];   // 动态创建迷宫数组（8*10）
    for(int i = 0; i < 8; i++) {
        maze[i] = new int[10];  
    }
    // 定义迷宫结构
    int arr0[10] = {1, 1, 0, 1, 1, 1, 1, 1, 1, 1};
    int arr1[10] = {1, 1, 0, 1, 1, 1, 0, 1, 0, 1};
    int arr2[10] = {1, 1, 1, 0, 0, 0, 0, 0, 1, 1};
    int arr3[10] = {1, 1, 1, 1, 1, 1, 1, 1, 0, 1};
    int arr4[10] = {1, 0, 0, 0, 0, 0, 0, 0, 1, 1};
    int arr5[10] = {1, 1, 0, 1, 1, 1, 1, 1, 0, 1};
    int arr6[10] = {1, 1, 1, 0, 1, 1, 1, 0, 1, 1};
    int arr7[10] = {1, 1, 0, 1, 1, 1, 1, 1, 1, 1};
    maze[0] = arr0;
    maze[1] = arr1;
    maze[2] = arr2;
    maze[3] = arr3;
    maze[4] = arr4;
    maze[5] = arr5;
    maze[6] = arr6;
    maze[7] = arr7;    
    path(8, 10, 0, 2, S, 7, 2, maze);   // 调用路径寻找函数
    return 0;
}

template<class T>
Stack<T>::Stack(int capacity) : capacity(capacity) 
{
    if (capacity < 1) {
        throw "Stack capacity must be > 0"; 
    }
    stack = new T[capacity]; 
    top = -1;                
}

template<class T>
T& Stack<T>::operator[](int idx)
{
    if(idx >= this->Size()) {
        throw "Error operation"; 
    }
    return this->stack[idx];
}

template<class T>
bool Stack<T>::IsEmpty() const
{
    return top==-1;
}

template<class T>
int Stack<T>::Size() const
{
    return top+1;;
}

template<class T>
T& Stack<T>::Top() const
{
    if(IsEmpty()){
        throw "Stack is empty";
    }
    return stack[top];
}

template<class T>
void Stack<T>::Push(const T& x)
{
    if(capacity==0){
        this->stack=new T;
        capacity++;
    }
    if(top==capacity-1){
        capacity*=2;
        T* temp=new T[capacity];
        for(int i=0;i<=top;i++){
            temp[i]=this->stack[i];
        }
        delete[]this->stack;
        this->stack=temp;
    }
    stack[++top]=x;
}

template<class T>
void Stack<T>::Pop()
{
    if(IsEmpty()){
        throw"Stack is empty";
    }
    top--;
}