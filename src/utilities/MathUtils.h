#pragma once
#include <algorithm>
#include <cstdlib>

namespace utils {
	namespace math {

		/**
		 * @brief Rounds value to the nearest integer (7.5 => 8, -7.5 => 7)
		 */
		inline int gRound(double d)
		{
			return d >= 0.0 ? int(d + 0.5) : int(d - double(int(d - 1)) + 0.5) + int(d - 1);
		}

		/**
		 * @brief Rounds value to the nearest integer (7.5 => 8, -7.5 => 7)
		 */
		inline int gRound(float d)
		{
			return d >= 0.0f ? int(d + 0.5f) : int(d - float(int(d - 1)) + 0.5f) + int(d - 1);
		}

		/**
		 * @brief Compares the floating point value p1 and p2 and returns true if they are considered equal, otherwise false. The two numbers are compared in a relative way, where the exactness is stronger the smaller the numbers are.
		 * @return true if p1 is equal to p2, otherwise false
		 */
		inline bool gFuzzyCompare(double p1, double p2)
		{
			return (std::abs(p1 - p2) * 1000000000000. <= std::min(std::abs(p1), std::abs(p2)));
		}

		/**
		 * @brief Compares the floating point value p1 and p2 and returns true if they are considered equal, otherwise false. The two numbers are compared in a relative way, where the exactness is stronger the smaller the numbers are.
		 * @return true if p1 is equal to p2, otherwise false
		 */
		inline bool gFuzzyCompare(float p1, float p2)
		{
			return (std::abs(p1 - p2) * 100000.f <= std::min(std::abs(p1), std::abs(p2)));
		}

		inline bool gFuzzyIsNull(float f)
		{
			return std::abs(f) <= 0.00001f;
		}

		inline bool gFuzzyIsNull(double d)
		{
			return std::abs(d) <= 0.000000000001;
		}

		inline bool gIsNull(double d)
		{
			union U {
				double d;
				unsigned long long u;
			};

			U val;
			val.d = d;
			return (val.u & 0x7fffffffffffffffULL) == 0;
		}

		inline bool gIsNull(float f)
		{
			union U {
				float f;
				unsigned int u;
			};

			U val;
			val.f = f;
			return (val.u & 0x7fffffff) == 0;
		}

	} // namespace math
} // namespace utils
