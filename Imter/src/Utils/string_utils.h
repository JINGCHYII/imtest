#pragma once
#pragma execution_character_set("utf-8")

#include <string>
#include <cstdio>
#include <vector>
#include <regex>
#include <stdexcept>
#include <stdio.h>

#include <string>

wchar_t* MBCS2Unicode(wchar_t * buff, const char * str);
char * Unicode2MBCS(char * buff, const wchar_t * str);
std::wstring str2wstr(std::string str);


namespace std {
	/*
	 * 简单模拟java.ang.String.format输出
	 * 除算术类型(int,long,float等)之外只支持std::string输出
	 * */
	class string_utils
	{
		// 普通类型直接返回值
		template<typename T>
		static T cvalue(T&& v) {
			return std::forward<T>(v);
		}
		// std::string类型返回c-string指针
		static const char* cvalue(std::string& v) {
			return v.c_str();
		}

		// 递归结束
		static int snprintf(char *__stream, size_t __n, const std::string &__format) {
			if (__n <= 0)return 0;
			// 正则表达式用于获取第一个格式化参数的%控制
			static std::regex fmt_first("^[\\s\\S]*?%[-+ #0]?(\\d+|\\*)?(\\.(?:\\d+|\\*))?(?:hh|h|l|ll|j|z|t|L)?[diuoxXfFeEgGaAcspn]");
			if (std::regex_match(__format, fmt_first)) {
				// 实际参数数目与格式化字符串不匹配抛出异常
				throw std::logic_error("invalid format string:missing argument");
			}
			// 调用标准snprintf输出
			return std::snprintf(__stream, __n, __format.c_str());
		}
		template<typename ARG1, typename ...Args>
		static int snprintf(char *__stream, size_t __n, const std::string &__format, ARG1&& first, Args&&...args) {
			if (__n <= 0)return 0;
			// 正则表达式用于获取第一个格式化参数的%控制
			static std::regex fmt_first("^(?:[^%]|%%)*%[-+ #0]?(\\d+|\\*)?(\\.(?:\\d+|\\*))?(?:hh|h|l|ll|j|z|t|L)?[diuoxXfFeEgGaAcspn]");
			std::smatch m;
			if (!std::regex_search(__format, m, fmt_first)) {
				// 没有找到%格式控制字符串则抛出异常
//                std::cerr<<"extra argument provied to printf\n__format:"<<__format<<std::endl;
				throw std::logic_error("extra argument provied to printf");
			}
			// 调用标准snprintf函数输出第一个参数
			int num = std::snprintf(__stream, __n, m[0].str().c_str(), cvalue(std::forward<ARG1>(first)));
			// 递归调用处理剩余的参数,调整缓冲指针和长度
			return num + snprintf(__stream + num, size_t(__n - num), m.suffix().str(), std::forward<Args>(args)...);
		}
	public:
		// 类printf格式化输出字符串
		template<typename ...Args>
		static std::string format(const std::string &__format, Args&&...args) {
			std::vector<char> buffer(size_t(1024));
			int num = std::snprintf(buffer.data(), size_t(1024), __format.c_str(), std::forward<Args>(args)...);
			return std::string(buffer.data(), buffer.data() + num);
		}

		//        template<typename ... Args>
		//        string string_format(const string& format, Args ... args){
		//            size_t size = 1 + snprintf(nullptr, 0, format.c_str(), args ...);  // Extra space for \0
		//            // unique_ptr<char[]> buf(new char[size]);
		//            char bytes[size];
		//            snprintf(bytes, size, format.c_str(), args ...);
		//            return string(bytes);
		//        }
	};
}