//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : YUKI TAKAHASHI
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "player.h"
#include "camera.h"
#include "fade.h"
#include "game.h"
#include "joypad.h"
#include "keyboard.h"
#include "meshField.h"
#include "model.h"
#include "sound.h"
#include "shadow.h"
#include "ball.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MODELFILE0			"data/MODEL/car100.x"					// 読み込むモデル＿[0]
#define TEXTUREFILE0		"data/TEXTURE/red.jpg"					// 読み込むテクスチャ
#define TEXTUREFILE1		"data/TEXTURE/blue.jpg"					// 読み込むテクスチャ
#define TEXTUREFILE2		"data/TEXTURE/yellow.jpg"				// 読み込むテクスチャ
#define TEXTUREFILE3		"data/TEXTURE/green.jpg"				// 読み込むテクスチャ
#define MAX_TEXTURE			(5)										// テクスチャ数
#define MAX_USETEXTURE		(4)										// 使用テクスチャ数
#define MAX_MODEL			(1)										// モデルの数
#define PLAYER_MOVE			(0.4f)									// プレイヤーの移動量
#define PLAYER_REST			(1475)									// プレイヤーの移動範囲
#define PLAYER_GRAVITY		(5)										// 重力
#define PLAYER_JUMP_MOVE	(11.25)									// ジャンプ量

//=============================================================================
// モーションの種類
//=============================================================================
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,	// ニュートラル
	//MOTIONTYPE_RUNNING,		// ランニング
	//MOTIONTYPE_ATTACK,		// アタック
	//MOTIONTYPE_JUMP,		// ジャンプ
	//MOTIONTYPE_LAND,		// ランド
	MOTIONTYPE_MAX			// モーションの最大数
} MOTIONTYPE;

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{// モデル
	LPD3DXMESH		pMesh;						// メッシュ情報へのポインタ
	LPD3DXBUFFER	pBuffMat;					// マテリアル情報へのポインタ
	DWORD			nNumMat;					// マテリアル情報の数
	D3DXMATRIX		mtxWorld;					// ワールドマトリックス
	D3DXVECTOR3		pos;						// 位置
	D3DXVECTOR3		posSet;						// 初期位置
	D3DXVECTOR3		rot;						// 向き(回転)
	D3DXVECTOR3		rotDest;					// 到達する向き(回転)
	int				nIdxModelParent;			// 親の番号
	int				nIdxShadow;					// 影のID
} MODEL;

typedef struct
{// キー要素
	D3DXVECTOR3		pos;						// 現在の位置
	D3DXVECTOR3		rot;						// 向き(回転)
} KEY;

typedef struct
{// キー情報
	int				nNumKyeFrame;				// キーフレーム数
	KEY				aKey[MAX_MODEL];			// キー要素
	//bool			bUse;						// キーを使用しているか
} KEY_INFO;

typedef struct
{// モーション情報
	int				nCntFrame;					// 現在のフレーム数
	int				nNumKey;					// 現在のキー
	int				nMaxKey;					// 最大キー数
	bool			bLoop;						// ループするか
	//KEY_INFO		aKeyInfo[MAX_KEY];			// キー情報
} MOTION_INFO;

typedef struct
{// プレイヤー
	D3DXMATRIX		mtxWorld;					// ワールドマトリックス
	D3DXVECTOR3		pos;						// 現在の位置
	D3DXVECTOR3		posOld;						// 前回の位置
	D3DXVECTOR3		move;						// 移動量
	D3DXVECTOR3		rot;						// 向き(回転)
	D3DXVECTOR3		rotDest;					// 到達する向き(回転)
	D3DXVECTOR3		rotDiff;					// 到達する向きと現在の向きの差
	int				nIdxShadow;					// 影のID
	int				nNumParts;					// パーツ数
	int				nLife;						// 体力
	bool			bJump;						// ジャンプしているか
	bool			bMotion;					// モーション再生中か
	MODEL			aModel[MAX_MODEL];			// モデル情報
	//MOTION_INFO		aMotionInfo[MAX_MOTION];	// モーション情報
	MOTIONTYPE		motionType;					// 現在のモーション
	bool			bCollAtk;					// 攻撃が当たっているか
	int				nRaidTrout;					// 乗っているマスの番号
	int				nNextTrout;					// 到達するマスの番号
	int				nCntNumber;					//
	float			fRadius;					//当たり判定用半径
} PLAYER;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
//void LoadPlayerMotion(void);
void Move(CAMERA *pCamera);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9	g_paTexturePlayer[MAX_TEXTURE] = {};			// テクスチャへのポインタ

