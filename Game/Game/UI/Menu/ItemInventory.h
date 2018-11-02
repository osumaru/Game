/*
*	インベントリクラス
*/
#pragma once

class CMenu;
class IItem;

class CItemInventory : public IGameObject
{
public:
	//コンストラクタ
	CItemInventory();

	//デストラクタ
	~CItemInventory();

	//初期化
	//menu	メニューのポインタ
	void Init(CMenu* menu);

	//更新する前に一度だけ呼ばれる
	bool Start() override;

	//更新
	void Update() override;

	//描画
	void AfterDraw() override;

	//アイテム所持上限を取得
	static int GetItemLimit()
	{
		return m_itemLimit;
	}

private:
	static const int	m_itemLimit = 15;				//アイテム所持上限
	CSprite				m_backGround;					//背景
	CTexture			m_backGroundTexture;
	CSprite				m_pointer;						//カーソル
	CTexture			m_pointerTexture;
	CSprite				m_item[m_itemLimit];			//アイテム
	std::list<IItem*>	m_itemList;						//アイテムリスト
	CMenu*				m_menu = nullptr;				//メニュー
	CVector2			m_basePos = CVector2::Zero;		//初期座標
	CVector2			m_size = CVector2::Zero;		//初期サイズ
	int					m_width = 0;					//インベントリの幅
	int					m_height = 0;					//インベントリの高さ
	int					m_pointerNum = 0;				//カーソルで選んでいるアイテムの番号
};