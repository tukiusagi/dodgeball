//=============================================================================
//
// メッシュフィールド処理 [meshField.cpp]
// Author : YUKI TAKAHASHI
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "meshField.h"
#include "keyboard.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEXTUREFILE0	"data/TEXTURE/miti2.jpg"				// 読み込むテクスチャ
#define TEXTUREFILE1	"data/TEXTURE/asphalt02-pattern.jpg"	// 読み込むテクスチャ
#define MAX_TEXTURE		(2)										// テクスチャ数
#define POLYFON_WIDTH	(2225)									// ポリゴンの幅
#define POLYGON_HEIGHT	(1900)									// ポリゴンの奥行
#define POLYFON_WIDTH1	(5000)									// ポリゴンの幅
#define POLYGON_HEIGHT1	(5000)									// ポリゴンの奥行
#define MAX_FIELD		(2)										// フィールドの数

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffer;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9	pIdxBuffer;	// インデックスバッファへのポインタ
	D3DXVECTOR3				pos;		// 位置
	D3DXVECTOR3				rot;		// 向き(回転)
	D3DXVECTOR3				size;		// 大きさ
	D3DXMATRIX				mtxWorld;	// ワールドマトリックス
	int						nNumWidth;	// 横の分割数
	int						nNumHeight;	// 縦の分割数
	int						nNumPolygon;// 総ポリゴン数
	int						nNumVertex;	// 総頂点数
	int						nNumIndex;	// 総インデックス数
	D3DXVECTOR3				sizePolygon;// 1つあたりのポリゴンの大きさ
	D3DXVECTOR2				texPolygon;	// 1つあたりのテクスチャ座標
	bool					bUse;		// 使用しているか
} MESHFIELD;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_apTextureMeshField[MAX_TEXTURE] = {};		// テクスチャへのポインタ

MESHFIELD				g_aMeshField[MAX_FIELD];					// メッシュポリゴンの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTUREFILE0, &g_apTextureMeshField[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTUREFILE1, &g_apTextureMeshField[1]);

	// 初期設定
	g_aMeshField[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aMeshField[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aMeshField[0].size = D3DXVECTOR3(POLYFON_WIDTH, 0.0f, POLYGON_HEIGHT);
	g_aMeshField[0].nNumWidth = 100;
	g_aMeshField[0].nNumHeight = 100;
	g_aMeshField[0].bUse = true;

	g_aMeshField[1].pos = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	g_aMeshField[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aMeshField[1].size = D3DXVECTOR3(POLYFON_WIDTH1, 0.0f, POLYGON_HEIGHT1);
	g_aMeshField[1].nNumWidth = 2;
	g_aMeshField[1].nNumHeight = 2;
	g_aMeshField[1].bUse = true;

	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		// 総頂点数
		g_aMeshField[nCntField].nNumVertex = (g_aMeshField[nCntField].nNumWidth + 1)*(g_aMeshField[nCntField].nNumHeight + 1);

		// 総ポリゴン数
		g_aMeshField[nCntField].nNumPolygon = (g_aMeshField[nCntField].nNumWidth*g_aMeshField[nCntField].nNumHeight * 2) + ((g_aMeshField[nCntField].nNumHeight - 1) * 4);

		// 総インデックス数
		g_aMeshField[nCntField].nNumIndex = g_aMeshField[nCntField].nNumPolygon + 2;

		// 1つあたりのポリゴンの大きさ
		g_aMeshField[nCntField].sizePolygon = D3DXVECTOR3(1.0f*g_aMeshField[nCntField].size.x / g_aMeshField[nCntField].nNumWidth, 0.0f,
			1.0f*g_aMeshField[nCntField].size.z / g_aMeshField[nCntField].nNumHeight);

		// 1つあたりのテクスチャ座標
		if (nCntField == 0)
		{
			g_aMeshField[nCntField].texPolygon = D3DXVECTOR2(1.0f / g_aMeshField[nCntField].nNumWidth, 1.0f / g_aMeshField[nCntField].nNumHeight);
		}
		else
		{
			g_aMeshField[nCntField].texPolygon = D3DXVECTOR2(5.0f / g_aMeshField[nCntField].nNumWidth, 5.0f / g_aMeshField[nCntField].nNumHeight);
		}
	}

	// 頂点情報の作成
	MakeVertexMeshField(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshField(void)
{
	// テクスチャの開放
	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		if (g_apTextureMeshField[nCntTex] != NULL)
		{
			g_apTextureMeshField[nCntTex]->Release();
			g_apTextureMeshField[nCntTex] = NULL;
		}
	}

	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		// インデックスバッファの解放
		if (g_aMeshField[nCntField].pIdxBuffer)
		{
			g_aMeshField[nCntField].pIdxBuffer->Release();
			g_aMeshField[nCntField].pIdxBuffer = NULL;
		}

		// 頂点バッファの開放
		if (g_aMeshField[nCntField].pVtxBuffer != NULL)
		{
			g_aMeshField[nCntField].pVtxBuffer->Release();
			g_aMeshField[nCntField].pVtxBuffer = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshField(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス

	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aMeshField[nCntField].mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshField[nCntField].rot.y, g_aMeshField[nCntField].rot.x, g_aMeshField[nCntField].rot.z);
		D3DXMatrixMultiply(&g_aMeshField[nCntField].mtxWorld, &g_aMeshField[nCntField].mtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aMeshField[nCntField].pos.x, g_aMeshField[nCntField].pos.y, g_aMeshField[nCntField].pos.z);
		D3DXMatrixMultiply(&g_aMeshField[nCntField].mtxWorld, &g_aMeshField[nCntField].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aMeshField[nCntField].mtxWorld);

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_aMeshField[nCntField].pVtxBuffer, 0, sizeof(VERTEX_3D));

		// インデックスバッファをデータストリームに設定
		pDevice->SetIndices(g_aMeshField[nCntField].pIdxBuffer);

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_apTextureMeshField[nCntField]);

		// ポリゴンの描画
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_aMeshField[nCntField].nNumVertex, 0, g_aMeshField[nCntField].nNumPolygon);
	}
}

