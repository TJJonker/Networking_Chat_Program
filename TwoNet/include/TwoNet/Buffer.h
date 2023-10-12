#pragma once
#include "pch.h"

namespace TwoNet {

	class Buffer
	{
	private:
		std::vector<char> buffer;

	public:
		Buffer(size_t intialSize = 1024);
		~Buffer();
	};
}

