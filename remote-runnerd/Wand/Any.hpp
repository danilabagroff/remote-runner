//
//  Any.hpp
//  Abra
//
//  Created by Daniil A Megrabyan on 20.05.15.
//  Copyright (c) 2015 Cadabra Systems. All rights reserved.
//

#ifndef Wand_Any_hpp
#define Wand_Any_hpp

namespace wand {

	class any
	{
	public:
		template <typename T>
		any& operator = (T const& t)
		{
			typedef type<T> assign_type;
			object = std::auto_ptr<assign_type>(new assign_type(t));
			
			return *this;
		}
		
		template <class T>
		operator T()
		{
			typedef typename<T> assign_type;
			assign_type& type = dynamic_cast<assign_type&>(*object);
			
			return type.get();
		}
		
	private:
		class base
		{
		public:
			virtual ~base() {}
		};
		
		typedef std::auto_ptr<base> base_ptr;
		
		template <class T>
		class type : public base
		{
		public:
			
			type(T const& t)
			: object(t)
			{
			}
			
			T get() const
			{
				return object;
			}
			
		private:
			
			T object;
		};
		
		base_ptr object;
	};
}

/*
 
 struct dummy
 {
	int a;
	int b;
	int c;
 };
 
 int main()
 {
	variant v1, v2, v3, v4;
	
	v1 = 2;
	v2 = 5.0f;
	v3 = std::string("Pot of gold");
	v4 = dummy();
	
	int         i = v1;
	float       f = v2;
	std::string s = v3;
	dummy       d = v4;
	
	return 0;
 }
 */

#endif