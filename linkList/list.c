#include <stdlib.h>
#include <string.h>
#include "list.h"


/* * * * * list_init * * * * * */
//Initialize the list
void list_init(List *list, void (*destroy) (void *data))
{
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;
	return;
}


/* * * * * * list_destroy * * * * * */
void list_destroy(List *list)
{
	void *data;
	//remove each element.
	while(list_size(list) > 0){
		if(list_rem_next(list, NULL, (void **)&data) == 0 &&
			list->destroy != NULL){
		/* call a user-defined function to free dynamically allocated
		 * data*/
			list->destroy(data);
		}
	}
	/* no operations are allowed now,but clear the structure as a 
	 * precaution.*/
	memset(list, 0, sizeof(List));
	
	return;
}

/* * * * * * lsit_ins_next * * * * * */
int list_ins_next(List *list, ListElmt *element, const void *data)
{
	ListElmt *new_element;
	/* allocate storage for the element*/
	if((new_element = (ListElmt *)malloc(sizeof(ListElmt))) == NULL){
		return -1;
	}

	/* insert the elememt into the list */
	new_element->data = (void *)data;
	if(element == NULL){
		/* if element is NULL, insert element at the head of list */
		if(list_size(list) == 0)
			list->tail = new_element;
		new_element->next = list->head;
		list->head = new_element;
	}
	else{
		/* handle insertion somewhere other than at the head */
		if(element->next == NULL)
			list->tail = new_element;
		new_element->next = element->next;
		element->next = new_element;
	}
	/* adjust the size of the list to account for the inserted element */
	list->size++;
	
	return 0;
}


/* * * * * * list_rem_next * * * * * */
int list_rem_next(List *list, ListElmt *element, void **data)
{
	ListElmt *old_element;

	/* do not allow removal from an empty list */
	if(list_size(list) == 0)
		return -1;

	/* remove the element from the list */
	if(element == NULL){
		/* if element is NULL, removal from the head of the list*/
		*data = list->head->data;
		old_element = list->head;
		list->head = list->head->next;
		if(list_size(list) == 1)
			list->tail = NULL;
	}
	else{
		/* handle removal from somewhere other than head */
		if(element->next == NULL)
			return -1;
		*data = element->data;
		old_element = element->next;
		element->next = element->next->next;
		if(element->next == NULL)
			list->tail = element;
	}

	/* free the storage allocated by tha abstract datatype */
	free(old_element);
	/* adjust the size of the list to account for the removed element */
	list->size--;

	return 0;
}




