//--------------------------------------------------------------------------------------
// File: DirectXTK.cpp
//
// DirectXTK�Ɋւ���֐��Q
//
// Date: 2015.8.27
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "Direct3D.h"
#include "DirectXTK.h"


using namespace DirectX;

//////////////////////////////////
// �����N���郉�C�u�����w��		//
//////////////////////////////////
#pragma comment(lib, "DirectXTK.lib")

//////////////////////
// �ÓI�ϐ�			//
//////////////////////
static std::unique_ptr<Keyboard> s_keyboard(new Keyboard);
static std::unique_ptr<Mouse> s_mouse(new Mouse);
std::unique_ptr<CommonStates> g_pCommonStates;


//////////////////////
// �O���[�o���ϐ�	//
//////////////////////

// �L�[�{�[�h�֌W
Keyboard::State g_key;
std::unique_ptr<Keyboard::KeyboardStateTracker> g_keyTracker(new Keyboard::KeyboardStateTracker);

// �}�E�X�֌W
Mouse::State g_mouse;
std::unique_ptr<Mouse::ButtonStateTracker> g_mouseTracker(new Mouse::ButtonStateTracker);

// �X�v���C�g�o�b�`
std::unique_ptr<SpriteBatch> g_spriteBatch;

// �X�v���C�g�t�H���g
std::unique_ptr<SpriteFont> g_spriteFont;

//--------------------------------------------------------------------------------------
// ������
//--------------------------------------------------------------------------------------
void DirectXTK_Initialize()
{
	// �X�v���C�g�o�b�`
	g_spriteBatch.reset(new SpriteBatch(g_pImmediateContext.Get()));

	// �X�v���C�g�t�H���g
	g_spriteFont.reset(new SpriteFont(g_pd3dDevice.Get(), L"myfile.spritefont"));

	g_pCommonStates.reset(new CommonStates(g_pd3dDevice.Get()));
}

//--------------------------------------------------------------------------------------
// �L�[���͂�}�E�X���̍X�V
//--------------------------------------------------------------------------------------
void DirectXTK_UpdateInputState()
{
	// �L�[���͏����擾
	g_key = s_keyboard->GetState();
	g_keyTracker->Update(g_key);

	// �}�E�X�����擾
	g_mouse = s_mouse->GetState();
	g_mouseTracker->Update(g_mouse);
}
