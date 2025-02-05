#pragma once
#include "GameLib/game_lib.h"

/// <summary>
/// 線形補完を行う関数（本来、VECTOR2クラスに追加実装した方が良い）
/// </summary>
/// <param name="start">開始値</param>
/// <param name="end">終了値</param>
/// <param name="t">開始値と終了値の間で補完する割合</param>
/// <returns>補完された値</returns>
VECTOR2 vec2Lerp(const VECTOR2& start, const VECTOR2& end, float t);

/// <summary>
/// 2Dベクトルの外積を計算します。
/// </summary>
/// <param name="v0">最初の2Dベクトル</param>
/// <param name="v1">2番目の2Dベクトル</param>
/// <returns>v0とv1の外積</returns>
float vec2Cross(const VECTOR2& v0, const VECTOR2& v1);
