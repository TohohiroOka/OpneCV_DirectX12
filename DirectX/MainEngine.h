#pragma once
#include "WindowApp.h"
#include "DirectXCommon.h"
#include "GameScene.h"
#include"Input.h"
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")
#include<sstream>
#include <iomanip>

using namespace DirectX;
using namespace Microsoft::WRL;

class MainEngine
{
public://�N���X�����Ŏg�p����
	//�[�x����
	void afterInit();

public://���C���ɏ���

	MainEngine() = default;
	~MainEngine();

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="gameName">�^�C�g���o�[��</param>
	/// <param name="window_width">��ʕ�</param>
	/// <param name="window_height">��ʍ���</param>
	void Initialize(const wchar_t* gameName, int window_width, int window_height);

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <returns>�Q�[���𑱂��邩</returns>
	bool Update();

	/// <summary>
	/// �f�o�b�O�p����
	/// </summary>
	/// <param name="x">�l1</param>
	/// <param name="y">�l2</param>
	/// <param name="z">�l3</param>
	void debugNum(float x, float y, float z);

	/// <summary>
	/// �`��
	/// </summary>
	void draw();

	/// <summary>
	/// �t���[�����[�g�Œ�
	/// </summary>
	void frameRateKeep();

	/// <summary>
	/// �G�X�P�[�v�����͂��ꂽ��I�����鏈��
	/// </summary>
	/// <param name="winApp">�E�B���h�E�Y�C���X�^���X</param>
	/// <returns>�Q�[���𑱂��邩</returns>
	bool gameFin(WindowApp* winApp);

	/// <summary>
	/// DirectXCommon��getter
	/// </summary>
	/// <returns>DirectXCommon�̃C���X�^���X</returns>
	DirectXCommon* GetDXCommon() { return dXCommon; }

	/// <summary>
	/// Input��getter
	/// </summary>
	/// <returns>Input�̃C���X�^���X</returns>
	Input* GetInput() { return input; }

	/// <summary>
	/// Camera��getter
	/// </summary>
	/// <returns>Camera�̃C���X�^���X</returns>
	Camera* GetCamera() { return camera; }

	/// <summary>
	/// ���݂̎��Ԏ擾
	/// </summary>
	/// <returns></returns>
	LARGE_INTEGER GetTime() { return timeEnd; }

private:

	//WindowApp�̃C���X�^���X
	WindowApp* winApp = nullptr;
	//DirectXCommon�̃C���X�^���X
	DirectXCommon* dXCommon = nullptr;
	//Input�̃C���X�^���X
	Input* input = nullptr;
	//Camera�̃C���X�^���X
	Camera* camera = nullptr;
	//GameScene�̃C���X�^���X
	GameScene* scene = nullptr;
	//�����\���f�o�b�O�p
	wchar_t str[256] = {};
	//�t���[�����[�g�Œ�p
	const float MIN_FREAM_TIME = 1.0f / 60;
	//�t���[���̃J�E���g
	float frameTime = 0;
	//�t���[���n��
	LARGE_INTEGER timeStart;
	//�t���[���Ō�
	LARGE_INTEGER timeEnd;
	//���݃t���[��
	LARGE_INTEGER timeFreq;
	//����FPS
	float fps = 0;
};