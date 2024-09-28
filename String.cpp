class String 
{
private:
    char* str;
    int* f;
public:
    String(){};
    String(char* init,int m);
    bool operator==(String t);      //判断*this字符串是否等于t
    bool operator!();               //若*this为空返回true
    void Print();                   //打印字符串
    int Length();                   //返回字符数目
    int Find(String pat);           //若pat与*this字符串的子串相匹配，返回索引，否则返回-1
    void FailureFunction();         //获取失效函数
    int FastFind(String pat);       //KMP算法
    String Concat(String t);        //将t连接为*this字符串的后缀
    String Substr(int i,int j);     //返回i到j-i+1共计j个字符串
};

String::String(char* init,int m)
{
    this->str=new char[m+1];
    for(int i=0;i<m;i++)
    {
        this->str[i]=init[i];
    }
    this->str[m]='\0';
}

bool String::operator==(String t)
{
    if(this->Length()!=t.Length()){
        return 0;
    }
    for(int i=0;str[i]!='\0';i++){
        if(str[i]!=t.str[i]){
            return 0;
        }
    }
    return 1;
}

bool String::operator!()
{
    return this->str==NULL?0:1;
}

int String::Length()
{
    int count=0;
    for(int i=0;this->str[i]!='\0';i++){
        count++;
    }
    return count;
}

void String::Print()
{
    for(int i=0;i<this->Length();i++){
        cout<<this->str[i];
    }
    cout<<endl;
}

int String::Find(String pat)
{
    for(int start=0;start<=this->Length()-pat.Length();start++){
        int j=0;
        while(j<pat.Length()&&this->str[start+j]==pat.str[j]){
            j++;
        }
        if(j==pat.Length()){
            return start;
        }
    }   
    return -1;
}

void String::FailureFunction()
{
    this->f=new int[this->Length()];
    f[0]=-1;
    for(int j=1;j<this->Length();j++){
        int i=f[j-1];
        while(str[j]!=str[i+1]&&i>=0){
            i=f[i];
        }
        if(str[j]==str[i+1]){
            f[j]=i+1;
        }
        else{
            f[j]=-1;
        }
    }
}

int String::FastFind(String pat)
{
    int posP=0,posS=0;
    while(posP<pat.Length()&&posS<this->Length()){
        if(this->str[posS]==pat.str[posP])
            posS++,posP++;
        else{
            if(posP==0)
                posS++;
            else{
                posP=pat.f[posP-1]+1;
            }
        }
    }
    if(posP=pat.Length())
        return posS-posP;
    return -1;
}

String String::Concat(String t)
{
    if(!this->Length()){    //本字符串为空
        return t;
    }
    if(!t.Length()){        //t为空
        return *this;
    }
    char* tempStr=new char[this->Length()+t.Length()];
    int count=0;
    while(count<this->Length()){
        tempStr[count]=this->str[count];
        count++;
    }
    while(count<this->Length()+t.Length()){
        tempStr[count]=t.str[count-this->Length()];
        count++;
    }
    tempStr[this->Length()+t.Length()]='\0';
    return String(tempStr,this->Length()+t.Length());
}

String String::Substr(int i,int j)
{
    if(j<i){
        throw"Error operations";
    }
    char* tempStr=new char[j-i+2];
    int temp=i;
    while(temp<=j){
        tempStr[temp-i]=this->str[temp];
        temp++;
    }
    return String(tempStr,j-i+1);
}