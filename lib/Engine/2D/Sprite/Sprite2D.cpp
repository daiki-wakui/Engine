#include "Sprite2D.h"

void Sprite2D::Initialize()
{
	SpriteInitialize();

	float width = static_cast<float>(WindowsApp::GetInstance()->GetWindowWidth());
	float height = static_cast<float>(WindowsApp::GetInstance()->GetWindowHeight());

	EngineMathF::MakeOrthogonalL(0.0f, width, height, 0.0f, 0.0f, 1.0f, matProjection);

	CreatVertexIndexBuffer();
}

//描画
void Sprite2D::Draw(TextureData& textureData, Transform& transform, Material* material)
{
		//画像の半分のサイズ
	float halfW = static_cast<float>(textureData.width) * 0.5f;
	float halfH = static_cast<float>(textureData.height) * 0.5f;

	// 頂点データ
	PosUvColor vertices[] =
	{//		x		y		z		u	v
		{{-halfW, -halfH, 0.0f},{0.0f,0.0f},{1.0f,1.0f,1.0f,1.0f}},//左上インデックス0
		{{-halfW, halfH, 0.0f},{0.0f,1.0f},{1.0f,1.0f,1.0f,1.0f}},//左下インデックス1
		{{halfW, -halfH, 0.0f},{1.0f,0.0f},{1.0f,1.0f,1.0f,1.0f}},//右上インデックス2
		{{halfW, halfH, 0.0f},{1.0f,1.0f},{1.0f,1.0f,1.0f,1.0f}},//右下インデックス3
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

	EngineMathF::Matrix4 mTrans, mRot, mScale, matWorld;
	//平行移動行列
	mTrans.MakeTranslation(transform.translation);
	//回転行列
	mRot.MakeRotation(transform.rotation);
	//スケール行列
	mScale.MakeScaling(transform.scale);
	//ワールド行列
	matWorld = mScale * mRot * mTrans;

	transform.matWorld = matWorld * matProjection;

	transform.GetWorldViewpojCamera()->matWorld = transform.matWorld;

	SpriteDraw(textureData, transform, material);
}

void Sprite2D::AnimationDraw(TextureData& textureData, Transform& transform, uint16_t radiusX, uint16_t radiusY, float& frame, float frameDiv, Material* material)
{
	size_t animeFrame = static_cast<size_t>(frame / frameDiv);

	size_t width = static_cast<size_t>(radiusX) * 2;
	size_t height = static_cast<size_t>(radiusY) * 2;

	float widthU = static_cast<float>(width / textureData.width);

	//画像の半分のサイズ
	float halfW = static_cast<float>(width);
	float halfH = static_cast<float>(height);

	if (textureData.width/ width <animeFrame+1)
	{
		frame = 0;
	}

	// 頂点データ
	PosUvColor vertices[] =
	{//		x		y		z		u	v
		{{-halfW, -halfH, 0.0f},{widthU * static_cast<float>(animeFrame),0.0f},{1.0f,1.0f,1.0f,1.0f}},//左上インデックス0
		{{-halfW, halfH, 0.0f},{widthU * static_cast<float>(animeFrame),1.0f},{1.0f,1.0f,1.0f,1.0f}},//左下インデックス1
		{{halfW, -halfH, 0.0f},{widthU * static_cast<float>((animeFrame+1)),0.0f},{1.0f,1.0f,1.0f,1.0f}},//右上インデックス2
		{{halfW, halfH, 0.0f},{widthU * static_cast<float>((animeFrame+1)),1.0f},{1.0f,1.0f,1.0f,1.0f}},//右下インデックス3
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

	EngineMathF::Matrix4 mTrans, mRot, mScale, matWorld;
	//平行移動行列
	mTrans.MakeTranslation(transform.translation);
	//回転行列
	mRot.MakeRotation(transform.rotation);
	//スケール行列
	mScale.MakeScaling(transform.scale);
	//ワールド行列
	matWorld = mScale * mRot * mTrans;

	transform.matWorld = matWorld * matProjection;

	transform.GetWorldViewpojCamera()->matWorld = transform.matWorld;

	SpriteDraw(textureData, transform, material);
}
