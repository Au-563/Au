template<class T>
class Stack {
private:
    T* stack;          
    int top;           
    int capacity;      
public:
    Stack():capacity(0),top(-1){};
    Stack(int capacity);               
    bool IsEmpty() const;
    int Size() const;
    T& Top() const;           
    void Push(const T& item);   
    void Pop();                
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
