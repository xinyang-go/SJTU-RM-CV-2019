#ifndef _MVCAMAPI_H_
#define _MVCAMAPI_H_


#ifdef DLL_EXPORT
#define MVSDK_API extern "C" __declspec(dllexport)
#else
#define MVSDK_API extern "C" __declspec(dllimport)
#endif
#include <Windows.h>
#include "CameraDefine.h"
#include "CameraStatus.h"

/// @ingroup API_BASIC
/// \~chinese
/// \brief 初始化SDK语言。该函数在整个进程运行期间只需要调用一次。
/// \param [in] iLanguageSel 用于选择SDK内部提示信息和界面的语种,0:表示英文,1:表示中文。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Initialize the SDK language. This function only needs to be called once during the entire process run.
/// \param [in] iLanguageSel The language used to select the prompt information and interface of the SDK. 0: English, 1: Chinese.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSdkInit(
    int     iLanguageSel
);

/// @ingroup API_ENUM
/// \~chinese
/// \brief 枚举设备，并建立设备列表
/// \param [out] pCameraList 设备列表数组指针
/// \param [inout] piNums 设备的个数指针，调用时传入pCameraList数组的元素个数，函数返回时，保存实际找到的设备个数
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义
/// \warning piNums指向的值必须初始化，且不超过pCameraList数组元素个数，否则有可能造成内存溢出
/// \note 返回的相机信息列表，会根据acFriendlyName排序的。例如可以将两个相机分别改为“Camera1”和“Camera2”的名字后，名字为“Camera1”的相机会排前面，名为“Camera2”的相机排后面。
/// \~english
/// \brief Enumerate devices and establish a list of devices
/// \param [out] pCameraList Device list array pointer
/// \param [inout] piNums The number of pointers to the device, the number of elements passed to the pCameraList array at the time of the call. When the function returns, the number of devices actually found is saved.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \warning piNums The value pointed to must be initialized and does not exceed the number of pCameraList array elements, otherwise it may cause memory overflow
/// \note The list of returned camera information will be sorted according to acFriendlyName. For example, after changing the two cameras to the names of "Camera1" and "Camera2," the camera named "Camera1" will be in front, and the camera named "Camera2" will be behind the row.
MVSDK_API CameraSdkStatus __stdcall CameraEnumerateDevice(
    tSdkCameraDevInfo* pCameraList, 
    INT*               piNums
);

/// @ingroup API_ENUM
/// \~chinese
/// \brief 枚举设备，并建立设备列表。在调用@link #CameraInitEx @endlink之前，必须调用该函数枚举设备。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Enumerate devices and create a list of devices. Before calling @link #CameraInitEx @endlink, this function must be called to enumerate the device.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API INT __stdcall CameraEnumerateDeviceEx(
);

/// @ingroup API_OPEN
/// \~chinese
/// \brief 检测设备是否已经被打开
/// \param [in] pCameraInfo 设备的枚举信息结构体指针，由@link #CameraEnumerateDevice @endlink获得。
/// \param [out] pOpened 设备的状态指针，返回设备是否被打开的状态，TRUE为打开，FALSE为空闲。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Check if the device has been opened
/// \param [in] pCameraInfo Device enumeration information structure pointer, obtained by @link #CameraEnumerateDevice @endlink
/// \param [out] pOpened The device's status pointer returns whether the device is turned on. TRUE is on and FALSE is idle.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraIsOpened(
  tSdkCameraDevInfo*  pCameraInfo, 
  BOOL*               pOpened
);

/// @ingroup API_OPEN
/// \~chinese
/// \brief 相机初始化。初始化成功后，才能调用其他相机相关的操作接口。
/// \param [in] pCameraInfo 设备的枚举信息结构体指针，由@link #CameraEnumerateDevice @endlink获得。
/// \param [in] emParamLoadMode 相机初始化时使用的参数加载方式。-1表示使用上次退出时的参数加载方式。其它取值参考@link #emSdkParameterMode @endlink定义。
/// \param [in] emTeam 初始化时使用的参数组。-1表示加载上次退出时的参数组。
/// \param [out] pCameraHandle 相机的句柄指针，初始化成功后，该指针返回该相机的有效句柄。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief The camera is initialized. After successful initialization, other camera-related operation interfaces can be called.
/// \param [in] pCameraInfo Device enumeration information structure pointer, obtained by @link #CameraEnumerateDevice @endlink.
/// \param [in] emParamLoadMode The parameter loading method used when the camera is initialized. -1 means to use the parameter loading method from the last exit. Other values are defined in @link #emSdkParameterMode @endlink.
/// \param [in] emTeam Parameter group used during initialization. -1 means to load the parameter group from the last exit.
/// \param [out] pCameraHandle The handle pointer of the camera, after successful initialization, returns the camera's effective handle.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraInit(
    tSdkCameraDevInfo*  pCameraInfo,
    int                 emParamLoadMode,
    int                 emTeam,
    CameraHandle*       pCameraHandle
);

/// @ingroup API_OPEN
/// \~chinese
/// \brief 相机初始化。初始化成功后，才能调用其他相机相关的操作接口。
/// \param [in] iDeviceIndex 相机的索引号，@link #CameraEnumerateDeviceEx @endlink返回相机个数。
/// \param [in] emParamLoadMode 相机初始化时使用的参数加载方式。-1表示使用上次退出时的参数加载方式。其它取值参考@link #emSdkParameterMode @endlink定义。
/// \param [in] emTeam 初始化时使用的参数组。-1表示加载上次退出时的参数组。
/// \param [out] pCameraHandle 相机的句柄指针，初始化成功后，该指针返回该相机的有效句柄。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief The camera is initialized. After successful initialization, other camera-related operation interfaces can be called.
/// \param [in] iDeviceIndex The camera's index number, @link #CameraEnumerateDeviceEx @endlink returns the number of cameras.
/// \param [in] emParamLoadMode The parameter loading method used when the camera is initialized. -1 means to use the parameter loading method from the last exit. Other values are defined in @link #emSdkParameterMode @endlink.
/// \param [in] emTeam Parameter group used during initialization. -1 means to load the parameter group from the last exit.
/// \param [out] pCameraHandle The handle pointer of the camera, after successful initialization, returns the camera's effective handle.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraInitEx(
    int             iDeviceIndex,
    int             emParamLoadMode,
    int             emTeam,
    CameraHandle*   pCameraHandle
);

/// @ingroup API_OPEN
/// \~chinese
/// \brief 相机初始化。初始化成功后，才能调用其他相机相关的操作接口。
/// \param [in] CameraName 相机昵称。@link #tSdkCameraDevInfo.acFriendlyName @endlink
/// \param [out] pCameraHandle 相机的句柄指针，初始化成功后，该指针返回该相机的有效句柄。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief The camera is initialized. After successful initialization, other camera-related operation interfaces can be called.
/// \param [in] CameraName Camera friendly name.@link #tSdkCameraDevInfo.acFriendlyName @endlink
/// \param [out] pCameraHandle The handle pointer of the camera, after successful initialization, returns the camera's effective handle.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraInitEx2(
	char* CameraName,
	CameraHandle   *pCameraHandle
);

/// @ingroup API_GRAB_CB
/// \~chinese
/// \brief 设置图像捕获的回调函数。当捕获到新的图像数据帧时，pCallBack所指向的回调函数就会被调用。
/// \param [in] hCamera 相机的句柄。
/// \param [in] pCallBack 回调函数指针。
/// \param [in] pContext 回调函数的附加参数，在回调函数被调用时该附加参数会被传入，可以为NULL。多用于多个相机时携带附加信息。
/// \param [out] pCallbackOld 用于返回之前设置的回调函数。可以为NULL。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Sets the image capture's callback function. When a new frame of image data is captured, the callback function pointed to by pCallBack is called.
/// \param [in] hCamera Camera handle.
/// \param [in] pCallBack Callback function pointer.
/// \param [in] pContext Additional parameters of the callback function, which will be passed in when the callback function is called, can be NULL. Use additional information when used with multiple cameras.
/// \param [out] pCallbackOld Returns the previously set callback function. Can be NULL.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetCallbackFunction(
    CameraHandle        hCamera,
    CAMERA_SNAP_PROC    pCallBack,
    PVOID               pContext,
    CAMERA_SNAP_PROC*   pCallbackOld
);

/// @ingroup API_CLOSE
/// \~chinese
/// \brief 相机反初始化。释放资源。
/// \param [in] hCamera 相机的句柄。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief The camera is deinitialized. Release resources.
/// \param [in] hCamera Camera handle.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraUnInit(
    CameraHandle hCamera
);

/// @ingroup API_BASIC
/// \~chinese
/// \brief 获得相机的描述信息
/// \param [in] hCamera 相机的句柄。
/// \param [out] pbuffer 指向相机描述信息指针的指针。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get camera description information
/// \param [in] hCamera Camera handle.
/// \param [out] pbuffer Pointer to the camera description information pointer.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetInformation(
    CameraHandle    hCamera, 
    char**          pbuffer
);

/// @ingroup API_ISP
/// \~chinese
/// \brief 将获得的相机原始输出图像数据进行处理，叠加饱和度、颜色增益和校正、降噪等处理效果，最后得到RGB888格式的图像数据。
/// \param [in] hCamera 相机的句柄。
/// \param [in] pbyIn 输入图像数据的缓冲区地址，不能为NULL。 
/// \param [out] pbyOut 处理后图像输出的缓冲区地址，不能为NULL。
/// \param [inout] pFrInfo 输入图像的帧头信息，处理完成后，帧头信息中的图像格式uiMediaType会随之改变。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief The obtained raw camera output image data is processed to superimpose processing effects such as saturation, color gain and correction, noise reduction, etc. Finally, image data of RGB888 format is obtained.
/// \param [in] hCamera Camera handle.
/// \param [in] pbyIn The buffer address of the input image data cannot be NULL.
/// \param [out] pbyOut The buffer address of the image output after processing cannot be NULL.
/// \param [inout] pFrInfo After inputting the frame header information of the image, the image format uiMediaType in the frame header information will be changed after the processing is completed.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraImageProcess(
    CameraHandle        hCamera, 
    BYTE*               pbyIn, 
    BYTE*               pbyOut,
    tSdkFrameHead*      pFrInfo
);

/// @ingroup API_ISP
/// \~chinese
/// \brief 将获得的相机原始输出图像数据进行处理，叠加饱和度、颜色增益和校正、降噪等处理效果，最后得到RGB888格式的图像数据。
/// \param [in] hCamera 相机的句柄。
/// \param [in] pbyIn 输入图像数据的缓冲区地址，不能为NULL。 
/// \param [out] pbyOut 处理后图像输出的缓冲区地址，不能为NULL。
/// \param [inout] pFrInfo 输入图像的帧头信息，处理完成后，帧头信息中的图像格式uiMediaType会随之改变。
/// \param [in] uOutFormat 处理完后图像的输出格式。可以是CAMERA_MEDIA_TYPE_MONO8、CAMERA_MEDIA_TYPE_RGB、CAMERA_MEDIA_TYPE_RGBA8的其中一种。
/// \param [in] uReserved 预留参数，必须设置为0。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief The obtained raw camera output image data is processed to superimpose processing effects such as saturation, color gain and correction, noise reduction, etc. Finally, image data of RGB888 format is obtained.
/// \param [in] hCamera Camera handle.
/// \param [in] pbyIn The buffer address of the input image data cannot be NULL.
/// \param [out] pbyOut The buffer address of the image output after processing cannot be NULL.
/// \param [inout] pFrInfo After inputting the frame header information of the image, the image format uiMediaType in the frame header information will be changed after the processing is completed.
/// \param [in] uOutFormat The output format of the image after processing. It may be one of CAMERA_MEDIA_TYPE_MONO8,CAMERA_MEDIA_TYPE_RGB,CAMERA_MEDIA_TYPE_RGBA8.
/// \param [in] uReserved Reservation parameters must be set to 0.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraImageProcessEx(
    CameraHandle        hCamera, 
    BYTE*               pbyIn, 
    BYTE*               pbyOut,
    tSdkFrameHead*      pFrInfo,
    UINT                uOutFormat,
    UINT                uReserved
);

/// @ingroup API_DISPLAY
/// \~chinese
/// \brief 初始化SDK内部的显示模块。在调用@link #CameraDisplayRGB24 @endlink前必须先调用该函数初始化。如果您在二次开发中，使用自己的方式进行图像显示(不调用CameraDisplayRGB24)则不需要调用本函数。 
/// \param [in] hCamera 相机的句柄。
/// \param [in] hWndDisplay 显示窗口的句柄，一般为窗口的m_hWnd成员。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Initialize the display module inside the SDK. The function must be called before calling @link #CameraDisplayRGB24 @endlink. If you use your own method for image display (do not call CameraDisplayRGB24) during secondary development, you do not need to call this function.
/// \param [in] hCamera Camera handle.
/// \param [in] hWndDisplay The handle of the display window, typically the m_hWnd member of the window.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraDisplayInit(
    CameraHandle    hCamera,
    HWND            hWndDisplay
);

/// @ingroup API_DISPLAY
/// \~chinese
/// \brief 显示图像。必须调用过@link #CameraDisplayInit @endlink进行初始化才能调用本函数。
/// \param [in] hCamera 相机的句柄。
/// \param [in] pFrameBuffer 图像的帧缓冲区
/// \param [in] pFrInfo 图像的帧头信息
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Display the image. You must call @link #CameraDisplayInit @endlink before you can call this function.
/// \param [in] hCamera Camera handle.
/// \param [in] pFrameBuffer Image frame buffer
/// \param [in] pFrInfo The frame header information of the image
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraDisplayRGB24(
    CameraHandle        hCamera,
    BYTE*               pFrameBuffer, 
    tSdkFrameHead*      pFrInfo
);

/// @ingroup API_DISPLAY
/// \~chinese
/// \brief 设置显示的模式。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iMode 显示模式，参见@link #emSdkDisplayMode @endlink的定义。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set the display mode.
/// \param [in] hCamera Camera handle.
/// \param [in] iMode Display mode, see @link #emSdkDisplayMode @endlink definition.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetDisplayMode(
    CameraHandle    hCamera,
    INT             iMode
);

/// @ingroup API_DISPLAY
/// \~chinese
/// \brief 设置显示的起始偏移值。仅当显示模式为DISPLAYMODE_REAL时有效。例如显示控件的大小为320X240，而图像的的尺寸为640X480，那么当iOffsetX = 160,iOffsetY = 120时显示的区域就是图像的居中320X240的位置。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iOffsetX 偏移的X坐标。
/// \param [in] iOffsetY  偏移的Y坐标。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set the starting offset of the display. This is valid only when the display mode is DISPLAY MODE_REAL. For example, the size of the display control is 320×240, and the size of the image is 640×480. When iOffsetX = 160 and iOffsetY = 120, the displayed area is the center 320×240 of the image.
/// \param [in] hCamera Camera handle.
/// \param [in] iOffsetX The offset's X coordinate.
/// \param [in] iOffsetY  The offset's Y coordinate.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetDisplayOffset(
    CameraHandle    hCamera,
    int             iOffsetX, 
    int             iOffsetY
);

/// @ingroup API_DISPLAY
/// \~chinese
/// \brief 设置显示控件的尺寸。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iWidth 宽度
/// \param [in] iHeight 高度
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set the size of the display control.
/// \param [in] hCamera Camera handle.
/// \param [in] iWidth width
/// \param [in] iHeight height
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetDisplaySize(
    CameraHandle    hCamera, 
    INT             iWidth, 
    INT             iHeight
);

/// @ingroup API_GRAB
/// \~chinese
/// \brief 获得一帧图像数据。为了提高效率，SDK在图像抓取时采用了零拷贝机制，本函数实际获得是内核中的一个缓冲区地址。
/// \param [in] hCamera 相机的句柄。
/// \param [out] pFrameInfo 图像的帧头信息指针。
/// \param [out] pbyBuffer 返回图像数据的缓冲区指针。
/// \param [in] wTimes 抓取图像的超时时间，单位毫秒。在wTimes时间内还未获得图像，则该函数会返回超时错误。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 该函数成功调用后，必须调用@link CameraReleaseImageBuffer @endlink释放缓冲区,以便让内核继续使用该缓冲区。  
/// \~english
/// \brief Get a frame of image data. To improve efficiency, the SDK uses a zero-copy mechanism for image capture. This function actually obtains a buffer address in the kernel.
/// \param [in] hCamera Camera handle.
/// \param [out] pFrameInfo The header information pointer of the image.
/// \param [out] pbyBuffer Returns the buffer pointer of the image data.
/// \param [in] wTimes Timeout for grabbing an image in milliseconds. The function returns a timeout error if no image has been obtained within wTimes.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note After the function is successfully called, @link CameraReleaseImageBuffer @endlink must be called to release the buffer so that the kernel can continue to use the buffer.
MVSDK_API CameraSdkStatus __stdcall CameraGetImageBuffer(
    CameraHandle        hCamera, 
    tSdkFrameHead*      pFrameInfo, 
    BYTE**              pbyBuffer,
    UINT                wTimes
);

/// @ingroup API_GRAB
/// \~chinese
/// \brief 获得一帧图像数据。该接口获得的图像数据是已经经过图像处理的数据。
/// \param [in] hCamera 相机的句柄。
/// \param [out] piWidth 整形指针，返回图像的宽度。
/// \param [out] piHeight 整形指针，返回图像的高度。
/// \param [in] wTimes 抓取图像的超时时间，单位毫秒。在wTimes时间内还未获得图像，则该函数会返回超时错误。
/// \return 成功时，返回帧数据缓冲区的首地址，否则返回0。
/// \note 本函数不需要调用@link CameraReleaseImageBuffer @endlink释放缓冲区。
/// \~english
/// \brief Get a frame of image data. The image data obtained by this interface is already image-processed data.
/// \param [in] hCamera Camera handle.
/// \param [out] piWidth  returns the width of the image.
/// \param [out] piHeight Returns the height of the image.
/// \param [in] wTimes Timeout for grabbing an image in milliseconds. The function returns a timeout error if no image has been obtained within wTimes.
/// \return On success, returns the first address of the frame data buffer, otherwise it returns 0.
/// \note This function does not need to call @link CameraReleaseImageBuffer @endlink to release the buffer.
MVSDK_API unsigned char* __stdcall CameraGetImageBufferEx(
    CameraHandle        hCamera, 
    INT*                piWidth,
    INT*                piHeight,
    UINT                wTimes
);

/// @ingroup API_GRAB
/// \~chinese
/// \brief 抓拍一张图像到缓冲区中。相机会进入抓拍模式，并且自动切换到抓拍模式的分辨率进行图像捕获。
/// \param [in] hCamera 相机的句柄。
/// \param [out] pFrameInfo 图像的帧头信息指针。
/// \param [out] pbyBuffer 返回图像数据的缓冲区指针。
/// \param [in] wTimes 抓取图像的超时时间，单位毫秒。在wTimes时间内还未获得图像，则该函数会返回超时错误。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 该函数成功调用后，必须调用@link CameraReleaseImageBuffer @endlink释放缓冲区,以便让内核继续使用该缓冲区。  
/// \warning 本函数可能会进行分辨率切换，因此效率会比@link #CameraGetImageBuffer @endlink低。如果没有切换分辨率抓拍的需求，请使用@link #CameraGetImageBuffer @endlink。
/// \~english
/// \brief Take an image into the buffer. The camera will enter snap mode and automatically switch to snap mode resolution for image capture.
/// \param [in] hCamera Camera handle.
/// \param [out] pFrameInfo The header information pointer of the image.
/// \param [out] pbyBuffer Returns the buffer pointer of the image data.
/// \param [in] wTimes Timeout for grabbing an image in milliseconds. The function returns a timeout error if no image has been obtained within wTimes.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note After the function is successfully called, @link CameraReleaseImageBuffer @endlink must be called to release the buffer so that the kernel can continue to use the buffer.
/// \warning This function may switch the resolution, so the efficiency will be lower than @link #CameraGetImageBuffer @endlink. If you do not need to switch resolution capture, use @link #CameraGetImageBuffer @endlink.
MVSDK_API CameraSdkStatus __stdcall CameraSnapToBuffer(
    CameraHandle        hCamera,
    tSdkFrameHead*      pFrameInfo,
    BYTE**              pbyBuffer,
    UINT                wTimes
);

/// @ingroup API_GRAB
/// \~chinese
/// \brief 释放由@link #CameraGetImageBuffer @endlink获得的缓冲区。
/// \param [in] hCamera 相机的句柄。
/// \param [in] pbyBuffer 帧缓冲区地址。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Releases the buffer obtained by @link #CameraGetImageBuffer @endlink.
/// \param [in] hCamera Camera handle.
/// \param [in] pbyBuffer Frame buffer address.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraReleaseImageBuffer(
    CameraHandle    hCamera, 
    BYTE*           pbyBuffer
);

/// @ingroup API_PLAY_CTRL
/// \~chinese
/// \brief 让相机进入工作模式，开始接收来自相机发送的图像数据。
/// \param [in] hCamera 相机的句柄。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Put the camera into working mode and start receiving image data from the camera.
/// \param [in] hCamera Camera handle.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraPlay(
    CameraHandle hCamera
);

/// @ingroup API_PLAY_CTRL
/// \~chinese
/// \brief 让相机进入暂停模式，不接收来自相机的图像数据，同时也会发送命令让相机暂停输出，释放传输带宽。暂停模式下，可以对相机的参数进行配置，并立即生效。
/// \param [in] hCamera 相机的句柄。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Put the camera into pause mode, do not receive image data from the camera, and also send a command to pause the camera output and release the transmission bandwidth. In pause mode, camera parameters can be configured and take effect immediately.
/// \param [in] hCamera Camera handle.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraPause(
    CameraHandle hCamera
);

/// @ingroup API_PLAY_CTRL
/// \~chinese
/// \brief 让相机进入停止状态，一般是反初始化时调用该函数，该函数被调用，不能再对相机的参数进行配置。
/// \param [in] hCamera 相机的句柄。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Let the camera enter the stop state. Generally, this function is called when deinitializing. The function is called and the camera parameters cannot be configured.
/// \param [in] hCamera Camera handle.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraStop(
    CameraHandle hCamera
);

/// @ingroup API_RECORD
/// \~chinese
/// \brief 初始化一次录像。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iFormat 录像的格式，当前只支持不压缩和MSCV两种方式。0:不压缩 1:MSCV方式压缩。
/// \param [in] pcSavePath 录像文件保存的路径。
/// \param [in] b2GLimit 如果为TRUE,则文件大于2G时自动分割。（功能未实现）
/// \param [in] dwQuality 录像的质量因子，越大，则质量越好。范围1到100.
/// \param [in] iFrameRate 录像的帧率。建议设定的比实际采集帧率大，这样就不会漏帧。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Initialize a video.
/// \param [in] hCamera Camera handle.
/// \param [in] iFormat The video format currently supports only the uncompressed and MSCV modes. 0: No compression 1: MSCV compression.
/// \param [in] pcSavePath The path to save the video file.
/// \param [in] b2GLimit If TRUE, the file is automatically split when it is larger than 2G. (Function not implemented)
/// \param [in] dwQuality The larger the quality factor of the video, the better the quality. Range 1 to 100.
/// \param [in] iFrameRate The frame rate of the video. It is recommended to set a larger frame rate than the actual acquisition so that no frames are missed.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraInitRecord(
    CameraHandle    hCamera,
    int             iFormat,
    char*           pcSavePath,
    BOOL            b2GLimit,
    DWORD           dwQuality,
    int             iFrameRate
);

/// @ingroup API_RECORD
/// \~chinese
/// \brief 结束本次录像。当@link #CameraInitRecord @endlink后，可以通过该函数来结束一次录像，并完成文件保存操作。
/// \param [in] hCamera 相机的句柄。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief End this video. After @link #CameraInitRecord @endlink, you can use this function to end a video and complete the file save operation.
/// \param [in] hCamera Camera handle.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraStopRecord(
    CameraHandle    hCamera
);

/// @ingroup API_RECORD
/// \~chinese
/// \brief 将一帧数据存入录像流中。由于我们的帧头信息中携带了图像采集的时间戳信息，因此录像可以精准的时间同步，而不受帧率不稳定的影响。
/// \param [in] hCamera 相机的句柄。
/// \param [in] pbyImageBuffer 图像的数据缓冲区。
/// \param [in] pFrInfo 图像的帧头信息。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief One frame of data is stored in the video stream. Since our frame header information carries the timestamp information of the image acquisition, the recording can be accurately time synchronized without being affected by the instability of the frame rate.
/// \param [in] hCamera Camera handle.
/// \param [in] pbyImageBuffer Image data buffer.
/// \param [in] pFrInfo The frame header information of the image.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraPushFrame(
    CameraHandle    hCamera,
    BYTE*           pbyImageBuffer,
    tSdkFrameHead*  pFrInfo
);

