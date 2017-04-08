//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GamePlay.cpp
//!
//! @brief  �v���C�V�[���̃\�[�X�t�@�C��
//!
//! @date   2017/4/5	
//!
//! @author Yuhei M	
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "GamePlay.h"
#include<string>
#include<sstream>
#include<fstream>
#include<iostream>
//#include "..ADX2Le.h"
//#include "..\CueSheet_0.h"

#include <time.h>

using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace std;

//	�R���X�g���N�^
GamePlay::GamePlay()
{
	//�f�o�b�O�p�X�e�[�W�ݒ�
	//serectMap = 1;//��

	serectMap = 2;//�X

	if (g_init == 0)
	{
		g_init = 1;
	}

	//�v���C���[�쐬
	player = new Player;

	//���t�g�i�M�~�b�N�j�쐬
	lift = new Gimmik;

	// �}�b�v�̐ݒ�
	if(serectMap == 1)importData("map1.csv");//�}�b�v�f�[�^�̓ǂݍ���
	if(serectMap == 2)importData("map2.csv");//�}�b�v�f�[�^�̓ǂݍ���
	

	// �}�b�v�̐ݒ�
	for (int i = 0; i < MAX_TIP; i++)
	{

		if (g_map[i / MAP_H][i % MAP_W] == 0)//�󔒎w��}�b�v�`�b�v
		{
			g_tip[i].state = 0;
		}
		else if (g_map[i / MAP_H][i % MAP_W] == 3)
		{
			lift->SetPosX((float)(i % MAP_W) * lift->GetGrpW());
			gimmikPosAX = lift->GetPosX();

			lift->SetPosY((float)(i / MAP_H) * lift->GetGrpH());
			gimmikPosAY = lift->GetPosY();
		}
		else if (g_map[i / MAP_H][i % MAP_W] == 4)
		{
			player->SetPosX((float)(i % MAP_W) * player->GetGrpW());
			player->SetPosY((float)(i / MAP_H) * player->GetGrpH());
		}
		else if (g_map[i / MAP_H][i % MAP_W] == 5)
		{
			gimmikPosBX = (i % MAP_W)* lift->GetGrpW();
			gimmikPosBY = (i / MAP_H)* lift->GetGrpH();
		}
		else
		{
			g_tip[i].grp_x = CHIP_SIZE * g_map[i / MAP_H][i %MAP_W];
			g_tip[i].grp_y = 0;
			g_tip[i].grp_w = CHIP_SIZE;
			g_tip[i].grp_h = CHIP_SIZE;
			g_tip[i].pos_x = (i % MAP_W) * g_tip[i].grp_w;
			g_tip[i].pos_y = (i / MAP_H) * g_tip[i].grp_h;
			g_tip[i].pos_x = (float)(i % MAP_W) * g_tip[i].grp_w;
			g_tip[i].pos_y = (float)(i / MAP_H) * g_tip[i].grp_h;
			g_tip[i].spd_x = 0.0f;
			g_tip[i].spd_y = 0.0f;
			g_tip[i].state = 1;
		}
	}
}



