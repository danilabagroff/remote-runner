/**
 @file URI.hpp
 @date 04.03.16
 @author Daniil A Megrabyan
*/

#ifndef Wand_URI_hpp
#define Wand_URI_hpp

#include "String.hpp"
#include <iostream>
#include <string>
#include <cstdlib>

namespace wand {
	class uri
	{
	/** @name Constants */
	/** @{ */
	public:
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		uri(std::string in = "")
		{
			if (in.length() > 0) {
				parse(std::move(in));
			} else {
				_string = "";
				_scheme = "";
				_host = "";
				_path = "";
				_query = "";
				_password = "";
				_username = "";
				
				_port = 0;
			}
		};
		
		virtual ~uri() = default;
	/** @} */
		
	/** @name Factories */
	/** @{ */
	public:
	/** @} */
		
	/** @name Operators */
	/** @{ */
	public:
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		std::string _string;
		
		std::string _scheme;
		std::string _host;
		std::string _path;
		std::string _query;
		std::string _username;
		std::string _password;

		unsigned short _port;
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
		const std::string parse(std::string in)
		{
			_string = in;
			
			_scheme = wand::slice_head(in, "://");
			_query = wand::slice_tail(in, "?", false);
			_path = wand::slice_tail(in, "/", false);
			
			std::string credentials = wand::slice_head(in, "@");
			_password = wand::slice_tail(credentials, ":");
			_username = credentials;
			
			_port = std::atoi(wand::slice_tail(in, ":").c_str());
			_host = in;
			
			return in;
		};
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
		const std::string& getString() const
		{
			return _string;
		};
		
		const std::string& getScheme() const
		{
			return _scheme;
		};
		
		const std::string& getHost() const
		{
			return _host;
		};
		
		const std::string& getPath() const
		{
			return _path;
		};
		
		const std::string& getQuery() const
		{
			return _query;
		};
		
		const std::string& getUsername() const
		{
			return _username;
		};
		
		const std::string& getPassword() const
		{
			return _password;
		};
		
		const unsigned short& getPort() const
		{
			return _port;
		};
	/** @} */
		
	/** @name Operators */
	/** @{ */
	public:
	/** @} */
	};
}

#endif
