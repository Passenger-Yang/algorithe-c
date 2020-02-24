/* dlist.c */
#include <stdlib.h>
#include <string.h>
#include "dlist.h"

/* * * * * dlist_init * * * * */
void dlist_init(Dlist *list, void (*destroy) (void *data))
{
	/* initialize the list */
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;

	return;
}

/* * * * * dlist_destroy * * * * */
void dlist_destroy(Dlist *list)
{
	void *data;
	/* remove each element */
	while(dlist_size(list) > 0){
		if(dlist_remove(list, dlist_tail(list), (void **)&data) == 0
		   && list->destroy != NULL){
			/* call a user-defined function to free dynamically
			 * allocated data*/
			list->destroy(data);
		}
	}
	/* no operations are allowed now,but clear the structure as a
	 * precaution*/
	memset(list, 0, sizeof(Dlist));
	
	return;
}

/* * * * * dlist_ins_next * * * * */
int dlist_ins_next(Dlist *list, DlistElmt *element, const void *data)
{
	DlistElmt *new_element;
	/* do not allow a NULL element unless the list is empty */
	if(element == NULL && dlist_size(list) != 0)
		return -1;
	/* allocate storage for the element */
	if((new_element = (DlistElmt *)malloc(sizeof(DlistElmt))) == NULL)
		return -1;

	/* insert the new element into the list */
	new_element->data = (void *)data;
	if(dlist_size(list) == 0){
		/* handle insertion when list is empty */
		list->head = new_element;
		list->head->prev = NULL;
		list->head->next = NULL;
		list->tail = new_element;
	}
	else{
		/* handle insertion when the list is not empty */
		new_element->next = element->next;
		new_element->prev = element;
		if(element->next == NULL)
			list->tail = new_element;
		else
			element->next->prev = new_element;
		element->next = new_element;
	}
	/*adjust the size of the list to accout for the inserted element*/
	list->size++;

	return 0;
}


/* * * * * dlist_ins_prev * * * * */
int dlist_ins_prev(Dlist *list, DlistElmt *element, const void *data)
{
	DlistElmt *new_element;
	/* do not allow a NULL element unless the list is empty*/
	if(element == NULL && dlist_size(list) != 0)
		return -1;

	/* allocate storage for the element */
	if((new_element = (DlistElmt *)malloc(sizeof(DlistElmt))) == NULL)
		return -1;
	/* insert the new element into the list */
	new_element->data = (void *)data;
	if(dlist_size(list) == 0){
		/*handle insertion when list is empty*/
		list->head = new_element;
		list->head->prev = NULL;
		list->head->next = NULL;
		list->tail = new_element;
	}
	else{
		/*handle insertion when list is not empty*/
		new_element->prev = element->prev;
		new_element->next = element;
		if(element->prev == NULL)
			list->head = new_element;
		else
			element->prev->next = new_element;
		element->prev = new_element;
	}
	/* adjust list size to acoout for the new element  */
	list->size++;

	return 0;
}

/* * * * * dlist_remove * * * * */
int dlist_remove(Dlist *list, DlistElmt *element, void **data)
{
	/* do not allow a NULL element or removal from an empty list*/
	if(element == NULL || dlist_size(list) == 0)
		return -1;

	/* remove the element from the list */
	*data = element->data;
	if(element == list->head){
		/* handle removal from the head of the list */
		list->head = element->next;
		if(list->head == NULL)
			list->tail = NULL;
		else
			element->next->prev = NULL;
	}
	else{
		/* handle remval from other than the head of the list */
		element->prev->next = element->next;
		if(element->next == NULL)
			list->tail = element->prev;
		else
			element->next->prev = element->prev;
	}

	/* free the storage allocaated by the abstract datetype */
	free(element);
	list->size--;
	
	return 0;
}



