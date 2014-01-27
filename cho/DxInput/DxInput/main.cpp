
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <strsafe.h>
#include "DxInput.h"

#pragma warning( disable : 4996 ) 
#pragma warning( default : 4996 )


LPDIRECT3D9             g_pD3D = NULL; 
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;

HRESULT InitD3D( HWND hWnd )
{
	if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof( d3dpp ) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	// Create the D3DDevice
	if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice ) ) )
	{
		return E_FAIL;
	}

	return S_OK;
}

VOID Cleanup()
{
	if( g_pVB != NULL )
		g_pVB->Release();

	if( g_pd3dDevice != NULL )
		g_pd3dDevice->Release();

	if( g_pD3D != NULL )
		g_pD3D->Release();
}

VOID Update()
{
	DxInput::GetInstance()->Update();

	if ( DxInput::GetInstance()->Keyboard_Down(DIK_1) )
	{
		printf("down '1' \n");
	}

	if ( DxInput::GetInstance()->Keyboard_Up(DIK_1) )
	{
		printf("Up '1' \n");
	}

	if ( DxInput::GetInstance()->Keyboard_Down(DIK_2) )
	{
		printf("down '2' \n");
	}

	if ( DxInput::GetInstance()->Keyboard_Up(DIK_2) )
	{
		printf("Up '2' \n");
	}

	if ( DxInput::GetInstance()->Keyboard_Down(DIK_3) )
	{
		printf("down '3' \n");
	}

	if ( DxInput::GetInstance()->Keyboard_Up(DIK_3) )
	{
		printf("Up '3' \n");
	}
	
	if ( DxInput::GetInstance()->Keyboard_DownState(DIK_4) )
	{
		printf("state '4' \n");
	}

	if ( DxInput::GetInstance()->Mouse_Down(DxInput::LBUTTONDOWN) )
	{
		printf("Mouse L Button Down \n");
	}

	if ( DxInput::GetInstance()->Mouse_Up(DxInput::RBUTTONDOWN) )
	{
		printf("Mouse R Button Up \n");
	}

	if ( DxInput::GetInstance()->Mouse_DownState(DxInput::WHEELBUTTONDOWN) )
	{
		printf("Mouse Wheel Button Down \n");
	}

	if ( DxInput::GetInstance()->Mouse_DoubleClick(DxInput::LBUTTONDOWN))
	{
		printf("Mouse LBUTTON Double Click\n");
	}

	//printf("%lf , %lf\n",DxInput::GetInstance()->GetCursorPos().x,DxInput::GetInstance()->GetCursorPos().y);
}

VOID Render()
{
	g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 0, 0, 255 ), 1.0f, 0 );

	if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 * 50 - 2 );
		g_pd3dDevice->EndScene();
	}

	g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}

LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage( 0 );
		return 0;
	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}

INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
	UNREFERENCED_PARAMETER( hInst );

	// Register the window class
	WNDCLASSEX wc =
	{
		sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
		L"D3D Tutorial", NULL
	};
	RegisterClassEx( &wc );

	// Create the application's window
	HWND hWnd = CreateWindow( L"D3D Tutorial", L"D3D Tutorial 05: Textures",
		WS_OVERLAPPEDWINDOW, 100, 100, 300, 300,
		NULL, NULL, wc.hInstance, NULL );

	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	printf("start App \n");

	if( SUCCEEDED( InitD3D( hWnd ) ) )
	{
		DxInput::GetInstance()->Create(hWnd);
		
		ShowWindow( hWnd, SW_SHOWDEFAULT );
		UpdateWindow( hWnd );

		MSG msg;
		ZeroMemory( &msg, sizeof( msg ) );
		while( msg.message != WM_QUIT )
		{
			if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
			else
			{
				Update();
				Render();
			}
		}
	}

	FreeConsole();
	DxInput::GetInstance()->Release();
	UnregisterClass( L"D3D Tutorial", wc.hInstance );
	
	return 0;
}