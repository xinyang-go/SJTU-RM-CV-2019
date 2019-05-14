#ifndef _MV_CAMERA_GRABBER_H_
#define _MV_CAMERA_GRABBER_H_

#include "CameraDefine.h"
#include "CameraStatus.h"


/// @ingroup GRABBER_CREATE
/// \~chinese
/// \brief 弹出相机列表让用户选择要打开的相机
/// \param [out] Grabber 返回新创建的采集器
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 本函数内部使用了 @link CameraInit @endlink 打开相机，因此可以使用 @link CameraGrabber_GetCameraHandle @endlink 获取相机句柄，进而使用其他SDK API来操作相机。
/// \~english
/// \brief Pop-up camera list allows the user to select the camera to open
/// \param [out] Grabber returns newly created grabber
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note This function uses @link CameraInit @endlink internally to open the camera, so you can use @link CameraGrabber_GetCameraHandle @endlink to get the camera handle and use other SDK APIs to operate the camera.
MVSDK_API CameraSdkStatus __stdcall CameraGrabber_CreateFromDevicePage(
	void** Grabber
	);

/// @ingroup GRABBER_CREATE
/// \~chinese
/// \brief 使用相机列表索引创建Grabber
/// \param [out] Grabber 返回新创建的采集器
/// \param [in] Index 相机索引
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 本函数内部使用了 @link CameraInit @endlink 打开相机，因此可以使用 @link CameraGrabber_GetCameraHandle @endlink 获取相机句柄，进而使用其他SDK API来操作相机。
/// \~english
/// \brief Creating a Grabber Using a Camera List Index
/// \param [out] Grabber returns newly created grabber
/// \param [in] Index Camera index
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note This function uses @link CameraInit @endlink internally to open the camera, so you can use @link CameraGrabber_GetCameraHandle @endlink to get the camera handle and use other SDK APIs to operate the camera.
MVSDK_API CameraSdkStatus __stdcall CameraGrabber_CreateByIndex(
	void** Grabber,
	int Index
	);

/// @ingroup GRABBER_CREATE
/// \~chinese
/// \brief 使用相机名称创建Grabber
/// \param [out] Grabber 返回新创建的采集器
/// \param [in] Name 相机名称。@link #tSdkCameraDevInfo.acFriendlyName @endlink
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 本函数内部使用了 @link CameraInit @endlink 打开相机，因此可以使用 @link CameraGrabber_GetCameraHandle @endlink 获取相机句柄，进而使用其他SDK API来操作相机。
/// \~english
/// \brief Create a Grabber with a Camera Name
/// \param [out] Grabber returns newly created grabber
/// \param [in] Name Camera name.@link #tSdkCameraDevInfo.acFriendlyName @endlink
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note This function uses @link CameraInit @endlink internally to open the camera, so you can use @link CameraGrabber_GetCameraHandle @endlink to get the camera handle and use other SDK APIs to operate the camera.
MVSDK_API CameraSdkStatus __stdcall CameraGrabber_CreateByName(
	void** Grabber,
	char* Name
	);

/// @ingroup GRABBER_CREATE
/// \~chinese
/// \brief 从设备信息创建Grabber
/// \param [out] Grabber 返回新创建的采集器
/// \param [in] pDevInfo 设备信息。@link #CameraEnumerateDevice @endlink
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 本函数内部使用了 @link CameraInit @endlink 打开相机，因此可以使用 @link CameraGrabber_GetCameraHandle @endlink 获取相机句柄，进而使用其他SDK API来操作相机。
/// \~english
/// \brief Create Grabber from device info
/// \param [out] Grabber returns newly created grabber
/// \param [in] pDevInfo device information. @link #CameraEnumerateDevice @endlink
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note This function uses @link CameraInit @endlink internally to open the camera, so you can use @link CameraGrabber_GetCameraHandle @endlink to get the camera handle and use other SDK APIs to operate the camera.
MVSDK_API CameraSdkStatus __stdcall CameraGrabber_Create(
	void** Grabber,
	tSdkCameraDevInfo* pDevInfo
	);

