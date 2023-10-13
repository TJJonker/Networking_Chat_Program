#pragma once
#include "TwoNet/tpch.h"

namespace TwoNet {

	class Buffer
	{
	private:
		std::vector<char> m_Buffer;
		size_t m_WriteIndex;
		size_t m_ReadIndex;

	public:
		Buffer(size_t intialSize = 1024);
		~Buffer();

		void SerializeUInt_32(uint32_t value);
		uint32_t DeserializeUInt_32();

		void SerializeUInt_16(uint16_t value);
		uint32_t DeserializeUInt_16();

		void SerializeString(const std::string& message);
		std::string DeserializeString(size_t stringLength);

		const char* GetData();
		void EnsureCapacity(size_t value);

		size_t GetSize();
		void Clear();
	};
}

