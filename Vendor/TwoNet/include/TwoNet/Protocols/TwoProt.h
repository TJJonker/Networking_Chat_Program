#pragma once

namespace TwoNet {
	class TwoProt {

	public:
		static void SerializeData(TwoNet::Buffer& buffer, const void* data, size_t dataSize);
		static const void* DeserializeData(TwoNet::Buffer& buffer);
	};
}