/// @ingroup GRABBER_DESTROY
/// \~chinese
/// \brief 销毁Grabber
/// \param [in] Grabber 采集器
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Destroy Grabber
/// \param [in] Grabber
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGrabber_Destroy(
	void* Grabber
	);

/// @ingroup GRABBER_CTRL
/// \~chinese
/// \brief 设置预览视频的显示窗口
/// \param [in] Grabber 采集器
/// \param [in] hWnd 显示窗口的窗口句柄
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set the preview video display window
/// \param [in] Grabber
/// \param [in] hWnd window handle of the display window
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGrabber_SetHWnd(
	void* Grabber,
	HWND hWnd
	);

/// @ingroup GRABBER_CTRL
/// \~chinese
/// \brief 设置Grabber取图时使用的优先级
/// \param [in] Grabber 采集器
/// \param [in] Priority 取图优先级 详见：@link #emCameraGetImagePriority @endlink
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Sets the priority used by Grabber when fetching graphs
/// \param [in] Grabber
/// \param [in] Priority GetImageBuffer priority, For details see: @link #emCameraGetImagePriority @endlink
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGrabber_SetPriority(
	void* Grabber,
	UINT Priority
	);

/// @ingroup GRABBER_CTRL
/// \~chinese
/// \brief 开始采集
/// \param [in] Grabber 采集器
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note Grabber必须进入采集状态，采集回调、抓图等功能才能正常运作
/// \~english
/// \brief Start Grabber
/// \param [in] Grabber
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note Grabber must enter the acquisition state, grab callbacks, snapshot and other functions in order to function properly
MVSDK_API CameraSdkStatus __stdcall CameraGrabber_StartLive(
	void* Grabber
	);

/// @ingroup GRABBER_CTRL
/// \~chinese
/// \brief 停止采集
/// \param [in] Grabber 采集器
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \warning 本函数内部会等待所有回调函数结束后才返回调用者,并且在等待时会派发windows消息。
/// \~english
/// \brief Stop Grabber
/// \param [in] Grabber
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \warning This function will wait for all callbacks to end before returning to the caller,And it will dispatch windows messages while waiting.
MVSDK_API CameraSdkStatus __stdcall CameraGrabber_StopLive(
	void* Grabber
	);

/// @ingroup GRABBER_SNAPSHOT
/// \~chinese
/// \brief 同步抓图
/// \param [in] Grabber 采集器
/// \param [out] Image 返回抓取到的图像 \note 需要调用@link #CameraImage_Destroy @endlink释放
/// \param [in] TimeOut 超时时间（毫秒）
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Synchronized snapshot
/// \param [in] Grabber
/// \param [out] Image Returns Captured Image \note Need to Call @link #CameraImage_Destroy @endlink Release
/// \param [in] TimeOut Timeout (milliseconds)
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGrabber_SaveImage(
	void* Grabber,
	void** Image,
	DWORD TimeOut
	);

/// @ingroup GRABBER_SNAPSHOT
/// \~chinese
/// \brief 提交一个异步的抓图请求，提交成功后待抓图完成会回调用户设置的完成函数
/// \param [in] Grabber 采集器
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \see CameraGrabber_SetSaveImageCompleteCallback
/// \~english
/// \brief Submit an asynchronous snapshot request, complete the user's completion function after the completion of the submission.
/// \param [in] Grabber
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \see CameraGrabber_SetSaveImageCompleteCallback
MVSDK_API CameraSdkStatus __stdcall CameraGrabber_SaveImageAsync(
	void* Grabber
	);

/// @ingroup GRABBER_SNAPSHOT
/// \~chinese
/// \brief 提交一个异步的抓图请求，提交成功后待抓图完成会回调用户设置的完成函数
/// \param [in] Grabber 采集器
/// \param [in] UserData 用户数据，可使用 @link CameraImage_GetUserData @endlink 从Image获取此值
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \see CameraGrabber_SetSaveImageCompleteCallback
/// \~english
/// \brief Submit an asynchronous snapshot request, complete the user's completion function after the completion of the submission.
/// \param [in] Grabber
/// \param [in] UserData user data, which can be obtained from Image using @link CameraImage_GetUserData @endlink
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \see CameraGrabber_SetSaveImageCompleteCallback
MVSDK_API CameraSdkStatus __stdcall CameraGrabber_SaveImageAsyncEx(
	void* Grabber,
	void* UserData
	);

