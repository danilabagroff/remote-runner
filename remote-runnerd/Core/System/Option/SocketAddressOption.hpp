/**
 @file SocketAddressOption.hpp
 @date 15.06.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_System_Option_SocketAddressOption_hpp
#define DrWeb_RemoteRunner_Core_System_Option_SocketAddressOption_hpp

#include "URIOption.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace System {
	class SocketAddressOption : public URIOption
	{
	/** @name Classes */
	/** @{ */
	public:
		enum class SocketFamily
		{
			Unknown,
			TCP,
			Unix
		};
	/** @} */
		
	/** @name Constructors */
	/** @{ */
	public:
		SocketAddressOption(const std::string& host, unsigned short port);
		SocketAddressOption(const std::string& socket_file);
		SocketAddressOption(const wand::uri& uri);
		virtual ~SocketAddressOption() = default;
	/** @} */
		
	/** @name Factories */
	/** @{ */
	public:
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
		virtual bool operator()(std::istream& stream) override;
		bool parse();
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		SocketAddressOption::SocketFamily _family;
	/** @} */
	
	/** @name Setters */
	/** @{ */
	public:
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
		const SocketAddressOption::SocketFamily getFamily() const;
	/** @} */
		
	/** @name Formatters */
	/** @{ */
	public:
	/** @} */
		
	/** @name States */
	/** @{ */
	public:
		bool isTCP() const;
		bool isUnix() const;
	/** @} */
	};
} } } }

#endif
