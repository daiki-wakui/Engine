#include "Camera.h"


void Camera::Initialize(UpdateProjMatrixFunc matFunc)
{
	//アスペクト比を計算する
	aspect =
		static_cast<float>(WindowsApp::GetInstance()->GetWindowWidth()) /
		static_cast<float>(WindowsApp::GetInstance()->GetWindowHeight());

	matrixFunc = matFunc;

	if (matFunc == UpdateProjMatrixFunc_Ortho)//平行投影
	{
		if (far_ == 0.0f)
		{
			far_ = 1.0f;
		}
		right = static_cast<float>(WindowsApp::GetInstance()->GetWindowWidth());
		bottom = static_cast<float>(WindowsApp::GetInstance()->GetWindowHeight());

		//平行投影の計算
		EngineMathF::MakeOrthogonalL(left, right, bottom, top, near_, far_, projectionMatrix);

	}
	else//透視投影
	{
		if (near_ == 0.0f)
		{
			near_ = 0.1f;
		}
		if (far_ == 0.0f)
		{
			far_ = 1000.0f;
		}
		if (fovAngleY == 0.0f)
		{
			fovAngleY = EngineMathF::AX_PI / 4;
		}

		//透視投影行列の計算
		EngineMathF::MakePerspectiveL(fovAngleY, aspect, near_, far_, projectionMatrix);

	}

	updateProjMatrix = false;

	//ビュー行列の算出
	EngineMathF::MakeLookL(eye, target, up, viewMatrix);
	//ビュー行列の逆行列を計算
	viewMatrixInv = EngineMathF::MakeInverse(&viewMatrix);
	//ビュープロジェクション行列の作成
	viewProjectionMatrix = viewMatrix * projectionMatrix;

	//カメラの前ベクトル取得
	forward = { viewMatrixInv.m[2][0], viewMatrixInv.m[2][1], viewMatrixInv.m[2][2] };
	forward.normal();

	//注視点と視点の距離取得
	EngineMathF::Vector3 toPos;
	toPos = eye - target;
	tgtToPosLen = toPos.length();

	updateViewMatrix = false;
}

void Camera::Update()
{

	if (oldEye != eye || oldTarget != target || oldUp != up)
	{
		updateViewMatrix = true;

		oldEye = eye;
		oldTarget = target;
		oldUp = up;
	}


	if (updateProjMatrix)
	{
		if (matrixFunc == UpdateProjMatrixFunc_Ortho)
		{
			if (far_ == 0.0f)
			{
				far_ = 1.0f;
			}

			right = static_cast<float>(WindowsApp::GetInstance()->GetWindowWidth());
			bottom = static_cast<float>(WindowsApp::GetInstance()->GetWindowHeight());
			EngineMathF::MakeOrthogonalL(left, right, bottom, top, near_, far_, projectionMatrix);

		}
		else
		{
			if (near_ == 0.0f)
			{
				near_ = 0.1f;
			}
			if (far_ == 0.0f)
			{
				far_ = 1000.0f;
			}
			if (fovAngleY == 0.0f)
			{
				fovAngleY = EngineMathF::AX_PI / 4;
			}

			EngineMathF::MakePerspectiveL(fovAngleY, aspect, near_, far_, projectionMatrix);
		}
		updateProjMatrix = false;
	}

	if (updateViewMatrix)
	{
		//ビュー行列の算出
		EngineMathF::MakeLookL(eye, target, up, viewMatrix);
		//ビュープロジェクション行列の作成
		viewProjectionMatrix = viewMatrix * projectionMatrix;
		//ビュー行列の逆行列を計算
		viewMatrixInv = EngineMathF::MakeInverse(&viewMatrix);

		forward = { viewMatrixInv.m[2][0], viewMatrixInv.m[2][1], viewMatrixInv.m[2][2] };

		EngineMathF::Vector3 toPos;
		toPos = eye - target;
		tgtToPosLen = toPos.length();

		updateViewMatrix = false;
	}
}

