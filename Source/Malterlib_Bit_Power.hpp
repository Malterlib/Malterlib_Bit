// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NPrivate
{
	consteval auto fg_Power(auto _Number, umint _Power) noexcept
	{
		auto Result = decltype(_Number)(1);
		for (umint i = 0; i < _Power; ++i)
			Result *= _Number;
		return Result;
	}

	template <typename t_CInt>
	constexpr inline_small t_CInt fg_FillBitsBelow(t_CInt _Number) noexcept
	{
		for (int Shift = 1; Shift < int(sizeof(t_CInt) * 8); Shift *= 2)
			_Number = _Number | (_Number >> Shift);
		return _Number;
	}
}

namespace NMib
{
	template <typename tf_CValue>
	constexpr bool fg_IsPowerOfTwo(tf_CValue _Value) noexcept
	{
		return _Value > 0 && (_Value & (_Value - 1)) == 0;
	}

	template <typename tf_CInt>
	constexpr inline_small tf_CInt fg_RoundPowerOfTwoUp(tf_CInt _Number) noexcept
	{
		using CUnsigned = NTraits::TCUnsigned<tf_CInt>;
		CUnsigned Number = CUnsigned(_Number);
		--Number;
		Number = NPrivate::fg_FillBitsBelow(Number);
		++Number;
		return tf_CInt(Number);
	}

	template <typename tf_CInt>
	constexpr inline_small tf_CInt fg_RoundPowerOfTwoDown(tf_CInt _Number) noexcept
	{
		using CUnsigned = NTraits::TCUnsigned<tf_CInt>;
		CUnsigned Number = CUnsigned(_Number);
		Number = NPrivate::fg_FillBitsBelow(Number);
		Number = Number - (Number >> 1);
		return tf_CInt(Number);
	}

	// use:  _ML = fg_MinPowerOfTwo(_Value)
	// post: _ML is the position of the highest set bit in _Value, or 0 if _Value <= 1
	template <typename tf_CValue>
	constexpr tf_CValue fg_MinPowerOfTwo(tf_CValue _Value) noexcept
	{
		if (_Value <= 1)
			return 0;

		return tf_CValue(fg_GetHighestBitSetNoZero(_Value));
	}
}
