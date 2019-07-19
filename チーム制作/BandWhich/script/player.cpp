//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : YUKI TAKAHASHI
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
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
// �}�N����`
//=============================================================================
#define MODELFILE0			"data/MODEL/car100.x"					// �ǂݍ��ރ��f���Q[0]
#define TEXTUREFILE0		"data/TEXTURE/red.jpg"					// �ǂݍ��ރe�N�X�`��
#define TEXTUREFILE1		"data/TEXTURE/blue.jpg"					// �ǂݍ��ރe�N�X�`��
#define TEXTUREFILE2		"data/TEXTURE/yellow.jpg"				// �ǂݍ��ރe�N�X�`��
#define TEXTUREFILE3		"data/TEXTURE/green.jpg"				// �ǂݍ��ރe�N�X�`��
#define MAX_TEXTURE			(5)										// �e�N�X�`����
#define MAX_USETEXTURE		(4)										// �g�p�e�N�X�`����
#define MAX_MODEL			(1)										// ���f���̐�
#define PLAYER_MOVE			(0.4f)									// �v���C���[�̈ړ���
#define PLAYER_REST			(1475)									// �v���C���[�̈ړ��͈�
#define PLAYER_GRAVITY		(5)										// �d��
#define PLAYER_JUMP_MOVE	(11.25)									// �W�����v��

//=============================================================================
// ���[�V�����̎��
//=============================================================================
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,	// �j���[�g����
	//MOTIONTYPE_RUNNING,		// �����j���O
	//MOTIONTYPE_ATTACK,		// �A�^�b�N
	//MOTIONTYPE_JUMP,		// �W�����v
	//MOTIONTYPE_LAND,		// �����h
	MOTIONTYPE_MAX			// ���[�V�����̍ő吔
} MOTIONTYPE;

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{// ���f��
	LPD3DXMESH		pMesh;						// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER	pBuffMat;					// �}�e���A�����ւ̃|�C���^
	DWORD			nNumMat;					// �}�e���A�����̐�
	D3DXMATRIX		mtxWorld;					// ���[���h�}�g���b�N�X
	D3DXVECTOR3		pos;						// �ʒu
	D3DXVECTOR3		posSet;						// �����ʒu
	D3DXVECTOR3		rot;						// ����(��])
	D3DXVECTOR3		rotDest;					// ���B�������(��])
	int				nIdxModelParent;			// �e�̔ԍ�
	int				nIdxShadow;					// �e��ID
} MODEL;

typedef struct
{// �L�[�v�f
	D3DXVECTOR3		pos;						// ���݂̈ʒu
	D3DXVECTOR3		rot;						// ����(��])
} KEY;

typedef struct
{// �L�[���
	int				nNumKyeFrame;				// �L�[�t���[����
	KEY				aKey[MAX_MODEL];			// �L�[�v�f
	//bool			bUse;						// �L�[���g�p���Ă��邩
} KEY_INFO;

typedef struct
{// ���[�V�������
	int				nCntFrame;					// ���݂̃t���[����
	int				nNumKey;					// ���݂̃L�[
	int				nMaxKey;					// �ő�L�[��
	bool			bLoop;						// ���[�v���邩
	//KEY_INFO		aKeyInfo[MAX_KEY];			// �L�[���
} MOTION_INFO;

typedef struct
{// �v���C���[
	D3DXMATRIX		mtxWorld;					// ���[���h�}�g���b�N�X
	D3DXVECTOR3		pos;						// ���݂̈ʒu
	D3DXVECTOR3		posOld;						// �O��̈ʒu
	D3DXVECTOR3		move;						// �ړ���
	D3DXVECTOR3		rot;						// ����(��])
	D3DXVECTOR3		rotDest;					// ���B�������(��])
	D3DXVECTOR3		rotDiff;					// ���B��������ƌ��݂̌����̍�
	int				nIdxShadow;					// �e��ID
	int				nNumParts;					// �p�[�c��
	int				nLife;						// �̗�
	bool			bJump;						// �W�����v���Ă��邩
	bool			bMotion;					// ���[�V�����Đ�����
	MODEL			aModel[MAX_MODEL];			// ���f�����
	//MOTION_INFO		aMotionInfo[MAX_MOTION];	// ���[�V�������
	MOTIONTYPE		motionType;					// ���݂̃��[�V����
	bool			bCollAtk;					// �U�����������Ă��邩
	int				nRaidTrout;					// ����Ă���}�X�̔ԍ�
	int				nNextTrout;					// ���B����}�X�̔ԍ�
	int				nCntNumber;					//
	float			fRadius;					//�����蔻��p���a
} PLAYER;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
//void LoadPlayerMotion(void);
void Move(CAMERA *pCamera);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9	g_paTexturePlayer[MAX_TEXTURE] = {};			// �e�N�X�`���ւ̃|�C���^

