#include "include.h"

#ifdef LEETCODE_141_150
#include "public.h"
#include "leetcode.h"

bool Solution::hasCycle(ListNode * head)
{
	//O(n)内存很简单
	//采用常量内存

	//来自评论:快慢指针
	if (head == nullptr) return false;

	ListNode* fast = head;
	ListNode* slow = head;

	while (true)
	{
		if (fast->next == nullptr) break;
		if (fast->next->next == nullptr) break;
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow) return true;
	}
	return false;
}

ListNode * Solution::detectCycle(ListNode * head)
{
	//快慢指针

	//假设head距离环起始处为a,环长b(总节点数即为a+b)
	//快指针将提前慢指针进圈a长度,
	//如果二者同时在圈起始点开始走,那么应当在圈起始点相遇
	//现在快指针提前了a长度,那么将在距离圈起始点a处(圈内的)相遇
	//这样从相遇出的指针和起始处的指针按同样速度走a长度后将在圈起始点处相遇

	//特殊情况
	if (head == nullptr) return nullptr;

	//第一部分
	ListNode* fast = head;
	ListNode* slow = head;

	while (true)
	{
		if (fast->next == nullptr) break;
		if (fast->next->next == nullptr) break;
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow) goto step2;
	}
	return nullptr;

	//第二部分
step2:
	ListNode* start = head;
	while (start != slow)
	{
		start = start->next;
		slow = slow->next;
	}
	return start;
}

void Solution::reorderList(ListNode * head)
{
	//特殊情况
	if (head == nullptr) return;
	if (head->next == nullptr) return;

	//快慢指针找到中点,分离出后半段
	ListNode* fast = head->next;
	ListNode* slow = head;

	ListNode* latterhalf;

	while (true)
	{
		if (fast->next == nullptr)
		{
			latterhalf = slow->next;
			slow->next = nullptr;
			break;
		}
		if (fast->next->next == nullptr)
		{
			latterhalf = slow->next->next;
			slow->next->next = nullptr;
			break;
		}
		fast = fast->next->next;
		slow = slow->next;
	}

	//反转后半段
	//人工拆成两个链表,不要混在一起操作
	ListNode *pre = nullptr;
	ListNode* p2 = latterhalf;
	ListNode* p3;
	while (p2)
	{
		p3 = p2->next;
		p2->next = pre;
		pre = p2;
		p2 = p3;
	}

	//后半段插入前半段,从latterhalf开始
	latterhalf = pre;
	pre = head;

	while (latterhalf)
	{
		ListNode* temp = latterhalf->next;
		latterhalf->next = pre->next;
		pre->next = latterhalf;
		latterhalf = temp;
		pre = pre->next->next;
	}
	return;
}



#else
#endif
