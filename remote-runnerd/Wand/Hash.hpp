//
//  Hash.hpp
//  Ace
//
//  Created by Daniil A Megrabyan on 25.08.15.
//  Copyright (c) 2015 Cadabra Systems. All rights reserved.
//

#ifndef Wand_Hash_hpp
#define Wand_Hash_hpp

#include <cstdint>
#include <memory>
#include <functional>

namespace wand {
	template <typename T>
	class hash
	{
	/** @name Overloads */
	/** @{ */
	public:
		std::size_t operator()(const std::shared_ptr<const T> value) const
		{
			return std::hash<std::shared_ptr<const T>>()(value);
		};
	/** @} */
	};
}

#endif
