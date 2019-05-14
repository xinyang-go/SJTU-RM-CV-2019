#pragma once
#ifndef _CAMERA_DEFINE_H_
#define _CAMERA_DEFINE_H_

#include "CameraStatus.h"

#define MAX_CROSS_LINE 9

/// @ingroup MV_TYPEDEF
/// \~chinese 相机的句柄类型定义
/// \~english Camera handle type definition
typedef int CameraHandle;



/// @ingroup MV_ENUM_TYPE
/// \~chinese 图像查表变换的方式
/// \~english Image lookup table transformation
typedef enum
{
    LUTMODE_PARAM_GEN=0, ///< \~chinese 通过调节参数动态生成LUT表。	\~english Dynamically generate LUT tables by adjusting parameters. 
    LUTMODE_PRESET=1,    ///< \~chinese 使用预设的LUT表				\~english Use a preset LUT table
    LUTMODE_USER_DEF=2	 ///< \~chinese 使用用户自定义的LUT表			\~english Use a user-defined LUT table
}emSdkLutMode;

/// @ingroup MV_ENUM_TYPE
/// \~chinese 相机的视频流控制
/// \~english Camera video flow control
typedef enum
{
	/// \~chinese 正常预览，捕获到图像就显示。（如果相机处于触发模式，则会等待触发帧的到来）
	/// \~english Normal preview, the captured image is displayed. (If the camera is in trigger mode, it will wait for the arrival of the trigger frame)
    RUNMODE_PLAY=0,
    RUNMODE_PAUSE=1,     ///< \~chinese 暂停，会暂停相机的图像输出，同时也不会去捕获图像	\~english Pause, will pause the camera's image output, and will not capture the image.
    RUNMODE_STOP=2       ///< \~chinese 停止相机工作。反初始化后，相机就处于停止模式		\~english Stop the camera. Camera is in stop mode after deinitialization.
}emSdkRunMode;

/// @ingroup MV_ENUM_TYPE
/// \~chinese SDK内部显示接口的显示方式
/// \~english How to display the internal display interface of the SDK
typedef enum
{
    DISPLAYMODE_SCALE=0, ///< \~chinese 缩放显示模式，缩放到显示控件的尺寸 \~english Zoom the display mode, zoom to the size of the display control
    DISPLAYMODE_REAL=1,  ///< \~chinese 1:1显示模式，当图像尺寸大于显示控件的尺寸时，只显示局部  \~english 1:1 display mode, when the image size is larger than the size of the display control, only the local display
	DISPLAYMODE_2X=2,	 ///< \~chinese 放大2X	\~english Zoom in 2X
	DISPLAYMODE_4X=3,	 ///< \~chinese 放大4X	\~english Zoom in 4X
	DISPLAYMODE_8X=4,    ///< \~chinese 放大8X	\~english Zoom in 8X
	DISPLAYMODE_16X=5	 ///< \~chinese 放大16X	\~english Zoom in 16X
}emSdkDisplayMode;

/// @ingroup MV_ENUM_TYPE
/// \~chinese 录像状态
/// \~english Recording status
typedef enum 
{
  RECORD_STOP=0,	///< \~chinese 停止		\~english Stop
  RECORD_START=1,   ///< \~chinese 录像中	\~english Start
  RECORD_PAUSE=2    ///< \~chinese 暂停		\~english Pause
}emSdkRecordMode;

/// @ingroup MV_ENUM_TYPE
/// \~chinese 图像的镜像操作
/// \~english Image mirroring operation
typedef enum
{
    MIRROR_DIRECTION_HORIZONTAL=0,		///< \~chinese 水平镜像	\~english Horizontal mirroring
    MIRROR_DIRECTION_VERTICAL=1			///< \~chinese 垂直镜像	\~english Vertical mirroring
}emSdkMirrorDirection;

/// @ingroup MV_ENUM_TYPE
/// \~chinese 图像的旋转操作
/// \~english Rotation of the image
typedef enum
{
	ROTATE_DIRECTION_0=0,		///< \~chinese 不旋转		\~english Do not rotate
	ROTATE_DIRECTION_90=1,		///< \~chinese 逆时针90度	\~english Counterclockwise 90 degrees
	ROTATE_DIRECTION_180=2,		///< \~chinese 逆时针180度	\~english Counterclockwise 180 degrees
	ROTATE_DIRECTION_270=3,		///< \~chinese 逆时针270度	\~english Counterclockwise 270 degrees
}emSdkRotateDirection;

/// @ingroup MV_ENUM_TYPE
/// \~chinese 相机视频的帧率
/// \~english Camera video frame rate
typedef enum
{
    FRAME_SPEED_LOW=0,		///< \~chinese 低速模式	\~english Low Speed
    FRAME_SPEED_NORMAL=1,   ///< \~chinese 普通模式	\~english Normal Speed
    FRAME_SPEED_HIGH=2,     ///< \~chinese 高速模式(需要较高的传输带宽,多设备共享传输带宽时会对帧率的稳定性有影响)	\~english High Speed
    FRAME_SPEED_SUPER=3     ///< \~chinese 超高速模式(需要较高的传输带宽,多设备共享传输带宽时会对帧率的稳定性有影响)	\~english Super Speed
}emSdkFrameSpeed;

/// @ingroup MV_ENUM_TYPE
/// \~chinese 保存文件的格式类型
/// \~english Save file format type
typedef enum
{
    FILE_JPG = 1,	///< \~chinese JPG				\~english JPG
    FILE_BMP = 2,	///< \~chinese BMP 24bit		\~english BMP 24bit
    FILE_RAW = 4,	///< \~chinese RAW				\~english RAW
    FILE_PNG = 8,	///< \~chinese PNG 24bit		\~english PNG 24bit
    FILE_BMP_8BIT = 16,	///< \~chinese BMP 8bit		\~english BMP 8bit
    FILE_PNG_8BIT = 32, ///< \~chinese PNG 8bit		\~english PNG 8bit
	FILE_RAW_16BIT = 64	///< \~chinese RAW 16bit	\~english RAW 16bit
}emSdkFileType;

/// @ingroup MV_ENUM_TYPE
/// \~chinese 相机中的图像传感器的工作模式
/// \~english Image Sensor Operation Mode in Camera
typedef enum 
{
	/// \~chinese 连续采集模式
	/// \~english Continuous acquisition mode
    CONTINUATION=0,

	/// \~chinese 软件触发模式，由软件发送指令后，传感器开始采集指定帧数的图像，采集完成后，停止输出
	/// \~english Software trigger mode. After the software sends the instruction, the sensor starts to capture the image of the specified frame number. After the acquisition is completed, the output is stopped.
    SOFT_TRIGGER=1,

	/// \~chinese 硬件触发模式，当接收到外部信号，传感器开始采集指定帧数的图像，采集完成后，停止输出
	/// \~english In the hardware trigger mode, when receiving an external signal, the sensor starts to capture the image of the specified frame number. After the acquisition is completed, the output is stopped.
    EXTERNAL_TRIGGER=2
} emSdkSnapMode;

/// @ingroup MV_ENUM_TYPE
/// \~chinese 自动曝光时抗频闪的频率
/// \~english Anti-strobe frequency at auto exposure
typedef enum
{
	/// \~chinese 50HZ,一般的灯光都是50HZ
	/// \~english 50HZ, the general lighting is 50HZ
    LIGHT_FREQUENCY_50HZ=0,

	/// \~chinese 60HZ,主要是指显示器的
	/// \~english 60HZ, mainly refers to the monitor
    LIGHT_FREQUENCY_60HZ=1
}emSdkLightFrequency;

/// @ingroup MV_ENUM_TYPE
/// \~chinese 相机的配置参数，分为A,B,C,D 4组进行保存。
/// \~english The camera configuration parameters are divided into groups A, B, C, and D for preservation.
typedef enum
{
	PARAMETER_TEAM_DEFAULT = 0xff,	///< \~chinese 默认参数 \~english Default parameters
    PARAMETER_TEAM_A = 0,	///< \~chinese 参数A \~english parametersA
    PARAMETER_TEAM_B = 1,	///< \~chinese 参数B \~english parametersB
    PARAMETER_TEAM_C = 2,	///< \~chinese 参数C \~english parametersC
    PARAMETER_TEAM_D = 3	///< \~chinese 参数D \~english parametersD
}emSdkParameterTeam;


