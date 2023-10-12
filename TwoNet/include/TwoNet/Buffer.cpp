#include "pch.h"
#include "Buffer.h"

TwoNet::Buffer::Buffer(size_t intialSize)
	: m_Index(0)
{
	m_Buffer.resize(intialSize);
}

TwoNet::Buffer::~Buffer() { }

void TwoNet::Buffer::SerializeUInt_32(uint32_t value)
{
	size_t size = sizeof(uint32_t);
	EnsureCapacity(size);
	memcpy(&m_Buffer[m_Index], &value, size);
	m_Index += size;
}

uint32_t TwoNet::Buffer::DeserializeUInt_32()
{
	size_t size = sizeof(uint32_t);
	if (m_Index - size >= 0) {
		uint32_t value;
		memcpy(&value, &m_Buffer[m_Index - size], size);
		m_Index -= size;
		return value;
	}
	else {
		// Handle buffer underflow error
		return 0; // You might want to define error handling here
	}
}

void TwoNet::Buffer::SerializeUInt_16(uint16_t value)
{
	size_t size = sizeof(uint16_t);
	EnsureCapacity(size);
	memcpy(&m_Buffer[m_Index], &value, size);
	m_Index += size;
}

uint32_t TwoNet::Buffer::DeserializeUInt_16()
{
	if (m_Index - sizeof(uint16_t) >= 0) {
		uint16_t value;
		memcpy(&value, &m_Buffer[m_Index - sizeof(uint16_t)], sizeof(uint16_t));
		m_Index -= sizeof(uint16_t);
		return value;
	}
	else {
		// Handle buffer underflow error
		return 0; // You might want to define error handling here
	}
}

const char* TwoNet::Buffer::GetData()
{
	return m_Buffer.data();
}

void TwoNet::Buffer::EnsureCapacity(size_t size)
{
	if (m_Index + size > m_Buffer.size())
		m_Buffer.resize(m_Index + size);
}

unsigned int TwoNet::Buffer::GetSize()
{
	return m_Index;
}

void TwoNet::Buffer::Clear()
{
	m_Index = 0;
	m_Buffer.clear();
}
