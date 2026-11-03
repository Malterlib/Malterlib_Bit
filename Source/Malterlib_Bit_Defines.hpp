// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NNumeric
{
	template <typename t_CUpper, typename t_CLower>
	struct TCInt;
}

namespace NMib::NPrivate
{
	struct CBitAutoConvert;
	struct CBitRangeAutoConvert;

	consteval umint fg_GetLowestBitSetStatic(auto _CurrentNumber, umint _Bit) noexcept;
	consteval smint fg_GetHighestBitSetStatic(auto _CurrentNumber) noexcept;

	consteval auto fg_Power(auto _Number, umint _Power) noexcept;
}

namespace NMib
{
	template <typename tf_CInt>
	constexpr NTraits::TCSmallerType<tf_CInt> fg_GetLower(tf_CInt const &_Integer) noexcept;

	template <typename tf_CInt>
	constexpr NTraits::TCSmallerType<tf_CInt> fg_GetUpper(tf_CInt const &_Integer) noexcept;

	template <typename tf_CUpper, typename tf_CLower>
	constexpr typename NNumeric::TCInt<tf_CUpper, tf_CLower>::CLower const &fg_GetLower(NNumeric::TCInt<tf_CUpper, tf_CLower> const &_Integer) noexcept;

	template <typename tf_CUpper, typename tf_CLower>
	constexpr typename NNumeric::TCInt<tf_CUpper, tf_CLower>::CUpper const &fg_GetUpper(NNumeric::TCInt<tf_CUpper, tf_CLower> const &_Integer) noexcept;
}
