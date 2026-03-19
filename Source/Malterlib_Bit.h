// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Bit_Defines.hpp"

namespace NMib
{
	constexpr NPrivate::CBitAutoConvert fg_Bit(umint _Bit) noexcept;
	template <typename tf_CType>
	constexpr tf_CType fg_Bit(umint _Bit, tf_CType _One) noexcept;

	constexpr NPrivate::CBitRangeAutoConvert fg_BitRange(umint _BitStart, umint _BitEnd) noexcept;
	template <typename tf_CType>
	constexpr tf_CType fg_BitRange(uaint _BitStart, uaint _BitEnd) noexcept;


	template <typename tf_CInt>
	constexpr int32 fg_GetLowestBitSet(tf_CInt const &_Number) noexcept;

	template <typename tf_CInt>
	constexpr int32 fg_GetLowestBitSetNoZero(tf_CInt const &_Number) noexcept;

	template <auto t_CurrentNumber>
	constexpr inline umint gc_LowestBitSet = NPrivate::fg_GetLowestBitSetStatic(t_CurrentNumber, 0);


	template <typename tf_CInt>
	constexpr int32 fg_GetHighestBitSet(tf_CInt const &_Number) noexcept;

	template <typename tf_CInt>
	constexpr int32 fg_GetHighestBitSetNoZero(tf_CInt const &_Number) noexcept;

	template <auto t_CurrentNumber>
	constexpr inline smint gc_HighestBitSet = NPrivate::fg_GetHighestBitSetStatic(t_CurrentNumber);


	template <typename tf_CInt>
	constexpr inline_small uint32 fg_NumBitsSet(tf_CInt const &_Number) noexcept;

	template <typename t_CType>
	constexpr inline umint gc_BitSize = sizeof(t_CType) * 8;


	template <typename tf_CType>
	constexpr inline_small tf_CType fg_RotateLeft(tf_CType _Data, aint _nBits) noexcept;

	template <typename tf_CType>
	constexpr inline_small tf_CType fg_RotateRight(tf_CType _Data, aint _nBits) noexcept;

	template <auto t_CurrentNumber>
	concept cIsPowerOfTwo = t_CurrentNumber > 0 && (decltype(t_CurrentNumber)(1) << gc_HighestBitSet<t_CurrentNumber>) == t_CurrentNumber;

	template <auto t_Number, umint t_Power>
	constexpr inline auto gc_Power = NPrivate::fg_Power(t_Number, t_Power);

	template <typename tf_CValue>
	constexpr bool fg_IsPowerOfTwo(tf_CValue _Value) noexcept;

	// use:  _ML = fg_MinPowerOfTwo(_Value)
	// post: _ML is the smallest non-negative integer such that 2^_ML >= _N
	template <typename tf_CValue>
	constexpr tf_CValue fg_MinPowerOfTwo(tf_CValue _Value) noexcept;

	template <typename tf_CInt>
	constexpr inline_small tf_CInt fg_RoundPowerOfTwoUp(tf_CInt _Number) noexcept;

	template <typename tf_CInt>
	constexpr inline_small tf_CInt fg_RoundPowerOfTwoDown(tf_CInt _Number) noexcept;


	// use:  _Lsb = fg_LeastSignificantBit<tf_CValue>(_Value)
	// post: _Lsb is the lowest significant set bit of _Value, or 0 iff _Value == 0
	template <typename tf_CValue>
	constexpr tf_CValue fg_LeastSignificantBit(tf_CValue _Value) noexcept;

	// use:  _Lsb = fg_LeastSignificantBitNoZero<tf_CValue>(_Value)
	// pre:  sizeof(tf_CValue) <= 4, _Value != 0
	// post: _Lsb is the lowest significant set bit of _Value, or 0 iff _Value == 0
	template <typename tf_CValue>
	constexpr tf_CValue fg_MostSignificantBitNoZero(tf_CValue _Value) noexcept;

	// use:  _Lsb = fg_LeastSignificantBit<tf_CValue>(_Value)
	// pre:  sizeof(tf_CValue) <= 4
	// post: _Lsb is the lowest significant set bit of _Value, or 0 iff _Value == 0
	template <typename tf_CValue>
	constexpr tf_CValue fg_MostSignificantBit(tf_CValue _Value) noexcept;

	// returns mask of bits higher than sole bit _Bit
	template <typename tf_CValue>
	constexpr tf_CValue fg_HigherMask(tf_CValue _Bit) noexcept;

	// returns mask of bits higher than or equal to sole bit _Bit
	template <typename tf_CValue>
	constexpr tf_CValue fg_HigherEqMask(tf_CValue _Bit) noexcept;

	// returns mask of bits lower than or equal to sole bit _Bit
	template <typename tf_CValue>
	constexpr tf_CValue fg_LowerMask(tf_CValue _Bit) noexcept;

	// returns mask of bits lower than or equal to sole bit _Bit
	template <typename tf_CValue>
	constexpr tf_CValue fg_LowerEqMask(tf_CValue _Bit) noexcept;
}

#include "Malterlib_Bit_LowestSet.hpp"
#include "Malterlib_Bit_HighestSet.hpp"
#include "Malterlib_Bit_NumSet.hpp"
#include "Malterlib_Bit_Power.hpp"
#include "Malterlib_Bit_Range.hpp"
#include "Malterlib_Bit_Rotate.hpp"
