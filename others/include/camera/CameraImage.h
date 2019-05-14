#ifndef _MV_CAMERA_IMAGE_H_
#define _MV_CAMERA_IMAGE_H_

#include "CameraDefine.h"
#include "CameraStatus.h"


/// @ingroup MV_IMAGE
/// \~chinese
/// \brief 创建一个新的Image
/// \param [out] Image 新创建的图片
/// \param [in] pFrameBuffer 帧数据
/// \param [in] pFrameHead 帧头
/// \param [in] bCopy TRUE: 复制出一份新的帧数据   FALSE: 不复制，直接使用pFrameBuffer指向的缓冲区
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Create a new Image
/// \param [out] Image Newly Created Image
/// \param [in] pFrameBuffer frame data
/// \param [in] pFrameHead Frame Header
/// \param [in] bCopy TRUE: Copy a new frame data FALSE: Do not copy, directly use the buffer pointed to by pFrameBuffer
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraImage_Create(
	void** Image,
	BYTE *pFrameBuffer, 
	tSdkFrameHead* pFrameHead,
	BOOL bCopy
	);

/// @ingroup MV_IMAGE
/// \~chinese
/// \brief 创建一个空的Image
/// \param [out] Image 新创建的图片
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Create an empty Image
/// \param [out] Image Newly Created Image
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraImage_CreateEmpty(
	void** Image
	);

/// @ingroup MV_IMAGE
/// \~chinese
/// \brief 销毁Image
/// \param [in] Image
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Destroy Image
/// \param [in] Image
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraImage_Destroy(
	void* Image
	);

/// @ingroup MV_IMAGE
/// \~chinese
/// \brief 从Image获取帧数据和帧头
/// \param [in] Image
/// \param [out] DataBuffer 帧数据
/// \param [out] Head 帧头
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get frame data and frame header from Image
/// \param [in] Image
/// \param [out] DataBuffer Frame Data
/// \param [out] Head header
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraImage_GetData(
	void* Image,
	BYTE** DataBuffer,
	tSdkFrameHead** Head
	);

/// @ingroup MV_IMAGE
/// \~chinese
/// \brief 获取Image的用户自定义数据
/// \param [in] Image
/// \param [out] UserData 返回用户自定义数据
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get User's Custom Data of Image
/// \param [in] Image
/// \param [out] UserData returns user-defined data
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraImage_GetUserData(
	void* Image,
	void** UserData
	);

/// @ingroup MV_IMAGE
/// \~chinese
/// \brief 设置Image的用户自定义数据
/// \param [in] Image
/// \param [in] UserData 用户自定义数据
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set user-defined data for Image
/// \param [in] Image
/// \param [in] UserData User-defined data
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraImage_SetUserData(
	void* Image,
	void* UserData
	);

/// @ingroup MV_IMAGE
/// \~chinese
/// \brief 判断一个Image是否为空
/// \param [in] Image
/// \param [out] IsEmpty 为空返回:TRUE(1)  否则返回:FALSE(0)
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Determine if an Image is empty
/// \param [in] Image
/// \param [out] IsEmpty Empty Returns: TRUE(1) Otherwise returns: FALSE(0)
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraImage_IsEmpty(
	void* Image,
	BOOL* IsEmpty
	);

/// @ingroup MV_IMAGE
/// \~chinese
/// \brief 绘制Image到指定窗口
/// \param [in] Image
/// \param [in] hWnd 目的窗口
/// \param [in] Algorithm 缩放算法  0：快速但质量稍差  1：速度慢但质量好
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Draw Image to the specified window
/// \param [in] Image
/// \param [in] hWnd destination window
/// \param [in] Algorithm scaling algorithm 0:fast but slightly worse quality  1:slower but better quality
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraImage_Draw(
	void* Image,
	HWND hWnd,
	int Algorithm
	);

/// @ingroup MV_IMAGE
/// \~chinese
/// \brief 拉升绘制Image到指定窗口
/// \param [in] Image
/// \param [in] hWnd 目的窗口
/// \param [in] Algorithm 缩放算法  0：快速但质量稍差  1：速度慢但质量好
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Pull up drawing Image to the specified window
/// \param [in] Image
/// \param [in] hWnd destination window
/// \param [in] Algorithm scaling algorithm 0:fast but slightly worse quality  1:slower but better quality
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraImage_DrawFit(
	void* Image,
	HWND hWnd,
	int Algorithm
	);

/// @ingroup MV_IMAGE
/// \~chinese
/// \brief 绘制Image到指定DC
/// \param [in] Image
/// \param [in] hDC 目的DC
/// \param [in] Algorithm 缩放算法  0：快速但质量稍差  1：速度慢但质量好
/// \param [in] xDst 目标矩形的左上角X坐标
/// \param [in] yDst 目标矩形的左上角Y坐标
/// \param [in] cxDst 目标矩形的宽度
/// \param [in] cyDst 目标矩形的高度
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Draw Image to specified DC
/// \param [in] Image
/// \param [in] hDC destination DC
/// \param [in] Algorithm scaling algorithm 0:fast but slightly worse quality   1:slower but better quality
/// \param [in] xDst The X coordinate of the upper left corner of the target rectangle
/// \param [in] yDst The Y coordinate of the upper left corner of the target rectangle
/// \param [in] cxDst Width of target rectangle
/// \param [in] cyDst Height of target rectangle
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraImage_DrawToDC(
	void* Image,
	HDC hDC,
	int Algorithm,
	int xDst,
	int yDst,
	int cxDst,
	int cyDst
	);