/// @ingroup API_SAVE_IMAGE
/// \~chinese
/// \brief 将图像缓冲区的数据保存成图片文件。
/// \param [in] hCamera 相机的句柄。
/// \param [in] lpszFileName 图片保存文件完整路径。
/// \param [in] pbyImageBuffer 图像的数据缓冲区。
/// \param [in] pFrInfo 图像的帧头信息。
/// \param [in] byFileType 图像保存的格式。取值范围参见@link #emSdkFileType @endlink的定义。
/// \param [in] byQuality 图像保存的质量因子，仅当保存为JPG格式时该参数有效，范围1到100。其余格式可以写成0。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 目前支持 BMP、JPG、PNG、RAW四种格式。其中RAW表示相机输出的原始数据，保存RAW格式文件要求pbyImageBuffer和pFrInfo是由@link #CameraGetImageBuffer @endlink获得的数据，而且未经@link #CameraImageProcess @endlink转换成BMP格式；反之，如果要保存成BMP、JPG或者PNG格式，则pbyImageBuffer和pFrInfo是由@link #CameraImageProcess @endlink处理后的RGB格式数据。具体用法可以参考Advanced的例程。   
/// \~english
/// \brief Save the image buffer data as a picture file.
/// \param [in] hCamera Camera handle.
/// \param [in] lpszFileName The picture saves the full path to the file.
/// \param [in] pbyImageBuffer Image data buffer.
/// \param [in] pFrInfo The frame header information of the image.
/// \param [in] byFileType Image save format. See the definition of @link #emSdkFileType @endlink for the range of values.
/// \param [in] byQuality The quality factor of the saved image. This parameter is valid only when saving in JPG format. The range is from 1 to 100. The rest of the format can be written as 0.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note Currently supports BMP, JPG, PNG, RAW four formats. Among them, RAW represents the raw data output by the camera. Saving RAW format files requires pbyImageBuffer and pFrInfo to be obtained by @link #CameraGetImageBuffer @endlink, and without @link #CameraImageProcess @endlink converting to BMP format; otherwise, if you want to save to BMP JPG or PNG format, pbyImageBuffer and pFrInfo are RGB format data processed by @link #CameraImageProcess @endlink. Specific usage can refer to Advanced's routines.
MVSDK_API CameraSdkStatus __stdcall CameraSaveImage(
    CameraHandle    hCamera,
    char*           lpszFileName,
    BYTE*           pbyImageBuffer,
    tSdkFrameHead*  pFrInfo,
    UINT            byFileType,
    BYTE            byQuality
);

/// @ingroup API_SAVE_IMAGE
/// \~chinese
/// \brief 将图像缓冲区的数据保存成图片文件。
/// \param [in] hCamera 相机的句柄。
/// \param [in] lpszFileName 图片保存文件完整路径。
/// \param [in] pbyImageBuffer 图像的数据缓冲区。
/// \param [in] uImageFormat 0:8 BIT gray   1:rgb24    2:rgba32    3:bgr24    4:bgra32
/// \param [in] iWidth 图片宽度
/// \param [in] iHeight 图片高度
/// \param [in] byFileType 图像保存的格式。取值范围参见@link #emSdkFileType @endlink的定义。
/// \param [in] byQuality 图像保存的质量因子，仅当保存为JPG格式时该参数有效，范围1到100。其余格式可以写成0。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 与@link #CameraSaveImage @endlink相同
/// \~english
/// \brief Save the image buffer data as a picture file.
/// \param [in] hCamera Camera handle.
/// \param [in] lpszFileName The picture saves the full path to the file.
/// \param [in] pbyImageBuffer Image data buffer.
/// \param [in] uImageFormat 0:8 BIT gray   1:rgb24    2:rgba32    3:bgr24    4:bgra32
/// \param [in] iWidth width
/// \param [in] iHeight height
/// \param [in] byFileType Image save format. See the definition of @link #emSdkFileType @endlink for the range of values.
/// \param [in] byQuality The quality factor of the saved image. This parameter is valid only when saving in JPG format. The range is from 1 to 100. The rest of the format can be written as 0.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note Same as @link #CameraSaveImage @endlink
MVSDK_API CameraSdkStatus __stdcall CameraSaveImageEx(
	CameraHandle    hCamera,
	char*           lpszFileName,
	BYTE*           pbyImageBuffer,
	UINT			uImageFormat,
	int				iWidth,
	int				iHeight,
	UINT            byFileType,
	BYTE            byQuality
	);

/// @ingroup API_ROI
/// \~chinese
/// \brief 获得当前预览的分辨率。
/// \param [in] hCamera 相机的句柄。
/// \param [out] psCurVideoSize 返回当前的分辨率。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the current preview resolution.
/// \param [in] hCamera Camera handle.
/// \param [out] psCurVideoSize Returns the current resolution.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetImageResolution(
    CameraHandle            hCamera, 
    tSdkImageResolution*    psCurVideoSize
);

/// @ingroup API_ROI
/// \~chinese
/// \brief 获得当前预览的分辨率。
/// \param [in] hCamera 相机的句柄。
/// \param [out] iIndex		   索引号，[0,N]表示预设的分辨率(N 为预设分辨率的最大个数，一般不超过20),OXFF 表示自定义分辨率(ROI)
/// \param [out] acDescription 该分辨率的描述信息。仅预设分辨率时该信息有效。自定义分辨率可忽略该信息
/// \param [out] Mode		   0: 普通模式     1：Sum       2：Average        3：Skip        4：Resample
/// \param [out] ModeSize	   普通模式下忽略，第1位表示2X2 第二位表示3X3 ...
/// \param [out] x			   水平偏移
/// \param [out] y			   垂直偏移
/// \param [out] width		   宽
/// \param [out] height		   高
/// \param [out] ZoomWidth     最终输出时缩放宽度，0表示不缩放 
/// \param [out] ZoomHeight    最终输出时缩放高度，0表示不缩放
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the current preview resolution.
/// \param [in] hCamera Camera handle.
/// \param [out] iIndex Index number, [0,N] indicates the default resolution (N is the maximum number of preset resolutions, generally no more than 20), OXFF indicates custom resolution (ROI)
/// \param [out] acDescription Descriptive information for this resolution. This information is valid only when the resolution is preset. Custom resolution ignores this information
/// \param [out] Mode 0: Normal Mode 1:Sum 2:Average 3:Skip 4:Resample
/// \param [out] ModeSize ignored in normal mode, the first bit represents 2X2 the second bit represents 3X3 ...
/// \param [out] x horizontal offset
/// \param [out] y vertical offset
/// \param [out] width width
/// \param [out] height high
/// \param [out] ZoomWidth Scale width when final output, 0 means not zoom
/// \param [out] ZoomHeight Scales the height of the final output, 0 means no scaling
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetImageResolutionEx(
	CameraHandle            hCamera, 
	int*					iIndex,
	char					acDescription[32],
	int*					Mode,
	UINT*					ModeSize,
	int*					x,
	int*					y,
	int*					width,
	int*					height,
	int*					ZoomWidth,
	int*					ZoomHeight
	);

/// @ingroup API_ROI
/// \~chinese
/// \brief 设置预览的分辨率。
/// \param [in] hCamera 相机的句柄。
/// \param [in] pImageResolution 新分辨率。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Sets the resolution of the preview.
/// \param [in] hCamera Camera handle.
/// \param [in] pImageResolution New resolution.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetImageResolution(
    CameraHandle            hCamera, 
    tSdkImageResolution*    pImageResolution
);

/// @ingroup API_ROI
/// \~chinese
/// \brief 获得当前预览的分辨率。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iIndex		   索引号，[0,N]表示预设的分辨率(N 为预设分辨率的最大个数，一般不超过20),OXFF 表示自定义分辨率(ROI)
/// \param [in] Mode		   0: 普通模式     1：Sum       2：Average        3：Skip        4：Resample
/// \param [in] ModeSize	   普通模式下忽略，第1位表示2X2 第二位表示3X3 ...
/// \param [in] x			   水平偏移
/// \param [in] y			   垂直偏移
/// \param [in] width		   宽
/// \param [in] height		   高
/// \param [in] ZoomWidth     最终输出时缩放宽度，0表示不缩放 
/// \param [in] ZoomHeight    最终输出时缩放高度，0表示不缩放
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the current preview resolution.
/// \param [in] hCamera Camera handle.
/// \param [in] iIndex Index number, [0,N] indicates the default resolution (N is the maximum number of preset resolutions, generally no more than 20), OXFF indicates custom resolution (ROI)
/// \param [in] Mode 0: Normal Mode 1:Sum 2:Average 3:Skip 4:Resample
/// \param [in] ModeSize ignored in normal mode, the first bit represents 2X2 the second bit represents 3X3 ...
/// \param [in] x horizontal offset
/// \param [in] y vertical offset
/// \param [in] width width
/// \param [in] height high
/// \param [in] ZoomWidth Scale width when final output, 0 means not zoom
/// \param [in] ZoomHeight Scales the height of the final output, 0 means no scaling
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetImageResolutionEx(
	CameraHandle            hCamera, 
	int						iIndex,
	int						Mode,
	UINT					ModeSize,
	int						x,
	int						y,
	int						width,
	int						height,
	int						ZoomWidth,
	int						ZoomHeight
	);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 获得相机当前输出原始数据的格式索引号。
/// \param [in] hCamera 相机的句柄。
/// \param [out] piMediaType 返回当前格式类型的索引号。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 在@link #tSdkCameraCapbility.pMediaTypeDesc @endlink成员中，以数组的形式保存了相机支持的格式，piMediaType所指向的索引号，就是该数组的索引号。
/// \~english
/// \brief Gets the format index number of the camera's current output raw data.
/// \param [in] hCamera Camera handle.
/// \param [out] piMediaType Returns the index of the current format type.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note In the @link #tSdkCameraCapbility.pMediaTypeDesc @endlink member, the format supported by the camera is saved as an array. The index number pointed to by piMediaType is the index number of the array.
MVSDK_API CameraSdkStatus __stdcall CameraGetMediaType(
    CameraHandle    hCamera, 
    INT*            piMediaType
);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 设置相机的输出原始数据格式。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iMediaType 新格式类型的索引号。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 与@link #CameraGetMediaType @endlink相同。
/// \~english
/// \brief Sets the camera's output raw data format.
/// \param [in] hCamera Camera handle.
/// \param [in] iMediaType The index number of the new format type.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note Same as @link #CameraGetMediaType @endlink.
MVSDK_API CameraSdkStatus __stdcall CameraSetMediaType(
    CameraHandle    hCamera, 
    INT             iMediaType
);

/// @ingroup API_EXPOSURE
/// \~chinese
/// \brief 设置相机曝光的模式。自动或者手动。
/// \param [in] hCamera 相机的句柄。
/// \param [in] bAeState TRUE:自动曝光；FALSE:手动曝光。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set the camera exposure mode. Automatic or manual.
/// \param [in] hCamera Camera handle.
/// \param [in] bAeState TRUE: Auto exposure; FALSE: Manual exposure.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetAeState(
    CameraHandle    hCamera, 
    BOOL            bAeState
);

/// @ingroup API_EXPOSURE
/// \~chinese
/// \brief 获得相机当前的曝光模式。
/// \param [in] hCamera 相机的句柄。
/// \param [out] pAeState 返回自动曝光的使能状态。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the camera's current exposure mode.
/// \param [in] hCamera Camera handle.
/// \param [out] pAeState Returns the auto exposure's enable state.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetAeState(
    CameraHandle    hCamera, 
    BOOL*           pAeState
);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 设置图像的处理的锐化参数。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iSharpness 锐化参数，一般是[0,100]，0表示关闭锐化处理。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Sets the sharpening parameters for the processing of the image.
/// \param [in] hCamera Camera handle.
/// \param [in] iSharpness Sharpen parameter, generally [0,100], 0 means close sharpening.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetSharpness(
    CameraHandle    hCamera, 
    int             iSharpness
);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 获取当前锐化设定值。
/// \param [in] hCamera 相机的句柄。
/// \param [out] piSharpness 返回当前设定的锐化的设定值。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Gets the current sharpening setting.
/// \param [in] hCamera Camera handle.
/// \param [out] piSharpness Returns the currently set sharpened setting.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetSharpness(
    CameraHandle    hCamera, 
    int*            piSharpness
);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 设置相机的查表变换模式LUT模式。
/// \param [in] hCamera 相机的句柄。
/// \param [in] emLutMode 定义参考@link #emSdkLutMode @endlink类型。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set the camera's lookup table transformation mode LUT mode.
/// \param [in] hCamera Camera handle.
/// \param [in] emLutMode Defines the reference @link #emSdkLutMode @endlink type.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetLutMode(
    CameraHandle    hCamera,
    int             emLutMode
);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 获得相机的查表变换模式LUT模式。
/// \param [in] hCamera 相机的句柄。
/// \param [out] pemLutMode 返回当前LUT模式。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Obtain the look-up table conversion mode LUT mode of the camera.
/// \param [in] hCamera Camera handle.
/// \param [out] pemLutMode Returns the current LUT mode.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetLutMode(
    CameraHandle    hCamera,
    int*            pemLutMode
);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 选择预设LUT模式下的LUT表。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iSel 表的索引号。表的个数由@link #tSdkCameraCapbility.iPresetLut @endlink获得。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 必须先使用@link #CameraSetLutMode @endlink将LUT模式设置为预设模式。
/// \~english
/// \brief Select the LUT table in the preset LUT mode.
/// \param [in] hCamera Camera handle.
/// \param [in] iSel The index number of the lut table. The number of tables is obtained by @link #tSdkCameraCapbility.iPresetLut @endlink.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note Must use @link #CameraSetLutMode @endlink to set LUT mode to preset mode.
MVSDK_API CameraSdkStatus __stdcall CameraSelectLutPreset(
    CameraHandle    hCamera,
    int             iSel
);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 获得预设LUT模式下的LUT表索引号。
/// \param [in] hCamera 相机的句柄。
/// \param [out] piSel  返回表的索引号。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief The LUT table index number in the preset LUT mode is obtained.
/// \param [in] hCamera Camera handle.
/// \param [out] piSel Returns the index number of the table.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetLutPresetSel(
    CameraHandle    hCamera,
    int*            piSel
);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 设置自定义的LUT表。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iChannel 指定要设定的LUT颜色通道，当为@link #LUT_CHANNEL_ALL @endlink时，三个通道的LUT将被同时替换。@see emSdkLutChannel
/// \param [in] pLut     指针，指向LUT表的地址。LUT表为无符号短整形数组，数组大小为4096，分别代码颜色通道从0到4096(12bit颜色精度)对应的映射值。 
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 必须先使用@link #CameraSetLutMode @endlink将LUT模式设置为自定义模式。
/// \~english
/// \brief Set up a custom LUT table.
/// \param [in] hCamera Camera handle.
/// \param [in] iChannel Specifies the LUT color channel to be set. When @link #LUT_CHANNEL_ALL @endlink, the three-channel LUTs will be replaced at the same time. @see emSdkLutChannel
/// \param [in] pLut pointer to the address of the LUT table. The LUT table is an unsigned short integer array, and the array size is 4096, which is the mapping value corresponding to the code color channel from 0 to 4096 (12 bit color accuracy).
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note You must use @link #CameraSetLutMode @endlink to set the LUT mode to custom mode.
MVSDK_API CameraSdkStatus __stdcall CameraSetCustomLut(
    CameraHandle    hCamera,
    int       iChannel,
    USHORT*         pLut
);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 获得当前使用的自定义LUT表。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iChannel 指定要获取的LUT颜色通道，当为@link #LUT_CHANNEL_ALL @endlink时，返回红色通道的LUT表。@see emSdkLutChannel
/// \param [out] pLut    指向LUT表的地址。LUT表为无符号短整形数组，数组大小为4096，分别代码颜色通道从0到4096(12bit颜色精度)对应的映射值。 
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the currently used custom LUT table.
/// \param [in] hCamera Camera handle.
/// \param [in] iChannel Specifies the LUT color channel to be obtained. When @link #LUT_CHANNEL_ALL @endlink, returns the LUT table of the red channel. @see emSdkLutChannel
/// \param [out] pLut points to the address of the LUT table. The LUT table is an unsigned short integer array, and the array size is 4096, which is the mapping value corresponding to the code color channel from 0 to 4096 (12 bit color accuracy).
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetCustomLut(
    CameraHandle    hCamera,
    int       iChannel,
    USHORT*         pLut
);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 获得相机当前的LUT表，在任何LUT模式下都可以调用,用来直观的观察LUT曲线的变化。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iChannel 指定要获取的LUT颜色通道，当为@link #LUT_CHANNEL_ALL @endlink时，返回红色通道的LUT表。@see emSdkLutChannel
/// \param [out] pLut    指向LUT表的地址。LUT表为无符号短整形数组，数组大小为4096，分别代码颜色通道从0到4096(12bit颜色精度)对应的映射值。 
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Obtain the camera's current LUT table, which can be called in any LUT mode, to intuitively observe changes in the LUT curve.
/// \param [in] hCamera Camera handle.
/// \param [in] iChannel Specifies the LUT color channel to be obtained. When @link #LUT_CHANNEL_ALL @endlink, returns the LUT table of the red channel. @see emSdkLutChannel
/// \param [out] pLut points to the address of the LUT table. The LUT table is an unsigned short integer array, and the array size is 4096, which is the mapping value corresponding to the code color channel from 0 to 4096 (12 bit color accuracy).
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetCurrentLut(
    CameraHandle    hCamera,
    int       iChannel,
    USHORT*         pLut
);

/// @ingroup API_COLOR
/// \~chinese
/// \brief 设置相机白平衡模式。分为手动和自动两种方式。
/// \param [in] hCamera 相机的句柄。
/// \param [in] bAuto TRUE，则表示使能自动模式。 FALSE，则表示使用手动模式，通过调用@link #CameraSetOnceWB @endlink来进行一次白平衡。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set camera white balance mode. Divided into manual and automatic two ways.
/// \param [in] hCamera Camera handle.
/// \param [in] bAuto TRUE to enable auto mode. FALSE indicates that using manual mode, a white balance is performed by calling @link #CameraSetOnceWB @endlink.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetWbMode(
    CameraHandle    hCamera,
    BOOL            bAuto
);

/// @ingroup API_COLOR
/// \~chinese
/// \brief 获得当前的白平衡模式。
/// \param [in] hCamera 相机的句柄。
/// \param [out] pbAuto   指针，返回TRUE表示自动模式，FALSE为手动模式。 
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the current white balance mode.
/// \param [in] hCamera Camera handle.
/// \param [out] pbAuto pointer, return TRUE for automatic mode, FALSE for manual mode.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetWbMode(
    CameraHandle    hCamera,
    BOOL*           pbAuto
);

/// @ingroup API_COLOR
/// \~chinese
/// \brief 选择指定预设色温模式
/// \param [in] hCamera 相机的句柄。
/// \param [in] iSel 预设色温的模式索引号，从0开始
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 调用@link #CameraSetClrTempMode @endlink设置为预设模式。
/// \~english
/// \brief Select the specified preset color temperature mode
/// \param [in] hCamera Camera handle.
/// \param [in] iSel The mode index number of the preset color temperature, starting from 0
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note Call @link #CameraSetClrTempMode @endlink set to preset mode.
MVSDK_API CameraSdkStatus __stdcall CameraSetPresetClrTemp(
    CameraHandle    hCamera,
    int             iSel
);

/// @ingroup API_COLOR
/// \~chinese
/// \brief 获得当前选择的预设色温模式。
/// \param [in] hCamera 相机的句柄。
/// \param [out] piSel  返回选择的预设色温索引号
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the currently selected preset color temperature mode.
/// \param [in] hCamera Camera handle.
/// \param [out] piSel Returns the selected preset color temperature index number
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetPresetClrTemp(
    CameraHandle    hCamera,
    int*            piSel
);

/// @ingroup API_COLOR
/// \~chinese
/// \brief 设置自定义色温模式下的数字增益
/// \param [in] hCamera 相机的句柄。
/// \param [in] iRgain  红色增益，范围0到400，表示0到4倍
/// \param [in] iGgain  绿色增益，范围0到400，表示0到4倍
/// \param [in] iBgain  蓝色增益，范围0到400，表示0到4倍
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 调用@link #CameraSetClrTempMode @endlink设置为自定义模式。
/// \~english
/// \brief Set digital gain in custom color temperature mode
/// \param [in] hCamera Camera handle.
/// \param [in] iRgain Red gain, range 0 to 400, 0 to 4 times
/// \param [in] iGgain Green gain, range 0 to 400, 0 to 4 times
/// \param [in] iBgain Blue gain, range 0 to 400, 0 to 4 times
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note Call @link #CameraSetClrTempMode @endlink set to custom mode.
MVSDK_API CameraSdkStatus __stdcall CameraSetUserClrTempGain(
  CameraHandle  hCamera,
  int       iRgain,
  int       iGgain,
  int       iBgain
);

/// @ingroup API_COLOR
/// \~chinese
/// \brief 获得自定义色温模式下的数字增益
/// \param [in] hCamera 相机的句柄。
/// \param [out] piRgain  指针，返回红色增益，范围0到400，表示0到4倍
/// \param [out] piGgain  指针，返回绿色增益，范围0到400，表示0到4倍
/// \param [out] piBgain  指针，返回蓝色增益，范围0到400，表示0到4倍
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get digital gain in custom color temperature mode
/// \param [in] hCamera Camera handle.
/// \param [out] piRgain pointer, returning red gain, range 0 to 400, 0 to 4 times
/// \param [out] piGgain pointer, return green gain, range 0 to 400, 0 to 4 times
/// \param [out] piBgain pointer, returns blue gain, range 0 to 400, 0 to 4 times
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetUserClrTempGain(
  CameraHandle  hCamera,
  int*      piRgain,
  int*      piGgain,
  int*      piBgain
);

/// @ingroup API_COLOR
/// \~chinese
/// \brief 设置自定义色温模式下的颜色矩阵
/// \param [in] hCamera 相机的句柄。
/// \param [in] pMatrix 指向一个float[3][3]数组的首地址
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 调用@link #CameraSetClrTempMode @endlink设置为自定义模式。
/// \~english
/// \brief Set the color matrix in custom color temperature mode
/// \param [in] hCamera Camera handle.
/// \param [in] pMatrix points to the first address of an array of float[3][3]
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note Call @link #CameraSetClrTempMode @endlink set to custom mode.
MVSDK_API CameraSdkStatus __stdcall CameraSetUserClrTempMatrix(
  CameraHandle  hCamera,
  float*      pMatrix
);

/// @ingroup API_COLOR
/// \~chinese
/// \brief 获得自定义色温模式下的颜色矩阵
/// \param [in] hCamera 相机的句柄。
/// \param [out] pMatrix 指向一个float[3][3]数组的首地址
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the color matrix in a custom color temperature mode
/// \param [in] hCamera Camera handle.
/// \param [out] pMatrix points to the first address of an array of float[3][3]
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetUserClrTempMatrix(
  CameraHandle  hCamera,
  float*      pMatrix
);

/// @ingroup API_COLOR
/// \~chinese
/// \brief 设置白平衡时使用的色温模式
/// \param [in] hCamera 相机的句柄。
/// \param [in] iMode 模式，只能是@link #emSdkClrTmpMode @endlink中定义的一种
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 支持的模式有三种，分别是自动，预设和自定义。
/// \note 自动模式下，会自动选择合适的色温模式
/// \note 预设模式下，会使用用户指定的色温模式
/// \note 自定义模式下，使用用户自定义的色温数字增益和矩阵
/// \~english
/// \brief Color temperature mode used when setting white balance
/// \param [in] hCamera Camera handle.
/// \param [in] iMode mode, can only be defined by @link #emSdkClrTmpMode @endlink
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note There are three supported modes, automatic, preset, and custom.
/// \note Automatic mode will automatically select the appropriate color temperature mode
/// \note In preset mode, user-specified color temperature mode is used
/// \note custom-defined color temperature digital gain and matrix
MVSDK_API CameraSdkStatus __stdcall CameraSetClrTempMode(
  CameraHandle  hCamera,
  int       iMode
);