/// @ingroup MV_ENUM_TYPE
/// \~chinese
/// \brief 相机参数加载模式
/// \note 您可以根据自己的使用环境，灵活使用以上几种方式加载参数。例如，以
/// \note MV-U300为例，您希望多台该型号的相机在您的 电脑上都共用4组参数，那么就
/// \note 使用PARAM_MODE_BY_MODEL方式;如果您希望其中某一台或者某几台MV-U300能
/// \note 使用自己参数文件而其余的MV-U300又要使用相同的参数文件，那么使用
/// \note PARAM_MODE_BY_NAME方式;如果您希望每台MV-U300都使用不同的参数文件，那么
/// \note 使用PARAM_MODE_BY_SN方式。
/// \note 参数文件存在安装目录的 \\Camera\\Configs 目录下，以config为后缀名的文件。
/// \~english
/// \brief Camera parameter loading mode
/// \note You can use the above several ways to load parameters according to your own environment. For example, with
/// \note MV-U300 as an example, you want multiple cameras of this model to share 4 sets of parameters on your computer.
/// \note Use the PARAM_MODE_BY_MODEL method; if you want one or more of the MV-U300s
/// \note Use your own parameter file and the rest of the MV-U300 use the same parameter file again, then use
/// \note PARAM_MODE_BY_NAME way; if you want each MV-U300 to use a different parameter file, then
/// \note Use the PARAM_MODE_BY_SN method.
/// \note The parameter file exists in the \\Camera\\Configs directory of the installation directory, with a config extension file.
typedef enum 
{
	/// \~chinese 根据相机型号名从文件中加载参数，例如MV-U300
	/// \note 所有同型号的相机共用ABCD四组参数文件。修改一台相机的参数文件，会影响到整个同型号的相机参数加载。
	/// \~english Load parameters from a file based on the camera model name, such as the MV-U300
	/// \note All ABCD four-group parameter files are shared by all cameras of the same model. Modifying a camera's parameter file will affect the entire camera model parameter loading.
	PARAM_MODE_BY_MODEL=0,

	/// \~chinese 根据设备昵称(tSdkCameraDevInfo.acFriendlyName)从文件中加载参数，例如MV-U300,该昵称可自定义
	/// \note 所有设备名相同的相机，共用ABCD四组参数文件。
	/// \note 默认情况下，当电脑上只接了某型号一台相机时，
	/// \note 设备名都是一样的，而您希望某一台相机能够加载
	/// \note 不同的参数文件，则可以通过修改其设备名的方式
	/// \note 来让其加载指定的参数文件。
	/// \~english Load parameters from a file based on device nickname (tSdkCameraDevInfo.acFriendlyName), such as MV-U300, which can be customized
	/// \note All cameras with the same device name share the four ABCD parameter files.
	/// \note By default, when only one model of a camera is connected to the computer,
	/// \note The device name is the same, and you want a camera to load
	/// \note different parameter files, you can modify the device name
	/// \note to have it load the specified parameter file.
	PARAM_MODE_BY_NAME=1,

	/// \~chinese 根据设备的唯一序列号从文件中加载参数，序列号在出厂时已经写入设备，每台相机拥有不同的序列号。
	/// \note 相机按照自己的唯一序列号来加载ABCD四组参数文件，
	/// \note 序列号在出厂时已经固化在相机内，每台相机的序列号
	/// \note 都不相同，通过这种方式，每台相机的参数文件都是独立的。
	/// \~english The parameters are loaded from the file according to the unique serial number of the device. The serial number is already written to the device at the factory and each camera has a different serial number.
	/// \note The camera loads ABCD four sets of parameter files according to their unique serial number.
	/// \note The serial number has been fixed in the camera at the factory, the serial number of each camera
	/// \note is not the same. In this way, the parameter files for each camera are independent.
	PARAM_MODE_BY_SN=2,

	/// \~chinese 从设备的固态存储器中加载参数。不是所有的型号都支持从相机中读写参数组，由tSdkCameraCapbility.bParamInDevice决定
	/// \~english Load parameters from the device's solid-state memory. Not all models support reading and writing parameters from the camera, as determined by tSdkCameraCapbility.bParamInDevice
	PARAM_MODE_IN_DEVICE=3      
}emSdkParameterMode;

/// @ingroup MV_ENUM_TYPE
/// \~chinese SDK生成的相机配置页面掩码值
/// \~english SDK generated camera configuration page mask values
typedef enum 
{
  PROP_SHEET_INDEX_EXPOSURE=0,			///< \~chinese 曝光设置 \~english Exposure Settings
  PROP_SHEET_INDEX_ISP_COLOR=1,			///< \~chinese 颜色矩阵设置 \~english Color Matrix Settings
  PROP_SHEET_INDEX_ISP_LUT=2,			///< \~chinese LUT设置 \~english LUT setting
  PROP_SHEET_INDEX_ISP_SHAPE=3,			///< \~chinese 变换设置 \~english transform settings
  PROP_SHEET_INDEX_VIDEO_FORMAT=4,		///< \~chinese 格式设置 \~english Formatting
  PROP_SHEET_INDEX_RESOLUTION=5,		///< \~chinese 分辨率设置 \~english resolution setting
  PROP_SHEET_INDEX_IO_CTRL=6,			///< \~chinese IO控制 \~english IO control
  PROP_SHEET_INDEX_TRIGGER_SET=7,		///< \~chinese 触发模式 \~english trigger setting
  PROP_SHEET_INDEX_OVERLAY=8,			///< \~chinese 十字线 \~english Crosshair
  PROP_SHEET_INDEX_DEVICE_INFO=9,		///< \~chinese 设备信息 \~english Device Information
  PROP_SHEET_INDEX_WDR=10				///< \~chinese 宽动态 \~english Wide Dynamic
}emSdkPropSheetMask;

/// @ingroup MV_ENUM_TYPE
/// \~chinese SDK生成的相机配置页面的回调消息类型
/// \~english SDK callback camera configuration page callback message type
typedef enum 
{
  SHEET_MSG_LOAD_PARAM_DEFAULT=0,	///< \~chinese 参数被恢复成默认后，触发该消息 \~english After the parameter is restored to the default, the message is triggered
  SHEET_MSG_LOAD_PARAM_GROUP=1,     ///< \~chinese 加载指定参数组，触发该消息 \~english Load the specified parameter group and trigger the message
  SHEET_MSG_LOAD_PARAM_FROMFILE=2,  ///< \~chinese 从指定文件加载参数后，触发该消息 \~english Fires the message after loading parameters from the specified file
  SHEET_MSG_SAVE_PARAM_GROUP=3      ///< \~chinese 当前参数组被保存时，触发该消息 \~english Trigger this message when the current parameter group is saved
}emSdkPropSheetMsg;

/// @ingroup MV_ENUM_TYPE
/// \~chinese 可视化选择参考窗口的类型
/// \~english Visualize the type of reference window
typedef enum 
{
  REF_WIN_AUTO_EXPOSURE=0,	///< \~chinese 自动曝光窗口 \~english Automatic exposure window
  REF_WIN_WHITE_BALANCE=1,	///< \~chinese 白平衡窗口 \~english White balance window
}emSdkRefWinType;

/// @ingroup MV_ENUM_TYPE
/// \~chinese 可视化选择参考窗口的类型
/// \~english Visualize the type of reference window
typedef enum 
{
  RES_MODE_PREVIEW=0,	///< \~chinese 预览 \~english Preview
  RES_MODE_SNAPSHOT=1,	///< \~chinese 抓拍 \~english Snapshot
}emSdkResolutionMode;

/// @ingroup MV_ENUM_TYPE
/// \~chinese 白平衡时色温模式
/// \~english White balance color temperature mode
typedef enum 
{
  CT_MODE_AUTO=0,		///< \~chinese 自动识别色温 \~english Automatically recognize color temperature
  CT_MODE_PRESET=1,		///< \~chinese 使用指定的预设色温 \~english Use the specified preset color temperature
  CT_MODE_USER_DEF=2	///< \~chinese 自定义色温(增益和矩阵) \~english Custom color temperature (gain and matrix)
}emSdkClrTmpMode;

/// @ingroup MV_ENUM_TYPE
/// \~chinese LUT的颜色通道
/// \~english LUT color channel
typedef enum 
{
  LUT_CHANNEL_ALL=0,	///< \~chinese R,B,G三通道同时调节 \~english R, B, G simultaneous adjustment of three channels
  LUT_CHANNEL_RED=1,	///< \~chinese 红色通道 \~english Red channel
  LUT_CHANNEL_GREEN=2,	///< \~chinese 绿色通道 \~english Green channel
  LUT_CHANNEL_BLUE=3,	///< \~chinese 蓝色通道 \~english Blue channel
}emSdkLutChannel;

/// @ingroup MV_ENUM_TYPE
/// \~chinese ISP处理单元
/// \~english ISP processing unit
typedef enum 
{
  ISP_PROCESSSOR_PC=0,		///< \~chinese 使用PC的软件ISP模块 \~english Use software ISP module of PC
  ISP_PROCESSSOR_DEVICE=1	///< \~chinese 使用相机自带的硬件ISP模块 \~english Use the camera's own hardware ISP module
}emSdkIspProcessor;

