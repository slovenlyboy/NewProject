//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   player.cpp
//!
//! @brief  プレイヤー関連のソースファイル
//!
//! @date   2017/4/5
//!
//! @author Yuhei M	
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#include"GameMain.h"
#include "Player.h"
#include<string>
#include<sstream>
#include<fstream>
#include<iostream>
#include "../ADX2Le.h"



using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace std;



Player::Player()
{
	SetHandle(g_PlayerImage);
	SetGrpX(0);
	SetGrpY(0);
	SetGrpW(32);
	SetGrpH(32);
	SetPosX(32);
	SetPosY(32);
	SetSpdX(0.0f);
	SetSpdY(0.0f);
	SetState(1);
	SetJump(FALSE);
	SetClimb(FALSE);
	SetHold(FALSE);
}


Player::~Player()
{
}


void Player::SetHandle(Texture* h)
{
	handle = h;

}

Texture* Player::GetHandle()
{
	return handle;

}


void Player::SetPosX(float x)
{
	pos_x = x;
}

float Player::GetPosX()
{
	return pos_x;
}
void Player::SetPosY(float y)
{
	pos_y = y;

}
float Player::GetPosY()
{
	return pos_y;
}


void Player::SetGrpX(int x)
{
	grp_x = x;
}
int Player::GetGrpX()
{
	return grp_x;
}


void Player::SetGrpY(int y)
{
	grp_y = y;
}
int Player::GetGrpY()
{
	return grp_y;
}


void Player::SetGrpW(int w)
{
	grp_w = w;

}
int Player::GetGrpW()
{

	return grp_w;
}

void Player::SetGrpH(int h)
{
	grp_h = h;
}
int Player::GetGrpH()
{
	return grp_h;
}


void Player::SetSpdX(float x)
{
	spd_x = x;
}
float Player::GetSpdX()
{
	return spd_x;
}

void Player::SetSpdY(float y)
{
	spd_y = y;
}
float Player::GetSpdY()
{
	return spd_y;
}

void Player::SetState(int s)
{
	state = s;
}
int Player::GetState()
{

	return state;
}


void  Player::SetJumpPower(float y)
{
	jumpPower = y;
}
float  Player::GetJumpPower()
{
	return jumpPower;
}


void  Player::SetJump(int s)
{
	jump = s;
}
int  Player::GetJump()
{
	return jump;
}



void Player::SetClimb(int s)
{
	climb = s;
}
int Player::GetClimb()
{
	return climb;
}

void Player::SetHold(int s)
{
	hold = s;
}
int Player::GetHold()
{

	return hold;
}



void Player::SetDir(int s)
{
	dir = s;
}
int Player::GetDir()
{
	return dir;
}




void Player::UpData()
{
	PlayerControl();

	if (GetSpdX() != 0 || GetSpdY() != 0)
	{
		m_cnt++;
	}
	else
	{
		m_cnt = 0;
	}

	if (GetState() == 2)
	{
		m_actCnt++;
	}
	
	if (m_actCnt > 60)
	{
		SetState(1);
		m_actCnt = 0;
	}
	if (soundFlag != 0)
	{

		soundCnt++;

		switch (soundFlag)
		{
		case 1:
			ADX2Le::Play(Walk1);
			soundSet = 20;
			break;
		case 2:
			ADX2Le::Play(Walk2);
			soundSet = 20;
			break;
		case 3:
			ADX2Le::Play(UpLadder);
			soundSet = 20;
			break;

		}

		soundFlag = 20;


		if (soundCnt >= soundSet)
		{

			soundFlag = 0;
			soundCnt = 0;
		}

	}






}

void Player::Render()
{
	RECT rect;			// 絵の左上の座標と右下の座標編集用


	//左に移動してるなら左に動き、右に移動しているなら右に動く

	switch (GetDir())
	{
	case LEFT:
		SetGrpY(32);
		break;
	case RIGHT:
		SetGrpY(64);
		break;
	}
	

	if (GetJump() == FALSE)
	{
		//左右に移動している場合
		if (GetSpdX() != 0)
		{
			if (soundFlag == 0&&GetHold()==FALSE)
			{
				if (serectMap == 1)soundFlag = 1;

				if (serectMap == 2)soundFlag = 2;
			}
			//移動してる場合歩く
			switch (m_cnt / 15 % 4)
			{
			case 0:
				SetGrpX(0);
				break;
			case 1:
			case 3:
				SetGrpX(32);
				break;
			case 2:
				SetGrpX(64);
				break;
			}
		}
	}

	//上下に動いているなら（ジャンプを除く）
	if (GetClimb() == TRUE)
	{
		SetGrpY(96);


		//移動してる場合歩く
		switch (m_cnt / 15 % 4)
		{
		case 0:
			SetGrpX(0);
			break;
		case 1:
		case 3:
			SetGrpX(32);
			break;
		case 2:
			SetGrpX(64);
			break;
		}
	}

	
		rect =
		{
			GetGrpX(),
			GetGrpY(),
			GetGrpX() + GetGrpW() ,
			GetGrpY() + GetGrpH()
		};
	

	float sx = GetPosX() - g_ScrollMap_x;
	float sy = GetPosY() - g_ScrollMap_y;


	g_spriteBatch->Draw(g_PlayerImage->m_pTexture,
		Vector2(sx, sy),
		&rect, Colors::White, 0.0f, Vector2(0, 0), 1.0f);

	RECT CPrect;
	if (GetGrpY() == 32 || GetGrpY() == 64)
	{
		if (GetGrpY() == 32)
		{
			if (g_key.Z)
			{
				CPrect = { 0,0,32,32 };
			}
			else
			{
				CPrect = { 32,0,64,32 };
			}
			if (GetJump() == true)
			{
				g_spriteBatch->Draw(g_PlayerClothesPins->m_pTexture,
					Vector2(sx - 10 + 48, sy),
					&CPrect, Colors::White, 90.0f, Vector2(0, 0), 1.0f);
			}
			else
			{
				g_spriteBatch->Draw(g_PlayerClothesPins->m_pTexture,
					Vector2(sx - 10, sy),
					&CPrect, Colors::White, 0.0f, Vector2(0, 0), 1.0f);
			}

		}
		else
		{
			if (g_key.Z)
			{
				CPrect = { 0,32,32,64 };
			}
			else
			{
				CPrect = { 32,32,64,64 };
			}

			if (GetJump() == true)
			{
				g_spriteBatch->Draw(g_PlayerClothesPins->m_pTexture,
					Vector2(sx + 10, sy +32),
					&CPrect, Colors::White, -90.0f, Vector2(0, 0), 1.0f);
			}
			else
			{
				g_spriteBatch->Draw(g_PlayerClothesPins->m_pTexture,
					Vector2(sx + 10, sy),
					&CPrect, Colors::White, 0.0f, Vector2(0, 0), 1.0f);
			}

		}
	}

}

