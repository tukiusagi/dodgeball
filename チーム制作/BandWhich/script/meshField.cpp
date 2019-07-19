//=============================================================================
//
// ���b�V���t�B�[���h���� [meshField.cpp]
// Author : YUKI TAKAHASHI
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "meshField.h"
#include "keyboard.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTUREFILE0	"data/TEXTURE/miti2.jpg"				// �ǂݍ��ރe�N�X�`��
#define TEXTUREFILE1	"data/TEXTURE/asphalt02-pattern.jpg"	// �ǂݍ��ރe�N�X�`��
#define MAX_TEXTURE		(2)										// �e�N�X�`����
#define POLYFON_WIDTH	(2225)									// �|���S���̕�
#define POLYGON_HEIGHT	(1900)									// �|���S���̉��s
#define POLYFON_WIDTH1	(5000)									// �|���S���̕�
#define POLYGON_HEIGHT1	(5000)									// �|���S���̉��s
#define MAX_FIELD		(2)										// �t�B�[���h�̐�

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffer;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	pIdxBuffer;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				pos;		// �ʒu
	D3DXVECTOR3				rot;		// ����(��])
	D3DXVECTOR3				size;		// �傫��
	D3DXMATRIX				mtxWorld;	// ���[���h�}�g���b�N�X
	int						nNumWidth;	// ���̕�����
	int						nNumHeight;	// �c�̕�����
	int						nNumPolygon;// ���|���S����
	int						nNumVertex;	// �����_��
	int						nNumIndex;	// ���C���f�b�N�X��
	D3DXVECTOR3				sizePolygon;// 1������̃|���S���̑傫��
	D3DXVECTOR2				texPolygon;	// 1������̃e�N�X�`�����W
	bool					bUse;		// �g�p���Ă��邩
} MESHFIELD;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_apTextureMeshField[MAX_TEXTURE] = {};		// �e�N�X�`���ւ̃|�C���^

MESHFIELD				g_aMeshField[MAX_FIELD];					// ���b�V���|���S���̏��

//=============================================================================
// ����������
//=============================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTUREFILE0, &g_apTextureMeshField[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTUREFILE1, &g_apTextureMeshField[1]);

	// �����ݒ�
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
		// �����_��
		g_aMeshField[nCntField].nNumVertex = (g_aMeshField[nCntField].nNumWidth + 1)*(g_aMeshField[nCntField].nNumHeight + 1);

		// ���|���S����
		g_aMeshField[nCntField].nNumPolygon = (g_aMeshField[nCntField].nNumWidth*g_aMeshField[nCntField].nNumHeight * 2) + ((g_aMeshField[nCntField].nNumHeight - 1) * 4);

		// ���C���f�b�N�X��
		g_aMeshField[nCntField].nNumIndex = g_aMeshField[nCntField].nNumPolygon + 2;

		// 1������̃|���S���̑傫��
		g_aMeshField[nCntField].sizePolygon = D3DXVECTOR3(1.0f*g_aMeshField[nCntField].size.x / g_aMeshField[nCntField].nNumWidth, 0.0f,
			1.0f*g_aMeshField[nCntField].size.z / g_aMeshField[nCntField].nNumHeight);

		// 1������̃e�N�X�`�����W
		if (nCntField == 0)
		{
			g_aMeshField[nCntField].texPolygon = D3DXVECTOR2(1.0f / g_aMeshField[nCntField].nNumWidth, 1.0f / g_aMeshField[nCntField].nNumHeight);
		}
		else
		{
			g_aMeshField[nCntField].texPolygon = D3DXVECTOR2(5.0f / g_aMeshField[nCntField].nNumWidth, 5.0f / g_aMeshField[nCntField].nNumHeight);
		}
	}

	// ���_���̍쐬
	MakeVertexMeshField(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshField(void)
{
	// �e�N�X�`���̊J��
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
		// �C���f�b�N�X�o�b�t�@�̉��
		if (g_aMeshField[nCntField].pIdxBuffer)
		{
			g_aMeshField[nCntField].pIdxBuffer->Release();
			g_aMeshField[nCntField].pIdxBuffer = NULL;
		}

		// ���_�o�b�t�@�̊J��
		if (g_aMeshField[nCntField].pVtxBuffer != NULL)
		{
			g_aMeshField[nCntField].pVtxBuffer->Release();
			g_aMeshField[nCntField].pVtxBuffer = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshField(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X

	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aMeshField[nCntField].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshField[nCntField].rot.y, g_aMeshField[nCntField].rot.x, g_aMeshField[nCntField].rot.z);
		D3DXMatrixMultiply(&g_aMeshField[nCntField].mtxWorld, &g_aMeshField[nCntField].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aMeshField[nCntField].pos.x, g_aMeshField[nCntField].pos.y, g_aMeshField[nCntField].pos.z);
		D3DXMatrixMultiply(&g_aMeshField[nCntField].mtxWorld, &g_aMeshField[nCntField].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aMeshField[nCntField].mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_aMeshField[nCntField].pVtxBuffer, 0, sizeof(VERTEX_3D));

		// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(g_aMeshField[nCntField].pIdxBuffer);

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureMeshField[nCntField]);

		// �|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_aMeshField[nCntField].nNumVertex, 0, g_aMeshField[nCntField].nNumPolygon);
	}
}

