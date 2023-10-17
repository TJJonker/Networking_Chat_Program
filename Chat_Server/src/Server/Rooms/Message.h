#pragma once
#include "pch.h"
#include <iomanip>

struct Message {

	std::string& Owner;
	std::string& Text;

	Message(std::string& owner, std::string& text)
		: Owner(owner), Text(text) { }
};