/// @ingroup MV_ENUM_TYPE
/// \~chinese 闪光灯信号控制方式
/// \~english Strobe signal control method
typedef enum 
{
  STROBE_SYNC_WITH_TRIG_AUTO=0,		///< \~chinese 和触发信号同步，触发后，相机进行曝光时，自动生成STROBE信号。此时，有效极性可设置(@link #CameraSetStrobePolarity @endlink)。 \~english Synchronized with the trigger signal, the STROBE signal is automatically generated when the camera performs exposure. At this point, the effective polarity can be set (@link #CameraSetStrobePolarity @endlink).
  STROBE_SYNC_WITH_TRIG_MANUAL=1,   ///< \~chinese 和触发信号同步，触发后，STROBE延时指定的时间后(@link #CameraSetStrobeDelayTime @endlink)，再持续指定时间的脉冲(@link #CameraSetStrobePulseWidth @endlink)，有效极性可设置(@link #CameraSetStrobePolarity @endlink)。 \~english Synchronized with the trigger signal. After the trigger, STROBE is delayed by the specified time (@link #CameraSetStrobeDelayTime @endlink) and continues for the specified time (@link #CameraSetStrobePulseWidth @endlink). The effective polarity can be set (@link #CameraSetStrobePolarity @endlink).
  STROBE_ALWAYS_HIGH=2,             ///< \~chinese 始终为高，忽略STROBE信号的其他设置 \~english Always high, ignoring other settings of the STROBE signal
  STROBE_ALWAYS_LOW=3               ///< \~chinese 始终为低，忽略STROBE信号的其他设置 \~english Always low, ignoring other settings of the STROBE signal
}emStrobeControl;

/// @ingroup MV_ENUM_TYPE
/// \~chinese 硬件外触发的信号种类
/// \~english Signal types triggered by hardware
typedef enum 
{
	EXT_TRIG_LEADING_EDGE=0,		///< \~chinese 上升沿触发，默认为该方式 \~english	Rising edge trigger, default is this method
	EXT_TRIG_TRAILING_EDGE=1,		///< \~chinese 下降沿触发 \~english	Falling edge trigger
	EXT_TRIG_HIGH_LEVEL=2,			///< \~chinese 高电平触发,电平宽度决定曝光时间，仅部分型号的相机支持电平触发方式。 \~english The high level triggers, the level width determines the exposure time, only some models of cameras support level triggering.
	EXT_TRIG_LOW_LEVEL=3,			///< \~chinese 低电平触发 \~english	Low level trigger
	EXT_TRIG_DOUBLE_EDGE=4,			///< \~chinese 双边沿触发 \~english	Bilateral trigger
}emExtTrigSignal;

/// @ingroup MV_ENUM_TYPE
/// \~chinese 硬件外触发时的快门方式
/// \~english Shutter mode when triggered by hardware
typedef enum 
{
  EXT_TRIG_EXP_STANDARD=0,			///< \~chinese 标准方式，默认为该方式。 \~english	Standard mode, the default is this mode.
  EXT_TRIG_EXP_GRR=1,				///< \~chinese 全局复位方式，部分滚动快门的CMOS型号的相机支持该方式，配合外部机械快门，可以达到全局快门的效果，适合拍高速运动的物体 \~english Global reset mode, part of the rolling shutter CMOS model camera supports this method, with the external mechanical shutter, you can achieve the effect of a global shutter, suitable for shooting high-speed objects
}emExtTrigShutterMode;

/// @ingroup MV_ENUM_TYPE
/// \~chinese 清晰度评估算法
/// \~english Sharpness assessment algorithm
typedef enum
{
	EVALUATE_DEFINITION_DEVIATION=0,	///< \~chinese 方差法 \~english	Variance method
	EVALUATE_DEFINITION_SMD=1,			///< \~chinese 相邻像素灰度方差法 \~english Adjacent Pixel Gray Difference Method
	EVALUATE_DEFINITION_GRADIENT=2,		///< \~chinese 梯度统计 \~english Gradient statistics
	EVALUATE_DEFINITION_SOBEL=3,		///< \~chinese Sobel \~english Sobel
	EVALUATE_DEFINITION_ROBERT=4,		///< \~chinese Robert \~english Robert
	EVALUATE_DEFINITION_LAPLACE=5,		///< \~chinese Laplace \~english Laplace

	EVALUATE_DEFINITION_ALG_MAX=6,		///< \~chinese 算法个数 \~english The number of algorithms
}emEvaluateDefinitionAlgorith;

/// @ingroup MV_ENUM_TYPE
/// \~chinese 文字输出标志
/// \~english Text output flag
typedef enum
{
	CAMERA_DT_VCENTER		= 0x1,		///< \~chinese 垂直居中 \~english Vertically centered
	CAMERA_DT_BOTTOM		= 0x2,		///< \~chinese 底部对齐 \~english Bottom alignment
	CAMERA_DT_HCENTER		= 0x4,		///< \~chinese 水平居中 \~english Horizontally centered
	CAMERA_DT_RIGHT			= 0x8,		///< \~chinese 右对齐 \~english	Right alignment
	CAMERA_DT_SINGLELINE	= 0x10,		///< \~chinese 单行显示 \~english Single-line display
	CAMERA_DT_ALPHA_BLEND	= 0x20,		///< \~chinese Alpha混合 \~english Alpha blend
	CAMERA_DT_ANTI_ALIASING = 0x40,		///< \~chinese 抗锯齿 \~english	Anti-aliasing
}emCameraDrawTextFlags;

/// @ingroup MV_ENUM_TYPE
/// \~chinese GPIO模式
/// \~english GPIO Mode
typedef enum 
{
	IOMODE_TRIG_INPUT=0,		///< \~chinese 触发输入 \~english Trigger input
	IOMODE_STROBE_OUTPUT=1,		///< \~chinese 闪光灯输出 \~english	Strobe output
	IOMODE_GP_INPUT=2,			///< \~chinese 通用型输入 \~english	Universal input
	IOMODE_GP_OUTPUT=3,			///< \~chinese 通用型输出 \~english	Universal output
	IOMODE_PWM_OUTPUT=4,		///< \~chinese PWM型输出 \~english	PWM output
}emCameraGPIOMode;

/// @ingroup MV_ENUM_TYPE
/// \~chinese 取图优先级
/// \~english Get Image priority
typedef enum
{
	CAMERA_GET_IMAGE_PRIORITY_OLDEST=0,		///< \~chinese 获取缓存中最旧的一帧 \~english	Get the oldest frame in the cache
	CAMERA_GET_IMAGE_PRIORITY_NEWEST=1,		///< \~chinese 获取缓存中最新的一帧（比此帧旧的将全部丢弃） \~english Get the latest frame in the cache (older than this frame will be discarded)

	/// \~chinese 丢弃缓存中的所有帧，并且如果此刻相机正在曝光或传输将会被立即打断，等待接收下一帧
	/// \note 某些型号的相机不支持此功能，对于不支持此功能的相机这个标志相当于@link #CAMERA_GET_IMAGE_PRIORITY_OLDEST @endlink
	/// \~english All frames in the cache are discarded, and if the camera is now being exposed or transmitted it will be immediately interrupted, waiting to receive the next frame
	/// \note Some models do not support this feature. For cameras that do not support this feature this flag is equivalent to @link #CAMERA_GET_IMAGE_PRIORITY_OLDEST @endlink
	CAMERA_GET_IMAGE_PRIORITY_NEXT=2,
}emCameraGetImagePriority;

/// @ingroup MV_ENUM_TYPE
/// \~chinese 软触发功能标志
/// \~english Soft trigger function flag
typedef enum
{
	CAMERA_ST_CLEAR_BUFFER_BEFORE	= 0x1,	///< \~chinese 在软触发之前先清空相机已缓存的帧 \~english Empty camera-cached frames before soft triggering
}emCameraSoftTriggerExFlags;

