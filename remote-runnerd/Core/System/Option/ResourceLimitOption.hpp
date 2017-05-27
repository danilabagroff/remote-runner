/**
 @file ResourceLimitOption.hpp
 @date 26.06.15

 @author Daniil A Megrabyan
*/

#ifndef DrWeb_RemoteRunner_Core_System_Option_ResourceLimitOption_hpp
#define DrWeb_RemoteRunner_Core_System_Option_ResourceLimitOption_hpp

#include "../AbstractOption.hpp"

#include <sys/resource.h>

namespace DrWeb { namespace RemoteRunner { namespace Core { namespace System {
	class ResourceLimitOption : public AbstractOption
	{
	/** @name Classes */
	/** @{ */
	public:
		enum class Type : int
		{
			NoFile = RLIMIT_NOFILE,
			NProc = RLIMIT_NPROC
		};
	/** @} */
	
	/** @name Constructors */
	/** @{ */
	public:
		ResourceLimitOption(const ResourceLimitOption::Type type);
		virtual ~ResourceLimitOption() = default;
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
		const ResourceLimitOption::Type _type;
		struct rlimit _limit;
	/** @} */
		
	/** @name Setters */
	/** @{ */
	public:
	/** @} */
		
	/** @name Getters */
	/** @{ */
	public:
		const struct rlimit& getLimit() const;
		const ResourceLimitOption::Type& getResourceType() const;
	/** @} */
		
	/** @name Formatters */
	/** @{ */
	public:
	/** @} */
	};
} } } }

#endif
