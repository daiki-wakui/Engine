#include "Sprite3D.h"


void Sprite3D::Initialize()
{
	SpriteInitialize();

	CreatVertexIndexBuffer();
}

void Sprite3D::Draw(TextureData& textureData, Transform& transform, Camera* camera, BillboardFlag flag, Material* material)
{
	EngineMathF::Matrix4 mTrans, mRot, mScale;

	//平行移動行列
	mTrans.MakeTranslation(transform.translation);
	//回転行列
	mRot.MakeRotation(transform.rotation);
	//スケール行列
	mScale.MakeScaling(transform.scale);

	switch (flag)
	{
	case NonBillboard:
		transform.GetWorldViewpojCamera()->matWorld = mScale * mRot * mTrans * camera->GetViewMatrixInv() * camera->GetProjectionMatrix();
		break;
	case AllBillboard:
	{
		EngineMathF::Matrix4 mat = camera->GetViewMatrix();

		mat.m[3][0] = 0;
		mat.m[3][1] = 0;
		mat.m[3][2] = 0;
		mat.m[3][3] = 1;

		transform.GetWorldViewpojCamera()->matWorld = mScale * mRot * mat * mTrans * camera->GetViewMatrixInv() * camera->GetProjectionMatrix();
		break;
	}
	case XBillboard:
	{
		EngineMathF::Matrix4 mat = camera->GetViewMatrix();

		mat.m[1][0] = 0;
		mat.m[1][1] = 1;
		mat.m[1][2] = 0;
		mat.m[1][3] = 0;

		mat.m[3][0] = 0;
		mat.m[3][1] = 0;
		mat.m[3][2] = 0;
		mat.m[3][3] = 1;

		transform.GetWorldViewpojCamera()->matWorld = mScale * mRot * mat * mTrans * camera->GetViewMatrixInv() * camera->GetProjectionMatrix();
		break;
	}
	case YBillboard:
	{
		EngineMathF::Matrix4 mat = camera->GetViewMatrix();

		mat.m[0][0] = 1;
		mat.m[0][1] = 0;
		mat.m[0][2] = 0;
		mat.m[0][3] = 0;

		mat.m[3][0] = 0;
		mat.m[3][1] = 0;
		mat.m[3][2] = 0;
		mat.m[3][3] = 1;


		transform.GetWorldViewpojCamera()->matWorld = mScale * mRot * mat * mTrans * camera->GetViewMatrixInv() * camera->GetProjectionMatrix();
		break;
	}
	case XYBillboard:
	{
		EngineMathF::Matrix4 mat = camera->GetViewMatrix();

		mat.m[2][0] = 0;
		mat.m[2][1] = 0;
		mat.m[2][2] = 1;
		mat.m[2][3] = 0;

		mat.m[3][0] = 0;
		mat.m[3][1] = 0;
		mat.m[3][2] = 0;
		mat.m[3][3] = 1;

		transform.GetWorldViewpojCamera()->matWorld = mScale * mRot * mat * mTrans * camera->GetViewMatrixInv() * camera->GetProjectionMatrix();
		break;
	}
	default:
		assert(0);
		break;
	}

	Draw(textureData, transform, material);
}

void Sprite3D::AnimationDraw(TextureData& textureData, Transform& transform, uint16_t radiusX, uint16_t radiusY, float& frame, float frameDiv, Material* material)
{
	size_t animeFrame = static_cast<size_t>(frame / frameDiv);

	size_t width = static_cast<size_t>(radiusX) * 2;
	size_t height = static_cast<size_t>(radiusY) * 2;

	float widthU = static_cast<float>(width) / textureData.width;

	//画像の半分のサイズ
	float halfW = static_cast<float>(width) / 10;
	float halfH = static_cast<float>(height) / 10;

	if (textureData.width / width < animeFrame + 1)
	{
		frame = 0;
	}

	// 頂点データ
	PosUvColor vertices[] =
	{//		x		y		z		u	v
		{{-halfW, halfH, 0.0f},{widthU * static_cast<float>((animeFrame)),0.0f},{1.0f,1.0f,1.0f,1.0f}},//左上インデックス0
		{{-halfW, -halfH, 0.0f},{widthU * static_cast<float>((animeFrame)),1.0f},{1.0f,1.0f,1.0f,1.0f}},//左下インデックス1
		{{halfW, halfH, 0.0f},{widthU * static_cast<float>((animeFrame + 1)),0.0f},{1.0f,1.0f,1.0f,1.0f}},//右上インデックス2
		{{halfW, -halfH, 0.0f},{widthU * static_cast<float>((animeFrame + 1)),1.0f},{1.0f,1.0f,1.0f,1.0f}},//右下インデックス3
	};

	// インデックスデータ
	uint16_t indices[] =
	{
		1, 0, 3, // 三角形1つ目
		2, 3, 0, // 三角形2つ目
	};

	//頂点バッファへのデータ転送
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i]; // 座標をコピー
	}

	//インデックスバッファへのデータ転送
	for (int i = 0; i < _countof(indices); i++)
	{
		indexMap[i] = indices[i];   // インデックスをコピー
	}

	SpriteDraw(textureData, transform, material);
}

//描画
void Sprite3D::Draw(TextureData& textureData, Transform& transform, Material* material)
{

	//画像の半分のサイズ
	float halfW = static_cast<float>(textureData.width) * 0.0625f;
	float halfH = static_cast<float>(textureData.height) * 0.0625f;

	// 頂点データ
	PosUvColor vertices[] =
	{//		x		y		z		u	v
		{{-halfW, halfH, 0.0f},{0.0f,0.0f},{1.0f,1.0f,1.0f,1.0f}},//左上インデックス0
		{{-halfW, -halfH, 0.0f},{0.0f,1.0f},{1.0f,1.0f,1.0f,1.0f}},//左下インデックス1
		{{halfW, halfH, 0.0f},{1.0f,0.0f},{1.0f,1.0f,1.0f,1.0f}},//右上インデックス2
		{{halfW, -halfH, 0.0f},{1.0f,1.0f},{1.0f,1.0f,1.0f,1.0f}},//右下インデックス3
	};

	// インデックスデータ
	uint16_t indices[] =
	{
		1, 0, 3, // 三角形1つ目
		2, 3, 0, // 三角形2つ目
	};

	//頂点バッファへのデータ転送
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i]; // 座標をコピー
	}

	//インデックスバッファへのデータ転送
	for (int i = 0; i < _countof(indices); i++)
	{
		indexMap[i] = indices[i];   // インデックスをコピー
	}

	SpriteDraw(textureData, transform, material);
}

