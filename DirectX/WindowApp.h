#pragma once
#include <Windows.h>

class WindowApp
{
public:
	int windowWidth;
	int windowHeight;
	//�E�B���h�E�v���\�W���̐���
	static LRESULT WindowProcdure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	MSG msg = {};

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="windowWidth">��ʕ�</param>
	/// <param name="windowHeight">��ʍ���</param>
	/// <param name="gameName">�^�C�g���o�[��</param>
	void Initialize(const int windowWidth, const int windowHeight, const wchar_t* gameName);

	/// <summary>
	/// �X�V
	/// </summary>
	/// <returns>�A�v���P�[�V�������I�����邩�ۂ�</returns>
	bool Update();

	/// <summary>
	/// �o�^����
	/// </summary>
	void Release();

	//�O���Ŏg��������n��
	HWND GetHwnd() { return hwnd; }
	HINSTANCE getWinInstance() { return winClass.hInstance; }

private:
	WNDCLASSEX winClass{}; // �E�B���h�E�N���X�̐ݒ�
	HWND hwnd = nullptr;
};

