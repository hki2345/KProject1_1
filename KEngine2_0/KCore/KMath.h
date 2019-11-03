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

	// ��... ���࿡ ��Ʋ ��Ƽ�� ���� ������ �ƴ� ��츦 �����غ���...
	// ��, �밢�� �̵��� ������ ��� -> �̵� ���Ͱ� 1.2134, 12.123 ���
	// �̷��ٸ� �ش� ��ü�� �̵� ��δ� ����ȭ(Normalize) �Ǿ�� �� ���̸�,
	// �� ��ü�� ������ �̵� ������ ������ �ܼ� AABB�� �ƴ� �簢�� + �밢������ ������ �簢���� �ɰ��̴�.
	// ��, OBB�浹�� ���� �ϰ� ���� ���� �浹�� ������ �� �ִ�.
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