//�X�V
void GamePlay::Update()
{

	////////////////////  �X�V����  //////////////////
	
	//���x���Z�b�g
	player->SetSpdX(0);
	if (player->GetJump() == TRUE&& player->GetClimb() == FALSE)
	{
		player->SetSpdY(player->GetSpdY() + GRAVITY);
	}
	else
	{
		player->SetSpdY(0);
	}

	//���Ƃ̔���
	Collisionfloor(player);

	if (Collision(player, lift)&&player->GetHold()==TRUE)
	{
		player->SetJump(FALSE);
		player->SetJumpPower(0.0f);
		player->SetPosX(lift->GetPosX()+player->GetGrpW());
		player->SetPosY(lift->GetPosY());
	}

	player->UpData();

	if (gimmikFlag == 0)
	{
		gimmikCnt++;
		SetSpeadToAsaaignedPosition(lift, gimmikPosAX, gimmikPosAY, 2.0f);
		if (gimmikCnt == 180)
		{
			gimmikCnt = 0;
			gimmikFlag = 1;
		}
	}

	if (gimmikFlag == 1)
	{
		gimmikCnt++;
		SetSpeadToAsaaignedPosition(lift, gimmikPosBX, gimmikPosBY, 2.0f);
		if (gimmikCnt == 180)
		{
			gimmikCnt = 0;
			gimmikFlag = 0;
		}
	}
	
	lift->UpData();

	ScrollMap();

	m_timeCount++;	//	���Ԃ̃J�E���g


	////////////////////  �L�[����  //////////////////	


	// �}�E�X�N���b�N��
	//if (g_mouse.leftButton)
	//{
	//	SetSpeadToAsaaignedPosition(player, 200.0f, 200.0f, 3.0f);//�w��ʒu�Ɉړ��֐��e�X�g
	//}

	mouseState = g_mouse.leftButton;
}


//�`��
void GamePlay::Render()
{
	//�}�E�X�J�[�\���B��
	/*ShowCursor(FALSE);*/

	RECT rect;			// �G�̍���̍��W�ƉE���̍��W�ҏW�p
	wchar_t buf[256];	// ������ҏW�p						
	wchar_t buf2[256];	// ������ҏW�p
	wchar_t buf3[256];	// ������ҏW�p

	rect = { 0, 0,640,480 };
	switch (serectMap)
	{
	case 2:
		g_spriteBatch->Draw(g_BackImage->m_pTexture,
			Vector2(0, 0));
		break;
	case 1:
		g_spriteBatch->Draw(g_BackImage2->m_pTexture,
			Vector2(0, 0));
		break;
	}
	

	//�X�e�[�W�`��
	for (int i = 0; i < MAX_TIP; i++)
	{
		if (g_tip[i].state)
		{
			rect = { g_tip[i].grp_x, g_tip[i].grp_y,
				g_tip[i].grp_x + g_tip[i].grp_w,
				g_tip[i].grp_y + g_tip[i].grp_h };

			float sx = g_tip[i].pos_x - g_ScrollMap_x;
			float sy = g_tip[i].pos_y - g_ScrollMap_y;

			g_spriteBatch->Draw(g_StageImage->m_pTexture,
				Vector2(sx, sy),
				&rect, Colors::White, 0.0f, Vector2(0, 0), 1.0f);
		}
	}

	lift->Render();

	//	 �v���C���[
	player->Render();

	rect = { 0, 0,680,96};
	g_spriteBatch->Draw(g_StateImage->m_pTexture,
		Vector2(0, 480-96),
		&rect, Colors::White, 0.0f, Vector2(0, 0), 1.0f);

	rect = { 0, 0,64,84 };
	g_spriteBatch->Draw(g_SBImage->m_pTexture,
		Vector2(40, 480 - 84),
		&rect, Colors::White, 0.0f, Vector2(0, 0), 0.8f);

	//	���ԕ\��
	if (m_timeCount % 60 == 1)
	{
		cnt++;
	}

	//�f�o�b�O�p����
	swprintf_s(buf, 16, L"X ,%d", (int)player->GetPosX());
	swprintf_s(buf2, 16, L"Y ,%d", (int)player->GetPosY());
	swprintf_s(buf3, 16, L"T ,%d", cnt);

	g_spriteFont->DrawString(g_spriteBatch.get(), buf, Vector2(0, 0));
	g_spriteFont->DrawString(g_spriteBatch.get(), buf2, Vector2(0, 16));
	g_spriteFont->DrawString(g_spriteBatch.get(), buf3, Vector2(0, 32));
}

