#pragma once
#include <assert.h>

///////////////////////////////////////////
// ���� �迭 ���ø� Ŭ����
template <typename T>
class CVector
{
///////////////////////////////////////////
// ������, �Ҹ���
public :
	CVector();
	~CVector();

///////////////////////////////////////////
// private �ɹ� ����
private :
	T*		m_pData;		// �����͸� ������ ���޸� �ּ�
	int		m_iCount;		// ���� ����Ǿ� �ִ� ������ ����
	int		m_iMaxCount;	// ������ �� �ִ� ������ �ִ� ����

///////////////////////////////////////////
// private �ɹ� �Լ�
private :
	void ReAllocate(int _iSize);

///////////////////////////////////////////
// public �ɹ� �Լ�
public :
	void Push_back(const T& _data);  // ������ ���� �ڿ� �߰�
	void Pop_back();				 // ���� �ڿ� �ִ� ������ ����
	int Size() { return m_iCount; }  // ���� ����
	T* Data() { return m_pData; }	 // �������� ���� �ּ� ��ȯ
	void Clear() { m_iCount = 0; }	 // ������ �ʱ�ȭ
	
	 // �ε����� ������ ����
	T& operator [](int _iIndex) 
	{ 
		// �ε����� �������� �۾ƾ���
		assert(_iIndex < m_iCount);
		return m_pData[_iIndex];
	} 

	class CIterator;  // ���� ����
	CIterator Begin() 
	{ 
		// �����Ͱ� �ϳ��� ������ end iterator
		if (m_iCount == 0)
			return End();

		// �������� ó���� ����Ű�� iterator
		return *(new CIterator(this, m_pData, 0)); 
	}  

	//End�� index�� -1�� �ɷ� ����
	CIterator End() { return *(new CIterator(this, m_pData, -1)); }   // �������� �������� ����Ű�� iterator
	CIterator Erase(CIterator& _iter);  // ������ ����

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
	// private �ɹ� ����
	private :
		CVector<T>*	m_pOwner;  // iterator�� ����Ű�� �ִ� �迭�� ������ ����
		T*			m_pData;   // iterator�� ����Ű�� �ִ� �迭
		int			m_iIndex;  // iterator�� ����Ű�� �ִ� �迭�� �ε���
		bool		m_bValid;  // ��ȿ�� üũ

	///////////////////////////////////////////
	// public �ɹ� �Լ�
	public :
		///////////////////////////////////////////
		// == �� ������
		bool operator == (const CIterator& _other)
		{
			return (m_pOwner == _other.m_pOwner) && (m_iIndex == _other.m_iIndex);
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
			// iterator�� valid�ϰ� end iterator�� �ƴϰ� ������ ������ �����ּҰ� ��ġ�ؾ���
			assert(m_bValid && -1 != m_iIndex);

			// �ε����� �����ϰ� �ε����� ���� ������ ������ ������ end iterator
			if (++m_iIndex == m_pOwner->m_iCount)
				m_iIndex = -1;

			return *this;
		}

		///////////////////////////////////////////
		// ++ ����������
		CIterator operator ++ (int)
		{
			// ��ȯ�� ���� ����
			CIterator temp = *this;

			// ���� �����ڸ� ���� ����
			++(*this);

			return temp;
		}

		///////////////////////////////////////////
		// -- ����������
		CIterator& operator -- ()
		{
			// iterator�� valid�ϰ� �ε����� 0�� �ƴϰ� ������ ������ �����ּҰ� ��ġ�ؾ���
			assert(m_bValid && 0 != m_iIndex && m_pOwner->m_pData == m_pData);

			if (-1 == m_iIndex)
				m_iIndex = m_pOwner->m_iCount - 1;  // end iterator �� ������ ������ �ε��� ����
			else
				--m_iIndex;  // ���� �ε����� ����

			return *this;
		}

		///////////////////////////////////////////
		// -- ����������
		CIterator operator -- (int)
		{
			// ��ȯ�� ���� ����
			CIterator temp = *this;

			// ���� �����ڸ� ���� ����
			--(*this);

			return temp;
		}

		///////////////////////////////////////////
		// * ������
		T& operator * ()
		{
			assert(m_bValid && -1 != m_iIndex && m_iIndex < m_pOwner->m_iCount);
			return m_pData[m_iIndex];
		}

		// CVector Ŭ������ ���� �����ϰ� ����
		friend class CVector<T>;
	};
};

///////////////////////////////////////////
// ������, �ɹ� �ʱ�ȭ
template<typename T>
inline CVector<T>::CVector()
	: m_pData(nullptr)
	, m_iCount(0)
	, m_iMaxCount(2)
{
	// �ʱ� ���޸� ����
	m_pData = new T[2];
}

///////////////////////////////////////////
// �Ҹ���, ���޸� ����
template<typename T>
inline CVector<T>::~CVector()
{
	delete[] m_pData;
	m_pData = nullptr;
}

///////////////////////////////////////////
// ������ ���� ���� �߰�
template<typename T>
inline void CVector<T>::ReAllocate(int _iSize)
{
	// ���ο� ���޸� ���� �Ҵ�
	T* pTemp = new T[_iSize];

	// ���ο� �޸𸮿� ������ ����
	for (int i = 0; i < m_iCount; ++i)
	{
		pTemp[i] = m_pData[i];
	}

	// ���� ������ ���� ����
	delete[] m_pData;

	// ���ο� �����͸� ������ �ּ� ����Ű�� 
	m_pData = pTemp;

	// �ִ� ���� ����
	m_iMaxCount = _iSize;
}

///////////////////////////////////////////
// ������ �߰�
template<typename T>
inline void CVector<T>::Push_back(const T & _data)
{
	// ���� ������ �ִ� ���� �̻��̸�
	if (m_iMaxCount <= m_iCount)
	{
		// ���� �ִ� ������ 2��� Ȯ��
		ReAllocate(m_iMaxCount * 2);
	}

	// ������ ����, ���� ���� ����
	m_pData[m_iCount++] = _data;
}

///////////////////////////////////////////
// ���� �ڿ� �ִ� ������ ����
template<typename T>
inline void CVector<T>::Pop_back()
{
	// �������� ������ 1�� �̻�
	assert(0 < m_iCount);

	// ������ ���� 1�� ���̱�
	--m_iCount;
}

///////////////////////////////////////////
// ������ ����
template<typename T>
inline typename CVector<T>::CIterator CVector<T>::Erase(CIterator& _iter)
{
	// ���� ��Ȳ
	assert(_iter.m_bValid && _iter.m_iIndex != -1 && this == _iter.m_pOwner);

	// ���� �ε����� ������ �����
	for (int i = _iter.m_iIndex; i < m_iCount - 1; ++i)
	{
		m_pData[i] = m_pData[i + 1];
	}

	// ���� ���� iterator�� ���� valid ���� ����
	_iter.m_bValid = false;

	// ������ �ϳ� ���� 
	--m_iCount;

	// ������ �ε����� ���ų� ������ 0�̸� end iterator�� ����
	if (_iter.m_iIndex == m_iCount || 0 == m_iCount)
		return End();

	return CIterator(this, m_pData, _iter.m_iIndex);
}
