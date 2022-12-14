#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include <unordered_map>
#include <string>

class IScene;

// シーン管理クラス
class SceneManager {
public:
	// コンストラクタ
	SceneManager();
	// デストラクタ
	~SceneManager();
	// 更新
	void update(float delta_time);
	// 描画
	void draw()const;
	// 終了
	void end();
	// シーンの追加
	void add(const std::string& name, IScene* scene);
	// シーンの変更
	void change(const std::string& name);
	//非同期読み込み
	void load(const std::string& name);
	// シーンの消去
	void clear();
	// コピー禁止
	SceneManager(const SceneManager& other) = default;
	SceneManager& operator=(const SceneManager& other) = default;

private:
	// シーン
	std::unordered_map<std::string, IScene*>scenes_;
	// 現在のシーン
	IScene* current_scene_;
	bool change_load{ false };
	std::string str{ "Now Loading" };
};

#endif
