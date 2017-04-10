#include "Gimmik.h"
#include "Game\GameMain.h"
#include <string>



using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace std;



Gimmik::Gimmik()
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


Gimmik::~Gimmik()
{

}


void Gimmik::SetHandle(Texture* h)
{
	handle = h;
}

Texture* Gimmik::GetHandle()
{
	return handle;
}


void Gimmik::SetPosX(float x)
{
	pos_x = x;
}

float Gimmik::GetPosX()
{
	return pos_x;
}
void Gimmik::SetPosY(float y)
{
	pos_y = y;

}
float Gimmik::GetPosY()
{
	return pos_y;
}


void Gimmik::SetGrpX(int x)
{
	grp_x = x;
}
int Gimmik::GetGrpX()
{
	return grp_x;
}


void Gimmik::SetGrpY(int y)
{
	grp_y = y;
}
int Gimmik::GetGrpY()
{
	return grp_y;
}


void Gimmik::SetGrpW(int w)
{
	grp_w = w;

}
int Gimmik::GetGrpW()
{

	return grp_w;
}

void Gimmik::SetGrpH(int h)
{
	grp_h = h;
}
int Gimmik::GetGrpH()
{
	return grp_h;
}


void Gimmik::SetSpdX(float x)
{
	spd_x = x;
}
float Gimmik::GetSpdX()
{
	return spd_x;
}

void Gimmik::SetSpdY(float y)
{
	spd_y = y;
}
float Gimmik::GetSpdY()
{
	return spd_y;
}

void Gimmik::SetState(int s)
{
	state = s;
}
int Gimmik::GetState()
{

	return state;
}


void  Gimmik::SetJumpPower(float y)
{
	jumpPower = y;
}

float  Gimmik::GetJumpPower()
{
	return jumpPower;
}


void  Gimmik::SetJump(int s)
{
	jump = s;
}

int  Gimmik::GetJump()
{
	return jump;
}


void Gimmik::UpData()
{
	GimmikControl();

}


void Gimmik::SetClimb(int s)
{
	climb = s;
}
int Gimmik::GetClimb()
{
	return climb;
}

void Gimmik::SetHold(int s)
{
	hold = s;
}
int Gimmik::GetHold()
{

	return hold;
}

void Gimmik::SetDir(int s)
{
	dir = s;
}

int Gimmik::GetDir()
{
	return dir;
}

void Gimmik::Render()
{

	if (serectMap == 1)
	{
		SetGrpX(416);
		SetGrpY(0);
		SetGrpW(32);
		SetGrpH(32);
	}


		// 絵の左上の座標と右下の座標編集用
	RECT rect;

	rect =
	{
		GetGrpX(),
		GetGrpY(),
		GetGrpX() + GetGrpW() ,
		GetGrpY() + GetGrpH()
	};

	float sx = GetPosX() - g_ScrollMap_x;
	float sy = GetPosY() - g_ScrollMap_y;

	switch (serectMap)
	{
	case 1:
		g_spriteBatch->Draw(g_StageImage->m_pTexture,
			Vector2(sx, sy),
			&rect, Colors::White, 0.0f, Vector2(0, 0), 1.0f);
		break;
	case 2:
		g_spriteBatch->Draw(g_RopeImage->m_pTexture, Vector2(sx, sy -298));
		break;
	}
	

}

//プレイヤー操作
void Gimmik::GimmikControl()
{
	if (GetState() != 0)
	{
		//座標変更処理/////////////////////////////
		SetPosX(GetPosX() + GetSpdX());
		SetPosY(GetPosY() + GetSpdY() + GetJumpPower());
	}
}