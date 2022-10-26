#pragma once
#include"ErrorException.h"
#include"EngineMathUtility.h"
#include"Camera.h"

class Transform
{
private:
	// 定数バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuff;
	//定数バッファのマッピング用ポインタ
	worldViewpojCamera* constBuffMap = nullptr;

public:
	// ローカル座標
	EngineMathF::Vector3 translation = { 0, 0, 0 };
	// X,Y,Z軸回りのローカル回転角
	EngineMathF::Vector3 rotation = { 0, 0, 0 };
	// ローカルスケール
	EngineMathF::Vector3 scale = { 1, 1, 1 };

	EngineMathF::Matrix4 matWorld;
private:
	char PADDING[4]{};
public:
	// 親となるワールド変換へのポインタ
	const Transform* parent = nullptr;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 行列を転送する
	/// </summary>
	void TransUpdate(Camera* camera);

	void MakeWorldMatrix();

	ID3D12Resource* GetconstBuff();

	worldViewpojCamera* GetWorldViewpojCamera();


};

namespace EngineMathF
{
	Matrix4 MakeWorldMatrix4(Transform& transform);

	/// <summary>
	/// ワールド座標取得
	/// </summary>
	Vector3 GetWorldPosition(Transform& transform);
}