PLAYER				g_player[NUM_JOYPAD_MAX];						// プレイヤーの情報

// 陣取りの色
D3DXCOLOR g_aPlayer[4] = {
	D3DXCOLOR(1.0f,0.0f,0.0f,1.0f),	// 1P
	D3DXCOLOR(0.0f,0.0f,1.0f,1.0f),	// 2P
	D3DXCOLOR(1.0f,1.0f,0.0f,1.0f),	// 3P
	D3DXCOLOR(0.0f,1.0f,0.0f,1.0f)	// 4P
};

//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 初期化（遊ぶプレイヤー数で最大回数を変更する）
	for (int nCnt = 0; nCnt < GetNumPad(); nCnt++)
	{
		// 初期設定
		g_player[nCnt].posOld = g_player[nCnt].pos;

		g_player[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player[nCnt].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player[nCnt].rotDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player[nCnt].bJump = false;
		g_player[nCnt].bMotion = true;
		g_player[nCnt].motionType = MOTIONTYPE_NEUTRAL;
		g_player[nCnt].bCollAtk = false;
		g_player[nCnt].fRadius = 30;
		
		// 影の作成
		g_player[nCnt].nIdxShadow = SetShadow(g_player[nCnt].pos, g_player[nCnt].rot, D3DXVECTOR3(20.0f, 0.0f, 20.0f));

		// 体
		g_player[nCnt].aModel[0].nIdxModelParent = -1;// NULL
		g_player[nCnt].aModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player[nCnt].aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		
		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
		{
			g_player[nCnt].aModel[nCntModel].posSet = g_player[nCnt].aModel[nCntModel].pos;
		}
	}

	if (*GetMode() == MODE_TITLE)
	{
		for (int nCnt = 0; nCnt < NUM_JOYPAD_MAX; nCnt++)
		{
			g_player[nCnt].posOld = g_player[nCnt].pos;
			g_player[nCnt].nRaidTrout = 0;
			g_player[nCnt].nNextTrout = 0;
		}
	}

	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODELFILE0, D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&g_player[0].aModel[0].pBuffMat, NULL,
		&g_player[0].aModel[0].nNumMat,
		&g_player[0].aModel[0].pMesh);

	for (int nCnt = 1; nCnt < NUM_JOYPAD_MAX; nCnt++)
	{// 同じデータを格納
		g_player[nCnt].aModel[0].pBuffMat = g_player[0].aModel[0].pBuffMat;
		g_player[nCnt].aModel[0].nNumMat = g_player[0].aModel[0].nNumMat;
		g_player[nCnt].aModel[0].pMesh = g_player[0].aModel[0].pMesh;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTUREFILE0, &g_paTexturePlayer[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTUREFILE1, &g_paTexturePlayer[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTUREFILE2, &g_paTexturePlayer[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTUREFILE3, &g_paTexturePlayer[3]);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		// メッシュの開放
		for (int nCntMesh = 0; nCntMesh < MAX_MODEL; nCntMesh++)
		{
			if (g_player[nCnt].aModel[nCntMesh].pMesh != NULL)
			{
				g_player[nCnt].aModel[nCntMesh].pMesh->Release();
				g_player[nCnt].aModel[nCntMesh].pMesh = NULL;
			}
		}

		// マテリアルの開放
		for (int nCntMat = 0; nCntMat < MAX_MODEL; nCntMat++)
		{
			if (g_player[nCnt].aModel[nCntMat].pBuffMat != NULL)
			{
				g_player[nCnt].aModel[nCntMat].pBuffMat->Release();
				g_player[nCnt].aModel[nCntMat].pBuffMat = NULL;
			}
		}
	}

	// テクスチャの開放
	for (int nCntTex = 0; nCntTex < 4; nCntTex++)
	{
		if (g_paTexturePlayer[nCntTex] != NULL)
		{
			g_paTexturePlayer[nCntTex]->Release();
			g_paTexturePlayer[nCntTex] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	MODE *pMode = GetMode();		// 現在のモードの取得
	CAMERA *pCamera = GetCamera(0);	// カメラ情報の取得
	int nStickH, nStickV;

	for (int nCnt = 0; nCnt < GetNumPad(); nCnt++, pCamera++)
	{
		// アナログスティック左の取得
		GetJoypadStickLeft(nCnt, &nStickH, &nStickV);
		
		// 前回の位置を保存
		g_player[nCnt].posOld = g_player[nCnt].pos;

		// 重力の設定
		g_player[nCnt].pos.y -= PLAYER_GRAVITY;
		
		// パッド
		if (nStickH != 0 || nStickV != 0)
		{
			// 移動
			g_player[0].move.x += sinf(D3DX_PI * (float)atan2(nStickH, nStickV) / D3DX_PI + pCamera->rot.y) * 1.0f;
			g_player[0].move.z += cosf(D3DX_PI * (float)atan2(nStickH, nStickV) / D3DX_PI + pCamera->rot.y) * 1.0f;

			// 向き
			g_player[0].rotDest.y = D3DX_PI * -(float)atan2(nStickH, -nStickV) / D3DX_PI + pCamera->rot.y;
		}
		//キーボード移動
		Move(pCamera);
		
		// 角度が一定値を超えた場合の数値制限
		if (g_player[nCnt].rot.y > D3DX_PI)
		{
			g_player[nCnt].rot.y -= D3DX_PI * 2;
		}

		if (g_player[nCnt].rot.y < -D3DX_PI)
		{
			g_player[nCnt].rot.y += D3DX_PI * 2;
		}

		// 角度が一定値を超えた場合の数値制限
		if (g_player[nCnt].rotDest.y > D3DX_PI)
		{
			g_player[nCnt].rotDest.y -= D3DX_PI * 2;
		}

		if (g_player[nCnt].rotDest.y < -D3DX_PI)
		{
			g_player[nCnt].rotDest.y += D3DX_PI * 2;
		}

		// 向きの差を求める
		g_player[nCnt].rotDiff.y = g_player[nCnt].rotDest.y - g_player[nCnt].rot.y;

		// 角度が一定値を超えた場合の数値制限
		if (g_player[nCnt].rotDiff.y > D3DX_PI)
		{
			g_player[nCnt].rotDiff.y -= D3DX_PI * 2;
		}

		if (g_player[nCnt].rotDiff.y < -D3DX_PI)
		{
			g_player[nCnt].rotDiff.y += D3DX_PI * 2;
		}

		// 向き
		g_player[nCnt].rot.y += (g_player[nCnt].rotDiff.y)*0.2f;

		// 位置の更新
		g_player[nCnt].pos.x += g_player[nCnt].move.x;
		g_player[nCnt].pos.y += g_player[nCnt].move.y;
		g_player[nCnt].pos.z += g_player[nCnt].move.z;

		//ボール投げる＆つかむ
		BALL *pBall = GetBall();

		float fDistX, fDistZ;
		float fDistans = 100000;
		fDistX = pBall->pos.x - g_player[nCnt].pos.x;
		fDistZ = pBall->pos.z - g_player[nCnt].pos.z;
		fDistans = (float)sqrt(fDistX * fDistX + fDistZ * fDistZ);

		if (GetJoypadTrigger(nCnt, JOYPADKEY_B))
		{
			if (pBall->nParent == nCnt && pBall->bHold)
			{	//投げる
				pBall->bHold = false;
				ThrowBall(g_player[nCnt].move);
			}
			else if(g_player[nCnt].fRadius + PLAYER_RANGE > fDistans && !pBall->bHold)
			{	//つかむ
				pBall->bHold = true;
				pBall->nParent = nCnt;
			}
		}

		// 当たり判定
		bool bRand = false;// 着地判定

		if (*GetMode() == MODE_GAME)
		{
			if (CollisionMeshField(&g_player[nCnt].pos, &g_player[nCnt].posOld, D3DXVECTOR3(15.0f, 50.0f, 15.0f)) == true)// フィールド
			{
				bRand = true;
			}
			if (!pBall->bHold)
			{
				CollisionBall(&g_player[nCnt].pos, &g_player[nCnt].posOld, g_player[nCnt].fRadius);
			}
		}

		if (*GetMode() != MODE_GAME)
		{
			if (CollisionModel(&g_player[nCnt].pos, &g_player[nCnt].posOld, D3DXVECTOR3(15.0f, 50.0f, 15.0f)) == true)// モデル
			{
				bRand = true;
			}
		}

		// 影の位置を設定
		SetPositionShadow(g_player[nCnt].nIdxShadow, g_player[nCnt].pos);

		// 慣性(減速)
		g_player[nCnt].move.x += (0 - g_player[nCnt].move.x)*0.125f;
		g_player[nCnt].move.y += (0 - g_player[nCnt].move.y)*0.125f;
		g_player[nCnt].move.z += (0 - g_player[nCnt].move.z)*0.125f;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxParent;		// 計算用マトリックス
	D3DXMATERIAL *pMat;							// 現在のマテリアル保存用
	D3DMATERIAL9 matDef;						// マテリアルデータへのポインタ

	for (int nCnt = 0; nCnt < GetNumPad(); nCnt++)
	{
		// 本体
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_player[nCnt].mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player[nCnt].rot.y, g_player[nCnt].rot.x, g_player[nCnt].rot.z);
		D3DXMatrixMultiply(&g_player[nCnt].mtxWorld, &g_player[nCnt].mtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_player[nCnt].pos.x, g_player[nCnt].pos.y, g_player[nCnt].pos.z);
		D3DXMatrixMultiply(&g_player[nCnt].mtxWorld, &g_player[nCnt].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_player[nCnt].mtxWorld);
	
		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_player[nCnt].aModel[nCntModel].mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player[nCnt].aModel[nCntModel].rot.y,
				g_player[nCnt].aModel[nCntModel].rot.x, g_player[nCnt].aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_player[nCnt].aModel[nCntModel].mtxWorld, &g_player[nCnt].aModel[nCntModel].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_player[nCnt].aModel[nCntModel].pos.x,
				g_player[nCnt].aModel[nCntModel].pos.y, g_player[nCnt].aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_player[nCnt].aModel[nCntModel].mtxWorld, &g_player[nCnt].aModel[nCntModel].mtxWorld, &mtxTrans);

			if (g_player[nCnt].aModel[nCntModel].nIdxModelParent == -1)
			{
				D3DXMatrixMultiply(&g_player[nCnt].aModel[nCntModel].mtxWorld, &g_player[nCnt].aModel[nCntModel].mtxWorld, &g_player[nCnt].mtxWorld);
			}
			else
			{
				D3DXMatrixMultiply(&g_player[nCnt].aModel[nCntModel].mtxWorld, &g_player[nCnt].aModel[nCntModel].mtxWorld,
					&g_player[nCnt].aModel[g_player[nCnt].aModel[nCntModel].nIdxModelParent].mtxWorld);
			}

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_player[nCnt].aModel[nCntModel].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアル情報に対するポインタを取得
			pMat = (D3DXMATERIAL*)g_player[nCnt].aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_player[nCnt].aModel[nCntModel].nNumMat; nCntMat++)
			{
				// テクスチャの設定
				if (nCntMat == 0)
				{
					pDevice->SetTexture(0, g_paTexturePlayer[nCnt]);
				}
				else
				{
					pDevice->SetTexture(0, g_paTexturePlayer[MAX_TEXTURE - 1]);
				}
				
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// 描画
				g_player[nCnt].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}
			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=============================================================================
//	移動処理
//=============================================================================
void Move(CAMERA *pCamera)
{
	// キーボード
	if (GetKeyboardPress(DIK_A))
	{
		if (GetKeyboardPress(DIK_W))
		{// 左上
			g_player[1].move.x += sinf(-D3DX_PI*0.75f - pCamera->rot.y) * PLAYER_MOVE;
			g_player[1].move.z -= cosf(-D3DX_PI*0.75f - pCamera->rot.y) * PLAYER_MOVE;

			g_player[1].rotDest.y = D3DX_PI*0.75f + pCamera->rot.y;
		}
		else if (GetKeyboardPress(DIK_S))
		{// 左下
			g_player[1].move.x += sinf(-D3DX_PI*0.25f - pCamera->rot.y) * PLAYER_MOVE;
			g_player[1].move.z -= cosf(-D3DX_PI*0.25f - pCamera->rot.y) * PLAYER_MOVE;

			g_player[1].rotDest.y = D3DX_PI*0.25f + pCamera->rot.y;
		}
		else
		{// 左
			g_player[1].move.x += sinf(-D3DX_PI*0.5f - pCamera->rot.y) * PLAYER_MOVE;
			g_player[1].move.z -= cosf(-D3DX_PI*0.5f - pCamera->rot.y) * PLAYER_MOVE;

			g_player[1].rotDest.y = D3DX_PI*0.5f + pCamera->rot.y;
		}
	}
	else if (GetKeyboardPress(DIK_D))
	{
		if (GetKeyboardPress(DIK_W))
		{// 右上
			g_player[1].move.x += sinf(D3DX_PI*0.75f - pCamera->rot.y) * PLAYER_MOVE;
			g_player[1].move.z -= cosf(D3DX_PI*0.75f - pCamera->rot.y) * PLAYER_MOVE;

			g_player[1].rotDest.y = -D3DX_PI*0.75f + pCamera->rot.y;
		}
		else if (GetKeyboardPress(DIK_S))
		{// 右下
			g_player[1].move.x += sinf(D3DX_PI*0.25f - pCamera->rot.y) * PLAYER_MOVE;
			g_player[1].move.z -= cosf(D3DX_PI*0.25f - pCamera->rot.y) * PLAYER_MOVE;

			g_player[1].rotDest.y = -D3DX_PI*0.25f + pCamera->rot.y;
		}
		else
		{// 右
			g_player[1].move.x += sinf(D3DX_PI*0.5f - pCamera->rot.y) * PLAYER_MOVE;
			g_player[1].move.z -= cosf(D3DX_PI*0.5f - pCamera->rot.y) * PLAYER_MOVE;

			g_player[1].rotDest.y = -D3DX_PI*0.5f + pCamera->rot.y;
		}
	}
	else if (GetKeyboardPress(DIK_W))
	{// 上
		g_player[1].move.x += sinf(D3DX_PI - pCamera->rot.y) * PLAYER_MOVE;
		g_player[1].move.z -= cosf(D3DX_PI - pCamera->rot.y) * PLAYER_MOVE;

		g_player[1].rotDest.y = D3DX_PI + pCamera->rot.y;
	}
	else if (GetKeyboardPress(DIK_S))
	{// 下
		g_player[1].move.x += sinf(0 - pCamera->rot.y) * PLAYER_MOVE;
		g_player[1].move.z -= cosf(0 - pCamera->rot.y) * PLAYER_MOVE;

		g_player[1].rotDest.y = 0 + pCamera->rot.y;
	}
}

////=============================================================================
//// モーションのロード
////=============================================================================
//void LoadPlayerMotion(void)
//{
//	FILE *pFile = NULL;		// ファイルポインタ
//	char cReedText[128];	// 読み取り用
//	char cHeadText[128];	// 文字格納用
//	char cDie[128];			// 文字格納用
//	int nLoop = 0;;			// ループ格納用
//	int nCntKey = 0;		// パーツカウント
//	int nCntKeySet = 0;		// キー番号カウント
//	int nCntMotion = 0;		// モーションカウント
//
//	// ファイルオープン
//	pFile = fopen(TEXTFILE0, "r");
//
//	if (pFile != NULL)// ファイルが無事に開けた場合
//	{
//		while (strcmp(cHeadText, "SCRIPT") != 0)
//		{
//			fgets(cReedText, sizeof(cReedText), pFile);
//			sscanf(cReedText, "%s", &cHeadText);
//		}
//
//		if (strcmp(cHeadText, "SCRIPT") == 0)
//		{// ファイルのロード処理
//			while (strcmp(cHeadText, "END_SCRIPT") != 0)
//			{
//				fgets(cReedText, sizeof(cReedText), pFile);
//				sscanf(cReedText, "%s", &cHeadText);
//
//				if (strcmp(cHeadText, "NUM_PARTS") == 0)
//				{// パーツ数
//					sscanf(cReedText, "%s %s %d", &cDie, &cDie, &g_player.nNumParts);
//				}
//
//				if (strcmp(cHeadText, "MOTIONSET") == 0)
//				{
//					while (strcmp(cHeadText, "END_MOTIONSET") != 0)
//					{
//						fgets(cReedText, sizeof(cReedText), pFile);
//						sscanf(cReedText, "%s", &cHeadText);
//
//						if (strcmp(cHeadText, "LOOP") == 0)
//						{// ループするかどうか
//							sscanf(cReedText, "%s %s %d", &cDie, &cDie, &nLoop);
//
//							if (nLoop == 1)
//							{// ループする場合
//								g_player.aMotionInfo[nCntMotion].bLoop = true;
//							}
//							else
//							{// ループしない場合
//								g_player.aMotionInfo[nCntMotion].bLoop = false;
//							}
//						}
//
//						if (strcmp(cHeadText, "NUM_KEY") == 0)
//						{// 最大キー数
//							sscanf(cReedText, "%s %s %d", &cDie, &cDie,
//								&g_player.aMotionInfo[nCntMotion].nMaxKey);
//						}
//
//						if (strcmp(cHeadText, "KEYSET") == 0)
//						{
//							while (strcmp(cHeadText, "END_KEYSET") != 0)
//							{
//								fgets(cReedText, sizeof(cReedText), pFile);
//								sscanf(cReedText, "%s", &cHeadText);
//
//								if (strcmp(cHeadText, "FRAME") == 0)
//								{// キーフレーム数
//									sscanf(cReedText, "%s %s %d", &cDie, &cDie,
//										&g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].nNumKyeFrame);
//								}
//
//								if (strcmp(cHeadText, "KEY") == 0)
//								{
//									while (strcmp(cHeadText, "END_KEY") != 0)
//									{
//										fgets(cReedText, sizeof(cReedText), pFile);
//										sscanf(cReedText, "%s", &cHeadText);
//
//										if (strcmp(cHeadText, "POS") == 0)
//										{// 位置
//											sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie,
//												&g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].pos.x,
//												&g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].pos.y,
//												&g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].pos.z);
//										}
//
//										if (strcmp(cHeadText, "ROT") == 0)
//										{// 向き
//											sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie,
//												&g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].rot.x,
//												&g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].rot.y,
//												&g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].rot.z);
//										}
//									}
//
//									nCntKey++;
//								}
//							}
//
//							nCntKeySet++;
//						}
//
//						nCntKey = 0;// キーパーツカウントリセット
//					}
//
//					nCntMotion++;
//					nCntKeySet = 0;// キー番号カウントリセット
//				}
//			}
//		}
//
//		// ファイルを閉じる
//		fclose(pFile);
//	}
//	else// 開けなかった場合
//	{
//		// エラーメッセージ
//	}
//}

//=============================================================================
// 場所の設定
//=============================================================================
void SetPlayerPos(D3DXVECTOR3 pos, int nNum)
{
	g_player[nNum].pos = pos;
}

//=============================================================================
// 向きの設定
//=============================================================================
void SetPlayerRot(D3DXVECTOR3 rot, int nNum)
{
	g_player[nNum].rot = rot;
	g_player[nNum].rotDest = g_player[nNum].rot;
}

//=============================================================================
// 移動量の設定
//=============================================================================
void SetPlayerMove(D3DXVECTOR3 move, int nNum)
{
	g_player[nNum].move = move;
}

//=============================================================================
// 場所情報の取得処理
//=============================================================================
D3DXVECTOR3 *GetPlayerPos(int nNum)
{
	return&g_player[nNum].pos;
}

//=============================================================================
// 場所情報の取得処理
//=============================================================================
D3DXVECTOR3 *GetPlayerPosOld(int nNum)
{
	return&g_player[nNum].posOld;
}

//=============================================================================
// 向き情報の取得処理
//=============================================================================
D3DXVECTOR3 *GetPlayerRot(int nNum)
{
	return&g_player[nNum].rot;
}

//=============================================================================
// 移動量情報の取得処理
//=============================================================================
D3DXVECTOR3 *GetPlayerMove(int nNum)
{
	return&g_player[nNum].move;
}

//=============================================================================
// 半径情報の取得処理
//=============================================================================
float *GetPlayerRadius(int nNum)
{
	return&g_player[nNum].fRadius;
}