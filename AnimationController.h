#pragma once
#include "Animator.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "GUI\UI.h"
#include "GUIMrakup.h"
class AnimationController
{
public:
	struct FractalData {
		float iterations, zoom, x, y, r, g, b, step, rl,im;
	};
	struct KeyCard {
		InputField* frame;
		std::vector<InputField*>value;
		Key* key;
	};
	int newKeyType;
	Button* playButton;
	Button* createKeyButton;
	Plane* clipSettings;
	Plane* keysPlane;
	Plane* createKeyPlane;
	Plane* keyTypes;
	Button* closeSettings;
	Button* showTypes;
	InputField* animLength;
	ScrollBar* keysBar;
	Slider* timeLine;
	Texture menuTex;
	Texture closeTex;
	Texture tipTex;
	Texture ifTex;
	Texture keyFrame;
	Texture createKeyTex;
	Texture showTypesTex;
	Texture tlHandle;
	RectangleShape currType;
	std::vector<Texture> typeTex;
	std::vector<int> waskFrame;
	std::vector<InputField*> val;
	InputField*newKeyFrame;
	Text headerText, smallText;
	std::vector<KeyCard> keyCards;
	bool isReplaying;
	bool isPlaying;
	FractalData fracData;
	int length;
	int frame;
	UiController* controller;
	AnimationController(UiController* controller);
	AnimationController(int length, UiController* gui,std::string dirS);
	std::vector<int> Frame();
	void kFrame();
	void AddKey(Key newKey);
	void DeleteKey(int num);
	void UpdateAnimators();
	void End();
	void SaveKey();
	bool Sorting(const Key& a, const Key& b);
	std::vector<Animator> animators;
	std::vector<Key> keys;
	void BreakAnim();
	void RestartAnim();
	void ReplayMode();
	void Play();
	void CreateKeyCard();
	void SaveCards();
	void DeleteAllKeys();
	void SetType(int i);
};

