#include "Game.h"
#include "Scene/StartScene.h"
#include "Scene/TitleScene.h"
#include "Scene/GamePlayScene.h"

Game::~Game() 
{
	//�V�[���̏I��
	scene_manager_.end();
}


void Game::Init()
{
	// Init����
	InputManager::Init();
	//�X�^�[�g�V�[���̒ǉ�
	scene_manager_.add("StartScene", new StartScene());
	//�^�C�g���V�[���̒ǉ�
	scene_manager_.add("TitleScene", new TitleScene());
	//�Q�[���v���C�V�[���̒ǉ�
	scene_manager_.add("GamePlayScene", new GamePlayScene());
	//�^�C�g���V�[������J�n
	scene_manager_.change("StartScene");
}

void Game::Update(float delta_time)
{
	if (CheckHitKey(KEY_INPUT_ESCAPE) ==TRUE) {
		is_end = true;
	}
	// �X�V����
	InputManager::Update();
	//�V�[���̍X�V
	scene_manager_.update(delta_time);
}

void Game::Draw()
{
	// �`�揈��

	//�V�[���̕`��
	scene_manager_.draw();
}

bool Game::IsEnd()
{
	return is_end;
}
