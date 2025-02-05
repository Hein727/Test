#pragma once
#include "GameLib/game_lib.h"

/// <summary>
/// ���`�⊮���s���֐��i�{���AVECTOR2�N���X�ɒǉ��������������ǂ��j
/// </summary>
/// <param name="start">�J�n�l</param>
/// <param name="end">�I���l</param>
/// <param name="t">�J�n�l�ƏI���l�̊Ԃŕ⊮���銄��</param>
/// <returns>�⊮���ꂽ�l</returns>
VECTOR2 vec2Lerp(const VECTOR2& start, const VECTOR2& end, float t);

/// <summary>
/// 2D�x�N�g���̊O�ς��v�Z���܂��B
/// </summary>
/// <param name="v0">�ŏ���2D�x�N�g��</param>
/// <param name="v1">2�Ԗڂ�2D�x�N�g��</param>
/// <returns>v0��v1�̊O��</returns>
float vec2Cross(const VECTOR2& v0, const VECTOR2& v1);
