#include "stdafx.h"
#include "Animation.h"

template<unsigned int Count>
Animation<Count>::Animation(unsigned int _size)
	: m_Size(((!Count) ? _size : Count))
{
	if (!Count) { m_pFrames = new Frame[_size]{ 0 }; }
	else { m_pFrames = nullptr; }
}

template<unsigned int Count>
Animation<Count>::Animation(const Frame* pFrames, unsigned int count)
	: m_Size(count)
{
	m_pFrames = new Frame[count]{ 0 };
}

template<unsigned int Count>
bool Animation<Count>::AddFrame(const Frame& frame)
{
	if (m_pFrames) {
		if (m_Position < m_Size)
		{
			m_pFrames[m_Position] = frame;
			m_Position++;
			return true;
		}
	}
	else if (m_Position < m_Size)
	{
		m_Frames[m_Position] = frame;
		m_Position++;
		return true;
	}

	return false;
}

template<unsigned int Count>
const Frame& Animation<Count>::getFrame(unsigned int idx) const
{
	if (idx < m_Position) {
		return (m_pFrames) ? m_pFrames[idx] : m_pFrames[idx];
	}

	return Frame{ 0 };
}

template<unsigned int Count>
Animation<Count>::~Animation()
{ 
	if (m_pFrames) delete[] m_pFrames; 
}