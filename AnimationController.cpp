#include "AnimationController.h"

AnimationController::AnimationController(int l, UiController* controller,std::string dirS) {

	/*medium.loadFromFile("Resourses/Fonts/Inter-SemiBold.ttf");
	regular.loadFromFile("Resourses/Fonts/Inter-Regular.ttf");
	Text headerText;

	headerText.setFont(medium);
	headerText.setCharacterSize(30);
	headerText.setPosition(0, 0);
	headerText.setFillColor(sf::Color::Black);

	Text smallText;
	smallText.setFont(regular);
	smallText.setCharacterSize(27);
	smallText.setPosition(0, 0);
	smallText.setFillColor(sf::Color::Black);*/
	val.resize(3);
	newKeyType = 0;
	this->controller = controller;
	length = l;
	isPlaying = 0;
	isReplaying = 0;
	clipSettings = controller->CreatePlane(Color::White, Vector2i(460, 350), Vector2i(1070, 463));
	clipSettings->isEnable = false;
	closeTex.loadFromFile(dirS + "Resourses\\Textures\\close.png");
	tipTex.loadFromFile(dirS + "Resourses\\Textures\\tipButton.png");
	menuTex.loadFromFile(dirS + "Resourses\\Textures\\menu.png");
	ifTex.loadFromFile(dirS + "Resourses\\Textures\\inputField1.png");
	keyFrame.loadFromFile(dirS + "Resourses\\Textures\\keyFrame.png");
	clipSettings->bg.setTexture(&menuTex);
	closeSettings = controller->CreateButton(Vector2f(1000, 0), Vector2f(51, 51), [&]() {
		clipSettings->isEnable = false;
		SaveCards();
		keysBar->Close();
		keysPlane->Clear();
		keysBar->SetValue(0);
		keyCards.clear();
		length = animLength->value;
		kFrame();
		}, 1);
	closeSettings->SetTexture(closeTex);
	animLength = controller->CreateInputField(Vector2i(190, 100), Vector2i(88, 35), 20, 1);
	keysBar = controller->CreateScrollBar(100, 395, 900, 20, 1);
	keysBar->SetValue(0.0f);
	keysBar->SetHandleProperties(Vector2i(30, 20), 0);
	keysPlane= controller->CreatePlane(Color(10, 10, 10), Vector2i(560, 570), Vector2i(900, 173));
	sf::IntRect mask;
	mask.left = 560; mask.top = 570; mask.width = 900; mask.height = 173;
	keysPlane->AddMask(mask);
	keysBar->AddObject(keysPlane);
	keysBar->Close();
	timeLine = controller->CreateSlider(700, 850, 1162, 10);
	createKeyPlane = controller->CreatePlane(Color::White, Vector2i(160, 150), Vector2i(1070, 463));
	createKeyPlane->isEnable = false;
	createKeyPlane->bg.setTexture(&menuTex);
	Button* openCKPlane= controller->CreateButton(Vector2f(200, 170), Vector2f(51, 51), [&]() {
		SaveCards();
		createKeyPlane->isEnable = true;
		newKeyFrame->SetValue(0);
		val[0]->SetValue(0);
		val[1]->SetValue(0);
		val[2]->SetValue(0);
		}, clipSettings->id);
	createKeyTex.loadFromFile(dirS + "Resourses\\Textures\\createKey.png");
	openCKPlane->SetTexture(createKeyTex);
	Button* closeCKPlane = controller->CreateButton(Vector2f(1000, 0), Vector2f(51, 51), [&]() {
		createKeyPlane->isEnable = false;
		keyTypes->isEnable = 0;
		showTypes->SetRotation(0);
		}, createKeyPlane->id);
	closeCKPlane->SetTexture(closeTex);

	keyTypes = controller->CreatePlane(Color(0, 0, 0, 0), Vector2i(280, 280), Vector2i(72, 30*7));
	keyTypes->isEnable = 0;
	showTypes = controller->CreateButton(Vector2f(200, 100), Vector2f(26, 26), [&]() {
	keyTypes->isEnable = !keyTypes->isEnable; 

	showTypes->Rotate(180); }, createKeyPlane->id);
	showTypesTex.loadFromFile(dirS + "Resourses\\Textures\\showTypes.png");
	showTypes->SetTexture(showTypesTex);
	typeTex.resize(7);
	typeTex[0].loadFromFile(dirS + "Resourses\\Textures\\zoom.png");
	typeTex[1].loadFromFile(dirS + "Resourses\\Textures\\coord.png");
	typeTex[2].loadFromFile(dirS + "Resourses\\Textures\\zcoord.png");
	typeTex[3].loadFromFile(dirS + "Resourses\\Textures\\color.png");
	typeTex[4].loadFromFile(dirS + "Resourses\\Textures\\step.png");
	typeTex[5].loadFromFile(dirS + "Resourses\\Textures\\iter.png");
	typeTex[6].loadFromFile(dirS + "Resourses\\Textures\\const.png");
	
	for (int i = 0; i < 7; i++) {
		Button* typeBut= controller->CreateButton(Vector2f(0, 30*i), Vector2f(72, 25), [&,i]() {
			keyTypes->isEnable = false;
			SetType(i);
			showTypes->SetRotation(0);
			}, keyTypes->id);
		typeBut->SetTexture(typeTex[i]);
	}
	newKeyFrame = controller->CreateInputField(Vector2i(390, 100), Vector2i(88, 35), 20, createKeyPlane->id);
	newKeyFrame->SetTexture(&ifTex);
	newKeyFrame->SetType(InputField::Integer);
	val[0]= controller->CreateInputField(Vector2i(590, 100), Vector2i(88, 35), 20, createKeyPlane->id);
	val[1] = controller->CreateInputField(Vector2i(590, 150), Vector2i(88, 35), 20, createKeyPlane->id);
	val[2] = controller->CreateInputField(Vector2i(590, 200), Vector2i(88, 35), 20, createKeyPlane->id);
	val[0]->SetTexture(&ifTex);
	val[1]->SetTexture(&ifTex);
	val[2]->SetTexture(&ifTex);
	Button* tipButton = controller->CreateButton(Vector2f(900, 0), Vector2f(51, 51), [&]() {
		createKeyPlane->isEnable = false;
		keyTypes->isEnable = 0;
		showTypes->SetRotation(0);
		SaveKey();
		}, createKeyPlane->id);
	tipButton->SetTexture(tipTex);
	currType.setTexture(&typeTex[newKeyType]);
	currType.setPosition(120, 100);
	currType.setSize(Vector2f(72, 25));
	createKeyPlane->AddDeco(currType);
	SetType(0);
	animLength->SetValue(l);
	animLength->SetTexture(&ifTex);
	animLength->ifType = InputField::Integer;
	tlHandle.loadFromFile(dirS + "Resourses\\Textures\\circle.png");
	timeLine->SetHandleTexture(&tlHandle);
	timeLine->SetBackgroundColor(Color(51, 51, 51));
	timeLine->SetFillAreaColor(Color(128,128,128));
	
	timeLine->SetHandleColors(Color(221,39,45), Color(200, 39, 45));
	timeLine->SetHandleProperties(Vector2i(25, 25), 0);

}
void AnimationController::AddKey(Key k) {
	keys.push_back(k);
	UpdateAnimators();
}
void AnimationController::DeleteKey(int num) {
	keys.erase(keys.begin()+num);
	UpdateAnimators();
}
void AnimationController::SaveKey() {

	Key k(Key::Type(newKeyType), newKeyFrame->value, { val[0]->value,val[1]->value, val[2]->value });
		AddKey(k);
		if (clipSettings->isEnable)
			keysPlane->SetSize(std::fmax(315 * keys.size(), 900), 173);
		keysBar->NewLen();
			CreateKeyCard();
}
bool AnimationController::Sorting(const Key& a, const Key& b) {
	return a.frame > b.frame;
}
void AnimationController::SetType(int type) {
	newKeyType = type;
	currType.setTexture(&typeTex[newKeyType]);
	createKeyPlane->deco[0] = currType;
	for (auto i : val)
		i->isActive = 0;
	for (int i = 0; i < Key::GetValuesNum(Key::Type(type)); i++) {
		val[i]->isActive = 1;
		val[i]->SetValue(0);
	}
	
}
void AnimationController::UpdateAnimators() {
	if (keys.size() > 1) {
		std::sort(keys.begin(), keys.end(), [](const Key a, const Key b) {return a.frame < b.frame; });
		std::vector<Key> keys_ = keys;
		std::vector<Key> tmp;
		animators.erase(animators.begin(), animators.end());
		while (keys_.size() > 0) {
			tmp.push_back(keys_[0]);
			Key::Type type = keys_[0].type;
			keys_.erase(keys_.begin());

			for (int i = 0; i < keys_.size(); i++) {
				if (keys_[i].type == type) {
					tmp.push_back(keys_[i]);
					keys_.erase(keys_.begin() + i);
					i--;
				}
			}

			std::sort(tmp.begin(), tmp.end(), [](const Key a, const Key b) {return a.frame < b.frame; });

			for (int i = 0; i < tmp.size() - 1; i++) {
				animators.push_back(Animator(tmp[i], tmp[i + 1]));
				//std::cout << tmp[i].frame << " " << tmp[i + 1].frame << " ";
			}

			tmp.erase(tmp.begin(), tmp.end());
		}
	}

}