/// @ingroup API_COLOR
/// \~chinese
/// \brief 获得白平衡时使用的色温模式。参考@link #CameraSetClrTempMode @endlink中功能描述部分。
/// \param [in] hCamera 相机的句柄。
/// \param [out] pimode 指针，返回模式选择，参考@link #emSdkClrTmpMode @endlink类型定义
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief The color temperature mode used when obtaining white balance. Refer to the function description section of @link #CameraSetClrTempMode @endlink.
/// \param [in] hCamera Camera handle.
/// \param [out] pimode pointer, return mode selection, reference @link #emSdkClrTmpMode @endlink type definition
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetClrTempMode(
  CameraHandle  hCamera,
  int*      pimode
);

/// @ingroup API_COLOR
/// \~chinese
/// \brief 在手动白平衡模式下，调用该函数会进行一次白平衡。生效的时间为接收到下一帧图像数据时。
/// \param [in] hCamera 相机的句柄。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief In manual white balance mode, calling this function will perform a white balance. The effective time is when the next frame of image data is received.
/// \param [in] hCamera Camera handle.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetOnceWB(
    CameraHandle    hCamera
);

/// @ingroup API_COLOR
/// \~chinese
/// \brief 执行一次黑平衡操作。（需要相机支持本功能）
/// \param [in] hCamera 相机的句柄。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Performs a black balance operation. (Requires camera support for this feature)
/// \param [in] hCamera Camera handle.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetOnceBB(
    CameraHandle    hCamera
);

/// @ingroup API_EXPOSURE
/// \~chinese
/// \brief 设定自动曝光的亮度目标值。设定范围[@link #tSdkExpose.uiTargetMin @endlink, @link #tSdkExpose.uiTargetMax @endlink]
/// \param [in] hCamera 相机的句柄。
/// \param [in] iAeTarget 亮度目标值。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Sets the brightness target for auto exposure. Setting range [@link #tSdkExpose.uiTargetMin @endlink, @link #tSdkExpose.uiTargetMax @endlink]
/// \param [in] hCamera Camera handle.
/// \param [in] iAeTarget Brightness target value.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetAeTarget(
    CameraHandle    hCamera, 
    int             iAeTarget
);

/// @ingroup API_EXPOSURE
/// \~chinese
/// \brief 获得自动曝光的亮度目标值。
/// \param [in] hCamera 相机的句柄。
/// \param [out] piAeTarget 指针，返回目标值。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the auto exposure's brightness target value.
/// \param [in] hCamera Camera handle.
/// \param [out] piAeTarget pointer, return target value.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetAeTarget(
    CameraHandle    hCamera, 
    int*            piAeTarget
);

/// @ingroup API_EXPOSURE
/// \~chinese
/// \brief 设定自动曝光模式的曝光时间调节范围
/// \param [in] hCamera 相机的句柄。
/// \param [in] fMinExposureTime 最小曝光时间（微秒）
/// \param [in] fMaxExposureTime 最大曝光时间（微秒）
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Setting the exposure time adjustment range of the automatic exposure mode
/// \param [in] hCamera Camera handle.
/// \param [in] fMinExposureTime Minimum exposure time (microseconds)
/// \param [in] fMaxExposureTime Maximum exposure time (microseconds)
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetAeExposureRange(
	CameraHandle    hCamera, 
	double          fMinExposureTime,
	double			fMaxExposureTime
	);

/// @ingroup API_EXPOSURE
/// \~chinese
/// \brief 获得自动曝光模式的曝光时间调节范围
/// \param [in] hCamera 相机的句柄。
/// \param [out] fMinExposureTime 最小曝光时间（微秒）
/// \param [out] fMaxExposureTime 最大曝光时间（微秒）
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Exposure time adjustment range for automatic exposure mode
/// \param [in] hCamera Camera handle.
/// \param [out] fMinExposureTime Minimum exposure time (microseconds)
/// \param [out] fMaxExposureTime Maximum exposure time (microseconds)
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetAeExposureRange(
	CameraHandle    hCamera, 
	double*         fMinExposureTime,
	double*			fMaxExposureTime
	);

/// @ingroup API_EXPOSURE
/// \~chinese
/// \brief 设定自动曝光模式的增益调节范围
/// \param [in] hCamera 相机的句柄。
/// \param [in] iMinAnalogGain 最小增益
/// \param [in] iMaxAnalogGain 最大增益
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Setting the gain adjustment range of the automatic exposure mode
/// \param [in] hCamera Camera handle.
/// \param [in] iMinAnalogGain minimum gain
/// \param [in] iMaxAnalogGain maximum gain
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetAeAnalogGainRange(
	CameraHandle    hCamera, 
	int				iMinAnalogGain,
	int				iMaxAnalogGain
	);

/// @ingroup API_EXPOSURE
/// \~chinese
/// \brief 获得自动曝光模式的增益调节范围
/// \param [in] hCamera 相机的句柄。
/// \param [out] iMinAnalogGain 最小增益
/// \param [out] iMaxAnalogGain 最大增益
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Gain adjustment range for automatic exposure mode
/// \param [in] hCamera Camera handle.
/// \param [out] iMinAnalogGain minimum gain
/// \param [out] iMaxAnalogGain maximum gain
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetAeAnalogGainRange(
	CameraHandle    hCamera, 
	int*			iMinAnalogGain,
	int*			iMaxAnalogGain
	);

/// @ingroup API_EXPOSURE
/// \~chinese
/// \brief 设置自动曝光模式的调节阈值
/// \param [in] hCamera 相机的句柄。
/// \param [in] iThreshold   如果 abs(目标亮度-图像亮度) < iThreshold 则停止自动调节
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set the adjustment threshold for auto exposure mode
/// \param [in] hCamera Camera handle.
/// \param [in] iThreshold Stops automatic adjustment if abs (target brightness - image brightness) < iThreshold
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetAeThreshold(
	CameraHandle    hCamera, 
	int				iThreshold
	);

/// @ingroup API_EXPOSURE
/// \~chinese
/// \brief 获取自动曝光模式的调节阈值
/// \param [in] hCamera 相机的句柄。
/// \param [out] iThreshold   读取到的调节阈值
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get adjustment threshold for auto exposure mode
/// \param [in] hCamera Camera handle.
/// \param [out] iThreshold Read Threshold
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetAeThreshold(
	CameraHandle    hCamera, 
	int*			iThreshold
	);

/// @ingroup API_EXPOSURE
/// \~chinese
/// \brief 设置曝光时间。单位为微秒。
/// \param [in] hCamera 相机的句柄。
/// \param [in] fExposureTime 曝光时间，单位微秒。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 对于CMOS传感器，其曝光的单位是按照行来计算的，因此，曝光时间并不能在微秒级别连续可调。而是会按照整行来取舍。在调用本函数设定曝光时间后，建议再调用@link #CameraGetExposureTime @endlink来获得实际设定的值。
/// \~english
/// \brief Set the exposure time. The unit is microseconds.
/// \param [in] hCamera Camera handle.
/// \param [in] fExposureTime Exposure time in microseconds.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note For CMOS sensors, the unit of exposure is calculated in rows, so the exposure time cannot be continuously adjusted in microseconds. Instead, the entire line will be chosen. After calling this function to set the exposure time, it is recommended to call @link #CameraGetExposureTime @endlink to get the actual set value.
MVSDK_API CameraSdkStatus __stdcall CameraSetExposureTime(
    CameraHandle    hCamera, 
    double          fExposureTime
);

/// @ingroup API_EXPOSURE
/// \~chinese
/// \brief 获得一行的曝光时间。
/// \param [in] hCamera 相机的句柄。
/// \param [out] pfLineTime 指针，返回一行的曝光时间，单位为微秒。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 对于CMOS传感器，其曝光的单位是按照行来计算的，因此，曝光时间并不能在微秒级别连续可调。而是会按照整行来取舍。这个函数的作用就是返回CMOS相机曝光一行对应的时间。
/// \~english
/// \brief Get a line of exposure time.
/// \param [in] hCamera Camera handle.
/// \param [out] pfLineTime returns the exposure time of one line in microseconds.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note For CMOS sensors, the unit of exposure is calculated in rows, so the exposure time cannot be continuously adjusted in microseconds. Instead, the entire line will be chosen. The function of this function is to return the CMOS camera exposure one line corresponding time.
MVSDK_API CameraSdkStatus __stdcall CameraGetExposureLineTime(
    CameraHandle    hCamera, 
    double*         pfLineTime
);

/// @ingroup API_EXPOSURE
/// \~chinese
/// \brief 获得相机的曝光时间。
/// \param [in] hCamera 相机的句柄。
/// \param [out] pfExposureTime   指针，返回当前的曝光时间，单位微秒。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \see CameraSetExposureTime
/// \~english
/// \brief Get camera exposure time.
/// \param [in] hCamera Camera handle.
/// \param [out] pfExposureTime returns the current exposure time in microseconds.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \see CameraSetExposureTime
MVSDK_API CameraSdkStatus __stdcall CameraGetExposureTime(
    CameraHandle    hCamera, 
    double*         pfExposureTime
);

/// @ingroup API_EXPOSURE
/// \~chinese
/// \brief 获得相机的曝光时间范围
/// \param [in] hCamera 相机的句柄。
/// \param [out] pfMin		指针，返回曝光时间的最小值，单位微秒。
/// \param [out] pfMax		指针，返回曝光时间的最大值，单位微秒。
/// \param [out] pfStep		指针，返回曝光时间的步进值，单位微秒。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get camera exposure time range
/// \param [in] hCamera Camera handle.
/// \param [out] pfMin Returns the minimum exposure time in microseconds.
/// \param [out] pfMax Returns the maximum exposure time in microseconds.
/// \param [out] pfStep Returns the exposure time in microseconds.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetExposureTimeRange(
	CameraHandle    hCamera, 
	double*         pfMin,
	double*			pfMax,
	double*			pfStep
	);

/// @ingroup API_EXPOSURE
/// \~chinese
/// \brief 设置相机的图像模拟增益值。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iAnalogGain 设定的模拟增益值。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 该值乘以@link #tSdkExpose.fAnalogGainStep @endlink，就得到实际的图像信号放大倍数。
/// \~english
/// \brief Set the camera's image analog gain value.
/// \param [in] hCamera Camera handle.
/// \param [in] iAnalogGain gain value set
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note This value is multiplied by @link #tSdkExpose.fAnalogGainStep @endlink to get the actual image signal magnification.
MVSDK_API CameraSdkStatus __stdcall CameraSetAnalogGain(
    CameraHandle    hCamera,
    INT             iAnalogGain
);

/// @ingroup API_EXPOSURE
/// \~chinese
/// \brief 获得图像信号的模拟增益值。
/// \param [in] hCamera 相机的句柄。
/// \param [out] piAnalogGain 指针，返回当前的模拟增益值。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \see CameraSetAnalogGain
/// \~english
/// \brief Obtain the analog gain value of the image signal.
/// \param [in] hCamera Camera handle.
/// \param [out] piAnalogGain Returns the current analog gain value.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \see CameraSetAnalogGain
MVSDK_API CameraSdkStatus __stdcall CameraGetAnalogGain(
    CameraHandle    hCamera, 
    INT*            piAnalogGain
);

/// @ingroup API_COLOR
/// \~chinese
/// \brief 设置图像的数字增益。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iRGain   红色通道的增益值。 
/// \param [in] iGGain   绿色通道的增益值。
/// \param [in] iBGain   蓝色通道的增益值。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 设定范围由@link #tRgbGainRange @endlink成员表述。实际的放大倍数是设定值/100。
/// \~english
/// \brief Set the digital gain of the image.
/// \param [in] hCamera Camera handle.
/// \param [in] iRGain The gain value of the red channel.
/// \param [in] iGGain Gain value of green channel.
/// \param [in] iBGain The gain value of the blue channel.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note The set scope is described by the @link #tRgbGainRange @endlink member. The actual magnification is the setting /100.
MVSDK_API CameraSdkStatus __stdcall CameraSetGain(
    CameraHandle    hCamera, 
    int             iRGain, 
    int             iGGain, 
    int             iBGain
);

/// @ingroup API_COLOR
/// \~chinese
/// \brief 获得图像处理的数字增益。
/// \param [in] hCamera 相机的句柄。
/// \param [out] piRGain  指针，返回红色通道的数字增益值。
/// \param [out] piGGain    指针，返回绿色通道的数字增益值。
/// \param [out] piBGain    指针，返回蓝色通道的数字增益值。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \see CameraSetGain
/// \~english
/// \brief Get the digital gain of image processing.
/// \param [in] hCamera Camera handle.
/// \param [out] piRGain Returns the digital gain value of the red channel.
/// \param [out] piGGain Returns the digital gain value of the green channel.
/// \param [out] piBGain Returns the digital gain value of the blue channel.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \see CameraSetGain
MVSDK_API CameraSdkStatus __stdcall CameraGetGain(
    CameraHandle    hCamera, 
    int*            piRGain, 
    int*            piGGain, 
    int*            piBGain
);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 设定LUT动态生成模式下的Gamma值。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iGamma     要设定的Gamma值。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 设定的值会马上保存在SDK内部，但是只有当相机处于动态参数生成的LUT模式时，才会生效。请参考@link #CameraSetLutMode @endlink的函数说明部分。
/// \~english
/// \brief Set the gamma value in LUT dynamic generation mode.
/// \param [in] hCamera Camera handle.
/// \param [in] iGamma The gamma to be set.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note The set value will be stored in the SDK immediately, but it will only take effect when the camera is in LUT mode generated by dynamic parameters. Please refer to the function description part of @link #CameraSetLutMode @endlink.
MVSDK_API CameraSdkStatus __stdcall CameraSetGamma(
    CameraHandle    hCamera, 
    int             iGamma
);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 获得LUT动态生成模式下的Gamma值
/// \param [in] hCamera 相机的句柄。
/// \param [out] piGamma    指针，返回当前的Gamma值。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \see CameraSetGamma
/// \~english
/// \brief Get gamma value in LUT dynamic generation mode
/// \param [in] hCamera Camera handle.
/// \param [out] piGamma Returns the current gamma value.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \see CameraSetGamma
MVSDK_API CameraSdkStatus __stdcall CameraGetGamma(
    CameraHandle    hCamera, 
    int*            piGamma
);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 设定LUT动态生成模式下的对比度值。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iContrast  设定的对比度值。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 设定的值会马上保存在SDK内部，但是只有当相机处于动态参数生成的LUT模式时，才会生效。请参考@link #CameraSetLutMode @endlink的函数说明部分。
/// \~english
/// \brief Sets the contrast value in LUT dynamic generation mode.
/// \param [in] hCamera Camera handle.
/// \param [in] iContrast Contrast value set by iContrast.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note The set value will be stored in the SDK immediately, but it will only take effect when the camera is in LUT mode generated by dynamic parameters. Please refer to the function description part of @link #CameraSetLutMode @endlink.
MVSDK_API CameraSdkStatus __stdcall CameraSetContrast(
    CameraHandle    hCamera, 
    int             iContrast
);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 获得LUT动态生成模式下的对比度值。
/// \param [in] hCamera 相机的句柄。
/// \param [out] piContrast 指针，返回当前的对比度值。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \see CameraSetContrast
/// \~english
/// \brief Get the contrast value in LUT dynamic generation mode.
/// \param [in] hCamera Camera handle.
/// \param [out] piContrast Returns the current contrast value.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \see CameraSetContrast
MVSDK_API CameraSdkStatus __stdcall CameraGetContrast(
    CameraHandle    hCamera, 
    int*            piContrast
);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 设定图像处理的饱和度。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iSaturation  设定的饱和度值。 
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 对黑白相机无效。设定范围由@link #tSaturationRange @endlink获得。100表示原始色度，不增强。
/// \~english
/// \brief Sets the saturation of image processing.
/// \param [in] hCamera Camera handle.
/// \param [in] iSaturation saturation value.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note is not valid for black and white cameras. The setting range is obtained by @link #tSaturationRange @endlink. 100 represents the original color and is not enhanced.
MVSDK_API CameraSdkStatus __stdcall CameraSetSaturation(
    CameraHandle    hCamera, 
    int             iSaturation
);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 获得图像处理的饱和度。
/// \param [in] hCamera 相机的句柄。
/// \param [out] piSaturation 指针，返回当前图像处理的饱和度值。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \see CameraSetSaturation
/// \~english
/// \brief Get image processing saturation.
/// \param [in] hCamera Camera handle.
/// \param [out] piSaturation Returns the saturation value of the current image processing.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \see CameraSetSaturation
MVSDK_API CameraSdkStatus __stdcall CameraGetSaturation(
    CameraHandle    hCamera, 
    int*            piSaturation
);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 设置彩色转为黑白功能的使能。
/// \param [in] hCamera 相机的句柄。
/// \param [in] bEnable   TRUE，表示将彩色图像转为黑白。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set the color to mono function enable.
/// \param [in] hCamera Camera handle.
/// \param [in] bEnable TRUE to change the color image to black and white.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetMonochrome(
    CameraHandle    hCamera, 
    BOOL            bEnable
);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 获得彩色转换黑白功能的使能状况。
/// \param [in] hCamera 相机的句柄。
/// \param [out] pbEnable   指针。返回TRUE表示开启了彩色图像转换为黑白图像的功能。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \see CameraSetMonochrome
/// \~english
/// \brief Get the status of enabling black and white color conversion.
/// \param [in] hCamera Camera handle.
/// \param [out] pbEnable Returns TRUE to enable the conversion of a color image to a mono image.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \see CameraSetMonochrome
MVSDK_API CameraSdkStatus __stdcall CameraGetMonochrome(
    CameraHandle    hCamera, 
    BOOL*           pbEnable
);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 设置彩图像颜色翻转功能的使能。
/// \param [in] hCamera 相机的句柄。
/// \param [in] bEnable    TRUE，表示开启图像颜色翻转功能，可以获得类似胶卷底片的效果。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set the enable for the color image color flip function.
/// \param [in] hCamera Camera handle.
/// \param [in] bEnable TRUE, means that the image color flip function is enabled, and the effect of similar film negatives can be obtained.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetInverse(
    CameraHandle    hCamera, 
    BOOL            bEnable
);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 获得图像颜色反转功能的使能状态。
/// \param [in] hCamera 相机的句柄。
/// \param [out] pbEnable   指针，返回该功能使能状态。 
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the status of the image color inversion function.
/// \param [in] hCamera Camera handle.
/// \param [out] pbEnable Returns this function enable state.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetInverse(
    CameraHandle    hCamera, 
    BOOL*           pbEnable
);

/// @ingroup API_EXPOSURE
/// \~chinese
/// \brief 设置自动曝光时抗频闪功能的使能状态。
/// \param [in] hCamera 相机的句柄。
/// \param [in] bEnable    TRUE，开启抗频闪功能;FALSE，关闭该功能。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 对于手动曝光模式下无效。
/// \~english
/// \brief Set the anti-strobe function's enable state during auto exposure.
/// \param [in] hCamera Camera handle.
/// \param [in] bEnable TRUE, enable anti-strobe function; FALSE, disable this function.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note Not valid for manual exposure mode.
MVSDK_API CameraSdkStatus __stdcall CameraSetAntiFlick(
    CameraHandle    hCamera,
    BOOL            bEnable
);

/// @ingroup API_EXPOSURE
/// \~chinese
/// \brief 获得自动曝光时抗频闪功能的使能状态。
/// \param [in] hCamera 相机的句柄。
/// \param [out] pbEnable   指针，返回该功能的使能状态。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the anti-strobe function's enable state during auto exposure.
/// \param [in] hCamera Camera handle.
/// \param [out] pbEnable Returns the enable state of this function.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetAntiFlick(
    CameraHandle    hCamera, 
    BOOL*           pbEnable
);

/// @ingroup API_EXPOSURE
/// \~chinese
/// \brief 获得自动曝光时，消频闪的频率选择。
/// \param [in] hCamera 相机的句柄。
/// \param [out] piFrequencySel 指针，返回选择的索引号。0:50HZ 1:60HZ
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief When the auto exposure is obtained, the frequency of the deflashing is selected.
/// \param [in] hCamera Camera handle.
/// \param [out] piFrequencySel Returns the selected index number. 0:50HZ 1:60HZ
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetLightFrequency(
    CameraHandle    hCamera, 
    int*            piFrequencySel
);

/// @ingroup API_EXPOSURE
/// \~chinese
/// \brief 设置自动曝光时消频闪的频率。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iFrequencySel 0:50HZ , 1:60HZ 
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Sets the frequency at which the flash disappears during auto exposure.
/// \param [in] hCamera Camera handle.
/// \param [in] iFrequencySel 0:50HZ , 1:60HZ 
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetLightFrequency(
    CameraHandle    hCamera,
    int             iFrequencySel
);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 设定相机输出图像的帧率。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iFrameSpeed 选择的帧率模式索引号，范围从0到tSdkCameraCapbility.iFrameSpeedDesc - 1
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Sets the frame rate of the camera output image.
/// \param [in] hCamera Camera handle.
/// \param [in] iFrameSpeed Frame rate index, ranging from 0 to tSdkCameraCapbility.iFrameSpeedDesc - 1
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetFrameSpeed(
    CameraHandle    hCamera, 
    int             iFrameSpeed
);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 获得相机输出图像的帧率选择索引号。
/// \param [in] hCamera 相机的句柄。
/// \param [out] piFrameSpeed 返回选择的帧率模式索引号。 
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \see CameraSetFrameSpeed
/// \~english
/// \brief Obtain the frame rate selection index number of the camera output image.
/// \param [in] hCamera Camera handle.
/// \param [out] piFrameSpeed Returns the selected frame rate mode index number.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \see CameraSetFrameSpeed
MVSDK_API CameraSdkStatus __stdcall CameraGetFrameSpeed(
    CameraHandle    hCamera, 
    int*            piFrameSpeed
);

/// @ingroup API_PARAMETERS
/// \~chinese
/// \brief 设定参数存取的目标对象。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iMode  参数存取的对象。参考@link #emSdkParameterMode @endlink
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Sets the target object for parameter access.
/// \param [in] hCamera Camera handle.
/// \param [in] iMode The object accessed by the iMode parameter. Reference @link #emSdkParameterMode @endlink
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetParameterMode(
    CameraHandle    hCamera, 
    int             iMode
);

/// @ingroup API_PARAMETERS
/// \~chinese
/// \brief 获取参数存取的目标对象。
/// \param [in] hCamera 相机的句柄。
/// \param [out] piTarget 返回参数存取的对象。参考@link #emSdkParameterMode @endlink
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Gets the target object for the parameter access.
/// \param [in] hCamera Camera handle.
/// \param [out] piTarget Returns the object accessed by the parameter. Reference @link #emSdkParameterMode @endlink
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetParameterMode(
    CameraHandle    hCamera, 
    int*            piTarget
);

/// @ingroup API_PARAMETERS
/// \~chinese
/// \brief 设置参数存取的掩码。参数加载和保存时会根据该掩码来决定各个模块参数的是否加载或者保存。
/// \param [in] hCamera 相机的句柄。
/// \param [in] uMask     掩码。参考@link #emSdkPropSheetMask @endlink
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Sets the mask for parameter access. When the parameters are loaded and saved, the mask is used to determine whether each module parameter is loaded or saved.
/// \param [in] hCamera Camera handle.
/// \param [in] uMask mask. Reference @link #emSdkPropSheetMask @endlink
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetParameterMask(
    CameraHandle    hCamera, 
    UINT            uMask
);

/// @ingroup API_PARAMETERS
/// \~chinese
/// \brief 保存当前相机参数到指定的参数组中。相机提供了A,B,C,D四组空间来进行参数的保存。 
/// \param [in] hCamera 相机的句柄。
/// \param [in] iTeam   参数组，参考@link #emSdkParameterTeam @endlink
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Save current camera parameters to the specified parameter group. The camera provides A, B, C, D four sets of space for parameter preservation.
/// \param [in] hCamera Camera handle.
/// \param [in] iTeam parameter group, refer to @link #emSdkParameterTeam @endlink
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSaveParameter(
    CameraHandle    hCamera, 
    int             iTeam
);

/// @ingroup API_PARAMETERS
/// \~chinese
/// \brief 保存当前相机参数到指定的文件中。该文件可以复制到别的电脑上供其他相机加载，也可以做参数备份用。
/// \param [in] hCamera 相机的句柄。
/// \param [in] sFileName 参数文件的完整路径。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Saves the current camera parameters to the specified file. This file can be copied to another computer for loading by other cameras, or it can be used for parameter backup.
/// \param [in] hCamera Camera handle.
/// \param [in] sFileName Full path to the sFileName parameter file.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSaveParameterToFile(
  CameraHandle  hCamera, 
  char*       sFileName
);

