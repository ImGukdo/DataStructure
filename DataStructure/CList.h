#pragma once
#include <assert.h>

///////////////////////////////////////////
// 노드 템플릿 구조체
template <typename T>
struct tNode
{
///////////////////////////////////////////
// public 맴버 변수
	tNode<T>* pPrevNode;  // 연결된 이전 노드 주소
	tNode<T>* pNextNode;  // 연결된 다음 노드 주소
	T		  data;	      // 데이터

///////////////////////////////////////////
// 생성자
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
// 링크드 리스트 템플릿 클래스
template <typename T>
class CList
{
///////////////////////////////////////////
// 생성자, 소멸자
public :
	CList();
	~CList();

///////////////////////////////////////////
// private 맴버 변수
private :
	tNode<T>*	m_pBeginNode;		// 시작 노드
	tNode<T>*	m_pEndNode;			// 마지막 노드
	tNode<T>*	m_pEndIterNode;     // end iterator가 가리키는 노드
	int			m_iCount;			// 현재 데이터 개수

///////////////////////////////////////////
// public 맴버 함수
public :
	void Push_back(const T& _data);   // 데이터 가장 뒤쪽에 추가
	void Push_front(const T& _data);  // 데이터 가장 앞쪽에 추가
	void Pop_back();				  // 가장 뒤에 있는 데이터 삭제
	void Pop_front();				  // 가장 앞에 있는 데이터 삭제
	void Clear();					  // 모든 데이터 삭제
	int Size() { return m_iCount; }  // 현재 개수
	tNode<T>* GetBeginNode() { return m_pBeginNode; }  // begin node 반환
	tNode<T>* GetEndNode() { return m_pEndNode; }  // end node 반환

	class CIterator;  // 전방 선언
	CIterator Begin()  // begin node를 가리키는 iterator 반환
	{
		// 데이터가 하나도 없으면 end iterator
		if (m_iCount == 0)
			return End();

		// 데이터의 처음을 가리키는 iterator
		return *(new CIterator(this, m_pBeginNode));
	}
	CIterator End() { return *(new CIterator(this, m_pEndIterNode)); }  // EndIter Node를 가리키는 iterator 반환
	CIterator Erase(CIterator& _iter);  // 데이터 삭제
	CIterator Insert(CIterator& _iter, const T& _data);  // 데이터 추가

///////////////////////////////////////////
// inner 클래스
public :
	class CIterator
	{
	///////////////////////////////////////////
	// 생성자, 소멸자
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
	// private 맴버 변수
	private :
		CList<T>*	m_pOwner;  // iterator가 가리키는 노드를 소유한 리스트
		tNode<T>*	m_pNode;   // iterator가 가리키는 노드
		bool		m_bValid;  // 유효성 체크

	///////////////////////////////////////////
	// public 맴버 함수
	public :
		///////////////////////////////////////////
		// == 비교 연산자
		bool operator == (const CIterator& _other)
		{
			return m_pNode == _other.m_pNode;
		}

		///////////////////////////////////////////
		// != 비교 연산자
		bool operator != (const CIterator& _other)
		{
			return !(*this == _other);
		}

		///////////////////////////////////////////
		// ++ 전위연산자
		CIterator& operator ++ ()
		{
			assert(nullptr != m_pNode);

			// m_pNode가 nullptr이면 end iterator
			m_pNode = m_pNode->pNextNode;

			return *this;
		}

		///////////////////////////////////////////
		// ++ 후위연산자
		CIterator operator ++ (int)
		{
			CIterator iter = *this;
			
			++(*this);

			return iter;
		}

		///////////////////////////////////////////
		// -- 전위연산자
		CIterator& operator -- ()
		{
			assert(m_pNode != m_pBeginNode);

			m_pNode = m_pNode->pPrevNode;

			return *this;
		}

		///////////////////////////////////////////
		// -- 후위연산자
		CIterator operator -- (int)
		{
			CIterator iter = *this;

			--(*iter);

			return iter;
		}

		///////////////////////////////////////////
		// * 연산자
		T& operator * ()
		{
			assert(m_bValid && nullptr != m_pNode);

			return m_pNode->data;
		}

