#pragma once

#include "Sprite.h"
#include <Windows.h>
#include <string>

/// <summary>
/// �f�o�b�O�p�����\��
/// </summary>
class DebugText
{
public:
	// �f�o�b�O�e�L�X�g�p�̃e�N�X�`���ԍ����w��
	static const int maxCharCount = 256;	// �ő啶����
	static const int fontWidth = 9;			// �t�H���g�摜��1�������̉���
	static const int fontHeight = 18;		// �t�H���g�摜��1�������̏c��
	static const int fontLineCount = 14;	// �t�H���g�摜��1�s���̕�����
	static const int bufferSize = 256;	// �����t��������W�J�p�o�b�t�@�T�C�Y

private://�ÓI�����o�ϐ�

	// �X�v���C�g�f�[�^�̔z��
	static Sprite* spriteDatas[maxCharCount];


public:// �ÓI�����o�֐�

	/// <summary>
	/// �C���X�^���X�̐���
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static DebugText* GetInstance();

	/// <summary>
	/// �������
	/// </summary>
	static void AllDelete();

public:// �����o�֐�

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="texnumber">�g���e�N�X�`���̔ԍ�</param>
	void Initialize(UINT texnumber);

	/// <summary>
	/// �ʒu�̃Z�b�g
	/// </summary>
	/// <param name="x">x��</param>
	/// <param name="y">y��</param>
	inline void SetPos(float x, float y) {
		posX = x;
		posY = y;
	}

	inline void SetSize(float size) { this->size = size; }

	/// <summary>
	/// �o�͂��镶���̐ݒ�
	/// </summary>
	/// <param name="text">����</param>
	/// <param name="x">x���̈ʒu</param>
	/// <param name="y">y���̈ʒu</param>
	/// <param name="size">�傫��</param>
	void Print(const std::string& text, float x, float y, float size);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="len">������̒���</param>
	/// <param name="text">�o�͂��镶��</param>
	void NPrint(int len, const char* text);

	/// <summary>
	/// �S�Ă̕`��
	/// </summary>
	/// <param name="cmdList">�R�}���h���X�g</param>
	void DrawAll(ID3D12GraphicsCommandList* cmdList);

private:
	DebugText();
	DebugText(const DebugText&) = delete;
	~DebugText();
	DebugText& operator=(const DebugText&) = delete;

private:
	// �X�v���C�g�f�[�^�z��̓Y�����ԍ�
	int spriteIndex = 0;

	float posX = 0.0f;
	float posY = 0.0f;
	float size = 1.0f;

	char buffer[bufferSize];
};