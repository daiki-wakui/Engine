#pragma once
//#DirectXのやつ
#include"ErrorException.h"

//自作.h
#include"EngineMathUtility.h"
#include"WindowsApp.h"
#include"DirectX12Core.h"
#include "Camera.h"
#include"Sprite.h"
#include"DefaultMaterial.h"

//pragma comment



//using namespace


class Sprite3D : public Sprite
{
private:

public:

	Sprite3D() = default;
	~Sprite3D() = default;

	//初期化
	virtual void Initialize()override;

	///<summary>
	///描画
	///</summary>
	virtual void Draw(TextureData& textureData, Transform& transform, Material* material = &DEFAULT_SPRITE3D_MATERIAL);
	
	virtual void Draw(TextureData& textureData, Transform& transform,Camera* camera, BillboardFlag flag = NonBillboard, Material* material = &DEFAULT_SPRITE3D_MATERIAL);

	virtual void AnimationDraw(TextureData& textureData, Transform& transform, uint16_t radiusX, uint16_t radiusY, float& frame, float frameDiv, Material* material = &DEFAULT_SPRITE3D_MATERIAL);

private:



	//コピーコンストラクタ・代入演算子削除
	Sprite3D& operator=(const Sprite3D&) = delete;
	Sprite3D(const Sprite3D&) = delete;
};

