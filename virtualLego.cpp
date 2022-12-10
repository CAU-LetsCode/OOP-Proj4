////////////////////////////////////////////////////////////////////////////////
//
// File: virtualLego.cpp
//
// Original Author: 박창현 Chang-hyeon Park, 
// Modified by Bong-Soo Sohn and Dong-Jun Kim
// 
// Originally programmed for Virtual LEGO. 
// Modified later to program for Virtual Billiard.
//        
////////////////////////////////////////////////////////////////////////////////

#include "d3dUtility.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <array>

#include "CSphere.h"
#include "CWall.h"
#include "CLight.h"
#include "CTopWall.h"
#include "CBottomWall.h"
#include "CRightWall.h"
#include "CLeftWall.h"
#include "CFloor.h"
#include "CHole.h"
#include "CHandSphere.h"
#include "Status.h"
#include "Player.h"
#include "d3dUtility.h"
#include "d3dfont.h"

#include "Platform.h"
#include "Jumper.h"

#define NUM_PLATFORM 1
#define PLATFORMWIDTH 2
#define PLATFORMHEIGHT 0.5
#define PLATFORMDEPTH 0.5

using std::array;

// -----------------------------------------------------------------------------
// Transform matrices
// -----------------------------------------------------------------------------
D3DXMATRIX g_mWorld;
D3DXMATRIX g_mView;
D3DXMATRIX g_mProj;

// -----------------------------------------------------------------------------
// Global variables
// -----------------------------------------------------------------------------
float g_camera_pos[3] = { 0.0f, 10.0f, 0.0f };

// window size
const int Width = 1024;
const int Height = 768;

HWND window;

IDirect3DDevice9* Device = NULL;

Platform g_platform;
vector<Platform> g_platforms(NUM_PLATFORM);
vector<array<float, 3>> g_platform_cord(NUM_PLATFORM);
Jumper g_jumper;
CLight g_light;

Player players[2] = { Player(1), Player(2) };
vector<Player*> playerVec = { &players[0], &players[1] };
Status status(playerVec);

// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------
void destroyAllLegoBlock(void)
{
}

// initialization
bool Setup() {
	int i;

	D3DXMatrixIdentity(&g_mWorld);
	D3DXMatrixIdentity(&g_mView);
	D3DXMatrixIdentity(&g_mProj);

	//if (!displayGameStatus.create("Times New Roman", 16, Device)) return false;

	// create platform
	if (!g_platform.create(Device, 10, 0.1, 10, d3d::GREEN)) return false;
	g_platform.setPosition(0, -5, 0);

	for (int i = 0; i < NUM_PLATFORM; i++) {
		if (!g_platforms[i].create(Device, PLATFORMWIDTH, PLATFORMHEIGHT, PLATFORMDEPTH, d3d::RED)) return false;
		g_platforms[i].setPosition(0, 0, 0);
	}

	// create jumper
	if (!g_jumper.create(Device)) return false;
	g_jumper.setPosition(0, 0, 3);

	// light setting 
	D3DLIGHT9 lit;
	::ZeroMemory(&lit, sizeof(lit));
	lit.Type = D3DLIGHT_POINT;
	lit.Diffuse = d3d::WHITE;
	lit.Specular = d3d::WHITE * 1.0f;
	lit.Ambient = d3d::WHITE * 1.0f;
	lit.Position = D3DXVECTOR3(g_camera_pos[0], g_camera_pos[1], g_camera_pos[2]);
	lit.Range = 100.0f;
	lit.Attenuation0 = 0.0f;
	lit.Attenuation1 = 0.9f;
	lit.Attenuation2 = 0.0f;

	float radius = 0.1f;
	if (false == g_light.create(Device, lit, radius)) return false;

	// Position and aim the camera.
	D3DXVECTOR3 pos(g_camera_pos[0], g_camera_pos[1], g_camera_pos[2]);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 0.0f, 1.0f);	// camera's rotation
	D3DXMatrixLookAtLH(&g_mView, &pos, &target, &up);
	Device->SetTransform(D3DTS_VIEW, &g_mView);

	// Set the projection matrix.
	D3DXMatrixPerspectiveFovLH(&g_mProj, D3DX_PI / 4, (float)Width / (float)Height, 1.0f, 100.0f);
	Device->SetTransform(D3DTS_PROJECTION, &g_mProj);

	// Set render states.
	Device->SetRenderState(D3DRS_LIGHTING, TRUE);
	Device->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	Device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

	g_light.setLight(Device, g_mWorld);
	return true;
}

// set of destroy function
void Cleanup(void)
{
	g_platform.destroy();
	g_light.destroy();
}

// Update
bool Display(float timeDelta)
{
	int i = 0;
	int j = 0;

	if (Device)
	{
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00afafaf, 1.0f, 0);
		Device->BeginScene();

		// draw platforms
		g_platform.draw(Device, g_mWorld);

		for (int i = 0; i < NUM_PLATFORM; i++) {
			g_platforms[i].draw(Device, g_mWorld);
		}

		// intersect between jumper and platform
		// todo

		// draw jumper
		g_jumper.draw(Device, g_mWorld);
		
		//g_light.draw(Device); // 효과는 주되, 화면상에서 가려줌

		Device->EndScene();
		Device->Present(0, 0, 0, 0);
		Device->SetTexture(0, NULL);
	}

	// game over
	//todo

	return true;
}

LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static bool wire = false;
	static bool isReset = true;
	static int old_x = 0;
	static int old_y = 0;
	static enum { WORLD_MOVE, LIGHT_MOVE, BLOCK_MOVE } move = WORLD_MOVE;

	switch (msg) {
	case WM_DESTROY: {
		::PostQuitMessage(0);
		break;
	}
	case WM_KEYDOWN: {
		switch (wParam) {
		case VK_ESCAPE:
			::DestroyWindow(hwnd);
			break;
		case VK_RETURN:
			if (NULL != Device) {
				wire = !wire;
				Device->SetRenderState(D3DRS_FILLMODE,
					(wire ? D3DFILL_WIREFRAME : D3DFILL_SOLID));
			}
			break;
		case VK_SPACE:
			
			
			break;

		}
		break;
	}

	case WM_MOUSEMOVE:
	{
		int new_x = LOWORD(lParam);
		int new_y = HIWORD(lParam);
		float dx;
		float dy;

		if (LOWORD(wParam) & MK_LBUTTON) {


			if (isReset) {
				isReset = false;
			}
			else {
				D3DXVECTOR3 vDist;
				D3DXVECTOR3 vTrans;
				D3DXMATRIX mTrans;
				D3DXMATRIX mX;
				D3DXMATRIX mY;

				switch (move) {
				case WORLD_MOVE:
					dx = (old_x - new_x) * 0.01f;
					dy = (old_y - new_y) * 0.01f;
					D3DXMatrixRotationZ(&mX, dx);
					D3DXMatrixRotationX(&mY, dy);
					g_mWorld = g_mWorld * mX * mY;

					break;
				}
			}

			old_x = new_x;
			old_y = new_y;

		}
		else {
			isReset = true;

			old_x = new_x;
			old_y = new_y;

			move = WORLD_MOVE;
		}
		break;
	}
	}

	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE prevInstance,
	PSTR cmdLine,
	int showCmd)
{
	srand(static_cast<unsigned int>(time(NULL)));

	if (!d3d::InitD3D(hinstance,
		Width, Height, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
		return 0;
	}

	if (!Setup())
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
		return 0;
	}

	d3d::EnterMsgLoop(Display);

	Cleanup();

	Device->Release();

	return 0;
}