#include "tpch.h"
#include "Serialization/Serialization.h"

namespace TwoNet {

    /*#define EndOfStringSymbol '\0'

    const void* Serialization::SerializeStringVector(const std::vector<std::string>& stringVec)
    {
        size_t dataLength = 0;

        for (const std::string& str : stringVec) {
            dataLength += str.size() + 1;
        }

        char* serializedData = new char[dataLength];
        char* currentPos = serializedData;

        for (const std::string& str : stringVec) {
            std::strcpy(currentPos, str.c_str());
            currentPos += str.size();
            *currentPos = EndOfStringSymbol;
            currentPos++;
        }

        return static_cast<const void*>(serializedData);
    }

    std::vector<std::string> Serialization::DeserializeStringVector(const void* data, size_t dataLength)
    {
        std::vector<std::string> strings; 
        const char* serializedData = static_cast<const char*>(data); 

        size_t currentPosition = 0; 

        while (currentPosition < dataLength) { 
            const char* start = serializedData + currentPosition; 
            const char* end = std::strchr(start, '\0'); 

            if (end != nullptr) {
                size_t length = end - start;
                strings.emplace_back(start, length); 
                currentPosition += (length + 1); 
            }
            else {
                break;
            }
        }

        return strings;
    }*/
}
