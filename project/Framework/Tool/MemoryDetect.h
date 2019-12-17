//=============================================================================
//
// メモリリーク検査クラス [MemoryDetect.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _MemoryDetect_H_
#define _MemoryDetect_H_


// メモリリーク検査用
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h> 

// newのオーバーロード
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#endif