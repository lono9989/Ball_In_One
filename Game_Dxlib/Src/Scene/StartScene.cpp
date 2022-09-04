#include "Scene/StartScene.h"

#include "Mylib/Debug.h"
#include "Rendering/Screen.h"

void StartScene::load()
{
	//起動時に始めるシーンのためスタート関数に読み込みお願いいたす。
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
	Debug::DrawData(Screen::Width/2, Screen::Height/2, "起動中......");
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