		friend class CList<T>;
	};
};

///////////////////////////////////////////
// 생성자, 맴버 초기화
template<typename T>
inline CList<T>::CList()
	: m_pBeginNode(nullptr)
	, m_pEndNode(nullptr)
	, m_pEndIterNode(nullptr)
	, m_iCount(0)
{
	// end iterator가 가리킬 노드 생성
	m_pEndIterNode = new tNode<T>(nullptr, nullptr, 0);
}

///////////////////////////////////////////
// 소멸자, 힙메모리 해제
template<typename T>
inline CList<T>::~CList()
{
	// 개체 소멸시 저장하고 있는 노드 제거
	Clear();

	// end iterator가 가리키는 노드 제거
	delete m_pEndIterNode;
}

///////////////////////////////////////////
// 데이터 가장 뒤쪽에 추가
template<typename T>
inline void CList<T>::Push_back(const T& _data)
{
	// 리스트에 저장할 노드 만들기
	tNode<T>* pNewNode = new tNode<T>(m_pEndNode, nullptr, _data);

	if (nullptr == m_pBeginNode)
	{
		// 저장된 데이터가 0개일 때, 새로 넣어줄 데이터가 begin, end node
		m_pBeginNode = m_pEndNode = pNewNode;	
	}
	else
	{
		// 데이터가 있는 상태에서 추가 시, 마지막 데이터와 연결
		m_pEndNode->pNextNode = pNewNode;
		m_pEndNode = pNewNode;
	}

	// end iterator가 가리키는 노드와 연결
	m_pEndNode->pNextNode = m_pEndIterNode;
	m_pEndIterNode->pPrevNode = m_pEndNode;

	// 데이터 개수 증가
	++m_iCount;
}

///////////////////////////////////////////
// 데이터 가장 앞쪽에 추가
template<typename T>
inline void CList<T>::Push_front(const T & _data)
{
	// 리스트에 저장할 노드 만들기
	tNode<T>* pNewNode = new tNode<T>(nullptr, m_pBeginNode, _data);

	if (nullptr == m_pBeginNode)
	{
		// 저장된 데이터가 0개일 때, 새로 넣어줄 데이터가 begin, end node
		m_pBeginNode = m_pEndNode = pNewNode;

		// end iterator가 가리키는 노드와 연결
		m_pEndNode->pNextNode = m_pEndIterNode;
		m_pEndIterNode->pPrevNode = m_pEndNode;
	}
	else
	{
		// 데이터가 있는 상태에서 추가 시, 처음 데이터와 연결
		m_pBeginNode->pPrevNode = pNewNode;
		m_pBeginNode = pNewNode;
	}

	// 데이터 개수 증가
	++m_iCount;
}

///////////////////////////////////////////
// 가장 뒤에 있는 데이터 삭제
template<typename T>
inline void CList<T>::Pop_back()
{
	// 데이터 개수가 1개 이상
	assert(0 < m_iCount);

	if (1 == m_iCount)
	{
		// 데이터 개수가 1이면
		delete m_pEndNode;
		m_pBeginNode = m_pEndNode = m_pEndIterNode;
		m_pEndIterNode->pPrevNode = nullptr;
	}
	else
	{
		// end node의 이전 node 
		tNode<T>* pNode = m_pEndNode->pPrevNode;
		
		// end node의 이전 node와 end iterator가 가리키는 node 연결
		pNode->pNextNode = m_pEndIterNode;
		m_pEndIterNode->pPrevNode = pNode;

		// end node 제거
		delete m_pEndNode;

		// end node의 이전 node를 end node로
		m_pEndNode = pNode;
	}

	// 개수 1개 줄이기
	--m_iCount;
}

///////////////////////////////////////////
// 가장 앞에 있는 데이터 삭제
template<typename T>
inline void CList<T>::Pop_front()
{
	// 데이터 개수가 1개 이상
	assert(0 < m_iCount);

	if (1 == m_iCount)
	{
		// 데이터 개수가 1이면
		delete m_pEndNode;
		m_pBeginNode = m_pEndNode = m_pEndIterNode;
		m_pEndIterNode->pPrevNode = nullptr;
	}
	else
	{
		// begin node의 다음 node 
		tNode<T>* pNode = m_pBeginNode->pNextNode;

		// begin node의 다음 node의 이전 노드를 없음 처리
		pNode->pPrevNode = nullptr;

		// begin node 제거
		delete m_pBeginNode;

		// begin node의 다음 node를 begin node로
		m_pBeginNode = pNode;
	}

	// 개수 1개 줄이기
	--m_iCount;
}

///////////////////////////////////////////
// 모든 노드 삭제
template<typename T>
inline void CList<T>::Clear()
{
	tNode<T>* pNode = m_pBeginNode;  // 시작 노드
	tNode<T>* pTempNode = nullptr;   // 다음 노드를 저장할 노드
	
	// 저장하고 있는 모든 노드를 순회 하면서 제거
	while (pNode)
	{
		pTempNode = pNode->pNextNode;  // 다음 노드 저장
		delete pNode;				   // 현재 노드 제거
		pNode = pTempNode;			   // 현재 노드를 다음 노드로
	}

	m_iCount = 0;  // 개수 초기화
	m_pBeginNode = m_pEndNode = nullptr;  // begin, end, EndIter 노드 초기화

	// end iterator가 가리킬 노드 재생성 
	m_pEndIterNode = new tNode<T>(nullptr, nullptr, 0);
}

///////////////////////////////////////////
// iterator가 가리키고 있는 노드 삭제
template<typename T>
inline typename CList<T>::CIterator CList<T>::Erase(CIterator& _iter)
{
	// iterator가 유효하고, iterator가 가리키는 list와 삭제하려는 list가 동일하고, node가 nullptr이 아니고 end iterator가 아니여야 함
	assert(_iter.m_bValid && this == _iter.m_pOwner && nullptr != _iter.m_pNode && End() != _iter);
	tNode<T>* pPrev = nullptr;
	tNode<T>* pNext = nullptr;
	if (m_pBeginNode == _iter.m_pNode)
	{
		// begin node 삭제시
		pNext = m_pBeginNode->pNextNode;  // begin node의 next node
		m_pBeginNode = pNext;  // begin node 변경
		m_pBeginNode->pPrevNode = nullptr;  // 새로운 begin node의 이전 노드를 nullptr
	}
	else
	{
		pPrev = _iter.m_pNode->pPrevNode;  // 현재 node의 이전 node
		pNext = _iter.m_pNode->pNextNode;  // 현재 node의 다음 node

		pPrev->pNextNode = pNext;  // 이전 node의 다음 노드를 현재 node의 다음 node와 연결
		pNext->pPrevNode = pPrev;  // 다음 node의 이전 노드를 현재 node의 이전 node와 연결
	}

	delete _iter.m_pNode;  // node 삭제
	_iter.m_bValid = false;  // 현재 iterator의 유효성 false
	--m_iCount;  // 개수 감소

	return CIterator(this, pNext);
}

///////////////////////////////////////////
// iterator가 가리키고 있는 노드 위치에 데이터 추가
template<typename T>
inline typename CList<T>::CIterator CList<T>::Insert(CIterator& _iter, const T& _data)
{
	// iterator가 유효하고, iterator가 가리키는 list와 삭제하려는 list가 동일해야하고  node가 nullptr이 아니여야 함
	assert(_iter.m_bValid && this == _iter.m_pOwner && nullptr != _iter.m_pNode);

	// 추가 하려는 노드 생성
	tNode<T>* pNode = new tNode<T>(_iter.m_pNode->pPrevNode, _iter.m_pNode, _data);

	if (End() == _iter)
	{
		// end node 위치에 추가 시
		m_pEndNode->pNextNode = pNode;  // end node의 다음 node를 새로 생성한 노드로 설정
		m_pEndNode = pNode;  // end node 변경
	}
	else if (m_pBeginNode == _iter.m_pNode)
	{
		// begin node 위치에 추가 시
		m_pBeginNode->pPrevNode = pNode;  // begin node의 이전 node를 새로 생성한 노드로 설정
		m_pBeginNode = pNode;  // begin node 변경
	}
	else
	{
		tNode<T>* pPrev = _iter.m_pNode->pPrevNode;  // 새로 생성한 노드의 이전 노드
		tNode<T>* pNext = _iter.m_pNode;  // 새로 생성한 노드의 다음 노드

		pPrev->pNextNode = pNode;  // 새로 생성한 노드의 이전 노드의 다음 노드를 새로 생성한 노드로 설정
		pNext->pPrevNode = pNode;  // 새로 생성한 노드의 다음 노드의 이전 노드를 새로 생성한 노드로 설정
	}

	_iter.m_bValid = false;  // 현재 iterator의 유효성 false
	++m_iCount;  // 개수 증가

	return CIterator(this, pNode);
}
