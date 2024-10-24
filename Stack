template<class T>
class Stack {
private:
    T* stack;          // 动态数组，存储栈的元素
    int top;           // 栈顶索引
    int capacity;      // 栈的容量
public:
    Stack():capacity(0),top(-1){};      // 默认构造函数
    Stack(int capacity);                // 带参数的构造函数
    bool IsEmpty() const;               // 检查栈是否为空
    int Size() const;                   // 获取栈的当前大小
    T& Top() const;                     // 获取栈顶元素
    void Push(const T& item);           // 压入栈元素
    void Pop();                         // 弹出栈顶元素
};

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
