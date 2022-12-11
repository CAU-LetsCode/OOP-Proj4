#include "DisplayText.h"



DisplayText::DisplayText(const int windowWidth, const int windowHeight) {
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
}

DisplayText::~DisplayText() {
	for (unsigned int i = 0; i < 9; i++) {
		delete this->FontObjects[i];
	}

	delete[] this->FontObjects;
}

bool DisplayText::create(const char* fontFamily, const int fontSize, IDirect3DDevice9* pDevice) {
	for (unsigned int i = 0; i < 9; i++) {
		this->FontObjects[i] = new CD3DFont(fontFamily, fontSize, 0);
		this->FontObjects[i]->InitDeviceObjects(pDevice);
		this->FontObjects[i]->RestoreDeviceObjects();
	}

	this->jumperName = "player";

	return true;
}

void DisplayText::destroy() {
	for (unsigned int i = 0; i < 9; i++) {
		this->FontObjects[i]->InvalidateDeviceObjects();
		this->FontObjects[i]->DeleteDeviceObjects();
		d3d::Delete<CD3DFont*>(this->FontObjects[i]);
	}
}




bool DisplayText::update() {
	
	this->FontObjects[0]->DrawText(windowWidth / 2, 10, 0xff0000FF, "Stage 1");
	
	this->FontObjects[1]->DrawText(60, 20, 0xff0000000, "Forest of Patience");
	this->FontObjects[2]->DrawText(60, 50, 0xff0000FF, this->jumperName.c_str());

	this->FontObjects[3]->DrawText(windowWidth - 160, 20, 0xff000000, "Team14");
	this->FontObjects[4]->DrawText(windowWidth - 160, 50, 0xff000000, "JiMin");
	this->FontObjects[5]->DrawText(windowWidth - 160, 80, 0xff000000, "MinJun");
	this->FontObjects[6]->DrawText(windowWidth - 160, 110, 0xff000000, "DoYeop");

	return false;
}

bool DisplayText::updateRetry() {
	this->FontObjects[7]->DrawText(windowWidth - 160, 150, 0xff000000, "DoYeop");
	/*this->FontObjects[7]->DrawText(windowWidth / 2, windowHeight / 2 - 30, 0xff000000, "Do You wanna Retry?");
	this->FontObjects[8]->DrawText(windowWidth / 20, windowHeight / 2, 0xff000000, "[Y/N]");*/

	return false;
}

bool DisplayText::destroyRetry() {
	for (unsigned int i = 7; i < 9; i++) {
		this->FontObjects[i]->InvalidateDeviceObjects();
		this->FontObjects[i]->DeleteDeviceObjects();
		d3d::Delete<CD3DFont*>(this->FontObjects[i]);
	}
	return false;
}
