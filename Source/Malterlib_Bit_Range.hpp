// Copyright © 2026 Unborken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once
namespace NMib::NPrivate
{
	struct CBitAutoConvert
	{
		template <typename tf_CType>
		constexpr operator tf_CType() const noexcept
		{
			using CIntType = NTraits::TCUnsigned<NTraits::TCIntFromSize<sizeof(tf_CType)>>;

			return tf_CType(CIntType(1) << m_Bit);
		}

		mint m_Bit;
	};

	struct CBitRangeAutoConvert
	{
		template <typename tf_CType>
		constexpr operator tf_CType() const noexcept
		{
			using CIntType = NTraits::TCUnsigned<NTraits::TCIntFromSize<sizeof(tf_CType)>>;

			return tf_CType
				(
					(
						(
							(CIntType(1) << m_BitEnd)
							- CIntType(1)
						)
						| (CIntType(1) << m_BitEnd)
					)
					^
					(
						(CIntType(1) << m_BitStart)
						- CIntType(1)
					)
				)
			;
		}

		mint m_BitStart;
		mint m_BitEnd;
	};
}

namespace NMib
{
	constexpr NPrivate::CBitAutoConvert fg_Bit(mint _Bit) noexcept
	{
		return NPrivate::CBitAutoConvert{.m_Bit = _Bit};
	}

	template <typename tf_CType>
	constexpr tf_CType fg_Bit(mint _Bit, tf_CType _One) noexcept
	{
		return _One << _Bit;
	}

	constexpr NPrivate::CBitRangeAutoConvert fg_BitRange(mint _BitStart, mint _BitEnd) noexcept
	{
		return NPrivate::CBitRangeAutoConvert{.m_BitStart = _BitStart, .m_BitEnd = _BitEnd};
	}

	template <typename tf_CType>
	constexpr tf_CType fg_BitRange(uaint _BitStart, uaint _BitEnd) noexcept
	{
		using CUnsigned = NTraits::TCUnsigned<tf_CType>;

		return
			(
				(
					(CUnsigned(1) << _BitEnd)
					- CUnsigned(1)
				)
				| (CUnsigned(1) << _BitEnd)
			)
			^
			(
				(CUnsigned(1) << _BitStart)
				- CUnsigned(1)
			)
		;
	}
}
