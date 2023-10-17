#pragma once

namespace TwoNet {
	class Utils {
	public:
		enum class Response {
			FAILED = 0,
			SUCCESS = 1
		};

		static std::string ResponseToString(Response response) {
			return std::to_string((int)response);
		}
	};
}