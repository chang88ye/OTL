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
#include "Distance/Distance2.h"
#include "Shape/Shape1.h"

namespace otl
{
namespace problem
{
namespace zdt
{
template <typename _TReal>
class ZDT4 : public ZDT<_TReal>
{
public:
	typedef _TReal TReal;
	typedef ZDT<TReal> TSuper;
	typedef typename TSuper::TDecision TDecision;
	typedef typename TSuper::TSolution TSolution;
	typedef typename TSuper::TRange TRange;
	typedef typename TSuper::TBoundary TBoundary;

	ZDT4(const size_t nDistDecisions = 29);
	~ZDT4(void);
	static TBoundary GetDecisionSpace(const size_t nDecisions);

protected:
	size_t _DoEvaluate(TSolution &solution);
	void _Evaluate(const TDecision &decision, std::vector<TReal> &objective);
};

template <typename _TReal>
ZDT4<_TReal>::ZDT4(const size_t nDistDecisions)
	: TSuper(GetDecisionSpace(1 + nDistDecisions))
{
}

template <typename _TReal>
ZDT4<_TReal>::~ZDT4(void)
{
}

template <typename _TReal>
typename ZDT4<_TReal>::TBoundary ZDT4<_TReal>::GetDecisionSpace(const size_t nDecisions)
{
	TBoundary boundary(nDecisions);
	boundary[0].first = 0;
	boundary[0].second = 1;
	for (size_t i = 1; i < boundary.size(); ++i)
	{
		boundary[i].first = -5;
		boundary[i].second = 5;
	}
	return boundary;
}

template <typename _TReal>
size_t ZDT4<_TReal>::_DoEvaluate(TSolution &solution)
{
	_Evaluate(solution.decision_, solution.objective_);
	return 1;
}

template <typename _TReal>
void ZDT4<_TReal>::_Evaluate(const TDecision &decision, std::vector<TReal> &objective)
{
	assert(this->IsInside(decision));
	objective.resize(TSuper::GetNumberOfObjectives());
	const TReal distance = 1 + distance::Distance2<TReal>(decision.begin() + 1, decision.end());
	objective[0] = decision[0];
	objective[1] = distance * shape::Shape1(objective[0] / distance);
}
}
}
}
