#include "Scene/StartScene.h"

#include "Mylib/Debug.h"
#include "Rendering/Screen.h"

void StartScene::load()
{
	//�N�����Ɏn�߂�V�[���̂��߃X�^�[�g�֐��ɓǂݍ��݂��肢�������B
}

void StartScene::start()
{
	timer_ = 0.0f;
}

void StartScene::update(float delta_time)
{
	if (timer_ >= 1.0f) {
		is_end_ = true;
	}
	timer_ += delta_time;
}

void StartScene::draw() const
{
	Debug::DrawData(Screen::Width/2, Screen::Height/2, "�N����......");
}

bool StartScene::is_end() const
{
	return is_end_;
}

std::string StartScene::next() const
{
	return "TitleScene";
}

void StartScene::end()
{
}