/// @ingroup API_PARAMETERS
/// \~chinese
/// \brief 从PC上指定的参数文件中加载参数。我公司相机参数保存在PC上为.config后缀的文件，位于安装下的Camera\\Configs文件夹中。
/// \param [in] hCamera 相机的句柄。
/// \param [in] sFileName 参数文件的完整路径。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Load parameters from the parameter file specified on the PC. Our camera parameters are saved on the PC as a .config suffix file, which is located in the Camera\\Configs folder under installation.
/// \param [in] hCamera Camera handle.
/// \param [in] sFileName Full path to the sFileName parameter file.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraReadParameterFromFile(
    CameraHandle    hCamera,
    char*           sFileName
);

/// @ingroup API_PARAMETERS
/// \~chinese
/// \brief 加载指定组的参数到相机中。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iTeam   参数组，参考@link #emSdkParameterTeam @endlink
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Loads the parameters of the specified group into the camera.
/// \param [in] hCamera Camera handle.
/// \param [in] iTeam parameter group, refer to @link #emSdkParameterTeam @endlink
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraLoadParameter(
    CameraHandle    hCamera, 
    int             iTeam
);

/// @ingroup API_PARAMETERS
/// \~chinese
/// \brief 获得当前选择的参数组。
/// \param [in] hCamera 相机的句柄。
/// \param [in] piTeam  指针，返回当前选择的参数组。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the currently selected parameter group.
/// \param [in] hCamera Camera handle.
/// \param [in] piTeam Returns the currently selected parameter group.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetCurrentParameterGroup(
    CameraHandle    hCamera, 
    int*            piTeam
);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 设置相机传输图像数据的分包大小。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iPackSel 分包长度选择的索引号。分包长度可由获得相机属性结构体中@link #tSdkCameraCapbility.pPackLenDesc @endlink成员表述，@link #tSdkCameraCapbility.iPackLenDesc @endlink成员则表示最大可选的分包模式个数。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 目前的SDK版本中，该接口仅对GIGE接口相机有效，用来控制网络传输的分包大小。
/// \note 对于支持巨帧的网卡，我们建议选择8K的分包大小，可以有效的降低传输所占用的CPU处理时间。
/// \warning 新版本的SDK无需调用此函数，SDK会自动根据网络情况协商最优的分包大小
/// \~english
/// \brief Sets the packet size of the camera's transmitted image data.
/// \param [in] hCamera Camera handle.
/// \param [in] iPackSel Index number of the iPackSel packet length selection. The packet length can be expressed by the @link #tSdkCameraCapbility.pPackLenDesc @endlink member in the camera attribute structure. The @link #tSdkCameraCapbility.iPackLenDesc @endlink member represents the maximum number of optional packet modes.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note In the current SDK version, this interface is only valid for GIGE interface cameras and is used to control the packet size of the network transmission.
/// \note For NICs that support Jumbo Frames, we recommend choosing an 8K packet size that can effectively reduce the CPU processing time taken by the transfer.
/// \warning New version of the SDK does not need to call this function, the SDK will automatically negotiate the optimal packet size according to the network conditions
MVSDK_API CameraSdkStatus __stdcall CameraSetTransPackLen(
    CameraHandle    hCamera, 
    INT             iPackSel
);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 获得相机当前传输分包大小的选择索引号。
/// \param [in] hCamera 相机的句柄。
/// \param [out] piPackSel  指针，返回当前选择的分包大小索引号。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \see CameraSetTransPackLen
/// \~english
/// \brief Gets the selected index number of the camera's current transmission packet size.
/// \param [in] hCamera Camera handle.
/// \param [out] piPackSel Returns the currently selected packet size index number.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \see CameraSetTransPackLen
MVSDK_API CameraSdkStatus __stdcall CameraGetTransPackLen(
    CameraHandle    hCamera, 
    INT*            piPackSel
);

/// @ingroup API_EXPOSURE
/// \~chinese
/// \brief 获得自动曝光参考窗口的显示状态。
/// \param [in] hCamera 相机的句柄。
/// \param [out] pbIsVisible  指针，返回TRUE，则表示当前窗口会被叠加在图像内容上。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Gets the display status of the auto exposure reference window.
/// \param [in] hCamera Camera handle.
/// \param [out] pbIsVisible returns TRUE, indicating that the current window will be overlaid on the image content.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraIsAeWinVisible(
    CameraHandle    hCamera,
    BOOL*           pbIsVisible
);

/// @ingroup API_EXPOSURE
/// \~chinese
/// \brief 设置自动曝光参考窗口的显示状态。
/// \param [in] hCamera 相机的句柄。
/// \param [in] bIsVisible  TRUE，设置为显示；FALSE，不显示。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 当设置窗口状态为显示，调用@link #CameraImageOverlay @endlink后，能够将窗口位置以矩形的方式叠加在图像上。
/// \~english
/// \brief Sets the display status of the auto exposure reference window.
/// \param [in] hCamera Camera handle.
/// \param [in] bIsVisible TRUE, set to show; FALSE, not show.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note When the window state is set to display, after calling @link #CameraImageOverlay @endlink, the window position can be superimposed on the image in a rectangular manner.
MVSDK_API CameraSdkStatus __stdcall CameraSetAeWinVisible(
    CameraHandle    hCamera,
    BOOL            bIsVisible
);

/// @ingroup API_EXPOSURE
/// \~chinese
/// \brief 获得自动曝光参考窗口的位置。
/// \param [in] hCamera 相机的句柄。
/// \param [out] piHOff     指针，返回窗口位置左上角横坐标值。
/// \param [out] piVOff     指针，返回窗口位置左上角纵坐标值。
/// \param [out] piWidth    指针，返回窗口的宽度。
/// \param [out] piHeight   指针，返回窗口的高度。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the position of the auto exposure reference window.
/// \param [in] hCamera Camera handle.
/// \param [out] piHOff Returns the abscissa of the upper-left corner of the window.
/// \param [out] piVOff Returns the ordinate value in the upper left corner of the window.
/// \param [out] piWidth Returns the width of the window.
/// \param [out] piHeight Returns the height of the window.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetAeWindow(
    CameraHandle    hCamera, 
    INT*            piHOff, 
    INT*            piVOff, 
    INT*            piWidth, 
    INT*            piHeight
);

/// @ingroup API_EXPOSURE
/// \~chinese
/// \brief 设置自动曝光的参考窗口。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iHOff    窗口左上角的横坐标
/// \param [in] iVOff      窗口左上角的纵坐标
/// \param [in] iWidth     窗口的宽度 
/// \param [in] iHeight    窗口的高度
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 如果iHOff、iVOff、iWidth、iHeight全部为0，则窗口设置为每个分辨率下的居中1/2大小。可以随着分辨率的变化而跟随变化。
/// \note 如果iHOff、iVOff、iWidth、iHeight所决定的窗口位置范围超出了当前分辨率范围内， 则自动使用居中1/2大小窗口。
/// \~english
/// \brief Set the reference window for auto exposure.
/// \param [in] hCamera Camera handle.
/// \param [in] iHOff The horizontal axis of the window in the upper left corner
/// \param [in] iVOff The ordinate of the top left corner of the window
/// \param [in] iWidth width of window
/// \param [in] iHeight Height of window
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note If iHOff, iVOff, iWidth, and iHeight are all 0, the window is set to the center 1/2 size for each resolution. It can follow changes as the resolution changes.
/// \note If the window position range determined by iHOff, iVOff, iWidth, and iHeight exceeds the current resolution range, the centered 1/2 size window is automatically used.
MVSDK_API CameraSdkStatus __stdcall CameraSetAeWindow(
    CameraHandle    hCamera, 
    int             iHOff, 
    int             iVOff, 
    int             iWidth, 
    int             iHeight
);

/// @ingroup API_MIRROR
/// \~chinese
/// \brief 设置图像镜像操作。镜像操作分为水平和垂直两个方向。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iDir     表示镜像的方向。0，表示水平方向；1，表示垂直方向。
/// \param [in] bEnable  TRUE，使能镜像;FALSE，禁止镜像
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set image mirroring operation. The mirroring operation is divided into horizontal and vertical directions.
/// \param [in] hCamera Camera handle.
/// \param [in] iDir Indicates the direction of the mirror. 0 means horizontal direction; 1 means vertical direction.
/// \param [in] bEnable TRUE to enable mirroring; FALSE to disable mirroring
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetMirror(
    CameraHandle    hCamera, 
    int             iDir, 
    BOOL            bEnable
);

/// @ingroup API_MIRROR
/// \~chinese
/// \brief 获得图像的镜像状态。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iDir     表示要获得的镜像方向。0，表示水平方向；1，表示垂直方向。
/// \param [out] pbEnable   指针，返回TRUE，则表示iDir所指的方向镜像被使能。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the mirrored state of the image.
/// \param [in] hCamera Camera handle.
/// \param [in] iDir Indicates the mirroring direction to be obtained. 0 means horizontal direction; 1 means vertical direction.
/// \param [out] pbEnable Returns TRUE, indicating that the direction mirror image of iDir is enabled.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetMirror(
    CameraHandle    hCamera, 
    int             iDir, 
    BOOL*           pbEnable
);

/// @ingroup API_MIRROR
/// \~chinese
/// \brief 设置图像旋转操作
/// \param [in] hCamera 相机的句柄。
/// \param [in] iRot    表示旋转的角度（逆时针方向）（0：不旋转 1:90度 2:180度 3:270度）
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set image rotation operation
/// \param [in] hCamera Camera handle.
/// \param [in] iRot rotation angle (counterclockwise) (0: no rotation 1:90 degrees 2:180 degrees 3:270 degrees)
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetRotate(
	CameraHandle    hCamera, 
	int             iRot 
	);

/// @ingroup API_MIRROR
/// \~chinese
/// \brief 获得图像的旋转状态。
/// \param [in] hCamera 相机的句柄。
/// \param [out] iRot     表示要获得的旋转方向。（逆时针方向）（0：不旋转 1:90度 2:180度 3:270度）
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the rotation state of the image.
/// \param [in] hCamera Camera handle.
/// \param [out] iRot Indicates the direction of rotation to get. (Counterclockwise) (0: Do not rotate 1:90 degree 2: 180 degree 3: 270 degree)
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetRotate(
	CameraHandle    hCamera, 
	int*            iRot 
	);

/// @ingroup API_COLOR
/// \~chinese
/// \brief 获得白平衡参考窗口的位置。
/// \param [in] hCamera 相机的句柄。
/// \param [out] PiHOff   指针，返回参考窗口的左上角横坐标 。
/// \param [out] PiVOff     指针，返回参考窗口的左上角纵坐标 。
/// \param [out] PiWidth    指针，返回参考窗口的宽度。
/// \param [out] PiHeight   指针，返回参考窗口的高度。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the position of the white balance reference window.
/// \param [in] hCamera Camera handle.
/// \param [out] PiHOff Returns the top-left abscissa of the reference window.
/// \param [out] PiVOff Returns the upper-left ordinate of the reference window.
/// \param [out] PiWidth Returns the width of the reference window.
/// \param [out] PiHeight Returns the height of the reference window.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetWbWindow(
    CameraHandle    hCamera, 
    INT*            PiHOff, 
    INT*            PiVOff, 
    INT*            PiWidth, 
    INT*            PiHeight
);

/// @ingroup API_COLOR
/// \~chinese
/// \brief 设置白平衡参考窗口的位置。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iHOff   参考窗口的左上角横坐标。
/// \param [in] iVOff     参考窗口的左上角纵坐标。
/// \param [in] iWidth    参考窗口的宽度。
/// \param [in] iHeight   参考窗口的高度。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Sets the position of the white balance reference window.
/// \param [in] hCamera Camera handle.
/// \param [in] iHOff The upper left corner of the reference window.
/// \param [in] iVOff The upper left ordinate of the reference window.
/// \param [in] iWidth Width of the reference window.
/// \param [in] iHeight The height of the reference window.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetWbWindow(
    CameraHandle    hCamera, 
    INT             iHOff, 
    INT             iVOff, 
    INT             iWidth, 
    INT             iHeight
);

/// @ingroup API_COLOR
/// \~chinese
/// \brief 获得白平衡窗口的显示状态。
/// \param [in] hCamera 相机的句柄。
/// \param [out] pbShow   指针，返回TRUE，则表示窗口是可见的。 
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the display status of the white balance window.
/// \param [in] hCamera Camera handle.
/// \param [out] pbShow returns TRUE, indicating that the window is visible.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraIsWbWinVisible(
    CameraHandle    hCamera,
    BOOL*           pbShow
);

/// @ingroup API_COLOR
/// \~chinese
/// \brief 设置白平衡窗口的显示状态。
/// \param [in] hCamera 相机的句柄。
/// \param [in] bShow      TRUE，则表示设置为可见。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 在调用@link #CameraImageOverlay @endlink后，图像内容上将以矩形的方式叠加白平衡参考窗口的位置。
/// \~english
/// \brief Sets the display status of the white balance window.
/// \param [in] hCamera Camera handle.
/// \param [in] bShow TRUE indicates that the setting is visible.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note After calling @link #CameraImageOverlay @endlink, the white balance reference window's position will be overlaid on the image content in a rectangular manner.
MVSDK_API CameraSdkStatus __stdcall CameraSetWbWinVisible(
    CameraHandle    hCamera, 
    BOOL            bShow
);

/// @ingroup API_ISP
/// \~chinese
/// \brief 将输入的图像数据上叠加十字线、白平衡参考窗口、自动曝光参考窗口等图形。只有设置为可见状态的十字线和参考窗口才能被叠加上。
/// \param [in] hCamera 相机的句柄。
/// \param [in] pRgbBuffer 图像数据缓冲区。
/// \param [in] pFrInfo    图像的帧头信息。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief The cross-line, white balance reference window, auto exposure reference window, etc. are superimposed on the input image data. Only crosshairs and reference windows that are set to visible can be overlaid.
/// \param [in] hCamera Camera handle.
/// \param [in] pRgbBuffer image data buffer.
/// \param [in] pFrInfo Frame header information for the image.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraImageOverlay(
    CameraHandle    hCamera,
    BYTE*           pRgbBuffer,
    tSdkFrameHead*  pFrInfo
);

/// @ingroup API_UTIL
/// \~chinese
/// \brief 设置指定十字线的参数。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iLine    表示要设置第几条十字线的状态。范围为[0,8]，共9条。    
/// \param [in] x          十字线中心位置的横坐标值。
/// \param [in] y      十字线中心位置的纵坐标值。
/// \param [in] uColor     十字线的颜色，格式为(R|(G<<8)|(B<<16))
/// \param [in] bVisible   十字线的显示状态。TRUE，表示显示。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 只有设置为显示状态的十字线，在调用@link #CameraImageOverlay @endlink后才会被叠加到图像上。
/// \~english
/// \brief Set the parameters for the specified crosshairs.
/// \param [in] hCamera Camera handle.
/// \param [in] iLine Indicates the status of the first few crosshairs. The range is [0,8] for a total of 9.
/// \param [in] x The abscissa of the crosshair center position.
/// \param [in] y The y-axis value of the crosshair center position.
/// \param [in] uColor The color of the crosshair in the format (R|(G<<8)|(B<<16))
/// \param [in] bVisible Crosshair display status. TRUE, indicates the display.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note Only crosshairs set to display state will be superimposed on the image after calling @link #CameraImageOverlay @endlink.
MVSDK_API CameraSdkStatus __stdcall CameraSetCrossLine(
    CameraHandle    hCamera, 
    int             iLine, 
    INT             x,
    INT             y,
    UINT            uColor,
    BOOL            bVisible
);

/// @ingroup API_UTIL
/// \~chinese
/// \brief 获得指定十字线的状态。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iLine    表示要获取的第几条十字线的状态。范围为[0,8]，共9条。  
/// \param [out] px     指针，返回该十字线中心位置的横坐标。
/// \param [out] py     指针，返回该十字线中心位置的横坐标。
/// \param [out] pcolor     指针，返回该十字线的颜色，格式为(R|(G<<8)|(B<<16))。
/// \param [out] pbVisible  指针，返回TRUE，则表示该十字线可见。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the status of the designated crosshairs.
/// \param [in] hCamera Camera handle.
/// \param [in] iLine Indicates the status of the first few crosshairs to get. The range is [0,8] for a total of 9.
/// \param [out] px Returns the abscissa of the center of the crosshair.
/// \param [out] py Returns the abscissa of the center of the crosshair.
/// \param [out] pcolor Returns the color of this crosshair in the format (R|(G<<8)|(B<<16)).
/// \param [out] pbVisible returns TRUE, indicating that the crosshairs are visible.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetCrossLine(
    CameraHandle    hCamera, 
    INT             iLine,
    INT*            px,
    INT*            py,
    UINT*           pcolor,
    BOOL*           pbVisible
);

/// @ingroup API_BASIC
/// \~chinese
/// \brief 获得相机的特性描述结构体。该结构体中包含了相机可设置的各种参数的范围信息。决定了相关函数的参数返回，也可用于动态创建相机的配置界面。
/// \param [in] hCamera 相机的句柄。
/// \param [out] pCameraInfo 指针，返回该相机特性描述的结构体。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the camera's characteristic description structure. This structure contains range information of various parameters that the camera can set. Determines the return of parameters for related functions and can also be used to dynamically create camera configuration interfaces.
/// \param [in] hCamera Camera handle.
/// \param [out] pCameraInfo Returns the structure of the camera's property description.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetCapability(
    CameraHandle            hCamera, 
    tSdkCameraCapbility*    pCameraInfo
);

/******************************************************/
// 函数名   : CameraGetCapabilityEx
// 功能描述 : 获得相机的特性描述结构体。该结构体中包含了相机
//        可设置的各种参数的范围信息。决定了相关函数的参数
//        返回，也可用于动态创建相机的配置界面。
// 参数     : sDeviceModel    相机的型号，由扫描列表中获取
//            pCameraInfo 指针，返回该相机特性描述的结构体。
//                        tSdkCameraCapbility在CameraDefine.h中定义。
// 返回值   : 成功时，返回CAMERA_STATUS_SUCCESS (0);
//            否则返回非0值的错误码,请参考CameraStatus.h
//            中错误码的定义。
/******************************************************/
MVSDK_API CameraSdkStatus __stdcall CameraGetCapabilityEx(
    char*                   sDeviceModel, 
    tSdkCameraCapbility*    pCameraInfo,
    PVOID                   hCameraHandle
);

/// @ingroup API_USERDATA
/// \~chinese
/// \brief 设置相机的序列号。
/// \param [in] hCamera 相机的句柄。
/// \param [in] pbySN    序列号的缓冲区。 
/// \param [in] iLevel   要设定的序列号级别，只能是1或者2。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 我公司相机序列号分为3级。0级的是我公司自定义的相机序列号，出厂时已经设定好且无法修改，1级和2级留给二次开发使用。每级序列号长度都是32个字节。
/// \~english
/// \brief Set the camera's serial number.
/// \param [in] hCamera Camera handle.
/// \param [in] pbySN The buffer for the serial number.
/// \param [in] iLevel The serial number to be set can only be 1 or 2.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note Our company camera serial number is divided into 3 levels. Level 0 is our company's custom camera serial number, which has been set at the factory and cannot be modified. Levels 1 and 2 are reserved for secondary development. Each serial number length is 32 bytes.
MVSDK_API CameraSdkStatus __stdcall CameraWriteSN(
    CameraHandle    hCamera, 
    BYTE*           pbySN, 
    INT             iLevel
);

/// @ingroup API_USERDATA
/// \~chinese
/// \brief 读取相机指定级别的序列号。
/// \param [in] hCamera 相机的句柄。
/// \param [in] pbySN   序列号的缓冲区。
/// \param [in] iLevel  要读取的序列号级别。可以为0、1和2。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \see CameraWriteSN
/// \~english
/// \brief Reads the camera's assigned level serial number.
/// \param [in] hCamera Camera handle.
/// \param [in] pbySN The buffer for the serial number.
/// \param [in] iLevel The sequence number to read. Can be 0, 1 and 2.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \see CameraWriteSN
MVSDK_API CameraSdkStatus __stdcall CameraReadSN(
    CameraHandle        hCamera, 
    BYTE*               pbySN, 
    INT                 iLevel
);

/// @ingroup API_TRIGGER
/// \~chinese
/// \brief 设置硬件触发模式下的触发延时时间，单位微秒。
/// \param [in] hCamera 相机的句柄。
/// \param [in] uDelayTimeUs 硬触发延时。单位微秒。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 当硬触发信号来临后，经过指定的延时，再开始采集图像。
/// \~english
/// \brief Set the trigger delay time in hardware trigger mode, in microseconds.
/// \param [in] hCamera Camera handle.
/// \param [in] uDelayTimeUs Hard trigger delay. Units microseconds.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note When the hard trigger signal arrives, after a specified delay, it begins to capture the image.
MVSDK_API CameraSdkStatus __stdcall CameraSetTriggerDelayTime(
    CameraHandle    hCamera, 
    UINT            uDelayTimeUs
);

/// @ingroup API_TRIGGER
/// \~chinese
/// \brief 获得当前设定的硬触发延时时间。
/// \param [in] hCamera 相机的句柄。
/// \param [out] puDelayTimeUs 指针，返回延时时间，单位微秒。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the currently set hard trigger delay time.
/// \param [in] hCamera Camera handle.
/// \param [out] puDelayTimeUs Returns the delay time in microseconds.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetTriggerDelayTime(
    CameraHandle    hCamera, 
    UINT*           puDelayTimeUs
);

/// @ingroup API_TRIGGER
/// \~chinese
/// \brief 设置触发模式下的触发帧数。对软件触发和硬件触发模式都有效。默认为1帧，即一次触发信号采集一帧图像。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iCount    一次触发采集的帧数。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Sets the number of trigger frames in the trigger mode. Valid for both software and hardware trigger modes. The default is 1 frame, that is, one trigger signal captures a frame of image.
/// \param [in] hCamera Camera handle.
/// \param [in] iCount The number of frames triggered at a time.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetTriggerCount(
    CameraHandle    hCamera, 
    INT             iCount
);

/// @ingroup API_TRIGGER
/// \~chinese
/// \brief 获得一次触发的帧数。
/// \param [in] hCamera 相机的句柄。
/// \param [out] piCount 一次触发信号采集的帧数。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the number of trigger frames.
/// \param [in] hCamera Camera handle.
/// \param [out] piCount The number of frames to trigger signal acquisition at one time.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetTriggerCount(
    CameraHandle    hCamera, 
    INT*            piCount
);

/// @ingroup API_TRIGGER
/// \~chinese
/// \brief 执行一次软触发。执行后，会触发由@link #CameraSetTriggerCount @endlink指定的帧数。
/// \param [in] hCamera 相机的句柄。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \see CameraSetTriggerMode
/// \~english
/// \brief Perform a soft trigger. After execution, the number of frames specified by @link #CameraSetTriggerCount @endlink is triggered.
/// \param [in] hCamera Camera handle.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \see CameraSetTriggerMode
MVSDK_API CameraSdkStatus __stdcall CameraSoftTrigger(
    CameraHandle    hCamera
);

/// @ingroup API_TRIGGER
/// \~chinese
/// \brief 设置相机的触发模式。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iModeSel   模式选择索引号。0表示连续采集模式；1表示软件触发模式；2表示硬件触发模式。  
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set the camera's trigger mode.
/// \param [in] hCamera Camera handle.
/// \param [in] iModeSel mode selects the index number. 0 means continuous acquisition mode; 1 means software trigger mode; 2 means hardware trigger mode.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetTriggerMode(
    CameraHandle    hCamera, 
    int             iModeSel
);

/// @ingroup API_TRIGGER
/// \~chinese
/// \brief 获得相机的触发模式。
/// \param [in] hCamera 相机的句柄。
/// \param [out] piModeSel  指针，返回当前选择的相机触发模式的索引号。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the camera's trigger mode.
/// \param [in] hCamera Camera handle.
/// \param [out] piModeSel Returns the index of the currently selected camera trigger mode.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetTriggerMode(
    CameraHandle    hCamera,
    INT*            piModeSel
);

