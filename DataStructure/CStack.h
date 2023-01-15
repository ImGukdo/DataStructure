#pragma once
#include "CList.h"

///////////////////////////////////////////
// ���� ���ø� Ŭ����
template <typename T>
class CStack
{
///////////////////////////////////////////
// ������, �Ҹ���
public :
	CStack(){}
	~CStack(){}

///////////////////////////////////////////
// private �ɹ� ����
private :
	CList<T>	m_myList;  // �����͸� ������ ����Ʈ

///////////////////////////////////////////
// public �ɹ� �Լ�
public :
	void Push(const T& _data) { m_myList.Push_back(_data); }  // ����Ʈ�� ���� ���ʿ� ������ �߰�
	void Pop() { m_myList.Pop_back(); }  // ����Ʈ�� ���� ������ ������ ����
	T& Top() {	return m_myList.GetEndNode()->data;}  // ����Ʈ�� ���� ���� ������ ��ȯ
	bool Empty() { return 0 == m_myList.Size(); }  // ����Ʈ�� ��� �ִ���
	int Size(){return m_myList.Size();}  // ����Ʈ�� ũ�� ��ȯ
};
