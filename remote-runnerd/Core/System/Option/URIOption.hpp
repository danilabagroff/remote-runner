/**
 @file URIOption.hpp
 @date 26.06.15

 @author Daniil A Megrabyan
 */

#ifndef DrWeb_RemoteRunner_Core_System_Option_URIOption_hpp
#define DrWeb_RemoteRunner_Core_System_Option_URIOption_hpp

#include "../AbstractOption.hpp"

#include "../../../Wand/URI.hpp"

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace System {
	class URIOption : public AbstractOption
	{
	/** @name Constructors */
	/** @{ */
	public:
		URIOption(const std::string uri = "");
		URIOption(const wand::uri& uri);
		virtual ~URIOption() = default;
	/** @} */
		
	/** @name Factories */
	/** @{ */
	public:
	/** @} */
		
	/** @name Procedures  */
	/** @{ */
	public:
		virtual bool operator()(std::istream& stream) override;
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		wand::uri _uri;
	/** @} */
		
	/** @name Setters */
	/** @{ */
	public:
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
		const wand::uri& get() const;
		
		const std::string& getScheme() const;
		const std::string& getHost() const;
		const unsigned short& getPort() const;
		const std::string& getUsername() const;
		const std::string& getPassword() const;
		const std::string& getPath() const;
		const std::string& getQuery() const;
	/** @} */
		
	/** @name Formatters */
	/** @{ */
	public:
	/** @} */
		
	/** @name States */
	/** @{ */
	public:
		const bool hasPort() const;
	/** @} */
	};
} } } }

#endif
