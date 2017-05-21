#include "stdafx.h"
#include "EffectData.h"

CU::Matrix44<float> EffectData::worldMatrix;
CU::Matrix44<float> EffectData::viewMatrix;
CU::Matrix44<float> EffectData::projectionMatrix;

Vector4<float> EffectData::color;
Vector4<float> EffectData::position;

Vector2<float> EffectData::scale;
Vector2<float> EffectData::resolution;
Vector2<float> EffectData::characterSize;
Vector2<float> EffectData::animationFrameSize;
Vector2<float> EffectData::animationUV;

float EffectData::rotation_2D;
float EffectData::alpha;

bool EffectData::flipX;
bool EffectData::flipY;