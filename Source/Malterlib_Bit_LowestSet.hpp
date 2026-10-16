// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NPrivate
{
	consteval umint fg_GetLowestBitSetStatic(auto _CurrentNumber, umint _Bit) noexcept
	{
		if (_CurrentNumber == 0)
			return -1;

		if (_CurrentNumber & 1)
			return _Bit;

		return fg_GetLowestBitSetStatic(_CurrentNumber >> 1, _Bit + 1);
	}

	inline constexpr int8 gc_LowestBitSetTable256[]
		{
			// malterlib-format columns: 16
			  -1, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
			,  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
			,  5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
			,  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
			,  6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
			,  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
			,  5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
			,  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
			,  7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
			,  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
			,  5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
			,  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
			,  6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
			,  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
			,  5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
			,  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
		}
	;

	template <typename tf_CInt>
	constexpr inline_small int32 fg_GetLowestBitSetGeneric(tf_CInt const &_Number) noexcept
	{
		using CUnsigned = NMib::NTraits::TCUnsigned<tf_CInt>;
		constexpr int c_Shift = sizeof(tf_CInt) == 1 ? 0 : 8;

		CUnsigned Number = _Number;

		for (umint i = 0; i < umint(sizeof(CUnsigned)); ++i, Number >>= c_Shift)
		{
			CUnsigned Current = Number & CUnsigned(0xff);
			if (Current != 0)
				return i * 8 + gc_LowestBitSetTable256[umint(Current)];
		}

		return -1;
	}

	template <typename t_CInt, bool t_bSupportZero>
	struct TCGetLowestBitSet
	{
		constexpr static bool mc_bHasIntrinsic = false;
	};

#ifdef DMibPGetLowestBitSet32
	template <>
	struct TCGetLowestBitSet<uint32, true>
	{
		constexpr static inline_small int32 fs_GetLowestBitSet(uint32 const &_Number) noexcept
		{
			return DMibPGetLowestBitSet32(_Number);
		}

		constexpr static bool mc_bHasIntrinsic = true;
	};
#endif

#ifdef DMibPGetLowestBitSet32NoZero
	template <>
	struct TCGetLowestBitSet<uint32, false>
	{
		constexpr static inline_small int32 fs_GetLowestBitSet(uint32 const &_Number) noexcept
		{
			return DMibPGetLowestBitSet32NoZero(_Number);
		}

		constexpr static bool mc_bHasIntrinsic = true;
	};
#endif

#ifdef DMibPGetLowestBitSet64
	template <>
	struct TCGetLowestBitSet<uint64, true>
	{
		constexpr static inline_small int32 fs_GetLowestBitSet(uint64 const &_Number) noexcept
		{
			return DMibPGetLowestBitSet64(_Number);
		}

		constexpr static bool mc_bHasIntrinsic = true;
	};
#endif

#ifdef DMibPGetLowestBitSet64NoZero
	template <>
	struct TCGetLowestBitSet<uint64, false>
	{
		constexpr static inline_small int32 fs_GetLowestBitSet(uint64 const &_Number) noexcept
		{
			return DMibPGetLowestBitSet64NoZero(_Number);
		}

		constexpr static bool mc_bHasIntrinsic = true;
	};
#endif

	template <typename t_CInt, bool t_bSupportZero>
	constexpr bool gc_bHasLowestBitSetIntrinsic = TCGetLowestBitSet<t_CInt, t_bSupportZero>::mc_bHasIntrinsic || (!t_bSupportZero && TCGetLowestBitSet<t_CInt, true>::mc_bHasIntrinsic);

	template <typename tf_CInt, bool tf_bSupportZero>
	constexpr inline_small int32 fg_CallLowestBitSetIntrinsic(tf_CInt const &_Number) noexcept
	{
		if constexpr (TCGetLowestBitSet<tf_CInt, tf_bSupportZero>::mc_bHasIntrinsic)
			return TCGetLowestBitSet<tf_CInt, tf_bSupportZero>::fs_GetLowestBitSet(_Number);
		else
			return TCGetLowestBitSet<tf_CInt, true>::fs_GetLowestBitSet(_Number);
	}

	template <typename tf_CInt, bool tf_bSupportZero>
	constexpr inline_small int32 fg_GetLowestBitSetDispatch(tf_CInt const &_Number) noexcept
	{
		using CUnsigned = NMib::NTraits::TCUnsigned<tf_CInt>;

		if constexpr (gc_bHasLowestBitSetIntrinsic<CUnsigned, tf_bSupportZero>)
			return fg_CallLowestBitSetIntrinsic<CUnsigned, tf_bSupportZero>(CUnsigned(_Number));
		else if constexpr (sizeof(tf_CInt) <= 4 && gc_bHasLowestBitSetIntrinsic<uint32, tf_bSupportZero>)
			return fg_CallLowestBitSetIntrinsic<uint32, tf_bSupportZero>(uint32(CUnsigned(_Number)));
		else if constexpr (sizeof(tf_CInt) > 4 && sizeof(tf_CInt) <= 8 && gc_bHasLowestBitSetIntrinsic<uint64, tf_bSupportZero>)
			return fg_CallLowestBitSetIntrinsic<uint64, tf_bSupportZero>(uint64(CUnsigned(_Number)));
		else if constexpr (NMib::NTraits::cIsSame<NMib::NTraits::TCSmallerType<tf_CInt>, tf_CInt>)
			return fg_GetLowestBitSetGeneric(_Number);
		else
		{
			constexpr umint c_ToShift = sizeof(_Number) * 4;
			decltype(auto) Lower = fg_GetLower(_Number);
			using CLower = NMib::NTraits::TCRemoveReference<decltype(Lower)>;

			if constexpr (NMib::NTraits::cIsFundamental<CLower>)
			{
				if (Lower)
				{
					if constexpr (tf_bSupportZero)
						return fg_GetLowestBitSet(Lower);
					else
						return fg_GetLowestBitSetNoZero(Lower);
				}
			}
			else
			{
				int32 Ret = fg_GetLowestBitSet(Lower);
				if (Ret >= 0)
					return Ret;
			}

			decltype(auto) Upper = fg_GetUpper(_Number);
			if constexpr (tf_bSupportZero)
			{
				int32 Ret = fg_GetLowestBitSet(Upper);
				if (Ret < 0)
					return -1;
				return Ret + c_ToShift;
			}
			else
				return fg_GetLowestBitSetNoZero(Upper) + c_ToShift;
		}
	}
}

namespace NMib
{
	template <typename tf_CInt>
	constexpr int32 fg_GetLowestBitSet(tf_CInt const &_Number) noexcept
	{
		return NPrivate::fg_GetLowestBitSetDispatch<tf_CInt, true>(_Number);
	}

	template <typename tf_CInt>
	constexpr int32 fg_GetLowestBitSetNoZero(tf_CInt const &_Number) noexcept
	{
		return NPrivate::fg_GetLowestBitSetDispatch<tf_CInt, false>(_Number);
	}
}
