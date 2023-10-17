#pragma once

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

		void SerializeData(const char* data, size_t dataSize);
		const char* DeserializeData(size_t dataSize);

		const char* GetBufferData();
		void WriteBuffer(const void* data, size_t dataSize);
		void EnsureCapacity(size_t value);

		size_t GetSize();
		size_t GetBufferSize() { return m_Buffer.size(); }
		void Clear();
	};
}

