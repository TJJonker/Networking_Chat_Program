#pragma once
#include <TwoNet/Buffer/Buffer.h>
#include <functional>

struct Request {
	std::shared_ptr<TwoNet::Buffer> buffer;
	std::function<void(TwoNet::Buffer)> callback;
};