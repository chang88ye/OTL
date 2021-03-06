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
#include <list>
#include <string>
#include <algorithm>
#include <cctype>
#include <cassert>
#include <boost/serialization/serialization.hpp>
#include <OTL/Solution.h>

namespace otl
{
namespace problem
{
/*!
 * \brief The optimization problem base class
 * \param[in] _TReal The type of objective, must be a real number type
 * \param[in] _TDecision The type of the decision, can be any data structure
 */
template <typename _TReal, typename _TDecision>
class Problem
{
public:
	typedef _TReal TReal;
	typedef _TDecision TDecision;
	typedef Solution<TReal, TDecision> TSolution;

	Problem(const size_t nObjectives);
	virtual ~Problem(void);
	size_t GetNumberOfObjectives(void) const;
	size_t GetNumberOfEvaluations(void) const;
	void operator ()(TSolution &solution);
	void Fix(std::vector<TReal> &objective);

protected:
	virtual size_t _DoEvaluate(TSolution &solution) = 0;
	virtual void _DoFix(std::vector<TReal> &objective) = 0;

private:
	size_t nObjectives_;
	size_t nEvaluations_;

	template<class _TArchive> void serialize(_TArchive &archive, const unsigned version);

	friend class boost::serialization::access;
};

/*!
 * \brief Constructor
 * \param[in] nObjectives The number of objectives
 */
template <typename _TReal, typename _TDecision>
Problem<_TReal, _TDecision>::Problem(const size_t nObjectives)
{
	assert(nObjectives > 0);
	nObjectives_ = nObjectives;
	nEvaluations_ = 0;
}

template <typename _TReal, typename _TDecision>
Problem<_TReal, _TDecision>::~Problem(void)
{
}

/*!
 * \brief Get number of objectives
 * \return The number of objectives
 */
template <typename _TReal, typename _TDecision>
size_t Problem<_TReal, _TDecision>::GetNumberOfObjectives(void) const
{
	return nObjectives_;
}

/*!
 * \brief Get number of evaluation
 * \return The number of evaluation
 */
template <typename _TReal, typename _TDecision>
size_t Problem<_TReal, _TDecision>::GetNumberOfEvaluations(void) const
{
	return nEvaluations_;
}

/*!
 * \brief Evaluate a solution
 * \param[in, out] solution The solution which need be evaluated
 */
template <typename _TReal, typename _TDecision>
void Problem<_TReal, _TDecision>::operator ()(TSolution &solution)
{
	const size_t nEvaluation = _DoEvaluate(solution);
	assert(nEvaluation > 0);
	nEvaluations_ += nEvaluation;
}

template <typename _TReal, typename _TDecision>
void Problem<_TReal, _TDecision>::Fix(std::vector<TReal> &objective)
{
	_DoFix(objective);
}

template <typename _TReal, typename _TDecision>
template<class _TArchive> void Problem<_TReal, _TDecision>::serialize(_TArchive &archive, const unsigned version)
{
	archive & nObjectives_;
	archive & nEvaluations_;
}

/*!
 * \fn Problem::_DoEvaluate(TSolution &solution)
 * \brief Evaluate a solution
 * \return Number of evaluation
 */
}
}
