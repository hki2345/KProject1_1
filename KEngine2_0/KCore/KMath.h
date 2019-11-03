#pragma once
#include "KVector.h"

namespace kstd
{
	class AABB
	{
	public:
		bool operator()(const KRect& _R1, const KRect& _R2) const
		{
			if (true ==
				(_R1.End.x > _R2.Start.x) &&
				(_R2.End.x > _R1.Start.x) &&
				(_R1.End.y > _R2.Start.y) &&
				(_R2.End.y > _R1.Start.y))
			{
				return true;
			}

			return false;
		}
	};

	// 자... 만약에 배틀 시티와 같은 게임이 아닌 경우를 생각해보자...
	// 즉, 대각선 이동이 가능한 경우 -> 이동 벡터가 1.2134, 12.123 경우
	// 이렇다면 해당 객체의 이동 경로는 정규화(Normalize) 되어야 할 것이며,
	// 그 객체가 지나간 이동 도형의 모형은 단순 AABB가 아닌 사각형 + 대각선으로 누워진 사각형이 될것이다.
	// 즉, OBB충돌을 먼저 하고 들어가야 다음 충돌을 진행할 수 있다.
	class OBB
	{
	public:
		OBB(const KRect& _R1, const KRect& _R2, bool& _Result)
		{
			if (true ==
				(_R1.End.x > _R2.Start.x) &&
				(_R2.End.x > _R1.Start.x) &&
				(_R1.End.y > _R2.Start.y) &&
				(_R2.End.y > _R1.Start.y))
			{
				_Result = true;
			}

			else
			{
				_Result = false;
			}
		}
	};

}




