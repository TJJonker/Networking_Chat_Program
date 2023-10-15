#include "tpch.h"
#include "Protocols/TwoProt.h"

namespace TwoNet {
	void TwoProt::SerializeData(TwoNet::Buffer& buffer, const void* data, size_t dataLength)
	{
		buffer.SerializeUInt_16(dataLength);
		buffer.SerializeData(data, dataLength);
	}

	const void* TwoProt::DeserializeData(TwoNet::Buffer& buffer)
	{
		uint16_t dataLength = buffer.DeserializeUInt_16();
		return buffer.DeserializeData(dataLength);
	}


}