void Camera::Move(const EngineMathF::Vector3& move)
{
	eye += move;
	target += move;
	updateViewMatrix = true;
}

void Camera::MoveTarget(const EngineMathF::Vector3& move)
{
	target += move;
	updateViewMatrix = true;
}

void Camera::MovePosition(const EngineMathF::Vector3& move)
{
	eye += move;
	updateViewMatrix = true;
}

#pragma region セッター

void Camera::SetAspect(float aspect_)
{
	aspect = aspect_;
	updateViewMatrix = true;
}

//void Camera::SetPosition(const EngineMathF::Vector3& pos)
//{
//	eye = pos;
//	updateViewMatrix = true;
//}
//
//void Camera::SetPosition(float x, float y, float z)
//{
//	SetPosition(EngineMathF::Vector3(x, y, z));
//}
//
//void Camera::SetTarget(const EngineMathF::Vector3& tgt)
//{
//	target = tgt;
//	updateViewMatrix = true;
//}
//
//void Camera::SetTarget(float x, float y, float z)
//{
//	SetTarget(EngineMathF::Vector3(x, y, z));
//}
//
//void Camera::SetUp(const EngineMathF::Vector3& upVec)
//{
//	up = upVec;
//	up.normal();
//	updateProjMatrix = true;
//}
//
//void Camera::SetUp(float x, float y, float z)
//{
//	SetUp(EngineMathF::Vector3(x, y, z));
//}

void Camera::SetFar(float fFar)
{
	far_ = fFar;
	updateProjMatrix = true;
}

void Camera::SetNear(float fNear)
{
	near_ = fNear;
	updateProjMatrix = true;
}

void Camera::SetFovAngleY(float fovAngle)
{
	this->fovAngleY = fovAngle;
	updateProjMatrix = true;
}

void Camera::SetUpdateProjMatrixFunc(UpdateProjMatrixFunc func)
{
	matrixFunc = func;
	updateProjMatrix = true;
}

void Camera::SetLeft(float left_)
{
	left = left_;
	updateProjMatrix = true;
}
void Camera::SetRight(float right_)
{
	right = right_;
	updateProjMatrix = true;
}

void Camera::SetTop(float top_)
{
	top = top_;
	updateProjMatrix = true;
}

void Camera::SetBottom(float bottom_)
{
	bottom = bottom_;
	updateProjMatrix = true;
}

#pragma endregion

#pragma region ゲッター

//const EngineMathF::Vector3& Camera::GetPosition() const
//{
//	return eye;
//}
//
//const EngineMathF::Vector3& Camera::GetTarget() const
//{
//	return target;
//}
//
//const EngineMathF::Vector3& Camera::GetUp() const
//{
//	return up;
//}

const EngineMathF::Matrix4& Camera::GetViewMatrix()
{
	//更新
	Update();
	return viewMatrix;
}

const EngineMathF::Matrix4& Camera::GetViewMatrixInv()
{
	//更新
	Update();
	return viewMatrixInv;
}

const EngineMathF::Matrix4& Camera::GetProjectionMatrix()
{
	//更新
	Update();
	return projectionMatrix;
}

const EngineMathF::Matrix4& Camera::GetViewProjectionMatrix()
{
	//更新
	Update();
	return viewProjectionMatrix;
}

const EngineMathF::Matrix4& Camera::GetCameraRotation()
{
	//更新
	Update();
	return cameraRotation;
}

float Camera::GetFar() const
{
	return far_;
}

float Camera::GetNear() const
{
	return near_;
}

float Camera::GetFovAngleY() const
{
	return fovAngleY;
}

float Camera::GetTargetToPositionLength() const
{
	return tgtToPosLen;
}

const EngineMathF::Vector3& Camera::GetForward() const
{
	return forward;
}

float Camera::GetAspect() const
{
	return aspect;
}

float Camera::GetLeft()
{
	return left;
}

float Camera::GetRight()
{
	return right;
}

float Camera::GetTop()
{
	return top;
}

float Camera::GetBottom()
{
	return bottom;
}

#pragma endregion