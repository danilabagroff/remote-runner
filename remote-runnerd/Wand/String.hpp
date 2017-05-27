/**
 @file String.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#ifndef Wand_String_hpp
#define Wand_String_hpp

#include <algorithm>
#include <string>
#include <vector>
#include <iterator>
#include <functional>
#include <regex>

namespace wand {
	/// @brief std::list<string> v = explode<std::list, std::string>("Hello, there; Ace", ";,");
	template<template<class, class> class C, class T>
	static C<T, std::allocator<T>> explode(const T& str, const T& delimiter)
	{
		C<T, std::allocator<T>> retval;
		
		typename T::size_type start = 0;
		auto pos = str.find_first_of(delimiter, start);
		while (pos != T::npos) {
			if(pos != start) {
				retval.emplace_back(str, start, pos - start);
			}

			start = pos + 1;
			pos = str.find_first_of(delimiter, start);
		}


		if (start < str.length()) {
			retval.emplace_back(str, start, str.length() - start);
		}
		
		return std::move(retval);
	}

	/// @attention (danilabagroff) Не уверен, что нужно мордавать источник
	static inline std::string &ltrim(std::string& s)
	{
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
		
		return s;
	}

	/// @attention (danilabagroff) Не уверен, что нужно мордавать источник
	static inline std::string &rtrim(std::string& s)
	{
		s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
		
		return s;
	}

	static inline std::string &trim(std::string& s)
	{
		return ltrim(rtrim(s));
	}

	static inline std::string slice_tail(std::string& subject, std::string delimiter, bool keep_delimeter = false)
	{
		// Chops off the delimiter and everything that follows (destructively)
		// returns everything after the delimiter
		auto delimiter_location = subject.find(delimiter);
		auto delimiter_length = delimiter.length();
		std::string output = "";
		
		if (delimiter_location < std::string::npos) {
			auto start = keep_delimeter ? delimiter_location : delimiter_location + delimiter_length;
			auto end = subject.length() - start;
			output = subject.substr(start, end);
			subject = subject.substr(0, delimiter_location);
		}
		
		return output;
	}
	
	static inline std::string slice_head(std::string& subject, std::string delimiter)
	{
		// Chops off the delimiter and everything that precedes (destructively)
		// returns everthing before the delimeter
		auto delimiter_location = subject.find(delimiter);
		auto delimiter_length = delimiter.length();
		std::string output = "";
		if (delimiter_location < std::string::npos) {
			output = subject.substr(0, delimiter_location);
			subject = subject.substr(delimiter_location + delimiter_length, subject.length() - (delimiter_location + delimiter_length));
		}
		
		return output;
	}
	
	static inline std::string string_to_lower(std::string subject)
	{
		std::transform(subject.begin(), subject.end(), subject.begin(), ::tolower);
		
		return subject;
	}
	
	static inline std::string string_to_upper(std::string subject)
	{
		std::transform(subject.begin(), subject.end(), subject.begin(), ::toupper);
		
		return subject;
	}
	
	static inline std::string sql_escape_characters(const std::string& value)
	{
		return std::regex_replace(value, std::regex("'"), "''");
	}
}
#endif
