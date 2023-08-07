#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int size;
int parent(int i){
    return (i - 1) / 2;
}

int left_child(int i){
    return (2*i + 1);
}

int right_child(int i){
    return (2*i + 2);
}

void swap(int heap[],int a,int b){
	int t=heap[a];
	heap[a]=heap[b];
	heap[b]=t;
}

int getMin(int heap[]){
	return heap[0];
}

int getMax(int heap[]){
	return (heap[2]>heap[1]?heap[2]:heap[1]);
}

void heapify(int heap[],int index){
	if(index>=size)
		return;
	
	int i=left_child(left_child(index));
	int lvl=log2(index+1);
	if(lvl%2==0){
		int min=index;
		for(int j=1;i<size && j<=4;i++,j++){
			if(heap[i]<heap[min])
				min=i;
		}
		if(min!=index){
			swap(heap,min,index);
			heapify(heap,min);
		}
		else if(left_child(index)<size && heap[index]>heap[left_child(index)]){
			swap(heap,index,left_child(index));
			heapify(heap,left_child(index));
		}
		if(right_child(index)<size && heap[index]>heap[right_child(index)]){
			swap(heap,index,right_child(index));
			heapify(heap,right_child(index));
		}
	}
	else{
		int max=index;
		for(int j=1;i<size && j<=4;i++,j++){
			
			if(heap[i]>heap[max])
				max=i;
		}
		if(max!=index){
			swap(heap,max,index);
			heapify(heap,max);
		}
		else if(left_child(index)<size && heap[index]<heap[left_child(index)]){
			
			swap(heap,index,left_child(index));
			heapify(heap,left_child(index));
		}
		if(right_child(index)<size && heap[index]<heap[right_child(index)]){
			swap(heap,index,right_child(index));
			heapify(heap,right_child(index));
		}		
	}
}


void insert(int heap[],int index){
	int lvl=log2(index+1);
	if(lvl==0){
		return;
	}
	if(lvl%2==0){
		if(heap[parent(index)]<heap[index]){
			swap(heap,parent(index),index);
			insert(heap,parent(index));
		}
		else if(lvl>1 && heap[parent(parent(index))]>heap[index]){
			swap(heap,parent(parent(index)),index);
			insert(heap,parent(index));
		}
	}
	else{
		if(heap[parent(index)]>heap[index]){
			swap(heap,parent(index),index);
			insert(heap,parent(index));
		}
		else if(lvl>1 && heap[parent(parent(index))]<heap[index]){
			swap(heap,parent(parent(index)),index);
			insert(heap,parent(index));
		}
	}	
}

int extractMin(int heap[]){
	int min=getMin(heap);
	swap(heap,0,size-1);
	size--;
	heapify(heap,0);
	return min;		
}

int extractMax(int heap[]){
	int ind=heap[2]>heap[1]?2:1;
	int max=heap[ind];
	swap(heap,ind,size-1);
	size--;
	heapify(heap,ind);
	return max;
}

int findMedian(int heap[],int size){
	if(size==0){
		printf("Empty Heap!");
		return;
	}
	
	if(size==1)
		return heap[0];
		
	if(size%2==0){
		int mid1 = heap[size/2 - 1];
		int mid2 = heap[size/2];
		return (mid1+mid2)/2;
	}
	else
		return heap[size/2];		
}

int main(){
	int heap[16];
	size=0;
	
	// Operations
	//INSERTION, FIND_MIN, FIND_MAX, EXTRACT_MIN, EXTRACT_MAX, MEDIAN
	
	int arr[]={1,4,-5,6,7,9,3,40,20,2,70,100};
	for(int i=0;i<12;i++){
		heap[i]=arr[i];
		size++;
		insert(heap,i);
	}
	
	printf("After insertion in heap: ");
	for(int i=0;i<size;i++)
		printf("%d ",heap[i]);
	
	printf("\nExtract Min: %d\n",extractMin(heap));
	printf("Heap after extractMin(): ");
	for(int i=0;i<size;i++)
		printf("%d ",heap[i]);
	
	printf("\nExtract Max: %d\n",extractMax(heap));
	printf("Heap after extractMax(): ");
	for(int i=0;i<size;i++)
		printf("%d ",heap[i]);
		
	printf("\nFind Min: %d\n",getMin(heap));
	printf("Find Max: %d\n",getMax(heap));
	
	extractMin(heap);
	
		
	printf("Median: %d\n",findMedian(heap,size));
	
	return 0;
}
