#include "bubble.h"
#include <fstream> 
#define PopSpeed 0.1
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
		p->Velocity[0]=0;
		p->Velocity[1]=0;
		p->Mass=0.1;
		time(&(p->time));

		end->next=p;
		end=p;
		p=new BUBBLE;
	}
	end->next=NULL;
	free(p);
}

void BubbleList::AddPoint()
{
	
	for(int i=0;i<rand()%4+1;i++){
	BUBBlE *p=new BUBBlE;
	p->num=end->num+1;
	p->pointX=randompoint();
	p->pointY=randompoint();
	p->Attribute=randomattr();
	p->Mass=0.1*(p->Attribute)/0.04;
	time(&(p->time));
	p->Velocity[0]=0.0;
	p->Velocity[1]=0.0;
	end->next=p;
	end=p;
	}
	end->next=NULL;
	
}
REAL randompoint()
{
	
	 REAL point=(rand()%80)/100.0;
	 if(rand()%2==0)point=-1*point;

	 return point;
}

REAL randomattr()
{
	
	REAL point=(rand()%4+2)/100.0;
	return point;
}

void BubbleList::popPoint()
{
	BUBBlE* p;
	BUBBlE* q;
		p=q=head;
	BUBBlE* r=head;
	REAL t;
	time_t t1;
	p=p->next;
	while(p->next!=NULL)
	{
	time(&t1);
	 
	 t=difftime(t1,p->time);
	 t=-1*PopSpeed*t*p->Attribute;
	 t=pow(2.71828,t);
	 t=1-t;
	 REAL temp=(rand()%900+100)/1000.0;
	 if(temp<t)
	 {
		
		q->next=p->next;
		r=p;
		p=q->next;
		free(r);
	 }
	 else
	 {
		q=p;
		p=p->next;
	 }

	}
}


void BubbleList::popPoint2()
{
	BUBBlE* p;
	BUBBlE* q;
	p=q=head;
	if(ListSize()>5)
	{
	p=q->next;
	q->next=p->next;
	free(p);
	}
}
