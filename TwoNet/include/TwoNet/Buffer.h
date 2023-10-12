#pragma once
#include "pch.h"

namespace TwoNet {

	class Buffer
	{
	private:
		std::vector<char> m_Buffer;
		unsigned int m_Index;

	public:
		Buffer(size_t intialSize = 1024);
		~Buffer();

		void SerializeUInt_32(uint32_t value);
		uint32_t DeserializeUInt_32();

		void SerializeUInt_16(uint16_t value);
		uint32_t DeserializeUInt_16();

		const char* GetData();
		void EnsureCapacity(size_t value);

		unsigned int GetSize();
		void Clear();
	};
}

