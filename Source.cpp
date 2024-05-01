#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <iostream>
#include<array>
#include "Fractal.h"
#include "GUI/UI.h"
#include "NewColor.h"
#include <ctime>
#include <fstream>
#include <functional>
#include <Windows.h>
#include "AnimationController.h"
#include <stdio.h>
#include "process.h"
#include <tchar.h>
#include "GUIMrakup.h"
#include <iomanip>
#include <fcntl.h>
#include <io.h>
#define SAVEBUTTON 123
#define EXPORTBUTTON 456
#define LOADBUTTON 789
using namespace sf;

std::string directory;
bool SAVE = 0;
bool EXPORT = 0;
bool LOAD = 0;
struct fracData {
    float iterations, zoom, x, y, r, g, b, step, rl, im;
};
struct keyData {
    int frame, valsNum, type;
    float val1, val2, val3;
};
struct fracData2 {
    float iterations, zoom, x, y, r, g, b, step, rl, im;
    int length,keysNum;
};
LRESULT CALLBACK WindowProc(
    HWND hwnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_COMMAND:
        switch (wParam) {
        case SAVEBUTTON:
            SAVE = 1;
            break;
        case EXPORTBUTTON:
            EXPORT = 1;
            break;
        case LOADBUTTON:
            LOAD = 1;
            break;
        }

        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
auto keyToByte(keyData kd) {
    union bob {
        keyData a;
        std::array<char, sizeof(keyData)> res;
    };
    bob a;
    //a.res = new char[sizeof(int)];
    a.a = kd;
    std::string ret;
    ret.insert(ret.begin(), a.res.begin(), a.res.end());
    return ret;
}
keyData byteToKey(std::vector<char> data) {
    union bob {
        keyData a;
        std::array<char, sizeof(keyData)> res;
    };
    bob a;
    std::copy(data.begin(), data.end(), a.res.begin());
    return a.a;
}
void writeKDArray(std::vector<keyData> kds,std::ofstream& out) {
    for (auto kd:kds) {
        std::string tmp;
        tmp = keyToByte(kd);
        out.write(tmp.c_str(), tmp.size());
    }
}
std::vector<keyData> readKDArray(int kdnum , std::ifstream& in) {
    std::vector<keyData> kds;
    for (int i = 0; i < kdnum; i++) {
        char* tmp2;
        tmp2 = new char[sizeof(keyData)];
        in.read(tmp2, sizeof(keyData));
        std::vector<char> tmp3;
        for (int j = 0; j < sizeof(keyData); j++)
            tmp3.push_back(tmp2[j]);
        kds.push_back(byteToKey(tmp3));
    }
    return kds;
}
void openWin(OPENFILENAMEA *ofn) {
    if (GetOpenFileNameA(ofn)) {
        std::cout << 123;
    }
}
OPENFILENAMEA ofn;
std::string GetInputFile(char* dir,char* types)
{
    CHAR fInputPath[MAX_PATH];
    CHAR szFileNameIN[MAX_PATH];
    CHAR szFileNameOUT[MAX_PATH];

    // get the input file name

    ZeroMemory(&fInputPath, sizeof(fInputPath));
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = types;
    ofn.lpstrFile = fInputPath; // must be CHAR[]...
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFileTitle = szFileNameIN;
    ofn.nMaxFileTitle = MAX_PATH;
    ofn.lpstrInitialDir = dir;
    //ofn.lpstrTitle = "Select an input File";
    ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
    if (GetOpenFileNameA(&ofn)) // user selected an input file
    {
        return fInputPath;
    }
    else return "";
}
std::string SetInputFile(std::string dir, char* types)
{
    CHAR fInputPath[MAX_PATH];
    CHAR szFileNameIN[MAX_PATH];
    CHAR szFileNameOUT[MAX_PATH];

    // get the input file name
    
    ZeroMemory(&fInputPath, sizeof(fInputPath));
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = types;
    ofn.lpstrFile = fInputPath; // must be CHAR[]...
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFileTitle = szFileNameIN;
    ofn.nMaxFileTitle = MAX_PATH;
    ofn.lpstrInitialDir = dir.c_str();
    //ofn.lpstrTitle = "Select an input File";
    ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
    if (GetSaveFileNameA(&ofn)) // user selected an input file
    {
        return fInputPath;
    }
    else return "";
}
std::string createDate(){
    time_t now = time(0);
    tm* ltm = localtime(&now);
    std::string name = std::to_string(ltm->tm_mday);
    name += std::to_string(ltm->tm_mon + 1);
    name += std::to_string(ltm->tm_year + 1900);
    name += std::to_string(ltm->tm_hour);
    name += std::to_string(ltm->tm_min);
    name += std::to_string(ltm->tm_sec);
    return name;
}
std::string to_char(unsigned long l) {
    std::string res = "    ";
    res[3] = l % 256;
    res[2] = l >>= 8 % 256;
    res[1] = l >>= 8 % 256;
    res[0] = l >>= 8 % 256;
    return res;
};
std::string to_bin(float f) {
    union { float x; unsigned long y; }a;
    a.x = f;
    return to_char(a.y);
}
float to_float(std::vector<unsigned char> c) {
    unsigned long l = c[0]*pow(256,3) + c[1] * pow(256, 2) + c[2] * 256 + c[3];

    union { float x; unsigned long y; }a;
    a.y = l;
    return a.x;
}
float to_float(std::string c) {
    unsigned long l = c[0] * pow(256, 3) + c[1] * pow(256, 2) + c[2] * 256 + c[3];

    union { float x; unsigned long y; }a;
    a.y = l;
    return a.x;
}
Text write(Text text, String str, Vector2f pos) {
    text.setString(str);
    text.setPosition(pos);
    return text;
}
Text write(Text text, String str, Vector2f pos, float size) {

    text.setCharacterSize(size);
    text.setString(str);
    text.setPosition(pos);
    return text;
}

int main(int argc, char **argv)
{
    std::string dirS = argv[0];
    for (int i = dirS.length(); dirS[i] != '\\'; i--) {
        dirS.erase(dirS.begin() + i);
    }
    GUIMrakup gui(1920,1080);
    gui.controller.dirS = dirS;
    AnimationController ac(60, &gui.controller,dirS);
    gui.dirS = dirS;
    gui.CreateMainLayer();
    Fractal julia(&gui.xCoord->value, &gui.yCoord->value, &gui.zoom->value, &gui.iterations->value, &gui.real->value, &gui.imaginary->value,dirS);
    Fractal mandelbrot(&gui.xCoord->value, &gui.yCoord->value, &gui.zoom->value, &gui.iterations->value,dirS);
    NewColor nc(dirS);
    bool type = 0;
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Craftals");
    HWND win = window.getSystemHandle();
    //HMENU windMenu=CreateMenu();
    //AppendMenu(windMenu, MF_STRING, SAVEBUTTON , L"Save");
    //AppendMenu(windMenu, MF_STRING, EXPORTBUTTON, L"Export");
    //AppendMenu(windMenu, MF_STRING, LOADBUTTON, L"Load");
    //SetMenu(win, windMenu);
    int windowWidth=window.getSize().x;
    int windowHeight= window.getSize().y;
    float widthK=windowWidth/1920.f;
    float heightK=windowHeight/1080.f;


    //UiController& controller=gui.controller;

    gui.type0->SetFunction([&]() {type = 0; gui.type0->SetTexture(gui.radioOn); gui.type1->SetTexture(gui.radioOff);});
    gui.type1->SetFunction([&]() {type = 1; gui.type1->SetTexture(gui.radioOn); gui.type0->SetTexture(gui.radioOff);});
   
    

    Sprite fractalSprite;
    fractalSprite.setPosition(700*widthK, 60*heightK);
    Texture fractalTexture;
    fractalTexture.create(1162, 775);
    fractalSprite.setTexture(fractalTexture);
    Texture gradientTexture;
    gradientTexture.create(228, 20);
    Sprite gradientSprite;
    gradientSprite.setTexture(gradientTexture);
    gradientSprite.setPosition(100*widthK, 950*heightK);
    gradientSprite.setScale(widthK, heightK);
    
    julia.SetColor(&nc.col);
    mandelbrot.SetColor(&nc.col);
    mandelbrot.SetStep(&gui.step->value);
    julia.SetColor(&nc.col);
    julia.SetStep(&gui.step->value);

    gui.play->SetFunction([&]() {
        ac.Play();
        if (ac.isPlaying)
            gui.play->SetTexture(gui.stopTex);
        else
            gui.play->SetTexture(gui.playTex);
        });
    ac.playButton = gui.play;
    gui.animSettings->SetFunction([&]() {
        ac.clipSettings->isEnable = true;
        ac.CreateKeyCard();
        });
    gui.breakAnim->SetFunction([=, &ac, &gui]() {
        ac.BreakAnim();
        gui.play->SetTexture(gui.playTex);
        });
    gui.replay->SetFunction([=, &ac,&gui]() {
        ac.ReplayMode();
        if (ac.isReplaying)
            gui.replay->SetTexture(gui.replayOn);
        else
            gui.replay->SetTexture(gui.replayOff);
        });
    gui.restartButton->SetFunction([&ac]() {
        ac.RestartAnim();
        });
    ac.clipSettings->write(gui.headerText,"Animation clip settings",Vector2f(350,50));
    ac.clipSettings->write(gui.smallText, "length", Vector2f(95, 100));
    ac.clipSettings->write(gui.smallText, "Keys", Vector2f(95, 170),35*heightK);
    ac.headerText = gui.headerText;
    ac.smallText = gui.smallText;
    ac.createKeyPlane->write(gui.headerText, "Add key", Vector2f(400, 50));
    ac.createKeyPlane->write(gui.smallText, "frame", Vector2f(300, 100));
    ac.createKeyPlane->write(gui.smallText, "value", Vector2f(510, 100));
    
    auto export_=[=,&type,&mandelbrot,&julia]() {
        Image saveImage;
        RenderTexture saveTex;
        Sprite saveSprite;
        saveSprite.setTexture(fractalTexture);
        saveTex.create(1162, 775);
        if (type == 0)
            saveTex.draw(saveSprite, mandelbrot.Draw()); 
        else saveTex.draw(saveSprite, julia.Draw());
        saveImage = saveTex.getTexture().copyToImage();
        String saveDir = dirS + "saves\\Images";

        char types[] = "PNG (*.PNG)\0*.png\0JPEG (*.JPG;*.JPEG)\0*.jpg;*.jpeg\0\0";
        std::string name = SetInputFile(saveDir, types);

        if (name != "") {
            if (name.substr(name.length() - 4, 4) != ".png" && ofn.nFilterIndex == 1)
                name += ".png";
            else if ((name.substr(name.length() - 4, 4) != ".jpg" && name.substr(name.length() - 5, 5) != ".jpeg") && ofn.nFilterIndex == 2)
                name += ".jpg";
            saveImage.saveToFile(name);
        }
        };

    auto save = [=, &ac, &mandelbrot, &julia,&gui]() {
        char dir[] = "saves\\Fractals";
        char types[] = "FractalDataFile (*.FRAC)\0*.frac\0DynamicFractalData (*.CRFL)\0*.crfl\0\0";
        std::string name = SetInputFile(dir, types);
        if (name != "") {
            if (name.substr(name.length() - 5, 5) != ".frac" && ofn.nFilterIndex == 1)
                name += ".frac";
            else if (name.substr(name.length() - 5, 5) != ".crfl" && ofn.nFilterIndex == 2)
                name += ".crfl";
            std::string data;
            std::ofstream out((name), std::ios_base::binary);
            if (ofn.nFilterIndex == 1) {
                fracData saveFrac;
                saveFrac.iterations = gui.iterations->value;
                saveFrac.zoom = gui.zoom->value;
                saveFrac.x = gui.xCoord->value;
                saveFrac.y = gui.yCoord->value;
                saveFrac.r = gui.r->value;
                saveFrac.g = gui.g->value;
                saveFrac.b = gui.b->value;
                saveFrac.step = gui.step->value;
                saveFrac.rl = gui.real->value;
                saveFrac.im = gui.imaginary->value;
                out.write((char*)&saveFrac, sizeof(fracData));
            }
            else if (ofn.nFilterIndex == 2) {
                fracData2 saveFrac;
                std::vector<keyData> kds;
                saveFrac.iterations = gui.iterations->value;
                saveFrac.zoom = gui.zoom->value;
                saveFrac.x = gui.xCoord->value;
                saveFrac.y = gui.yCoord->value;
                saveFrac.r = gui.r->value;
                saveFrac.g = gui.g->value;
                saveFrac.b = gui.b->value;
                saveFrac.step = gui.step->value;
                saveFrac.rl = gui.real->value;
                saveFrac.im = gui.imaginary->value;
                saveFrac.length = ac.length;
                saveFrac.keysNum = ac.keys.size();
                for (int i = 0; i < ac.keys.size(); i++) {
                    keyData kd;
                    kd.frame = ac.keys[i].frame;
                    kd.type = ac.keys[i].type;
                    if (ac.keys[i].value.size() >= 1)
                        kd.val1 = ac.keys[i].value[0];

                    if (ac.keys[i].value.size() >= 2)
                        kd.val2 = ac.keys[i].value[1];

                    if (ac.keys[i].value.size() >= 3)
                        kd.val3 = ac.keys[i].value[2];
                    kd.valsNum = ac.keys[i].value.size();
                    kds.push_back(kd);
                }
                out.write((char*)&saveFrac, sizeof(fracData2)); writeKDArray(kds, out);
            }
            out.close();
        }
        };
    
    auto load = [=, &ac,&gui]() {
        char dir[] = "saves\\Fractals";
        char types[] = "FractalDataFile (*.FRAC)\0*.frac\0DynamicFractalData (*.CRFL)\0*.crfl\0\0";
        std::string name = GetInputFile(dir, types);
        if (name != "") {
            std::ifstream in((name), std::ios_base::binary);
            if (ofn.nFilterIndex == 1) {
                fracData loadFrac;
                in.read((char*)&loadFrac, sizeof(fracData));
                gui.iterations->SetValue(loadFrac.iterations);
                gui.zoom->SetValue(loadFrac.zoom);
                gui.xCoord->SetValue(loadFrac.x);
                gui.yCoord->value = loadFrac.y;
                gui.r->SetValue(loadFrac.r);
                gui.g->SetValue(loadFrac.g);
                gui.b->SetValue(loadFrac.b);
                gui.step->SetValue(loadFrac.step);
                gui.real->SetValue(loadFrac.rl);
                gui.imaginary->SetValue(loadFrac.im);
            }
            if (ofn.nFilterIndex == 2) {
                fracData2 loadFrac;
                in.read((char*)&loadFrac, sizeof(fracData2));
                std::vector<keyData> kds;
                kds = readKDArray(loadFrac.keysNum, in);
                gui.iterations->SetValue(loadFrac.iterations);
                gui.zoom->SetValue(loadFrac.zoom);
                gui.xCoord->SetValue(loadFrac.x);
                gui.yCoord->value = loadFrac.y;
                gui.r->SetValue(loadFrac.r);
                gui.g->SetValue(loadFrac.g);
                gui.b->SetValue(loadFrac.b);
                gui.step->SetValue(loadFrac.step);
                gui.real->SetValue(loadFrac.rl);
                gui.imaginary->SetValue(loadFrac.im);
                ac.length = loadFrac.length;
                ac.keys.clear();
                ac.frame = 0;
                //std::cout << " " << ;
                for (int i = 0; i < loadFrac.keysNum; i++) {
                    std::vector<float> vals;
                    if (kds[i].valsNum >= 1)
                        vals.push_back(kds[i].val1);
                    if (kds[i].valsNum >= 2)
                        vals.push_back(kds[i].val2);
                    if (kds[i].valsNum >= 3)
                        vals.push_back(kds[i].val3);
                    Key k(Key::Type(kds[i].type), kds[i].frame, vals);

                    ac.AddKey(k);
                }
            }
            in.close();
        }
        };
    gui.exportB->SetFunction(export_);
    gui.saveB->SetFunction(save);
    gui.loadB->SetFunction(load);
    gui.r->SetBackgroundTexture(nc.GetTexture(1));
    gui.g->SetBackgroundTexture(nc.GetTexture(2));
    gui.b->SetBackgroundTexture(nc.GetTexture(3));

    if (argc == 2) {
        std::string name = argv[1];
        if (name != "") {
            std::ifstream in((name), std::ios_base::binary);
            if (name.substr(name.length() - 5, 5) == ".frac"){
                fracData loadFrac;
                in.read((char*)&loadFrac, sizeof(fracData));
                gui.iterations->SetValue(loadFrac.iterations);
                gui.zoom->SetValue(loadFrac.zoom);
                gui.xCoord->SetValue(loadFrac.x);
                gui.yCoord->value = loadFrac.y;
                gui.r->SetValue(loadFrac.r);
                gui.g->SetValue(loadFrac.g);
                gui.b->SetValue(loadFrac.b);
                gui.step->SetValue(loadFrac.step);
                gui.real->SetValue(loadFrac.rl);
                gui.imaginary->SetValue(loadFrac.im);
            }
            else if (name.substr(name.length() - 5, 5) == ".crfl") {
                fracData2 loadFrac;
                in.read((char*)&loadFrac, sizeof(fracData2));
                std::vector<keyData> kds;
                kds = readKDArray(loadFrac.keysNum, in);
                gui.iterations->SetValue(loadFrac.iterations);
                gui.zoom->SetValue(loadFrac.zoom);
                gui.xCoord->SetValue(loadFrac.x);
                gui.yCoord->value = loadFrac.y;
                gui.r->SetValue(loadFrac.r);
                gui.g->SetValue(loadFrac.g);
                gui.b->SetValue(loadFrac.b);
                gui.step->SetValue(loadFrac.step);
                gui.real->SetValue(loadFrac.rl);
                gui.imaginary->SetValue(loadFrac.im);
                ac.length = loadFrac.length;
                ac.keys.clear();
                ac.frame = 0;
                //std::cout << " " << ;
                for (int i = 0; i < loadFrac.keysNum; i++) {
                    std::vector<float> vals;
                    if (kds[i].valsNum >= 1)
                        vals.push_back(kds[i].val1);
                    if (kds[i].valsNum >= 2)
                        vals.push_back(kds[i].val2);
                    if (kds[i].valsNum >= 3)
                        vals.push_back(kds[i].val3);
                    Key k(Key::Type(kds[i].type), kds[i].frame, vals);

                    ac.AddKey(k);
                }
            }
            in.close();
        }
    }
    
    Image ico;
    ico.loadFromFile(dirS+"Resourses\\ico256.png");
    
    fractalSprite.setScale(widthK, heightK);
    window.setIcon(256, 256, ico.getPixelsPtr());
    window.setFramerateLimit(60);
    sf::Event event;
    MSG message = { 0 };
    RectangleShape header;
    using namespace std;
    auto export_video = [&]() {
        String saveDir = dirS + "saves\\Videos";

        char types[] = "MP4 (*.MP4)\0*.mp4\0\0";
        std::string name = SetInputFile(saveDir, types);

        if (name != "") {
            if (name.substr(name.length() - 4, 4) != ".mp4" && ofn.nFilterIndex == 1)
                name += ".mp4";
            FILE* pPipe;
            string dirff = dirS + "Resourses\\ffmpeg";
            cout << dirff << " ";
            long lSize;
            string arg = dirff + " -y -f rawvideo -vcodec rawvideo -s " + "1162x775" + " -r 60 -pix_fmt rgba -i - -c:v libx264 -shortest " + name;
            pPipe = _popen(arg.c_str(), "w");
            _setmode(_fileno(pPipe), _O_BINARY);
            lSize = 1162 * 775 * 4;
            sf::Sprite renderSprite;
            renderSprite.setTexture(fractalTexture);
            sf::RenderTexture render;
            render.create(1162, 775);

            ac.frame = 0;
            for (int j = 0; j < ac.length; j++) {
                render.clear();
                ac.isPlaying = 1;
                for (int i : ac.Frame()) {
                    if (i == Key::Zoom) {
                        gui.zoom->SetValue(ac.fracData.zoom);
                    }
                    else if (i == Key::ZCoord) {
                        gui.xCoord->SetValue(ac.fracData.x);
                        gui.yCoord->SetValue(ac.fracData.y);
                        gui.zoom->SetValue(ac.fracData.zoom);
                    }
                    else if (i == Key::Color) {
                        gui.r->SetValue(ac.fracData.r);
                        gui.g->SetValue(ac.fracData.g);
                        gui.b->SetValue(ac.fracData.b);
                    }
                    else if (i == Key::Coord) {
                        gui.xCoord->SetValue(ac.fracData.x);
                        gui.yCoord->SetValue(ac.fracData.y);
                    }
                    else if (i == Key::Iter) {
                        gui.iterations->SetValue(ac.fracData.iterations);
                    }
                    else if (i == Key::Const) {
                        gui.real->SetValue(ac.fracData.rl);
                        gui.imaginary->SetValue(ac.fracData.im);
                    }
                    else if (i == Key::Step) {
                        gui.step->SetValue(ac.fracData.step);
                    }
                }
                nc.SetColor(Vector3f(gui.r->value, gui.g->value, gui.b->value));

                if (type == 0) render.draw(renderSprite, mandelbrot.Draw());
                else render.draw(renderSprite, julia.Draw());

                render.display();
                sf::Image img;

                img = render.getTexture().copyToImage();

                fwrite(img.getPixelsPtr(), 1, lSize, pPipe);
                ac.isPlaying = 0;
            }
            fflush(pPipe);
            fclose(pPipe);
        }

        
        };
    gui.exportvB->SetFunction(export_video);
        using namespace sf;
    header.setSize(Vector2f(1920, 25));
    while ( window.isOpen()) {
        
        

        for (int i : ac.Frame()) {
            if (i == Key::Zoom) {
                gui.zoom->SetValue(ac.fracData.zoom);
            }
            else if (i == Key::ZCoord) {
                gui.xCoord->SetValue(ac.fracData.x);
                gui.yCoord->SetValue(ac.fracData.y);
                gui.zoom->SetValue(ac.fracData.zoom);
            }
            else if (i == Key::Color) {
                gui.r->SetValue(ac.fracData.r);
                gui.g->SetValue(ac.fracData.g);
                gui.b->SetValue(ac.fracData.b);
            }
            else if (i == Key::Coord) {
                gui.xCoord->SetValue(ac.fracData.x);
                gui.yCoord->SetValue(ac.fracData.y);
            }
            else if (i == Key::Iter) {
                gui.iterations->SetValue(ac.fracData.iterations);
            }
            else if (i == Key::Const) {
                gui.real->SetValue(ac.fracData.rl);
                gui.imaginary->SetValue(ac.fracData.im);
            }
            else if (i == Key::Step) {
                gui.step->SetValue(ac.fracData.step);
            }
            }
        
        window.clear(Color(230,230,230));
        RectangleShape head; 
        head.setFillColor(Color(255,255,255));
        head.setSize(Vector2f(1920* widthK, 30* heightK));
        //window.draw(head);
        nc.SetColor(Vector3f(gui.r->value, gui.g->value, gui.b->value));
        //event
        while (window.pollEvent(event))
        {
            
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type==sf::Event::MouseButtonPressed){
                gui.controller.OnEvent(event);
            }
            else {
                gui.controller.OnEvent(event);
            
            }
        }
        
       //write
        Text smallText = gui.smallText;
        window.draw(header);
        window.draw(write(smallText, L"Mandelbrot", Vector2f(160 * widthK, 283 * heightK)));
        window.draw(write(smallText, L"Julia", Vector2f(160 * widthK, 369* heightK)));
        window.draw(write(smallText, "img", Vector2f(414 * widthK, 367 * heightK)));
        window.draw(write(smallText, "real", Vector2f(256 * widthK, 367 * heightK)));
        window.draw(write(smallText, L"Iterations", Vector2f(100 * widthK, 100 * heightK)));
        window.draw(write(smallText, L"Set", Vector2f(100 * widthK, 227 * heightK)));
        window.draw(write(smallText, L"Zoom", Vector2f(100 * widthK, 450 * heightK)));
        window.draw(write(smallText, L"Coordinates", Vector2f(100 * widthK, 538 * heightK)));
        window.draw(write(smallText, "x", Vector2f(115 * widthK, 580 * heightK)));
        window.draw(write(smallText, "y", Vector2f(115 * widthK, 635 * heightK)));
        window.draw(write(smallText, "Color", Vector2f(100 * widthK, 720 * heightK)));
        window.draw(write(smallText, "Step", Vector2f(350 * widthK, 940 * heightK)));
        window.draw(write(smallText, "Gradient", Vector2f(100 * widthK, 900 * heightK)));
        window.draw(write(smallText, "R", Vector2f(120 * widthK, 760 * heightK)));
        window.draw(write(smallText, "G", Vector2f(120 * widthK, 810 * heightK)));
        window.draw(write(smallText, "B", Vector2f(120 * widthK, 855 * heightK)));
        //draw
        if(type==0)
        window.draw(fractalSprite, mandelbrot.Draw());
        else if (type==1) window.draw(fractalSprite, julia.Draw());
        window.draw(gradientSprite, mandelbrot.GetGradient());
        window.draw(gui.controller.Draw());
        
        window.display();
    }

    return 0;
}
