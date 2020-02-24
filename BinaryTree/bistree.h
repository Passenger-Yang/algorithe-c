/* bistree.h */
#ifndef BISTREE_H
#define BISTREE_H

#include "bitree.h"

//define balance factors for AVL trees
#define AVL_LFT_HEAVY	1
#define AVL_BALANCED	0
#define AVL_RGT_HEAVY	-1

//define structure for nodes in AVL trees
typedef struct AvlNode_{
	void *data;
	int hidden;
	int factor;
}AvlNode;

typedef Bitree Bistree;


#endif