/// @ingroup GRABBER_SNAPSHOT
/// \~chinese
/// \brief 设置异步方式抓图的完成函数
/// \param [in] Grabber 采集器
/// \param [in] Callback 当异步抓图任务完成时被调用
/// \param [in] Context 当Callback被调用时，作为参数传入Callback
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \see CameraGrabber_SaveImageAsync CameraGrabber_SaveImageAsyncEx
/// \~english
/// \brief Set the completion function of asynchronous mode snapshot
/// \param [in] Grabber
/// \param [in] Callback Callback is called when the asynchronous snapshot task completes
/// \param [in] Context Passed as a parameter when the Callback is invoked
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \see CameraGrabber_SaveImageAsync CameraGrabber_SaveImageAsyncEx
MVSDK_API CameraSdkStatus __stdcall CameraGrabber_SetSaveImageCompleteCallback(
	void* Grabber,
	pfnCameraGrabberSaveImageComplete Callback,
	void* Context
	);

/// @ingroup GRABBER_CB
/// \~chinese
/// \brief 设置帧监听函数
/// \param [in] Grabber 采集器
/// \param [in] Listener 监听函数
/// \param [in] Context 当Listener被调用时，作为参数传入Listener
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set frame listening function
/// \param [in] Grabber
/// \param [in] Listener listener function
/// \param [in] Context Passed as a parameter when the Listener is invoked
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGrabber_SetFrameListener(
	void* Grabber,
	pfnCameraGrabberFrameListener Listener,
	void* Context
	);

/// @ingroup GRABBER_CB
/// \~chinese
/// \brief 设置RAW数据回调函数
/// \param [in] Grabber 采集器
/// \param [in] Callback Raw回调函数
/// \param [in] Context 当Callback被调用时，作为参数传入Callback
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set RAW data callback function
/// \param [in] Grabber
/// \param [in] Callback Raw data callback function
/// \param [in] Context Passed as a parameter when the Callback is invoked
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGrabber_SetRawCallback(
	void* Grabber,
	pfnCameraGrabberFrameCallback Callback,
	void* Context
	);

/// @ingroup GRABBER_CB
/// \~chinese
/// \brief 设置RGB回调函数
/// \param [in] Grabber 采集器
/// \param [in] Callback RGB回调函数
/// \param [in] Context 当Callback被调用时，作为参数传入Callback
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set RGB callback function
/// \param [in] Grabber
/// \param [in] Callback RGB data callback function
/// \param [in] Context Passed as a parameter when the Callback is invoked
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGrabber_SetRGBCallback(
	void* Grabber,
	pfnCameraGrabberFrameCallback Callback,
	void* Context
	);

/// @ingroup GRABBER_CTRL
/// \~chinese
/// \brief 获取相机句柄
/// \param [in] Grabber 采集器
/// \param [out] hCamera 返回的相机句柄
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get camera handle
/// \param [in] Grabber
/// \param [out] hCamera returned camera handle
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGrabber_GetCameraHandle(
	void* Grabber,
	CameraHandle *hCamera
	);

/// @ingroup GRABBER_CTRL
/// \~chinese
/// \brief 获取帧统计信息
/// \param [in] Grabber 采集器
/// \param [out] stat 返回的统计信息
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get frame statistics
/// \param [in] Grabber
/// \param [out] stat returned statistics
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGrabber_GetStat(
	void* Grabber,
	tSdkGrabberStat *stat
	);

/// @ingroup GRABBER_CTRL
/// \~chinese
/// \brief 获取相机DevInfo
/// \param [in] Grabber 采集器
/// \param [out] DevInfo 返回的相机DevInfo
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get Camera DevInfo
/// \param [in] Grabber
/// \param [out] DevInfo Returns Camera DevInfo
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGrabber_GetCameraDevInfo(
	void* Grabber,
	tSdkCameraDevInfo *DevInfo
	);




#endif // _MV_CAMERA_GRABBER_H_