/// @ingroup API_TRIGGER
/// \~chinese
/// \brief 设置IO引脚端子上的STROBE信号。该信号可以做闪光灯控制，也可以做外部机械快门控制。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iMode 闪光灯模式，参考@link #emStrobeControl @endlink
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set the STROBE signal on the IO pin terminal. This signal can be used for flash control or external mechanical shutter control.
/// \param [in] hCamera Camera handle.
/// \param [in] iMode strobe mode, refer to @link #emStrobeControl @endlink
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall  CameraSetStrobeMode(
    CameraHandle    hCamera, 
    INT             iMode
);

/// @ingroup API_TRIGGER
/// \~chinese
/// \brief 获取当前STROBE信号设置的模式。
/// \param [in] hCamera 相机的句柄。
/// \param [out] piMode 返回模式
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Gets the mode of the current STROBE signal setting.
/// \param [in] hCamera Camera handle.
/// \param [out] piMode Return Mode
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall  CameraGetStrobeMode(
    CameraHandle    hCamera, 
    INT*            piMode
);

/// @ingroup API_TRIGGER
/// \~chinese
/// \brief 当STROBE信号处于STROBE_SYNC_WITH_TRIG时，通过该函数设置其相对触发信号延时时间。
/// \param [in] hCamera 相机的句柄。
/// \param [in] uDelayTimeUs  相对触发信号的延时时间，单位为us。可以为0，但不能为负数。 
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief When the STROBE signal is in STROBE_SYNC_WITH_TRIG, set its relative trigger signal delay time by this function.
/// \param [in] hCamera Camera handle.
/// \param [in] uDelayTimeUs Delay time relative to the trigger signal, in units of us. Can be 0, but it cannot be negative.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall  CameraSetStrobeDelayTime(
    CameraHandle    hCamera, 
    UINT            uDelayTimeUs
);

/// @ingroup API_TRIGGER
/// \~chinese
/// \brief 当STROBE信号处于STROBE_SYNC_WITH_TRIG时，通过该函数获得其相对触发信号延时时间。
/// \param [in] hCamera 相机的句柄。
/// \param [out] upDelayTimeUs     指针，返回延时时间，单位us。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief When the STROBE signal is in STROBE_SYNC_WITH_TRIG, the relative trigger signal delay time is obtained through this function.
/// \param [in] hCamera Camera handle.
/// \param [out] upDelayTimeUs Returns the delay time in us.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall  CameraGetStrobeDelayTime(
    CameraHandle    hCamera, 
    UINT*           upDelayTimeUs
);

/// @ingroup API_TRIGGER
/// \~chinese
/// \brief 当STROBE信号处于STROBE_SYNC_WITH_TRIG时，通过该函数设置其脉冲宽度。
/// \param [in] hCamera 相机的句柄。
/// \param [in] uTimeUs 脉冲的宽度，单位为时间us。  
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief When the STROBE signal is in STROBE_SYNC_WITH_TRIG, set its pulse width by this function.
/// \param [in] hCamera Camera handle.
/// \param [in] uTimeUs The width of the pulse in units of time us.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall  CameraSetStrobePulseWidth(
    CameraHandle    hCamera, 
    UINT            uTimeUs
);

/// @ingroup API_TRIGGER
/// \~chinese
/// \brief 当STROBE信号处于STROBE_SYNC_WITH_TRIG时，通过该函数获得其脉冲宽度。
/// \param [in] hCamera 相机的句柄。
/// \param [out] upTimeUs  指针，返回脉冲宽度。单位为us。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief When the STROBE signal is at STROBE_SYNC_WITH_TRIG, its pulse width is obtained by this function.
/// \param [in] hCamera Camera handle.
/// \param [out] upTimeUs Returns the pulse width. The unit is us.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall  CameraGetStrobePulseWidth(
    CameraHandle    hCamera, 
    UINT*           upTimeUs
);

/// @ingroup API_TRIGGER
/// \~chinese
/// \brief 当STROBE信号处于STROBE_SYNC_WITH_TRIG时，通过该函数设置其有效电平的极性。默认为高有效，当触发信号到来时，STROBE信号被拉高。
/// \param [in] hCamera 相机的句柄。
/// \param [in] uPolarity STROBE信号的极性，0为低电平有效，1为高电平有效。默认为高电平有效。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief When the STROBE signal is at STROBE_SYNC_WITH_TRIG, the polarity of its active level is set by this function. The default is high active. When the trigger signal arrives, the STROBE signal is pulled high.
/// \param [in] hCamera Camera handle.
/// \param [in] uPolarity Polarity of STROBE signal, 0 is active low and 1 is active high. The default is active high.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall  CameraSetStrobePolarity(
    CameraHandle    hCamera, 
    INT             uPolarity
);

/// @ingroup API_TRIGGER
/// \~chinese
/// \brief 获得相机当前STROBE信号的有效极性。默认为高电平有效。
/// \param [in] hCamera 相机的句柄。
/// \param [in] upPolarity    指针，返回STROBE信号当前的有效极性。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Obtain the effective polarity of the camera's current STROBE signal. The default is active high.
/// \param [in] hCamera Camera handle.
/// \param [in] upPolarity Returns the current effective polarity of the STROBE signal.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall  CameraGetStrobePolarity(
    CameraHandle    hCamera, 
    INT*            upPolarity
);

/// @ingroup API_TRIGGER
/// \~chinese
/// \brief 设置相机外触发信号的种类。上边沿、下边沿、或者高、低电平方式。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iType   外触发信号种类，参考@link #emExtTrigSignal @endlink
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set the type of trigger signal outside the camera. Upper edge, lower edge, or high and low level.
/// \param [in] hCamera Camera handle.
/// \param [in] iType External trigger signal type, refer to @link #emExtTrigSignal @endlink
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall  CameraSetExtTrigSignalType(
    CameraHandle    hCamera, 
    INT             iType
);

/// @ingroup API_TRIGGER
/// \~chinese
/// \brief 获得相机当前外触发信号的种类。
/// \param [in] hCamera 相机的句柄。
/// \param [out] ipType 指针，返回外触发信号种类，参考@link #emExtTrigSignal @endlink
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the type of camera's current external trigger signal.
/// \param [in] hCamera Camera handle.
/// \param [out] ipType Returns the type of external trigger signal, see @link #emExtTrigSignal @endlink
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall  CameraGetExtTrigSignalType(
    CameraHandle    hCamera, 
    INT*            ipType
);

/// @ingroup API_TRIGGER
/// \~chinese
/// \brief 设置外触发模式下，相机快门的方式，默认为标准快门方式。部分滚动快门的CMOS相机支持GRR方式。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iType   外触发快门方式。参考@link #emExtTrigShutterMode @endlink
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief In the external trigger mode, the camera shutter mode defaults to the standard shutter mode. Part of the rolling shutter CMOS camera supports GRR mode.
/// \param [in] hCamera Camera handle.
/// \param [in] iType triggers the shutter. Reference @link #emExtTrigShutterMode @endlink
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall  CameraSetExtTrigShutterType(
    CameraHandle    hCamera, 
    INT             iType
);

/// @ingroup API_TRIGGER
/// \~chinese
/// \brief 获得外触发模式下，相机快门的方式
/// \param [in] hCamera 相机的句柄。
/// \param [out] ipType    指针，返回当前设定的外触发快门方式。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \see CameraSetExtTrigShutterType
/// \~english
/// \brief Get the camera shutter mode in external trigger mode
/// \param [in] hCamera Camera handle.
/// \param [out] ipType Returns the currently set external trigger shutter mode.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \see CameraSetExtTrigShutterType
MVSDK_API CameraSdkStatus __stdcall  CameraGetExtTrigShutterType(
    CameraHandle    hCamera, 
    INT*            ipType
);

/// @ingroup API_TRIGGER
/// \~chinese
/// \brief 设置外触发信号延时时间，默认为0，单位为微秒。 
/// \param [in] hCamera 相机的句柄。
/// \param [in] uDelayTimeUs  延时时间，单位为微秒，默认为0.
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set the delay time of external trigger signal. The default is 0 and the unit is microsecond.
/// \param [in] hCamera Camera handle.
/// \param [in] uDelayTimeUs Delay time in microseconds. Default is 0.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall  CameraSetExtTrigDelayTime(
    CameraHandle    hCamera, 
    UINT            uDelayTimeUs
);

/// @ingroup API_TRIGGER
/// \~chinese
/// \brief 获得设置的外触发信号延时时间，默认为0，单位为微秒。
/// \param [in] hCamera 相机的句柄。
/// \param [out] upDelayTimeUs 触发延时
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the set external trigger signal delay time, the default is 0, the unit is microseconds.
/// \param [in] hCamera Camera handle.
/// \param [out] upDelayTimeUs trigger delay
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall  CameraGetExtTrigDelayTime(
    CameraHandle    hCamera, 
    UINT*           upDelayTimeUs
);

/// @ingroup API_TRIGGER
/// \~chinese
/// \brief 设置相机外触发信号的消抖时间，只有当外触发信号模式选择高电平或者低电平触发时，去抖时间才会生效。默认为0，单位为微秒。
/// \param [in] hCamera 相机的句柄。
/// \param [in] uTimeUs 时间
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Sets the debouncing time of the trigger signal outside the camera. The debounce time will only take effect when the external trigger signal mode selects high or low trigger. The default is 0 and the unit is microseconds.
/// \param [in] hCamera Camera handle.
/// \param [in] uTimeUs time
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall  CameraSetExtTrigJitterTime(
    CameraHandle    hCamera,
    UINT            uTimeUs
);

/// @ingroup API_TRIGGER
/// \~chinese
/// \brief 获得设置的相机外触发消抖时间，默认为0.单位为微秒。
/// \param [in] hCamera 相机的句柄。
/// \param [out] upTimeUs 时间
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the set camera trigger debounce time, the default is 0. The unit is microseconds.
/// \param [in] hCamera Camera handle.
/// \param [out] upTimeUs time
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall  CameraGetExtTrigJitterTime(
    CameraHandle    hCamera,
    UINT*           upTimeUs
);

/// @ingroup API_TRIGGER
/// \~chinese
/// \brief 获得相机外触发的属性掩码
/// \param [in] hCamera 相机的句柄。
/// \param [out] puCapabilityMask  指针，返回该相机外触发特性掩码，掩码参考CameraDefine.h中EXT_TRIG_MASK_ 开头的宏定义。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the triggering attribute mask outside the camera
/// \param [in] hCamera Camera handle.
/// \param [out] puCapabilityMask Returns the mask of the camera's triggering property, masked by the macro definition at the beginning of EXT_TRIG_MASK_ in CameraDefine.h.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall  CameraGetExtTrigCapability(
    CameraHandle    hCamera,
    UINT*           puCapabilityMask
);

/// @ingroup API_TRIGGER
/// \~chinese
/// \brief 当外触发信号为电平模式时，暂时停止触发相机，直到电平信号跳变后继续触发。
/// \param [in] hCamera 相机的句柄。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief When the external trigger signal is in level mode, it temporarily stops triggering the camera until the level signal jumps and continues to trigger.
/// \param [in] hCamera Camera handle.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall  CameraPauseLevelTrigger(
	CameraHandle    hCamera
	);

/// @ingroup API_ROI
/// \~chinese
/// \brief 获得抓拍模式下的分辨率选择索引号。
/// \param [in] hCamera 相机的句柄。
/// \param [out] pImageResolution 指针，返回抓拍模式的分辨率。 
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the resolution selection index number in snap mode.
/// \param [in] hCamera Camera handle.
/// \param [out] pImageResolution Pointer to return the resolution of the snap mode.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetResolutionForSnap(
    CameraHandle            hCamera,
    tSdkImageResolution*    pImageResolution
);

/// @ingroup API_ROI
/// \~chinese
/// \brief 设置抓拍模式下相机输出图像的分辨率。
/// \param [in] hCamera 相机的句柄。
/// \param [in] pImageResolution 分辨率
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 如果pImageResolution->iWidth = pImageResolution->iHeight = 0，则表示设定为跟随当前预览分辨率。抓拍到的图像的分辨率会和当前设定的预览分辨率一样。
/// \~english
/// \brief Sets the resolution of the camera's output image in snap shot mode.
/// \param [in] hCamera Camera handle.
/// \param [in] pImageResolution Resolution
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note If pImageResolution->iWidth = pImageResolution->iHeight = 0, then it is set to follow the current preview resolution. The resolution of the captured image will be the same as the currently set preview resolution.
MVSDK_API CameraSdkStatus __stdcall CameraSetResolutionForSnap(
    CameraHandle            hCamera, 
    tSdkImageResolution*    pImageResolution
);

/// @ingroup API_ROI
/// \~chinese
/// \brief 打开分辨率自定义面板，并通过可视化的方式来配置一个自定义分辨率。
/// \param [in] hCamera 相机的句柄。
/// \param [out] pImageCustom 指针，返回自定义的分辨率。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Open the resolution custom panel and configure a custom resolution visually.
/// \param [in] hCamera Camera handle.
/// \param [out] pImageCustom Returns the custom resolution.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraCustomizeResolution(
    CameraHandle            hCamera,
    tSdkImageResolution*    pImageCustom
);

/// @ingroup API_UTIL
/// \~chinese
/// \brief 打开参考窗口自定义面板。并通过可视化的方式来获得一个自定义窗口的位置。一般是用自定义白平衡和自动曝光的参考窗口。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iWinType   要生成的参考窗口的用途。0:自动曝光参考窗口；1:白平衡参考窗口。
/// \param [in] hParent    调用该函数的窗口的句柄。可以为NULL。
/// \param [out] piHOff     指针，返回自定义窗口的左上角横坐标。
/// \param [out] piVOff     指针，返回自定义窗口的左上角纵坐标。
/// \param [out] piWidth    指针，返回自定义窗口的宽度。 
/// \param [out] piHeight   指针，返回自定义窗口的高度。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Open the reference window custom panel. And through a visual way to get a custom window location. It is generally a reference window with custom white balance and auto exposure.
/// \param [in] hCamera Camera handle.
/// \param [in] iWinType Purpose of the reference window to be generated. 0: Auto exposure reference window; 1: White balance reference window.
/// \param [in] hParent The handle of the window that called the function. Can be NULL.
/// \param [out] piHOff Returns the upper left-hand abscissa of the custom window.
/// \param [out] piVOff Returns the upper left ordinate of the custom window.
/// \param [out] piWidth Returns the width of the custom window.
/// \param [out] piHeight Returns the height of the custom window.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraCustomizeReferWin(
    CameraHandle    hCamera,
    INT             iWinType,
    HWND            hParent, 
    INT*            piHOff,
    INT*            piVOff,
    INT*            piWidth,
    INT*            piHeight
);

/// @ingroup API_SETTINGS_PAGE
/// \~chinese
/// \brief 设置相机属性配置窗口显示状态。
/// \param [in] hCamera 相机的句柄。
/// \param [in] bShow    TRUE，显示;FALSE，隐藏。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 必须先调用@link #CameraCreateSettingPage @endlink成功创建相机属性配置窗口后，才能调用本函数进行显示。
/// \~english
/// \brief Set the camera property configuration window display status.
/// \param [in] hCamera Camera handle.
/// \param [in] bShow TRUE, show; FALSE, hide.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note You must call @link #CameraCreateSettingPage @endlink successfully to create the camera property configuration window before calling this function to display.
MVSDK_API CameraSdkStatus __stdcall CameraShowSettingPage(
    CameraHandle    hCamera,
    BOOL            bShow
);

/// @ingroup API_SETTINGS_PAGE
/// \~chinese
/// \brief 创建该相机的属性配置窗口。调用该函数，SDK内部会帮您创建好相机的配置窗口，省去了您重新开发相机配置界面的时间。强烈建议使用您使用该函数让SDK为您创建好配置窗口。
/// \param [in] hCamera 相机的句柄。
/// \param [in] hParent       应用程序主窗口的句柄。可以为NULL。
/// \param [in] pWinText      字符串指针，窗口显示的标题栏。
/// \param [in] pCallbackFunc 窗口消息的回调函数，当相应的事件发生时，pCallbackFunc所指向的函数会被调用
/// \param [in] pCallbackCtx  回调函数的附加参数。可以为NULL。
/// \param [in] uReserved     预留。必须设置为0。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Create the camera's property configuration window. Call this function, the SDK will help you create a camera configuration window, eliminating the need to redevelop the camera configuration interface. It is strongly recommended that you use this function to have the SDK create a configuration window for you.
/// \param [in] hCamera Camera handle.
/// \param [in] hParent Handle to the main window of the application. Can be NULL.
/// \param [in] pWinText string pointer, window title bar.
/// \param [in] pCallbackFunc Callback function of window message. The function pointed to by pCallbackFunc will be called when the corresponding event occurs.
/// \param [in] pCallbackCtx Additional parameters for the callback function. Can be NULL.
/// \param [in] uReserved Reserved. Must be set to 0.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraCreateSettingPage(
    CameraHandle            hCamera,
    HWND                    hParent,
    char*                   pWinText,
    CAMERA_PAGE_MSG_PROC    pCallbackFunc,
    PVOID                   pCallbackCtx,
    UINT                    uReserved
);

/// @ingroup API_SETTINGS_PAGE
/// \~chinese
/// \brief 使用默认参数创建该相机的属性配置窗口。
/// \param [in] hCamera 相机的句柄。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Use the default parameters to create the camera's property configuration window.
/// \param [in] hCamera Camera handle.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraCreateSettingPageEx(
    CameraHandle            hCamera
);

/// @ingroup API_SETTINGS_PAGE
/// \~chinese
/// \brief 设置相机配置窗口的激活页面。相机配置窗口有多个子页面构成，该函数可以设定当前哪一个子页面为激活状态，显示在最前端。
/// \param [in] hCamera 相机的句柄。
/// \param [in] index   子页面的索引号。参考@link #emSdkPropSheetMask @endlink
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Sets the camera configuration window's activation page. The camera configuration window is composed of multiple sub-pages. This function can set which sub-page is currently active and displayed at the forefront.
/// \param [in] hCamera Camera handle.
/// \param [in] index The index number of the subpage. Reference @link #emSdkPropSheetMask @endlink
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetActiveSettingSubPage(
    CameraHandle    hCamera,
    INT             index
);

/// @ingroup API_SETTINGS_PAGE
/// \~chinese
/// \brief 把相机配置页设置为子窗口风格，并且指定它的父窗口。
/// \param [in] hCamera 相机的句柄。
/// \param [in] hParentWnd 父窗口句柄，为NULL(0)则恢复配置页为弹出窗口。
/// \param [in] Flags 功能标志位，bit0: 隐藏标题栏，bit1-31: 保留(必须为0)
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Sets the camera configuration page to child window style and specifies its parent window.
/// \param [in] hCamera Camera handle.
/// \param [in] hParentWnd The parent window handle, NULL (0) restores the configuration page to a popup window.
/// \param [in] Flags function flag, bit0: Hide title bar, bit1-31: Reserved (must be 0)
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetSettingPageParent(
	CameraHandle    hCamera,
	HWND            hParentWnd,
	DWORD			Flags
	);

/// @ingroup API_SETTINGS_PAGE
/// \~chinese
/// \brief 获取相机配置页的窗口句柄。
/// \param [in] hCamera 相机的句柄。
/// \param [out] hWnd 返回配置页的窗口句柄。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Gets the window handle of the camera configuration page.
/// \param [in] hCamera Camera handle.
/// \param [out] hWnd Returns the window handle of the configuration page.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetSettingPageHWnd(
	CameraHandle    hCamera,
	HWND*           hWnd
	);

MVSDK_API CameraSdkStatus __stdcall CameraSpecialControl(
    CameraHandle    hCamera, 
    DWORD           dwCtrlCode,
    DWORD           dwParam,
    LPVOID          lpData
);

/// @ingroup API_BASIC
/// \~chinese
/// \brief 获得相机接收帧率的统计信息，包括错误帧和丢帧的情况。
/// \param [in] hCamera 相机的句柄。
/// \param [out] psFrameStatistic 指针，返回统计信息。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the frame rate statistics of the camera, including error frame and frame loss.
/// \param [in] hCamera Camera handle.
/// \param [out] psFrameStatistic Returns statistics.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetFrameStatistic(
    CameraHandle            hCamera, 
    tSdkFrameStatistic*     psFrameStatistic
);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 设置图像降噪模块的使能状态。
/// \param [in] hCamera 相机的句柄。
/// \param [in] bEnable   TRUE，使能；FALSE，禁止。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set the enable status of the image noise reduction module.
/// \param [in] hCamera Camera handle.
/// \param [in] bEnable TRUE, enable; FALSE, disable.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetNoiseFilter(
    CameraHandle    hCamera,
    BOOL            bEnable
);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 获得图像降噪模块的使能状态。
/// \param [in] hCamera 相机的句柄。
/// \param [out] pEnable   指针，返回状态。TRUE，为使能。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the image noise reduction module's enable state.
/// \param [in] hCamera Camera handle.
/// \param [out] pEnable Returns status. TRUE, to enable.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetNoiseFilterState(
    CameraHandle    hCamera,
    BOOL*           pEnable
);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 复位图像采集的时间戳，从0开始。
/// \param [in] hCamera 相机的句柄。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Resets the time stamp of the image acquisition, starting from 0.
/// \param [in] hCamera Camera handle.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraRstTimeStamp(
    CameraHandle    hCamera
);

/// @ingroup API_USERDATA
/// \~chinese
/// \brief 将用户自定义的数据保存到相机的非易性存储器中。
/// \param [in] hCamera 相机的句柄。
/// \param [in] uStartAddr  起始地址，从0开始。
/// \param [in] pbData      数据缓冲区指针
/// \param [in] ilen        写入数据的长度，ilen + uStartAddr必须小于用户区最大长度
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 每个型号的相机可能支持的用户数据区最大长度不一样。可以从设备的特性描述中获取该长度信息。
/// \~english
/// \brief Save user-defined data to the camera's non-volatile memory.
/// \param [in] hCamera Camera handle.
/// \param [in] uStartAddr Start address, starting from 0.
/// \param [in] pbData data buffer pointer
/// \param [in] ilen The length of the write data, ilen + uStartAddr must be less than the maximum length of the user area
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note The maximum length of the user data area that each model of camera may support is different. This length information can be obtained from the device's feature description.
MVSDK_API CameraSdkStatus __stdcall CameraSaveUserData(
    CameraHandle    hCamera,
    UINT            uStartAddr,
    BYTE            *pbData,
    int             ilen
);

/// @ingroup API_USERDATA
/// \~chinese
/// \brief 从相机的非易性存储器中读取用户自定义的数据。
/// \param [in] hCamera 相机的句柄。
/// \param [in] uStartAddr  起始地址，从0开始。
/// \param [out] pbData     数据缓冲区指针
/// \param [in] ilen        数据的长度，ilen + uStartAddr必须小于用户区最大长度
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Read user-defined data from the camera's non-volatile memory.
/// \param [in] hCamera Camera handle.
/// \param [in] uStartAddr Start address, starting from 0.
/// \param [out] pbData data buffer pointer
/// \param [in] ilen The length of the data, ilen + uStartAddr must be less than the maximum length of the user area
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraLoadUserData(
    CameraHandle    hCamera,
    UINT            uStartAddr,
    BYTE            *pbData,
    int             ilen
);

/// @ingroup API_USERDATA
/// \~chinese
/// \brief 读取用户自定义的设备昵称。
/// \param [in] hCamera 相机的句柄。
/// \param [out] pName  指针，返回指向0结尾的字符串，设备昵称不超过32个字节，因此该指针指向的缓冲区必须大于等于32个字节空间。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Read user-defined device nicknames.
/// \param [in] hCamera Camera handle.
/// \param [out] pName returns a string that points to the end of 0, the device nickname does not exceed 32 bytes, so the buffer pointed to by this pointer must be greater than or equal to 32 bytes.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetFriendlyName(
  CameraHandle  hCamera,
  char*     pName
);

/// @ingroup API_USERDATA
/// \~chinese
/// \brief 设置用户自定义的设备昵称。
/// \param [in] hCamera 相机的句柄。
/// \param [in] pName   指针，指向0结尾的字符串，设备昵称不超过32个字节，因此该指针指向字符串必须小于等于32个字节空间。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set user-defined device nicknames.
/// \param [in] hCamera Camera handle.
/// \param [in] pName A string that ends with 0, the device nickname does not exceed 32 bytes, so the pointer to the string must be less than or equal to 32 bytes.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetFriendlyName(
  CameraHandle  hCamera,
  char*       pName
);

