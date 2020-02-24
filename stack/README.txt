/* stack readme */

stack_init
@因为栈本身就是一个链表，所以将stack_init定义为list_init
@运行时复杂度O(1)


stack_destroy
@同上
@运行时复杂度O(n)。n为栈包含的元素


stack_push
@栈通过stack_push往栈顶压入元素。stack_push调用list_ins_next方法插入指向链表头部中data的元素
@运行时复杂度O(1)


stack_pop
@stack_pop通过调用list_rem_next方法来删除链表头元素，并将data指向已删除的元素中的数据
@运行时复杂度O(1)


stack_peek与stack_size
@宏。stack_peek用来获取栈顶元素但是不弹出;stack_size用来获取栈的大小。

