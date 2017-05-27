/**
 @file AbstractVersion.hpp
 @date 2014-01-01
 
 @author Daniil A Megrabyan <daniil@megrabyan.pro>
*/

#ifndef DrWeb_RemoteRunner_Core_System_AbstractVersion_hpp
#define DrWeb_RemoteRunner_Core_System_AbstractVersion_hpp

#include "../CXML/AbstractNode.hpp"

#include <string>
#include <cstdint>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace System {
	class AbstractVersion
	{
	/** @name Constructors */
	/** @{ */
	public:
		AbstractVersion(const std::string name, const std::uint8_t major, const std::uint8_t minor, const std::uint8_t build, const std::uint8_t revision);
		AbstractVersion(const std::string name, const std::uint32_t serial);
		virtual ~AbstractVersion() = default;
	/** @} */
		
	/** @name Properties */
	/** @{ */
	public:
		bool operator==(const AbstractVersion& origin) const;
	/** @} */
		
	/** @name Properties */
	/** @{ */
	private:
		const std::string _name;

		const std::uint8_t _major;
		const std::uint8_t _minor;
		const std::uint8_t _build;
		const std::uint8_t _revision;
	/** @} */

	/** @name Properties */
	/** @{ */
	public:
		void feed(std::shared_ptr<CXML::AbstractNode> node) const;
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
		const std::string& getName() const;
		std::string getDescription(bool with_prefix = false, bool with_version = true, bool with_revision = true) const;
		const std::uint32_t getSerial() const;
	/** @} */
		
	/** @name States */
	/** @{ */
	public:
		bool isEqual(const std::uint8_t major, const std::uint8_t minor, const std::uint8_t build, const std::uint8_t revision) const;
	/** @} */
	};
} } } }

#endif
