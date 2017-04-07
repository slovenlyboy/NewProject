//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   ObjectBase.h
//!
//! @brief  �I�u�W�F�N�g�̃w�b�_�t�@�C��
//!
//! @date   2017/4/5
//!
//! @author Yuhei M	
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once
#include "../DirectXTK.h"
#include "../Texture.h"

class ObjectBase
{
public:
	ObjectBase();
	~ObjectBase();


	//���̃Z�b�g�y�ю擾�̉��z�֐�

	virtual void UpData() = 0;
	virtual void Render() = 0;

	virtual void SetHandle(Texture* h) = 0;
	virtual Texture* GetHandle() = 0;
	virtual void SetPosX(float x) = 0;
	virtual float GetPosX() = 0;

	virtual void SetPosY(float y) = 0;
	virtual float GetPosY() = 0;

	virtual void SetGrpX(int x) = 0;
	virtual int GetGrpX() = 0;

	virtual void SetGrpY(int y) = 0;
	virtual int GetGrpY() = 0;

	virtual void SetGrpW(int w) = 0;
	virtual int GetGrpW() = 0;

	virtual void SetGrpH(int h) = 0;
	virtual int GetGrpH() = 0;

	virtual void SetSpdX(float x) = 0;
	virtual float GetSpdX() = 0;

	virtual void SetSpdY(float y) = 0;
	virtual float GetSpdY() = 0;

	virtual void SetJumpPower(float y) = 0;
	virtual float GetJumpPower() = 0;

	virtual void SetState(int s) = 0;
	virtual int GetState() = 0;

	virtual void SetJump(int s) = 0;
	virtual int GetJump() = 0;


	
protected:
	

	Texture* handle; //�e�N�X�`���n���h��
	int grp_x;//���摜��x���W 
	int grp_y;//���摜��y���W 
	int grp_w;//���摜�̕� 
	int grp_h;//���摜�̍��� 
	float pos_x;//���Wx
	float pos_y;//���Wy 
	float spd_x;//���xx 
	float spd_y;//���xy 
	float jumpPower;//�W�����v��
	int state;//���
	int jump;//���ł邩�H
	
};