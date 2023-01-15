#pragma once
#include "CList.h"

///////////////////////////////////////////
// ��ť ���ø� Ŭ����
template <typename T>
class CDeque
{
	///////////////////////////////////////////
	// ������, �Ҹ���
public:
	CDeque() {}
	~CDeque() {}

	///////////////////////////////////////////
	// private �ɹ� ����
private:
	CList<T>	m_myList;  // �����͸� ������ ����Ʈ

	///////////////////////////////////////////
	// public �ɹ� �Լ�
public:
	void Push_back(const T& _data) { m_myList.Push_back(_data); }  // ����Ʈ�� ���� ���ʿ� ������ �߰�
	void Push_front(const T& _data) { m_myList.Push_front(_data); }  // ����Ʈ�� ���� ���ʿ� ������ �߰�
	void Pop_back() { m_myList.Pop_back(); }  // ����Ʈ�� ���� ������ ������ ����
	void Pop_front() { m_myList.Pop_front(); }  // ����Ʈ�� ���� ������ ������ ����
	T& Front() { return m_myList.GetBeginNode()->data; }  // ����Ʈ�� ���� ���� ������ ��ȯ
	T& End() { return m_myList.GetEndNode()->data; }  // ����Ʈ�� ���� ���� ������ ��ȯ
	bool Empty() { return 0 == m_myList.Size(); }  // ����Ʈ�� ��� �ִ���
	int Size() { return m_myList.Size(); }  // ����Ʈ�� ũ�� ��ȯ
};

