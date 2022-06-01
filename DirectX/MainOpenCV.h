#pragma once

#include <opencv2/opencv.hpp>

class MainOpenCV
{
public://�ÓI�����o�֐�

private://�V���O���g���p�^�[��
	MainOpenCV() = default;
	~MainOpenCV();

public://�V���O���g���p�^�[��
	MainOpenCV(const MainOpenCV& mainOpenCV) = delete;
	MainOpenCV& operator=(const MainOpenCV& mainOpenCV) = delete;

	/// <summary>
	/// �C���X�^���X�̎擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static MainOpenCV* GetInstance();

	/// <summary>
	/// ������
	/// </summary>
	static void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	static void Update();

	/// <summary>
	/// �`��
	/// </summary>
	static void Draw();

private://�ÓI�����o�ϐ�

	MainOpenCV* instance;
	//�J�����ۑ��p�ϐ�
	static cv::VideoCapture cap;
	//�J�����̍Đ��t���[��
	static cv::Mat frame;
	//���ފ�ɂ�����^�C�~���O
	static int isCascade;
	//�J�X�P�[�h���ފ�i�[�p
	static cv::CascadeClassifier cascade;
	//��`�i�[�p
	static std::vector<cv::Rect> contour;
};