std::vector<int> AnimationController::Frame() {
	std::vector<int> ret;
	if (waskFrame.size() > 0) {
		ret = waskFrame;
		waskFrame.clear();
		return ret;
	}
	if (isPlaying && frame <= length) {
		timeLine->SetValue((float)frame / length);
		if (timeLine->isMouseDown)
			playButton->method();
		for (Animator animator : animators) {

			if (animator.GetValue(frame)) {
				//std::cout << frame;
				if (animator.type == Key::Type::Zoom) {
					fracData.zoom = animator.currentValue[0];
					ret.push_back(Key::Zoom);
				}

				else if (animator.type == Key::Type::Step) {
					fracData.step = animator.currentValue[0];
					ret.push_back(Key::Step);
				}
				else if (animator.type == Key::Type::Iter) {
					fracData.iterations = animator.currentValue[0];
					ret.push_back(Key::Iter);
				}
				else if (animator.type == Key::Type::ZCoord) {
					fracData.zoom = animator.currentValue[0];
					fracData.x = animator.currentValue[1];
					fracData.y = animator.currentValue[2];
					ret.push_back(Key::ZCoord);
				}

				else if (animator.type == Key::Type::Color) {
					fracData.r = animator.currentValue[0];
					fracData.g = animator.currentValue[1];
					fracData.b = animator.currentValue[2];
					ret.push_back(Key::Color);
				}

				else if (animator.type == Key::Type::Const) {
					fracData.rl = animator.currentValue[0];
					fracData.im = animator.currentValue[1];
					ret.push_back(Key::Const);
				}
			}
		}
		frame++;

		if (isReplaying)
			frame %= length;
		return ret;
	}
	else if (isPlaying)
		playButton->method();
	else if (timeLine->isMouseDown) {
		frame = timeLine->value * length;
		kFrame();
		
	}
	return ret;
}
void AnimationController::kFrame() {
	isPlaying = true;
	waskFrame=Frame();
	if (frame != 0)
		frame -= 1;
	//frame -= 1;
	isPlaying = false;
}
void AnimationController::BreakAnim() {
	frame = 0;
	kFrame();
}
void AnimationController::RestartAnim() {
	frame = 0;
	if(!isPlaying)
	kFrame();
}
void AnimationController::ReplayMode() {
	isReplaying = !isReplaying;
}
void AnimationController::Play() {
	isPlaying = !isPlaying;
}
void AnimationController::CreateKeyCard() {
	//Plane *p=new Plane(sf::Color::White, sf::Vector2i(0, 0), sf::Vector2i(50, 100));
	//keysBar->AddObject(p);
	keysPlane->Clear();
	keyCards.clear();

	keysPlane->SetSize(std::fmax(315 * keys.size(), 900), 173);
	this->keysBar->Move();
	int x = 0;
	int n = 0;
	for (Key i : keys) {
		KeyCard kc;
		kc.key = &i;
		sf::RectangleShape rs;
		rs.setPosition(Vector2f(34 + x, 5));
		rs.setSize(Vector2f(270,163));
		keysPlane->AddDeco(rs);
		rs.setPosition(Vector2f(5 + x, 5));
		rs.setSize(Vector2f(29, 163));
		rs.setTexture(&keyFrame);
		std::string type= "t\ny\np\ne";
		if (i.type == Key::ZCoord) {
			rs.setFillColor(Color(173, 0, 229));
			type = "z\nc\no\no\nr\nd";
		}
		else if (i.type == Key::Color) {
			rs.setFillColor(Color(0,146,69));
			type = "c\no\nl\no\nr";
		}
		else if (i.type == Key::Coord) {
			rs.setFillColor(Color(237, 28, 36));
			type = "c\no\no\nr\nd";
		}
		else if (i.type == Key::Zoom) {
			rs.setFillColor(Color(0, 113, 188));
			type = "z\no\no\nm";
		}
		else if (i.type == Key::Const) {
			rs.setFillColor(Color(241, 123, 49));
			type = "c\no\nn\ns\nt";
		}
		else if (i.type == Key::Iter) {
			rs.setFillColor(Color(251, 191, 59));
			type = "i\nt\ne\nr";
		}
		else if (i.type == Key::Step) {
			rs.setFillColor(Color(29, 195, 185));
			type = "s\nt\ne\np";
		}
		keysPlane->AddDeco(rs);
		smallText.setLineSpacing(0.7f);

		Button* deleteButton = controller->CreateButton(Vector2f(270 + x, 0), Vector2f(40, 40), [&, n]() { this->DeleteKey(n); 
		keysPlane->SetSize(std::fmax(315 * keys.size(), 900), 173);  
		this->keysBar->NewLen();
		this->CreateKeyCard();
		/*keyCards.erase(keyCards.begin() + n);*/ }, keysPlane->id);
		deleteButton->SetTexture(closeTex);
		keysPlane->write(smallText, "frame", Vector2f(40 + x, 10));
		keysPlane->write(smallText, "value", Vector2f(40 + x, 55));
		keysPlane->write(smallText, type, Vector2f(230 + x, 10));
		auto frame= controller->CreateInputField(Vector2i(120+x, 10), Vector2i(88, 35), 20, keysPlane->id);
		kc.frame = frame;
		int y = 0;
		for (auto j : i.value) {
			auto val = controller->CreateInputField(Vector2i(120 + x, 55+y), Vector2i(88, 35), 20, keysPlane->id);
			kc.value.push_back(val);
			val->SetValue(j);
			val->SetTexture(&ifTex);
			y += 35;
		}
		frame->SetValue(i.frame);
		frame->SetTexture(&ifTex);
		x += 315;
		n++;
		keyCards.push_back(kc);
	}
	if(keysPlane->isEnable==0)
		keysBar->Open();
}
void AnimationController::SaveCards() {
	for (auto i = 0; i < keyCards.size();i++) {
		keys[i].frame = keyCards[i].frame->value;
		for (int j = 0; j < keyCards[i].value.size(); j++)
			keys[i].value[j] = keyCards[i].value[j]->value;
	}
	UpdateAnimators();
}
void AnimationController::DeleteAllKeys() {
	keys.clear();

}