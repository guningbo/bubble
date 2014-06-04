#include "bubble.h"
#include <fstream> 
#define PopSpeed 0.07
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
	BUBBlE *p=new BUBBlE;
	p->pointX=randompoint();
	p->pointY=randompoint();
	p->Attribute=randomattr();
	p->Mass=0.1*(p->Attribute)/0.04;
	time(&(p->time));
	p->Velocity[0]=0.0;
	p->Velocity[1]=0.0;
	end->next=p;
	end=p;
	end->next=NULL;
	
}
REAL randompoint()
{
	
	 REAL point=(rand()%100)/100.0;
	 if(point<0.5)point-=0.8;
	 if(point>0.9)point-=0.4;
	 return point;
}

REAL randomattr()
{
	
	REAL point=(rand()%4+2)/100.0;
	return point;
}
void BubbleList::popPoint()
{
	BUBBlE* p=new BUBBlE;
	BUBBlE* q=new BUBBlE;
		p=q=head;
	BUBBlE* r=head;
	REAL t;
	time_t t1;
	p=p->next;
	while(p!=NULL)
	{
	time(&t1);
	 
	 t=difftime(t1,p->time);
	 t=-1*PopSpeed*t*p->Attribute;
	 t=pow(2.71828,t);
	 t=1-t;
	 REAL temp=(rand()%1000+200)/10000.0;
	 if(temp<t)
	 {
		q->next=p->next;
		r=p;
		p=p->next;
		free(r);
	 }
	 else
	 {
		q=p;
		p=p->next;
	 }
	}
}
