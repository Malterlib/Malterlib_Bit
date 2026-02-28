// Copyright © 2026 Unborken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NPrivate
{
	consteval smint fg_GetHighestBitSetStatic(auto _CurrentNumber) noexcept
	{
		if constexpr (NMib::NTraits::cIsEnum<decltype(_CurrentNumber)>)
			return fg_GetHighestBitSetStatic(NTraits::TCEnumUnderlyingType<decltype(_CurrentNumber)>(_CurrentNumber));
		else
		{
			if (_CurrentNumber == decltype(_CurrentNumber)(0))
				return -1;
			return 1 + fg_GetHighestBitSetStatic(decltype(_CurrentNumber)(_CurrentNumber >> 1));
		}
	}

	inline constexpr int8 gc_HighestBitSetTable256[]
		{
			-1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
			4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
			5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
			5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
			6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
			6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
			6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
			6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
			7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
			7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
			7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
			7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
			7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
			7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
			7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
			7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		}
	;

	template <typename tf_CInt>
	constexpr inline_small int32 fg_GetHighestBitSetGeneric(tf_CInt _Number) noexcept
	{
		using CUnsigned = NMib::NTraits::TCUnsigned<tf_CInt>;
		constexpr int c_Shift = sizeof(tf_CInt) == 1 ? 0 : 8;

		CUnsigned Number = _Number;
		CUnsigned CurrentCheck = CUnsigned(0xff) << ((sizeof(CUnsigned) - 1)) * 8;

		for (aint i = aint(sizeof(CUnsigned)) - 1; i >= 0; --i, CurrentCheck >>= c_Shift)
		{
			CUnsigned Current = Number & CurrentCheck;
			if (Current != 0)
				return i * 8 + gc_HighestBitSetTable256[mint((Number & CurrentCheck) >> i * 8)];
		}

		return -1;
	}

	template <typename t_CInt, bool t_bSupportZero>
	struct TCGetHighestBitSet
	{
		constexpr static bool mc_bHasIntrinsic = false;
	};

#ifdef DMibPGetHighestBitSet32
	template <>
	struct TCGetHighestBitSet<uint32, true>
	{
		constexpr static inline_small int32 fs_GetHighestBitSet(uint32 _Number) noexcept
		{
			return DMibPGetHighestBitSet32(_Number);
		}

		constexpr static bool mc_bHasIntrinsic = true;
	};
#endif

#ifdef DMibPGetHighestBitSet32NoZero
	template <>
	struct TCGetHighestBitSet<uint32, false>
	{
		constexpr static inline_small int32 fs_GetHighestBitSet(uint32 _Number) noexcept
		{
			return DMibPGetHighestBitSet32NoZero(_Number);
		}

		constexpr static bool mc_bHasIntrinsic = true;
	};
#endif

#ifdef DMibPGetHighestBitSet64
	template <>
	struct TCGetHighestBitSet<uint64, true>
	{
		constexpr static inline_small int32 fs_GetHighestBitSet(uint64 _Number) noexcept
		{
			return DMibPGetHighestBitSet64(_Number);
		}

		constexpr static bool mc_bHasIntrinsic = true;
	};
#endif

#ifdef DMibPGetHighestBitSet64NoZero
	template <>
	struct TCGetHighestBitSet<uint64, false>
	{
		constexpr static inline_small int32 fs_GetHighestBitSet(uint64 _Number) noexcept
		{
			return DMibPGetHighestBitSet64NoZero(_Number);
		}

		constexpr static bool mc_bHasIntrinsic = true;
	};
#endif

	template <typename t_CInt, bool t_bSupportZero>
	constexpr bool gc_bHasHighestBitSetIntrinsic = TCGetHighestBitSet<t_CInt, t_bSupportZero>::mc_bHasIntrinsic || (!t_bSupportZero && TCGetHighestBitSet<t_CInt, true>::mc_bHasIntrinsic);

	template <typename tf_CInt, bool tf_bSupportZero>
	constexpr inline_small int32 fg_CallHighestBitSetIntrinsic(tf_CInt _Number) noexcept
	{
		if constexpr (TCGetHighestBitSet<tf_CInt, tf_bSupportZero>::mc_bHasIntrinsic)
			return TCGetHighestBitSet<tf_CInt, tf_bSupportZero>::fs_GetHighestBitSet(_Number);
		else
			return TCGetHighestBitSet<tf_CInt, true>::fs_GetHighestBitSet(_Number);
	}

	template <typename tf_CInt, bool tf_bSupportZero>
	constexpr inline_small int32 fg_GetHighestBitSetDispatch(tf_CInt const &_Number) noexcept
	{
		using CUnsigned = NMib::NTraits::TCUnsigned<tf_CInt>;

		if constexpr (gc_bHasHighestBitSetIntrinsic<CUnsigned, tf_bSupportZero>)
			return fg_CallHighestBitSetIntrinsic<CUnsigned, tf_bSupportZero>(CUnsigned(_Number));
		else if constexpr (sizeof(tf_CInt) <= 4 && gc_bHasHighestBitSetIntrinsic<uint32, tf_bSupportZero>)
			return fg_CallHighestBitSetIntrinsic<uint32, tf_bSupportZero>(uint32(CUnsigned(_Number)));
		else if constexpr (sizeof(tf_CInt) > 4 && sizeof(tf_CInt) <= 8 && gc_bHasHighestBitSetIntrinsic<uint64, tf_bSupportZero>)
			return fg_CallHighestBitSetIntrinsic<uint64, tf_bSupportZero>(uint64(CUnsigned(_Number)));
		else if constexpr (NMib::NTraits::cIsSame<NMib::NTraits::TCSmallerType<tf_CInt>, tf_CInt>)
			return fg_GetHighestBitSetGeneric(_Number);
		else
		{
			constexpr mint c_ToShift = sizeof(_Number) * 4;
			decltype(auto) Upper = fg_GetUpper(_Number);
			using CUpper = NMib::NTraits::TCRemoveReference<decltype(Upper)>;

			if constexpr (NMib::NTraits::cIsFundamental<CUpper>)
			{
				if (Upper)
				{
					if constexpr (tf_bSupportZero)
						return c_ToShift + fg_GetHighestBitSet(Upper);
					else
						return c_ToShift + fg_GetHighestBitSetNoZero(Upper);
				}
			}
			else
			{
				int32 Ret = fg_GetHighestBitSet(Upper);
				if (Ret >= 0)
					return c_ToShift + Ret;
			}

			decltype(auto) Lower = fg_GetLower(_Number);
			if constexpr (tf_bSupportZero)
				return fg_GetHighestBitSet(Lower);
			else
				return fg_GetHighestBitSetNoZero(Lower);
		}
	}
}

namespace NMib
{
	template <typename tf_CInt>
	constexpr int32 fg_GetHighestBitSet(tf_CInt const &_Number) noexcept
	{
		return NPrivate::fg_GetHighestBitSetDispatch<tf_CInt, true>(_Number);
	}

	template <typename tf_CInt>
	constexpr int32 fg_GetHighestBitSetNoZero(tf_CInt const &_Number) noexcept
	{
		return NPrivate::fg_GetHighestBitSetDispatch<tf_CInt, false>(_Number);
	}
}
