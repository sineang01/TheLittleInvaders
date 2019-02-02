#pragma once

//namespace utils {
	namespace containers {

		/**
		 * @brief Push back to container unique element
		 * @return true if item added, false overwise
		 */
		template <class Container, class Value>
		inline bool gPushBackUnique(Container& container, const Value &value)
		{
			if (std::find(container.begin(), container.end(), value) == container.end())
			{
				container.push_back(value);
				return true;
			}

			return false;
		}

		/**
		 * @brief Find element in container.
		 * @return true if item found
		 */
		template <class Container, class Value>
		inline bool gFind(Container& container, const Value &value)
		{
			return std::find(container.begin(), container.end(), value) != container.end();
		}

		/**
		 * @brief Find and replace element from container.
		 * @return true if item was find and replaced with the new one, false if item not found
		 */
		template <class Container, class Value>
		inline bool gFindAndReplace(Container& container, const Value &value, const Value &replace)
		{
			typename Container::iterator it = std::find(container.begin(), container.end(), value);
			if (it != container.end())
			{
				*it = replace;
				return true;
			}

			return false;
		}

		/**
		 * @brief Find and erase element from container.
		 * @return true if item was find and erased, false if item not found
		 */
		template <class Container, class Value>
		inline bool gFindAndErase(Container& container, const Value &value)
		{
			typename Container::iterator it = std::find(container.begin(), container.end(), value);
			if (it != container.end())
			{
				container.erase(it);
				return true;
			}

			return false;
		}

		/**
		 * @brief Find and erase all elements matching value from container. Assume that this will invalidate any exiting iterators
		 */
		template <class Container>
		inline void gFindAndEraseAll(Container& container, const typename Container::value_type&value)
		{
			typename Container::iterator endIter(container.end());
			typename Container::iterator newEndIter(std::remove(container.begin(), endIter, value));
			container.erase(newEndIter, endIter);
		}


	} // namespace containers
//} // namespace utils
