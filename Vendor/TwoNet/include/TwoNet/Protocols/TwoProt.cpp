#include "tpch.h"
#include "TwoProt.h"

namespace TwoNet {
	TwoProt::TwoProt(Buffer& buffer)
		: m_Buffer(buffer) { }

	void TwoProt::SerializeMessage(const std::string& message)
	{
		uint16_t messageLength = static_cast<uint16_t>(message.size());
		m_Buffer.SerializeUInt_16(messageLength);
		m_Buffer.SerializeString(message);
	}

	std::string TwoProt::DeserializeMessage()
	{
		uint16_t messageLength = m_Buffer.DeserializeUInt_16();
		return m_Buffer.DeserializeString(messageLength);
	}


}