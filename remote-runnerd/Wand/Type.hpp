//
//  Type.hpp
//  Ace
//
//  Created by Daniil A Megrabyan on 25.08.15.
//  Copyright (c) 2015 Cadabra Systems. All rights reserved.
//

#ifndef Wand_Type_hpp
#define Wand_Type_hpp

#include <memory>

namespace wand {
	template<typename T>
	class type
	{
	/** @name Aliases */
	/** @{ */
	public:

	/** @} */
	
	/** @name Overloads */
	/** @{ */
	public:
		std::uint16_t operator()(const std::shared_ptr<const T> value) const
		{
			return value->geType();
		}
	/** @} */
	};
}

#endif
