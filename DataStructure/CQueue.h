#pragma once
#include "CList.h"

///////////////////////////////////////////
// ť ���ø� Ŭ����
template <typename T>
class CQueue
{
	///////////////////////////////////////////
	// ������, �Ҹ���
public:
	CQueue() {}
	~CQueue() {}

	///////////////////////////////////////////
	// private �ɹ� ����
private:
	CList<T>	m_myList;  // �����͸� ������ ����Ʈ

	///////////////////////////////////////////
	// public �ɹ� �Լ�
public:
	void Push(const T& _data) { m_myList.Push_back(_data); }  // ����Ʈ�� ���� ���ʿ� ������ �߰�
	void Pop() { m_myList.Pop_front(); }  // ����Ʈ�� ���� ������ ������ ����
	T& Front() { return m_myList.GetBeginNode()->data; }  // ����Ʈ�� ���� ���� ������ ��ȯ
	bool Empty() { return 0 == m_myList.Size(); }  // ����Ʈ�� ��� �ִ���
	int Size() { return m_myList.Size(); }  // ����Ʈ�� ũ�� ��ȯ
};
