#include "MainOpenCV.h"
#include "MainEngine.h"
#include <iostream>

using namespace std;
using namespace cv;

MainOpenCV* instance = nullptr;
VideoCapture MainOpenCV::cap = {};
Mat MainOpenCV::frame = {};
int MainOpenCV::isCascade = 0;
CascadeClassifier MainOpenCV::cascade = {};
vector<cv::Rect> MainOpenCV::contour = {};

MainOpenCV::~MainOpenCV()
{
	//���ׂẴE�B���h�E�����
	destroyAllWindows();
}

//�V���O���g���p�^�[��
MainOpenCV* MainOpenCV::GetInstance()
{
	static MainOpenCV instance;
	return &instance;
}

void MainOpenCV::Initialize()
{
	//�J�����̃Z�b�g
	cap = 2;

	//�J�����f�o�C�X������ɃI�[�v���������m�F
	if (!cap.isOpened())
	{
		//�ǂݍ��݂Ɏ��s�����Ƃ��̓G���[���o��
		assert(0);
	}

	//�J�X�P�[�h���ފ�̓ǂݍ���
	cascade.load("OpenCV/haarcascades/haarcascade_frontalface_default.xml");
}

void MainOpenCV::Update()
{
	//�ʒu�t���[����ϐ��ɕۑ�
	cap.read(frame);

	//�Ώۂ̌��o
	isCascade++;
	if (isCascade % 51 == 50)
	{
		cascade.detectMultiScale(frame, contour, 1.1, 5, 0, cv::Size(30, 30));
		isCascade = 0;
	}

	//���o�����J��Ԃ�
	for (int i = 0; i < contour.size(); i++)
	{
		//��`�̉���
		rectangle(frame, Point(contour[i].x, contour[i].y),
			Point(contour[i].x + contour[i].width, contour[i].y + contour[i].height), Scalar(255, 255, 255), 1);
	}
}

void MainOpenCV::Draw()
{
	imshow("camera4", frame);
}