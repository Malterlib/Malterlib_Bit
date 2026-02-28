// Copyright © 2026 Unborken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib
{
	template <typename tf_CValue>
	constexpr tf_CValue fg_LeastSignificantBit(tf_CValue _Value) noexcept
	{
		return (tf_CValue)(_Value & -_Value);
	}

	template <typename tf_CValue>
	constexpr tf_CValue fg_MostSignificantBitNoZero(tf_CValue _Value) noexcept
	{
		return (tf_CValue)(1 << fg_GetHighestBitSetNoZero(_Value));
	}

	template <typename tf_CValue>
	constexpr tf_CValue fg_MostSignificantBit(tf_CValue _Value) noexcept
	{
		return (_Value == 0) ? 0 : (tf_CValue)(1 << fg_GetHighestBitSetNoZero(_Value));
	}

	template <typename tf_CValue>
	constexpr tf_CValue fg_HigherMask(tf_CValue _Bit) noexcept
	{
		return ~((_Bit << 1) - 1);
	}

	template <typename tf_CValue>
	constexpr tf_CValue fg_HigherEqMask(tf_CValue _Bit) noexcept
	{
		return ~(_Bit - 1);
	}

	template <typename tf_CValue>
	constexpr tf_CValue fg_LowerMask(tf_CValue _Bit) noexcept
	{
		return _Bit - 1;
	}

	template <typename tf_CValue>
	constexpr tf_CValue fg_LowerEqMask(tf_CValue _Bit) noexcept
	{
		return (_Bit << 1) - 1;
	}
}
