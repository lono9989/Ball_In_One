#include "SceneManager.h"
#include "SceneNull.h"

#include "DxLib.h"

#include "Mylib/Tween/Tween.h"

static SceneNull scene_null;// null�V�[���i�������Ȃ��_�~�[�V�[���j

// �R���X�g���N�^
SceneManager::SceneManager() :
	current_scene_{ &scene_null } {
}

// �f�X�g���N�^
SceneManager::~SceneManager() {
	clear();
}

// �X�V
void SceneManager::update(float delta_time) {
	// �V�[���̍X�V
	current_scene_->update(delta_time);

	// �V�[�����I�����Ă��邩�H
	if (current_scene_->is_end()) {

		if (!change_load) {
		// �V�[����ύX����
		load(current_scene_->next());
		}
		else if (GetASyncLoadNum() == 0) {
			Tween::clear();
			change(current_scene_->next());
		}
		if (GetASyncLoadNum() != 0) {
			str += ".";
			if (str == "Now Loading.......") {
				str = "Now Loading";
			}
		}
	}
}

// �`��
void SceneManager::draw()const {
	
	// ���݂̃V�[����`��
	current_scene_->draw();
	
	if (GetASyncLoadNum() != 0) {

		// �񓯊��ǂݍ��݂̐���`��
		DrawFormatString(200, 0, GetColor(255, 255, 255), "�񓯊��ǂݍ��݂̐� %d", GetASyncLoadNum());
		DrawFormatString(0, 50, GetColor(255, 255, 255), str.c_str());
	}
}

// �I��
void SceneManager::end() {
	// ���݂̃V�[�����I��
	current_scene_->end();
	// null�V�[���ɂ��Ă���
	current_scene_ = &scene_null;
}

// �V�[���̒ǉ�
void SceneManager::add(const std::string& name, IScene* scene) {
	scenes_[name] = scene;
}

// �V�[���̕ύX
void SceneManager::change(const std::string& name) {
	// ���݂̃V�[�����I��
	end();
	// ���݂̃V�[����ύX
	current_scene_ = scenes_[name];
	// ���݂̃V�[�����J�n
	current_scene_->start();
	change_load = false;
}

void SceneManager::load(const std::string& name)
{
	change_load = true;
	// �񓯊��ǂݍ��ݐݒ�ɕύX
	SetUseASyncLoadFlag(TRUE);
	scenes_[name]->load();
	// �����ǂݍ��ݐݒ�ɕύX
	SetUseASyncLoadFlag(FALSE);
}

// �V�[���̏���
void SceneManager::clear() {
	// �O�̂��߃V�[���̏I�����Ăяo��
	end();
	// unordered_map���̃V�[�������ׂč폜
	for (auto& pair : scenes_) {
		// �V�[���̍폜
		delete pair.second;
	}
	// unordered_map������
	scenes_.clear();
}