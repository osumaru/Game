#pragma once
#pragma once
//オブジェクトのインターフェース

class IGameObject : Uncopyable
{
public:
	//コンストラクタ
	IGameObject();
	
	//仮想デストラクタ(基底クラスのデストラクタは仮想関数でなくてはならない。)
	virtual ~IGameObject();

	//初期化関数
	virtual bool Start() { return true; }

	//非同期の初期化関数
	virtual bool AsyncStart(){ return true; }

	//更新関数
	virtual void Update() = 0;

	//描画関数
	virtual void Draw() {};

	//Drawを呼び終わった後にもう一度呼ぶ関数。アルファブレンドしたいスプライトやポストエフェクトを切ってスプライトを描画したいときに使う。
	virtual void AfterDraw() {};

	//死ぬ前に一回だけ呼ばれる関数
	virtual void BeforeDead() {};

	//死んでいるか？
	bool IsDelete() const
	{
		return m_isDelete;
	}
	//初期化済みか？
	bool IsStart() const
	{
		return m_isStart;
	}

	//アクティブフラグを設定
	void SetIsActive(bool isActive)
	{
		m_isActiveUpdate = isActive;
		m_isActiveDraw = isActive;
	}

	//更新のアクティブフラグを設定
	void SetIsActiveUpdate(bool isActive)
	{
		m_isActiveUpdate = isActive;
	}

	//更新がアクティブか？
	bool IsActiveUpdate()
	{
		return m_isActiveUpdate;
	}

	//描画のアクティブフラグを設定
	void SetIsActiveDraw(bool isActive)
	{
		m_isActiveDraw = isActive;
	}

	//描画がアクティブか？
	bool IsActiveDraw()
	{
		return m_isActiveDraw;
	}

	//アクティブか？
	bool IsActive()
	{
		return m_isActiveUpdate && m_isActiveDraw;
	}

	friend class CGameObjectManager;
private:

	//AsyncStartを呼ぶ関数
	void AsyncStarter()
	{
		if (!m_isAsyncStart && !m_isDelete)
		{
			m_isAsyncStart = AsyncStart();
		}
	}

	//Start関数を呼ぶ関数
	void Starter()
	{
		if (!m_isStart && !m_isDelete)
		{
			m_isStart = Start();
		}
	}
	//Update関数を呼ぶ関数
	void Updater()
	{
		if (m_isStart && m_isAsyncStart && m_isActiveUpdate && !m_isDelete)
		{
			Update();
		}
	}
	//Draw関数を呼ぶ関数
	void Drawer()
	{
		if (m_isStart && m_isAsyncStart && m_isActiveDraw && !m_isDelete)
		{
			Draw();
		}
	}

	//AfterDrawerを呼ぶ関数
	void AfterDrawer()
	{
		if (m_isStart && m_isAsyncStart && m_isActiveDraw && !m_isDelete)
		{
			AfterDraw();
		}
	}


	//リセット関数、Addでオブジェクトマネージャーに登録されたものがDeleteされるときに呼ぶ
	void Reset()
	{
		m_isStart = false;
		m_isDelete = false;
		m_isAsyncStart = false;
		m_isActiveUpdate = true;
		m_isActiveDraw = true;
	}
private:
	bool m_isDelete;			//インスタンスを消す時に建てるフラグ
	bool m_isStart;				//初期化してるかのフラグ
	bool m_isAsyncStart;		//非同期の初期化をしてるかのフラグ
	bool m_isActiveUpdate;		//描画がアクティブかどうかのフラグ
	bool m_isActiveDraw;		//描画がアクティブかどうかのフラグ
};