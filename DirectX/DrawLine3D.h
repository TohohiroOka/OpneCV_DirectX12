#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>

class Camera;

class DrawLine3D
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public://�\���̐錾
	//�萔�o�b�t�@�̍\����
	struct ConstBufferData {
		XMFLOAT4 color;//�F
		XMMATRIX matWorld;//3D�ϊ��s��
		XMMATRIX matView;//3D�ϊ��s��
		XMMATRIX maProjection;//3D�ϊ��s��
	};

	//���_�f�[�^3D
	struct Vertex {
		XMFLOAT3 pos;
	};

private://�ÓI�����o�֐�

	/// <summary>
	/// �p�C�v���C������
	/// </summary>
	static void Pipeline();

	/// <summary>
	/// �p�x�����߂�
	/// </summary>
	/// <param name="startPoint">�n�_</param>
	/// <param name="endPoint">�I�_</param>
	/// <returns>��_�Ԃ̊p�x</returns>
	float GetAngle(XMFLOAT3 startPoint, XMFLOAT3 endPoint);

public://�ÓI�����o�֐�

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <returns></returns>
	DrawLine3D() {};

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~DrawLine3D();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="device">�f�o�C�X</param>
	static void StaticInitialize(ID3D12Device* device);

	/// <summary>
	/// Object�̐���
	/// </summary>
	static DrawLine3D* Create();

	/// <summary>
	/// �`��O����
	/// </summary>
	/// <param name="cmdList">�`��R�}���h���X�g</param>
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// �`��㏈��
	/// </summary>
	static void PostDraw();

public://�����o�֐�

	/// <summary>
	/// ������
	/// </summary>
	/// <returns>����</returns>
	bool Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="camera">�J�����̃C���X�^���X</param>
	void Update(Camera* camera);

	/// <summary>
	/// ���̏��Z�b�g
	/// </summary>
	/// <param name="startPoint">�n�_</param>
	/// <param name="endPoint">�I�_</param>
	/// <param name="color">�F</param>
	/// <param name="width">���̕�</param>
	void SetLine(DirectX::XMFLOAT3 startPoint, DirectX::XMFLOAT3 endPoint, XMFLOAT4 color, float width);

	/// <summary>
	/// //�`��
	/// </summary>
	void Draw();


private://�ÓI�����o�ϐ�

	// ���_��
	static const int vertNum = 4;
	// �C���f�b�N�X��
	static const int indexNum = 12;
	//�f�o�C�X
	static ID3D12Device* device;
	//�R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList;
	//�p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState>pipelineState;
	//���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature>rootSignature;

protected://�����o�ϐ�

	//���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//�C���f�b�N�X�o�b�t�@
	ComPtr<ID3D12Resource> indexBuff;
	//�C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView{};
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff;
	// �F
	XMFLOAT4 color = {};
};