#pragma once
#include <assert.h>

///////////////////////////////////////////
// ��� ���ø� ����ü
template <typename T>
struct tNode
{
///////////////////////////////////////////
// public �ɹ� ����
	tNode<T>* pPrevNode;  // ����� ���� ��� �ּ�
	tNode<T>* pNextNode;  // ����� ���� ��� �ּ�
	T		  data;	      // ������

///////////////////////////////////////////
// ������
	tNode()
		: pPrevNode(nullptr)
		, pNextNode(nullptr)
		, data()
	{}
	tNode(tNode<T>* _pPrevNode, tNode<T>* _pNextNode, const T& _data)
		: pPrevNode(_pPrevNode)
		, pNextNode(_pNextNode)
		, data(_data)
	{}
};



///////////////////////////////////////////
// ��ũ�� ����Ʈ ���ø� Ŭ����
template <typename T>
class CList
{
///////////////////////////////////////////
// ������, �Ҹ���
public :
	CList();
	~CList();

///////////////////////////////////////////
// private �ɹ� ����
private :
	tNode<T>*	m_pBeginNode;		// ���� ���
	tNode<T>*	m_pEndNode;			// ������ ���
	tNode<T>*	m_pEndIterNode;     // end iterator�� ����Ű�� ���
	int			m_iCount;			// ���� ������ ����

///////////////////////////////////////////
// public �ɹ� �Լ�
public :
	void Push_back(const T& _data);   // ������ ���� ���ʿ� �߰�
	void Push_front(const T& _data);  // ������ ���� ���ʿ� �߰�
	void Pop_back();				  // ���� �ڿ� �ִ� ������ ����
	void Pop_front();				  // ���� �տ� �ִ� ������ ����
	void Clear();					  // ��� ������ ����
	int Size() { return m_iCount; }  // ���� ����
	tNode<T>* GetBeginNode() { return m_pBeginNode; }  // begin node ��ȯ
	tNode<T>* GetEndNode() { return m_pEndNode; }  // end node ��ȯ

	class CIterator;  // ���� ����
	CIterator Begin()  // begin node�� ����Ű�� iterator ��ȯ
	{
		// �����Ͱ� �ϳ��� ������ end iterator
		if (m_iCount == 0)
			return End();

		// �������� ó���� ����Ű�� iterator
		return *(new CIterator(this, m_pBeginNode));
	}
	CIterator End() { return *(new CIterator(this, m_pEndIterNode)); }  // EndIter Node�� ����Ű�� iterator ��ȯ
	CIterator Erase(CIterator& _iter);  // ������ ����
	CIterator Insert(CIterator& _iter, const T& _data);  // ������ �߰�

///////////////////////////////////////////
// inner Ŭ����
public :
	class CIterator
	{
	///////////////////////////////////////////
	// ������, �Ҹ���
	public :
		CIterator()
			: m_pOwner(nullptr)
			, m_pNode(nullptr)
			, m_bValid(false)
		{}
		CIterator(CList<T>*	_pOwner, tNode<T>* _pNode)
			: m_pOwner(_pOwner)
			, m_pNode(_pNode)
			, m_bValid(true)
		{}
		~CIterator(){}

	///////////////////////////////////////////
	// private �ɹ� ����
	private :
		CList<T>*	m_pOwner;  // iterator�� ����Ű�� ��带 ������ ����Ʈ
		tNode<T>*	m_pNode;   // iterator�� ����Ű�� ���
		bool		m_bValid;  // ��ȿ�� üũ

	///////////////////////////////////////////
	// public �ɹ� �Լ�
	public :
		///////////////////////////////////////////
		// == �� ������
		bool operator == (const CIterator& _other)
		{
			return m_pNode == _other.m_pNode;
		}

		///////////////////////////////////////////
		// != �� ������
		bool operator != (const CIterator& _other)
		{
			return !(*this == _other);
		}

		///////////////////////////////////////////
		// ++ ����������
		CIterator& operator ++ ()
		{
			assert(nullptr != m_pNode);

			// m_pNode�� nullptr�̸� end iterator
			m_pNode = m_pNode->pNextNode;

			return *this;
		}

		///////////////////////////////////////////
		// ++ ����������
		CIterator operator ++ (int)
		{
			CIterator iter = *this;
			
			++(*this);

			return iter;
		}

		///////////////////////////////////////////
		// -- ����������
		CIterator& operator -- ()
		{
			assert(m_pNode != m_pBeginNode);

			m_pNode = m_pNode->pPrevNode;

			return *this;
		}

		///////////////////////////////////////////
		// -- ����������
		CIterator operator -- (int)
		{
			CIterator iter = *this;

			--(*iter);

			return iter;
		}

