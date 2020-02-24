/* set.c */
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "set.h"


/* * * ** * ** * * * * * * *
 *@返回值 无
 *@描述：初始化由参数set指定的集合。match是一个函数指针，用来
  在各种集合操作中判断两个成员是否相等。若key1 == key2 则return 1
  当调用set_destroy时，destroy参数提供一个释放动态空间的方法。
 *@复杂度：O(1)
* * * ** * ** * * * * * * */
void set_init(Set *set, int (*match) (const void *key1, const void *key2), 
		void (*destroy) (void *data))
{
	//initialize the set
	list_init(set, destroy);
	set->match = match;
	return;
}


/* * * * * * * * * * * * * * * *
 *@返回值：插入成功:0; 失败:-1; 已存在:1
 *@描述：在集合set中插入一个成员
 *@复杂度：O(n), n代表集合内元素个数
 * * * * * * * * * * * * * * * */
int set_insert(Set *set, const void *data)
{
	//do not allow the insertion of duplicates
	if(set_is_member(set, data))
		return 1;

	//insert the data
	return list_ins_next(set, list_tail(set), data);
}


/* * * * * * * * * * * * * * * * * * * * * * * *
 * @返回值：成功:0; 否则返回-1
 * @描述：在集合set中移除数据域与data相同的成员
 * @复杂度:O(n), n代表集合中的元素个数
 * * * * * * * * * * * * * * * * * * * * * * * */
int set_remove(Set *set, void **data)
{
	ListElmt *member, *prev;

	//find the member to remove
	prev = NULL;
	for(member = list_head(set); member != NULL; member = list_next(member)){
		if(set->match(*data, list_data(member)))
			break;
		prev = member;
	}

	//return if the meember is not found
	if(member == NULL)
		return -1;

	//remove the member
	return list_rem_next(set, prev, data);
}

/* * * * * * * * * * * * * * * * * * * * * * *
 * @返回值：计算并集成功返回0；否则-1
 * @描述：建立一个新集合，其结果为set1 set2 的并集setu
 * @复杂度：O(mn). m,n分别代表set1 set2中元素个数
 * * * * * * * * * * * * * * * * * * * * * * */
int set_union(Set *setu, const Set *set1, const Set *set2)
{
	ListElmt *member;
	void *data;

	//initialize the set for the union
	set_init(setu, set1->match, NULL);

	//insert the members of the first set
	for(member = list_head(set1); member != NULL; member = list_next(member)){
		data = list_data(member);
		if(list_ins_next(setu, list_tail(setu), data) != 0){
			set_destroy(setu);
			return -1;
		}
	}

	//insert the members of the second set
	for(member = list_head(set2); member != NULL; member = list_next(member)){
		if(set_is_member(set1, list_data(member))){
			// do not allow the insertion of duplicates
			continue;
		}
		else{
			data = list_data(member);
			if(list_ins_next(setu, list_tail(setu), data) != 0){
				set_destroy(setu);
				return -1;
			}
		}
	}
	return 0;
}


/* * * * * * * * * * * * * * * * * * * * * * * *
 * @返回值：交集计算成功返回0;否则-1
 * @描述：建立一个集合seti，其结果为set1 set2的交集
 * @复杂度：O(mn). m,n分别代表set1 set2中元素个数
 * * * * * * * * * * * * * * * * * * * * * * * */
int set_intersection(Set *seti, const Set *set1, const Set *set2)
{
	ListElmt *member;
	void *data;

	//initialize the set for the intersection
	set_init(seti, set1->match, NULL);

	//insert the members present both of sets
	for(member = list_head(set1); member != NULL; member = list_next(member)){
		if(set_is_member(set2, list_data(member))){
			data = list_data(member);
			if(list_ins_next(seti, list_tail(seti), data) != 0){
				set_destroy(seti);
				return -1;
			}
		}
	}
	return 0;
}


/* * * * * * * * * * * * * * * * * * * * * * * *
 * @返回值：差集计算成功返回0;否则-1
 * @描述：建立一个集合setd，其结果为set1 set2的差集
 * @复杂度：O(mn). m,n分别代表set1 set2中元素个数
 * * * * * * * * * * * * * * * * * * * * * * * */
int set_difference(Set *setd, const Set *set1, const Set *set2)
{
	ListElmt *member;
	void *data;

	//initialize the set for the difference
	set_init(setd, set1->match, NULL);

	//insert the members from set1 not in set2
	for(member = list_head(set1); member != NULL; member = list_next(member)){
		if(!set_is_member(set2, list_data(member))){
			data = list_data(member);
			if(list_ins_next(setd, list_tail(setd), data) != 0){
				list_destroy(setd);
				return -1;
			}
		}
	}
	return 0;
}


/* * * * * * * * * * * * * * * * * * * * * * * *
 * @返回值：如果找到返回1，否则-1
 * @描述：判断data指定的成员是否在set中
 * @复杂度：O(n) n代表集合中的元素
 * * * * * * * * * * * * * * * * * * * * * * * */
int set_is_member(const Set *set, const void *data)
{
	ListElmt *member;

	for(member = list_head(set); member != NULL; member = list_next(member)){
		if(set->match(data, list_data(member)))
			return 1;
	}

	return 0;
}


/* * * * * * * * * * * * * * * * * * * * * * * *
 * @返回值：如果set1是set2的子集返回1;否则-1
 * @描述：判断set1所指向的集合是否为 set2的子集
 * @复杂度：O(nm)
 * * * * * * * * * * * * * * * * * * * * * * * */
int set_is_subset(const Set *set1, const Set *set2)
{
	ListElmt *member;

	//do a quick test to rule out some cases
	if(set_size(set1) > set_size(set2))
		return 0;

	for(member = list_head(set1); member != NULL; member = list_next(member)){
		if(!set_is_member(set2, list_data(member)))
			return 0;
	}

	return 1;
}


/* * * * * * * * * * * * * * * * * * * * * * * *
 * @返回值：如果set1 set2 相等返回1;否则-1
 * @描述：判断set1所指向的集合于set2是否相等
 * @复杂度：O(nm)
 * * * * * * * * * * * * * * * * * * * * * * * */
int set_is_equal(const Set *set1, const Set *set2)
{
	if(set_size(set1) != set_size(set2))
		return 0;
	//sets of the same size are equal if the are subsets
	return set_is_subset(set1, set2);

}