/// \~chinese 相机的设备信息
/// \~english Camera device information
typedef struct
{
    char acProductSeries[32];	///< \~chinese 产品系列 \~english Product Series
    char acProductName[32];		///< \~chinese 产品名称 \~english product name

	/// \~chinese 产品昵称，用户可自定义改昵称，保存在相机内，用于区分多个相机同时使用,可以用@link #CameraSetFriendlyName @endlink接口改变该昵称，设备重启后生效。 
	/// \~english Product nicknames, users can customize the nickname, saved in the camera, used to distinguish between multiple cameras at the same time, you can use the @link #CameraSetFriendlyName @endlink interface to change the nickname, the device takes effect after restart.
    char acFriendlyName[32];
    char acLinkName[32];		///< \~chinese 内核符号连接名，内部使用 \~english	Kernel symbolic connection name, internal use
    char acDriverVersion[32];	///< \~chinese 驱动版本 \~english Driver version
    char acSensorType[32];		///< \~chinese sensor类型 \~english	Sensor type
    char acPortType[32];		///< \~chinese 接口类型 \~english Interface Type
    char acSn[32];				///< \~chinese 产品唯一序列号 \~english Product unique serial number
    UINT uInstance;				///< \~chinese 该型号相机在该电脑上的实例索引号，用于区分同型号多相机 \~english The example index number of this model camera on this computer, used to distinguish the same model multiple cameras
} tSdkCameraDevInfo;

/// @ingroup MV_MACRO_TYPE 
/// @{
#define EXT_TRIG_MASK_GRR_SHUTTER  1	///< \~chinese 快门支持GRR模式 \~english Shutter supports GRR mode
#define EXT_TRIG_MASK_LEVEL_MODE   2	///< \~chinese 支持电平触发 \~english Support level trigger
#define EXT_TRIG_MASK_DOUBLE_EDGE  4	///< \~chinese 支持双边沿触发 \~english Supports bilateral triggering

//tSdkResolutionRange结构体中SKIP、 BIN、RESAMPLE模式的掩码值
#define MASK_2X2_HD     (1<<0)    //硬件SKIP、BIN、重采样 2X2
#define MASK_3X3_HD     (1<<1)
#define MASK_4X4_HD     (1<<2)
#define MASK_5X5_HD     (1<<3)
#define MASK_6X6_HD     (1<<4)
#define MASK_7X7_HD     (1<<5)
#define MASK_8X8_HD     (1<<6)
#define MASK_9X9_HD     (1<<7)      
#define MASK_10X10_HD   (1<<8)
#define MASK_11X11_HD   (1<<9)
#define MASK_12X12_HD   (1<<10)
#define MASK_13X13_HD   (1<<11)
#define MASK_14X14_HD   (1<<12)
#define MASK_15X15_HD   (1<<13)
#define MASK_16X16_HD   (1<<14)
#define MASK_17X17_HD   (1<<15)
#define MASK_2X2_SW     (1<<16)   //软件SKIP、BIN、重采样 2X2
#define MASK_3X3_SW     (1<<17)
#define MASK_4X4_SW     (1<<18)
#define MASK_5X5_SW     (1<<19)
#define MASK_6X6_SW     (1<<20)
#define MASK_7X7_SW     (1<<21)
#define MASK_8X8_SW     (1<<22)
#define MASK_9X9_SW     (1<<23)     
#define MASK_10X10_SW   (1<<24)
#define MASK_11X11_SW   (1<<25)
#define MASK_12X12_SW   (1<<26)
#define MASK_13X13_SW   (1<<27)
#define MASK_14X14_SW   (1<<28)
#define MASK_15X15_SW   (1<<29)
#define MASK_16X16_SW   (1<<30)
#define MASK_17X17_SW   (1<<31)
/// @}

/// \~chinese 相机的分辨率设定范围，可用于构件UI
/// \~english Camera resolution setting range, can be used for component UI
typedef struct
{
  INT iHeightMax;			///< \~chinese 图像最大高度 \~english Maximum image height
  INT iHeightMin;           ///< \~chinese 图像最小高度 \~english Image minimum height
  INT iWidthMax;            ///< \~chinese 图像最大宽度 \~english The maximum width of the image
  INT iWidthMin;            ///< \~chinese 图像最小宽度 \~english The minimum width of the image
  UINT uSkipModeMask;       ///< \~chinese SKIP模式掩码，为0，表示不支持SKIP 。bit0为1,表示支持SKIP 2x2 ;bit1为1，表示支持SKIP 3x3.... \~english The SKIP mode mask, which is 0, indicates that SKIP is not supported. Bit0 is 1 to indicate that SKIP 2x2 is supported; bit1 is 1 to indicate that SKIP 3x3 is supported....
  UINT uBinSumModeMask;     ///< \~chinese BIN(求和)模式掩码，为0，表示不支持BIN 。bit0为1,表示支持BIN 2x2 ;bit1为1，表示支持BIN 3x3.... \~english The BIN (sum) pattern mask, which is 0, indicates that BIN is not supported. Bit0 is 1, indicating that BIN 2x2 is supported; bit1 is 1, indicating that BIN 3x3 is supported....
  UINT uBinAverageModeMask; ///< \~chinese BIN(求均值)模式掩码，为0，表示不支持BIN 。bit0为1,表示支持BIN 2x2 ;bit1为1，表示支持BIN 3x3.... \~english The BIN (mean value) mode mask, which is 0, indicates that BIN is not supported. Bit0 is 1, indicating that BIN 2x2 is supported; bit1 is 1, indicating that BIN 3x3 is supported....
  UINT uResampleMask;       ///< \~chinese 硬件重采样的掩码 \~english Hardware resampling mask
} tSdkResolutionRange;

/// \~chinese 相机的分辨率描述
/// \~english Camera resolution description
typedef struct
{
  INT     iIndex;				///< \~chinese 索引号，[0,N]表示预设的分辨率(N 为预设分辨率的最大个数，一般不超过20),OXFF 表示自定义分辨率(ROI) \~english Index number, [0, N] indicates the preset resolution (N is the maximum number of preset resolutions, generally no more than 20), OXFF indicates custom resolution (ROI)
  char    acDescription[32];	///< \~chinese 该分辨率的描述信息。仅预设分辨率时该信息有效。自定义分辨率可忽略该信息 \~english The description of the resolution. This information is valid only when the resolution is preset. Custom resolution ignores this information
  UINT    uBinSumMode;			///< \~chinese BIN(求和)的模式,范围不能超过tSdkResolutionRange.uBinSumModeMask \~english The BIN (sum) mode cannot exceed the tSdkResolutionRange.uBinSumModeMask
  UINT    uBinAverageMode;		///< \~chinese BIN(求均值)的模式,范围不能超过tSdkResolutionRange.uBinAverageModeMask \~english BIN (average) mode, the range cannot exceed tSdkResolutionRange.uBinAverageModeMask 
  UINT    uSkipMode;			///< \~chinese 是否SKIP的尺寸，为0表示禁止SKIP模式，范围不能超过tSdkResolutionRange.uSkipModeMask \~english Whether the SKIP size is 0 indicates that the SKIP mode is disabled and the range cannot exceed the tSdkResolutionRange.uSkipModeMask
  UINT    uResampleMask;		///< \~chinese 硬件重采样的掩码 \~english Hardware resampling mask
  INT     iHOffsetFOV;			///< \~chinese 采集视场相对于Sensor最大视场左上角的水平偏移 \~english The horizontal offset of the acquisition field of view relative to the top left corner of the Sensor's largest field of view
  INT     iVOffsetFOV;			///< \~chinese 采集视场相对于Sensor最大视场左上角的垂直偏移 \~english The vertical offset of the acquisition field of view relative to the upper left corner of the Sensor's largest field of view
  INT     iWidthFOV;			///< \~chinese 采集视场的宽度 \~english The width of the field of view
  INT     iHeightFOV;			///< \~chinese 采集视场的高度 \~english The height of the field of view
  INT     iWidth;				///< \~chinese 相机最终输出的图像的宽度 \~english The width of the final output image of the camera
  INT     iHeight;				///< \~chinese 相机最终输出的图像的高度 \~english The height of the final output image of the camera
  INT     iWidthZoomHd;			///< \~chinese 硬件缩放的宽度,不需要进行此操作的分辨率，此变量设置为0. \~english The width of the hardware zoom, resolution that does not require this operation, this variable is set to 0.
  INT     iHeightZoomHd;		///< \~chinese 硬件缩放的高度,不需要进行此操作的分辨率，此变量设置为0. \~english The height of the hardware zoom, resolution that does not require this operation, this variable is set to 0.
  INT     iWidthZoomSw;			///< \~chinese 软件缩放的宽度,不需要进行此操作的分辨率，此变量设置为0. \~english The width of the software's zoom, which does not require the resolution of this operation, this variable is set to 0.
  INT     iHeightZoomSw;		///< \~chinese 软件缩放的高度,不需要进行此操作的分辨率，此变量设置为0. \~english The height of the software's zoom, which does not require the resolution of this operation, this variable is set to 0.
} tSdkImageResolution;

/// \~chinese 相机白平衡色温模式描述信息
/// \~english Camera white balance color temperature mode description information
typedef struct
{
    INT  iIndex;			///< \~chinese 模式索引号 \~english	Mode index number
    char acDescription[32];	///< \~chinese 描述信息 \~english Description
} tSdkColorTemperatureDes;

