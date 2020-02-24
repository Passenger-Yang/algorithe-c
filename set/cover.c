/* cover.c */
#include <stdlib.h>
#include "coover.h"
#include "set.h"
#include "list.h"

//cover
int cover(Set *members, Set *subsets, Set *covering)
{
	Set intersection;
	KSet *subset;
	ListElmt *member, *max_member;
	void *data;
	int max_size;

	//initialize the covering
	set_init(covering, subsets->match, NULL);

	//continue while there are noncovered members and candidate subsets
	while(set_size(members) > 0 && set_size(subsets) > 0){
		//find the subset that covers the most members
		max_size = 0;
		for(member = list_head(subsets); member != NULL; 
				member = list_next(member))
		{
			if(set_intersection(&intersection, &((KSet *)list_data(member))->set, members) != 0)
				return -1;
			if(set_size(&intersection) > max_size){
				max_member = member;
				max_size = set_size(&intersection);
			}
			set_destroy(&intersection);
		}

		// a covering is not possible if there was no intersection
		if(max_size == 0)
			return -1;

		//insert the selected subset into the covering
		subset = (KSet *)list_data(max_member);
		if(set_insert(covering, subset) != 0)
			return -1;

		//remove each covered member
		for(member = list_head(&(KSet *)list_data(max_member))->set;
				member != NULL; member = list_next(member))
		{
			data = list_data(member);
			if(set_remove(members, (void **)&data) == 0 
				&& members->destroy != NULL)
				members->destroy(data);
		}
		//remove from candidate subsets
		if(set_remove(subsets, (void **)&subset) != 0)
			return -1;
	}
	if(set_size(members) > 0)
		return -1;

	return 0;
}