//�}�b�v�̓ǂݍ���
void GamePlay::importData(string filename)
{
	ifstream ifs(filename);
	string str;
	int i;

	if (!ifs) {
		for (i = 0; i < MAX_TIP; i++)
		{
			g_map[i / MAP_H][i % MAP_W] = 0;
		}
		return;
	}

	i = 0;
	while (getline(ifs, str)) {
		string token;
		istringstream stream(str);

		// 1�s�̂����A������ƃR���}�𕪊�����
		while (getline(stream, token, ',')) {
			// ���ׂĕ�����Ƃ��ēǂݍ��܂�邽��
			// ���l�͕ϊ����K�v
			g_map[i / MAP_H][i % MAP_W] = atoi(token.c_str());
			i++;
		}
	}
}

//���A�V��̔���
void  GamePlay::Collisionfloor(ObjectBase* obj)
{
	//�v���C���[�̍��E���W�����߂�
	float left = obj->GetPosX() + 0.01f;
	float right = obj->GetPosX() + (obj->GetGrpW() - 0.01f);

	// �v���C���[�̑����̍��W�����߂�
	float bottom = obj->GetPosY() + (obj->GetGrpH() + 0.01f);
	//�v���C���[�̓��̔���
	float head = obj->GetPosY();
	//�v���C���[�̓��̔���
	float body = obj->GetPosY() + (obj->GetGrpH() / 2);
	// �}�b�v�̔z��̈ʒu�@
	int map_x, map_y;

	// �v���C���[�̍����̈ʒu
	map_x = (int)floor(left / CHIP_SIZE + 0.5f);
	map_y = (int)floor(bottom / CHIP_SIZE);


	
	// ���ǂ�������
	if (g_map[map_y][map_x] == 1||g_map[map_y][map_x] == 9)
	{
		if (bottom > -map_y * CHIP_SIZE + obj->GetGrpH())
		{
			if (obj->GetJump() == TRUE|| obj->GetClimb() == TRUE)
			{
				// �v���C���[�̈ʒu�����̏�Ɉړ�������
				if (obj->GetState() == 1)
				{
					if (obj->GetGrpH() == 64)
					{

						obj->SetPosY((map_y - 1) * CHIP_SIZE - 32.0f);
					}
					else
					{
						obj->SetPosY((map_y - 1) * (float)CHIP_SIZE);
					}
				}
				else
				{
					obj->SetPosY((map_y - 1) * CHIP_SIZE - 32.0f);
				}
			}
			// ���x��0�ɂ���
			obj->SetSpdY(0.0f);
			obj->SetJump(FALSE);
			obj->SetJumpPower(0);
			obj->SetState(1);

		}
	}
	else if (g_map[map_y][map_x] == 6)
	{
		obj->SetSpdY(0.0f);
		obj->SetJump(TRUE);
		obj->SetJumpPower(0);
	}
	else if (g_map[map_y][map_x] == 10)
	{
		obj->SetSpdY(0.0f);
		obj->SetJump(TRUE);
		obj->SetJumpPower(20.0f);
	}
	else
	{
		//���������Ŗ�����Δ��ł���
		obj->SetJump(TRUE);
	}

	map_y = (int)floor(head / CHIP_SIZE);
	// �V�䂾������
	if (g_map[map_y][map_x] == 1)
	{
		if (bottom > -map_y * CHIP_SIZE + obj->GetGrpH())
		{
			{// ���Ƃ�
				obj->SetJumpPower(0.0f);
				obj->SetSpdY(10.0f);
			}
		} 
	}
	//����Ƀ��[�v���͂ݏ��
	if (g_map[map_y][map_x] == 7 && player->GetHold() == TRUE)
	{
		obj->SetJumpPower(0.0f);
		obj->SetJump(FALSE);
		obj->SetSpdY(0.0f);
		obj->SetSpdX(3.0f);
	}
	
	

	map_y = (int)floor(bottom / CHIP_SIZE);

	// �v���C���[�̉E���̈ʒu
	map_x = (int)floor(right / CHIP_SIZE-0.5f);
	// ����������
	if (g_map[map_y][map_x] == 1|| g_map[map_y][map_x] == 9)
	{
		if (bottom > -map_y * CHIP_SIZE + obj->GetGrpH())
		{
			if (obj->GetJump() == TRUE)
			{
				// �v���C���[�̈ʒu�����̏�Ɉړ�������
				if (obj->GetState())
				{
					if (obj->GetGrpH() == 64)
					{
						obj->SetPosY((map_y - 1) * CHIP_SIZE - 32.0f);
					}
					else
					{
						obj->SetPosY((map_y - 1) * (float)CHIP_SIZE);
					}
				}
				else
				{
					obj->SetPosY((map_y - 1) * CHIP_SIZE - 32.0f);
				}
			}
			// ���x��0�ɂ���
			obj->SetSpdY(0.0f);
			obj->SetJump(FALSE);
			obj->SetJumpPower(0.0f);
			obj->SetState(1);
		}
	}
	else if (g_map[map_y][map_x] == 6)
	{
		obj->SetSpdY(0.0f);
		obj->SetJump(TRUE);
		obj->SetJumpPower(0);
	}
	else if (g_map[map_y][map_x] == 10)
	{
		obj->SetSpdY(0.0f);
		obj->SetJump(TRUE);
		obj->SetJumpPower(20.0f);
	}
	else
	{
		//���������Ŗ�����Δ��ł���
		obj->SetJump(TRUE);
	}


	map_y = (int)floor(head / CHIP_SIZE);
	// �V�䂾������
	if (g_map[map_y][map_x] == 1)
	{
		if (bottom > -map_y * CHIP_SIZE + obj->GetGrpH())
		{
			{// ���Ƃ�
				obj->SetJumpPower(0.0f);
				obj->SetSpdY(10.0f);
			}
		}
	}
	//����Ƀ��[�v���͂ݏ��
	if (g_map[map_y][map_x] == 7&&player->GetHold()==TRUE)
	{
		obj->SetJumpPower(0.0f);
		obj->SetJump(FALSE);
		obj->SetSpdY(0.0f);
		obj->SetSpdX(3.0f);
	}
	
}

