#include<iostream>
#include<stack>
using namespace std;

/*示例
#S######.#
......#..#
.#.##.##.#
.#........
##.##.####
....#....#
.#######.#
....#.....
.####.###.
....#...G#

#S######.#
#.#...####
.#.##.##.#
.#........
##.##.####
....#....#
.#######.#
....#.....
.####.###.
....#...G#
*/

// 定义一个移动方向的枚举，以便于每次移动后位置的修改
enum Directions{E,S,W,N};

// 定义坐标偏移结构，用于描述各个方向的偏移
struct Offsets{
    int dx; //row的偏移量
    int dy; //col的偏移量
};

// 定义一个指针数组，用于存储方向偏移
Offsets* moves=new Offsets[4];

// 初始化方向偏移
void SetMoves(){
    moves[E].dx=0,moves[E].dy=1;    //东
    moves[S].dx=1,moves[S].dy=0;    //南
    moves[W].dx=0,moves[W].dy=-1;   //西
    moves[N].dx=-1,moves[N].dy=0;   //北
}

// 表示迷宫中的一个点
class Item{
public:
    int x;                                          //row
    int y;                                          //col
    int dir=E;                                      //当前方向（初始化为东）
    Item():x(0),y(0){}                              //默认构造函数
    Item(int x, int y,int dir):x(x),y(y),dir(dir){} //含参构造函数
};

// 重载<<运算符，用于输出Item对象
ostream& operator<<(ostream& os, Item& t) {    
    os << t.x << "\t" << t.y << endl;   
    return os;
}

//‘#’、’.’、‘S’、'G’分别表示墙壁、通道、起点、终点
void path(const int rows,const int cols,char **maze){
    // 创建并初始化mark数组用于标记，已走过或墙壁为#，其余为.
    char** mark = new char*[rows];
    for(int i = 0; i < rows; i++) {
        mark[i] = new char[cols];
        for(int j = 0; j < cols; j++) {
            // 将迷宫信息复制到mark中
            mark[i][j] = maze[i][j];    
        }
    }

    // 定位起点S
    int start_x=0,start_y=0;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(mark[i][j]=='S'){
                start_x=i,start_y=j;
            }
        }
    }

    //引入栈
    stack<Item>S;
    //引入临时节点
    Item temp(start_x,start_y,E);
    //压入起始位置
    S.push(temp);

    //栈空退出
    while(!S.empty()){
        //获取栈顶元素并删除
        temp=S.top();
        S.pop();
        //获取坐标、方向
        int x=temp.x;
        int y=temp.y;
        int d=temp.dir;
        //遍历所有方向
        while(d<4){
            //获取下一次移动后位置(n_x,n_y)
            int n_x=x+moves[d].dx;
            int n_y=y+moves[d].dy;
            //下一步在迷宫内
            if(n_x>=0&&n_x<rows&&n_y>=0&&n_y<cols){
                //到达出口
                if(mark[n_x][n_y]=='G'){
                    //将当前坐标与出口坐标入栈
                    if(S.top().x!=x||S.top().y!=y){
                        S.push(Item(x,y,E));
                    }
                    S.push(Item(n_x,n_y,E));
                    //打印路线
                    for(;!S.empty();S.pop()){
                        cout<<S.top();
                    }
                    cout<<start_x<<'\t'<<start_y<<endl;
                    return;
                }
                //未到达出口，下一步可行
                else if(mark[n_x][n_y]=='.'){
                    //标记已走过
                    mark[n_x][n_y]='#';
                    temp.dir++;
                    //入栈，更新方向
                    S.push(Item(n_x,n_y,E));
                    //更新临时坐标与方向
                    x=n_x,y=n_y;d=E;
                }
                //下一步不可行
                else{
                    d++;
                }
            }
            //下一步走出迷宫外
            else{
                d++;
            }
        }
    }
    //未找到出口
    cout<<"No Exist!"<<endl;
}

int main(){
    //初始化方向偏移
    SetMoves();

    //构建迷宫
    int rows=0,cols=0;
    cin>>rows>>cols;
    char** maze=new char*[rows];
    for(int i=0;i<rows;i++){
        maze[i]=new char[cols];
    }
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            cin>>maze[i][j];
        }
    }

    //寻找出口
    path(rows,cols,maze);
    
    return 0;
}