/// @ingroup API_BASIC
/// \~chinese
/// \brief 读取SDK版本号
/// \param [out] pVersionString 指针，返回SDK版本字符串。该指针指向的缓冲区大小必须大于32个字节
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Read the SDK version number
/// \param [out] pVersionString Returns the SDK version string. The buffer pointed to by this pointer must be larger than 32 bytes
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSdkGetVersionString(
  char*       pVersionString
);

/******************************************************/
// 函数名   : CameraCheckFwUpdate
// 功能描述 : 检测固件版本，是否需要升级。
// 参数     : hCamera 相机的句柄，由CameraInit函数获得。
//            pNeedUpdate 指针，返回固件检测状态，TRUE表示需要更新
// 返回值   : 成功时，返回CAMERA_STATUS_SUCCESS (0);
//            否则返回非0值的错误码,请参考CameraStatus.h
//            中错误码的定义。
/******************************************************/
MVSDK_API CameraSdkStatus __stdcall CameraCheckFwUpdate(
  CameraHandle  hCamera,
  BOOL*     pNeedUpdate
);

/// @ingroup API_BASIC
/// \~chinese
/// \brief 获得固件版本的字符串
/// \param [in] hCamera 相机的句柄。
/// \param [out] pVersion 必须指向一个大于32字节的缓冲区，返回固件的版本字符串。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the firmware version string
/// \param [in] hCamera Camera handle.
/// \param [out] pVersion must point to a buffer larger than 32 bytes and return the firmware version string.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetFirmwareVersion(
	CameraHandle  hCamera,
	char*     pVersion
	);

// 功能与CameraGetFirmwareVersion相同。Version拼写错误，为了兼容性保留
// Same function as CameraGetFirmwareVersion. Version misspelled, reserved for compatibility
MVSDK_API CameraSdkStatus __stdcall CameraGetFirmwareVision(
  CameraHandle  hCamera,
  char*     pVersion
);

/// @ingroup API_BASIC
/// \~chinese
/// \brief 获得指定设备的枚举信息
/// \param [in] hCamera 相机的句柄。
/// \param [out] pCameraInfo 指针，返回设备的枚举信息。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get enumeration information for the specified device
/// \param [in] hCamera Camera handle.
/// \param [out] pCameraInfo Returns the enumeration information for the device.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetEnumInfo(
  CameraHandle    hCamera,
  tSdkCameraDevInfo*  pCameraInfo
);

/// @ingroup API_BASIC
/// \~chinese
/// \brief 获得指定设备接口的版本
/// \param [in] hCamera 相机的句柄。
/// \param [out] pVersion 指向一个大于32字节的缓冲区，返回接口版本字符串。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the version of the specified device interface
/// \param [in] hCamera Camera handle.
/// \param [out] pVersion points to a buffer larger than 32 bytes and returns the interface version string.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetInerfaceVersion(
  CameraHandle    hCamera,
  char*       pVersion
);

/// @ingroup API_GPIO
/// \~chinese
/// \brief 设置指定IO的电平状态，IO为输出型IO，相机预留可编程输出IO的个数由@link #tSdkCameraCapbility.iOutputIoCounts @endlink决定。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iOutputIOIndex IO的索引号，从0开始。
/// \param [in] uState 要设定的状态，1为高，0为低
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set the level state of the specified IO. IO is the output IO. The number of programmable output IOs for the camera is determined by @link #tSdkCameraCapbility.iOutputIoCounts @endlink.
/// \param [in] hCamera Camera handle.
/// \param [in] iOutputIOIndex IO index, starting from 0.
/// \param [in] uState The state to set, 1 is high, 0 is low
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetIOState(
  CameraHandle    hCamera,
  INT         iOutputIOIndex,
  UINT        uState
);

/// @ingroup API_GPIO
/// \~chinese
/// \brief 读取指定IO的电平状态，IO为输入型IO，相机预留可编程输出IO的个数由@link #tSdkCameraCapbility.iInputIoCounts @endlink决定。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iInputIOIndex IO的索引号，从0开始。
/// \param [out] puState 指针，返回IO状态,1为高，0为低
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Read the level state of the specified IO, IO is input type IO, the number of programmable output IOs that the camera reserves is decided by @link #tSdkCameraCapbility.iInputIoCounts @endlink.
/// \param [in] hCamera Camera handle.
/// \param [in] iInputIOIndex IO index, starting from 0.
/// \param [out] puState returns IO state, 1 is high, 0 is low
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetIOState(
  CameraHandle    hCamera,
  INT         iInputIOIndex,
  UINT*         puState
);

/// @ingroup API_GPIO
/// \~chinese
/// \brief 设置输入IO的模式
/// \param [in] hCamera 相机的句柄。
/// \param [in] iInputIOIndex IO的索引号，从0开始。
/// \param [in] iMode IO模式,参考@link #emCameraGPIOMode @endlink
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set the input IO mode
/// \param [in] hCamera Camera handle.
/// \param [in] iInputIOIndex IO index, starting from 0.
/// \param [in] iMode IO mode, reference @link #emCameraGPIOMode @endlink
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetInPutIOMode(
	CameraHandle    hCamera,
	INT         iInputIOIndex,
	INT			iMode
	);

/// @ingroup API_GPIO
/// \~chinese
/// \brief 设置输出IO的模式
/// \param [in] hCamera 相机的句柄。
/// \param [in] iOutputIOIndex IO的索引号，从0开始。
/// \param [in] iMode IO模式,参考@link #emCameraGPIOMode @endlink
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set the output IO mode
/// \param [in] hCamera Camera handle.
/// \param [in] iOutputIOIndex IO index, starting from 0.
/// \param [in] iMode IO mode, reference @link #emCameraGPIOMode @endlink
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetOutPutIOMode(
	CameraHandle    hCamera,
	INT         iOutputIOIndex,
	INT			iMode
	);

/// @ingroup API_GPIO
/// \~chinese
/// \brief 设置PWM型输出的参数
/// \param [in] hCamera 相机的句柄。
/// \param [in] iOutputIOIndex IO的索引号，从0开始。
/// \param [in] iCycle PWM的周期，单位(us)
/// \param [in] uDuty  占用比，取值1%~99%
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set the PWM output parameters
/// \param [in] hCamera Camera handle.
/// \param [in] iOutputIOIndex IO index, starting from 0.
/// \param [in] iCycle Cycle of PWM, unit (us)
/// \param [in] uDuty Occupancy ratio, 1%~99%
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetOutPutPWM(
	CameraHandle    hCamera,
	INT         iOutputIOIndex,
	UINT		iCycle,
	UINT		uDuty
	);

// @ingroup API_EXPOSURE
/// \~chinese
/// \brief 设置自动曝光时选择的算法，不同的算法适用于不同的场景。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iIspProcessor   选择执行该算法的对象,参考@link #emSdkIspProcessor @endlink
/// \param [in] iAeAlgorithmSel   要选择的算法编号。从0开始，最大值由@link #tSdkCameraCapbility.iAeAlmSwDesc @endlink和@link #tSdkCameraCapbility.iAeAlmHdDesc @endlink决定。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief The algorithm selected when setting up the automatic exposure, different algorithms are suitable for different scenes.
/// \param [in] hCamera Camera handle.
/// \param [in] iIspProcessor Select the object to execute the algorithm, refer to @link #emSdkIspProcessor @endlink
/// \param [in] iAeAlgorithmSel The algorithm number to select. From 0, the maximum value is determined by @link #tSdkCameraCapbility.iAeAlmSwDesc @endlink and @link #tSdkCameraCapbility.iAeAlmHdDesc @endlink.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetAeAlgorithm(
    CameraHandle    hCamera,
    INT             iIspProcessor,
    INT             iAeAlgorithmSel
);

// @ingroup API_EXPOSURE
/// \~chinese
/// \brief 获得当前自动曝光所选择的算法
/// \param [in] hCamera 相机的句柄。
/// \param [in] iIspProcessor   选择执行该算法的对象,参考@link #emSdkIspProcessor @endlink
/// \param [out] piAlgorithmSel   返回当前选择的算法编号。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the current auto exposure selected algorithm
/// \param [in] hCamera Camera handle.
/// \param [in] iIspProcessor Select the object to execute the algorithm, refer to @link #emSdkIspProcessor @endlink
/// \param [out] piAlgorithmSel Returns the currently selected algorithm number.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetAeAlgorithm(
    CameraHandle    hCamera,
    INT             iIspProcessor,
    INT*            piAlgorithmSel
);

/// @ingroup API_ISP
/// \~chinese
/// \brief 设置Bayer数据转彩色的算法。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iIspProcessor   选择执行该算法的对象，参考@link #emSdkIspProcessor @endlink
/// \param [in] iAlgorithmSel     要选择的算法编号。从0开始，最大值由tSdkCameraCapbility.iBayerDecAlmSwDesc和tSdkCameraCapbility.iBayerDecAlmHdDesc决定。  
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set Bayer data to color algorithm.
/// \param [in] hCamera Camera handle.
/// \param [in] iIspProcessor Select the object to execute the algorithm, refer to @link #emSdkIspProcessor @endlink
/// \param [in] iAlgorithmSel The algorithm number to select. From 0, the maximum value is determined by tSdkCameraCapbility.iBayerDecAlmSwDesc and tSdkCameraCapbility.iBayerDecAlmHdDesc.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetBayerDecAlgorithm(
    CameraHandle    hCamera,
    INT             iIspProcessor,
    INT             iAlgorithmSel
);

/// @ingroup API_ISP
/// \~chinese
/// \brief 获得Bayer数据转彩色所选择的算法。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iIspProcessor   选择执行该算法的对象，参考@link #emSdkIspProcessor @endlink
/// \param [in] piAlgorithmSel  返回当前选择的算法编号。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the algorithm chosen by Bayer data to color.
/// \param [in] hCamera Camera handle.
/// \param [in] iIspProcessor Select the object to execute the algorithm, refer to @link #emSdkIspProcessor @endlink
/// \param [in] piAlgorithmSel Returns the currently selected algorithm number.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetBayerDecAlgorithm(
    CameraHandle    hCamera,
    INT             iIspProcessor,
    INT*            piAlgorithmSel
);

// @ingroup API_ISP
/// \~chinese
/// \brief 设置图像处理单元的算法执行对象，由PC端或者相机端来执行算法，当由相机端执行时，会降低PC端的CPU占用率。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iIspProcessor 参考@link #emSdkIspProcessor @endlink
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Sets the algorithm execution object of the image processing unit. The algorithm is executed by the PC or the camera. When executed by the camera, the CPU usage of the PC is reduced.
/// \param [in] hCamera Camera handle.
/// \param [in] iIspProcessor Reference @link #emSdkIspProcessor @endlink
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetIspProcessor(
    CameraHandle    hCamera,
    INT             iIspProcessor
);

// @ingroup API_ISP
/// \~chinese
/// \brief 获得图像处理单元的算法执行对象。
/// \param [in] hCamera 相机的句柄。
/// \param [out] piIspProcessor 返回选择的对象
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the image processing unit's algorithm execution object.
/// \param [in] hCamera Camera handle.
/// \param [out] piIspProcessor returns the selected object
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetIspProcessor(
    CameraHandle    hCamera,
    INT*            piIspProcessor
);

/// @ingroup API_ISP
/// \~chinese
/// \brief 设置图像的黑电平基准，默认值为0
/// \param [in] hCamera 相机的句柄。
/// \param [in] iBlackLevel 要设定的电平值。范围为0到255。 
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Sets the black level reference of the image. The default value is 0
/// \param [in] hCamera Camera handle.
/// \param [in] iBlackLevel The value to set. The range is 0 to 255.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetBlackLevel(
  CameraHandle    hCamera,
  INT         iBlackLevel
);

/// @ingroup API_ISP
/// \~chinese
/// \brief 获得图像的黑电平基准，默认值为0
/// \param [in] hCamera 相机的句柄。
/// \param [out] piBlackLevel 返回当前的黑电平值。范围为0到255。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the black level of the image, the default value is 0
/// \param [in] hCamera Camera handle.
/// \param [out] piBlackLevel Returns the current black level value. The range is 0 to 255.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetBlackLevel(
  CameraHandle    hCamera,
  INT*        piBlackLevel
);

/// @ingroup API_ISP
/// \~chinese
/// \brief 设置图像的白电平基准，默认值为255
/// \param [in] hCamera 相机的句柄。
/// \param [in] iWhiteLevel 要设定的电平值。范围为0到255。  
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Sets the white level reference of the image. The default value is 255
/// \param [in] hCamera Camera handle.
/// \param [in] iWhiteLevel The level to be set. The range is 0 to 255.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetWhiteLevel(
  CameraHandle    hCamera,
  INT         iWhiteLevel
);

/// @ingroup API_ISP
/// \~chinese
/// \brief 获得图像的白电平基准，默认值为255
/// \param [in] hCamera 相机的句柄。
/// \param [out] piWhiteLevel 返回当前的白电平值。范围为0到255。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the white level of the image, the default value is 255
/// \param [in] hCamera Camera handle.
/// \param [out] piWhiteLevel Returns the current white level value. The range is 0 to 255.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetWhiteLevel(
  CameraHandle    hCamera,
  INT*        piWhiteLevel
);

/// @ingroup API_ISP
/// \~chinese
/// \brief 设置@link #CameraImageProcess @endlink函数的图像处理的输出格式。
/// \param [in] hCamera 相机的句柄。
/// \param [in] uFormat	输出格式。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 支持的格式：CAMERA_MEDIA_TYPE_MONO8、CAMERA_MEDIA_TYPE_MONO16、CAMERA_MEDIA_TYPE_RGB8、CAMERA_MEDIA_TYPE_RGBA8	、CAMERA_MEDIA_TYPE_BGR8、CAMERA_MEDIA_TYPE_BGRA8
/// \~english
/// \brief Sets the output format of image processing for the @link #CameraImageProcess @endlink function.
/// \param [in] hCamera Camera handle.
/// \param [in] uFormat output format.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note Supported formats: CAMERA_MEDIA_TYPE_MONO8, CAMERA_MEDIA_TYPE_MONO16, CAMERA_MEDIA_TYPE_RGB8, CAMERA_MEDIA_TYPE_RGBA8, CAMERA_MEDIA_TYPE_BGR8, CAMERA_MEDIA_TYPE_BGRA8
MVSDK_API CameraSdkStatus __stdcall CameraSetIspOutFormat(
    CameraHandle    hCamera,
    UINT            uFormat
);

/// @ingroup API_ISP
/// \~chinese
/// \brief 获取输出格式
/// \param [in] hCamera 相机的句柄。
/// \param [out] puFormat	返回当前输出格式
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \see CameraSetIspOutFormat
/// \~english
/// \brief Get output format
/// \param [in] hCamera Camera handle.
/// \param [out] puFormat returns the current output format
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \see CameraSetIspOutFormat
MVSDK_API CameraSdkStatus __stdcall CameraGetIspOutFormat(
    CameraHandle    hCamera,
    UINT*           puFormat
);

/// @ingroup API_UTIL
/// \~chinese
/// \brief 获得错误码对应的描述字符串
/// \param [in] iStatusCode		错误码。(定义于CameraStatus.h中)
/// \return 成功时，返回错误码对应的字符串首地址;否则返回NULL。
/// \~english
/// \brief Get the description string corresponding to the error code
/// \param [in] iStatusCode error code. (Defined in CameraStatus.h)
/// When the return is successful, the first address of the string corresponding to the error code is returned; otherwise it returns NULL.
MVSDK_API char* __stdcall CameraGetErrorString(
    CameraSdkStatus     iStatusCode
);

/// @ingroup API_GRAB
/// \~chinese
/// \brief 获得一帧图像数据。该接口获得的图像是经过处理后的RGB格式。
/// \param [in] hCamera 相机的句柄。
/// \param [out] pImageData  接收图像数据的缓冲区，大小必须和uOutFormat指定的格式相匹配，否则数据会溢出
/// \param [in] uOutFormat	 输出格式 0:Mono8 1:rgb24 2:rgba32 3:bgr24 4:bgra32
/// \param [out] piWidth     整形指针，返回图像的宽度
/// \param [out] piHeight    整形指针，返回图像的高度
/// \param [in] wTimes      抓取图像的超时时间。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 不需要调用 @link #CameraReleaseImageBuffer @endlink
/// \~english
/// \brief Get a frame of image data. The image obtained by this interface is the processed RGB format.
/// \param [in] hCamera Camera handle.
/// \param [out] pImageData The buffer to receive the image data, the size must match the format specified by uOutFormat, otherwise the data will overflow
/// \param [in] uOutFormat output format 0:Mono8 1:rgb24 2:rgba32 3:bgr24 4:bgra32
/// \param [out] piWidth Returns the width of the image
/// \param [out] piHeight Returns the height of the image
/// \param [in] wTimes The time-out time for capturing images.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note does not need to call @link #CameraReleaseImageBuffer @endlink
MVSDK_API CameraSdkStatus __stdcall CameraGetImageBufferEx2(
    CameraHandle    hCamera, 
    BYTE*           pImageData,
    UINT            uOutFormat,
    int*            piWidth,
    int*            piHeight,
    UINT            wTimes
);

/// @ingroup API_GRAB
/// \~chinese
/// \brief 获得一帧图像数据。该接口获得的图像是经过处理后的RGB格式。
/// \param [in] hCamera 相机的句柄。
/// \param [out] pImageData  接收图像数据的缓冲区，大小必须和uOutFormat指定的格式相匹配，否则数据会溢出
/// \param [in] uOutFormat	 输出格式 0:Mono8 1:rgb24 2:rgba32 3:bgr24 4:bgra32
/// \param [out] piWidth     整形指针，返回图像的宽度
/// \param [out] piHeight    整形指针，返回图像的高度
/// \param [out] puTimeStamp 返回图像时间戳 
/// \param [in] wTimes      抓取图像的超时时间。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 不需要调用 @link #CameraReleaseImageBuffer @endlink
/// \~english
/// \brief Get a frame of image data. The image obtained by this interface is the processed RGB format.
/// \param [in] hCamera Camera handle.
/// \param [out] pImageData The buffer to receive the image data, the size must match the format specified by uOutFormat, otherwise the data will overflow
/// \param [in] uOutFormat output format 0:Mono8 1:rgb24 2:rgba32 3:bgr24 4:bgra32
/// \param [out] piWidth Returns the width of the image
/// \param [out] piHeight Returns the height of the image
/// \param [out] puTimeStamp returns image timestamp
/// \param [in] wTimes The time-out time for capturing images.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note does not need to call @link #CameraReleaseImageBuffer @endlink
MVSDK_API CameraSdkStatus __stdcall CameraGetImageBufferEx3(
	CameraHandle hCamera, 
	BYTE*pImageData,
	UINT uOutFormat,
	int *piWidth,
	int *piHeight,
	UINT* puTimeStamp,
	UINT wTimes
);

/// @ingroup API_BASIC
/// \~chinese
/// \brief 获得该相机的一些特性。
/// \param [in] hCamera 相机的句柄。
/// \param [out] pMaxWidth	    返回该相机最大分辨率的宽度
/// \param [out] pMaxHeight      返回该相机最大分辨率的高度 
/// \param [out] pbColorCamera    返回该相机是否是彩色相机。1表示彩色相机，0表示黑白相机
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get some of the camera's features.
/// \param [in] hCamera Camera handle.
/// \param [out] pMaxWidth Returns the width of the camera's maximum resolution
/// \param [out] pMaxHeight Returns the height of the camera's maximum resolution
/// \param [out] pbColorCamera Returns whether the camera is a color camera. 1 indicates a color camera, 0 indicates a black and white camera
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetCapabilityEx2(
    CameraHandle    hCamera,
    int*            pMaxWidth,
    int*            pMaxHeight,
    int*            pbColorCamera
);

/// @ingroup API_RECONNECT
/// \~chinese
/// \brief 重新连接设备，用于连接恢复后手动重连
/// \param [in] hCamera 相机的句柄。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \warning 相机默认使能了自动重连，在自动重连模式中请勿调用本函数。@see CameraSetAutoConnect
/// \~english
/// \brief Reconnect the device to manually reconnect after the connection is restored
/// \param [in] hCamera Camera handle.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \warning The camera automatically enables reconnection by default. Do not call this function in auto reconnect mode. @see CameraSetAutoConnect
MVSDK_API CameraSdkStatus __stdcall CameraReConnect(
    CameraHandle    hCamera
);

/// @ingroup API_RECONNECT
/// \~chinese
/// \brief 测试相机的连接状态，用于检测相机是否掉线
/// \param [in] hCamera 相机的句柄。
/// \return 连接正常返回CAMERA_STATUS_SUCCESS(0)。否则表示已掉线
/// \~english
/// \brief Test camera connection status to detect if camera is dropped
/// \param [in] hCamera Camera handle.
/// \return The connection normally returns CAMERA_STATUS_SUCCESS(0). Otherwise it is dropped
MVSDK_API CameraSdkStatus __stdcall CameraConnectTest(
    CameraHandle    hCamera
);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 设置相机的LED使能状态，不带LED的型号，此函数返回错误代码，表示不支持。
/// \param [in] hCamera 相机的句柄。
/// \param [in] index       LED灯的索引号，从0开始。如果只有一个可控制亮度的LED，则该参数为0 。
/// \param [in] enable      使能状态
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set the camera's LED enable status, without the LED's model, this function returns an error code indicating that it is not supported.
/// \param [in] hCamera Camera handle.
/// \param [in] index The index of the LED, starting from 0. If there is only one LED that can control the brightness, this parameter is 0.
/// \param [in] enable enable state
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetLedEnable(
	CameraHandle    hCamera,
	int             index,
	BOOL            enable
	);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 获得相机的LED使能状态，不带LED的型号，此函数返回错误代码，表示不支持。
/// \param [in] hCamera 相机的句柄。
/// \param [in] index       LED灯的索引号，从0开始。如果只有一个可控制亮度的LED，则该参数为0 。
/// \param [out] enable      指针，返回LED使能状态
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the camera's LED enable status, without the LED's model, this function returns an error code indicating that it is not supported.
/// \param [in] hCamera Camera handle.
/// \param [in] index The index of the LED, starting from 0. If there is only one LED that can control the brightness, this parameter is 0.
/// \param [out] enable Return LED enable status
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetLedEnable(
	CameraHandle    hCamera,
	int             index,
	BOOL*           enable
	);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 设置相机的LED开关状态，不带LED的型号，此函数返回错误代码，表示不支持。
/// \param [in] hCamera 相机的句柄。
/// \param [in] index       LED灯的索引号，从0开始。如果只有一个可控制亮度的LED，则该参数为0 。
/// \param [in] onoff	   LED开关状态
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set the camera's LED switch status, without the LED's model, this function returns an error code indicating that it is not supported.
/// \param [in] hCamera Camera handle.
/// \param [in] index The index of the LED, starting from 0. If there is only one LED that can control the brightness, this parameter is 0.
/// \param [in] onoff LED on/off status
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetLedOnOff(
	CameraHandle    hCamera,
	int             index,
	BOOL            onoff
	);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 获得相机的LED开关状态，不带LED的型号，此函数返回错误代码，表示不支持。
/// \param [in] hCamera 相机的句柄。
/// \param [in] index      LED灯的索引号，从0开始。如果只有一个可控制亮度的LED，则该参数为0 。
/// \param [out] onoff	   返回LED开关状态
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the camera's LED switch status, without the LED model, this function returns an error code that does not support.
/// \param [in] hCamera Camera handle.
/// \param [in] index The index of the LED, starting from 0. If there is only one LED that can control the brightness, this parameter is 0.
/// \param [out] onoff Returns LED switch status
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetLedOnOff(
	CameraHandle    hCamera,
	int             index,
	BOOL*           onoff
	);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 设置相机的LED持续时间，不带LED的型号，此函数返回错误代码，表示不支持。
/// \param [in] hCamera 相机的句柄。
/// \param [in] index        LED灯的索引号，从0开始。如果只有一个可控制亮度的LED，则该参数为0 。
/// \param [in] duration		LED持续时间，单位毫秒
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set the camera's LED duration, without the LED model, this function returns an error code indicating that it is not supported.
/// \param [in] hCamera Camera handle.
/// \param [in] index The index of the LED, starting from 0. If there is only one LED that can control the brightness, this parameter is 0.
/// \param [in] duration LED duration in milliseconds
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetLedDuration(
	CameraHandle    hCamera,
	int             index,
	UINT            duration
	);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 获得相机的LED持续时间，不带LED的型号，此函数返回错误代码，表示不支持。
