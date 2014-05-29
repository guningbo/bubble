#include "bubble.h"
#include <fstream> 
void BubbleList::Bubblelist()
{
	head=new BUBBlE;
	head->next=NULL;
	end=head;
	
}
//返回链表长度

int BubbleList::ListSize()
{
	int num=0;

	BUBBlE *p=NULL;
	p=head;
	while(p->next!=NULL)
	{
		p=p->next;
		num++;
	}
	return num;
}
BUBBlE* BubbleList::GetHead()
{
	return head;
}
void BubbleList::Getpoint()
{
	ifstream in("a.txt"); 
	BUBBLE* p=new BUBBLE;
	int N;
	in>>N;
	for(int i=0;i<N;i++)
	{
		in>>p->num;
		in>>p->pointX;
		in>>p->pointY;
		in>>p->Attribute;
		end->next=p;
		end=p;
		p=new BUBBLE;
	}
	end->next=NULL;

}

void BubbleList::AddPoint()
{
	

}