//㩂ƃL�����N�^�[�̓����蔻��
//void  GamePlay::Collisiontrup(ObjectBase* obj)
//{
//	//�v���C���[�̍��E���W�����߂�
//	float left = obj->GetPosX() + 0.01f;
//	float right = obj->GetPosX() + (obj->GetGrpW() - 0.01f);
//
//	// �v���C���[�̑����̍��W�����߂�
//	float bottom = obj->GetPosY() + (obj->GetGrpH() + 0.01f);
//	//�v���C���[�̓��̔���
//	float head = obj->GetPosY();
//	//�v���C���[�̓��̔���
//	float body = obj->GetPosY() + (obj->GetGrpH() / 2);
//	// �}�b�v�̔z��̈ʒu�@
//	int map_x, map_y;
//
//	// �v���C���[�̍����̈ʒu
//	map_x = (int)floor(left / CHIP_SIZE + 0.5f);
//	map_y = (int)floor(bottom / CHIP_SIZE);
//}

GamePlay::~GamePlay()
{
	delete player;
}

void GamePlay::Initialize()
{
	

	
}


////////////////////////////////////////////////////////////////////////////////////
//�I�u�W�F�N�g�̌��ݒn�ƖړI�n�̍������߁A���x��{���������Đݒ肷��֐�
//�߂�l:�Ȃ�
//����:(OBJECT�^�I�u�W�F�N�g��,float�^ �ړI���WX,float�^ �ړI���WY,float�^�@���B�܂ł̎���(0.0�ŏu�ԓ��B)�j
////////////////////////////////////////////////////////////////////////////////////
void GamePlay::SetSpeadToAsaaignedPosition(ObjectBase* obj, float AposX, float AposY, float Time)
{
	//�ړI�|�C���g�Ƃ̍����L������ϐ�
	float disX = 0.0f;
	float disY = 0.0f;
	int moveFlag = 0;
	int moveCnt = 0;


	//�ϐ��ɃI�u�W�F�N�g�ƖړI�|�C���g�Ƃ̍�������
	disX = AposX - obj->GetPosX();
	disY = AposY - obj->GetPosY();

	//�I�u�W�F�N�g�̑��x�ݒ�
	//X����
	//�I�u�W�F�N�g�̃|�W�V�����ƖړI�|�C���g�ɍ����������ꍇ
	if (disX != 0.0f)
	{
		obj->SetSpdX(disX / Time / 60.0f);

	}
	else if (disX == 0.0f)
	{
		obj->SetSpdX(0.0f);
	}
	//�ړI�|�C���g���߂�����
	if ((obj->GetSpdX() > 0 && obj->GetPosX() >= AposX) || (obj->GetSpdX() < 0 && obj->GetPosX() <= AposX))
	{
		obj->SetSpdX(0);
		obj->SetPosX(AposX);
	}
	//Y����
	//�I�u�W�F�N�g�̃|�W�V�����ƖړI�|�C���g�ɍ����������ꍇ
	if (disY != 0.0f)
	{
		obj->SetSpdY(disY / Time / 60.0f);

	}
	else if (disY == 0.0f)
	{
		obj->SetSpdY(0.0f);
	}
	//�ړI�|�C���g���߂�����
	if ((obj->GetSpdY() > 0.0f && obj->GetPosY() >= AposY) || (obj->GetSpdY() < 0.0f && obj->GetPosY() <= AposY))
	{
		obj->SetSpdY(0.0f);
		obj->SetPosY(AposY);
	}
	//�I�u�W�F�N�g�������Ă���ꍇ�b�����J�E���g����
	if (obj->GetSpdY() != 0 || obj->GetSpdY() != 0)
	{
		moveFlag = 1;
	}
	if (moveFlag == 1)
	{
		moveCnt++;
		if (moveCnt / 60 == Time)//�w�莞�ԂɂȂ�����w��|�W�V�����ɋ����ړ�
		{
			obj->SetPosX(AposX);
			obj->SetPosY(AposY);
		}
	}
	obj->SetPosX(obj->GetPosX() + obj->GetSpdX());
	obj->SetPosY(obj->GetPosY() + obj->GetSpdY());
}


