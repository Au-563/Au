class SparseMatrix;
class MatrixTerm
{
    friend SparseMatrix;
private:
    int row;    //行
    int col;    //列
    int value;  //元素数值
public:
    void set(int r,int c,int v)
    {
        row=r,col=c,value=v;
    }
};

class SparseMatrix			//稀疏矩阵
{
public:
    MatrixTerm* termArray;  //非零项数组
    int rows;               //总行数
    int cols;               //总列数
    int terms;              //非零项数
    int capacity;           //最大容量
public:
    SparseMatrix(){};                                   //默认构造函数
    SparseMatrix(MatrixTerm* m,int terms,int r,int c);  //缺省构造函数
    void Print();                                       //打印矩阵
    SparseMatrix Transpose();                           //矩阵转置
    SparseMatrix FastTranspose();                       //快速转置
    SparseMatrix Add(SparseMatrix b);                   //矩阵加法
    SparseMatrix Mult(SparseMatrix b);                  //矩阵乘法
    void TailInsertTerm(int row, int col, int value);   //尾插元素
    void InsertTerm(int row,int col,int value);         //插入元素
};

SparseMatrix::SparseMatrix(MatrixTerm* m,int terms,int r,int c):terms(terms),rows(r),cols(c),capacity(terms)
{
    if(terms){
        this->termArray=new MatrixTerm[terms];
        for(int i=0;i<terms;i++){
        this->termArray[i]=m[i];
    }
    }
}

void SparseMatrix::Print()
{
    int count=0;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(termArray[count].row==i&&termArray[count].col==j)cout<<termArray[count++].value<<" ";
            else cout<<"0 ";
        }
        cout<<'\n';
    }
}       

SparseMatrix SparseMatrix::Transpose()
{
    if(!this->terms)throw"The matrix is empty";
    else{
        SparseMatrix temp=SparseMatrix(termArray,terms,rows,cols);
        int counter=0;
        for(int i=0;i<this->cols;i++){
            for(int j=0;j<this->terms;j++){
                if(this->termArray[j].col==i){
                    temp.termArray[counter].row=i;
                    temp.termArray[counter].col=this->termArray[j].row;
                    temp.termArray[counter++].value=this->termArray[j].value;
                }
            }
        }
        return temp;
    }
}

SparseMatrix SparseMatrix::FastTranspose()
{
    if(!this->terms)throw"The matrix is empty";
    else{
        SparseMatrix temp=SparseMatrix(termArray,terms,rows,cols);
        int* rowStart=new int[this->cols]{};
        int* rowSize=new int[this->cols]{};
        for(int i=0;i<this->terms;i++)rowSize[this->termArray[i].col]++;
        for(int i=1;i<this->cols;i++)rowStart[i]=rowStart[i-1]+rowSize[i-1];
        for(int i=0;i<this->terms;i++){
            temp.termArray[rowStart[this->termArray[i].col]++]=this->termArray[i];
            swap(temp.termArray[rowStart[this->termArray[i].col]-1].col,temp.termArray[rowStart[this->termArray[i].col]-1].row);
        }
        delete[]rowSize;
        delete[]rowStart;
        return temp;
    }
}

SparseMatrix SparseMatrix::Add(SparseMatrix matrix)
{
    if(this->rows!=matrix.rows||this->cols!=matrix.cols){
        throw"Incompatible matrices";
    }
    SparseMatrix tempSparseMatrix{NULL,0,this->rows,matrix.cols};
    int apos=0,bpos=0;
    while(apos<this->terms&&bpos<matrix.terms)
    {
        if(this->termArray[apos].row<matrix.termArray[bpos].row){
            tempSparseMatrix.InsertTerm(this->termArray[apos].row,this->termArray[apos].col,this->termArray[apos].value);apos++;
        }
        else if(this->termArray[apos].row>matrix.termArray[bpos].row){
            tempSparseMatrix.InsertTerm(matrix.termArray[bpos].row,matrix.termArray[bpos].col,matrix.termArray[bpos].value);bpos++;
        }
        else if(this->termArray[apos].col<matrix.termArray[bpos].col){
            tempSparseMatrix.InsertTerm(this->termArray[apos].row,this->termArray[apos].col,this->termArray[apos].value);apos++;
        }
        else if(this->termArray[apos].col>matrix.termArray[bpos].col){
            tempSparseMatrix.InsertTerm(matrix.termArray[bpos].row,matrix.termArray[bpos].col,matrix.termArray[bpos].value);bpos++;
        }
        else{
            tempSparseMatrix.InsertTerm(matrix.termArray[bpos].row,matrix.termArray[bpos].col,this->termArray[apos].value+matrix.termArray[bpos].value);apos++,bpos++;
        }
    }
    while(apos<this->terms) //拷贝剩余矩阵元素
    {
        tempSparseMatrix.InsertTerm(this->termArray[apos].row,this->termArray[apos].col,this->termArray[apos].value);apos++;
    }
    while(bpos<matrix.terms)//拷贝剩余矩阵元素
    {
        tempSparseMatrix.InsertTerm(matrix.termArray[bpos].row,matrix.termArray[bpos].col,matrix.termArray[bpos].value);bpos++;
    }
    return tempSparseMatrix;
}

SparseMatrix SparseMatrix::Mult(SparseMatrix matrix)
{
    if(this->cols!=matrix.rows){
        throw"Incompatible matrices";
    }
    SparseMatrix tempSparseMatrix{NULL,0,this->rows,matrix.cols};
    matrix=matrix.FastTranspose();
    for (int i = 0; i < this->terms; i++) {
        for (int j = 0; j < matrix.terms; j++) {
            if(this->termArray[i].col==matrix.termArray[j].col){
                tempSparseMatrix.InsertTerm(this->termArray[i].row, matrix.termArray[j].row, this->termArray[i].value * matrix.termArray[j].value);
            }
        }
    }
    return tempSparseMatrix;
}

void SparseMatrix::TailInsertTerm(int row,int col,int value)
{
    if (this->terms == this->capacity)
    {
        if(terms==0){
            this->termArray=new MatrixTerm;
            this->capacity=1;
        }
        else{
            this->capacity *= 2;
            MatrixTerm* tempTerm = new MatrixTerm[this->capacity];
            for (int i = 0; i < this->terms; i++) {
            tempTerm[i] = this->termArray[i];
            }
            if(termArray){
                delete[]termArray;
            }
            this->termArray = tempTerm;
        }
    }
    this->termArray[terms].row=row;
    this->termArray[terms].col=col;
    this->termArray[terms].value=value;
    this->terms++;
}

void SparseMatrix::InsertTerm(int row, int col, int value)
{
    if (this->terms == this->capacity)
    {
        if(terms==0){
            this->termArray=new MatrixTerm;
            this->capacity=1;
        }
        else{
            this->capacity *= 2;
            MatrixTerm* tempTerm = new MatrixTerm[this->capacity];
            for (int i = 0; i < this->terms; i++) {
            tempTerm[i] = this->termArray[i];
            }
            if(termArray){
                delete[]termArray;
            }
            this->termArray = tempTerm;
        }
    }
    if(row==this->termArray[terms-1].row&&col==this->termArray[terms-1].col){    //与前项位置相同
        this->termArray[terms-1].value+=value;
        if(!this->termArray[terms-1].value)this->terms--;    //系数和为零            
    }
    else{    //与前面项位置不同
        this->termArray[terms].row = row;
        this->termArray[terms].col = col;
        this->termArray[terms].value = value;
        this->terms++;
    }
}