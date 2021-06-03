#pragma once

#include <vector>

namespace msl {
	template<class Type>
	inline void fastErase(typename std::vector<Type>& container, typename std::vector<Type>::iterator it)
	{
		auto lastEl = std::end(container) - 1;
		if (it != lastEl) {
			*it = std::move(*lastEl);
		}
		container.pop_back();
	}

	template<class Type>
	inline bool isLastElement(typename std::vector<Type>& container, typename std::vector<Type>::iterator it)
	{
		if (it == std::end(container) - 1)
			return true;

		return false;
	}

}