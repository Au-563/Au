//多项式
class Polynomial;
class Term
{
    friend Polynomial;
private:
    float coef;			//系数
    int exp;			//指数
public:
    Term(){};
    Term(float coef,int exp):coef(coef),exp(exp){};
    void Set(float coef,int exp){
        this->coef=coef,this->exp=exp;
    }
};

class Polynomial
{
private:
    Term* termArray;    //非零项数组
    int terms;          //非零项数
    int capacity;       //最大容量（默认为terms+5）
public:
    Polynomial();                               //默认构造函数（开辟termArray[5]）
    Polynomial(Term* t,int terms);              //缺省构造函数
    float Eval(float x);                        //计算多项式变量为x的值
    void Print();                               //打印多项式
    Polynomial Add(Polynomial ploy);            //多项式相加
    Polynomial Mult(Polynomial poly);           //多项式相乘
    void TailInsertTerm(Term t);                //尾插节点(用于Add)
    void InsertTerm(Term t);                    //插入节点(用于Mult)
};

Polynomial::Polynomial()
{
    this->termArray=new Term[5];
    this->terms=0;
    this->capacity=5;
}

Polynomial::Polynomial(Term* t,int terms):terms(terms)
{
    this->termArray=new Term[this->terms];
    for(int i=0;i<this->terms;i++){
        this->termArray[i]=t[i];
    }
    this->capacity=this->terms+5;
}

float Polynomial::Eval(float x)     
{
    int temp=0;
    for(int i=0;i<this->terms;i++)
    {
        temp+=this->termArray[i].coef*pow(x,this->termArray[i].exp);
    }
    return temp;
}

void Polynomial::Print()
{
    for(int i=0;i<terms;i++){
        if(i==0){
            if(termArray[i].exp==0) cout<<termArray[i].coef<<" ";
            else cout<<termArray[i].coef<<"x^"<<termArray[i].exp<<" ";
        }
        else{
            if(termArray[i].coef>0){
                if(termArray[i].exp==0) cout<<"+"<<termArray[i].coef<<" ";
                else cout<<"+"<<termArray[i].coef<<"x^"<<termArray[i].exp<<" ";
            }
            else{
                if(termArray[i].exp==0) cout<<termArray[i].coef<<" ";
                else cout<<termArray[i].coef<<"x^"<<termArray[i].exp<<" ";
            }
        }
    }
}

Polynomial Polynomial::Add(Polynomial poly)
{
    Polynomial tempPoly;
    int aPos=0,bPos=0;                          //记录this->terms与poly的下标
    while(aPos<this->terms&&bPos<poly.terms)
    {
        if(this->termArray[aPos].exp==poly.termArray[bPos].exp){
            if(this->termArray[aPos].coef+poly.termArray[bPos].coef!=0)     //指数相同且系数和非0   
                tempPoly.TailInsertTerm(Term(this->termArray[aPos].coef+poly.termArray[bPos].coef,this->termArray[aPos].exp));
            aPos++,bPos++;
        }
        else if(this->termArray[aPos].exp<poly.termArray[bPos].exp)         //存入指数更小的系数
            tempPoly.TailInsertTerm(Term(this->termArray[aPos].coef,this->termArray[aPos].exp)),aPos++;
        else
            tempPoly.TailInsertTerm(Term(poly.termArray[bPos].coef,poly.termArray[bPos].exp)),bPos++;
    }
    while(aPos<this->terms&&tempPoly.terms<=tempPoly.capacity)              //拷贝数组剩余元素
    {
        tempPoly.TailInsertTerm(Term(this->termArray[aPos].coef,this->termArray[aPos].exp)),aPos++;
    }
    while(bPos<poly.terms&&tempPoly.terms<=tempPoly.capacity)               //拷贝数组剩余元素
    {
        tempPoly.TailInsertTerm(Term(poly.termArray[bPos].coef,poly.termArray[bPos].exp)),bPos++;
    }
    return tempPoly;
}

Polynomial Polynomial::Mult(Polynomial poly)
{
    Polynomial tempPoly;
    int coef=0,exp=0;
    for(int i=0;i<this->terms;i++){
        for(int j=0;j<poly.terms;j++){
            coef=this->termArray[i].coef*poly.termArray[j].coef;
            exp=this->termArray[i].exp+poly.termArray[j].exp;
            tempPoly.InsertTerm(Term(coef,exp));
        }
    }
    return tempPoly;
}

void Polynomial::TailInsertTerm(Term t) //尾插节点
{
    if(this->terms==this->capacity){   //及时扩容
        this->capacity*=2;
        Term* tempTerm=new Term[this->capacity];
        for(int i=0;i<this->terms;i++){
            tempTerm[i]=this->termArray[i];
        }
        delete[]this->termArray;                                    
        this->termArray=tempTerm;          
    }    
    this->termArray[terms].exp=t.exp;
    this->termArray[terms++].coef=t.coef;
}

void Polynomial::InsertTerm(Term t)     //插入节点
{
    if(this->terms==this->capacity){   				//及时扩容
        this->capacity*=2;
        Term* tempTerm=new Term[this->capacity];
        for(int i=0;i<this->terms;i++){
            tempTerm[i]=this->termArray[i];
        }
        delete[]this->termArray;                                    
        this->termArray=tempTerm;          
    }  
    int idx=this->terms;                            //标记插入节点位置
    for(int i=0;i<this->terms-1;i++){
        if(this->termArray[i].exp==t.exp){
            idx=i;break;
        }
        if(this->termArray[i].exp<t.exp&&this->termArray[i+1].exp>t.exp){
            idx=i+1;break;
        }
    }
    if(this->termArray[0].exp>=t.exp)idx=0;
    if(this->termArray[terms-1].exp==t.exp)idx=terms-1;
    if(this->termArray[idx].exp==t.exp){               //查找到指数相同节点
        this->termArray[idx].coef+=t.coef;
        if(this->termArray[idx].coef==0){            //若系数和为零
            for(int i=idx;i<this->terms-1;i++)this->termArray[i]=this->termArray[i+1];
            this->terms--;
        }
    }
    else{                                            //未查找到指数相同节点
        for(int i=this->terms;i>idx;i--){
            this->termArray[i]=this->termArray[i-1];
        }
        this->termArray[idx].exp=t.exp;
        this->termArray[idx].coef=t.coef;
        this->terms++;
    }
}