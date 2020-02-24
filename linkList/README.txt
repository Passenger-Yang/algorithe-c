/* linkList.c */
void list_init(List *list, void (*destroy) (void *data));
@返回值：无
@描述：初始化由参数list指定的链表。当调用list_destroy时，destroy参数
提供一种释放动态分配的数据的方法。如果链表包含不应该释放的数据，
destroy应该置为NULL。


void list_destroy(List *list);
@返回值：无
@描述：销毁由参数list指定的链表。调用list_destroy后任何其他的操作
不允许执行。如果传给list_init的参数destroy不为NULL，则移除链表中的每
个元素时都应该调用该函数一次。


int list_ins_next(List *list, ListElmt *element, const void *data);
@返回值：如果插入元素成功则返回0，否则返回-1。
@在list指定的链表中element后面插入一个新元素。如果element设置为NULL，
则新元素插入链表头部。


int list_rem_next(List *list, ListElmt *element, void **data);
@返回值：如果移除元素成功则返回0，否则返回-1。
@移除由list指定的链表中的element后的那个元素。如果elememt设置为NULL
则移除链表头元素。调用返回后，data指向已移除元素中存储的数据。


