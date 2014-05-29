//声明一个气泡类
#ifndef _BUBBLE_H
#define _BUBBLE_H

#include<iostream>
#define REAL double
using namespace std;

typedef struct BUBBLE
{
	int num;
	REAL pointX;
	REAL pointY;
	REAL Attribute;
    struct BUBBLE *next;
}BUBBlE;


class BubbleList
{
	BUBBlE *head;
	BUBBLE *end;
	
public:
	void Bubblelist();
	bool InsertList(REAL x,REAL y,REAL attribute);  // 添加元素//
	bool FindList(REAL x, REAL y);
	int ListSize();
	bool UpdateList(REAL x,REAL y);
	BUBBlE* GetHead();
	void Getpoint();
	void getpoint();
	void AddPoint();
	
};



#endif