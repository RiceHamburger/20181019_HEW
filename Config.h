//=====================================================================//
//		総合処理ヘッダーファイル [config.h]                            //
//                                                                     //
//                                               GP51A247 SoSei        //
//                                               2018/05/05            //
//---------------------------------------------------------------------//
//                                                                     //
//=====================================================================//
#ifndef CONFIG_H
#define CONFIG_H
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <vector>


#include "Texture.h"


/**************************************************

				定数定義

**************************************************/
#define CLASS_NAME						("GameWindow")
#define WINDOW_CAPTION					("HEW TEST")
#define WINDOW_STYLE					(WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME))
#define SCREEN_WIDTH					(1600)
#define SCREEN_HEIGHT					(900)
#define FAILED_MESSAGE					("DX9取得失敗しました。")
#define FAILED_MESSAGE_TITLE			("エラー")

#define CNT_ZERO						(0)								//カウントゼロ

/* --------------------------------
ラジアン変換角度換算
-------------------------------- */
#define RADIAN_DEGREE(x)		(((x)/180.0f) * 3.141592653f)

#define DEGREE_RADIAN(x)		(((x)/3.141592653f) * 180.0f)

/* --------------------------------
メモリ開放
-------------------------------- */
#define PTR_DELETE_LIST(x)			{if((x)!=NULL){ delete[] (x); (x)=NULL; }}
#define PTR_DELETE(x)				{if((x)!=NULL){ delete	 (x); (x)=NULL; }}

#endif