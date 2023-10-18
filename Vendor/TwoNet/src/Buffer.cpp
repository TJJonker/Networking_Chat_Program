#include "tpch.h"
#include "Buffer/Buffer.h"
#include <iostream>

namespace TwoNet {

	Buffer::Buffer(size_t intialSize)
		: m_WriteIndex(0), m_ReadIndex(0)
	{
		m_Buffer.resize(intialSize);
	}

	Buffer::~Buffer() { }

	void Buffer::SerializeUInt_32(uint32_t value)
	{
		EnsureCapacity(sizeof(uint32_t));
		m_Buffer[m_WriteIndex++] = value >> 24;
		m_Buffer[m_WriteIndex++] = value >> 16;
		m_Buffer[m_WriteIndex++] = value >> 8;
		m_Buffer[m_WriteIndex++] = value; 
	}

	uint32_t Buffer::DeserializeUInt_32()
	{
		if (m_ReadIndex + sizeof(uint32_t) > m_Buffer.size())
			return 0;

		uint32_t value = 0;;

		value |= m_Buffer[m_ReadIndex++] << 24;
		value |= m_Buffer[m_ReadIndex++] << 16;
		value |= m_Buffer[m_ReadIndex++] << 8;
		value |= m_Buffer[m_ReadIndex++];

		return value;
	}

	void Buffer::SerializeUInt_16(uint16_t value)
	{
		EnsureCapacity(sizeof(uint16_t));
		m_Buffer[m_WriteIndex++] = value >> 8; 
		m_Buffer[m_WriteIndex++] = value; 
	}

	uint32_t Buffer::DeserializeUInt_16()
	{
		if (m_ReadIndex + sizeof(uint16_t) > m_Buffer.size())
			return 0;

		uint32_t value = 0;;

		value |= m_Buffer[m_ReadIndex++] << 8;
		value |= m_Buffer[m_ReadIndex++]; 

		return value;
	}

	void Buffer::SerializeData(const char* data, size_t dataSize)
	{
		EnsureCapacity(dataSize);
		memcpy(&m_Buffer[m_WriteIndex], data, dataSize);
		data += '\0';
		m_WriteIndex += dataSize + 1;
	}

	const char* Buffer::DeserializeData(size_t dataSize)
	{
		if (m_ReadIndex + dataSize <= m_Buffer.size()) {
			const char* data = &m_Buffer[m_ReadIndex];
			m_ReadIndex += dataSize + 1;
			return data;
		}
		return nullptr;
	}

	const char* Buffer::GetBufferData()
	{
		return m_Buffer.data();
	}

	void Buffer::WriteBuffer(const void* data, size_t dataSize)
	{
		EnsureCapacity(dataSize);
		memcpy(&m_Buffer[m_WriteIndex], data, dataSize);
		m_WriteIndex += dataSize;
	}

	void Buffer::EnsureCapacity(size_t size)
	{
		if (m_WriteIndex + size > m_Buffer.size())
			m_Buffer.resize(m_WriteIndex + size);
	}

	size_t Buffer::GetSize()
	{
		return m_WriteIndex;
	}

	void Buffer::Clear()
	{
		for (int i = 0; i < m_WriteIndex; i++) {
			m_Buffer[i] = '\0';
		}
		
		m_WriteIndex = 0;
		m_ReadIndex = 0;
	}
}