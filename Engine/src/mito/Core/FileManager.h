#pragma once

#include "MitchondiraAPI.h"

#include <string>

namespace mito
{

	void MITO_API loadFile(const char* src, std::string* dest);
	void MITO_API loadFile(const std::string& src, std::string* dest);
	void MITO_API saveFile(const char* dest, const std::string& contents);
	void MITO_API saveFile(const std::string& dest, const std::string& contents);

}