#include "pch.h"
#include "Utility.h"

namespace Utility
{
	[[deprecated("This function uses _popen() API which cannot be used in Windows Runtime.")]]
	std::vector<std::string> GetARPInterfaces()
	{
		const char* const command = "arp -a";
		const char* const mode    = "r";

		std::unique_ptr<FILE, decltype(&_pclose)> pFile( _popen(command,mode), _pclose );

		if (pFile == nullptr)
			throw("_popen() failed!");

		std::vector<std::string> addresses{};
		std::array<char, 128>    buffer{};
		std::regex               pattern{ "Interface: ([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3})" };

		while (fgets(buffer.data(), 128, pFile.get()) != nullptr)
		{
			const std::string& bufferStr = buffer.data();

			std::smatch matches{};
			if (std::regex_search(bufferStr, matches, pattern))
				addresses.push_back(matches[1]);

		}

		assert(!addresses.empty());
		return addresses;
	}

}