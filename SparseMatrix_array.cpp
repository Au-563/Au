class SparseMatrix;
class MatrixNode
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
    MatrixNode* array;      //非零项数组
    int rows;               //总行数
    int cols;               //总列数
    int terms;              //非零项数
    int capacity;           //最大容量
public:
    SparseMatrix():terms(0),rows(0),cols(0),capacity(0){};   //默认构造函数
    SparseMatrix(MatrixNode* m,int terms,int r,int c);       //缺省构造函数
    void Print();                                            //打印矩阵
    SparseMatrix Transpose();                                //矩阵转置
    SparseMatrix FastTranspose();                            //快速转置
    SparseMatrix Add(SparseMatrix b);                        //矩阵加法
    SparseMatrix Mult(SparseMatrix b);                       //矩阵乘法
    void InsertTerm(int row,int col,int value);              //插入元素
};

SparseMatrix::SparseMatrix(MatrixNode* m,int terms,int r,int c):terms(terms),rows(r),cols(c),capacity(terms)
{
    if(terms){
        this->array=new MatrixNode[terms];
        for(int i=0;i<terms;i++){
        this->array[i]=m[i];
    }
    }
}

void SparseMatrix::Print()
{
    int count=0;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(array[count].row==i&&array[count].col==j)cout<<array[count++].value<<" ";
            else cout<<"0 ";
        }
        cout<<'\n';
    }
}       

SparseMatrix SparseMatrix::Transpose()
{
    if(!this->terms)throw"The matrix is empty";
    else{
        SparseMatrix temp=SparseMatrix(array,terms,cols,rows);
        int counter=0;
        for(int i=0;i<this->cols;i++){
            for(int j=0;j<this->terms;j++){
                if(this->array[j].col==i){
                    temp.array[counter].row=i;
                    temp.array[counter].col=this->array[j].row;
                    temp.array[counter++].value=this->array[j].value;
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
        SparseMatrix temp=SparseMatrix(array,terms,cols,rows);
        int* rowStart=new int[this->cols]{};
        int* rowSize=new int[this->cols]{};
        for(int i=0;i<this->terms;i++)rowSize[this->array[i].col]++;
        for(int i=1;i<this->cols;i++)rowStart[i]=rowStart[i-1]+rowSize[i-1];
        for(int i=0;i<this->terms;i++){
            temp.array[rowStart[this->array[i].col]++]=this->array[i];
            swap(temp.array[rowStart[this->array[i].col]-1].col,temp.array[rowStart[this->array[i].col]-1].row);
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
        if(this->array[apos].row<matrix.array[bpos].row){
            tempSparseMatrix.InsertTerm(this->array[apos].row,this->array[apos].col,this->array[apos].value);apos++;
        }
        else if(this->array[apos].row>matrix.array[bpos].row){
            tempSparseMatrix.InsertTerm(matrix.array[bpos].row,matrix.array[bpos].col,matrix.array[bpos].value);bpos++;
        }
        else if(this->array[apos].col<matrix.array[bpos].col){
            tempSparseMatrix.InsertTerm(this->array[apos].row,this->array[apos].col,this->array[apos].value);apos++;
        }
        else if(this->array[apos].col>matrix.array[bpos].col){
            tempSparseMatrix.InsertTerm(matrix.array[bpos].row,matrix.array[bpos].col,matrix.array[bpos].value);bpos++;
        }
        else{
            tempSparseMatrix.InsertTerm(matrix.array[bpos].row,matrix.array[bpos].col,this->array[apos].value+matrix.array[bpos].value);apos++,bpos++;
        }
    }
    while(apos<this->terms) //拷贝剩余矩阵元素
    {
        tempSparseMatrix.InsertTerm(this->array[apos].row,this->array[apos].col,this->array[apos].value);apos++;
    }
    while(bpos<matrix.terms)//拷贝剩余矩阵元素
    {
        tempSparseMatrix.InsertTerm(matrix.array[bpos].row,matrix.array[bpos].col,matrix.array[bpos].value);bpos++;
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
            if(this->array[i].col==matrix.array[j].col){
                tempSparseMatrix.InsertTerm(this->array[i].row, matrix.array[j].row, this->array[i].value * matrix.array[j].value);
            }
        }
    }
    return tempSparseMatrix;
}

void SparseMatrix::InsertTerm(int row, int col, int value)
{
    if (this->terms == this->capacity)
    {
        if(terms==0){
            this->array=new MatrixNode;
            this->capacity=1;
        }
        else{
            this->capacity *= 2;
            MatrixNode* tempTerm = new MatrixNode[this->capacity];
            for (int i = 0; i < this->terms; i++) {
            tempTerm[i] = this->array[i];
            }
            if(array){
                delete[]array;
            }
            this->array = tempTerm;
        }
    }
    if(row==this->array[terms-1].row&&col==this->array[terms-1].col){    //与前项位置相同
        this->array[terms-1].value+=value;
        if(!this->array[terms-1].value)this->terms--;    //系数和为零            
    }
    else{    //与前面项位置不同
        this->array[terms].row = row;
        this->array[terms].col = col;
        this->array[terms].value = value;
        this->terms++;
    }
}