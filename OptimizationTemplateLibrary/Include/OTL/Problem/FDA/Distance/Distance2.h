/*!
Copyright (C) 2014, 申瑞珉 (Ruimin Shen)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <algorithm>
#include <cassert>

namespace otl
{
namespace problem
{
namespace fda
{
namespace distance
{
template <typename _TReal>
_TReal Distance2(const std::vector<_TReal> &decision, const size_t nObjectives, const _TReal distance)
{
	const size_t posDecision = nObjectives - 1;
	assert(0 <= posDecision && posDecision <= decision.size());
	_TReal sum = 0;
	for (size_t i = posDecision; i < decision.size(); ++i)
	{
		const _TReal temp = decision[i] - distance;
		sum += temp * temp;
	}
	return distance + sum;
}
}
}
}
}
