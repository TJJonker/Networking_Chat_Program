#include "pch.h"
#include "TwoNet/Buffer.h"

int main() {
	TwoNet::Buffer buffer;

	uint32_t value = 9002;
	buffer.SerializeUInt_32(value);

	uint32_t result = buffer.DeserializeUInt_32();
}