PLAYER				g_player[NUM_JOYPAD_MAX];						// �v���C���[�̏��

// �w���̐F
D3DXCOLOR g_aPlayer[4] = {
	D3DXCOLOR(1.0f,0.0f,0.0f,1.0f),	// 1P
	D3DXCOLOR(0.0f,0.0f,1.0f,1.0f),	// 2P
	D3DXCOLOR(1.0f,1.0f,0.0f,1.0f),	// 3P
	D3DXCOLOR(0.0f,1.0f,0.0f,1.0f)	// 4P
};

//=============================================================================
// ����������
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �������i�V�ԃv���C���[���ōő�񐔂�ύX����j
	for (int nCnt = 0; nCnt < GetNumPad(); nCnt++)
	{
		// �����ݒ�
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
		
		// �e�̍쐬
		g_player[nCnt].nIdxShadow = SetShadow(g_player[nCnt].pos, g_player[nCnt].rot, D3DXVECTOR3(20.0f, 0.0f, 20.0f));

		// ��
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

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODELFILE0, D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&g_player[0].aModel[0].pBuffMat, NULL,
		&g_player[0].aModel[0].nNumMat,
		&g_player[0].aModel[0].pMesh);

	for (int nCnt = 1; nCnt < NUM_JOYPAD_MAX; nCnt++)
	{// �����f�[�^���i�[
		g_player[nCnt].aModel[0].pBuffMat = g_player[0].aModel[0].pBuffMat;
		g_player[nCnt].aModel[0].nNumMat = g_player[0].aModel[0].nNumMat;
		g_player[nCnt].aModel[0].pMesh = g_player[0].aModel[0].pMesh;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTUREFILE0, &g_paTexturePlayer[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTUREFILE1, &g_paTexturePlayer[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTUREFILE2, &g_paTexturePlayer[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTUREFILE3, &g_paTexturePlayer[3]);
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		// ���b�V���̊J��
		for (int nCntMesh = 0; nCntMesh < MAX_MODEL; nCntMesh++)
		{
			if (g_player[nCnt].aModel[nCntMesh].pMesh != NULL)
			{
				g_player[nCnt].aModel[nCntMesh].pMesh->Release();
				g_player[nCnt].aModel[nCntMesh].pMesh = NULL;
			}
		}

		// �}�e���A���̊J��
		for (int nCntMat = 0; nCntMat < MAX_MODEL; nCntMat++)
		{
			if (g_player[nCnt].aModel[nCntMat].pBuffMat != NULL)
			{
				g_player[nCnt].aModel[nCntMat].pBuffMat->Release();
				g_player[nCnt].aModel[nCntMat].pBuffMat = NULL;
			}
		}
	}

	// �e�N�X�`���̊J��
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
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	MODE *pMode = GetMode();		// ���݂̃��[�h�̎擾
	CAMERA *pCamera = GetCamera(0);	// �J�������̎擾
	int nStickH, nStickV;

	for (int nCnt = 0; nCnt < GetNumPad(); nCnt++, pCamera++)
	{
		// �A�i���O�X�e�B�b�N���̎擾
		GetJoypadStickLeft(nCnt, &nStickH, &nStickV);
		
		// �O��̈ʒu��ۑ�
		g_player[nCnt].posOld = g_player[nCnt].pos;

		// �d�͂̐ݒ�
		g_player[nCnt].pos.y -= PLAYER_GRAVITY;
		
		// �p�b�h
		if (nStickH != 0 || nStickV != 0)
		{
			// �ړ�
			g_player[0].move.x += sinf(D3DX_PI * (float)atan2(nStickH, nStickV) / D3DX_PI + pCamera->rot.y) * 1.0f;
			g_player[0].move.z += cosf(D3DX_PI * (float)atan2(nStickH, nStickV) / D3DX_PI + pCamera->rot.y) * 1.0f;

			// ����
			g_player[0].rotDest.y = D3DX_PI * -(float)atan2(nStickH, -nStickV) / D3DX_PI + pCamera->rot.y;
		}
		//�L�[�{�[�h�ړ�
		Move(pCamera);
		
		// �p�x�����l�𒴂����ꍇ�̐��l����
		if (g_player[nCnt].rot.y > D3DX_PI)
		{
			g_player[nCnt].rot.y -= D3DX_PI * 2;
		}

		if (g_player[nCnt].rot.y < -D3DX_PI)
		{
			g_player[nCnt].rot.y += D3DX_PI * 2;
		}

		// �p�x�����l�𒴂����ꍇ�̐��l����
		if (g_player[nCnt].rotDest.y > D3DX_PI)
		{
			g_player[nCnt].rotDest.y -= D3DX_PI * 2;
		}

		if (g_player[nCnt].rotDest.y < -D3DX_PI)
		{
			g_player[nCnt].rotDest.y += D3DX_PI * 2;
		}

		// �����̍������߂�
		g_player[nCnt].rotDiff.y = g_player[nCnt].rotDest.y - g_player[nCnt].rot.y;

		// �p�x�����l�𒴂����ꍇ�̐��l����
		if (g_player[nCnt].rotDiff.y > D3DX_PI)
		{
			g_player[nCnt].rotDiff.y -= D3DX_PI * 2;
		}

		if (g_player[nCnt].rotDiff.y < -D3DX_PI)
		{
			g_player[nCnt].rotDiff.y += D3DX_PI * 2;
		}

		// ����
		g_player[nCnt].rot.y += (g_player[nCnt].rotDiff.y)*0.2f;

		// �ʒu�̍X�V
		g_player[nCnt].pos.x += g_player[nCnt].move.x;
		g_player[nCnt].pos.y += g_player[nCnt].move.y;
		g_player[nCnt].pos.z += g_player[nCnt].move.z;

		//�{�[�������違����
		BALL *pBall = GetBall();

		float fDistX, fDistZ;
		float fDistans = 100000;
		fDistX = pBall->pos.x - g_player[nCnt].pos.x;
		fDistZ = pBall->pos.z - g_player[nCnt].pos.z;
		fDistans = (float)sqrt(fDistX * fDistX + fDistZ * fDistZ);

		if (GetJoypadTrigger(nCnt, JOYPADKEY_B))
		{
			if (pBall->nParent == nCnt && pBall->bHold)
			{	//������
				pBall->bHold = false;
				ThrowBall(g_player[nCnt].move);
			}
			else if(g_player[nCnt].fRadius + PLAYER_RANGE > fDistans && !pBall->bHold)
			{	//����
				pBall->bHold = true;
				pBall->nParent = nCnt;
			}
		}

		// �����蔻��
		bool bRand = false;// ���n����

		if (*GetMode() == MODE_GAME)
		{
			if (CollisionMeshField(&g_player[nCnt].pos, &g_player[nCnt].posOld, D3DXVECTOR3(15.0f, 50.0f, 15.0f)) == true)// �t�B�[���h
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
			if (CollisionModel(&g_player[nCnt].pos, &g_player[nCnt].posOld, D3DXVECTOR3(15.0f, 50.0f, 15.0f)) == true)// ���f��
			{
				bRand = true;
			}
		}

		// �e�̈ʒu��ݒ�
		SetPositionShadow(g_player[nCnt].nIdxShadow, g_player[nCnt].pos);

		// ����(����)
		g_player[nCnt].move.x += (0 - g_player[nCnt].move.x)*0.125f;
		g_player[nCnt].move.y += (0 - g_player[nCnt].move.y)*0.125f;
		g_player[nCnt].move.z += (0 - g_player[nCnt].move.z)*0.125f;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxParent;		// �v�Z�p�}�g���b�N�X
	D3DXMATERIAL *pMat;							// ���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;						// �}�e���A���f�[�^�ւ̃|�C���^

	for (int nCnt = 0; nCnt < GetNumPad(); nCnt++)
	{
		// �{��
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_player[nCnt].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player[nCnt].rot.y, g_player[nCnt].rot.x, g_player[nCnt].rot.z);
		D3DXMatrixMultiply(&g_player[nCnt].mtxWorld, &g_player[nCnt].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_player[nCnt].pos.x, g_player[nCnt].pos.y, g_player[nCnt].pos.z);
		D3DXMatrixMultiply(&g_player[nCnt].mtxWorld, &g_player[nCnt].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_player[nCnt].mtxWorld);
	
		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_player[nCnt].aModel[nCntModel].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player[nCnt].aModel[nCntModel].rot.y,
				g_player[nCnt].aModel[nCntModel].rot.x, g_player[nCnt].aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_player[nCnt].aModel[nCntModel].mtxWorld, &g_player[nCnt].aModel[nCntModel].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
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

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_player[nCnt].aModel[nCntModel].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pMat = (D3DXMATERIAL*)g_player[nCnt].aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_player[nCnt].aModel[nCntModel].nNumMat; nCntMat++)
			{
				// �e�N�X�`���̐ݒ�
				if (nCntMat == 0)
				{
					pDevice->SetTexture(0, g_paTexturePlayer[nCnt]);
				}
				else
				{
					pDevice->SetTexture(0, g_paTexturePlayer[MAX_TEXTURE - 1]);
				}
				
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �`��
				g_player[nCnt].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}
			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=============================================================================
//	�ړ�����
//=============================================================================
void Move(CAMERA *pCamera)
{
	// �L�[�{�[�h
	if (GetKeyboardPress(DIK_A))
	{
		if (GetKeyboardPress(DIK_W))
		{// ����
			g_player[1].move.x += sinf(-D3DX_PI*0.75f - pCamera->rot.y) * PLAYER_MOVE;
			g_player[1].move.z -= cosf(-D3DX_PI*0.75f - pCamera->rot.y) * PLAYER_MOVE;

			g_player[1].rotDest.y = D3DX_PI*0.75f + pCamera->rot.y;
		}
		else if (GetKeyboardPress(DIK_S))
		{// ����
			g_player[1].move.x += sinf(-D3DX_PI*0.25f - pCamera->rot.y) * PLAYER_MOVE;
			g_player[1].move.z -= cosf(-D3DX_PI*0.25f - pCamera->rot.y) * PLAYER_MOVE;

			g_player[1].rotDest.y = D3DX_PI*0.25f + pCamera->rot.y;
		}
		else
		{// ��
			g_player[1].move.x += sinf(-D3DX_PI*0.5f - pCamera->rot.y) * PLAYER_MOVE;
			g_player[1].move.z -= cosf(-D3DX_PI*0.5f - pCamera->rot.y) * PLAYER_MOVE;

			g_player[1].rotDest.y = D3DX_PI*0.5f + pCamera->rot.y;
		}
	}
	else if (GetKeyboardPress(DIK_D))
	{
		if (GetKeyboardPress(DIK_W))
		{// �E��
			g_player[1].move.x += sinf(D3DX_PI*0.75f - pCamera->rot.y) * PLAYER_MOVE;
			g_player[1].move.z -= cosf(D3DX_PI*0.75f - pCamera->rot.y) * PLAYER_MOVE;

			g_player[1].rotDest.y = -D3DX_PI*0.75f + pCamera->rot.y;
		}
		else if (GetKeyboardPress(DIK_S))
		{// �E��
			g_player[1].move.x += sinf(D3DX_PI*0.25f - pCamera->rot.y) * PLAYER_MOVE;
			g_player[1].move.z -= cosf(D3DX_PI*0.25f - pCamera->rot.y) * PLAYER_MOVE;

			g_player[1].rotDest.y = -D3DX_PI*0.25f + pCamera->rot.y;
		}
		else
		{// �E
			g_player[1].move.x += sinf(D3DX_PI*0.5f - pCamera->rot.y) * PLAYER_MOVE;
			g_player[1].move.z -= cosf(D3DX_PI*0.5f - pCamera->rot.y) * PLAYER_MOVE;

			g_player[1].rotDest.y = -D3DX_PI*0.5f + pCamera->rot.y;
		}
	}
	else if (GetKeyboardPress(DIK_W))
	{// ��
		g_player[1].move.x += sinf(D3DX_PI - pCamera->rot.y) * PLAYER_MOVE;
		g_player[1].move.z -= cosf(D3DX_PI - pCamera->rot.y) * PLAYER_MOVE;

		g_player[1].rotDest.y = D3DX_PI + pCamera->rot.y;
	}
	else if (GetKeyboardPress(DIK_S))
	{// ��
		g_player[1].move.x += sinf(0 - pCamera->rot.y) * PLAYER_MOVE;
		g_player[1].move.z -= cosf(0 - pCamera->rot.y) * PLAYER_MOVE;

		g_player[1].rotDest.y = 0 + pCamera->rot.y;
	}
}

////=============================================================================
//// ���[�V�����̃��[�h
////=============================================================================
//void LoadPlayerMotion(void)
//{
//	FILE *pFile = NULL;		// �t�@�C���|�C���^
//	char cReedText[128];	// �ǂݎ��p
//	char cHeadText[128];	// �����i�[�p
//	char cDie[128];			// �����i�[�p
//	int nLoop = 0;;			// ���[�v�i�[�p
//	int nCntKey = 0;		// �p�[�c�J�E���g
//	int nCntKeySet = 0;		// �L�[�ԍ��J�E���g
//	int nCntMotion = 0;		// ���[�V�����J�E���g
//
//	// �t�@�C���I�[�v��
//	pFile = fopen(TEXTFILE0, "r");
//
//	if (pFile != NULL)// �t�@�C���������ɊJ�����ꍇ
//	{
//		while (strcmp(cHeadText, "SCRIPT") != 0)
//		{
//			fgets(cReedText, sizeof(cReedText), pFile);
//			sscanf(cReedText, "%s", &cHeadText);
//		}
//
//		if (strcmp(cHeadText, "SCRIPT") == 0)
//		{// �t�@�C���̃��[�h����
//			while (strcmp(cHeadText, "END_SCRIPT") != 0)
//			{
//				fgets(cReedText, sizeof(cReedText), pFile);
//				sscanf(cReedText, "%s", &cHeadText);
//
//				if (strcmp(cHeadText, "NUM_PARTS") == 0)
//				{// �p�[�c��
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
//						{// ���[�v���邩�ǂ���
//							sscanf(cReedText, "%s %s %d", &cDie, &cDie, &nLoop);
//
//							if (nLoop == 1)
//							{// ���[�v����ꍇ
//								g_player.aMotionInfo[nCntMotion].bLoop = true;
//							}
//							else
//							{// ���[�v���Ȃ��ꍇ
//								g_player.aMotionInfo[nCntMotion].bLoop = false;
//							}
//						}
//
//						if (strcmp(cHeadText, "NUM_KEY") == 0)
//						{// �ő�L�[��
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
//								{// �L�[�t���[����
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
//										{// �ʒu
//											sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie,
//												&g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].pos.x,
//												&g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].pos.y,
//												&g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKeySet].aKey[nCntKey].pos.z);
//										}
//
//										if (strcmp(cHeadText, "ROT") == 0)
//										{// ����
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
//						nCntKey = 0;// �L�[�p�[�c�J�E���g���Z�b�g
//					}
//
//					nCntMotion++;
//					nCntKeySet = 0;// �L�[�ԍ��J�E���g���Z�b�g
//				}
//			}
//		}
//
//		// �t�@�C�������
//		fclose(pFile);
//	}
//	else// �J���Ȃ������ꍇ
//	{
//		// �G���[���b�Z�[�W
//	}
//}

//=============================================================================
// �ꏊ�̐ݒ�
//=============================================================================
void SetPlayerPos(D3DXVECTOR3 pos, int nNum)
{
	g_player[nNum].pos = pos;
}

//=============================================================================
// �����̐ݒ�
//=============================================================================
void SetPlayerRot(D3DXVECTOR3 rot, int nNum)
{
	g_player[nNum].rot = rot;
	g_player[nNum].rotDest = g_player[nNum].rot;
}

//=============================================================================
// �ړ��ʂ̐ݒ�
//=============================================================================
void SetPlayerMove(D3DXVECTOR3 move, int nNum)
{
	g_player[nNum].move = move;
}

//=============================================================================
// �ꏊ���̎擾����
//=============================================================================
D3DXVECTOR3 *GetPlayerPos(int nNum)
{
	return&g_player[nNum].pos;
}

//=============================================================================
// �ꏊ���̎擾����
//=============================================================================
D3DXVECTOR3 *GetPlayerPosOld(int nNum)
{
	return&g_player[nNum].posOld;
}

//=============================================================================
// �������̎擾����
//=============================================================================
D3DXVECTOR3 *GetPlayerRot(int nNum)
{
	return&g_player[nNum].rot;
}

//=============================================================================
// �ړ��ʏ��̎擾����
//=============================================================================
D3DXVECTOR3 *GetPlayerMove(int nNum)
{
	return&g_player[nNum].move;
}

//=============================================================================
// ���a���̎擾����
//=============================================================================
float *GetPlayerRadius(int nNum)
{
	return&g_player[nNum].fRadius;
}