/// \param [in] hCamera 相机的句柄。
/// \param [in] index        LED灯的索引号，从0开始。如果只有一个可控制亮度的LED，则该参数为0 。
/// \param [out] duration	 返回LED持续时间，单位毫秒
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the camera's LED duration, without the LED model, this function returns an error code indicating that it is not supported.
/// \param [in] hCamera Camera handle.
/// \param [in] index The index of the LED, starting from 0. If there is only one LED that can control the brightness, this parameter is 0.
/// \param [out] duration Returns the LED duration in milliseconds
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetLedDuration(
	CameraHandle    hCamera,
	int             index,
	UINT*           duration
	);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 设置相机的LED亮度，不带LED的型号，此函数返回错误代码，表示不支持。
/// \param [in] hCamera 相机的句柄。
/// \param [in] index      LED灯的索引号，从0开始。如果只有一个可控制亮度的LED，则该参数为0 。
/// \param [in] uBrightness LED亮度值，范围0到255. 0表示关闭，255最亮。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set the camera's LED brightness, without the LED model, this function returns an error code indicating that it is not supported.
/// \param [in] hCamera Camera handle.
/// \param [in] index The index of the LED, starting from 0. If there is only one LED that can control the brightness, this parameter is 0.
/// \param [in] uBrightness LED brightness value, range 0 to 255. 0 means off, 255 brightest.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetLedBrightness(
    CameraHandle    hCamera,
    int             index,
    UINT            uBrightness
);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 获得相机的LED亮度，不带LED的型号，此函数返回错误代码，表示不支持。
/// \param [in] hCamera 相机的句柄。
/// \param [in] index      LED灯的索引号，从0开始。如果只有一个可控制亮度的LED，则该参数为0 。
/// \param [out] uBrightness 指针，返回LED亮度值，范围0到255. 0表示关闭，255最亮。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the camera's LED brightness, without the LED model, this function returns an error code that does not support.
/// \param [in] hCamera Camera handle.
/// \param [in] index The index of the LED, starting from 0. If there is only one LED that can control the brightness, this parameter is 0.
/// \param [out] uBrightness Returns the LED brightness value in the range 0 to 255. 0 means off, 255 is the brightest.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetLedBrightness(
    CameraHandle    hCamera,
    int             index,
    UINT*           uBrightness
);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 使能或者禁止相机的多区域传输功能，不带该功能的型号，此函数返回错误代码，表示不支持。
/// \param [in] hCamera 相机的句柄。
/// \param [in] uEnableMask 区域使能状态掩码，对应的比特位为1表示使能。0为禁止。目前SDK支持4个可编辑区域，index范围为0到3，即bit0 ，bit1，bit2，bit3控制4个区域的使能状态。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 该功能主要用于在相机端将采集的整幅画面切分，只传输指定的多个区域，以提高传输帧率。多个区域传输到PC上后，会自动拼接成整幅画面，没有被传输的部分，会用黑色填充。
/// \~english
/// \brief Enables or disables the camera's multi-zone transfer function. For models without this function, this function returns an error code indicating that it is not supported.
/// \param [in] hCamera Camera handle.
/// \param [in] uEnableMask Area enable mask. The corresponding bit is 1 to enable. 0 is prohibited. Currently, the SDK supports four editable regions. The index range is 0 to 3, that is, bit0, bit1, bit2, and bit3 control the enabling status of the four regions.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note This function is mainly used to split the entire picture collected on the camera side and only transmit specified multiple areas to increase the transmission frame rate. After multiple areas are transferred to the PC, they will be automatically spliced into an entire frame. Parts that have not been transmitted will be filled with black.
MVSDK_API CameraSdkStatus __stdcall CameraEnableTransferRoi(
    CameraHandle    hCamera,
    UINT            uEnableMask
);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 设置相机传输的裁剪区域。在相机端，图像从传感器上被采集后，将会被裁剪成指定的区域来传送，此函数返回错误代码，表示不支持。
/// \param [in] hCamera		相机的句柄。
/// \param [in] index		ROI区域的索引号，从0开始。
/// \param [in] X1			ROI区域的左上角X坐标
/// \param [in] Y1			ROI区域的左上角Y坐标
/// \param [in] X2			ROI区域的右下角X坐标
/// \param [in] Y2			ROI区域的右下角Y坐标
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Sets the clipping area for camera transmission. On the camera side, after the image is captured from the sensor, it will be cropped to the specified area for transmission. This function returns an error code indicating that it is not supported.
/// \param [in] hCamera Camera handle.
/// \param [in] index The index number of the ROI region, starting at 0.
/// \param [in] X1 The X coordinate of the upper left corner of ROI area
/// \param [in] Y1 The Y coordinate of the upper left corner of ROI area
/// \param [in] X2 The X coordinate of the lower right corner of ROI area
/// \param [in] Y2 The Y coordinate of the lower right corner of ROI area
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetTransferRoi(
    CameraHandle    hCamera,
    int             index,
    UINT            X1,
    UINT            Y1,
    UINT            X2,
    UINT            Y2
);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 获取相机传输的裁剪区域。在相机端，图像从传感器上被采集后，将会被裁剪成指定的区域来传送，此函数返回错误代码，表示不支持。
/// \param [in] hCamera		相机的句柄。
/// \param [in] index		ROI区域的索引号，从0开始。
/// \param [out] pX1		ROI区域的左上角X坐标
/// \param [out] pY1		ROI区域的左上角Y坐标
/// \param [out] pX2		ROI区域的右下角X坐标
/// \param [out] pY2		ROI区域的右下角Y坐标
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the cropped area of the camera transmission. On the camera side, after the image is captured from the sensor, it will be cropped to the specified area for transmission. This function returns an error code indicating that it is not supported.
/// \param [in] hCamera Camera handle.
/// \param [in] index The index number of the ROI region, starting at 0.
/// \param [out] pX1 Returns the X coordinate of the upper left corner of the ROI area
/// \param [out] pY1 Returns the Y coordinate of the upper left corner of the ROI area
/// \param [out] pX2 Returns the X coordinate of the lower right corner of the ROI area
/// \param [out] pY2 Returns the Y coordinate of the lower right corner of the ROI area
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetTransferRoi(
    CameraHandle    hCamera,
    int             index,
    UINT*           pX1,
    UINT*           pY1,
    UINT*           pX2,
    UINT*           pY2
);

/// @ingroup API_UTIL
/// \~chinese
/// \brief 申请一段对齐的内存空间。功能和malloc类似，但是返回的内存是以align指定的字节数对齐的。
/// \param [in] size	 空间的大小。 
/// \param [in] align    地址对齐的字节数。
/// \return 成功时，返回非0值，表示内存首地址。失败返回NULL。
/// \note 分配的内存必须使用@link #CameraAlignFree @endlink释放
/// \~english
/// \brief Apply for an aligned memory space. The function is similar to malloc, but the returned memory is aligned with the number of bytes specified by align.
/// \param [in] size Size of the space.
/// \param [in] align The number of aligned bytes.
/// \return Successful a non-zero value is returned indicating the first address of the memory. Fails to return NULL.
/// \note Memory allocated must be freed using @link #CameraAlignFree @endlink
MVSDK_API BYTE* __stdcall CameraAlignMalloc(
    int             size,
    int             align
    );

/// @ingroup API_UTIL
/// \~chinese
/// \brief 释放由@link #CameraAlignMalloc @endlink函数分配的内存空间。
/// \param [in] membuffer	内存地址
/// \~english
/// \brief Releases the memory space allocated by the @link #CameraAlignMalloc @endlink function.
/// \param [in] membuffer memory address
MVSDK_API void __stdcall CameraAlignFree(
    BYTE*           membuffer
);

/// @ingroup API_RECONNECT
/// \~chinese
/// \brief 启用或禁用自动重连，默认为启用。
/// \param [in] hCamera 相机的句柄。
/// \param [in] bEnable	使能相机重连，当位TRUE时，SDK内部自动检测相机是否掉线，掉线后自己重连。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Enables or disables automatic reconnection. The default is enabled.
/// \param [in] hCamera Camera handle.
/// \param [in] bEnable Enables the camera to reconnect. When TRUE, the SDK automatically detects if the camera is dropped and reconnects itself after disconnection.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetAutoConnect(CameraHandle hCamera,BOOL bEnable);

/// @ingroup API_RECONNECT
/// \~chinese
/// \brief 获取自动重连使能状态
/// \param [in] hCamera 相机的句柄。
/// \param [out] pbEnable	   返回相机自动重连使能状态
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get Automatic Reconnect Enable Status
/// \param [in] hCamera Camera handle.
/// \param [out] pbEnable Returns the camera's auto reconnect status
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetAutoConnect(CameraHandle hCamera,BOOL *pbEnable);

/// @ingroup API_RECONNECT
/// \~chinese
/// \brief 获得相机自动重连的次数，前提是@link #CameraSetAutoConnect @endlink使能相机自动重连功能。默认是使能的。
/// \param [in] hCamera 相机的句柄。
/// \param [out] puCounts	   返回自动重连的次数
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the number of times the camera automatically reconnects, provided @link #CameraSetAutoConnect @endlink enables automatic camera reconnection. The default is enabled.
/// \param [in] hCamera Camera handle.
/// \param [out] puCounts returns the number of automatic reconnections
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetReConnectCounts(CameraHandle hCamera,UINT* puCounts);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 启用或禁用单帧抓取模式，默认为禁用。（本功能仅USB2.0相机支持）
/// \param [in] hCamera 相机的句柄。
/// \param [in] bEnable	使能单帧抓取模式
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 每当成功抓取到一帧后SDK会进入暂停状态，从而不再占用USB带宽，主要用于多相机轮流拍照的场景。
/// \~english
/// \brief Enables or disables single-frame crawl mode, which is disabled by default. (This function is only supported by USB2.0 camera)
/// \param [in] hCamera Camera handle.
/// \param [in] bEnable enables single-frame mode
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note Whenever a frame is successfully captured, the SDK enters a pause state, so that it no longer occupies the USB bandwidth. It is mainly used in scenes where multiple cameras take pictures.
MVSDK_API CameraSdkStatus __stdcall CameraSetSingleGrabMode(CameraHandle hCamera, BOOL bEnable);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 获得相机的单帧抓取使能状态
/// \param [in] hCamera 相机的句柄。
/// \param [out] pbEnable 返回相机的单帧抓取模式使能状态
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the camera's single frame capture enable status
/// \param [in] hCamera Camera handle.
/// \param [out] pbEnable Returns the camera's single frame capture mode enable status
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetSingleGrabMode(CameraHandle hCamera, BOOL* pbEnable);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 当相机处于单帧抓取模式时，每当成功抓取到一帧后SDK会进入暂停状态，调用此函数可使SDK退出暂停状态并开始抓取下一帧
/// \param [in] hCamera 相机的句柄。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief When the camera is in the single frame capture mode, the SDK will enter a pause state after successfully capturing a frame. Calling this function will cause the SDK to exit the pause state and start to grab the next frame.
/// \param [in] hCamera Camera handle.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraRestartGrab(CameraHandle hCamera);

/// @ingroup API_UTIL
/// \~chinese
/// \brief 图片清晰度评估
/// \param [in] hCamera 相机的句柄。
/// \param [in] iAlgorithSel 使用的评估算法,参考@link emEvaluateDefinitionAlgorith @endlink的定义
/// \param [in] pbyIn    输入图像数据的缓冲区地址，不能为NULL。 
/// \param [in] pFrInfo  输入图像的帧头信息
/// \param [out] DefinitionValue 返回的清晰度估值（越大越清晰）
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Image clarity assessment
/// \param [in] hCamera Camera handle.
/// \param [in] iAlgorithSel The currently used evaluation algorithm, see @link emEvaluateDefinitionAlgorith @endlink
/// \param [in] pbyIn The buffer address of the input image data. Cannot be NULL.
/// \param [in] pFrInfo input image frame header information
/// \param [out] DefinitionValue Returns the sharpness value (greater the clearer)
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraEvaluateImageDefinition(
	CameraHandle        hCamera,
	INT					iAlgorithSel,
	BYTE*               pbyIn, 
	tSdkFrameHead*      pFrInfo,
	double*				DefinitionValue
	);

/// @ingroup API_UTIL
/// \~chinese
/// \brief 在输入的图像数据中绘制文字
/// \param [inout] pRgbBuffer 图像数据缓冲区
/// \param [in] pFrInfo 图像的帧头信息
/// \param [in] pFontFileName 字体文件名
/// \param [in] FontWidth 字体宽度
/// \param [in] FontHeight 字体高度
/// \param [in] pText 要输出的文字
/// \param [in] Left 文字的输出矩形
/// \param [in] Top 文字的输出矩形
/// \param [in] Width 文字的输出矩形
/// \param [in] Height 文字的输出矩形
/// \param [in] TextColor 文字颜色RGB
/// \param [in] uFlags 输出标志,详见@link #emCameraDrawTextFlags @endlink中的定义
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Draw text in the input image data
/// \param [inout] pRgbBuffer image data buffer
/// \param [in] pFrInfo frame header information
/// \param [in] pFontFileName font file name
/// \param [in] FontWidth font width
/// \param [in] FontHeight font height
/// \param [in] pText Text to output
/// \param [in] Left text output rectangle
/// \param [in] Top text output rectangle
/// \param [in] Width Output rectangle of text
/// \param [in] Height the output rectangle of the text
/// \param [in] TextColor Text Color RGB
/// \param [in] uFlags output flags, as defined in @link #emCameraDrawTextFlags @endlink
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraDrawText(
	BYTE*           pRgbBuffer,
	tSdkFrameHead*  pFrInfo,
	char const*		pFontFileName, 
	UINT			FontWidth,
	UINT			FontHeight,
	char const*		pText, 
	INT				Left,
	INT				Top,
	UINT			Width,
	UINT			Height,
	UINT			TextColor,
	UINT			uFlags
	);

/// @ingroup API_UTIL
/// \~chinese
/// \brief 获取GIGE相机的IP地址
/// \param [in] pCameraInfo 相机的设备描述信息，可由@link #CameraEnumerateDevice @endlink函数获得。 
/// \param [out] CamIp 相机IP(注意：必须保证传入的缓冲区大于等于16字节)
/// \param [out] CamMask 相机子网掩码(注意：必须保证传入的缓冲区大于等于16字节)
/// \param [out] CamGateWay 相机网关(注意：必须保证传入的缓冲区大于等于16字节)
/// \param [out] EtIp 网卡IP(注意：必须保证传入的缓冲区大于等于16字节)
/// \param [out] EtMask 网卡子网掩码(注意：必须保证传入的缓冲区大于等于16字节)
/// \param [out] EtGateWay 网卡网关(注意：必须保证传入的缓冲区大于等于16字节)
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the GIGE camera's IP address
/// \param [in] pCameraInfo camera's device description information can be obtained by @link #CameraEnumerateDevice @endlink function.
/// \param [out] CamIp camera IP (Note: must ensure that the incoming buffer is greater than or equal to 16 bytes)
/// \param [out] CamMask camera subnet mask (Note: must ensure that the incoming buffer is greater than or equal to 16 bytes)
/// \param [out] CamGateWay camera gateway (Note: must ensure that the incoming buffer is greater than or equal to 16 bytes)
/// \param [out] EtIp network card IP (Note: must ensure that the incoming buffer is greater than or equal to 16 bytes)
/// \param [out] EtMask subnet mask (Note: must ensure that the incoming buffer is greater than or equal to 16 bytes)
/// \param [out] EtGateWay NIC Gateway (Note: must ensure that the incoming buffer is greater than or equal to 16 bytes)
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGigeGetIp(
		tSdkCameraDevInfo* pCameraInfo,
		char* CamIp,
		char* CamMask,
		char* CamGateWay,
		char* EtIp,
		char* EtMask,
		char* EtGateWay
	);

/// @ingroup API_UTIL
/// \~chinese
/// \brief 设置GIGE相机的IP地址
/// \param [in] pCameraInfo 相机的设备描述信息，可由@link #CameraEnumerateDevice @endlink函数获得。 
/// \param [in] Ip 相机IP(如：192.168.1.100)
/// \param [in] SubMask 相机子网掩码(如：255.255.255.0)
/// \param [in] GateWay 相机网关(如：192.168.1.1)
/// \param [in] bPersistent TRUE: 设置相机为固定IP，FALSE：设置相机自动分配IP（忽略参数Ip, SubMask, GateWay）
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set the GIGE camera's IP address
/// \param [in] pCameraInfo camera's device description information can be obtained by @link #CameraEnumerateDevice @endlink function.
/// \param [in] Ip camera IP (eg 192.168.1.100)
/// \param [in] SubMask camera subnet mask (eg 255.255.255.0)
/// \param [in] GateWay Camera Gateway (eg 192.168.1.1)
/// \param [in] bPersistent TRUE: Set camera to fixed IP, FALSE: Set camera to assign IP automatically (ignoring parameters Ip, SubMask, GateWay)
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGigeSetIp(
	tSdkCameraDevInfo* pCameraInfo,
	char const* Ip,
	char const* SubMask,
	char const* GateWay,
	BOOL bPersistent
	);

/// @ingroup API_UTIL
/// \~chinese
/// \brief 获取GIGE相机的MAC地址
/// \param [in] pCameraInfo 相机的设备描述信息，可由@link #CameraEnumerateDevice @endlink函数获得。 
/// \param [out] CamMac 相机MAC(注意：必须保证传入的缓冲区大于等于18字节)
/// \param [out] EtMac 网卡MAC(注意：必须保证传入的缓冲区大于等于18字节)
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Select the LUT table in the preset LUT mode.
/// \param [in] pCameraInfo camera's device description information can be obtained by @link #CameraEnumerateDevice @endlink function.
/// \param [out] CamMac camera MAC (Note: must ensure that the incoming buffer is greater than or equal to 18 bytes)
/// \param [out] EtMac network card MAC (Note: must ensure that the incoming buffer is greater than or equal to 18 bytes)
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGigeGetMac(
	tSdkCameraDevInfo* pCameraInfo,
	char* CamMac,
	char* EtMac
	);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 使能快速响应
/// \param [in] hCamera 相机的句柄。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Enable quick response
/// \param [in] hCamera Camera handle.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraEnableFastResponse(
	CameraHandle hCamera
	);

/// @ingroup API_DEAD_PIXEL
/// \~chinese
/// \brief 使能坏点修正
/// \param [in] hCamera 相机的句柄。
/// \param [in] bEnable TRUE: 使能坏点修正   FALSE: 关闭坏点修正
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Enable dead pixel correction
/// \param [in] hCamera Camera handle.
/// \param [in] bEnable TRUE: Enable dead pixel correction FALSE: Turn off dead pixel correction
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetCorrectDeadPixel(
	CameraHandle hCamera,
	BOOL bEnable
	);

/// @ingroup API_DEAD_PIXEL
/// \~chinese
/// \brief 获取坏点修正使能状态
/// \param [in] hCamera 相机的句柄。
/// \param [out] pbEnable 返回使能状态
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get dead pixel correction enabled
/// \param [in] hCamera Camera handle.
/// \param [out] pbEnable Returns enable state
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetCorrectDeadPixel(
	CameraHandle hCamera,
	BOOL* pbEnable
	);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 使能平场校正
/// \param [in] hCamera 相机的句柄。
/// \param [in] bEnable     TRUE: 使能平场校正   FALSE: 关闭平场校正
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Enable flat field correction
/// \param [in] hCamera Camera handle.
/// \param [in] bEnable TRUE: Enable flat field correction FALSE: Turn off flat field correction
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraFlatFieldingCorrectSetEnable(
	CameraHandle hCamera,
	BOOL bEnable
	);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 获取平场校正使能状态
/// \param [in] hCamera 相机的句柄。
/// \param [out] pbEnable 返回使能状态
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get Plane Correction Enable Status
/// \param [in] hCamera Camera handle.
/// \param [out] pbEnable Returns enable state
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraFlatFieldingCorrectGetEnable(
	CameraHandle hCamera,
	BOOL* pbEnable
	);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 设置平场校正参数
/// \param [in] hCamera 相机的句柄。
/// \param [in] pDarkFieldingImage 暗场图片
/// \param [in] pDarkFieldingFrInfo 暗场图片信息
/// \param [in] pLightFieldingImage 明场图片
/// \param [in] pLightFieldingFrInfo 明场图片信息
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set flat field correction parameters
/// \param [in] hCamera Camera handle.
/// \param [in] pDarkFieldingImage dark field image
/// \param [in] pDarkFieldingFrInfo dark field image information
/// \param [in] pLightFieldingImage Brightfield image
/// \param [in] pLightFieldingFrInfo Brightfield image information
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraFlatFieldingCorrectSetParameter(
	CameraHandle hCamera,
	BYTE const* pDarkFieldingImage,
	tSdkFrameHead const* pDarkFieldingFrInfo,
	BYTE const* pLightFieldingImage,
	tSdkFrameHead const* pLightFieldingFrInfo
	);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 获取平场校正参数的状态
/// \param [in] hCamera 相机的句柄。
/// \param [out] pbValid 返回参数是否有效
/// \param [out] pFilePath 返回参数文件的路径
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get status of flat field correction parameters
/// \param [in] hCamera Camera handle.
/// \param [out] pbValid Return whether the parameter is valid
/// \param [out] pFilePath Returns the path of the parameter file
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraFlatFieldingCorrectGetParameterState(
	CameraHandle hCamera,
	BOOL *pbValid,
	char *pFilePath
	);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 保存平场校正参数到文件
/// \param [in] hCamera 相机的句柄。
/// \param [in] pszFileName 文件路径
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Save flat correction parameters to file
/// \param [in] hCamera Camera handle.
/// \param [in] pszFileName file path
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraFlatFieldingCorrectSaveParameterToFile(
	CameraHandle hCamera,
	char const* pszFileName
	);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 从文件中加载平场校正参数
/// \param [in] hCamera 相机的句柄。
/// \param [in] pszFileName 文件路径
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Load flat field correction parameters from file
/// \param [in] hCamera Camera handle.
/// \param [in] pszFileName file path
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraFlatFieldingCorrectLoadParameterFromFile(
	CameraHandle hCamera,
	char const* pszFileName
	);

/******************************************************/
// 函数名   : CameraCommonCall
// 功能描述 : 相机的一些特殊功能调用，二次开发时一般不需要调用。
// 参数     : hCamera   相机的句柄，由CameraInit函数获得。
//            pszCall   功能及参数
//            pszResult 调用结果，不同的pszCall时，意义不同。
//            uResultBufSize pszResult指向的缓冲区的字节大小
// 返回值   : 成功时，返回CAMERA_STATUS_SUCCESS (0);
//            否则返回非0值的错误码,请参考CameraStatus.h
//            中错误码的定义。
/******************************************************/
MVSDK_API CameraSdkStatus __stdcall CameraCommonCall(
	CameraHandle    hCamera, 
	char const*		pszCall,
	char*			pszResult,
	UINT			uResultBufSize
	);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 设置3D降噪参数
/// \param [in] hCamera 相机的句柄。
/// \param [in] bEnable  启用或禁用
/// \param [in] nCount   使用几张图片进行降噪(2-8张)
/// \param [in] Weights  降噪权重，如当使用3张图片进行降噪则这个参数可以传入3个浮点(0.3,0.3,0.4)，最后一张图片的权重大于前2张。如果不需要使用权重，则把这个参数传入0，表示所有图片的权重相同(0.33,0.33,0.33)
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set 3D noise reduction parameters
/// \param [in] hCamera Camera handle.
/// \param [in] bEnable enable or disable
/// \param [in] nCount Noise reduction using several pictures (2-8)
/// \param [in] Weights Noise reduction weight, such as when using 3 pictures for noise reduction, this parameter can be passed in 3 floating points (0.3, 0.3, 0.4). The weight of the last picture is larger than the first 2 pictures. . If you do not need to use weights, then pass this parameter to 0, indicating that all images have the same weight (0.33, 0.33, 0.33)
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetDenoise3DParams(
	CameraHandle    hCamera, 
	BOOL			bEnable,
	int				nCount,
	float			*Weights
	);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 获取当前的3D降噪参数
/// \param [in] hCamera 相机的句柄。
/// \param [out] bEnable  启用或禁用
/// \param [out] nCount   使用了几张图片进行降噪
/// \param [out] bUseWeight 是否使用了降噪权重
/// \param [out] Weights  降噪权重
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get current 3D noise reduction parameters
/// \param [in] hCamera Camera handle.
/// \param [out] bEnable enable or disable
/// \param [out] nCount uses several pictures for noise reduction
/// \param [out] bUseWeight whether to use noise reduction weights
/// \param [out] Weights Noise Reduction Weights
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetDenoise3DParams(
	CameraHandle    hCamera, 
	BOOL			*bEnable,
	int				*nCount,
	BOOL			*bUseWeight,
	float			*Weights
	);

