/*  heap.c */
#include <stdlib.h>
#include <string.h>
#include "heap.h"
/* define private macros uesd by the heap implementation */
#define heap_parent(npos)	((int)((npos - 1) / 2))
#define heap_left(npos)		(((npos) * 2) + 1)
#define heap_right(npos)	(((npos) * 2) + 2)

/* heap_init */
void heap_init(Heap *heap, int (*compare)(const void *key1, const void *key2),
				void (*destroy)(void *data))
{
	//initialize the heap
	heap->size = 0;
	heap->compare = compare;
	heap->destroy = destroy;
	heap->tree = NULL;
	
	return;
}


/* heap_destroy */
void heap_destroy(Heap *heap)
{
	int i;
	//remove all the nodes from the heap
	if(heap->destroy != NULL){
		for(i = 0; i < heap_size(heap); i++){
			//call a user-defined function to free dynamiclly allocated data
			heap->destroy(heap->tree[i]);
		}
	}
	//free the storage for the heap
	free(heap->tree);
	//No operations are allowed now
	memset(heap, 0, sizeof(Heap));

	return;
}

/* heap_insert */
int heap_insert(Heap *heap, const void *data)
{
	void *temp;
	int ipos, ppos;

	//allocate storage for the node
	if((temp = (void **)realloc(heap->tree, (heap_size(heap) + 1) * sizeof(void *))) 
					== NULL)
	{
		return -1;
	}
	else
		heap->tree = temp;

	//insert the node after the last node
	heap->tree[heap_size(heap)] = (void *)data;
	//
	ipos = heap_size(heap);
	ppos = heap_parent(ipos);
	while(ipos > 0 && heap->compare(heap->tree[ppos], heap->tree[ipos]) < 0){
		//swap the contents of the current node and its parent
		temp = heap->tree[ppos];
		heap->tree[ppos] = heap->tree[ipos];
		heap->tree[ipos] = temp;
		//move up one level 
		ipos = ppos;
		ppos = heap_parent(ipos);
	}
	//adjust the size of the heap to accout for the inserted node
	heap->size++;

	return 0;
}

/* heap_extract */
int heap_extract(Heap *heap, void **data)
{
	void *save, *temp;
	int ipos, lpos, rpos, mpos;

	//do not allow extraction from empty heap
	if(heap_size(heap) == 0)
		return -1;
	//extract the node at the top of the heap
	*data = heap->tree[0];

	//adjust the storage used by the heap
	save = heap->tree[heap_size(heap) - 1];
	if(heap_size(heap) - 1 > 0){
		if((temp = (void **)realloc(heap, (heap_size(heap) - 1) * sizeof(void *)))
					 	== NULL)
			return -1;
		else
			heap->tree = temp;

		//adjust the size
		heap->size--;
	}
	else{
		//manage the heap when extracting the last node
		free(heap->tree);
		heap->tree = NULL;
		heap->size = 0;
		
		return 0;
	}

	//copy the last node to the top
	heap->tree[0] = save;
	//heapify the tree
	ipos = 0;
	lpos = heap_left(ipos);
	rpos = heap_right(ipos);
	while(1){
		//select the child to swap with the current node
		lpos = heap_left(ipos);
		rpos = heap_right(ipos);
		if(lpos < heap_size(heap) && heap->compare(heap->tree[lpos], heap->tree[ipos]) > 0)
			mpos = lpos;
		else
			mpos = ipos;
		if(rpos < heap_size(heap) && heap->compare(heap->tree[rpos], heap->tree[mpos]) > 0)
			mpos = rpos;

		//when mpos is ipos, the heap property has been resorted
		if(mpos = ipos)
			break;
		else{
			//swap
			temp = heap->tree[mpos];
			heap->tree[mpos] = heap->tree[ipos];
			heap->tree[ipos] = temp;
			ipos = mpos;
		}
	}

	return 0;
}





