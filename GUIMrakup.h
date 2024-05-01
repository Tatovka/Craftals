#pragma once
#include "GUI\UI.h"
class GUIMrakup
{
public:
    std::string dirS;
    Texture circle;
    Texture circleRect;
    Texture triangal;
    Texture radioOff;
    Texture radioOn;
    Texture saveT;
    Texture exportT;
    Texture exportvT;
    Texture loadT;
    Texture ifTex;
    Texture ifTex2;
    Texture collapseTex;
    Texture minimizeTex;
    Texture playTex;
    Texture stopTex;
    Texture restartTex;
    Texture replayOn;
    Texture replayOff;
    Texture breakButton;
    Texture settingsButton;

    Font medium;
    Font regular;
    Text headerText;
    Text smallText;

    InputField* xCoord;
    InputField* yCoord;
    InputField* zoom;
    InputField* step;
    InputField* imaginary;
    InputField* real;

    Button* type0;
    Button* type1;
    Button* play;
    Button* replay;
    Button* breakAnim;
    Button* restartButton;
    Button* animSettings;
    Button* exportB;
    Button* exportvB;
    Button* saveB;
    Button* loadB;

    Slider* iterations;
    Slider* r;
    Slider* g;
    Slider* b;


	UiController controller;
    GUIMrakup(int w, int h) { controller.Create(w, h); dirS = ""; }
    void CreateMainLayer(){
        circle.loadFromFile(dirS + "Resourses\\Textures\\circle.png");
        triangal.loadFromFile(dirS + "Resourses\\Textures\\triangal.png");
        radioOff.loadFromFile(dirS + "Resourses\\Textures\\radioButton.png");
        radioOn.loadFromFile(dirS + "Resourses\\Textures\\radioButton1.png");
        saveT.loadFromFile(dirS + "Resourses\\Textures\\SaveTex.png");
        exportT.loadFromFile(dirS + "Resourses\\Textures\\ExportTex.png");
        exportvT.loadFromFile(dirS + "Resourses\\Textures\\ExportvTex.png");
        loadT.loadFromFile(dirS + "Resourses\\Textures\\LoadTex.png");
        ifTex.loadFromFile(dirS + "Resourses\\Textures\\inputField1.png");
        ifTex2.loadFromFile(dirS + "Resourses\\Textures\\inputField2.png");
        playTex.loadFromFile(dirS + "Resourses\\Textures\\playButton.png");
        stopTex.loadFromFile(dirS + "Resourses\\Textures\\stopButton.png");
        restartTex.loadFromFile(dirS + "Resourses\\Textures\\restartButton.png");
        replayOn.loadFromFile(dirS + "Resourses\\Textures\\replayOn.png");
        replayOff.loadFromFile(dirS + "Resourses\\Textures\\replayOff.png");
        breakButton.loadFromFile(dirS + "Resourses\\Textures\\breakButton.png");
        settingsButton.loadFromFile(dirS + "Resourses\\Textures\\settingsButton.png");

        
        medium.loadFromFile(dirS + "Resourses\\Fonts\\Inter-SemiBold.ttf");
        
        regular.loadFromFile(dirS + "Resourses\\Fonts\\Inter-Regular.ttf");
        

        headerText.setFont(medium);
        //headerText.setCharacterSize(30 * heightK);
        headerText.setPosition(0, 0);
        headerText.setFillColor(sf::Color::Black);

        
        smallText.setFont(regular);
        //smallText.setCharacterSize(27 * heightK);
        smallText.setPosition(0, 0);
        smallText.setFillColor(sf::Color::Black);

        //IFs
        xCoord = controller.CreateInputField(Vector2i(150, 580), Vector2i(88, 35), 20);
        yCoord = controller.CreateInputField(Vector2i(150, 635), Vector2i(88, 35), 20);
        zoom = controller.CreateInputField(Vector2i(206, 450), Vector2i(88, 35), 20);
        step = controller.CreateInputField(Vector2i(430, 945), Vector2i(88, 35), 20);
        imaginary = controller.CreateInputField(Vector2i(481, 367), Vector2i(65, 35), 20);
        real = controller.CreateInputField(Vector2i(326, 367), Vector2i(65, 35), 20);

        //BUTTONS
       
        replay = controller.CreateButton(Vector2f(1725, 900), Vector2f(49, 49), []() {});
        exportB = controller.CreateButton(Vector2f(255, 0), Vector2f(116, 24), []() {}); 
        exportvB = controller.CreateButton(Vector2f(430, 0), Vector2f(114, 23), []() {});
        animSettings = controller.CreateButton(Vector2f(1791, 900), Vector2f(49, 49), [&]() {});
        restartButton = controller.CreateButton(Vector2f(866, 900), Vector2f(49, 49), [](){}); 
        type0 = controller.CreateButton(Vector2f(100, 280), Vector2f(38, 38), []() {});
        type0->SetTexture(radioOn);
        type1 = controller.CreateButton(Vector2f(100, 360), Vector2f(38, 38), []() {});
        type1->SetTexture(radioOff);
        play = controller.CreateButton(Vector2f(735, 900), Vector2f(49, 49), []() {});
        breakAnim = controller.CreateButton(Vector2f(800, 900), Vector2f(49, 49), []() {});
        saveB = controller.CreateButton(Vector2f(40, 0), Vector2f(50, 24), []() {});
        loadB = controller.CreateButton(Vector2f(140, 0), Vector2f(59, 24), []() {});
        controller.layers[0]->cd[16]->isActive = 1;
        if(exportB!=0)
        exportB->SetTexture(exportT);
        exportvB->SetTexture(exportvT);
        if (saveB != 0)
        saveB->SetTexture(saveT);
        if (loadB != 0)
        loadB->SetTexture(loadT);
        //SLIDERS
        iterations = controller.CreateSlider(100, 180, 200, 6);
        r = controller.CreateSlider(160, 750, 330, 20);
        g = controller.CreateSlider(160, 800, 330, 20);
        b = controller.CreateSlider(160, 850, 330, 20);

        
        breakAnim->SetTexture(breakButton);
        restartButton->SetTexture(restartTex);
        replay->SetTexture(replayOff);
        animSettings->SetTexture(settingsButton);
        play->SetTexture(playTex);
        r->SetFillAreaColor(Color(0, 0, 0, 0));
        g->SetFillAreaColor(Color(0, 0, 0, 0));
        b->SetFillAreaColor(Color(0, 0, 0, 0));

        r->SetHandleTexture(&triangal);
        g->SetHandleTexture(&triangal);
        b->SetHandleTexture(&triangal);

        r->SetHandleColors(Color(200, 200, 200), Color(150, 150, 150));
        g->SetHandleColors(Color(200, 200, 200), Color(150, 150, 150));
        b->SetHandleColors(Color(200, 200, 200), Color(150, 150, 150));
        iterations->SetHandleTexture(&circle);
        iterations->SetHandleColors(sf::Color(0, 113, 188), sf::Color(46, 49, 146));

        zoom->SetTexture(&ifTex);
        real->SetTexture(&ifTex2);
        imaginary->SetTexture(&ifTex2);
        xCoord->SetTexture(&ifTex);
        yCoord->SetTexture(&ifTex);
        step->SetTexture(&ifTex);

        iterations->SetValue(0.5);
        zoom->SetValue(1.f);
        step->SetValue(0.1f);
        xCoord->SetValue(-2);
        yCoord->SetValue(1);
        real->SetValue(0);
        imaginary->SetValue(0);
        xCoord->SetK(&zoom->value);
        yCoord->SetK(&zoom->value);
        zoom->SetK(&zoom->value);

        iterations->SetHandleProperties(sf::Vector2i(30, 30), 0);
        r->SetHandleProperties(sf::Vector2i(16, 12), 1);
        g->SetHandleProperties(sf::Vector2i(16, 12), 1);
        b->SetHandleProperties(sf::Vector2i(16, 12), 1);

        
	}
    UiController& GetController() {
        return controller;
    }
    void CreateAnimLayer() {

    }
};

