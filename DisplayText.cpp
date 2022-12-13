#include "DisplayText.h"

extern Status status;

DisplayText::DisplayText(const int windowWidth, const int windowHeight) {
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
}

DisplayText::~DisplayText() {
    for (unsigned int i = 0; i < 11; i++) {
        delete this->FontObjects[i];
    }

    delete[] this->FontObjects;
}

bool DisplayText::create(const char* fontFamily, const int fontSize, IDirect3DDevice9* pDevice) {
    for (unsigned int i = 0; i < 11; i++) {
        this->FontObjects[i] = new CD3DFont(fontFamily, fontSize, 0);
        this->FontObjects[i]->InitDeviceObjects(pDevice);
        this->FontObjects[i]->RestoreDeviceObjects();
    }

    this->jumperName = "player";

    return true;
}

void DisplayText::destroy() {
    for (unsigned int i = 0; i < 11; i++) {
        this->FontObjects[i]->InvalidateDeviceObjects();
        this->FontObjects[i]->DeleteDeviceObjects();
        d3d::Delete<CD3DFont*>(this->FontObjects[i]);
    }
}




bool DisplayText::update() {

    this->jumperNumStage = "Stage " + std::to_string(status.getNumStage());

    if (status.getNumStage() == 4) {
        this->jumperNumStage = "Every stage cleared !";
    }
       
    this->FontObjects[0]->DrawText(windowWidth / 2 - 20 , 10, 0xff0000FF, this->jumperNumStage.c_str());
    

    this->FontObjects[1]->DrawText(60, 20, 0xff0000000, "Forest of Patience");
    this->FontObjects[2]->DrawText(60, 50, 0xff0000FF, "OOP Final Project");

    this->FontObjects[3]->DrawText(windowWidth - 160, 20, 0xff000000, "Team14");
    this->FontObjects[4]->DrawText(windowWidth - 160, 50, 0xff000000, "JiMin");
    this->FontObjects[5]->DrawText(windowWidth - 160, 80, 0xff000000, "MinJun");
    this->FontObjects[6]->DrawText(windowWidth - 160, 110, 0xff000000, "DoYeop");

    if (status.getIsGameOver() == true) {
        this->finalScoreStatus = "Your final Score is Stage " + std::to_string(status.getNumFinalStage()) + " !";
        this->FontObjects[10]->DrawText(windowWidth / 2 - 100, windowHeight / 2 - 350, 0xff000000, this->finalScoreStatus.c_str());
        this->FontObjects[7]->DrawText(windowWidth / 2 - 90, windowHeight / 2 - 250 , 0xffff0000, "Do You wanna Retry ?");
        this->FontObjects[8]->DrawText(windowWidth / 2 - 50, windowHeight / 2 - 200, 0xffff0000, "[ Y / ESC ]");
    }
    else if (status.getIsGameOver() == false && status.getNumStage() == 4) {
        this->FontObjects[9]->DrawText(windowWidth / 2 - 90, windowHeight / 2 - 250, 0xff0000FF, "Congratulation !");
    }

    return false;
}
