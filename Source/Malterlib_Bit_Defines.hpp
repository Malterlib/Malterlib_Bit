// Copyright © 2026 Unborken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

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

	consteval mint fg_GetLowestBitSetStatic(auto _CurrentNumber, mint _Bit) noexcept;
	consteval smint fg_GetHighestBitSetStatic(auto _CurrentNumber) noexcept;

	consteval auto fg_Power(auto _Number, mint _Power) noexcept;
}

namespace NMib
{
	template <typename t_CInt>
	constexpr NTraits::TCSmallerType<t_CInt> fg_GetLower(t_CInt const &_Integer) noexcept;

	template <typename t_CInt>
	constexpr NTraits::TCSmallerType<t_CInt> fg_GetUpper(t_CInt const &_Integer) noexcept;

	template <typename t_CUpper, typename t_CLower>
	constexpr typename NNumeric::TCInt<t_CUpper, t_CLower>::CLower const &fg_GetLower(NNumeric::TCInt<t_CUpper, t_CLower> const &_Integer) noexcept;

	template <typename t_CUpper, typename t_CLower>
	constexpr typename NNumeric::TCInt<t_CUpper, t_CLower>::CUpper const &fg_GetUpper(NNumeric::TCInt<t_CUpper, t_CLower> const &_Integer) noexcept;
}
