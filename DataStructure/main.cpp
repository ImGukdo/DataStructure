#include <iostream>
#include "CVector.h"
#include "CList.h"
#include "CStack.h"
#include "CQueue.h"
#include "CDeque.h"


using namespace std;

int main()
{
	///////////////////////////////////////////
	// vector
	CVector<int> vec;
	// 데이터 뒤쪽에 넣기
	for (int i = 0; i < 10; ++i)
	{
		vec.Push_back(i);
	}
	cout << "vector : ";

	// 인덱스를 이용하여 데이터 출력
	for (int i = 0; i < vec.Size(); ++i)
	{
		cout << vec[i] << " ";
	}
	cout << endl;


	///////////////////////////////////////////
	// list
	CList<int> list;
	// 데이터 뒤쪽에 넣기
	for (int i = 0; i < 5; ++i)
	{
		list.Push_back(i);
	}
	
	// 데이터 사이 사이에 999 넣기
	CList<int>::CIterator listIter = list.Begin();
	for (; listIter != list.End(); ++listIter)
	{
		++listIter;
		listIter = list.Insert(listIter, 999);
	}
	cout << "list : ";

	// iterator로 데이터 출력
	for (listIter = list.Begin(); listIter != list.End(); ++listIter)
	{
		cout << *listIter << " ";
	}
	cout << endl;


	///////////////////////////////////////////
	// stack
	CStack<int> stack;
	// 데이터 넣기
	for (int i = 0; i < 10; ++i)
	{
		stack.Push(i);
	}
	cout << "stack : ";
	// 데이터를 빼기
	while (!stack.Empty())
	{
		cout << stack.Top() << " ";
		stack.Pop();
	}
	cout << endl;


	///////////////////////////////////////////
	// queue
	CQueue<int> que;
	// 데이터 넣기
	for (int i = 0; i < 10; ++i)
	{
		que.Push(i);
	}
	cout << "queue : ";
	// 데이터를 빼기
	while (!que.Empty())
	{
		cout << que.Front() << " ";
		que.Pop();
	}
	cout << endl;


	///////////////////////////////////////////
	// deque
	CDeque<int> dq;
	// 데이터를 앞쪽에서부터 넣기
	for (int i = 0; i < 10; ++i)
	{
		dq.Push_front(i);
	}
	cout << "deque : ";
	// 데이터를 뒤쪽에서부터 빼기
	while (!dq.Empty())
	{
		cout << dq.End() << " ";
		dq.Pop_back();
	}
	cout << endl;

	return 0;
}