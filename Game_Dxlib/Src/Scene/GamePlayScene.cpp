#include "GamePlayScene.h"
#include "Rendering/Field.h"
#include "Assets.h"
#include "Actor/Camera/Camera.h"
#include "Actor/Player/Player.h"
#include "Actor/Light/Light.h"
#include "Mylib/DXlib_Input/InputManager.h"

#include "Ball.h"


void GamePlayScene::load()
{

	//Assets::Mesh_Skydome = MV1LoadModel("");
	Assets::Mesh_Field = MV1LoadModel("Assets/Model/Field/room100.mv1");
	//Assets::Mesh_Player = MV1LoadModel("");
	//Assets::VShader_MMD = LoadVertexShader("");
	//Assets::PShader_MMD = LoadPixelShader("");
	//Assets::VShader_Normal = LoadVertexShader("");
	//Assets::PShader_Normal = LoadPixelShader("");
	//Assets::Texture_GradPlayer = LoadGraph("");

}

//�J�n
void GamePlayScene::start() {
	//�}�E�X�J�[�\�����\��
	SetMouseDispFlag(FALSE);

	//�X�J�C�h�[����Z�o�b�t�@���g��Ȃ�
	MV1SetUseZBuffer(Assets::Mesh_Skydome, FALSE);
	MV1SetScale(Assets::Mesh_Field, VGet(0.1f, 0.1f, 0.1f));
	// �t�B�[���h�N���X�̒ǉ�
	world_.add_field(new Field{});
	//�J�����N���X�̒ǉ�
	world_.add_camera(new Camera{ &world_,GSvector3{0.0f,0.0f,0.0f} ,GSvector3{0.0f, 1.93f, 0.0f} });
	//���C�g�N���X�̒ǉ�
	world_.add_light(new Light{ &world_ });
	//�v���C���̒ǉ�
	world_.add_actor(new Player{ &world_,Assets::Mesh_Player,GSvector3{2.0f,0.0f,20.0f} });

	world_.add_actor(new Ball(&world_, GSvector3{ 2.0f,10.0f,20.0f },0.8f));

	//�I���t���O��������
	is_end_ = false;
	
}

//�X�V
void GamePlayScene::update(float delta_time) 
{
	//�G���^�[�L�[�ŏI���Ƃ��Ă���
	if (InputManager::GetInputDown(InputType::KEY, KEY_INPUT_RETURN)) {
			is_end_ = true; //�V�[���I��
	}

	//���[���h�̍X�V
	world_.update(delta_time);
	//�X�J�C�h�[���̍��W���J�����ʒu��
	MV1SetPosition(Assets::Mesh_Skydome, world_.camera()->transform().position().VECTOR_);
}



//�`��
void GamePlayScene::draw()const {
	//�X�J�C�h�[���̕`��
	MV1DrawModel(Assets::Mesh_Skydome);
	//�V���h�E�}�b�v�̎g�p
	//SetUseShadowMap(0, Shadow_Handle);
	//���[���h�̕`��
	world_.draw();
	//�V���h�E�}�b�v�̉���
	//SetUseShadowMap(0, -1);

	DrawString(80, 215, "�v���C�V�[���i���j", GetColor(255, 255, 255));
	
	
}

//�I�����Ă��邩�H
bool GamePlayScene::is_end()const {
	return is_end_; //�I���t���O��Ԃ�
}

//���̃V�[����Ԃ�
std::string GamePlayScene::next()const {
	return "TitleScene"; //�^�C�g���V�[���ɖ߂�
}

//�I��
void GamePlayScene::end() {
	//���[���h�̃N���A
	SetMouseDispFlag(TRUE);
	world_.clear();
	MV1DeleteModel(Assets::Mesh_Skydome);
	MV1DeleteModel(Assets::Mesh_Field);
	MV1DeleteModel(Assets::Mesh_Player);
	DeleteShader(Assets::VShader_MMD);
	DeleteShader(Assets::PShader_MMD);
	DeleteShader(Assets::VShader_Normal);
	DeleteShader(Assets::PShader_Normal);
	DeleteGraph(Assets::Texture_GradPlayer);

}