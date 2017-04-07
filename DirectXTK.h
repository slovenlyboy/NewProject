//--------------------------------------------------------------------------------------
// File: DirectXTK.h
//
// DirectXTK�Ɋւ���֐��Q
//
// Date: 2015.8.27
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include <Windows.h>
#include <Keyboard.h>
#include <Mouse.h>
#include <SpriteFont.h>
#include <CommonStates.h>

//////////////////////////////
// �֐��̃v���g�^�C�v�錾	//
//////////////////////////////
void DirectXTK_Initialize();
void DirectXTK_UpdateInputState();

//////////////////////////////
// �O���[�o���ϐ�			//
//////////////////////////////

// �L�[�{�[�h�֌W
extern DirectX::Keyboard::State g_key;
extern std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> g_keyTracker;

// �}�E�X�֌W
extern DirectX::Mouse::State g_mouse;
extern std::unique_ptr<DirectX::Mouse::ButtonStateTracker> g_mouseTracker;

// �X�v���C�g�o�b�`
extern std::unique_ptr<DirectX::SpriteBatch> g_spriteBatch;

// �X�v���C�g�t�H���g
extern std::unique_ptr<DirectX::SpriteFont> g_spriteFont;

extern std::unique_ptr<DirectX::CommonStates> g_pCommonStates;