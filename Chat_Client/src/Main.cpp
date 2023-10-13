#include "pch.h"
#include <TwoNet/Buffer/Buffer.h>
#include <TwoNet/Protocols/TwoProt.h>

int main() {
	TwoNet::Buffer buffer;
	TwoNet::TwoProt protocol(buffer);

	std::string message = "Hallo wereld!";
	protocol.SerializeMessage(message);

	std::string result = protocol.DeserializeMessage();

	//TwoNet::Buffer buffer;

	//uint32_t value = 9002;
	//uint16_t value2 = 1091;

	//buffer.SerializeUInt_32(value);
	//buffer.SerializeUInt_16(value2);

	//uint32_t result = buffer.DeserializeUInt_32();
	//uint32_t result2 = buffer.DeserializeUInt_16(); 
}