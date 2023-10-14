#include "tpch.h"
#include "Buffer/Buffer.h"

namespace TwoNet {

	Buffer::Buffer(size_t intialSize)
		: m_WriteIndex(0), m_ReadIndex(0)
	{
		m_Buffer.resize(intialSize);
	}

	Buffer::~Buffer() { }

	void Buffer::SerializeUInt_32(uint32_t value)
	{
		size_t size = sizeof(uint32_t);
		EnsureCapacity(size);
		memcpy(&m_Buffer[m_WriteIndex], &value, size);
		m_WriteIndex += size;
	}

	uint32_t Buffer::DeserializeUInt_32()
	{
		size_t size = sizeof(uint32_t);
		if (m_ReadIndex + size <= m_Buffer.size()) {
			uint32_t value;
			memcpy(&value, &m_Buffer[m_ReadIndex], size);
			m_ReadIndex += size;
			return value;
		}
		else {
			// Handle buffer underflow error
			return 0; // You might want to define error handling here
		}
	}

	void Buffer::SerializeUInt_16(uint16_t value)
	{
		size_t size = sizeof(uint16_t);
		EnsureCapacity(size);
		memcpy(&m_Buffer[m_WriteIndex], &value, size);
		m_WriteIndex += size;
	}

	uint32_t Buffer::DeserializeUInt_16()
	{
		if (m_ReadIndex + sizeof(uint16_t) <= m_Buffer.size()) {
			uint16_t value;
			memcpy(&value, &m_Buffer[m_ReadIndex], sizeof(uint16_t));
			m_ReadIndex += sizeof(uint16_t);
			return value;
		}
		else {
			// Handle buffer underflow error
			return 0; // You might want to define error handling here
		}
	}

	void Buffer::SerializeString(const std::string& message)
	{
		size_t messageSize = message.size();
		EnsureCapacity(messageSize);
		memcpy(&m_Buffer[m_WriteIndex], &message, messageSize);
		m_WriteIndex += messageSize;
	}

	std::string Buffer::DeserializeString(size_t stringLength)
	{
		if (m_ReadIndex + stringLength <= m_Buffer.size()) {
			std::string message(&m_Buffer[m_ReadIndex], stringLength);
			return message;
		}
		return "";
	}

	const char* Buffer::GetData()
	{
		return m_Buffer.data();
	}

	void Buffer::WriteBuffer(const char* data, size_t dataSize)
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
		m_WriteIndex = 0;
		m_ReadIndex = 0;
		m_Buffer.clear();
	}
}