//�X�N���[���ʌ��o
void GamePlay::ScrollMap(void)
{

	g_ScrollMap_x = player->GetPosX() + player->GetGrpW() / 2 - SCREEN_WIDTH / 2;

	if (g_ScrollMap_x < 0|| serectMap == 1)
	{
		g_ScrollMap_x = 0;
	}
	else if (g_ScrollMap_x >(MAP_W * CHIP_SIZE - SCREEN_WIDTH))
	{
		g_ScrollMap_x = (MAP_W * CHIP_SIZE - SCREEN_WIDTH);
	}


	g_ScrollMap_y = player->GetPosY() + player->GetGrpH() / 2 - SCREEN_HEIGHT / 2;

	if (g_ScrollMap_y < 0 )
	{
		g_ScrollMap_y = 0;
	}
	//else if (g_ScrollMap_y >(MAP_H  * CHIP_SIZE - SCREEN_HEIGHT) || serectMap == 2)
	else if (g_ScrollMap_y >(MAP_H  * CHIP_SIZE - SCREEN_HEIGHT) )
	{
		g_ScrollMap_y = (MAP_H * CHIP_SIZE - SCREEN_HEIGHT);
	}
}

bool GamePlay::Collision(ObjectBase* obj1, ObjectBase*obj2)
{
	/*�l�p�`�̓����蔻��*/
	if ((obj1->GetPosX() /*- g_ScrollMap_x */ <= (obj2->GetPosX() + obj2->GetGrpW())) &&
		((obj1->GetPosX() /*- g_ScrollMap_x */+ obj1->GetGrpW()) >= obj2->GetPosX()) &&
		(obj1->GetPosY() <= (obj2->GetPosY() + obj2->GetGrpH())) &&
		((obj1->GetPosY() + obj1->GetGrpH() >= obj2->GetPosY())))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}