//=============================================================================
// ���b�V���t�B�[���h�Ƃ̓����蔻��
//=============================================================================
bool CollisionMeshField(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 size)
{
	bool bRand = false;// ���n����

	// �����蔻��
	for (int nCountField = 0; nCountField < MAX_FIELD; nCountField++)
	{
		if (g_aMeshField[nCountField].bUse)// �t�B�[���h���g�p����Ă���ꍇ
		{
			if (pPos->x + size.x > g_aMeshField[nCountField].pos.x - g_aMeshField[nCountField].size.x / 2 &&
				pPos->x - size.x < g_aMeshField[nCountField].pos.x + g_aMeshField[nCountField].size.x / 2)
			{// X���W���͈͓���
				if (pPos->z + size.z > g_aMeshField[nCountField].pos.z - g_aMeshField[nCountField].size.z / 2 &&
					pPos->z - size.z < g_aMeshField[nCountField].pos.z + g_aMeshField[nCountField].size.z / 2)
				{// Z���W���͈͓���
					if (pPos->y <= g_aMeshField[nCountField].pos.y&&
						pPosOld->y >= g_aMeshField[nCountField].pos.y)
					{// �ォ��߂荞�񂾏ꍇ
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
// ���_���̍쐬
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice)
{
	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_aMeshField[nCntField].nNumVertex,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_aMeshField[nCntField].pVtxBuffer,
			NULL);

		// �C���f�b�N�X�o�b�t�@�𐶐�
		pDevice->CreateIndexBuffer(sizeof(WORD) * g_aMeshField[nCntField].nNumIndex,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&g_aMeshField[nCntField].pIdxBuffer,
			NULL);

		VERTEX_3D *pVtx;

		// ���_���̐ݒ�
		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_aMeshField[nCntField].pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntV = 0; nCntV < g_aMeshField[nCntField].nNumHeight + 1; nCntV++)
		{
			for (int nCntH = 0; nCntH < g_aMeshField[nCntField].nNumWidth + 1; nCntH++)
			{
				// ���_���W�̐ݒ�
				pVtx[nCntH + nCntV * (g_aMeshField[nCntField].nNumWidth + 1)].pos =
					D3DXVECTOR3(-g_aMeshField[nCntField].size.x / 2 + g_aMeshField[nCntField].sizePolygon.x*nCntH,
						0.0f, g_aMeshField[nCntField].size.z / 2 - g_aMeshField[nCntField].sizePolygon.z*nCntV);

				// �@���x�N�g���̐ݒ�
				pVtx[nCntH + nCntV * (g_aMeshField[nCntField].nNumWidth + 1)].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				// ���_�J���[�̐ݒ�
				pVtx[nCntH + nCntV * (g_aMeshField[nCntField].nNumWidth + 1)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// �e�N�X�`�����W�̐ݒ�
				pVtx[nCntH + nCntV * (g_aMeshField[nCntField].nNumWidth + 1)].tex = D3DXVECTOR2(g_aMeshField[nCntField].texPolygon.x*nCntH,
					g_aMeshField[nCntField].texPolygon.y*nCntV);
			}
		}
		// ���_�f�[�^���A�����b�N����
		g_aMeshField[nCntField].pVtxBuffer->Unlock();

		WORD *pIdx;// �C���f�b�N�X�f�[�^�ւ̃|�C���^

		// �C���f�b�N�X�̐ݒ�
		// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
		g_aMeshField[nCntField].pIdxBuffer->Lock(0, 0, (void**)&pIdx, 0);

		int nNum = 0;
		int nNumCnt = 0;

		// �C���f�b�N�X
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
		// �C���f�b�N�X�o�b�t�@���A�����b�N����
		g_aMeshField[nCntField].pIdxBuffer->Unlock();
	}
}
