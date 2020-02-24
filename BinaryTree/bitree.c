/* bitree.c */
#include <stdlib.h>
#include <string.h>
#include "bitree.h"

/* bitree_init */
void bitree_init(BiTree *tree, void (*destroy)(void *data))
{
	//initialize the tree
	tree->size = 0;
	tree->destroy = destroy;
	tree->root = NULL;

	return;
}

/* bitree_destroy */
void bitree_destroy(BiTree *tree)
{
	// remove all the nodes from the tree
	bitree_rem_left(tree, NULL);

	memset(tree, 0, sizeof(BiTree));
	return;
}

/*bitree_ins_left */
int bitree_ins_left(BiTree *tree, BiTreeNode *node, const void *data)
{
	BiTreeNode *new_node, **position;

	//determine where to insert the node
	if(node == NULL){
		//allow insertion at the root only in an empty tree
		if(bitree_size(tree) > 0)
			return -1;
		position = &tree->root;
	}
	else{
		//normally allow insertion only at the end of a branch
		if(bitree_left(node) != NULL)
			return -1;
		position = &node->left;
	}
	//allocate storage for the node
	if((new_node = (BiTreeNode *)malloc(sizeof(BiTreeNode))) == NULL)
		return -1;
	//insert the node into the tree;
	new_node->data = (void *)data;
	new_node->left = NULL;
	new_node->right = NULL;
	//tree->root or node->left -> new_node
	*position = new_node;
	//adjust the size of the tree
	tree->size++;

	return 0;
}

/* bitree_ins_right */
int bitree_ins_right(BiTree *tree, BiTreeNode *node, const void *data)
{
	BiTreeNode *new_node, **position;

	//determine where to insert the node
	if(node == NULL){
		//allow insertion at the root only in an empty tree
		if(bitree_size(tree) > 0)
			return -1;
		position = &tree->root;
	}
	else{
		//normally allow insertion only at the end of a branch
		if(bitree_right(node) != NULL)
			return -1;
		position = &node->right;
	}
	//allocate storage for the node
	if((new_node = (BiTreeNode *)malloc(sizeof(BiTreeNode))) == NULL)
		return -1;
	//insert the node into the tree;
	new_node->data = (void *)data;
	new_node->left = NULL;
	new_node->right = NULL;
	//tree->root or node->left -> new_node
	*position = new_node;
	//adjust the size of the tree
	tree->size++;

	return 0;
}
	

/* bitree_rem_left */
void bitree_rem_left(BiTree *tree, BiTreeNode *node)
{
	BiTreeNode **position;
	//do not allow remval from an empty tree
	if(bitree_size(tree) == 0)
		return;
	//determine where to remove nodes
	if(node == NULL)
		position = &tree->root;
	else
		position = &node->left;

	//remove the nodes
	if(*position != NULL){
		bitree_rem_left(tree, *position);
		bitree_rem_right(tree, *position);
		if(tree->destroy != NULL){
			tree->destroy((*position)->data);
		}
		free(*position);
		*position = NULL;
		tree->size--;
	}
	return;
}


void bitree_rem_right(BiTree *tree, BiTreeNode *node)
{
	BiTreeNode **position;
	//do not allow remval from an empty tree
	if(bitree_size(tree) == 0)
		return;
	//determine where to remove nodes
	if(node == NULL)
		position = &tree->root;
	else
		position = &node->right;

	//remove the nodes
	if(*position != NULL){
		bitree_rem_left(tree, *position);
		bitree_rem_right(tree, *position);
		if(tree->destroy != NULL){
			tree->destroy((*position)->data);
		}
		free(*position);
		*position = NULL;
		tree->size--;
	}
	return;
}

/* bitree_merge */
int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data)
{
	//initialize the merge tree
	bitree_init(merge, left->destroy);
	//insert the data for the root node of the merged tree
	if(bitree_ins_left(merge, NULL, data) != 0){
		bitree_destroy(merge);
		return -1;
	}
	//merge the two trees
	bitree_root(merge)->left = bitree_root(left);
	bitree_root(merge)->right = bitree_root(right);

	//adjust the size of the new tree
	bitree_size(merge) = bitree_size(merge) + bitree_size(left) 
		+ bitree_size(right);
	//do not allow the original trees access the merged tree
	left->root = NULL;
	left->size = 0;
	right->root = NULL;
	right->size = 0;

	return 0;
}

