// Copyright © 2026 Unborken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NPrivate
{
	inline constexpr uint8 gc_NumBitsSetTable256[]
		{
			0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
			3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
			3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
			3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
			3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
			4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
		}
	;

	template <typename tf_CInt>
	constexpr inline_small uint32 fg_NumBitsSetGeneric(tf_CInt const &_Number) noexcept
	{
		using CUnsigned = NMib::NTraits::TCUnsigned<tf_CInt>;
		constexpr int c_Shift = sizeof(tf_CInt) == 1 ? 0 : 8;

		CUnsigned Number = _Number;
		uint32 Ret = 0;

		for (uint32 i = 0; i < uint32(sizeof(CUnsigned)); ++i, Number >>= c_Shift)
			Ret += gc_NumBitsSetTable256[mint(Number & CUnsigned(0xff))];

		return Ret;
	}

	template <typename t_CInt>
	struct TCNumBitsSet
	{
		constexpr static bool mc_bHasIntrinsic = false;
	};

#ifdef DMibPNumBitsSet32
	template <>
	struct TCNumBitsSet<uint32>
	{
		constexpr static inline_small uint32 fs_NumBitsSet(uint32 _Number) noexcept
		{
			return DMibPNumBitsSet32(_Number);
		}

		constexpr static bool mc_bHasIntrinsic = true;
	};
#endif

#ifdef DMibPNumBitsSet64
	template <>
	struct TCNumBitsSet<uint64>
	{
		constexpr static bool mc_bHasIntrinsic = true;
		constexpr static inline_small uint32 fs_NumBitsSet(uint64 _Number) noexcept
		{
			return DMibPNumBitsSet64(_Number);
		}
	};
#endif

	template <typename tf_CInt>
	constexpr inline_small uint32 fg_NumBitsSetDispatch(tf_CInt const &_Number) noexcept
	{
		using CUnsigned = NMib::NTraits::TCUnsigned<tf_CInt>;

		if constexpr (TCNumBitsSet<CUnsigned>::mc_bHasIntrinsic)
			return TCNumBitsSet<CUnsigned>::fs_NumBitsSet(CUnsigned(_Number));
		else if constexpr (sizeof(tf_CInt) <= 4 && TCNumBitsSet<uint32>::mc_bHasIntrinsic)
			return TCNumBitsSet<uint32>::fs_NumBitsSet(uint32(CUnsigned(_Number)));
		else if constexpr (sizeof(tf_CInt) > 4 && sizeof(tf_CInt) <= 8 && TCNumBitsSet<uint64>::mc_bHasIntrinsic)
			return TCNumBitsSet<uint64>::fs_NumBitsSet(uint64(CUnsigned(_Number)));
		else if constexpr (NMib::NTraits::cIsSame<NMib::NTraits::TCSmallerType<tf_CInt>, tf_CInt>)
			return fg_NumBitsSetGeneric(_Number);
		else
			return fg_NumBitsSet(fg_GetUpper(_Number)) + fg_NumBitsSet(fg_GetLower(_Number));
	}
}

namespace NMib
{
	template <typename tf_CInt>
	constexpr uint32 fg_NumBitsSet(tf_CInt const &_Number) noexcept
	{
		return NPrivate::fg_NumBitsSetDispatch(_Number);
	}
}