/// \~chinese 相机帧率描述信息
/// \~english Camera frame rate description information
typedef struct
{
    INT  iIndex;             ///< \~chinese 帧率索引号，一般0对应于低速模式，1对应于普通模式，2对应于高速模式 \~english Frame rate index number, generally 0 corresponds to low speed mode, 1 corresponds to normal mode, 2 corresponds to high speed mode
    char acDescription[32];  ///< \~chinese 描述信息 \~english Description
} tSdkFrameSpeed;

/// \~chinese 相机曝光功能范围定义
/// \see tSdkCameraCapbility.sExposeDesc
/// \~english Camera exposure function scope definition
/// \see tSdkCameraCapbility.sExposeDesc
typedef struct
{           
    UINT  uiTargetMin;		///< \~chinese 自动曝光亮度目标最小值	\~english Auto exposure brightness target minimum
    UINT  uiTargetMax;		///< \~chinese 自动曝光亮度目标最大值	\~english Auto exposure brightness target maximum
    UINT  uiAnalogGainMin;	///< \~chinese 模拟增益的最小值，单位为fAnalogGainStep中定义 \~english	The minimum value of the analog gain in fAnalog defined in GainStep
    UINT  uiAnalogGainMax;	///< \~chinese 模拟增益的最大值，单位为fAnalogGainStep中定义 \~english The maximum value of the analog gain in fAnalog defined in GainStep
    float fAnalogGainStep;	///< \~chinese 模拟增益每增加1，对应的增加的放大倍数。例如，uiAnalogGainMin一般为16，fAnalogGainStep一般为0.125，那么最小放大倍数就是16*0.125 = 2倍 \~english Each increase in analog gain corresponds to an increased amplification factor. For example, uiAnalogGainMin is generally 16 and fAnalogGainStep is generally 0.125, so the minimum magnification is 16*0.125 = 2 times
    UINT  uiExposeTimeMin;	///< \~chinese 手动模式下，曝光时间的最小值，单位:行。根据CameraGetExposureLineTime可以获得一行对应的时间(微秒),从而得到整帧的曝光时间 \~english The minimum exposure time in manual mode, unit: line. According to CameraGetExposureLineTime can get a row of corresponding time (microseconds) to get the entire frame exposure time
    UINT  uiExposeTimeMax;	///< \~chinese 手动模式下，曝光时间的最大值，单位:行 \~english Maximum exposure time in manual mode, unit: line
} tSdkExpose;

/// \~chinese 触发模式描述
/// \~english Trigger mode description
typedef struct
{
  INT   iIndex;            ///< \~chinese 模式索引号 \~english Mode index number
  char  acDescription[32]; ///< \~chinese 该模式的描述信息 \~english Description information of this mode
} tSdkTrigger;

/// \~chinese 传输分包大小描述(针对某些网络相机有效)
/// \~english Transmission packet size description (valid for some web cameras)
typedef struct
{
    INT  iIndex;              ///< \~chinese 分包大小索引号 \~english Packet size index number
    char acDescription[32];   ///< \~chinese 对应的描述信息 \~english Corresponding description information
    UINT iPackSize;			  ///< \~chinese 包大小 \~english Packet size
} tSdkPackLength;

/// \~chinese 预设的LUT表描述
/// \~english Preset LUT Table Description
typedef struct
{
    INT  iIndex;                ///< \~chinese 索引 \~english index
    char acDescription[32];     ///< \~chinese 描述信息 \~english description
} tSdkPresetLut;

/// \~chinese AE算法描述
/// \~english AE algorithm description
typedef struct
{
    INT  iIndex;                ///< \~chinese 索引 \~english index  
    char acDescription[32];     ///< \~chinese 描述信息 \~english description
} tSdkAeAlgorithm;

/// \~chinese RAW转RGB算法描述
/// \~english RAW to RGB algorithm description
typedef struct
{
    INT  iIndex;                ///< \~chinese 索引 \~english index
    char acDescription[32];     ///< \~chinese 描述信息 \~english description
} tSdkBayerDecodeAlgorithm;

/// \~chinese 帧统计信息
/// \~english Frame statistics
typedef struct
{
  INT iTotal;           ///< \~chinese 当前采集的总帧数（包括错误帧） \~english The current total number of frames collected (including error frames)
    INT iCapture;       ///< \~chinese 当前采集的有效帧的数量 \~english The number of valid frames currently collected
    INT iLost;          ///< \~chinese 当前丢帧的数量 \~english Current number of dropped frames
} tSdkFrameStatistic;

/// \~chinese 相机输出的图像数据格式
/// \~english Camera output image data format
typedef struct
{
  INT     iIndex;             ///< \~chinese 格式种类编号 \~english Format type number
  char    acDescription[32];  ///< \~chinese 描述信息 \~english description
  UINT    iMediaType;         ///< \~chinese 对应的图像格式编码，如CAMERA_MEDIA_TYPE_BAYGR8。 \~english Corresponding image format encoding, such as CAMERA_MEDIA_TYPE_BAYGR8.
} tSdkMediaType;

/// \~chinese 伽马的设定范围
/// \~english Gamma setting range
typedef struct 
{
  INT iMin;       ///< \~chinese 最小值 \~english min
  INT iMax;       ///< \~chinese 最大值 \~english max
} tGammaRange;

/// \~chinese 对比度的设定范围
/// \~english Contrast setting range
typedef struct 
{
    INT iMin;   ///< \~chinese 最小值 \~english min
    INT iMax;   ///< \~chinese 最大值 \~english max
} tContrastRange;

/// \~chinese RGB三通道数字增益的设定范围
/// \~english RGB three channel digital gain setting range
typedef struct 
{ 
    INT iRGainMin;    ///< \~chinese 红色增益的最小值 \~english Red gain minimum
    INT iRGainMax;    ///< \~chinese 红色增益的最大值 \~english Red gain maximum
    INT iGGainMin;    ///< \~chinese 绿色增益的最小值 \~english Green gain minimum
    INT iGGainMax;    ///< \~chinese 绿色增益的最大值 \~english Green gain maximum
    INT iBGainMin;    ///< \~chinese 蓝色增益的最小值 \~english Blue gain minimum
    INT iBGainMax;    ///< \~chinese 蓝色增益的最大值 \~english blue gain maximum
} tRgbGainRange;

/// \~chinese 饱和度设定的范围
/// \~english Saturation setting range
typedef struct 
{  
    INT iMin;   ///< \~chinese 最小值 \~english min
    INT iMax;   ///< \~chinese 最大值 \~english max
} tSaturationRange;

/// \~chinese 锐化的设定范围
/// \~english Sharpening setting range
typedef struct 
{  
  INT iMin;   ///< \~chinese 最小值 \~english min
  INT iMax;   ///< \~chinese 最大值 \~english max
} tSharpnessRange;

/// \~chinese ISP模块的使能信息
/// \~english ISP module enable information
typedef struct
{
    BOOL bMonoSensor;       ///< \~chinese 表示该型号相机是否为黑白相机,如果是黑白相机，则颜色相关的功能都无法调节 \~english Indicates whether this model is a black-and-white camera. If it is a black-and-white camera, color-related functions cannot be adjusted.
    BOOL bWbOnce;           ///< \~chinese 表示该型号相机是否支持手动白平衡功能 \~english Indicates whether this model camera supports manual white balance function
    BOOL bAutoWb;           ///< \~chinese 表示该型号相机是否支持自动白平衡功能 \~english Indicates whether this model camera supports automatic white balance function
    BOOL bAutoExposure;     ///< \~chinese 表示该型号相机是否支持自动曝光功能 \~english Indicates whether this model camera supports auto exposure function
    BOOL bManualExposure;   ///< \~chinese 表示该型号相机是否支持手动曝光功能 \~english Indicates whether this model camera supports manual exposure function
    BOOL bAntiFlick;        ///< \~chinese 表示该型号相机是否支持抗频闪功能 \~english Indicates whether this model camera supports anti-strobe function
    BOOL bDeviceIsp;        ///< \~chinese 表示该型号相机是否支持硬件ISP功能 \~english Indicates whether this model camera supports hardware ISP function
    BOOL bForceUseDeviceIsp;///< \~chinese bDeviceIsp和bForceUseDeviceIsp同时为TRUE时，表示强制只用硬件ISP，不可取消。 \~english When both bDeviceIsp and bForceUseDeviceIsp are TRUE, this means that only the hardware ISP is forced and cannot be cancelled.
    BOOL bZoomHD;           ///< \~chinese 相机硬件是否支持图像缩放输出(只能是缩小)。 \~english Whether the camera hardware supports image scaling output (can only be reduced).
} tSdkIspCapacity;

