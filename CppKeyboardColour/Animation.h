// Created by DeviceIoControl

#pragma once
#include <Windows.h>

enum Zone : byte
{
	LEFT,
	MID,
	RIGHT,
	ALL
};

struct Colour
{
	byte rgb[3];
	Zone zone;
};

struct Frame
{
	Colour colour[3];
	unsigned int ms_time;
};

template<unsigned int Count>
class Animation
{
public:
	Animation(unsigned int size);
	Animation(const Frame* pFrames, unsigned int count);
	bool AddFrame(const Frame& frame);
	const Frame& getFrame(unsigned int idx) const;
	inline unsigned int size() const { return m_Size; }
	~Animation();

private:
	Frame* m_pFrames;
	Frame m_Frames[Count];
	const unsigned int m_Size;
	unsigned int m_Position = 0;
};