/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 对一组帧进行一次降噪处理
/// \param [in] InFramesHead  输入帧头
/// \param [in] InFramesData  输入帧数据
/// \param [in] nCount   输入帧的数量
/// \param [in] Weights  降噪权重
/// \param [out] OutFrameHead 输出帧头
/// \param [out] OutFrameData 输出帧数据
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Perform a noise reduction on a group of frames
/// \param [in] InFramesHead input frame header
/// \param [in] InFramesData input frame data
/// \param [in] nCount Number of input frames
/// \param [in] Weights Noise Reduction Weight
/// \param [out] OutFrameHead output frame header
/// \param [out] OutFrameData output frame data
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraManualDenoise3D(
	tSdkFrameHead	*InFramesHead,
	BYTE			**InFramesData,
	int				nCount,
	float			*Weights,
	tSdkFrameHead	*OutFrameHead,
	BYTE			*OutFrameData
	);

/// @ingroup API_DEAD_PIXEL
/// \~chinese
/// \brief 打开坏点编辑面板
/// \param [in] hCamera 相机的句柄。
/// \param [in] hParent    调用该函数的窗口的句柄。可以为NULL。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Open the dead pixels editing panel
/// \param [in] hCamera Camera handle.
/// \param [in] hParent The handle of the window that called the function. Can be NULL.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraCustomizeDeadPixels(
	CameraHandle	hCamera,
	HWND			hParent
	);

/// @ingroup API_DEAD_PIXEL
/// \~chinese
/// \brief 读取相机坏点
/// \param [in] hCamera 相机的句柄。
/// \param [out] pRows 坏点y坐标
/// \param [out] pCols 坏点x坐标
/// \param [out] pNumPixel 输入时表示行列缓冲区的大小，返回时表示行列缓冲区中返回的坏点数量。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 当pRows或者pCols为NULL时函数会把相机当前的坏点个数通过pNumPixel返回
/// \~english
/// \brief Reading camera dead pixels
/// \param [in] hCamera Camera handle.
/// \param [out] pRows dead pixels y coordinates
/// \param [out] pCols bad x coordinate
/// \param [out] pNumPixel Inputs the size of the row and column buffers. When returned, it indicates the number of bad pixels returned in the row and column buffers.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note When pRows or pCols is NULL, the function will return the camera's current number of dead pixels through pNumPixel.
MVSDK_API CameraSdkStatus __stdcall CameraReadDeadPixels(
	CameraHandle    hCamera,
	USHORT*			pRows,
	USHORT*			pCols,
	UINT*			pNumPixel
	);

/// @ingroup API_DEAD_PIXEL
/// \~chinese
/// \brief 添加相机坏点
/// \param [in] hCamera 相机的句柄。
/// \param [in] pRows 坏点y坐标
/// \param [in] pCols 坏点x坐标
/// \param [in] NumPixel 行列缓冲区中的坏点个数
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Add camera dead pixels
/// \param [in] hCamera Camera handle.
/// \param [in] pRows dead point y coordinates
/// \param [in] pCols bad x coordinate
/// \param [in] NumPixel Number of dead pixels in row buffer
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraAddDeadPixels(
	CameraHandle    hCamera,
	USHORT*			pRows,
	USHORT*			pCols,
	UINT			NumPixel
	);

/// @ingroup API_DEAD_PIXEL
/// \~chinese
/// \brief 删除相机指定坏点
/// \param [in] hCamera 相机的句柄。
/// \param [in] pRows 坏点y坐标
/// \param [in] pCols 坏点x坐标
/// \param [in] NumPixel 行列缓冲区中的坏点个数
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Delete camera specified dead pixels
/// \param [in] hCamera Camera handle.
/// \param [in] pRows dead point y coordinates
/// \param [in] pCols bad x coordinate
/// \param [in] NumPixel Number of dead pixels in row buffer
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraRemoveDeadPixels(
	CameraHandle    hCamera,
	USHORT*			pRows,
	USHORT*			pCols,
	UINT			NumPixel
	);

/// @ingroup API_DEAD_PIXEL
/// \~chinese
/// \brief 删除相机的所有坏点
/// \param [in] hCamera 相机的句柄。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Remove all camera's dead pixels
/// \param [in] hCamera Camera handle.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraRemoveAllDeadPixels(
	CameraHandle    hCamera
	);

/// @ingroup API_DEAD_PIXEL
/// \~chinese
/// \brief 保存相机坏点到相机存储中
/// \param [in] hCamera 相机的句柄。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Save camera dead pixels to camera memory
/// \param [in] hCamera Camera handle.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSaveDeadPixels(
	CameraHandle    hCamera
	);

/// @ingroup API_DEAD_PIXEL
/// \~chinese
/// \brief 保存相机坏点到文件中
/// \param [in] hCamera 相机的句柄。
/// \param [in] sFileName  文件的完整路径。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Save Camera Dead Points to File
/// \param [in] hCamera Camera handle.
/// \param [in] sFileName Full path to the file.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSaveDeadPixelsToFile(
	CameraHandle    hCamera,
	char const*		sFileName
	);

/// @ingroup API_DEAD_PIXEL
/// \~chinese
/// \brief 从文件加载相机坏点
/// \param [in] hCamera 相机的句柄。
/// \param [in] sFileName  文件的完整路径。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Loading camera dead pixels from file
/// \param [in] hCamera Camera handle.
/// \param [in] sFileName Full path to the file.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraLoadDeadPixelsFromFile(
	CameraHandle    hCamera,
	char const*		sFileName
	);

/// @ingroup API_GRAB
/// \~chinese
/// \brief 获得一帧图像数据。
/// \param [in] hCamera 相机的句柄。
/// \param [out] pFrameInfo  图像的帧头信息指针。
/// \param [out] pbyBuffer   指向图像的数据的缓冲区指针。
/// \param [in] wTimes 抓取图像的超时时间。
/// \param [in] Priority 取图优先级 详见：@link #emCameraGetImagePriority @endlink
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 除了多一个优先级参数外与@link #CameraGetImageBuffer @endlink相同
/// \~english
/// \brief Get a frame of image data.
/// \param [in] hCamera Camera handle.
/// \param [out] pFrameInfo Frame header information pointer
/// \param [out] pbyBuffer Pointer to the buffer of data for the image.
/// \param [in] wTimes The time-out time for capturing images.
/// \param [in] Priority map priority See: @link #emCameraGetImagePriority @endlink
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note Same as @link #CameraGetImageBuffer @endlink except one more priority parameter
MVSDK_API CameraSdkStatus __stdcall CameraGetImageBufferPriority(
	CameraHandle        hCamera, 
	tSdkFrameHead*      pFrameInfo, 
	BYTE**              pbyBuffer,
	UINT                wTimes,
	UINT				Priority
	);

/// @ingroup API_GRAB
/// \~chinese
/// \brief 获得一帧图像数据。该接口获得的图像是经过处理后的RGB格式。
/// \param [in] hCamera 相机的句柄。
/// \param [out] piWidth    整形指针，返回图像的宽度
/// \param [out] piHeight   整形指针，返回图像的高度
/// \param [in] wTimes 抓取图像的超时时间。单位毫秒。
/// \param [in] Priority 取图优先级 详见：@link #emCameraGetImagePriority @endlink
/// \return 成功时，返回RGB数据缓冲区的首地址;否则返回0。
/// \note 除了多一个优先级参数外与@link #CameraGetImageBufferEx @endlink相同
/// \~english
/// \brief Get a frame of image data. The image obtained by this interface is the processed RGB format.
/// \param [in] hCamera Camera handle.
/// \param [out] piWidth Returns the width of the image
/// \param [out] piHeight Returns the height of the image
/// \param [in] wTimes The time-out time for capturing images. The unit is milliseconds.
/// \param [in] Priority map priority See: @link #emCameraGetImagePriority @endlink
/// \return Returns the first address of the RGB data buffer when successful; otherwise returns 0.
/// \note Same as @link #CameraGetImageBufferEx @endlink except one more priority parameter
MVSDK_API unsigned char* __stdcall CameraGetImageBufferPriorityEx(
	CameraHandle        hCamera, 
	INT*                piWidth,
	INT*                piHeight,
	UINT                wTimes,
	UINT				Priority
	);

/// @ingroup API_GRAB
/// \~chinese
/// \brief 获得一帧图像数据。该接口获得的图像是经过处理后的RGB格式。
/// \param [in] hCamera 相机的句柄。
/// \param [out] pImageData  接收图像数据的缓冲区，大小必须和uOutFormat指定的格式相匹配，否则数据会溢出
/// \param [in] uOutFormat	 输出格式 0:Mono8 1:rgb24 2:rgba32 3:bgr24 4:bgra32
/// \param [out] piWidth     整形指针，返回图像的宽度
/// \param [out] piHeight    整形指针，返回图像的高度
/// \param [in] wTimes      抓取图像的超时时间。单位毫秒。
/// \param [in] Priority 取图优先级 详见：@link #emCameraGetImagePriority @endlink
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 除了多一个优先级参数外与@link #CameraGetImageBufferEx2 @endlink相同
/// \~english
/// \brief Get a frame of image data. The image obtained by this interface is the processed RGB format.
/// \param [in] hCamera Camera handle.
/// \param [out] pImageData The buffer to receive the image data, the size must match the format specified by uOutFormat, otherwise the data will overflow
/// \param [in] uOutFormat Output Format 0:Mono8 1:rgb24 2:rgba32 3:bgr24 4:bgra32
/// \param [out] piWidth Returns the width of the image
/// \param [out] piHeight Returns the height of the image
/// \param [in] wTimes The time-out time for capturing images. The unit is milliseconds.
/// \param [in] Priority map priority See: @link #emCameraGetImagePriority @endlink
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note Same as @link #CameraGetImageBufferEx2 @endlink except one more priority parameter
MVSDK_API CameraSdkStatus __stdcall CameraGetImageBufferPriorityEx2(
	CameraHandle    hCamera, 
	BYTE*           pImageData,
	UINT            uOutFormat,
	int*            piWidth,
	int*            piHeight,
	UINT            wTimes,
	UINT			Priority
	);

/// @ingroup API_GRAB
/// \~chinese
/// \brief 获得一帧图像数据。该接口获得的图像是经过处理后的RGB格式。
/// \param [in] hCamera 相机的句柄。
/// \param [out] pImageData  接收图像数据的缓冲区，大小必须和uOutFormat指定的格式相匹配，否则数据会溢出
/// \param [in] uOutFormat	 输出格式 0:Mono8 1:rgb24 2:rgba32 3:bgr24 4:bgra32
/// \param [out] piWidth     整形指针，返回图像的宽度
/// \param [out] piHeight    整形指针，返回图像的高度
/// \param [out] puTimeStamp 返回图像时间戳 
/// \param [in] wTimes      抓取图像的超时时间。
/// \param [in] Priority 取图优先级 详见：@link #emCameraGetImagePriority @endlink
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \note 除了多一个优先级参数外与@link #CameraGetImageBufferEx3 @endlink相同
/// \~english
/// \brief Get a frame of image data. The image obtained by this interface is the processed RGB format.
/// \param [in] hCamera Camera handle.
/// \param [out] pImageData The buffer to receive the image data, the size must match the format specified by uOutFormat, otherwise the data will overflow
/// \param [in] uOutFormat output format 0:Mono8 1:rgb24 2:rgba32 3:bgr24 4:bgra32
/// \param [out] piWidth Returns the width of the image
/// \param [out] piHeight Returns the height of the image
/// \param [out] puTimeStamp returns image timestamp
/// \param [in] wTimes The time-out time for capturing images.
/// \param [in] Priority map priority See: @link #emCameraGetImagePriority @endlink
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \note Same as @link #CameraGetImageBufferEx3 @endlink except one more priority parameter
MVSDK_API CameraSdkStatus __stdcall CameraGetImageBufferPriorityEx3(
	CameraHandle hCamera, 
	BYTE*pImageData,
	UINT uOutFormat,
	int *piWidth,
	int *piHeight,
	UINT* puTimeStamp,
	UINT wTimes,
	UINT Priority
	);

/// @ingroup API_GRAB
/// \~chinese
/// \brief 清空相机内已缓存的所有帧
/// \param [in] hCamera 相机的句柄。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Clear all cached frames in the camera
/// \param [in] hCamera Camera handle.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraClearBuffer(
	CameraHandle hCamera
	);

/// @ingroup API_TRIGGER
/// \~chinese
/// \brief 执行软触发。
/// \param [in] hCamera 相机的句柄。
/// \param [in] uFlags 功能标志,详见@link #emCameraSoftTriggerExFlags @endlink中的定义
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \see CameraSoftTrigger
/// \~english
/// \brief Perform a soft trigger.
/// \param [in] hCamera Camera handle.
/// \param [in] uFlags function flags, as defined in @link #emCameraSoftTriggerExFlags @endlink
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
/// \see CameraSoftTrigger
MVSDK_API CameraSdkStatus __stdcall CameraSoftTriggerEx(
	CameraHandle hCamera,
	UINT uFlags
	);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 设置相机的HDR，需要相机支持，不带HDR功能的型号，此函数返回错误代码，表示不支持。
/// \param [in] hCamera 相机的句柄。
/// \param [in] value	HDR系数，范围0.0到1.0
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Setting the HDR of the camera requires camera support. Models without the HDR function. This function returns an error code indicating that it is not supported.
/// \param [in] hCamera Camera handle.
/// \param [in] value HDR coefficient, range 0.0 to 1.0
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetHDR(
	CameraHandle    hCamera,
	float           value
	);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 获取相机的HDR，需要相机支持，不带HDR功能的型号，此函数返回错误代码，表示不支持。
/// \param [in] hCamera 相机的句柄。
/// \param [out] value	HDR系数，范围0.0到1.0
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get camera HDR, need camera support, model without HDR function, this function returns an error code, indicating that it is not supported.
/// \param [in] hCamera Camera handle.
/// \param [out] value HDR coefficient, range 0.0 to 1.0
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetHDR(
	CameraHandle    hCamera,
	float*          value
	);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 获取当前帧的ID，需相机支持(网口全系列支持)，此函数返回错误代码，表示不支持。
/// \param [in] hCamera 相机的句柄。
/// \param [out] id		   帧ID
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief The ID of the current frame needs to be supported by the camera (supported by the full range of network ports). This function returns an error code indicating that it is not supported.
/// \param [in] hCamera Camera handle.
/// \param [out] id Frame ID
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetFrameID(
	CameraHandle    hCamera,
	UINT*           id
	);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 获取当前帧的时间戳(单位微秒)
/// \param [in] hCamera 相机的句柄。
/// \param [out] TimeStampL   时间戳低32位
/// \param [out] TimeStampH   时间戳高32位
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the timestamp of the current frame (in microseconds)
/// \param [in] hCamera Camera handle.
/// \param [out] TimeStampL timestamp low 32 bits
/// \param [out] TimeStampH Timestamp high 32 bits
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetFrameTimeStamp(
	CameraHandle    hCamera,
	UINT*           TimeStampL,
	UINT*			TimeStampH
	);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 设置相机的增益模式，需要相机支持，不带增益模式切换功能的型号，此函数返回错误代码，表示不支持。
/// \param [in] hCamera 相机的句柄。
/// \param [in] value		   0：低增益    1：高增益
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Setting the camera's gain mode requires camera support. Models without the gain mode switching function. This function returns an error code indicating that it is not supported.
/// \param [in] hCamera Camera handle.
/// \param [in] value 0: low gain 1: high gain
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetHDRGainMode(
	CameraHandle    hCamera,
	int				value
	);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 获取相机的增益模式，需要相机支持，不带增益模式切换功能的型号，此函数返回错误代码，表示不支持。
/// \param [in] hCamera 相机的句柄。
/// \param [out] value	0：低增益    1：高增益
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get camera's gain mode, need camera support, model without gain mode switching function, this function returns error code, indicating that it is not supported.
/// \param [in] hCamera Camera handle.
/// \param [out] value 0: low gain 1: high gain
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetHDRGainMode(
	CameraHandle    hCamera,
	int*			value
	);

/// @ingroup API_UTIL
/// \~chinese
/// \brief 从帧数据创建HBITMAP
/// \param [in] hDC Handle to a device context（WIN32 API CreateDIBitmap的参数hdc）
/// \param [in] pFrameBuffer 帧数据
/// \param [in] pFrameHead 帧头
/// \param [out] outBitmap 新创建的HBITMAP（使用完后需要调用WIN32 API DeleteObject释放）
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Create HBITMAP from Frame Data
/// \param [in] hDC Handle to a device context (parameter hdc of WIN32 API CreateDIBitmap)
/// \param [in] pFrameBuffer Frame data
/// \param [in] pFrameHead Frame Header
/// \param [out] outBitmap newly created HBITMAP (need to call WIN32 API DeleteObject after use)
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraCreateDIBitmap(
	HDC hDC, 
	BYTE *pFrameBuffer, 
	tSdkFrameHead* pFrameHead,
	HBITMAP* outBitmap
	);

/// @ingroup API_UTIL
/// \~chinese
/// \brief 绘制帧到指定窗口
/// \param [in] pFrameBuffer 帧数据
/// \param [in] pFrameHead 帧头
/// \param [in] hWnd 目的窗口
/// \param [in] Algorithm 缩放算法  0：快速但质量稍差  1：速度慢但质量好
/// \param [in] Mode 缩放模式   0: 等比缩放  1：拉伸缩放
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Draw frames to the specified window
/// \param [in] pFrameBuffer frame data
/// \param [in] pFrameHead Frame Header
/// \param [in] hWnd destination window
/// \param [in] Algorithm scaling algorithm 0: fast but slightly worse quality 1 slower but better quality
/// \param [in] Mode Zoom Mode 0: Scale 1: Scale Zoom
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraDrawFrameBuffer(
	BYTE *pFrameBuffer, 
	tSdkFrameHead* pFrameHead,
	HWND hWnd,
	int Algorithm,
	int Mode
	);

/// @ingroup API_UTIL
/// \~chinese
/// \brief 翻转帧数据
/// \param [inout] pFrameBuffer 帧数据
/// \param [in] pFrameHead 帧头
/// \param [in] Flags 1:上下   2：左右    3：上下、左右皆做一次翻转(相当于旋转180度)
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Flip frame data
/// \param [inout] pFrameBuffer frame data
/// \param [in] pFrameHead Frame Header
/// \param [in] Flags 1: Up and down 2: Around 3: Up and down, left and right are all flipped (equivalent to 180 degrees rotation)
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraFlipFrameBuffer(
	BYTE *pFrameBuffer, 
	tSdkFrameHead* pFrameHead,
	int Flags
	);

/// @ingroup API_UTIL
/// \~chinese
/// \brief 转换帧数据格式
/// \param [in] hCamera 相机的句柄。
/// \param [in] pInFrameBuffer 输入帧数据
/// \param [out] pOutFrameBuffer 输出帧数据
/// \param [in] outWidth 输出宽度
/// \param [in] outHeight 输出高度
/// \param [in] outMediaType 输出格式 @see CameraSetIspOutFormat
/// \param [inout] pFrameHead 帧头信息（转换成功后，里面的信息会被修改为输出帧的信息）
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Conversion frame data format
/// \param [in] hCamera Camera handle.
/// \param [in] pInFrameBuffer input frame data
/// \param [out] pOutFrameBuffer output frame data
/// \param [in] outWidth output width
/// \param [in] outHeight output height
/// \param [in] outMediaType output format @see CameraSetIspOutFormat
/// \param [inout] pFrameHead frame header information (after successful conversion, the information inside will be modified to output frame information)
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraConvertFrameBufferFormat(
	CameraHandle hCamera,
	BYTE *pInFrameBuffer, 
	BYTE *pOutFrameBuffer, 
	int outWidth,
	int outHeight,
	UINT outMediaType,
	tSdkFrameHead* pFrameHead
	);

/// @ingroup API_RECONNECT
/// \~chinese
/// \brief 设置相机连接状态改变的回调通知函数。当相机掉线、重连时，pCallBack所指向的回调函数就会被调用。 
/// \param [in] hCamera 相机的句柄。
/// \param [in] pCallBack 回调函数指针。
/// \param [in] pContext  回调函数的附加参数，在回调函数被调用时该附加参数会被传入，可以为NULL。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Sets the callback notification function for camera connection state changes. When the camera is disconnected and reconnected, the callback function pointed to by pCallBack will be called.
/// \param [in] hCamera Camera handle.
/// \param [in] pCallBack callback function pointer.
/// \param [in] pContext Additional parameter of the callback function. This additional parameter will be passed in when the callback function is called. It can be NULL.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetConnectionStatusCallback(
	CameraHandle        hCamera,
	CAMERA_CONNECTION_STATUS_CALLBACK pCallBack,
	PVOID               pContext
	);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 设置光源控制器的输出模式（智能相机系列且需要硬件支持）
/// \param [in] hCamera 相机的句柄。
/// \param [in] index 控制器索引
/// \param [in] mode 输出模式（0:跟随闪光灯 1:手动）
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set the output mode of the light controller (Smart camera series and hardware support required)
/// \param [in] hCamera Camera handle.
/// \param [in] index controller index
/// \param [in] mode output mode (0: follow strobe 1: manual)
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetLightingControllerMode(
	CameraHandle        hCamera,
	int					index,
	int					mode
	);

/// @ingroup API_ADVANCE
/// \~chinese
/// \brief 设置光源控制器的输出状态（智能相机系列且需要硬件支持）
/// \param [in] hCamera 相机的句柄。
/// \param [in] index 控制器索引
/// \param [in] state 输出状态（0:关闭  1：打开）
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Set the output status of the light controller (Smart camera series and hardware support required)
/// \param [in] hCamera Camera handle.
/// \param [in] index controller index
/// \param [in] state output state (0: off 1: on)
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraSetLightingControllerState(
	CameraHandle        hCamera,
	int					index,
	int					state
	);

/// @ingroup API_MULTI_EYE
/// \~chinese
/// \brief 获取多目相机的目数
/// \param [in] hCamera 相机的句柄。
/// \param [out] EyeCount 目数
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Get the number of eyes in the camera
/// \param [in] hCamera Camera handle.
/// \param [out] EyeCount eye count
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraGetEyeCount(
	CameraHandle        hCamera,
	int*				EyeCount
	);

/// @ingroup API_MULTI_EYE
/// \~chinese
/// \brief 对多目相机帧内的某个单目图做ISP
/// \param [in] hCamera 相机的句柄。
/// \param [in] iEyeIndex 单目索引。
/// \param [in] pbyIn 输入图像数据的缓冲区地址，不能为NULL。 
/// \param [in] pInFrInfo 输入图像数据的帧头，不能为NULL。 
/// \param [out] pbyOut 处理后图像输出的缓冲区地址，不能为NULL。
/// \param [out] pOutFrInfo 处理后图像的帧头信息，不能为NULL。 
/// \param [in] uOutFormat 处理完后图像的输出格式。
/// \param [in] uReserved 预留参数，必须设置为0。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。否则返回非0值的错误码, 请参考 CameraStatus.h 中错误码的定义。
/// \~english
/// \brief Do ISP for a certain monocular in the multi-camera frame.
/// \param [in] hCamera Camera handle.
/// \param [in] iEyeIndex eye index.
/// \param [in] pbyIn Input the buffer address of the image data, which cannot be NULL.
/// \param [in] pInFrInfo Input the frame header of the image data, which cannot be NULL.
/// \param [out] pbyOut The buffer address of the image output after processing, cannot be NULL.
/// \param [out] pOutFrInfo The header information of the processed image cannot be NULL.
/// \param [in] uOutFormat The output format of the image after processing.
/// \param [in] uReserved Reservation parameters must be set to 0.
/// \return Returns CAMERA_STATUS_SUCCESS(0) successfully. Otherwise, it returns a non-zero error code. Please refer to the definition of the error code in CameraStatus.h.
MVSDK_API CameraSdkStatus __stdcall CameraMultiEyeImageProcess(
	CameraHandle        hCamera, 
	int					iEyeIndex,
	BYTE*               pbyIn, 
	tSdkFrameHead*		pInFrInfo,
	BYTE*               pbyOut,
	tSdkFrameHead*      pOutFrInfo,
	UINT                uOutFormat,
	UINT                uReserved
	);

#endif