/// \~chinese 定义整合的设备描述信息，这些信息可以用于动态构建UI
/// \note 调用@link #CameraGetCapability @endlink获取本结构
/// \~english Define integrated device description information that can be used to dynamically build UI
/// \note call @link #CameraGetCapability @endlink to get this structure
typedef struct
{
    
  tSdkTrigger   *pTriggerDesc;          ///< \~chinese 触发模式 \~english trigger mode
  INT           iTriggerDesc;           ///< \~chinese 触发模式的个数，即pTriggerDesc数组的大小 \~english The number of trigger modes, that is, the size of the pTriggerDesc array
  
  tSdkImageResolution   *pImageSizeDesc;///< \~chinese 预设分辨率 \~english Preset resolution
  INT                   iImageSizeDesc; ///< \~chinese 预设分辨率的个数，即pImageSizeDesc数组的大小 \~english The number of preset resolutions, that is, the size of the pImageSizeDesc array
  
  tSdkColorTemperatureDes *pClrTempDesc;///< \~chinese 预设色温，用于白平衡 \~english Preset color temperature for white balance
  INT                     iClrTempDesc; ///< \~chinese 预设色温个数 \~english The number of preset color temperatures
  
  tSdkMediaType     *pMediaTypeDesc;    ///< \~chinese 相机输出图像格式 \~english Camera output image format
  INT               iMediaTypdeDesc;    ///< \~chinese 相机输出图像格式的种类个数，即pMediaTypeDesc数组的大小。 \~english The number of types of camera output image formats, that is, the size of the pMediaTypeDesc array.

  tSdkFrameSpeed    *pFrameSpeedDesc;   ///< \~chinese 可调节帧速类型，对应界面上普通 高速 和超级三种速度设置 \~english Adjustable frame rate type, normal high speed and super three speed settings on the corresponding interface
  INT               iFrameSpeedDesc;    ///< \~chinese 可调节帧速类型的个数，即pFrameSpeedDesc数组的大小。 \~english The number of frame rate types that can be adjusted, that is, the size of the pFrameSpeedDesc array.
  
  tSdkPackLength    *pPackLenDesc;      ///< \~chinese 传输包长度，一般用于网络设备 \~english Transmission packet length, generally used for network equipment
  INT               iPackLenDesc;       ///< \~chinese 可供选择的传输分包长度的个数，即pPackLenDesc数组的大小。  \~english The number of transmission packetization lengths available for selection, which is the size of the pPackLenDesc array.
  
  INT           iOutputIoCounts;        ///< \~chinese 可编程输出IO的个数 \~english Number of programmable output IOs
  INT           iInputIoCounts;         ///< \~chinese 可编程输入IO的个数 \~english Number of programmable input IOs

  tSdkPresetLut  *pPresetLutDesc;       ///< \~chinese 相机预设的LUT表 \~english Camera preset LUT table
  INT            iPresetLut;            ///< \~chinese 相机预设的LUT表的个数，即pPresetLutDesc数组的大小 \~english The number of LUT tables preset by the camera, that is, the size of the pPresetLutDesc array

  INT           iUserDataMaxLen;        ///< \~chinese 指示该相机中用于保存用户数据区的最大长度。为0表示无。 \~english Indicates the maximum length in the camera used to save the user data area. 0 means no.
  BOOL          bParamInDevice;         ///< \~chinese 指示该设备是否支持从设备中读写参数组。1为支持，0不支持。 \~english Indicates whether the device supports reading and writing parameter groups from the device. 1 is supported, 0 is not supported.

  tSdkAeAlgorithm   *pAeAlmSwDesc;      ///< \~chinese 软件自动曝光算法描述 \~english Software auto exposure algorithm description
  int                iAeAlmSwDesc;      ///< \~chinese 软件自动曝光算法个数 \~english Software automatic exposure algorithm number

  tSdkAeAlgorithm    *pAeAlmHdDesc;     ///< \~chinese 硬件自动曝光算法描述，为NULL表示不支持硬件自动曝光 \~english Hardware auto exposure algorithm description, NULL means hardware auto exposure is not supported
  int                iAeAlmHdDesc;      ///< \~chinese 硬件自动曝光算法个数，为0表示不支持硬件自动曝光 \~english Number of hardware auto exposure algorithms, 0 means hardware auto exposure is not supported

  tSdkBayerDecodeAlgorithm   *pBayerDecAlmSwDesc; ///< \~chinese 软件Bayer转换为RGB数据的算法描述 \~english Algorithm Description of Software Bayer Conversion to RGB Data
  int                        iBayerDecAlmSwDesc;  ///< \~chinese 软件Bayer转换为RGB数据的算法个数 \~english The number of algorithms that Bayer converts to RGB data

  tSdkBayerDecodeAlgorithm   *pBayerDecAlmHdDesc; ///< \~chinese 硬件Bayer转换为RGB数据的算法描述，为NULL表示不支持 \~english Hardware Bayer converts to RGB data algorithm description, is not supported for NULL representation
  int                        iBayerDecAlmHdDesc;  ///< \~chinese 硬件Bayer转换为RGB数据的算法个数，为0表示不支持 \~english The number of algorithms that hardware Bayer converts to RGB data, 0 means not supported
  
  /* 图像参数的调节范围定义,用于动态构建UI*/
  tSdkExpose            sExposeDesc;      ///< \~chinese 曝光的范围值 \~english Exposure range value
  tSdkResolutionRange   sResolutionRange; ///< \~chinese 分辨率范围描述 \~english Resolution range description
  tRgbGainRange         sRgbGainRange;    ///< \~chinese 图像数字增益范围描述 \~english Image digital gain range description
  tSaturationRange      sSaturationRange; ///< \~chinese 饱和度范围描述 \~english Saturation range description
  tGammaRange           sGammaRange;      ///< \~chinese 伽马范围描述 \~english Gamma range description
  tContrastRange        sContrastRange;   ///< \~chinese 对比度范围描述 \~english Contrast range description
  tSharpnessRange       sSharpnessRange;  ///< \~chinese 锐化范围描述 \~english Sharpening range description
  tSdkIspCapacity       sIspCapacity;     ///< \~chinese ISP能力描述 \~english ISP capability description

    
} tSdkCameraCapbility;


/// \~chinese 图像帧头信息
/// \~english Image frame header information
typedef struct 
{
  UINT    uiMediaType;    ///< \~chinese 图像格式 \~english Image Format
  UINT    uBytes;         ///< \~chinese 图像数据字节数 \~english Total bytes
  INT     iWidth;         ///< \~chinese 图像的宽度，调用图像处理函数后，该变量可能被动态修改，来指示处理后的图像尺寸 \~english The width of the image, after calling the image processing function, the variable may be dynamically modified to indicate the image size after processing
  INT     iHeight;        ///< \~chinese 图像的高度，调用图像处理函数后，该变量可能被动态修改，来指示处理后的图像尺寸 \~english The height of the image, after calling the image processing function, the variable may be dynamically modified to indicate the image size after processing
  INT     iWidthZoomSw;   ///< \~chinese 软件缩放的宽度,不需要进行软件裁剪的图像，此变量设置为0. \~english The width of the software zoom, which does not require software cropping. This variable is set to 0.
  INT     iHeightZoomSw;  ///< \~chinese 软件缩放的高度,不需要进行软件裁剪的图像，此变量设置为0. \~english Software zoom height, no software cropped image is required. This variable is set to 0.
  BOOL    bIsTrigger;     ///< \~chinese 指示是否为触发帧 \~english is trigger 
  UINT    uiTimeStamp;    ///< \~chinese 该帧的采集时间，单位0.1毫秒 \~english The frame acquisition time, in units of 0.1 milliseconds
  UINT    uiExpTime;      ///< \~chinese 当前图像的曝光值，单位为微秒us \~english Exposure of the current image in microseconds us
  float   fAnalogGain;    ///< \~chinese 当前图像的模拟增益倍数 \~english The current image's analog gain multiplier
  INT     iGamma;         ///< \~chinese 该帧图像的伽马设定值，仅当LUT模式为动态参数生成时有效，其余模式下为-1 \~english The gamma setting value of the frame image is valid only when the LUT mode is a dynamic parameter generation, and is -1 in other modes.
  INT     iContrast;      ///< \~chinese 该帧图像的对比度设定值，仅当LUT模式为动态参数生成时有效，其余模式下为-1 \~english The contrast setting value of the frame image is only valid when the LUT mode is generated by the dynamic parameter, and is -1 in other modes.
  INT     iSaturation;    ///< \~chinese 该帧图像的饱和度设定值，对于黑白相机无意义，为0 \~english The saturation value of the frame image, which is meaningless for a black and white camera, is 0
  float   fRgain;         ///< \~chinese 该帧图像处理的红色数字增益倍数，对于黑白相机无意义，为1 \~english The red digital gain multiple of this frame image processing is meaningless for a black and white camera and is 1
  float   fGgain;         ///< \~chinese 该帧图像处理的绿色数字增益倍数，对于黑白相机无意义，为1 \~english The green digital gain multiplier for this frame image processing, meaning no significance for black and white cameras, is 1
  float   fBgain;         ///< \~chinese 该帧图像处理的蓝色数字增益倍数，对于黑白相机无意义，为1 \~english The blue digital gain multiplier for this frame image processing, meaning no significance for black and white cameras, is 1
}tSdkFrameHead;

