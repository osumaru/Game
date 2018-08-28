#pragma once
class Camera
{
public:
	//コンストラクタ
	Camera();

	//デストラクタ
	~Camera();

	//アスペクト比を設定
	void SetAspect(float _aspect);

	//アスペクト比を取得
	float GetAspect() const;

	//ファーを設定
	void SetFar(float _far);

	//ファーを取得
	float GetFar() const;

	//ニアを設定
	void SetNear(float _near);

	//ニアを取得
	float GetNear() const;

	//画角を設定。
	void SetAngle(float angle);

	//画角を取得
	float GetAngle() const;

	//視点を設定
	void SetTarget(const Vector3& target);

	//視点を取得
	const Vector3& GetTarget() const;

	//座標を設定
	void SetPosition(const Vector3& position);

	//座標を取得
	const Vector3& GetPosition() const;

	//カメラの上方向を設定
	void SetUp(const Vector3& up);

	//カメラの上方向を取得
	const Vector3& GetUp() const;

	//カメラの前方向を取得
	const Vector3& GetFlont() const;

	//カメラの横方向を取得
	const Vector3& GetRight() const;

	//ビュー行列の設定。
	void SetViewMatrix(const Matrix& view);

	//ビュー行列の取得
	const Matrix& GetViewMatrix() const;

	//プロジェクション行列の設定。
	void SetProjectionMatrix(const Matrix& projection);

	//プロジェクション行列の取得。
	const Matrix& GetProjectionMatrix() const;

	//初期化
	void Init();

	//更新処理
	void Update();

private:
	Matrix			m_viewMatrix;			//ビュー行列。カメラ行列とも言う。
	Matrix			m_projectionMatrix;		//プロジェクション行列。ビュー空間から射影空間に変換する。
	Vector3			m_position;				//カメラの視点。
	Vector3			m_target;				//カメラの注視点
	Vector3			m_up;					//カメラの上方向
	Vector3			m_flont;				//カメラの前方向
	Vector3			m_right;				//カメラの横方向

	float				m_Far;					//遠平面
	float				m_Near;					//近平面
	float				m_Aspect;				//アスペクト比
	float				m_angle;				//画角
};