		///////////////////////////////////////////
		// * ������
		T& operator * ()
		{
			assert(m_bValid && nullptr != m_pNode);

			return m_pNode->data;
		}

		friend class CList<T>;
	};
};

///////////////////////////////////////////
// ������, �ɹ� �ʱ�ȭ
template<typename T>
inline CList<T>::CList()
	: m_pBeginNode(nullptr)
	, m_pEndNode(nullptr)
	, m_pEndIterNode(nullptr)
	, m_iCount(0)
{
	// end iterator�� ����ų ��� ����
	m_pEndIterNode = new tNode<T>(nullptr, nullptr, 0);
}

///////////////////////////////////////////
// �Ҹ���, ���޸� ����
template<typename T>
inline CList<T>::~CList()
{
	// ��ü �Ҹ�� �����ϰ� �ִ� ��� ����
	Clear();

	// end iterator�� ����Ű�� ��� ����
	delete m_pEndIterNode;
}

///////////////////////////////////////////
// ������ ���� ���ʿ� �߰�
template<typename T>
inline void CList<T>::Push_back(const T& _data)
{
	// ����Ʈ�� ������ ��� �����
	tNode<T>* pNewNode = new tNode<T>(m_pEndNode, nullptr, _data);

	if (nullptr == m_pBeginNode)
	{
		// ����� �����Ͱ� 0���� ��, ���� �־��� �����Ͱ� begin, end node
		m_pBeginNode = m_pEndNode = pNewNode;	
	}
	else
	{
		// �����Ͱ� �ִ� ���¿��� �߰� ��, ������ �����Ϳ� ����
		m_pEndNode->pNextNode = pNewNode;
		m_pEndNode = pNewNode;
	}

	// end iterator�� ����Ű�� ���� ����
	m_pEndNode->pNextNode = m_pEndIterNode;
	m_pEndIterNode->pPrevNode = m_pEndNode;

	// ������ ���� ����
	++m_iCount;
}

///////////////////////////////////////////
// ������ ���� ���ʿ� �߰�
template<typename T>
inline void CList<T>::Push_front(const T & _data)
{
	// ����Ʈ�� ������ ��� �����
	tNode<T>* pNewNode = new tNode<T>(nullptr, m_pBeginNode, _data);

	if (nullptr == m_pBeginNode)
	{
		// ����� �����Ͱ� 0���� ��, ���� �־��� �����Ͱ� begin, end node
		m_pBeginNode = m_pEndNode = pNewNode;

		// end iterator�� ����Ű�� ���� ����
		m_pEndNode->pNextNode = m_pEndIterNode;
		m_pEndIterNode->pPrevNode = m_pEndNode;
	}
	else
	{
		// �����Ͱ� �ִ� ���¿��� �߰� ��, ó�� �����Ϳ� ����
		m_pBeginNode->pPrevNode = pNewNode;
		m_pBeginNode = pNewNode;
	}

	// ������ ���� ����
	++m_iCount;
}

///////////////////////////////////////////
// ���� �ڿ� �ִ� ������ ����
template<typename T>
inline void CList<T>::Pop_back()
{
	// ������ ������ 1�� �̻�
	assert(0 < m_iCount);

	if (1 == m_iCount)
	{
		// ������ ������ 1�̸�
		delete m_pEndNode;
		m_pBeginNode = m_pEndNode = m_pEndIterNode;
		m_pEndIterNode->pPrevNode = nullptr;
	}
	else
	{
		// end node�� ���� node 
		tNode<T>* pNode = m_pEndNode->pPrevNode;
		
		// end node�� ���� node�� end iterator�� ����Ű�� node ����
		pNode->pNextNode = m_pEndIterNode;
		m_pEndIterNode->pPrevNode = pNode;

		// end node ����
		delete m_pEndNode;

		// end node�� ���� node�� end node��
		m_pEndNode = pNode;
	}

	// ���� 1�� ���̱�
	--m_iCount;
}

///////////////////////////////////////////
// ���� �տ� �ִ� ������ ����
template<typename T>
inline void CList<T>::Pop_front()
{
	// ������ ������ 1�� �̻�
	assert(0 < m_iCount);

	if (1 == m_iCount)
	{
		// ������ ������ 1�̸�
		delete m_pEndNode;
		m_pBeginNode = m_pEndNode = m_pEndIterNode;
		m_pEndIterNode->pPrevNode = nullptr;
	}
	else
	{
		// begin node�� ���� node 
		tNode<T>* pNode = m_pBeginNode->pNextNode;

		// begin node�� ���� node�� ���� ��带 ���� ó��
		pNode->pPrevNode = nullptr;

		// begin node ����
		delete m_pBeginNode;

		// begin node�� ���� node�� begin node��
		m_pBeginNode = pNode;
	}

	// ���� 1�� ���̱�
	--m_iCount;
}