/// \~chinese 图像帧描述
/// \~english Image frame description
typedef struct sCameraFrame
{
  tSdkFrameHead   head;     ///< \~chinese 帧头 \~english Frame Head
  BYTE *          pBuffer;  ///< \~chinese 数据区 \~english Image Data
}tSdkFrame;

/// @ingroup API_GRAB_CB
/// \~chinese 图像捕获的回调函数定义
/// \~english Callback function definition for image capture
typedef void (WINAPI* CAMERA_SNAP_PROC)(CameraHandle hCamera, BYTE *pFrameBuffer, tSdkFrameHead* pFrameHead,PVOID pContext);

/// @ingroup API_SETTINGS_PAGE
/// \~chinese 相机配置页面的消息回调函数定义
/// \~english camera configuration page message callback function definition
typedef void (WINAPI* CAMERA_PAGE_MSG_PROC)(CameraHandle hCamera,UINT MSG,UINT uParam,PVOID pContext);

/// @ingroup API_RECONNECT
/// \~chinese 相机连接状态回调
/// \param [in] hCamera 相机句柄
/// \param [in] MSG 消息，0: 相机连接断开    1: 相机连接恢复
/// \param [in] uParam 附加信息
/// \param [in] pContext 用户数据
/// \return 无
/// \note USB相机uParam取值：
/// \note 		未定义
/// \note 网口相机uParam取值：
/// \note		当MSG=0时：未定义
/// \note		当MSG=1时：
/// \note			0：上次掉线原因，网络通讯失败
/// \note			1：上次掉线原因，相机掉电
/// \~english Camera connection status callback
/// \param [in] hCamera Camera handle
/// \param [in] MSG message, 0: Camera disconnected 1: Camera connection restored
/// \param [in] uParam Additional Information
/// \param [in] pContext user data
/// \return None
/// \note USB camera uParam value:
/// \note       Undefined
/// \note network camera uParam value:
/// \note       When MSG=0: Undefined
/// \note       When MSG=1:
/// \note           0: The last dropped reason, network communication failed
/// \note           1: The last dropped reason, the camera lost power
typedef void (WINAPI* CAMERA_CONNECTION_STATUS_CALLBACK)(CameraHandle hCamera,UINT MSG,UINT uParam,PVOID pContext);


//////////////////////////////////////////////////////////////////////////
// Grabber 相关

/// \~chinese Grabber统计信息
/// \~english Grabber statistics
typedef struct
{
	int Width;			///< \~chinese 帧宽度 \~english Frame image width
	int Height;			///< \~chinese 帧高度 \~english Frame image height
	int Disp;			///< \~chinese 显示帧数量 \~english Display frame number
	int Capture;		///< \~chinese 采集的有效帧的数量 \~english The number of valid frames collected
	int Lost;			///< \~chinese 丢帧的数量 \~english The number of dropped frames
	int Error;			///< \~chinese 错帧的数量 \~english The number of error frames
	float DispFps;		///< \~chinese 显示帧率 \~english Display frame rate
	float CapFps;		///< \~chinese 捕获帧率 \~english Capture frame rate
}tSdkGrabberStat;

/// @ingroup GRABBER_CB
/// \~chinese 图像捕获的回调函数定义
/// \~english Callback function definition for image capture
typedef void (__stdcall *pfnCameraGrabberFrameCallback)(
	void* Grabber, 
	BYTE *pFrameBuffer, 
	tSdkFrameHead* pFrameHead,
	void* Context);

/// @ingroup GRABBER_CB
/// \~chinese 帧监听函数定义
/// \param [in] Grabber
/// \param [in] Phase 图像处理阶段
/// \param [in] pFrameBuffer 帧数据
/// \param [in] pFrameHead 帧头
/// \param [in] Context 用户数据
/// \return 0:Grabber将会丢弃此帧并结束针对此帧的所有后续处理阶段   1:继续下一阶段处理
/// \note 每当Grabber捕获到一帧图像时，会分3个阶段来依次调用FrameListener
/// \note 阶段0: RAW数据处理，pFrameBuffer=Raw数据
/// \note 阶段1: 截图前处理，pFrameBuffer=RGB数据
/// \note 阶段2: 显示前处理，pFrameBuffer=RGB数据
/// \note 特别的，当相机掉线后此回调也会被调用，此时Phase=-1，pFrameBuffer=NULL,pFrameHead=NULL。
/// \~english Frame listening function definition
/// \param [in] Grabber
/// \param [in] Phase image processing phase
/// \param [in] pFrameBuffer frame data
/// \param [in] pFrameHead Frame Header
/// \param [in] Context user data
/// \return 0: Grabber will discard this frame and end all subsequent processing stages for this frame     1: Continue to the next stage of processing
/// \note Whenever Grabber captures a frame of image, it will call FrameListener in turn in 3 stages.
/// \note Phase 0: RAW data processing, pFrameBuffer= Raw data
/// \note Phase 1: Screenshot pre-processing, pFrameBuffer=RGB data
/// \note Phase 2: Display preprocessing, pFrameBuffer=RGB data
/// \note In particular, this callback will be called when the camera is disconnected. At this time, Phase=-1, pFrameBuffer=NULL, and pFrameHead=NULL.
typedef int (__stdcall *pfnCameraGrabberFrameListener)(
	void* Grabber, 
	int Phase,
	BYTE *pFrameBuffer, 
	tSdkFrameHead* pFrameHead,
	void* Context);

/// @ingroup GRABBER_SNAPSHOT
/// \~chinese 异步抓图的回调函数定义
/// \warning Image需要调用 @link CameraImage_Destroy @endlink 释放
/// \~english Asynchronous snapshot callback function definition
/// \warning Image needs to call @link CameraImage_Destroy @endlink to release
typedef void (__stdcall *pfnCameraGrabberSaveImageComplete)(
	void* Grabber, 
	void* Image,	// 需要调用CameraImage_Destroy释放
	CameraSdkStatus Status,
	void* Context
	);


/// @ingroup MV_MACRO_TYPE 
/// @{
//----------------------------IMAGE FORMAT DEFINE------------------------------------
//----------------------------图像格式定义-------------------------------------------
#define CAMERA_MEDIA_TYPE_MONO                           0x01000000
#define CAMERA_MEDIA_TYPE_RGB                            0x02000000 
#define CAMERA_MEDIA_TYPE_COLOR                          0x02000000
#define CAMERA_MEDIA_TYPE_CUSTOM                         0x80000000
#define CAMERA_MEDIA_TYPE_COLOR_MASK                     0xFF000000
#define CAMERA_MEDIA_TYPE_OCCUPY1BIT                     0x00010000
#define CAMERA_MEDIA_TYPE_OCCUPY2BIT                     0x00020000
#define CAMERA_MEDIA_TYPE_OCCUPY4BIT                     0x00040000
#define CAMERA_MEDIA_TYPE_OCCUPY8BIT                     0x00080000
#define CAMERA_MEDIA_TYPE_OCCUPY10BIT                    0x000A0000
#define CAMERA_MEDIA_TYPE_OCCUPY12BIT                    0x000C0000
#define CAMERA_MEDIA_TYPE_OCCUPY16BIT                    0x00100000
#define CAMERA_MEDIA_TYPE_OCCUPY24BIT                    0x00180000
#define CAMERA_MEDIA_TYPE_OCCUPY32BIT                    0x00200000
#define CAMERA_MEDIA_TYPE_OCCUPY36BIT                    0x00240000
#define CAMERA_MEDIA_TYPE_OCCUPY48BIT                    0x00300000
#define CAMERA_MEDIA_TYPE_OCCUPY64BIT					 0x00400000

#define CAMERA_MEDIA_TYPE_EFFECTIVE_PIXEL_SIZE_MASK      0x00FF0000
#define CAMERA_MEDIA_TYPE_EFFECTIVE_PIXEL_SIZE_SHIFT     16

