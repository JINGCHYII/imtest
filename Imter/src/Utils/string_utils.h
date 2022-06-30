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
	 * ��ģ��java.ang.String.format���
	 * ����������(int,long,float��)֮��ֻ֧��std::string���
	 * */
	class string_utils
	{
		// ��ͨ����ֱ�ӷ���ֵ
		template<typename T>
		static T cvalue(T&& v) {
			return std::forward<T>(v);
		}
		// std::string���ͷ���c-stringָ��
		static const char* cvalue(std::string& v) {
			return v.c_str();
		}

		// �ݹ����
		static int snprintf(char *__stream, size_t __n, const std::string &__format) {
			if (__n <= 0)return 0;
			// ������ʽ���ڻ�ȡ��һ����ʽ��������%����
			static std::regex fmt_first("^[\\s\\S]*?%[-+ #0]?(\\d+|\\*)?(\\.(?:\\d+|\\*))?(?:hh|h|l|ll|j|z|t|L)?[diuoxXfFeEgGaAcspn]");
			if (std::regex_match(__format, fmt_first)) {
				// ʵ�ʲ�����Ŀ���ʽ���ַ�����ƥ���׳��쳣
				throw std::logic_error("invalid format string:missing argument");
			}
			// ���ñ�׼snprintf���
			return std::snprintf(__stream, __n, __format.c_str());
		}
		template<typename ARG1, typename ...Args>
		static int snprintf(char *__stream, size_t __n, const std::string &__format, ARG1&& first, Args&&...args) {
			if (__n <= 0)return 0;
			// ������ʽ���ڻ�ȡ��һ����ʽ��������%����
			static std::regex fmt_first("^(?:[^%]|%%)*%[-+ #0]?(\\d+|\\*)?(\\.(?:\\d+|\\*))?(?:hh|h|l|ll|j|z|t|L)?[diuoxXfFeEgGaAcspn]");
			std::smatch m;
			if (!std::regex_search(__format, m, fmt_first)) {
				// û���ҵ�%��ʽ�����ַ������׳��쳣
//                std::cerr<<"extra argument provied to printf\n__format:"<<__format<<std::endl;
				throw std::logic_error("extra argument provied to printf");
			}
			// ���ñ�׼snprintf���������һ������
			int num = std::snprintf(__stream, __n, m[0].str().c_str(), cvalue(std::forward<ARG1>(first)));
			// �ݹ���ô���ʣ��Ĳ���,��������ָ��ͳ���
			return num + snprintf(__stream + num, size_t(__n - num), m.suffix().str(), std::forward<Args>(args)...);
		}
	public:
		// ��printf��ʽ������ַ���
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