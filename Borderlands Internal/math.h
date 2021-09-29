#pragma once

namespace Math
{
	template <typename T>
	static T Clamp(T Val, T Min, T Max)
	{
		if (Val > Min && Max > Val)
		{
			return Val;
		}
		if (Min > Val)
			return Min;

		return Max;
	}
}