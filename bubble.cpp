#include "bubble.h"
#include <fstream> 
void BubbleList::Bubblelist()
{
	head=new BUBBlE;
	head->next=NULL;
	
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
	BUBBLE *end;
	end=head;
	BUBBLE* p=new BUBBLE;
	int N;
	in>>N;
	for(int i=0;i<N;i++)
	{
		in>>p->num;
		in>>p->pointX;
		p->pointX=(p->pointX-0.5)*2;
		in>>p->pointY;
		p->pointY=(p->pointY+0.5)*2;
		in>>p->Attribute;
		p->Attribute=p->Attribute/8.0;
		end->next=p;
		end=p;
		p=new BUBBLE;
	}
	end->next=NULL;

}