#pragma once

#include <string>
#include <vector>
#include <stdarg.h> //va list

#include "Graphics\Frame.h"

enum LOG_LEVEL{
    logINFO,
    logWARNING,
    logERROR,
    logCRITICAL
};

class Log {
private:
	struct LogNode {
		LOG_LEVEL level;
		std::string msg;
	};

	static std::vector<LogNode> log;
        static std::string Format(std::string str, va_list argv);
public:
        static void Info(std::string msg, ...);
        static void Warn(std::string msg, ...);
        static void Error(std::string msg, ...);
        static void Critical(std::string msg, ...);
        
	static void Display(Frame* console, LOG_LEVEL lvl = logINFO, int xOffset = 0, int yOffset = 0);
	static void ToFile(std::string file, LOG_LEVEL lvl = logINFO);
};