//一、冒泡排序
//时间复杂度O(N^2)，额外空间复杂度O(1)
void sort(int arr[],int length)
{
    for(int i=0;i<length-1;i++)
    {
        for(int j=0;j<length-1-i;j++)
        {
        	if(arr[j]>arr[j+1])
                swap(arr[j],arr[j+1]);
        }          
    }
}

//二、选择排序
//时间复杂度O(N^2)，额外空间复杂度O(1)
void sort(int arr[],int length)
{
    for(int i=0;i<length-1;i++)
    {
        int idx=i;
        for(int j=i+1;j<length;j++)
        {
        	idx=arr[j]<arr[idx]?j:idx;
        }
        swap(arr[i],arr[idx]);
    }
}

//三、插入排序
//时间复杂度O(N^2)，额外空间复杂度O(1)
void sort(int arr[],int length)
{
    for(int i=1;i<length;i++)
    {
        for(int j=i;j>0&&arr[j]<arr[j-1];j--)
        {
            swap(arr[j],arr[j-1]);
        }
    }
}

//四、希尔排序
//时间复杂度O(N*logN)，额外空间复杂度O(1)
void sort(int arr[], int length) 
{
    for(int inc=length/2;inc>0;inc/=2)
    {
        for(int i=inc;i<length;i++)
        {
            for(int j=i;j>=inc&&arr[j]<arr[j-inc];j-=inc)
            {
                swap(arr[j],arr[j-inc]);
            }
        }
    }
}

//五、计数排序
//时间复杂度O(N+k)，额外空间复杂度O(k)
void sort(int arr[], int length)
{
    int max = arr[0], min = arr[0];
    for (int i = 0; i < length; i++)
    {
        max = max > arr[i] ? max : arr[i];
        min = min < arr[i] ? min : arr[i];
    }
    int* count = new int[max - min + 1] {};	//初始值设为0
    for (int i = 0; i < length; i++)
    {
        count[arr[i] - min]++;
    }
    for (int i = 1; i < max - min + 1; i++)
    {
        count[i] += count[i - 1];
    }
    int* temp = new int[length];
    for (int i = 0; i < length; i++)
    {
        temp[--count[arr[i] - min]] = arr[i];
    }
    for (int i = 0; i < length; i++)
    {
        arr[i] = temp[i];
    }
}

//六、归并排序
//时间复杂度O(N*logN)，额外空间复杂度O(N)
void sort(int arr[], int L, int R)
{
	if (L == R)		//防止无限递归
	{
		return;
	}
	int mid = L + ((R - L) >> 1);
	sort(arr, L, mid);
	sort(arr, mid + 1, R);
	merge(arr, L, mid, R);
}
void merge(int arr[], int L, int M, int R)
{
	int* temp = new int[R - L + 1];
	int i = 0, p1 = L, p2 = M + 1;
	while (p1 <= M && p2 <= R)
	{
		temp[i++] = arr[p1] <= arr[p2] ? arr[p1++] : arr[p2++];
	}
	while (p1 <= M)
	{
		temp[i++] = arr[p1++];
	}
	while (p2 <= R)
	{
		temp[i++] = arr[p2++];
	}
    while(i-->0)
	{
		arr[L + i] = temp[i];
	}
} 

//七、快速排序
//时间复杂度O(N*logN)，额外空间复杂度O(logN)
int partition(int arr[], int low, int high) 
{
    int pivot = arr[high];      // 选择最后一个元素作为基准
    int i = low;        
    for (int j = low; j < high; j++) 
    {
        if (arr[j] < pivot) 
        {
            swap(arr[i++], arr[j]);  
        }  
    }
    swap(arr[i], arr[high]); 
    return i;
}
void sort(int arr[], int low, int high) 
{
    if (low < high) 
    {
        int pi = partition(arr, low, high); 
        sort(arr, low , pi - 1 );
        sort(arr, pi + 1, high);
    }
}

//八、堆排序
//时间复杂度O(N*logN)，额外空间复杂度O(1)
void heapify(int arr[],int length,int i)    //维护堆，使得父节点大于左孩子与右孩子，复杂度O(N)
{
    int largest=i;
    int lson=2*i+1,rson=2*i+2;
    if(lson<length&&arr[largest]<arr[lson])
    {
        largest=lson;
    }
    if(rson<length&&arr[largest]<arr[rson])
    {
        largest=rson;
    }
    if(largest!=i)
    {
        swap(arr[largest],arr[i]);
        heapify(arr,length,largest);
    }
}
void sort(int arr[],int length)
{
    for(int i=length/2-1;i>=0;i--)
    {
        heapify(arr,length,i);
    }
    for(int i=length-1;i>0;i--)
    {
        swap(arr[i],arr[0]);
        heapify(arr,i,0);
    }
}
