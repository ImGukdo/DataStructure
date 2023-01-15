#pragma once
#include "CList.h"

///////////////////////////////////////////
// 큐 템플릿 클래스
template <typename T>
class CQueue
{
	///////////////////////////////////////////
	// 생성자, 소멸자
public:
	CQueue() {}
	~CQueue() {}

	///////////////////////////////////////////
	// private 맴버 변수
private:
	CList<T>	m_myList;  // 데이터를 저장할 리스트

	///////////////////////////////////////////
	// public 맴버 함수
public:
	void Push(const T& _data) { m_myList.Push_back(_data); }  // 리스트의 가장 뒤쪽에 데이터 추가
	void Pop() { m_myList.Pop_front(); }  // 리스트의 가장 앞쪽의 데이터 제거
	T& Front() { return m_myList.GetBeginNode()->data; }  // 리스트의 가장 앞쪽 데이터 반환
	bool Empty() { return 0 == m_myList.Size(); }  // 리스트가 비어 있는지
	int Size() { return m_myList.Size(); }  // 리스트의 크기 반환
};