//プレイヤー操作
void Player::PlayerControl(void)
{
	float spd = 2.0f;
	float jumpPower = -12.0f;

	//キー入力

	int index_x = (int)GetPosX() / CHIP_SIZE;//マップに対するプレイヤーのX座標
	int index_y = ((int)GetPosY() + (int)GetGrpH()) / CHIP_SIZE;//マップに対するプレイヤーのY座標
	
	if (GetState() != 0)
	{
		if (g_key.Right)//右キー押下
		{

			int* mapdata = &g_map[index_y - 1][index_x + 1];//プレイヤーの右側のマップチップ判定

			


			if (GetHold() == FALSE)
			{
				SetDir(RIGHT);
			}
			
			if (*mapdata == 0 || *mapdata == 2 || *mapdata == 3 || *mapdata == 4|| *mapdata == 6 || *mapdata == 8|| *mapdata == 12 || *mapdata == 13 || *mapdata == 16)//移動可能マップチップ
			{
				SetSpdX(spd);
				SetClimb(FALSE);
				if (*mapdata == 2|| *mapdata == 12)//ゴールのチップ番号指定
				{
					g_NextScene = CLEAR;
				}
			}
		}
		else if (g_key.Left)//左キー押下
		{
			if (GetHold() == FALSE)
			{
				SetDir(LEFT);
			}
			int* mapdata = &g_map[index_y - 1][index_x];//プレイヤーの左のマップチップ判定

			
		
			if (*mapdata == 0 || *mapdata == 2 || *mapdata == 3 || *mapdata == 4 || *mapdata == 6 || *mapdata == 8 || *mapdata == 12 || *mapdata == 13 || *mapdata == 16)
			{

				SetSpdX(-spd);
				SetClimb(FALSE);
				if (*mapdata == 2 || *mapdata == 12)//ゴールのチップ番号指定
				{
					g_NextScene = CLEAR;
				}
			}

		}

		//梯子昇降
		if (g_key.Up)//上キー押下
		{
			int* mapdata = &g_map[index_y - 1][index_x + 1];//プレイヤーの右側のマップチップ
			int* mapdata2 = &g_map[index_y - 1][index_x];//プレイヤーの左のマップチップ判定
			if (*mapdata == 6 || *mapdata2 == 6)//移動可能マップチップ
			{
				SetSpdY(-spd);
				SetClimb(TRUE);
			}
			if (soundFlag == 0)
			{
				soundFlag = 3;
			}
		}
		else if (g_key.Down)//上キー押下
		{
			int* mapdata = &g_map[index_y - 1][index_x + 1];//プレイヤーの右側のマップチップ
			int* mapdata2 = &g_map[index_y - 1][index_x];//プレイヤーの左のマップチップ判定
			if (*mapdata == 6 || *mapdata2 == 6)//移動可能マップチップ
			{

				SetSpdY(spd);
				SetClimb(TRUE);
			}
			if (soundFlag == 0)
			{
				soundFlag = 3;
			}
		}
		if (g_keyTracker->pressed.Z)
		{
			ADX2Le::Play(SAND,2.0f);
		}

		if (g_key.Z)//Zキー押下時
		{
			//はさみ状態にする
			
			SetHold(TRUE);

		}
		else//離したら
		{
			//はさみ状態解除
			SetHold(FALSE);
		}
	

		//スペースキーでジャンプ
		if (g_keyTracker->pressed.Space&&GetState() == 1 && GetJump() == FALSE)
		{
			ADX2Le::Play(Jump);
			SetJump(TRUE);
			SetJumpPower(jumpPower);
		}


		//プレイヤーキャラの移動
		//座標変更処理/////////////////////////////
		SetPosX(GetPosX() + GetSpdX());
		SetPosY(GetPosY() + GetSpdY() + GetJumpPower());

		

		//移動してない場合両手をもとに戻す
		if (GetSpdX() == 0)
		{
			SetGrpX(32);
		}

		

		//状態による変更
		switch (GetState())
		{
		case 1:
			break;
		default:
			break;

		}
	}

}