#define CAMERA_MEDIA_TYPE_PIXEL_SIZE(type)				 (((type) & CAMERA_MEDIA_TYPE_EFFECTIVE_PIXEL_SIZE_MASK) >> CAMERA_MEDIA_TYPE_EFFECTIVE_PIXEL_SIZE_SHIFT)


#define CAMERA_MEDIA_TYPE_ID_MASK                        0x0000FFFF
#define CAMERA_MEDIA_TYPE_COUNT                          0x46 

/*mono*/
#define CAMERA_MEDIA_TYPE_MONO1P             (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY1BIT | 0x0037)
#define CAMERA_MEDIA_TYPE_MONO2P             (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY2BIT | 0x0038)
#define CAMERA_MEDIA_TYPE_MONO4P             (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY4BIT | 0x0039)
#define CAMERA_MEDIA_TYPE_MONO8              (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY8BIT | 0x0001)
#define CAMERA_MEDIA_TYPE_MONO8S             (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY8BIT | 0x0002)
#define CAMERA_MEDIA_TYPE_MONO10             (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0003)
#define CAMERA_MEDIA_TYPE_MONO10_PACKED      (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0004)
#define CAMERA_MEDIA_TYPE_MONO12             (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0005)
#define CAMERA_MEDIA_TYPE_MONO12_PACKED      (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0006)
#define CAMERA_MEDIA_TYPE_MONO14             (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0025)
#define CAMERA_MEDIA_TYPE_MONO16             (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0007)

/*Bayer */
#define CAMERA_MEDIA_TYPE_BAYGR8             (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY8BIT | 0x0008)
#define CAMERA_MEDIA_TYPE_BAYRG8             (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY8BIT | 0x0009)
#define CAMERA_MEDIA_TYPE_BAYGB8             (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY8BIT | 0x000A)
#define CAMERA_MEDIA_TYPE_BAYBG8             (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY8BIT | 0x000B)

#define CAMERA_MEDIA_TYPE_BAYGR10_MIPI       (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY10BIT | 0x0026)
#define CAMERA_MEDIA_TYPE_BAYRG10_MIPI       (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY10BIT | 0x0027)
#define CAMERA_MEDIA_TYPE_BAYGB10_MIPI       (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY10BIT | 0x0028)
#define CAMERA_MEDIA_TYPE_BAYBG10_MIPI       (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY10BIT | 0x0029)


#define CAMERA_MEDIA_TYPE_BAYGR10            (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x000C)
#define CAMERA_MEDIA_TYPE_BAYRG10            (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x000D)
#define CAMERA_MEDIA_TYPE_BAYGB10            (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x000E)
#define CAMERA_MEDIA_TYPE_BAYBG10            (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x000F)

#define CAMERA_MEDIA_TYPE_BAYGR12            (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0010)
#define CAMERA_MEDIA_TYPE_BAYRG12            (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0011)
#define CAMERA_MEDIA_TYPE_BAYGB12            (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0012)
#define CAMERA_MEDIA_TYPE_BAYBG12            (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0013)


#define CAMERA_MEDIA_TYPE_BAYGR10_PACKED     (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0026)
#define CAMERA_MEDIA_TYPE_BAYRG10_PACKED     (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0027)
#define CAMERA_MEDIA_TYPE_BAYGB10_PACKED     (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0028)
#define CAMERA_MEDIA_TYPE_BAYBG10_PACKED     (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0029)

#define CAMERA_MEDIA_TYPE_BAYGR12_PACKED     (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x002A)
#define CAMERA_MEDIA_TYPE_BAYRG12_PACKED     (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x002B)
#define CAMERA_MEDIA_TYPE_BAYGB12_PACKED     (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x002C)
#define CAMERA_MEDIA_TYPE_BAYBG12_PACKED     (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x002D)

#define CAMERA_MEDIA_TYPE_BAYGR16            (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x002E)
#define CAMERA_MEDIA_TYPE_BAYRG16            (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x002F)
#define CAMERA_MEDIA_TYPE_BAYGB16            (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0030)
#define CAMERA_MEDIA_TYPE_BAYBG16            (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0031)

/*RGB */
#define CAMERA_MEDIA_TYPE_RGB8               (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY24BIT | 0x0014)
#define CAMERA_MEDIA_TYPE_BGR8               (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY24BIT | 0x0015)
#define CAMERA_MEDIA_TYPE_RGBA8              (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY32BIT | 0x0016)
#define CAMERA_MEDIA_TYPE_BGRA8              (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY32BIT | 0x0017)
#define CAMERA_MEDIA_TYPE_RGB10              (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY48BIT | 0x0018)
#define CAMERA_MEDIA_TYPE_BGR10              (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY48BIT | 0x0019)
#define CAMERA_MEDIA_TYPE_RGB12              (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY48BIT | 0x001A)
#define CAMERA_MEDIA_TYPE_BGR12              (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY48BIT | 0x001B)
#define CAMERA_MEDIA_TYPE_RGB16              (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY48BIT | 0x0033)
#define CAMERA_MEDIA_TYPE_BGR16              (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY48BIT | 0x004B)
#define CAMERA_MEDIA_TYPE_RGBA16             (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY64BIT | 0x0064)
#define CAMERA_MEDIA_TYPE_BGRA16             (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY64BIT | 0x0051)
#define CAMERA_MEDIA_TYPE_RGB10V1_PACKED     (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY32BIT | 0x001C)
#define CAMERA_MEDIA_TYPE_RGB10P32           (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY32BIT | 0x001D)
#define CAMERA_MEDIA_TYPE_RGB12V1_PACKED     (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY36BIT | 0X0034)
#define CAMERA_MEDIA_TYPE_RGB565P            (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0035)
#define CAMERA_MEDIA_TYPE_BGR565P            (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0X0036)

/*YUV and YCbCr*/
#define CAMERA_MEDIA_TYPE_YUV411_8_UYYVYY    (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x001E)
#define CAMERA_MEDIA_TYPE_YUV422_8_UYVY      (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x001F)
#define CAMERA_MEDIA_TYPE_YUV422_8           (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0032)
#define CAMERA_MEDIA_TYPE_YUV8_UYV           (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY24BIT | 0x0020)
#define CAMERA_MEDIA_TYPE_YCBCR8_CBYCR       (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY24BIT | 0x003A)
//CAMERA_MEDIA_TYPE_YCBCR422_8 : YYYYCbCrCbCr
#define CAMERA_MEDIA_TYPE_YCBCR422_8             (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x003B)
#define CAMERA_MEDIA_TYPE_YCBCR422_8_CBYCRY      (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0043)
#define CAMERA_MEDIA_TYPE_YCBCR411_8_CBYYCRYY    (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x003C)
#define CAMERA_MEDIA_TYPE_YCBCR601_8_CBYCR       (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY24BIT | 0x003D)
#define CAMERA_MEDIA_TYPE_YCBCR601_422_8         (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x003E)
#define CAMERA_MEDIA_TYPE_YCBCR601_422_8_CBYCRY  (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0044)
#define CAMERA_MEDIA_TYPE_YCBCR601_411_8_CBYYCRYY    (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x003F)
#define CAMERA_MEDIA_TYPE_YCBCR709_8_CBYCR           (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY24BIT | 0x0040)
#define CAMERA_MEDIA_TYPE_YCBCR709_422_8             (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0041)
#define CAMERA_MEDIA_TYPE_YCBCR709_422_8_CBYCRY      (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0045)
#define CAMERA_MEDIA_TYPE_YCBCR709_411_8_CBYYCRYY    (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0042)

/*RGB Planar */
#define CAMERA_MEDIA_TYPE_RGB8_PLANAR        (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY24BIT | 0x0021)
#define CAMERA_MEDIA_TYPE_RGB10_PLANAR       (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY48BIT | 0x0022)
#define CAMERA_MEDIA_TYPE_RGB12_PLANAR       (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY48BIT | 0x0023)
#define CAMERA_MEDIA_TYPE_RGB16_PLANAR       (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY48BIT | 0x0024)

/*MindVision 12bit packed bayer*/
#define CAMERA_MEDIA_TYPE_BAYGR12_PACKED_MV     (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0060)
#define CAMERA_MEDIA_TYPE_BAYRG12_PACKED_MV     (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0061)
#define CAMERA_MEDIA_TYPE_BAYGB12_PACKED_MV     (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0062)
#define CAMERA_MEDIA_TYPE_BAYBG12_PACKED_MV     (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0063)

/*MindVision 12bit packed monochome*/
#define CAMERA_MEDIA_TYPE_MONO12_PACKED_MV     (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0064)
/// @}

#endif