//=============================================================================
// メッシュフィールドとの当たり判定
//=============================================================================
bool CollisionMeshField(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 size)
{
	bool bRand = false;// 着地判定

	// 当たり判定
	for (int nCountField = 0; nCountField < MAX_FIELD; nCountField++)
	{
		if (g_aMeshField[nCountField].bUse)// フィールドが使用されている場合
		{
			if (pPos->x + size.x > g_aMeshField[nCountField].pos.x - g_aMeshField[nCountField].size.x / 2 &&
				pPos->x - size.x < g_aMeshField[nCountField].pos.x + g_aMeshField[nCountField].size.x / 2)
			{// X座標が範囲内か
				if (pPos->z + size.z > g_aMeshField[nCountField].pos.z - g_aMeshField[nCountField].size.z / 2 &&
					pPos->z - size.z < g_aMeshField[nCountField].pos.z + g_aMeshField[nCountField].size.z / 2)
				{// Z座標が範囲内か
					if (pPos->y <= g_aMeshField[nCountField].pos.y&&
						pPosOld->y >= g_aMeshField[nCountField].pos.y)
					{// 上からめり込んだ場合
						pPos->y = g_aMeshField[nCountField].pos.y;
						bRand = true;
					}
				}
			}
		}
	}

	return bRand;
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice)
{
	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		// オブジェクトの頂点バッファを生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_aMeshField[nCntField].nNumVertex,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_aMeshField[nCntField].pVtxBuffer,
			NULL);

		// インデックスバッファを生成
		pDevice->CreateIndexBuffer(sizeof(WORD) * g_aMeshField[nCntField].nNumIndex,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&g_aMeshField[nCntField].pIdxBuffer,
			NULL);

		VERTEX_3D *pVtx;

		// 頂点情報の設定
		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_aMeshField[nCntField].pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntV = 0; nCntV < g_aMeshField[nCntField].nNumHeight + 1; nCntV++)
		{
			for (int nCntH = 0; nCntH < g_aMeshField[nCntField].nNumWidth + 1; nCntH++)
			{
				// 頂点座標の設定
				pVtx[nCntH + nCntV * (g_aMeshField[nCntField].nNumWidth + 1)].pos =
					D3DXVECTOR3(-g_aMeshField[nCntField].size.x / 2 + g_aMeshField[nCntField].sizePolygon.x*nCntH,
						0.0f, g_aMeshField[nCntField].size.z / 2 - g_aMeshField[nCntField].sizePolygon.z*nCntV);

				// 法線ベクトルの設定
				pVtx[nCntH + nCntV * (g_aMeshField[nCntField].nNumWidth + 1)].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				// 頂点カラーの設定
				pVtx[nCntH + nCntV * (g_aMeshField[nCntField].nNumWidth + 1)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// テクスチャ座標の設定
				pVtx[nCntH + nCntV * (g_aMeshField[nCntField].nNumWidth + 1)].tex = D3DXVECTOR2(g_aMeshField[nCntField].texPolygon.x*nCntH,
					g_aMeshField[nCntField].texPolygon.y*nCntV);
			}
		}
		// 頂点データをアンロックする
		g_aMeshField[nCntField].pVtxBuffer->Unlock();

		WORD *pIdx;// インデックスデータへのポインタ

		// インデックスの設定
		// インデックスバッファをロックし、インデックスデータへのポインタを取得
		g_aMeshField[nCntField].pIdxBuffer->Lock(0, 0, (void**)&pIdx, 0);

		int nNum = 0;
		int nNumCnt = 0;

		// インデックス
		for (int nCntV = 0; nCntV < g_aMeshField[nCntField].nNumHeight; nCntV++)
		{
			if (nCntV != 0)
			{
				pIdx[nNum] = nNumCnt - 1 + g_aMeshField[nCntField].nNumWidth - 1 + 3;
				nNum++;
			}

			for (int nCntH = 0; nCntH < g_aMeshField[nCntField].nNumWidth + 1; nCntH++, nNumCnt++, nNum += 2)
			{
				pIdx[nNum] = nNumCnt + g_aMeshField[nCntField].nNumWidth + 1;
				pIdx[nNum + 1] = nNumCnt;
			}

			if (nCntV != g_aMeshField[nCntField].nNumHeight - 1)
			{
				pIdx[nNum] = nNumCnt - 1;
				nNum++;
			}
		}
		// インデックスバッファをアンロックする
		g_aMeshField[nCntField].pIdxBuffer->Unlock();
	}
}
