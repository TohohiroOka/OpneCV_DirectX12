#include "MainEngine.h"
#include "GameScene.h"
#include "Object3d.h"
#include "Sprite.h"
#include "Emitter.h"
#include "Fbx.h"
#include "NormalMap.h"
#include "SafeDelete.h"
#include "MainOpenCV.h"

MainEngine::~MainEngine()
{
	safe_delete(camera);
	safe_delete(scene);
	DebugText::AllDelete();
	safe_delete(dXCommon);
	safe_delete(winApp);
}

//���C���ɏ����i�����������j
void MainEngine::Initialize(const wchar_t* gameName, int window_width, int window_height)
{
	
	//�E�B���h�E������
	winApp = new WindowApp();
	winApp->Initialize(window_width, window_height, gameName);

	//1�t���[���̎��Ԑݒ�
	QueryPerformanceFrequency(&timeFreq);

	// 1�x�擾���Ă���(����v�Z�p)
	QueryPerformanceCounter(&timeStart);

	//directX������
	dXCommon = new DirectXCommon();
	dXCommon->Initialize(winApp);

	//key
	input = Input::GetInstance();
	input->Initialize(winApp);

	//�J�����̏�����
	camera = new Camera(window_width, window_height);

	//Object�n�̏�����
	Object3d::StaticInitialize(dXCommon->GetDevice(), camera);
	Sprite::StaticInitialize(dXCommon->GetDevice(), window_width, window_height);
	ParticleManager::Initialize(dXCommon);
	LightGroup::StaticInitialize(dXCommon->GetDevice());
	Fbx::StaticInitialize(dXCommon->GetDevice());
	NormalMap::StaticInitialize(dXCommon->GetDevice());

	scene = new GameScene();
	scene->Initialize(input, camera);

	Sprite::LoadTexture(0, L"Resources/LetterResources/debugfont.png");

	//�[�x�̏�����
	dXCommon->CreateDepth(winApp);

}

//���C���ɏ����i�X�V�����j
bool MainEngine::Update()
{
	input->Update();

	//�G�X�P�[�v���~�������ꂽ�Ƃ��Q�[���I��
	if (gameFin(winApp) == true)
	{
		return true;
	}

	//�X�V
	scene->Update(camera);

	//�`��O�ݒ�
	dXCommon->BeforeDraw(winApp);

	//�`��
	scene->Draw(dXCommon->getcmdList());

	return false;
}

//�f�o�b�O�p����
void MainEngine::debugNum(float x, float y, float z)
{
	//�����̃f�o�b�O
	swprintf_s(str, L"%f,%f,%f\n", x, y, z);
	OutputDebugString(str);
}

//���C���ɏ����i�`�揈���j
void MainEngine::draw() {
	//�R�}���h���s
	dXCommon->AfterDraw();
}

void MainEngine::frameRateKeep() {
	// ���̎��Ԃ��擾
	QueryPerformanceCounter(&timeEnd);
	// (���̎��� - �O�t���[���̎���) / ���g�� = �o�ߎ���(�b�P��)
	frameTime = static_cast<float>(timeEnd.QuadPart - timeStart.QuadPart) / static_cast<float>(timeFreq.QuadPart);

	if (frameTime < MIN_FREAM_TIME) { // ���Ԃɗ]�T������
		// �~���b�ɕϊ�
		DWORD sleepTime = static_cast<DWORD>((MIN_FREAM_TIME - frameTime) * 1000);

		timeBeginPeriod(1); // ����\���グ��(�������Ȃ���Sleep�̐��x�̓K�^�K�^)
		Sleep(sleepTime);   // �Q��
		timeEndPeriod(1);   // �߂�

		// ���T�Ɏ����z��(�������Ȃ���fps���ςɂȂ�?)
		return;
	}

	if (frameTime > 0.0) { // �o�ߎ��Ԃ�0���傫��(�������Ȃ��Ɖ��̌v�Z�Ń[�����Z�ɂȂ�Ǝv���)
		fps = (fps * 0.99f) + (0.01f / frameTime); // ����fps���v�Z
#ifdef _DEBUG
// �f�o�b�O�p(�f�o�b�K��FSP�o��)
#ifdef UNICODE
		std::wstringstream stream;
#else
		std::stringstream stream;
#endif
		stream << fps << " FPS" << std::endl;
		// �J�E���^�t����10���1��o�́A�Ƃ��ɂ��Ȃ��ƌ��Â炢������
		OutputDebugString(stream.str().c_str());
#endif // _DEBUG
	}

	timeStart = timeEnd; // ����ւ�
}

//���C���ɏ����i�G�X�P�[�v�����͂��ꂽ��I�����鏈���j
bool MainEngine::gameFin(WindowApp* winApp) {
	//�~�������ꂽ�Ƃ�
	if (input->PushKey(DIK_ESCAPE) || winApp->Update() == true) {
		//MainOpenCV::End();
		return true;
	} else { return false; }

}