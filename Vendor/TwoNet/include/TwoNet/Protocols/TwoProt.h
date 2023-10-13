#pragma once
#include <TwoNet/Buffer/Buffer.h>
#include "TwoNet/tpch.h"

namespace TwoNet {
	class TwoProt {

	private:
		Buffer& m_Buffer;

	public:
		TwoProt(Buffer& buffer);

		void SerializeMessage(const std::string& message);
		std::string DeserializeMessage();
	};
}