/// @ingroup MV_IMAGE
/// \~chinese
/// \brief 拉升绘制Image到指定DC
/// \param [in] Image
/// \param [in] hDC 目的DC
/// \param [in] Algorithm 缩放算法  0：快速但质量稍差  1：速度慢但质量好
/// \param [in] xDst 目标矩形的左上角X坐标
/// \param [in] yDst 目标矩形的左上角Y坐标
/// \param [in] cxDst 目标矩形的宽度
/// \param [in] cyDst 目标矩形的高度
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Pull up drawing Image to specified DC
/// \param [in] Image
/// \param [in] hDC destination DC
/// \param [in] Algorithm scaling algorithm 0:fast but slightly worse quality   1:slower but better quality
/// \param [in] xDst The X coordinate of the upper left corner of the target rectangle
/// \param [in] yDst The Y coordinate of the upper left corner of the target rectangle
/// \param [in] cxDst Width of target rectangle
/// \param [in] cyDst Height of target rectangle
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraImage_DrawToDCFit(
	void* Image,
	HDC hDC,
	int Algorithm,
	int xDst,
	int yDst,
	int cxDst,
	int cyDst
	);

/// @ingroup MV_IMAGE
/// \~chinese
/// \brief 绘制Image到指定窗口（不缩放）
/// \param [in] Image
/// \param [in] hWnd 目的窗口
/// \param [in] xDst 目标矩形的左上角X坐标
/// \param [in] yDst 目标矩形的左上角Y坐标
/// \param [in] cxDst 目标矩形的宽度
/// \param [in] cyDst 目标矩形的高度
/// \param [in] xSrc 图像矩形的左上角X坐标
/// \param [in] ySrc 图像矩形的左上角Y坐标
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Draw Image to specified window (without scaling)
/// \param [in] Image
/// \param [in] hWnd destination window
/// \param [in] xDst The X coordinate of the upper left corner of the target rectangle
/// \param [in] yDst The Y coordinate of the upper left corner of the target rectangle
/// \param [in] cxDst Width of target rectangle
/// \param [in] cyDst Height of target rectangle
/// \param [in] xSrc X coordinate of the upper left corner of the image rectangle
/// \param [in] ySrc Y coordinate of the upper left corner of the image rectangle
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraImage_BitBlt(
	void* Image,
	HWND hWnd,
	int xDst,
	int yDst,
	int cxDst,
	int cyDst,
	int xSrc,
	int ySrc
	);

/// @ingroup MV_IMAGE
/// \~chinese
/// \brief 绘制Image到指定DC（不缩放）
/// \param [in] Image
/// \param [in] hDC 目的DC
/// \param [in] xDst 目标矩形的左上角X坐标
/// \param [in] yDst 目标矩形的左上角Y坐标
/// \param [in] cxDst 目标矩形的宽度
/// \param [in] cyDst 目标矩形的高度
/// \param [in] xSrc 图像矩形的左上角X坐标
/// \param [in] ySrc 图像矩形的左上角Y坐标
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Draw Image to specified DC (without scaling)
/// \param [in] Image
/// \param [in] hDC destination DC
/// \param [in] xDst The X coordinate of the upper left corner of the target rectangle
/// \param [in] yDst The Y coordinate of the upper left corner of the target rectangle
/// \param [in] cxDst Width of target rectangle
/// \param [in] cyDst Height of target rectangle
/// \param [in] xSrc X coordinate of the upper left corner of the image rectangle
/// \param [in] ySrc Y coordinate of the upper left corner of the image rectangle
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraImage_BitBltToDC(
	void* Image,
	HDC hDC,
	int xDst,
	int yDst,
	int cxDst,
	int cyDst,
	int xSrc,
	int ySrc
	);

/// @ingroup MV_IMAGE
/// \~chinese
/// \brief 以bmp格式保存Image
/// \param [in] Image
/// \param [in] FileName 文件名
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Save Image as bmp
/// \param [in] Image
/// \param [in] FileName file name
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraImage_SaveAsBmp(
	void* Image,
	char const* FileName
	);

/// @ingroup MV_IMAGE
/// \~chinese
/// \brief 以jpg格式保存Image
/// \param [in] Image
/// \param [in] FileName 文件名
/// \param [in] Quality 保存质量(1-100)，100为质量最佳但文件也最大
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Save Image as jpg
/// \param [in] Image
/// \param [in] FileName file name
/// \param [in] Quality save quality (1-100), 100 is the best quality but the file is also the largest
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraImage_SaveAsJpeg(
	void* Image,
	char const* FileName,
	BYTE  Quality
	);

/// @ingroup MV_IMAGE
/// \~chinese
/// \brief 以png格式保存Image
/// \param [in] Image
/// \param [in] FileName 文件名
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Save Image as png
/// \param [in] Image
/// \param [in] FileName file name
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraImage_SaveAsPng(
	void* Image,
	char const* FileName
	);

/// @ingroup MV_IMAGE
/// \~chinese
/// \brief 以raw格式保存Image
/// \param [in] Image
/// \param [in] FileName 文件名
/// \param [in] Format 0: 8Bit Raw     1: 16Bit Raw
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Save Image as raw
/// \param [in] Image
/// \param [in] FileName file name
/// \param [in] Format 0: 8Bit Raw     1: 16Bit Raw
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraImage_SaveAsRaw(
	void* Image,
	char const* FileName,
	int Format
	);

/// @ingroup MV_IMAGE
/// \~chinese
/// \brief 从Image创建一个IPicture
/// \param [in] Image
/// \param [out] NewPic 新创建的IPicture
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Create an IPicture from an Image
/// \param [in] Image
/// \param [out] NewPic Newly created IPicture
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraImage_IPicture(
	void* Image,
	IPicture** NewPic
	);




#endif // _MV_CAMERA_IMAGE_H_