///////////////////////////////////////////
// ��� ��� ����
template<typename T>
inline void CList<T>::Clear()
{
	tNode<T>* pNode = m_pBeginNode;  // ���� ���
	tNode<T>* pTempNode = nullptr;   // ���� ��带 ������ ���
	
	// �����ϰ� �ִ� ��� ��带 ��ȸ �ϸ鼭 ����
	while (pNode)
	{
		pTempNode = pNode->pNextNode;  // ���� ��� ����
		delete pNode;				   // ���� ��� ����
		pNode = pTempNode;			   // ���� ��带 ���� ����
	}

	m_iCount = 0;  // ���� �ʱ�ȭ
	m_pBeginNode = m_pEndNode = nullptr;  // begin, end, EndIter ��� �ʱ�ȭ

	// end iterator�� ����ų ��� ����� 
	m_pEndIterNode = new tNode<T>(nullptr, nullptr, 0);
}

///////////////////////////////////////////
// iterator�� ����Ű�� �ִ� ��� ����
template<typename T>
inline typename CList<T>::CIterator CList<T>::Erase(CIterator& _iter)
{
	// iterator�� ��ȿ�ϰ�, iterator�� ����Ű�� list�� �����Ϸ��� list�� �����ϰ�, node�� nullptr�� �ƴϰ� end iterator�� �ƴϿ��� ��
	assert(_iter.m_bValid && this == _iter.m_pOwner && nullptr != _iter.m_pNode && End() != _iter);
	tNode<T>* pPrev = nullptr;
	tNode<T>* pNext = nullptr;
	if (m_pBeginNode == _iter.m_pNode)
	{
		// begin node ������
		pNext = m_pBeginNode->pNextNode;  // begin node�� next node
		m_pBeginNode = pNext;  // begin node ����
		m_pBeginNode->pPrevNode = nullptr;  // ���ο� begin node�� ���� ��带 nullptr
	}
	else
	{
		pPrev = _iter.m_pNode->pPrevNode;  // ���� node�� ���� node
		pNext = _iter.m_pNode->pNextNode;  // ���� node�� ���� node

		pPrev->pNextNode = pNext;  // ���� node�� ���� ��带 ���� node�� ���� node�� ����
		pNext->pPrevNode = pPrev;  // ���� node�� ���� ��带 ���� node�� ���� node�� ����
	}

	delete _iter.m_pNode;  // node ����
	_iter.m_bValid = false;  // ���� iterator�� ��ȿ�� false
	--m_iCount;  // ���� ����

	return CIterator(this, pNext);
}

///////////////////////////////////////////
// iterator�� ����Ű�� �ִ� ��� ��ġ�� ������ �߰�
template<typename T>
inline typename CList<T>::CIterator CList<T>::Insert(CIterator& _iter, const T& _data)
{
	// iterator�� ��ȿ�ϰ�, iterator�� ����Ű�� list�� �����Ϸ��� list�� �����ؾ��ϰ�  node�� nullptr�� �ƴϿ��� ��
	assert(_iter.m_bValid && this == _iter.m_pOwner && nullptr != _iter.m_pNode);

	// �߰� �Ϸ��� ��� ����
	tNode<T>* pNode = new tNode<T>(_iter.m_pNode->pPrevNode, _iter.m_pNode, _data);

	if (End() == _iter)
	{
		// end node ��ġ�� �߰� ��
		m_pEndNode->pNextNode = pNode;  // end node�� ���� node�� ���� ������ ���� ����
		m_pEndNode = pNode;  // end node ����
	}
	else if (m_pBeginNode == _iter.m_pNode)
	{
		// begin node ��ġ�� �߰� ��
		m_pBeginNode->pPrevNode = pNode;  // begin node�� ���� node�� ���� ������ ���� ����
		m_pBeginNode = pNode;  // begin node ����
	}
	else
	{
		tNode<T>* pPrev = _iter.m_pNode->pPrevNode;  // ���� ������ ����� ���� ���
		tNode<T>* pNext = _iter.m_pNode;  // ���� ������ ����� ���� ���

		pPrev->pNextNode = pNode;  // ���� ������ ����� ���� ����� ���� ��带 ���� ������ ���� ����
		pNext->pPrevNode = pNode;  // ���� ������ ����� ���� ����� ���� ��带 ���� ������ ���� ����
	}

	_iter.m_bValid = false;  // ���� iterator�� ��ȿ�� false
	++m_iCount;  // ���� ����

	return CIterator(this, pNode);
}
