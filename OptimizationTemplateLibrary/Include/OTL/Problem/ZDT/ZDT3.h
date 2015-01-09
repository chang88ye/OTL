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

#include <vector>
#include "ZDT.h"
#include "Distance/Distance1.h"
#include "Shape/Shape3.h"

namespace otl
{
namespace problem
{
namespace zdt
{
template <typename _TReal>
class ZDT3 : public ZDT<_TReal>
{
public:
	typedef _TReal TReal;
	typedef ZDT<TReal> TSuper;
	typedef typename TSuper::TDecision TDecision;
	typedef typename TSuper::TSolution TSolution;
	typedef typename TSuper::TRange TRange;
	typedef typename TSuper::TBoundary TBoundary;

	ZDT3(const size_t nDistDecisions = 29);
	~ZDT3(void);

protected:
	size_t _DoEvaluate(TSolution &solution);
	void _Evaluate(const TDecision &decision, std::vector<TReal> &objective);
};

template <typename _TReal>
ZDT3<_TReal>::ZDT3(const size_t nDistDecisions)
	: TSuper(TBoundary(1 + nDistDecisions, std::make_pair<TReal, TReal>(0, 1)))
{
}

template <typename _TReal>
ZDT3<_TReal>::~ZDT3(void)
{
}

template <typename _TReal>
size_t ZDT3<_TReal>::_DoEvaluate(TSolution &solution)
{
	_Evaluate(solution.decision_, solution.objective_);
	return 1;
}

template <typename _TReal>
void ZDT3<_TReal>::_Evaluate(const TDecision &decision, std::vector<TReal> &objective)
{
	assert(this->IsInside(decision));
	objective.resize(TSuper::GetNumberOfObjectives());
	const TReal distance = 1 + 9 * distance::Distance1<TReal>(decision.begin() + 1, decision.end());
	objective[0] = decision[0];
	objective[1] = distance * shape::Shape3(objective[0], distance);
}
}
}
}
