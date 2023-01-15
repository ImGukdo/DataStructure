#pragma once
#include <assert.h>

///////////////////////////////////////////
// 가변 배열 템플릿 클래스
template <typename T>
class CVector
{
///////////////////////////////////////////
// 생성자, 소멸자
public :
	CVector();
	~CVector();

///////////////////////////////////////////
// private 맴버 변수
private :
	T*		m_pData;		// 데이터를 저장할 힙메모리 주소
	int		m_iCount;		// 현재 저장되어 있는 데이터 개수
	int		m_iMaxCount;	// 저장할 수 있는 데이터 최대 개수

///////////////////////////////////////////
// private 맴버 함수
private :
	void ReAllocate(int _iSize);

///////////////////////////////////////////
// public 맴버 함수
public :
	void Push_back(const T& _data);  // 데이터 가장 뒤에 추가
	void Pop_back();				 // 가장 뒤에 있는 데이터 삭제
	int Size() { return m_iCount; }  // 현재 개수
	T* Data() { return m_pData; }	 // 데이터의 시작 주소 반환
	void Clear() { m_iCount = 0; }	 // 데이터 초기화
	
	 // 인덱스로 데이터 접근
	T& operator [](int _iIndex) 
	{ 
		// 인덱스가 개수보다 작아야함
		assert(_iIndex < m_iCount);
		return m_pData[_iIndex];
	} 

	class CIterator;  // 전방 선언
	CIterator Begin() 
	{ 
		// 데이터가 하나도 없으면 end iterator
		if (m_iCount == 0)
			return End();

		// 데이터의 처음을 가리키는 iterator
		return *(new CIterator(this, m_pData, 0)); 
	}  

	//End는 index가 -1인 걸로 정의
	CIterator End() { return *(new CIterator(this, m_pData, -1)); }   // 데이터의 마지막을 가리키는 iterator
	CIterator Erase(CIterator& _iter);  // 데이터 삭제

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
			, m_pData(nullptr)
			, m_iIndex(-1)
			, m_bValid(false)
		{}
		CIterator(CVector<T>* _pVector, T* _pData, int _iIndex)
			: m_pOwner(_pVector)
			, m_pData(_pData)
			, m_iIndex(_iIndex)
			, m_bValid(true)
		{}
		~CIterator(){}

	///////////////////////////////////////////
	// private 맴버 변수
	private :
		CVector<T>*	m_pOwner;  // iterator가 가리키고 있는 배열을 소유한 백터
		T*			m_pData;   // iterator가 가리키고 있는 배열
		int			m_iIndex;  // iterator가 가리키고 있는 배열의 인덱스
		bool		m_bValid;  // 유효성 체크

	///////////////////////////////////////////
	// public 맴버 함수
	public :
		///////////////////////////////////////////
		// == 비교 연산자
		bool operator == (const CIterator& _other)
		{
			return (m_pOwner == _other.m_pOwner) && (m_iIndex == _other.m_iIndex);
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
			// iterator가 valid하고 end iterator가 아니고 백터의 데이터 시작주소가 일치해야함
			assert(m_bValid && -1 != m_iIndex);

			// 인덱스를 증가하고 인덱스가 현재 데이터 개수와 같으면 end iterator
			if (++m_iIndex == m_pOwner->m_iCount)
				m_iIndex = -1;

			return *this;
		}

		///////////////////////////////////////////
		// ++ 후위연산자
		CIterator operator ++ (int)
		{
			// 반환할 값을 생성
			CIterator temp = *this;

			// 전위 연산자를 통해 증가
			++(*this);

			return temp;
		}

		///////////////////////////////////////////
		// -- 전위연산자
		CIterator& operator -- ()
		{
			// iterator가 valid하고 인덱스가 0이 아니고 백터의 데이터 시작주소가 일치해야함
			assert(m_bValid && 0 != m_iIndex && m_pOwner->m_pData == m_pData);

			if (-1 == m_iIndex)
				m_iIndex = m_pOwner->m_iCount - 1;  // end iterator 면 마지막 데이터 인덱스 설정
			else
				--m_iIndex;  // 이전 인덱스로 설정

			return *this;
		}

		///////////////////////////////////////////
		// -- 후위연산자
		CIterator operator -- (int)
		{
			// 반환할 값을 생성
			CIterator temp = *this;

			// 후위 연산자를 통해 감소
			--(*this);

			return temp;
		}

		///////////////////////////////////////////
		// * 연산자
		T& operator * ()
		{
			assert(m_bValid && -1 != m_iIndex && m_iIndex < m_pOwner->m_iCount);
			return m_pData[m_iIndex];
		}

		// CVector 클래스가 접근 가능하게 설정
		friend class CVector<T>;
	};
};

///////////////////////////////////////////
// 생성자, 맴버 초기화
template<typename T>
inline CVector<T>::CVector()
	: m_pData(nullptr)
	, m_iCount(0)
	, m_iMaxCount(2)
{
	// 초기 힙메모리 생성
	m_pData = new T[2];
}

///////////////////////////////////////////
// 소멸자, 힙메모리 해제
template<typename T>
inline CVector<T>::~CVector()
{
	delete[] m_pData;
	m_pData = nullptr;
}

///////////////////////////////////////////
// 데이터 저장 공간 추가
template<typename T>
inline void CVector<T>::ReAllocate(int _iSize)
{
	// 새로운 힙메모리 공간 할당
	T* pTemp = new T[_iSize];

	// 새로운 메모리에 데이터 복사
	for (int i = 0; i < m_iCount; ++i)
	{
		pTemp[i] = m_pData[i];
	}

	// 기존 데이터 공간 삭제
	delete[] m_pData;

	// 새로운 데이터를 저장할 주소 가리키기 
	m_pData = pTemp;

	// 최대 개수 설정
	m_iMaxCount = _iSize;
}

///////////////////////////////////////////
// 데이터 추가
template<typename T>
inline void CVector<T>::Push_back(const T & _data)
{
	// 현재 개수가 최대 개수 이상이면
	if (m_iMaxCount <= m_iCount)
	{
		// 현재 최대 개수의 2배로 확장
		ReAllocate(m_iMaxCount * 2);
	}

	// 데이터 저장, 현재 개수 증가
	m_pData[m_iCount++] = _data;
}

///////////////////////////////////////////
// 가장 뒤에 있는 데이터 삭제
template<typename T>
inline void CVector<T>::Pop_back()
{
	// 데이터의 개수가 1개 이상
	assert(0 < m_iCount);

	// 데이터 개수 1개 줄이기
	--m_iCount;
}

///////////////////////////////////////////
// 데이터 삭제
template<typename T>
inline typename CVector<T>::CIterator CVector<T>::Erase(CIterator& _iter)
{
	// 에러 상황
	assert(_iter.m_bValid && _iter.m_iIndex != -1 && this == _iter.m_pOwner);

	// 현재 인덱스의 데이터 지우기
	for (int i = _iter.m_iIndex; i < m_iCount - 1; ++i)
	{
		m_pData[i] = m_pData[i + 1];
	}

	// 전달 받은 iterator는 이제 valid 하지 않음
	_iter.m_bValid = false;

	// 개수를 하나 줄임 
	--m_iCount;

	// 개수가 인덱스와 같거나 개수가 0이면 end iterator로 설정
	if (_iter.m_iIndex == m_iCount || 0 == m_iCount)
		return End();

	return CIterator(this, m_pData, _iter.m_iIndex);
}
