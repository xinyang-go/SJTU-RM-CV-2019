#coding=utf-8
import platform
from ctypes import *
from threading import local

# 回调函数类型
CALLBACK_FUNC_TYPE = None

# SDK动态库
_sdk = None

def _Init():
	global _sdk
	global CALLBACK_FUNC_TYPE

	is_win = (platform.system() == "Windows")
	is_x86 = (platform.architecture()[0] == '32bit')

	if is_win:
		_sdk = windll.MVCAMSDK if is_x86 else windll.MVCAMSDK_X64
		CALLBACK_FUNC_TYPE = WINFUNCTYPE
	else:
		_sdk = cdll.LoadLibrary("libMVSDK.so")
		CALLBACK_FUNC_TYPE = CFUNCTYPE

_Init()

#-------------------------------------------类型定义--------------------------------------------------

# 状态码定义
CAMERA_STATUS_SUCCESS = 0   # 操作成功
CAMERA_STATUS_FAILED = -1   # 操作失败
CAMERA_STATUS_INTERNAL_ERROR = -2   # 内部错误
CAMERA_STATUS_UNKNOW = -3   # 未知错误
CAMERA_STATUS_NOT_SUPPORTED = -4   # 不支持该功能
CAMERA_STATUS_NOT_INITIALIZED = -5   # 初始化未完成
CAMERA_STATUS_PARAMETER_INVALID = -6   # 参数无效
CAMERA_STATUS_PARAMETER_OUT_OF_BOUND = -7   # 参数越界
CAMERA_STATUS_UNENABLED = -8   # 未使能
CAMERA_STATUS_USER_CANCEL = -9   # 用户手动取消了，比如roi面板点击取消，返回
CAMERA_STATUS_PATH_NOT_FOUND = -10  # 注册表中没有找到对应的路径
CAMERA_STATUS_SIZE_DISMATCH = -11  # 获得图像数据长度和定义的尺寸不匹配
CAMERA_STATUS_TIME_OUT = -12  # 超时错误
CAMERA_STATUS_IO_ERROR = -13  # 硬件IO错误
CAMERA_STATUS_COMM_ERROR = -14  # 通讯错误
CAMERA_STATUS_BUS_ERROR = -15  # 总线错误
CAMERA_STATUS_NO_DEVICE_FOUND = -16  # 没有发现设备
CAMERA_STATUS_NO_LOGIC_DEVICE_FOUND = -17  # 未找到逻辑设备
CAMERA_STATUS_DEVICE_IS_OPENED = -18  # 设备已经打开
CAMERA_STATUS_DEVICE_IS_CLOSED = -19  # 设备已经关闭
CAMERA_STATUS_DEVICE_VEDIO_CLOSED = -20  # 没有打开设备视频，调用录像相关的函数时，如果相机视频没有打开，则回返回该错误。
CAMERA_STATUS_NO_MEMORY = -21  # 没有足够系统内存
CAMERA_STATUS_FILE_CREATE_FAILED = -22  # 创建文件失败
CAMERA_STATUS_FILE_INVALID = -23  # 文件格式无效
CAMERA_STATUS_WRITE_PROTECTED = -24  # 写保护，不可写
CAMERA_STATUS_GRAB_FAILED = -25  # 数据采集失败
CAMERA_STATUS_LOST_DATA = -26  # 数据丢失，不完整
CAMERA_STATUS_EOF_ERROR = -27  # 未接收到帧结束符
CAMERA_STATUS_BUSY = -28  # 正忙(上一次操作还在进行中)，此次操作不能进行
CAMERA_STATUS_WAIT = -29  # 需要等待(进行操作的条件不成立)，可以再次尝试
CAMERA_STATUS_IN_PROCESS = -30  # 正在进行，已经被操作过
CAMERA_STATUS_IIC_ERROR = -31  # IIC传输错误
CAMERA_STATUS_SPI_ERROR = -32  # SPI传输错误
CAMERA_STATUS_USB_CONTROL_ERROR = -33  # USB控制传输错误
CAMERA_STATUS_USB_BULK_ERROR = -34  # USB BULK传输错误
CAMERA_STATUS_SOCKET_INIT_ERROR = -35  # 网络传输套件初始化失败
CAMERA_STATUS_GIGE_FILTER_INIT_ERROR = -36  # 网络相机内核过滤驱动初始化失败，请检查是否正确安装了驱动，或者重新安装。
CAMERA_STATUS_NET_SEND_ERROR = -37  # 网络数据发送错误
CAMERA_STATUS_DEVICE_LOST = -38  # 与网络相机失去连接，心跳检测超时
CAMERA_STATUS_DATA_RECV_LESS = -39  # 接收到的字节数比请求的少 
CAMERA_STATUS_FUNCTION_LOAD_FAILED = -40  # 从文件中加载程序失败
CAMERA_STATUS_CRITICAL_FILE_LOST = -41  # 程序运行所必须的文件丢失。
CAMERA_STATUS_SENSOR_ID_DISMATCH = -42  # 固件和程序不匹配，原因是下载了错误的固件。
CAMERA_STATUS_OUT_OF_RANGE = -43  # 参数超出有效范围。   
CAMERA_STATUS_REGISTRY_ERROR = -44  # 安装程序注册错误。请重新安装程序，或者运行安装目录Setup/Installer.exe
CAMERA_STATUS_ACCESS_DENY = -45  # 禁止访问。指定相机已经被其他程序占用时，再申请访问该相机，会返回该状态。(一个相机不能被多个程序同时访问) 
#AIA的标准兼容的错误码
CAMERA_AIA_PACKET_RESEND = 0x0100 #该帧需要重传
CAMERA_AIA_NOT_IMPLEMENTED = 0x8001 #设备不支持的命令
CAMERA_AIA_INVALID_PARAMETER = 0x8002 #命令参数非法
CAMERA_AIA_INVALID_ADDRESS = 0x8003 #不可访问的地址
CAMERA_AIA_WRITE_PROTECT = 0x8004 #访问的对象不可写
CAMERA_AIA_BAD_ALIGNMENT = 0x8005 #访问的地址没有按照要求对齐
CAMERA_AIA_ACCESS_DENIED = 0x8006 #没有访问权限
CAMERA_AIA_BUSY = 0x8007 #命令正在处理中
CAMERA_AIA_DEPRECATED = 0x8008 #0x8008-0x0800B  0x800F  该指令已经废弃
CAMERA_AIA_PACKET_UNAVAILABLE = 0x800C #包无效
CAMERA_AIA_DATA_OVERRUN = 0x800D #数据溢出，通常是收到的数据比需要的多
CAMERA_AIA_INVALID_HEADER = 0x800E #数据包头部中某些区域与协议不匹配
CAMERA_AIA_PACKET_NOT_YET_AVAILABLE = 0x8010 #图像分包数据还未准备好，多用于触发模式，应用程序访问超时
CAMERA_AIA_PACKET_AND_PREV_REMOVED_FROM_MEMORY = 0x8011 #需要访问的分包已经不存在。多用于重传时数据已经不在缓冲区中
CAMERA_AIA_PACKET_REMOVED_FROM_MEMORY = 0x8012 #CAMERA_AIA_PACKET_AND_PREV_REMOVED_FROM_MEMORY
CAMERA_AIA_NO_REF_TIME = 0x0813 #没有参考时钟源。多用于时间同步的命令执行时
CAMERA_AIA_PACKET_TEMPORARILY_UNAVAILABLE = 0x0814 #由于信道带宽问题，当前分包暂时不可用，需稍后进行访问
CAMERA_AIA_OVERFLOW = 0x0815 #设备端数据溢出，通常是队列已满
CAMERA_AIA_ACTION_LATE = 0x0816 #命令执行已经超过有效的指定时间
CAMERA_AIA_ERROR = 0x8FFF   #错误

# 图像格式定义
CAMERA_MEDIA_TYPE_MONO = 0x01000000
CAMERA_MEDIA_TYPE_RGB = 0x02000000
CAMERA_MEDIA_TYPE_COLOR = 0x02000000
CAMERA_MEDIA_TYPE_OCCUPY1BIT = 0x00010000
CAMERA_MEDIA_TYPE_OCCUPY2BIT = 0x00020000
CAMERA_MEDIA_TYPE_OCCUPY4BIT = 0x00040000
CAMERA_MEDIA_TYPE_OCCUPY8BIT = 0x00080000
CAMERA_MEDIA_TYPE_OCCUPY10BIT = 0x000A0000
CAMERA_MEDIA_TYPE_OCCUPY12BIT = 0x000C0000
CAMERA_MEDIA_TYPE_OCCUPY16BIT = 0x00100000
CAMERA_MEDIA_TYPE_OCCUPY24BIT = 0x00180000
CAMERA_MEDIA_TYPE_OCCUPY32BIT = 0x00200000
CAMERA_MEDIA_TYPE_OCCUPY36BIT = 0x00240000
CAMERA_MEDIA_TYPE_OCCUPY48BIT = 0x00300000
CAMERA_MEDIA_TYPE_EFFECTIVE_PIXEL_SIZE_MASK = 0x00FF0000
CAMERA_MEDIA_TYPE_EFFECTIVE_PIXEL_SIZE_SHIFT = 16
CAMERA_MEDIA_TYPE_ID_MASK = 0x0000FFFF
CAMERA_MEDIA_TYPE_COUNT = 0x46

#mono
CAMERA_MEDIA_TYPE_MONO1P = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY1BIT | 0x0037)
CAMERA_MEDIA_TYPE_MONO2P = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY2BIT | 0x0038)
CAMERA_MEDIA_TYPE_MONO4P = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY4BIT | 0x0039)
CAMERA_MEDIA_TYPE_MONO8 = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY8BIT | 0x0001)
CAMERA_MEDIA_TYPE_MONO8S = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY8BIT | 0x0002)
CAMERA_MEDIA_TYPE_MONO10 = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0003)
CAMERA_MEDIA_TYPE_MONO10_PACKED = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0004)
CAMERA_MEDIA_TYPE_MONO12 = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0005)
CAMERA_MEDIA_TYPE_MONO12_PACKED = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0006)
CAMERA_MEDIA_TYPE_MONO14 = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0025)
CAMERA_MEDIA_TYPE_MONO16 = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0007)

# Bayer
CAMERA_MEDIA_TYPE_BAYGR8 = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY8BIT | 0x0008)
CAMERA_MEDIA_TYPE_BAYRG8 = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY8BIT | 0x0009)
CAMERA_MEDIA_TYPE_BAYGB8 = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY8BIT | 0x000A)
CAMERA_MEDIA_TYPE_BAYBG8 = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY8BIT | 0x000B)

CAMERA_MEDIA_TYPE_BAYGR10_MIPI = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY10BIT | 0x0026)
CAMERA_MEDIA_TYPE_BAYRG10_MIPI = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY10BIT | 0x0027)
CAMERA_MEDIA_TYPE_BAYGB10_MIPI = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY10BIT | 0x0028)
CAMERA_MEDIA_TYPE_BAYBG10_MIPI = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY10BIT | 0x0029)

CAMERA_MEDIA_TYPE_BAYGR10 = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x000C)
CAMERA_MEDIA_TYPE_BAYRG10 = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x000D)
CAMERA_MEDIA_TYPE_BAYGB10 = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x000E)
CAMERA_MEDIA_TYPE_BAYBG10 = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x000F)

CAMERA_MEDIA_TYPE_BAYGR12 = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0010)
CAMERA_MEDIA_TYPE_BAYRG12 = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0011)
CAMERA_MEDIA_TYPE_BAYGB12 = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0012)
CAMERA_MEDIA_TYPE_BAYBG12 = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0013)

CAMERA_MEDIA_TYPE_BAYGR10_PACKED = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0026)
CAMERA_MEDIA_TYPE_BAYRG10_PACKED = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0027)
CAMERA_MEDIA_TYPE_BAYGB10_PACKED = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0028)
CAMERA_MEDIA_TYPE_BAYBG10_PACKED = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0029)

CAMERA_MEDIA_TYPE_BAYGR12_PACKED = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x002A)
CAMERA_MEDIA_TYPE_BAYRG12_PACKED = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x002B)
CAMERA_MEDIA_TYPE_BAYGB12_PACKED = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x002C)
CAMERA_MEDIA_TYPE_BAYBG12_PACKED = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x002D)

CAMERA_MEDIA_TYPE_BAYGR16 = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x002E)
CAMERA_MEDIA_TYPE_BAYRG16 = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x002F)
CAMERA_MEDIA_TYPE_BAYGB16 = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0030)
CAMERA_MEDIA_TYPE_BAYBG16 = (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0031)

# RGB
CAMERA_MEDIA_TYPE_RGB8 = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY24BIT | 0x0014)
CAMERA_MEDIA_TYPE_BGR8 = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY24BIT | 0x0015)
CAMERA_MEDIA_TYPE_RGBA8 = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY32BIT | 0x0016)
CAMERA_MEDIA_TYPE_BGRA8 = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY32BIT | 0x0017)
CAMERA_MEDIA_TYPE_RGB10 = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY48BIT | 0x0018)
CAMERA_MEDIA_TYPE_BGR10 = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY48BIT | 0x0019)
CAMERA_MEDIA_TYPE_RGB12 = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY48BIT | 0x001A)
CAMERA_MEDIA_TYPE_BGR12 = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY48BIT | 0x001B)
CAMERA_MEDIA_TYPE_RGB16 = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY48BIT | 0x0033)
CAMERA_MEDIA_TYPE_RGB10V1_PACKED = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY32BIT | 0x001C)
CAMERA_MEDIA_TYPE_RGB10P32 = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY32BIT | 0x001D)
CAMERA_MEDIA_TYPE_RGB12V1_PACKED = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY36BIT | 0X0034)
CAMERA_MEDIA_TYPE_RGB565P = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0035)
CAMERA_MEDIA_TYPE_BGR565P = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0X0036)

# YUV and YCbCr
CAMERA_MEDIA_TYPE_YUV411_8_UYYVYY = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x001E)
CAMERA_MEDIA_TYPE_YUV422_8_UYVY = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x001F)
CAMERA_MEDIA_TYPE_YUV422_8 = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0032)
CAMERA_MEDIA_TYPE_YUV8_UYV = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY24BIT | 0x0020)
CAMERA_MEDIA_TYPE_YCBCR8_CBYCR = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY24BIT | 0x003A)
#CAMERA_MEDIA_TYPE_YCBCR422_8 : YYYYCbCrCbCr
CAMERA_MEDIA_TYPE_YCBCR422_8 = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x003B)
CAMERA_MEDIA_TYPE_YCBCR422_8_CBYCRY = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0043)
CAMERA_MEDIA_TYPE_YCBCR411_8_CBYYCRYY = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x003C)
CAMERA_MEDIA_TYPE_YCBCR601_8_CBYCR = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY24BIT | 0x003D)
CAMERA_MEDIA_TYPE_YCBCR601_422_8 = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x003E)
CAMERA_MEDIA_TYPE_YCBCR601_422_8_CBYCRY = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0044)
CAMERA_MEDIA_TYPE_YCBCR601_411_8_CBYYCRYY = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x003F)
CAMERA_MEDIA_TYPE_YCBCR709_8_CBYCR = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY24BIT | 0x0040)
CAMERA_MEDIA_TYPE_YCBCR709_422_8 = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0041)
CAMERA_MEDIA_TYPE_YCBCR709_422_8_CBYCRY = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0045)
CAMERA_MEDIA_TYPE_YCBCR709_411_8_CBYYCRYY = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0042)

# RGB Planar
CAMERA_MEDIA_TYPE_RGB8_PLANAR = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY24BIT | 0x0021)
CAMERA_MEDIA_TYPE_RGB10_PLANAR = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY48BIT | 0x0022)
CAMERA_MEDIA_TYPE_RGB12_PLANAR = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY48BIT | 0x0023)
CAMERA_MEDIA_TYPE_RGB16_PLANAR = (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY48BIT | 0x0024)

# 保存格式
FILE_JPG = 1
FILE_BMP = 2
FILE_RAW = 4
FILE_PNG = 8 
FILE_BMP_8BIT = 16
FILE_PNG_8BIT = 32
FILE_RAW_16BIT = 64

# 触发信号
EXT_TRIG_LEADING_EDGE = 0
EXT_TRIG_TRAILING_EDGE = 1
EXT_TRIG_HIGH_LEVEL = 2
EXT_TRIG_LOW_LEVEL = 3
EXT_TRIG_DOUBLE_EDGE = 4

# IO模式
IOMODE_TRIG_INPUT = 0
IOMODE_STROBE_OUTPUT = 1
IOMODE_GP_INPUT = 2
IOMODE_GP_OUTPUT = 3
IOMODE_PWM_OUTPUT = 4


# 相机操作异常信息
class CameraException(Exception):
	"""docstring for CameraException"""
	def __init__(self, error_code):
		super(CameraException, self).__init__()
		self.error_code = error_code
		self.message = CameraGetErrorString(error_code)

	def __str__(self):
		return 'error_code:{} message:{}'.format(self.error_code, self.message)

class MvStructure(Structure):
	def __str__(self):
		strs = []
		for field in self._fields_:
			name = field[0]
			value = getattr(self, name)
			if isinstance(value, type(b'')):
				value = _string_buffer_to_str(value)
			strs.append("{}:{}".format(name, value))
		return '\n'.join(strs)

# 相机的设备信息，只读信息，请勿修改
class tSdkCameraDevInfo(MvStructure):
	_fields_ = [("acProductSeries", c_char * 32), #产品系列
				("acProductName", c_char * 32), #产品名称
				("acFriendlyName", c_char * 32), #产品昵称
				("acLinkName", c_char * 32), #内核符号连接名，内部使用
				("acDriverVersion", c_char * 32), #驱动版本
				("acSensorType", c_char * 32), #sensor类型
				("acPortType", c_char * 32), #接口类型
				("acSn", c_char * 32), #产品唯一序列号
				("uInstance", c_uint)] #该型号相机在该电脑上的实例索引号，用于区分同型号多相机

	def GetProductSeries(self):
		return _string_buffer_to_str(self.acProductSeries)
	def GetProductName(self):
		return _string_buffer_to_str(self.acProductName)
	def GetFriendlyName(self):
		return _string_buffer_to_str(self.acFriendlyName)
	def GetLinkName(self):
		return _string_buffer_to_str(self.acLinkName)
	def GetDriverVersion(self):
		return _string_buffer_to_str(self.acDriverVersion)
	def GetSensorType(self):
		return _string_buffer_to_str(self.acSensorType)
	def GetPortType(self):
		return _string_buffer_to_str(self.acPortType)
	def GetSn(self):
		return _string_buffer_to_str(self.acSn)

# 相机的分辨率设定范围
class tSdkResolutionRange(MvStructure):
	_fields_ = [("iHeightMax", c_int), 	#图像最大高度
				("iHeightMin", c_int), 	#图像最小高度
				("iWidthMax", c_int), 	#图像最大宽度
				("iWidthMin", c_int), 	#图像最小宽度
				("uSkipModeMask", c_uint), 		#SKIP模式掩码，为0，表示不支持SKIP 。bit0为1,表示支持SKIP 2x2 bit1为1，表示支持SKIP 3x3....
				("uBinSumModeMask", c_uint), 	#BIN(求和)模式掩码，为0，表示不支持BIN 。bit0为1,表示支持BIN 2x2 bit1为1，表示支持BIN 3x3....
				("uBinAverageModeMask", c_uint),#BIN(求均值)模式掩码，为0，表示不支持BIN 。bit0为1,表示支持BIN 2x2 bit1为1，表示支持BIN 3x3....
				("uResampleMask", c_uint)] 		#硬件重采样的掩码

#相机的分辨率描述
class tSdkImageResolution(MvStructure):
	_fields_ = [
		("iIndex", c_int),                # 索引号，[0,N]表示预设的分辨率(N 为预设分辨率的最大个数，一般不超过20),OXFF 表示自定义分辨率(ROI)
		("acDescription", c_char * 32),   # 该分辨率的描述信息。仅预设分辨率时该信息有效。自定义分辨率可忽略该信息
		("uBinSumMode", c_uint),          # BIN(求和)的模式,范围不能超过tSdkResolutionRange中uBinSumModeMask
		("uBinAverageMode", c_uint),      # BIN(求均值)的模式,范围不能超过tSdkResolutionRange中uBinAverageModeMask
		("uSkipMode", c_uint),            # 是否SKIP的尺寸，为0表示禁止SKIP模式，范围不能超过tSdkResolutionRange中uSkipModeMask
		("uResampleMask", c_uint),        # 硬件重采样的掩码
		("iHOffsetFOV", c_int),        # 采集视场相对于Sensor最大视场左上角的垂直偏移
		("iVOffsetFOV", c_int),        # 采集视场相对于Sensor最大视场左上角的水平偏移
		("iWidthFOV", c_int),          # 采集视场的宽度 
		("iHeightFOV", c_int),         # 采集视场的高度
		("iWidth", c_int),             # 相机最终输出的图像的宽度
		("iHeight", c_int),            # 相机最终输出的图像的高度
		("iWidthZoomHd", c_int),       # 硬件缩放的宽度,不需要进行此操作的分辨率，此变量设置为0.
		("iHeightZoomHd", c_int),      # 硬件缩放的高度,不需要进行此操作的分辨率，此变量设置为0.
		("iWidthZoomSw", c_int),       # 软件缩放的宽度,不需要进行此操作的分辨率，此变量设置为0.
		("iHeightZoomSw", c_int),      # 软件缩放的高度,不需要进行此操作的分辨率，此变量设置为0.
	]

	def GetDescription(self):
		return _string_buffer_to_str(self.acDescription)

#相机白平衡模式描述信息
class tSdkColorTemperatureDes(MvStructure):
	_fields_ = [
		("iIndex", c_int),				# 模式索引号
		("acDescription", c_char * 32), # 描述信息
	]

	def GetDescription(self):
		return _string_buffer_to_str(self.acDescription)

#相机帧率描述信息
class tSdkFrameSpeed(MvStructure):
	_fields_ = [
		("iIndex", c_int),				# 帧率索引号，一般0对应于低速模式，1对应于普通模式，2对应于高速模式      
		("acDescription", c_char * 32), # 描述信息
	]

	def GetDescription(self):
		return _string_buffer_to_str(self.acDescription)

#相机曝光功能范围定义
class tSdkExpose(MvStructure):
	_fields_ = [
		("uiTargetMin", c_uint),       #自动曝光亮度目标最小值
		("uiTargetMax", c_uint),       #自动曝光亮度目标最大值
		("uiAnalogGainMin", c_uint),   #模拟增益的最小值，单位为fAnalogGainStep中定义      
		("uiAnalogGainMax", c_uint),   #模拟增益的最大值，单位为fAnalogGainStep中定义        
		("fAnalogGainStep", c_float),  #模拟增益每增加1，对应的增加的放大倍数。例如，uiAnalogGainMin一般为16，fAnalogGainStep一般为0.125，那么最小放大倍数就是16*0.125 = 2倍
		("uiExposeTimeMin", c_uint),   #手动模式下，曝光时间的最小值，单位:行。根据CameraGetExposureLineTime可以获得一行对应的时间(微秒),从而得到整帧的曝光时间    
		("uiExposeTimeMax", c_uint),   #手动模式下，曝光时间的最大值，单位:行
	]

#触发模式描述
class tSdkTrigger(MvStructure):
	_fields_ = [
		("iIndex", c_int),				# 模式索引号      
		("acDescription", c_char * 32), # 描述信息
	]

	def GetDescription(self):
		return _string_buffer_to_str(self.acDescription)

#传输分包大小描述(主要是针对网络相机有效)
class tSdkPackLength(MvStructure):
	_fields_ = [
		("iIndex", c_int),				# 模式索引号      
		("acDescription", c_char * 32), # 描述信息
		("iPackSize", c_uint),
	]

	def GetDescription(self):
		return _string_buffer_to_str(self.acDescription)

#预设的LUT表描述
class tSdkPresetLut(MvStructure):
	_fields_ = [
		("iIndex", c_int),				# 编号
		("acDescription", c_char * 32), # 描述信息
	]

	def GetDescription(self):
		return _string_buffer_to_str(self.acDescription)

#AE算法描述
class tSdkAeAlgorithm(MvStructure):
	_fields_ = [
		("iIndex", c_int),				# 编号
		("acDescription", c_char * 32), # 描述信息
	]

	def GetDescription(self):
		return _string_buffer_to_str(self.acDescription)

#RAW转RGB算法描述
class tSdkBayerDecodeAlgorithm(MvStructure):
	_fields_ = [
		("iIndex", c_int),				# 编号
		("acDescription", c_char * 32), # 描述信息
	]

	def GetDescription(self):
		return _string_buffer_to_str(self.acDescription)

#帧率统计信息
class tSdkFrameStatistic(MvStructure):
	_fields_ = [
		("iTotal", c_int),        #当前采集的总帧数（包括错误帧）
		("iCapture", c_int),      #当前采集的有效帧的数量    
		("iLost", c_int),         #当前丢帧的数量    
	]

#相机输出的图像数据格式
class tSdkMediaType(MvStructure):
	_fields_ = [
		("iIndex", c_int),				# 格式种类编号
		("acDescription", c_char * 32), # 描述信息
		("iMediaType", c_uint),			# 对应的图像格式编码，如CAMERA_MEDIA_TYPE_BAYGR8。
	]

	def GetDescription(self):
		return _string_buffer_to_str(self.acDescription)

#伽马的设定范围
class tGammaRange(MvStructure):
	_fields_ = [
		("iMin", c_int),       #最小值
		("iMax", c_int),       #最大值
	]

#对比度的设定范围
class tContrastRange(MvStructure):
	_fields_ = [
		("iMin", c_int),       #最小值
		("iMax", c_int),       #最大值
	]

#RGB三通道数字增益的设定范围
class tRgbGainRange(MvStructure):
	_fields_ = [
		("iRGainMin", c_int),   #红色增益的最小值
		("iRGainMax", c_int),   #红色增益的最大值
		("iGGainMin", c_int),   #绿色增益的最小值
		("iGGainMax", c_int),   #绿色增益的最大值
		("iBGainMin", c_int),   #蓝色增益的最小值
		("iBGainMax", c_int),   #蓝色增益的最大值
	]

#饱和度设定的范围
class tSaturationRange(MvStructure):
	_fields_ = [
		("iMin", c_int),       #最小值
		("iMax", c_int),       #最大值
	]

#锐化的设定范围
class tSharpnessRange(MvStructure):
	_fields_ = [
		("iMin", c_int),       #最小值
		("iMax", c_int),       #最大值
	]

#ISP模块的使能信息
class tSdkIspCapacity(MvStructure):
	_fields_ = [
		("bMonoSensor", c_int),        #表示该型号相机是否为黑白相机,如果是黑白相机，则颜色相关的功能都无法调节
		("bWbOnce", c_int),            #表示该型号相机是否支持手动白平衡功能  
		("bAutoWb", c_int),            #表示该型号相机是否支持自动白平衡功能
		("bAutoExposure", c_int),      #表示该型号相机是否支持自动曝光功能
		("bManualExposure", c_int),    #表示该型号相机是否支持手动曝光功能
		("bAntiFlick", c_int),         #表示该型号相机是否支持抗频闪功能
		("bDeviceIsp", c_int),         #表示该型号相机是否支持硬件ISP功能
		("bForceUseDeviceIsp", c_int), #bDeviceIsp和bForceUseDeviceIsp同时为TRUE时，表示强制只用硬件ISP，不可取消。
		("bZoomHD", c_int),            #相机硬件是否支持图像缩放输出(只能是缩小)。
	]

# 定义整合的设备描述信息，这些信息可以用于动态构建UI
class tSdkCameraCapbility(MvStructure):
	_fields_ = [
		("pTriggerDesc", POINTER(tSdkTrigger)),
		("iTriggerDesc", c_int),	#触发模式的个数，即pTriggerDesc数组的大小
		("pImageSizeDesc", POINTER(tSdkImageResolution)),
		("iImageSizeDesc", c_int),	#预设分辨率的个数，即pImageSizeDesc数组的大小 
		("pClrTempDesc", POINTER(tSdkColorTemperatureDes)),
		("iClrTempDesc", c_int),	#预设色温个数
		("pMediaTypeDesc", POINTER(tSdkMediaType)),
		("iMediaTypeDesc", c_int),	#相机输出图像格式的种类个数，即pMediaTypeDesc数组的大小。
		("pFrameSpeedDesc", POINTER(tSdkFrameSpeed)), #可调节帧速类型，对应界面上普通 高速 和超级三种速度设置
		("iFrameSpeedDesc", c_int), #可调节帧速类型的个数，即pFrameSpeedDesc数组的大小。
		("pPackLenDesc", POINTER(tSdkPackLength)), #传输包长度，一般用于网络设备
		("iPackLenDesc", c_int), #可供选择的传输分包长度的个数，即pPackLenDesc数组的大小。 
		("iOutputIoCounts", c_int),        #可编程输出IO的个数
		("iInputIoCounts", c_int),         #可编程输入IO的个数
		("pPresetLutDesc", POINTER(tSdkPresetLut)), #相机预设的LUT表
		("iPresetLut", c_int),             #相机预设的LUT表的个数，即pPresetLutDesc数组的大小
		("iUserDataMaxLen", c_int),        #指示该相机中用于保存用户数据区的最大长度。为0表示无。
		("bParamInDevice", c_int),         #指示该设备是否支持从设备中读写参数组。1为支持，0不支持。
		("pAeAlmSwDesc", POINTER(tSdkAeAlgorithm)),#软件自动曝光算法描述
		("iAeAlmSwDesc", c_int),           #软件自动曝光算法个数
		("pAeAlmHdDesc", POINTER(tSdkAeAlgorithm)),#硬件自动曝光算法描述，为NULL表示不支持硬件自动曝光
		("iAeAlmHdDesc", c_int),           #硬件自动曝光算法个数，为0表示不支持硬件自动曝光
		("pBayerDecAlmSwDesc", POINTER(tSdkBayerDecodeAlgorithm)),#软件Bayer转换为RGB数据的算法描述
		("iBayerDecAlmSwDesc", c_int),     #软件Bayer转换为RGB数据的算法个数
		("pBayerDecAlmHdDesc", POINTER(tSdkBayerDecodeAlgorithm)),#硬件Bayer转换为RGB数据的算法描述，为NULL表示不支持
		("iBayerDecAlmHdDesc", c_int),     #硬件Bayer转换为RGB数据的算法个数，为0表示不支持

		# 图像参数的调节范围定义,用于动态构建UI
		("sExposeDesc", tSdkExpose),      #曝光的范围值
		("sResolutionRange", tSdkResolutionRange), #分辨率范围描述  
		("sRgbGainRange", tRgbGainRange),    #图像数字增益范围描述  
		("sSaturationRange", tSaturationRange), #饱和度范围描述  
		("sGammaRange", tGammaRange),      #伽马范围描述  
		("sContrastRange", tContrastRange),   #对比度范围描述  
		("sSharpnessRange", tSharpnessRange),  #锐化范围描述  
		("sIspCapacity", tSdkIspCapacity),     #ISP能力描述
	]

#图像帧头信息
class tSdkFrameHead(MvStructure):
	_fields_ = [
		("uiMediaType", c_uint),      # 图像格式,Image Format
		("uBytes", c_uint),           # 图像数据字节数,Total bytes
		("iWidth", c_int),            # 宽度 Image height
		("iHeight", c_int),           # 高度 Image width
		("iWidthZoomSw", c_int),      # 软件缩放的宽度,不需要进行软件裁剪的图像，此变量设置为0.
		("iHeightZoomSw", c_int),     # 软件缩放的高度,不需要进行软件裁剪的图像，此变量设置为0.
		("bIsTrigger", c_int),        # 指示是否为触发帧 is trigger 
		("uiTimeStamp", c_uint),      # 该帧的采集时间，单位0.1毫秒 
		("uiExpTime", c_uint),        # 当前图像的曝光值，单位为微秒us
		("fAnalogGain", c_float),     # 当前图像的模拟增益倍数
		("iGamma", c_int),            # 该帧图像的伽马设定值，仅当LUT模式为动态参数生成时有效，其余模式下为-1
		("iContrast", c_int),         # 该帧图像的对比度设定值，仅当LUT模式为动态参数生成时有效，其余模式下为-1
		("iSaturation", c_int),       # 该帧图像的饱和度设定值，对于黑白相机无意义，为0
		("fRgain", c_float),          # 该帧图像处理的红色数字增益倍数，对于黑白相机无意义，为1
		("fGgain", c_float),          # 该帧图像处理的绿色数字增益倍数，对于黑白相机无意义，为1
		("fBgain", c_float),          # 该帧图像处理的蓝色数字增益倍数，对于黑白相机无意义，为1
	]

# Grabber统计信息
class tSdkGrabberStat(MvStructure):
	_fields_ = [
		("Width", c_int),           # 帧图像大小
		("Height", c_int),	        # 帧图像大小
		("Disp", c_int),			# 显示帧数量
		("Capture", c_int),		    # 采集的有效帧的数量
		("Lost", c_int),			# 丢帧的数量
		("Error", c_int),			# 错帧的数量
		("DispFps", c_float),		# 显示帧率
		("CapFps", c_float),		# 捕获帧率
	]

# 方法回调辅助类
class method(object):
	def __init__(self, FuncType):
		super(method, self).__init__()
		self.FuncType = FuncType
		self.cache = {}

	def __call__(self, cb):
		self.cb = cb
		return self

	def __get__(self, obj, objtype):
		try:
			return self.cache[obj]
		except KeyError as e:
			def cl(*args):
				return self.cb(obj, *args)
			r = self.cache[obj] = self.FuncType(cl)
			return r

# 图像捕获的回调函数定义
CAMERA_SNAP_PROC = CALLBACK_FUNC_TYPE(None, c_int, c_void_p, POINTER(tSdkFrameHead), c_void_p)

# 相机连接状态回调
CAMERA_CONNECTION_STATUS_CALLBACK = CALLBACK_FUNC_TYPE(None, c_int, c_uint, c_uint, c_void_p)

# 异步抓图完成回调
pfnCameraGrabberSaveImageComplete = CALLBACK_FUNC_TYPE(None, c_void_p, c_void_p, c_int, c_void_p)

# 帧监听回调
pfnCameraGrabberFrameListener = CALLBACK_FUNC_TYPE(c_int, c_void_p, c_int, c_void_p, POINTER(tSdkFrameHead), c_void_p)

# 采集器图像捕获的回调
pfnCameraGrabberFrameCallback = CALLBACK_FUNC_TYPE(None, c_void_p, c_void_p, POINTER(tSdkFrameHead), c_void_p)

#-----------------------------------函数接口------------------------------------------

# 线程局部存储
_tls = local()

# 存储最后一次SDK调用返回的错误码
def GetLastError():
	try:
		return _tls.last_error
	except AttributeError as e:
		_tls.last_error = 0
		return 0

def SetLastError(err_code):
	_tls.last_error = err_code

def _string_buffer_to_str(buf):
	s = buf if isinstance(buf, type(b'')) else buf.value

	for codec in ('gbk', 'utf-8'):
		try:
			s = s.decode(codec)
			break
		except UnicodeDecodeError as e:
			continue

	if isinstance(s, str):
		return s
	else:
		return s.encode('utf-8')

def _str_to_string_buffer(str):
	if type(str) is type(u''):
		s = str.encode('gbk')
	else:
		s = str.decode('utf-8').encode('gbk')
	return create_string_buffer(s)

def CameraSdkInit(iLanguageSel):
	err_code = _sdk.CameraSdkInit(iLanguageSel)
	SetLastError(err_code)
	return err_code

def CameraEnumerateDevice(MaxCount = 32):
	Nums = c_int(MaxCount)
	pCameraList = (tSdkCameraDevInfo * Nums.value)()
	err_code = _sdk.CameraEnumerateDevice(pCameraList, byref(Nums))
	SetLastError(err_code)
	return pCameraList[0:Nums.value]

def CameraEnumerateDeviceEx():
	return _sdk.CameraEnumerateDeviceEx()

def CameraIsOpened(pCameraInfo):
	pOpened = c_int()
	err_code = _sdk.CameraIsOpened(pCameraInfo, byref(pOpened) )
	SetLastError(err_code)
	return pOpened.value != 0

def CameraInit(pCameraInfo, emParamLoadMode = -1, emTeam = -1):
	pCameraHandle = c_int()
	err_code = _sdk.CameraInit(byref(pCameraInfo), emParamLoadMode, emTeam, byref(pCameraHandle))
	SetLastError(err_code)
	if err_code != 0:
		raise CameraException(err_code)
	return pCameraHandle.value

def CameraInitEx(iDeviceIndex, emParamLoadMode = -1, emTeam = -1):
	pCameraHandle = c_int()
	err_code = _sdk.CameraInitEx(iDeviceIndex, emParamLoadMode, emTeam, byref(pCameraHandle))
	SetLastError(err_code)
	if err_code != 0:
		raise CameraException(err_code)
	return pCameraHandle.value

def CameraInitEx2(CameraName):
	pCameraHandle = c_int()
	err_code = _sdk.CameraInitEx2(_str_to_string_buffer(CameraName), byref(pCameraHandle))
	SetLastError(err_code)
	if err_code != 0:
		raise CameraException(err_code)
	return pCameraHandle.value

def CameraSetCallbackFunction(hCamera, pCallBack, pContext = 0):
	err_code = _sdk.CameraSetCallbackFunction(hCamera, pCallBack, c_void_p(pContext), None)
	SetLastError(err_code)
	return err_code

def CameraUnInit(hCamera):
	err_code = _sdk.CameraUnInit(hCamera)
	SetLastError(err_code)
	return err_code

def CameraGetInformation(hCamera):
	pbuffer = c_char_p()
	err_code = _sdk.CameraGetInformation(hCamera, byref(pbuffer) )
	SetLastError(err_code)
	if err_code == 0 and pbuffer.value is not None:
		return _string_buffer_to_str(pbuffer)
	return ''

def CameraImageProcess(hCamera, pbyIn, pbyOut, pFrInfo):
	err_code = _sdk.CameraImageProcess(hCamera, c_void_p(pbyIn), c_void_p(pbyOut), byref(pFrInfo))
	SetLastError(err_code)
	return err_code

def CameraImageProcessEx(hCamera, pbyIn, pbyOut, pFrInfo, uOutFormat, uReserved):
	err_code = _sdk.CameraImageProcessEx(hCamera, c_void_p(pbyIn), c_void_p(pbyOut), byref(pFrInfo), uOutFormat, uReserved)
	SetLastError(err_code)
	return err_code

def CameraDisplayInit(hCamera, hWndDisplay):
	err_code = _sdk.CameraDisplayInit(hCamera, hWndDisplay)
	SetLastError(err_code)
	return err_code

def CameraDisplayRGB24(hCamera, pFrameBuffer, pFrInfo):
	err_code = _sdk.CameraDisplayRGB24(hCamera, c_void_p(pFrameBuffer), byref(pFrInfo) )
	SetLastError(err_code)
	return err_code

def CameraSetDisplayMode(hCamera, iMode):
	err_code = _sdk.CameraSetDisplayMode(hCamera, iMode)
	SetLastError(err_code)
	return err_code

def CameraSetDisplayOffset(hCamera, iOffsetX, iOffsetY):
	err_code = _sdk.CameraSetDisplayOffset(hCamera, iOffsetX, iOffsetY)
	SetLastError(err_code)
	return err_code

def CameraSetDisplaySize(hCamera, iWidth, iHeight):
	err_code = _sdk.CameraSetDisplaySize(hCamera, iWidth, iHeight)
	SetLastError(err_code)
	return err_code

def CameraGetImageBuffer(hCamera, wTimes):
	pbyBuffer = c_void_p()
	pFrameInfo = tSdkFrameHead()
	err_code = _sdk.CameraGetImageBuffer(hCamera, byref(pFrameInfo), byref(pbyBuffer), wTimes)
	SetLastError(err_code)
	if err_code != 0:
		raise CameraException(err_code)
	return (pbyBuffer.value, pFrameInfo)

def CameraGetImageBufferEx(hCamera, wTimes):
	_sdk.CameraGetImageBufferEx.restype = c_void_p
	piWidth = c_int()
	piHeight = c_int()
	pFrameBuffer = _sdk.CameraGetImageBufferEx(hCamera, byref(piWidth), byref(piHeight), wTimes)
	err_code = CAMERA_STATUS_SUCCESS if pFrameBuffer else CAMERA_STATUS_TIME_OUT
	SetLastError(err_code)
	if pFrameBuffer:
		return (pFrameBuffer, piWidth.value, piHeight.value)
	else:
		raise CameraException(err_code)

def CameraSnapToBuffer(hCamera, wTimes):
	pbyBuffer = c_void_p()
	pFrameInfo = tSdkFrameHead()
	err_code = _sdk.CameraSnapToBuffer(hCamera, byref(pFrameInfo), byref(pbyBuffer), wTimes)
	SetLastError(err_code)
	if err_code != 0:
		raise CameraException(err_code)
	return (pbyBuffer.value, pFrameInfo)

def CameraReleaseImageBuffer(hCamera, pbyBuffer):
	err_code = _sdk.CameraReleaseImageBuffer(hCamera, c_void_p(pbyBuffer) )
	SetLastError(err_code)
	return err_code

def CameraPlay(hCamera):
	err_code = _sdk.CameraPlay(hCamera)
	SetLastError(err_code)
	return err_code

def CameraPause(hCamera):
	err_code = _sdk.CameraPause(hCamera)
	SetLastError(err_code)
	return err_code

def CameraStop(hCamera):
	err_code = _sdk.CameraStop(hCamera)
	SetLastError(err_code)
	return err_code

def CameraInitRecord(hCamera, iFormat, pcSavePath, b2GLimit, dwQuality, iFrameRate):
	err_code = _sdk.CameraInitRecord(hCamera, iFormat, _str_to_string_buffer(pcSavePath), b2GLimit, dwQuality, iFrameRate)
	SetLastError(err_code)
	return err_code

def CameraStopRecord(hCamera):
	err_code = _sdk.CameraStopRecord(hCamera)
	SetLastError(err_code)
	return err_code

def CameraPushFrame(hCamera, pbyImageBuffer, pFrInfo):
	err_code = _sdk.CameraPushFrame(hCamera, c_void_p(pbyImageBuffer), byref(pFrInfo) )
	SetLastError(err_code)
	return err_code

def CameraSaveImage(hCamera, lpszFileName, pbyImageBuffer, pFrInfo, byFileType, byQuality):
	err_code = _sdk.CameraSaveImage(hCamera, _str_to_string_buffer(lpszFileName), c_void_p(pbyImageBuffer), byref(pFrInfo), byFileType, byQuality)
	SetLastError(err_code)
	return err_code

def CameraSaveImageEx(hCamera, lpszFileName, pbyImageBuffer, uImageFormat, iWidth, iHeight, byFileType, byQuality):
	err_code = _sdk.CameraSaveImageEx(hCamera, _str_to_string_buffer(lpszFileName), c_void_p(pbyImageBuffer), uImageFormat, iWidth, iHeight, byFileType, byQuality)
	SetLastError(err_code)
	return err_code

def CameraGetImageResolution(hCamera):
	psCurVideoSize = tSdkImageResolution()
	err_code = _sdk.CameraGetImageResolution(hCamera, byref(psCurVideoSize) )
	SetLastError(err_code)
	return psCurVideoSize

def CameraSetImageResolution(hCamera, pImageResolution):
	err_code = _sdk.CameraSetImageResolution(hCamera, byref(pImageResolution) )
	SetLastError(err_code)
	return err_code

def CameraSetImageResolutionEx(hCamera, iIndex, Mode, ModeSize, x, y, width, height, ZoomWidth, ZoomHeight):
	err_code = _sdk.CameraSetImageResolutionEx(hCamera, iIndex, Mode, ModeSize, x, y, width, height, ZoomWidth, ZoomHeight)
	SetLastError(err_code)
	return err_code

def CameraGetMediaType(hCamera):
	piMediaType = c_int()
	err_code = _sdk.CameraGetMediaType(hCamera, byref(piMediaType) )
	SetLastError(err_code)
	return piMediaType.value

def CameraSetMediaType(hCamera, iMediaType):
	err_code = _sdk.CameraSetMediaType(hCamera, iMediaType)
	SetLastError(err_code)
	return err_code

def CameraSetAeState(hCamera, bAeState):
	err_code = _sdk.CameraSetAeState(hCamera, bAeState)
	SetLastError(err_code)
	return err_code

def CameraGetAeState(hCamera):
	pAeState = c_int()
	err_code = _sdk.CameraGetAeState(hCamera, byref(pAeState) )
	SetLastError(err_code)
	return pAeState.value

def CameraSetSharpness(hCamera, iSharpness):
	err_code = _sdk.CameraSetSharpness(hCamera, iSharpness)
	SetLastError(err_code)
	return err_code

def CameraGetSharpness(hCamera):
	piSharpness = c_int()
	err_code = _sdk.CameraGetSharpness(hCamera, byref(piSharpness) )
	SetLastError(err_code)
	return piSharpness.value

def CameraSetLutMode(hCamera, emLutMode):
	err_code = _sdk.CameraSetLutMode(hCamera, emLutMode)
	SetLastError(err_code)
	return err_code

def CameraGetLutMode(hCamera):
	pemLutMode = c_int()
	err_code = _sdk.CameraGetLutMode(hCamera, byref(pemLutMode) )
	SetLastError(err_code)
	return pemLutMode.value

def CameraSelectLutPreset(hCamera, iSel):
	err_code = _sdk.CameraSelectLutPreset(hCamera, iSel)
	SetLastError(err_code)
	return err_code

def CameraGetLutPresetSel(hCamera):
	piSel = c_int()
	err_code = _sdk.CameraGetLutPresetSel(hCamera, byref(piSel) )
	SetLastError(err_code)
	return piSel.value

def CameraSetCustomLut(hCamera, iChannel, pLut):
	pLutNative = (c_ushort * 4096)(*pLut)
	err_code = _sdk.CameraSetCustomLut(hCamera, iChannel, pLutNative)
	SetLastError(err_code)
	return err_code

def CameraGetCustomLut(hCamera, iChannel):
	pLutNative = (c_ushort * 4096)()
	err_code = _sdk.CameraGetCustomLut(hCamera, iChannel, pLutNative)
	SetLastError(err_code)
	return pLutNative[:]

def CameraGetCurrentLut(hCamera, iChannel):
	pLutNative = (c_ushort * 4096)()
	err_code = _sdk.CameraGetCurrentLut(hCamera, iChannel, pLutNative)
	SetLastError(err_code)
	return pLutNative[:]

def CameraSetWbMode(hCamera, bAuto):
	err_code = _sdk.CameraSetWbMode(hCamera, bAuto)
	SetLastError(err_code)
	return err_code

def CameraGetWbMode(hCamera):
	pbAuto = c_int()
	err_code = _sdk.CameraGetWbMode(hCamera, byref(pbAuto) )
	SetLastError(err_code)
	return pbAuto.value

def CameraSetPresetClrTemp(hCamera, iSel):
	err_code = _sdk.CameraSetPresetClrTemp(hCamera, iSel)
	SetLastError(err_code)
	return err_code

def CameraGetPresetClrTemp(hCamera):
	piSel = c_int()
	err_code = _sdk.CameraGetPresetClrTemp(hCamera, byref(piSel) )
	SetLastError(err_code)
	return piSel.value

def CameraSetUserClrTempGain(hCamera, iRgain, iGgain, iBgain):
	err_code = _sdk.CameraSetUserClrTempGain(hCamera, iRgain, iGgain, iBgain)
	SetLastError(err_code)
	return err_code

def CameraGetUserClrTempGain(hCamera):
	piRgain = c_int()
	piGgain = c_int()
	piBgain = c_int()
	err_code = _sdk.CameraGetUserClrTempGain(hCamera, byref(piRgain), byref(piGgain), byref(piBgain) )
	SetLastError(err_code)
	return (piRgain.value, piGgain.value, piBgain.value)

def CameraSetUserClrTempMatrix(hCamera, pMatrix):
	pMatrixNative = (c_float * 9)(*pMatrix)
	err_code = _sdk.CameraSetUserClrTempMatrix(hCamera, pMatrixNative)
	SetLastError(err_code)
	return err_code

def CameraGetUserClrTempMatrix(hCamera):
	pMatrixNative = (c_float * 9)()
	err_code = _sdk.CameraGetUserClrTempMatrix(hCamera, pMatrixNative)
	SetLastError(err_code)
	return pMatrixNative[:]

def CameraSetClrTempMode(hCamera, iMode):
	err_code = _sdk.CameraSetClrTempMode(hCamera, iMode)
	SetLastError(err_code)
	return err_code

def CameraGetClrTempMode(hCamera):
	piMode = c_int()
	err_code = _sdk.CameraGetClrTempMode(hCamera, byref(piMode) )
	SetLastError(err_code)
	return piMode.value

def CameraSetOnceWB(hCamera):
	err_code = _sdk.CameraSetOnceWB(hCamera)
	SetLastError(err_code)
	return err_code

def CameraSetOnceBB(hCamera):
	err_code = _sdk.CameraSetOnceBB(hCamera)
	SetLastError(err_code)
	return err_code

def CameraSetAeTarget(hCamera, iAeTarget):
	err_code = _sdk.CameraSetAeTarget(hCamera, iAeTarget)
	SetLastError(err_code)
	return err_code

def CameraGetAeTarget(hCamera):
	piAeTarget = c_int()
	err_code = _sdk.CameraGetAeTarget(hCamera, byref(piAeTarget) )
	SetLastError(err_code)
	return piAeTarget.value

def CameraSetAeExposureRange(hCamera, fMinExposureTime, fMaxExposureTime):
	err_code = _sdk.CameraSetAeExposureRange(hCamera, c_double(fMinExposureTime), c_double(fMaxExposureTime) )
	SetLastError(err_code)
	return err_code

def CameraGetAeExposureRange(hCamera):
	fMinExposureTime = c_double()
	fMaxExposureTime = c_double()
	err_code = _sdk.CameraGetAeExposureRange(hCamera, byref(fMinExposureTime), byref(fMaxExposureTime) )
	SetLastError(err_code)
	return (fMinExposureTime.value, fMaxExposureTime.value)

def CameraSetAeAnalogGainRange(hCamera, iMinAnalogGain, iMaxAnalogGain):
	err_code = _sdk.CameraSetAeAnalogGainRange(hCamera, iMinAnalogGain, iMaxAnalogGain)
	SetLastError(err_code)
	return err_code

def CameraGetAeAnalogGainRange(hCamera):
	iMinAnalogGain = c_int()
	iMaxAnalogGain = c_int()
	err_code = _sdk.CameraGetAeAnalogGainRange(hCamera, byref(iMinAnalogGain), byref(iMaxAnalogGain) )
	SetLastError(err_code)
	return (iMinAnalogGain.value, iMaxAnalogGain.value)

def CameraSetAeThreshold(hCamera, iThreshold):
	err_code = _sdk.CameraSetAeThreshold(hCamera, iThreshold)
	SetLastError(err_code)
	return err_code

def CameraGetAeThreshold(hCamera):
	iThreshold = c_int()
	err_code = _sdk.CameraGetAeThreshold(hCamera, byref(iThreshold))
	SetLastError(err_code)
	return iThreshold.value

def CameraSetExposureTime(hCamera, fExposureTime):
	err_code = _sdk.CameraSetExposureTime(hCamera, c_double(fExposureTime) )
	SetLastError(err_code)
	return err_code

def CameraGetExposureLineTime(hCamera):
	pfLineTime = c_double()
	err_code = _sdk.CameraGetExposureLineTime(hCamera, byref(pfLineTime))
	SetLastError(err_code)
	return pfLineTime.value

def CameraGetExposureTime(hCamera):
	pfExposureTime = c_double()
	err_code = _sdk.CameraGetExposureTime(hCamera, byref(pfExposureTime))
	SetLastError(err_code)
	return pfExposureTime.value

def CameraGetExposureTimeRange(hCamera):
	pfMin = c_double()
	pfMax = c_double()
	pfStep = c_double()
	err_code = _sdk.CameraGetExposureTimeRange(hCamera, byref(pfMin), byref(pfMax), byref(pfStep))
	SetLastError(err_code)
	return (pfMin.value, pfMax.value, pfStep.value)

def CameraSetAnalogGain(hCamera, iAnalogGain):
	err_code = _sdk.CameraSetAnalogGain(hCamera, iAnalogGain)
	SetLastError(err_code)
	return err_code

def CameraGetAnalogGain(hCamera):
	piAnalogGain = c_int()
	err_code = _sdk.CameraGetAnalogGain(hCamera, byref(piAnalogGain))
	SetLastError(err_code)
	return piAnalogGain.value

def CameraSetGain(hCamera, iRGain, iGGain, iBGain):
	err_code = _sdk.CameraSetGain(hCamera, iRGain, iGGain, iBGain)
	SetLastError(err_code)
	return err_code

def CameraGetGain(hCamera):
	piRGain = c_int()
	piGGain = c_int()
	piBGain = c_int()
	err_code = _sdk.CameraGetGain(hCamera, byref(piRGain), byref(piGGain), byref(piBGain))
	SetLastError(err_code)
	return (piRGain.value, piGGain.value, piBGain.value)

def CameraSetGamma(hCamera, iGamma):
	err_code = _sdk.CameraSetGamma(hCamera, iGamma)
	SetLastError(err_code)
	return err_code

def CameraGetGamma(hCamera):
	piGamma = c_int()
	err_code = _sdk.CameraGetGamma(hCamera, byref(piGamma))
	SetLastError(err_code)
	return piGamma.value

def CameraSetContrast(hCamera, iContrast):
	err_code = _sdk.CameraSetContrast(hCamera, iContrast)
	SetLastError(err_code)
	return err_code

def CameraGetContrast(hCamera):
	piContrast = c_int()
	err_code = _sdk.CameraGetContrast(hCamera, byref(piContrast))
	SetLastError(err_code)
	return piContrast.value

def CameraSetSaturation(hCamera, iSaturation):
	err_code = _sdk.CameraSetSaturation(hCamera, iSaturation)
	SetLastError(err_code)
	return err_code

def CameraGetSaturation(hCamera):
	piSaturation = c_int()
	err_code = _sdk.CameraGetSaturation(hCamera, byref(piSaturation))
	SetLastError(err_code)
	return piSaturation.value

def CameraSetMonochrome(hCamera, bEnable):
	err_code = _sdk.CameraSetMonochrome(hCamera, bEnable)
	SetLastError(err_code)
	return err_code

def CameraGetMonochrome(hCamera):
	pbEnable = c_int()
	err_code = _sdk.CameraGetMonochrome(hCamera, byref(pbEnable))
	SetLastError(err_code)
	return pbEnable.value

def CameraSetInverse(hCamera, bEnable):
	err_code = _sdk.CameraSetInverse(hCamera, bEnable)
	SetLastError(err_code)
	return err_code

def CameraGetInverse(hCamera):
	pbEnable = c_int()
	err_code = _sdk.CameraGetInverse(hCamera, byref(pbEnable))
	SetLastError(err_code)
	return pbEnable.value

def CameraSetAntiFlick(hCamera, bEnable):
	err_code = _sdk.CameraSetAntiFlick(hCamera, bEnable)
	SetLastError(err_code)
	return err_code

def CameraGetAntiFlick(hCamera):
	pbEnable = c_int()
	err_code = _sdk.CameraGetAntiFlick(hCamera, byref(pbEnable))
	SetLastError(err_code)
	return pbEnable.value

def CameraGetLightFrequency(hCamera):
	piFrequencySel = c_int()
	err_code = _sdk.CameraGetLightFrequency(hCamera, byref(piFrequencySel))
	SetLastError(err_code)
	return piFrequencySel.value

def CameraSetLightFrequency(hCamera, iFrequencySel):
	err_code = _sdk.CameraSetLightFrequency(hCamera, iFrequencySel)
	SetLastError(err_code)
	return err_code

def CameraSetFrameSpeed(hCamera, iFrameSpeed):
	err_code = _sdk.CameraSetFrameSpeed(hCamera, iFrameSpeed)
	SetLastError(err_code)
	return err_code

def CameraGetFrameSpeed(hCamera):
	piFrameSpeed = c_int()
	err_code = _sdk.CameraGetFrameSpeed(hCamera, byref(piFrameSpeed))
	SetLastError(err_code)
	return piFrameSpeed.value

def CameraSetParameterMode(hCamera, iMode):
	err_code = _sdk.CameraSetParameterMode(hCamera, iMode)
	SetLastError(err_code)
	return err_code

def CameraGetParameterMode(hCamera):
	piTarget = c_int()
	err_code = _sdk.CameraGetParameterMode(hCamera, byref(piTarget))
	SetLastError(err_code)
	return piTarget.value

def CameraSetParameterMask(hCamera, uMask):
	err_code = _sdk.CameraSetParameterMask(hCamera, uMask)
	SetLastError(err_code)
	return err_code

def CameraSaveParameter(hCamera, iTeam):
	err_code = _sdk.CameraSaveParameter(hCamera, iTeam)
	SetLastError(err_code)
	return err_code

def CameraSaveParameterToFile(hCamera, sFileName):
	err_code = _sdk.CameraSaveParameterToFile(hCamera, _str_to_string_buffer(sFileName))
	SetLastError(err_code)
	return err_code

def CameraReadParameterFromFile(hCamera, sFileName):
	err_code = _sdk.CameraReadParameterFromFile(hCamera, _str_to_string_buffer(sFileName))
	SetLastError(err_code)
	return err_code

def CameraLoadParameter(hCamera, iTeam):
	err_code = _sdk.CameraLoadParameter(hCamera, iTeam)
	SetLastError(err_code)
	return err_code

def CameraGetCurrentParameterGroup(hCamera):
	piTeam = c_int()
	err_code = _sdk.CameraGetCurrentParameterGroup(hCamera, byref(piTeam))
	SetLastError(err_code)
	return piTeam.value

def CameraSetTransPackLen(hCamera, iPackSel):
	err_code = _sdk.CameraSetTransPackLen(hCamera, iPackSel)
	SetLastError(err_code)
	return err_code

def CameraGetTransPackLen(hCamera):
	piPackSel = c_int()
	err_code = _sdk.CameraGetTransPackLen(hCamera, byref(piPackSel))
	SetLastError(err_code)
	return piPackSel.value

def CameraIsAeWinVisible(hCamera):
	pbIsVisible = c_int()
	err_code = _sdk.CameraIsAeWinVisible(hCamera, byref(pbIsVisible))
	SetLastError(err_code)
	return pbIsVisible.value

def CameraSetAeWinVisible(hCamera, bIsVisible):
	err_code = _sdk.CameraSetAeWinVisible(hCamera, bIsVisible)
	SetLastError(err_code)
	return err_code

def CameraGetAeWindow(hCamera):
	piHOff = c_int()
	piVOff = c_int()
	piWidth = c_int()
	piHeight = c_int()
	err_code = _sdk.CameraGetAeWindow(hCamera, byref(piHOff), byref(piVOff), byref(piWidth), byref(piHeight))
	SetLastError(err_code)
	return (piHOff.value, piVOff.value, piWidth.value, piHeight.value)

def CameraSetAeWindow(hCamera, iHOff, iVOff, iWidth, iHeight):
	err_code = _sdk.CameraSetAeWindow(hCamera, iHOff, iVOff, iWidth, iHeight)
	SetLastError(err_code)
	return err_code

def CameraSetMirror(hCamera, iDir, bEnable):
	err_code = _sdk.CameraSetMirror(hCamera, iDir, bEnable)
	SetLastError(err_code)
	return err_code

def CameraGetMirror(hCamera, iDir):
	pbEnable = c_int()
	err_code = _sdk.CameraGetMirror(hCamera, iDir, byref(pbEnable))
	SetLastError(err_code)
	return pbEnable.value

def CameraSetRotate(hCamera, iRot):
	err_code = _sdk.CameraSetRotate(hCamera, iRot)
	SetLastError(err_code)
	return err_code

def CameraGetRotate(hCamera):
	iRot = c_int()
	err_code = _sdk.CameraGetRotate(hCamera, byref(iRot))
	SetLastError(err_code)
	return iRot.value

def CameraGetWbWindow(hCamera):
	PiHOff = c_int()
	PiVOff = c_int()
	PiWidth = c_int()
	PiHeight = c_int()
	err_code = _sdk.CameraGetWbWindow(hCamera, byref(PiHOff), byref(PiVOff), byref(PiWidth), byref(PiHeight))
	SetLastError(err_code)
	return (PiHOff.value, PiVOff.value, PiWidth.value, PiHeight.value)

def CameraSetWbWindow(hCamera, iHOff, iVOff, iWidth, iHeight):
	err_code = _sdk.CameraSetWbWindow(hCamera, iHOff, iVOff, iWidth, iHeight)
	SetLastError(err_code)
	return err_code

def CameraIsWbWinVisible(hCamera):
	pbShow = c_int()
	err_code = _sdk.CameraIsWbWinVisible(hCamera, byref(pbShow))
	SetLastError(err_code)
	return pbShow.value

def CameraSetWbWinVisible(hCamera, bShow):
	err_code = _sdk.CameraSetWbWinVisible(hCamera, bShow)
	SetLastError(err_code)
	return err_code

def CameraImageOverlay(hCamera, pRgbBuffer, pFrInfo):
	err_code = _sdk.CameraImageOverlay(hCamera, c_void_p(pRgbBuffer), byref(pFrInfo))
	SetLastError(err_code)
	return err_code

def CameraSetCrossLine(hCamera, iLine, x, y, uColor, bVisible):
	err_code = _sdk.CameraSetCrossLine(hCamera, iLine, x, y, uColor, bVisible)
	SetLastError(err_code)
	return err_code

def CameraGetCrossLine(hCamera, iLine):
	px = c_int()
	py = c_int()
	pcolor = c_uint()
	pbVisible = c_int()
	err_code = _sdk.CameraGetCrossLine(hCamera, iLine, byref(px), byref(py), byref(pcolor), byref(pbVisible))
	SetLastError(err_code)
	return (px.value, py.value, pcolor.value, pbVisible.value)

def CameraGetCapability(hCamera):
	pCameraInfo = tSdkCameraCapbility()
	err_code = _sdk.CameraGetCapability(hCamera, byref(pCameraInfo))
	SetLastError(err_code)
	return pCameraInfo

def CameraWriteSN(hCamera, pbySN, iLevel):
	err_code = _sdk.CameraWriteSN(hCamera, _str_to_string_buffer(pbySN), iLevel)
	SetLastError(err_code)
	return err_code

def CameraReadSN(hCamera, iLevel):
	pbySN = create_string_buffer(64)
	err_code = _sdk.CameraReadSN(hCamera, pbySN, iLevel)
	SetLastError(err_code)
	return _string_buffer_to_str(pbySN)

def CameraSetTriggerDelayTime(hCamera, uDelayTimeUs):
	err_code = _sdk.CameraSetTriggerDelayTime(hCamera, uDelayTimeUs)
	SetLastError(err_code)
	return err_code

def CameraGetTriggerDelayTime(hCamera):
	puDelayTimeUs = c_uint()
	err_code = _sdk.CameraGetTriggerDelayTime(hCamera, byref(puDelayTimeUs))
	SetLastError(err_code)
	return puDelayTimeUs.value

def CameraSetTriggerCount(hCamera, iCount):
	err_code = _sdk.CameraSetTriggerCount(hCamera, iCount)
	SetLastError(err_code)
	return err_code

def CameraGetTriggerCount(hCamera):
	piCount = c_int()
	err_code = _sdk.CameraGetTriggerCount(hCamera, byref(piCount))
	SetLastError(err_code)
	return piCount.value

def CameraSoftTrigger(hCamera):
	err_code = _sdk.CameraSoftTrigger(hCamera)
	SetLastError(err_code)
	return err_code

def CameraSetTriggerMode(hCamera, iModeSel):
	err_code = _sdk.CameraSetTriggerMode(hCamera, iModeSel)
	SetLastError(err_code)
	return err_code

def CameraGetTriggerMode(hCamera):
	piModeSel = c_int()
	err_code = _sdk.CameraGetTriggerMode(hCamera, byref(piModeSel))
	SetLastError(err_code)
	return piModeSel.value

def CameraSetStrobeMode(hCamera, iMode):
	err_code = _sdk.CameraSetStrobeMode(hCamera, iMode)
	SetLastError(err_code)
	return err_code

def CameraGetStrobeMode(hCamera):
	piMode = c_int()
	err_code = _sdk.CameraGetStrobeMode(hCamera, byref(piMode))
	SetLastError(err_code)
	return piMode.value

def CameraSetStrobeDelayTime(hCamera, uDelayTimeUs):
	err_code = _sdk.CameraSetStrobeDelayTime(hCamera, uDelayTimeUs)
	SetLastError(err_code)
	return err_code

def CameraGetStrobeDelayTime(hCamera):
	upDelayTimeUs = c_uint()
	err_code = _sdk.CameraGetStrobeDelayTime(hCamera, byref(upDelayTimeUs))
	SetLastError(err_code)
	return upDelayTimeUs.value

def CameraSetStrobePulseWidth(hCamera, uTimeUs):
	err_code = _sdk.CameraSetStrobePulseWidth(hCamera, uTimeUs)
	SetLastError(err_code)
	return err_code

def CameraGetStrobePulseWidth(hCamera):
	upTimeUs = c_uint()
	err_code = _sdk.CameraGetStrobePulseWidth(hCamera, byref(upTimeUs))
	SetLastError(err_code)
	return upTimeUs.value

def CameraSetStrobePolarity(hCamera, uPolarity):
	err_code = _sdk.CameraSetStrobePolarity(hCamera, uPolarity)
	SetLastError(err_code)
	return err_code

def CameraGetStrobePolarity(hCamera):
	upPolarity = c_uint()
	err_code = _sdk.CameraGetStrobePolarity(hCamera, byref(upPolarity))
	SetLastError(err_code)
	return upPolarity.value

def CameraSetExtTrigSignalType(hCamera, iType):
	err_code = _sdk.CameraSetExtTrigSignalType(hCamera, iType)
	SetLastError(err_code)
	return err_code

def CameraGetExtTrigSignalType(hCamera):
	ipType = c_int()
	err_code = _sdk.CameraGetExtTrigSignalType(hCamera, byref(ipType))
	SetLastError(err_code)
	return ipType.value

def CameraSetExtTrigShutterType(hCamera, iType):
	err_code = _sdk.CameraSetExtTrigShutterType(hCamera, iType)
	SetLastError(err_code)
	return err_code

def CameraGetExtTrigShutterType(hCamera):
	ipType = c_int()
	err_code = _sdk.CameraGetExtTrigShutterType(hCamera, byref(ipType))
	SetLastError(err_code)
	return ipType.value

def CameraSetExtTrigDelayTime(hCamera, uDelayTimeUs):
	err_code = _sdk.CameraSetExtTrigDelayTime(hCamera, uDelayTimeUs)
	SetLastError(err_code)
	return err_code

def CameraGetExtTrigDelayTime(hCamera):
	upDelayTimeUs = c_uint()
	err_code = _sdk.CameraGetExtTrigDelayTime(hCamera, byref(upDelayTimeUs))
	SetLastError(err_code)
	return upDelayTimeUs.value

def CameraSetExtTrigJitterTime(hCamera, uTimeUs):
	err_code = _sdk.CameraSetExtTrigJitterTime(hCamera, uTimeUs)
	SetLastError(err_code)
	return err_code

def CameraGetExtTrigJitterTime(hCamera):
	upTimeUs = c_uint()
	err_code = _sdk.CameraGetExtTrigJitterTime(hCamera, byref(upTimeUs))
	SetLastError(err_code)
	return upTimeUs.value

def CameraGetExtTrigCapability(hCamera):
	puCapabilityMask = c_uint()
	err_code = _sdk.CameraGetExtTrigCapability(hCamera, byref(puCapabilityMask))
	SetLastError(err_code)
	return puCapabilityMask.value

def CameraPauseLevelTrigger(hCamera):
	err_code = _sdk.CameraPauseLevelTrigger(hCamera)
	SetLastError(err_code)
	return err_code

def CameraGetResolutionForSnap(hCamera):
	pImageResolution = tSdkImageResolution()
	err_code = _sdk.CameraGetResolutionForSnap(hCamera, byref(pImageResolution))
	SetLastError(err_code)
	return pImageResolution

def CameraSetResolutionForSnap(hCamera, pImageResolution):
	err_code = _sdk.CameraSetResolutionForSnap(hCamera, byref(pImageResolution))
	SetLastError(err_code)
	return err_code

def CameraCustomizeResolution(hCamera):
	pImageCustom = tSdkImageResolution()
	err_code = _sdk.CameraCustomizeResolution(hCamera, byref(pImageCustom))
	SetLastError(err_code)
	return pImageCustom

def CameraCustomizeReferWin(hCamera, iWinType, hParent):
	piHOff = c_int()
	piVOff = c_int()
	piWidth = c_int()
	piHeight = c_int()
	err_code = _sdk.CameraCustomizeReferWin(hCamera, iWinType, hParent, byref(piHOff), byref(piVOff), byref(piWidth), byref(piHeight))
	SetLastError(err_code)
	return (piHOff.value, piVOff.value, piWidth.value, piHeight.value)

def CameraShowSettingPage(hCamera, bShow):
	err_code = _sdk.CameraShowSettingPage(hCamera, bShow)
	SetLastError(err_code)
	return err_code

def CameraCreateSettingPage(hCamera, hParent, pWinText, pCallbackFunc = None, pCallbackCtx = 0, uReserved = 0):
	err_code = _sdk.CameraCreateSettingPage(hCamera, hParent, _str_to_string_buffer(pWinText), pCallbackFunc, c_void_p(pCallbackCtx), uReserved)
	SetLastError(err_code)
	return err_code

def CameraCreateSettingPageEx(hCamera):
	err_code = _sdk.CameraCreateSettingPageEx(hCamera)
	SetLastError(err_code)
	return err_code

def CameraSetActiveSettingSubPage(hCamera, index):
	err_code = _sdk.CameraSetActiveSettingSubPage(hCamera, index)
	SetLastError(err_code)
	return err_code

def CameraSetSettingPageParent(hCamera, hParentWnd, Flags):
	err_code = _sdk.CameraSetSettingPageParent(hCamera, hParentWnd, Flags)
	SetLastError(err_code)
	return err_code

def CameraGetSettingPageHWnd(hCamera):
	hWnd = c_void_p()
	err_code = _sdk.CameraGetSettingPageHWnd(hCamera, byref(hWnd))
	SetLastError(err_code)
	return hWnd.value

def CameraSpecialControl(hCamera, dwCtrlCode, dwParam, lpData):
	err_code = _sdk.CameraSpecialControl(hCamera, dwCtrlCode, dwParam, c_void_p(lpData) )
	SetLastError(err_code)
	return err_code

def CameraGetFrameStatistic(hCamera):
	psFrameStatistic = tSdkFrameStatistic()
	err_code = _sdk.CameraGetFrameStatistic(hCamera, byref(psFrameStatistic))
	SetLastError(err_code)
	return psFrameStatistic

def CameraSetNoiseFilter(hCamera, bEnable):
	err_code = _sdk.CameraSetNoiseFilter(hCamera, bEnable)
	SetLastError(err_code)
	return err_code

def CameraGetNoiseFilterState(hCamera):
	pEnable = c_int()
	err_code = _sdk.CameraGetNoiseFilterState(hCamera, byref(pEnable))
	SetLastError(err_code)
	return pEnable.value

def CameraRstTimeStamp(hCamera):
	err_code = _sdk.CameraRstTimeStamp(hCamera)
	SetLastError(err_code)
	return err_code

def CameraSaveUserData(hCamera, uStartAddr, pbData):
	err_code = _sdk.CameraSaveUserData(hCamera, uStartAddr, pbData, len(pbData))
	SetLastError(err_code)
	return err_code

def CameraLoadUserData(hCamera, uStartAddr, ilen):
	pbData = create_string_buffer(ilen)
	err_code = _sdk.CameraLoadUserData(hCamera, uStartAddr, pbData, ilen)
	SetLastError(err_code)
	return pbData[:]

def CameraGetFriendlyName(hCamera):
	pName = create_string_buffer(64)
	err_code = _sdk.CameraGetFriendlyName(hCamera, pName)
	SetLastError(err_code)
	return _string_buffer_to_str(pName)

def CameraSetFriendlyName(hCamera, pName):
	pNameBuf = _str_to_string_buffer(pName)
	resize(pNameBuf, 64)
	err_code = _sdk.CameraSetFriendlyName(hCamera, pNameBuf)
	SetLastError(err_code)
	return err_code

def CameraSdkGetVersionString():
	pVersionString = create_string_buffer(64)
	err_code = _sdk.CameraSdkGetVersionString(pVersionString)
	SetLastError(err_code)
	return _string_buffer_to_str(pVersionString)

def CameraCheckFwUpdate(hCamera):
	pNeedUpdate = c_int()
	err_code = _sdk.CameraCheckFwUpdate(hCamera, byref(pNeedUpdate))
	SetLastError(err_code)
	return pNeedUpdate.value

def CameraGetFirmwareVersion(hCamera):
	pVersion = create_string_buffer(64)
	err_code = _sdk.CameraGetFirmwareVersion(hCamera, pVersion)
	SetLastError(err_code)
	return _string_buffer_to_str(pVersion)

def CameraGetEnumInfo(hCamera):
	pCameraInfo = tSdkCameraDevInfo()
	err_code = _sdk.CameraGetEnumInfo(hCamera, byref(pCameraInfo))
	SetLastError(err_code)
	return pCameraInfo

def CameraGetInerfaceVersion(hCamera):
	pVersion = create_string_buffer(64)
	err_code = _sdk.CameraGetInerfaceVersion(hCamera, pVersion)
	SetLastError(err_code)
	return _string_buffer_to_str(pVersion)

def CameraSetIOState(hCamera, iOutputIOIndex, uState):
	err_code = _sdk.CameraSetIOState(hCamera, iOutputIOIndex, uState)
	SetLastError(err_code)
	return err_code

def CameraGetIOState(hCamera, iInputIOIndex):
	puState = c_int()
	err_code = _sdk.CameraGetIOState(hCamera, iInputIOIndex, byref(puState))
	SetLastError(err_code)
	return puState.value

def CameraSetInPutIOMode(hCamera, iInputIOIndex, iMode):
	err_code = _sdk.CameraSetInPutIOMode(hCamera, iInputIOIndex, iMode)
	SetLastError(err_code)
	return err_code

def CameraSetOutPutIOMode(hCamera, iOutputIOIndex, iMode):
	err_code = _sdk.CameraSetOutPutIOMode(hCamera, iOutputIOIndex, iMode)
	SetLastError(err_code)
	return err_code

def CameraSetOutPutPWM(hCamera, iOutputIOIndex, iCycle, uDuty):
	err_code = _sdk.CameraSetOutPutPWM(hCamera, iOutputIOIndex, iCycle, uDuty)
	SetLastError(err_code)
	return err_code

def CameraSetAeAlgorithm(hCamera, iIspProcessor, iAeAlgorithmSel):
	err_code = _sdk.CameraSetAeAlgorithm(hCamera, iIspProcessor, iAeAlgorithmSel)
	SetLastError(err_code)
	return err_code

def CameraGetAeAlgorithm(hCamera, iIspProcessor):
	piAlgorithmSel = c_int()
	err_code = _sdk.CameraGetAeAlgorithm(hCamera, iIspProcessor, byref(piAlgorithmSel))
	SetLastError(err_code)
	return piAlgorithmSel.value

def CameraSetBayerDecAlgorithm(hCamera, iIspProcessor, iAlgorithmSel):
	err_code = _sdk.CameraSetBayerDecAlgorithm(hCamera, iIspProcessor, iAlgorithmSel)
	SetLastError(err_code)
	return err_code

def CameraGetBayerDecAlgorithm(hCamera, iIspProcessor):
	piAlgorithmSel = c_int()
	err_code = _sdk.CameraGetBayerDecAlgorithm(hCamera, iIspProcessor, byref(piAlgorithmSel))
	SetLastError(err_code)
	return piAlgorithmSel.value

def CameraSetIspProcessor(hCamera, iIspProcessor):
	err_code = _sdk.CameraSetIspProcessor(hCamera, iIspProcessor)
	SetLastError(err_code)
	return err_code

def CameraGetIspProcessor(hCamera):
	piIspProcessor = c_int()
	err_code = _sdk.CameraGetIspProcessor(hCamera, byref(piIspProcessor))
	SetLastError(err_code)
	return piIspProcessor.value

def CameraSetBlackLevel(hCamera, iBlackLevel):
	err_code = _sdk.CameraSetBlackLevel(hCamera, iBlackLevel)
	SetLastError(err_code)
	return err_code

def CameraGetBlackLevel(hCamera):
	piBlackLevel = c_int()
	err_code = _sdk.CameraGetBlackLevel(hCamera, byref(piBlackLevel))
	SetLastError(err_code)
	return piBlackLevel.value

def CameraSetWhiteLevel(hCamera, iWhiteLevel):
	err_code = _sdk.CameraSetWhiteLevel(hCamera, iWhiteLevel)
	SetLastError(err_code)
	return err_code

def CameraGetWhiteLevel(hCamera):
	piWhiteLevel = c_int()
	err_code = _sdk.CameraGetWhiteLevel(hCamera, byref(piWhiteLevel))
	SetLastError(err_code)
	return piWhiteLevel.value

def CameraSetIspOutFormat(hCamera, uFormat):
	err_code = _sdk.CameraSetIspOutFormat(hCamera, uFormat)
	SetLastError(err_code)
	return err_code

def CameraGetIspOutFormat(hCamera):
	puFormat = c_int()
	err_code = _sdk.CameraGetIspOutFormat(hCamera, byref(puFormat))
	SetLastError(err_code)
	return puFormat.value

def CameraGetErrorString(iStatusCode):
	_sdk.CameraGetErrorString.restype = c_char_p
	msg = _sdk.CameraGetErrorString(iStatusCode)
	if msg:
		return _string_buffer_to_str(msg)
	else:
		return ''

def CameraGetImageBufferEx2(hCamera, pImageData, uOutFormat, wTimes):
	piWidth = c_int()
	piHeight = c_int()
	err_code = _sdk.CameraGetImageBufferEx2(hCamera, c_void_p(pImageData), uOutFormat, byref(piWidth), byref(piHeight), wTimes)
	SetLastError(err_code)
	if err_code != 0:
		raise CameraException(err_code)
	return (piWidth.value, piHeight.value)

def CameraGetImageBufferEx3(hCamera, pImageData, uOutFormat, wTimes):
	piWidth = c_int()
	piHeight = c_int()
	puTimeStamp = c_int()
	err_code = _sdk.CameraGetImageBufferEx3(hCamera, c_void_p(pImageData), uOutFormat, byref(piWidth), byref(piHeight), byref(puTimeStamp), wTimes)
	SetLastError(err_code)
	if err_code != 0:
		raise CameraException(err_code)
	return (piWidth.value, piHeight.value, puTimeStamp.value)

def CameraGetCapabilityEx2(hCamera):
	pMaxWidth = c_int()
	pMaxHeight = c_int()
	pbColorCamera = c_int()
	err_code = _sdk.CameraGetCapabilityEx2(hCamera, byref(pMaxWidth), byref(pMaxHeight), byref(pbColorCamera))
	SetLastError(err_code)
	return (pMaxWidth.value, pMaxHeight.value, pbColorCamera.value)

def CameraReConnect(hCamera):
	err_code = _sdk.CameraReConnect(hCamera)
	SetLastError(err_code)
	return err_code

def CameraConnectTest(hCamera):
	err_code = _sdk.CameraConnectTest(hCamera)
	SetLastError(err_code)
	return err_code

def CameraSetLedEnable(hCamera, index, enable):
	err_code = _sdk.CameraSetLedEnable(hCamera, index, enable)
	SetLastError(err_code)
	return err_code

def CameraGetLedEnable(hCamera, index):
	enable = c_int()
	err_code = _sdk.CameraGetLedEnable(hCamera, index, byref(enable))
	SetLastError(err_code)
	return enable.value

def CameraSetLedOnOff(hCamera, index, onoff):
	err_code = _sdk.CameraSetLedOnOff(hCamera, index, onoff)
	SetLastError(err_code)
	return err_code

def CameraGetLedOnOff(hCamera, index):
	onoff = c_int()
	err_code = _sdk.CameraGetLedOnOff(hCamera, index, byref(onoff))
	SetLastError(err_code)
	return onoff.value

def CameraSetLedDuration(hCamera, index, duration):
	err_code = _sdk.CameraSetLedDuration(hCamera, index, duration)
	SetLastError(err_code)
	return err_code

def CameraGetLedDuration(hCamera, index):
	duration = c_uint()
	err_code = _sdk.CameraGetLedDuration(hCamera, index, byref(duration))
	SetLastError(err_code)
	return duration.value

def CameraSetLedBrightness(hCamera, index, uBrightness):
	err_code = _sdk.CameraSetLedBrightness(hCamera, index, uBrightness)
	SetLastError(err_code)
	return err_code

def CameraGetLedBrightness(hCamera, index):
	uBrightness = c_uint()
	err_code = _sdk.CameraGetLedBrightness(hCamera, index, byref(uBrightness))
	SetLastError(err_code)
	return uBrightness.value

def CameraEnableTransferRoi(hCamera, uEnableMask):
	err_code = _sdk.CameraEnableTransferRoi(hCamera, uEnableMask)
	SetLastError(err_code)
	return err_code

def CameraSetTransferRoi(hCamera, index, X1, Y1, X2, Y2):
	err_code = _sdk.CameraSetTransferRoi(hCamera, index, X1, Y1, X2, Y2)
	SetLastError(err_code)
	return err_code

def CameraGetTransferRoi(hCamera, index):
	pX1 = c_uint()
	pY1 = c_uint()
	pX2 = c_uint()
	pY2 = c_uint()
	err_code = _sdk.CameraGetTransferRoi(hCamera, index, byref(pX1), byref(pY1), byref(pX2), byref(pY2))
	SetLastError(err_code)
	return (pX1.value, pY1.value, pX2.value, pY2.value)

def CameraAlignMalloc(size, align = 16):
	_sdk.CameraAlignMalloc.restype = c_void_p
	r = _sdk.CameraAlignMalloc(size, align)
	return r

def CameraAlignFree(membuffer):
	_sdk.CameraAlignFree(c_void_p(membuffer))

def CameraSetAutoConnect(hCamera, bEnable):
	err_code = _sdk.CameraSetAutoConnect(hCamera, bEnable)
	SetLastError(err_code)
	return err_code

def CameraGetAutoConnect(hCamera):
	pbEnable = c_int()
	err_code = _sdk.CameraGetAutoConnect(hCamera, byref(pbEnable))
	SetLastError(err_code)
	return pbEnable.value

def CameraGetReConnectCounts(hCamera):
	puCounts = c_int()
	err_code = _sdk.CameraGetReConnectCounts(hCamera, byref(puCounts))
	SetLastError(err_code)
	return puCounts.value

def CameraSetSingleGrabMode(hCamera, bEnable):
	err_code = _sdk.CameraSetSingleGrabMode(hCamera, bEnable)
	SetLastError(err_code)
	return err_code

def CameraGetSingleGrabMode(hCamera):
	pbEnable = c_int()
	err_code = _sdk.CameraGetSingleGrabMode(hCamera, byref(pbEnable))
	SetLastError(err_code)
	return pbEnable.value

def CameraRestartGrab(hCamera):
	err_code = _sdk.CameraRestartGrab(hCamera)
	SetLastError(err_code)
	return err_code

def CameraEvaluateImageDefinition(hCamera, iAlgorithSel, pbyIn, pFrInfo):
	DefinitionValue = c_double()
	err_code = _sdk.CameraEvaluateImageDefinition(hCamera, iAlgorithSel, c_void_p(pbyIn), byref(pFrInfo), byref(DefinitionValue))
	SetLastError(err_code)
	return DefinitionValue.value

def CameraDrawText(pRgbBuffer, pFrInfo, pFontFileName, FontWidth, FontHeight, pText, Left, Top, Width, Height, TextColor, uFlags):
	err_code = _sdk.CameraDrawText(c_void_p(pRgbBuffer), byref(pFrInfo), _str_to_string_buffer(pFontFileName), FontWidth, FontHeight, _str_to_string_buffer(pText), Left, Top, Width, Height, TextColor, uFlags)
	SetLastError(err_code)
	return err_code

def CameraGigeGetIp(pCameraInfo):
	CamIp = create_string_buffer(32)
	CamMask = create_string_buffer(32)
	CamGateWay = create_string_buffer(32)
	EtIp = create_string_buffer(32)
	EtMask = create_string_buffer(32)
	EtGateWay = create_string_buffer(32)
	err_code = _sdk.CameraGigeGetIp(byref(pCameraInfo), CamIp, CamMask, CamGateWay, EtIp, EtMask, EtGateWay)
	SetLastError(err_code)
	return (_string_buffer_to_str(CamIp), _string_buffer_to_str(CamMask), _string_buffer_to_str(CamGateWay), 
		_string_buffer_to_str(EtIp), _string_buffer_to_str(EtMask), _string_buffer_to_str(EtGateWay) )

def CameraGigeSetIp(pCameraInfo, Ip, SubMask, GateWay, bPersistent):
	err_code = _sdk.CameraGigeSetIp(byref(pCameraInfo), 
		_str_to_string_buffer(Ip), _str_to_string_buffer(SubMask), _str_to_string_buffer(GateWay), bPersistent)
	SetLastError(err_code)
	return err_code

def CameraGigeGetMac(pCameraInfo):
	CamMac = create_string_buffer(32)
	EtMac = create_string_buffer(32)
	err_code = _sdk.CameraGigeGetMac(byref(pCameraInfo), CamMac, EtMac)
	SetLastError(err_code)
	return (_string_buffer_to_str(CamMac), _string_buffer_to_str(EtMac) )

def CameraEnableFastResponse(hCamera):
	err_code = _sdk.CameraEnableFastResponse(hCamera)
	SetLastError(err_code)
	return err_code

def CameraSetCorrectDeadPixel(hCamera, bEnable):
	err_code = _sdk.CameraSetCorrectDeadPixel(hCamera, bEnable)
	SetLastError(err_code)
	return err_code

def CameraGetCorrectDeadPixel(hCamera):
	pbEnable = c_int()
	err_code = _sdk.CameraGetCorrectDeadPixel(hCamera, byref(pbEnable))
	SetLastError(err_code)
	return pbEnable.value

def CameraFlatFieldingCorrectSetEnable(hCamera, bEnable):
	err_code = _sdk.CameraFlatFieldingCorrectSetEnable(hCamera, bEnable)
	SetLastError(err_code)
	return err_code

def CameraFlatFieldingCorrectGetEnable(hCamera):
	pbEnable = c_int()
	err_code = _sdk.CameraFlatFieldingCorrectGetEnable(hCamera, byref(pbEnable))
	SetLastError(err_code)
	return pbEnable.value

def CameraFlatFieldingCorrectSetParameter(hCamera, pDarkFieldingImage, pDarkFieldingFrInfo, pLightFieldingImage, pLightFieldingFrInfo):
	err_code = _sdk.CameraFlatFieldingCorrectSetParameter(hCamera, c_void_p(pDarkFieldingImage), byref(pDarkFieldingFrInfo), c_void_p(pLightFieldingImage), byref(pLightFieldingFrInfo))
	SetLastError(err_code)
	return err_code

def CameraFlatFieldingCorrectGetParameterState(hCamera):
	pbValid = c_int()
	pFilePath = create_string_buffer(1024)
	err_code = _sdk.CameraFlatFieldingCorrectGetParameterState(hCamera, byref(pbValid), pFilePath)
	SetLastError(err_code)
	return (pbValid.value, _string_buffer_to_str(pFilePath) )

def CameraFlatFieldingCorrectSaveParameterToFile(hCamera, pszFileName):
	err_code = _sdk.CameraFlatFieldingCorrectSaveParameterToFile(hCamera, _str_to_string_buffer(pszFileName))
	SetLastError(err_code)
	return err_code

def CameraFlatFieldingCorrectLoadParameterFromFile(hCamera, pszFileName):
	err_code = _sdk.CameraFlatFieldingCorrectLoadParameterFromFile(hCamera, _str_to_string_buffer(pszFileName))
	SetLastError(err_code)
	return err_code

def CameraCommonCall(hCamera, pszCall, uResultBufSize):
	pszResult = create_string_buffer(uResultBufSize) if uResultBufSize > 0 else None
	err_code = _sdk.CameraCommonCall(hCamera, _str_to_string_buffer(pszCall), pszResult, uResultBufSize)
	SetLastError(err_code)
	return _string_buffer_to_str(pszResult) if pszResult else ''

def CameraSetDenoise3DParams(hCamera, bEnable, nCount, Weights):
	assert(nCount >= 2 and nCount <= 8)
	if Weights:
		assert(len(Weights) == nCount)
		WeightsNative = (c_float * nCount)(*Weights)
	else:
		WeightsNative = None
	err_code = _sdk.CameraSetDenoise3DParams(hCamera, bEnable, nCount, WeightsNative)
	SetLastError(err_code)
	return err_code

def CameraGetDenoise3DParams(hCamera):
	bEnable = c_int()
	nCount = c_int()
	bUseWeight = c_int()
	Weights = (c_float * 8)()
	err_code = _sdk.CameraGetDenoise3DParams(hCamera, byref(bEnable), byref(nCount), byref(bUseWeight), Weights)
	SetLastError(err_code)
	bEnable, nCount, bUseWeight = bEnable.value, nCount.value, bUseWeight.value
	if bUseWeight:
		Weights = Weights[:nCount]
	else:
		Weights = None
	return (bEnable, nCount, bUseWeight, Weights)

def CameraManualDenoise3D(InFramesHead, InFramesData, nCount, Weights, OutFrameHead, OutFrameData):
	assert(nCount > 0)
	assert(len(InFramesData) == nCount)
	assert(Weights is None or len(Weights) == nCount)
	InFramesDataNative = (c_void_p * nCount)(*InFramesData)
	WeightsNative = (c_float * nCount)(*Weights) if Weights else None
	err_code = _sdk.CameraManualDenoise3D(byref(InFramesHead), InFramesDataNative, nCount, WeightsNative, byref(OutFrameHead), c_void_p(OutFrameData))
	SetLastError(err_code)
	return err_code

def CameraCustomizeDeadPixels(hCamera, hParent):
	err_code = _sdk.CameraCustomizeDeadPixels(hCamera, hParent)
	SetLastError(err_code)
	return err_code

def CameraReadDeadPixels(hCamera):
	pNumPixel = c_int()
	err_code = _sdk.CameraReadDeadPixels(hCamera, None, None, byref(pNumPixel))
	SetLastError(err_code)
	if pNumPixel.value < 1:
		return None
	UShortArray = c_ushort * pNumPixel.value
	pRows = UShortArray()
	pCols = UShortArray()
	err_code = _sdk.CameraReadDeadPixels(hCamera, pRows, pCols, byref(pNumPixel))
	SetLastError(err_code)
	if err_code == 0:
		pNumPixel = pNumPixel.value
	else:
		pNumPixel = 0
	return (pRows[:pNumPixel], pCols[:pNumPixel])

def CameraAddDeadPixels(hCamera, pRows, pCols, NumPixel):
	UShortArray = c_ushort * NumPixel
	pRowsNative = UShortArray(*pRows)
	pColsNative = UShortArray(*pCols)
	err_code = _sdk.CameraAddDeadPixels(hCamera, pRowsNative, pColsNative, NumPixel)
	SetLastError(err_code)
	return err_code

def CameraRemoveDeadPixels(hCamera, pRows, pCols, NumPixel):
	UShortArray = c_ushort * NumPixel
	pRowsNative = UShortArray(*pRows)
	pColsNative = UShortArray(*pCols)
	err_code = _sdk.CameraRemoveDeadPixels(hCamera, pRowsNative, pColsNative, NumPixel)
	SetLastError(err_code)
	return err_code

def CameraRemoveAllDeadPixels(hCamera):
	err_code = _sdk.CameraRemoveAllDeadPixels(hCamera)
	SetLastError(err_code)
	return err_code

def CameraSaveDeadPixels(hCamera):
	err_code = _sdk.CameraSaveDeadPixels(hCamera)
	SetLastError(err_code)
	return err_code

def CameraSaveDeadPixelsToFile(hCamera, sFileName):
	err_code = _sdk.CameraSaveDeadPixelsToFile(hCamera, _str_to_string_buffer(sFileName))
	SetLastError(err_code)
	return err_code

def CameraLoadDeadPixelsFromFile(hCamera, sFileName):
	err_code = _sdk.CameraLoadDeadPixelsFromFile(hCamera, _str_to_string_buffer(sFileName))
	SetLastError(err_code)
	return err_code

def CameraGetImageBufferPriority(hCamera, wTimes, Priority):
	pFrameInfo = tSdkFrameHead()
	pbyBuffer = c_void_p()
	err_code = _sdk.CameraGetImageBufferPriority(hCamera, byref(pFrameInfo), byref(pbyBuffer), wTimes, Priority)
	SetLastError(err_code)
	if err_code != 0:
		raise CameraException(err_code)
	return (pbyBuffer.value, pFrameInfo)

def CameraGetImageBufferPriorityEx(hCamera, wTimes, Priority):
	_sdk.CameraGetImageBufferPriorityEx.restype = c_void_p
	piWidth = c_int()
	piHeight = c_int()
	pFrameBuffer = _sdk.CameraGetImageBufferPriorityEx(hCamera, byref(piWidth), byref(piHeight), wTimes, Priority)
	err_code = CAMERA_STATUS_SUCCESS if pFrameBuffer else CAMERA_STATUS_TIME_OUT
	SetLastError(err_code)
	if pFrameBuffer:
		return (pFrameBuffer, piWidth.value, piHeight.value)
	else:
		raise CameraException(err_code)

def CameraGetImageBufferPriorityEx2(hCamera, pImageData, uOutFormat, wTimes, Priority):
	piWidth = c_int()
	piHeight = c_int()
	err_code = _sdk.CameraGetImageBufferPriorityEx2(hCamera, c_void_p(pImageData), uOutFormat, byref(piWidth), byref(piHeight), wTimes, Priority)
	SetLastError(err_code)
	if err_code != 0:
		raise CameraException(err_code)
	return (piWidth.value, piHeight.value)

def CameraGetImageBufferPriorityEx3(hCamera, pImageData, uOutFormat, wTimes, Priority):
	piWidth = c_int()
	piHeight = c_int()
	puTimeStamp = c_uint()
	err_code = _sdk.CameraGetImageBufferPriorityEx3(hCamera, c_void_p(pImageData), uOutFormat, byref(piWidth), byref(piHeight), byref(puTimeStamp), wTimes, Priority)
	SetLastError(err_code)
	if err_code != 0:
		raise CameraException(err_code)
	return (piWidth.value, piHeight.value, puTimeStamp.value)

def CameraClearBuffer(hCamera):
	err_code = _sdk.CameraClearBuffer(hCamera)
	SetLastError(err_code)
	return err_code

def CameraSoftTriggerEx(hCamera, uFlags):
	err_code = _sdk.CameraSoftTriggerEx(hCamera, uFlags)
	SetLastError(err_code)
	return err_code

def CameraSetHDR(hCamera, value):
	err_code = _sdk.CameraSetHDR(hCamera, value)
	SetLastError(err_code)
	return err_code

def CameraGetHDR(hCamera):
	value = c_int()
	err_code = _sdk.CameraGetHDR(hCamera, byref(value))
	SetLastError(err_code)
	return value.value

def CameraGetFrameID(hCamera):
	FrameID = c_uint()
	err_code = _sdk.CameraGetFrameID(hCamera, byref(FrameID))
	SetLastError(err_code)
	return FrameID.value

def CameraGetFrameTimeStamp(hCamera):
	TimeStamp = c_uint64()
	TimeStampL = c_uint32.from_buffer(TimeStamp)
	TimeStampH = c_uint32.from_buffer(TimeStamp, 4)
	err_code = _sdk.CameraGetFrameTimeStamp(hCamera, byref(TimeStampL), byref(TimeStampH))
	SetLastError(err_code)
	return TimeStamp.value

def CameraSetHDRGainMode(hCamera, value):
	err_code = _sdk.CameraSetHDRGainMode(hCamera, value)
	SetLastError(err_code)
	return err_code

def CameraGetHDRGainMode(hCamera):
	value = c_int()
	err_code = _sdk.CameraGetHDRGainMode(hCamera, byref(value))
	SetLastError(err_code)
	return value.value

def CameraCreateDIBitmap(hDC, pFrameBuffer, pFrameHead):
	outBitmap = c_void_p()
	err_code = _sdk.CameraCreateDIBitmap(hDC, c_void_p(pFrameBuffer), byref(pFrameHead), byref(outBitmap))
	SetLastError(err_code)
	return outBitmap.value

def CameraDrawFrameBuffer(pFrameBuffer, pFrameHead, hWnd, Algorithm, Mode):
	err_code = _sdk.CameraDrawFrameBuffer(c_void_p(pFrameBuffer), byref(pFrameHead), c_void_p(hWnd), Algorithm, Mode)
	SetLastError(err_code)
	return err_code

def CameraFlipFrameBuffer(pFrameBuffer, pFrameHead, Flags):
	err_code = _sdk.CameraFlipFrameBuffer(c_void_p(pFrameBuffer), byref(pFrameHead), Flags)
	SetLastError(err_code)
	return err_code

def CameraConvertFrameBufferFormat(hCamera, pInFrameBuffer, pOutFrameBuffer, outWidth, outHeight, outMediaType, pFrameHead):
	err_code = _sdk.CameraConvertFrameBufferFormat(hCamera, c_void_p(pInFrameBuffer), c_void_p(pOutFrameBuffer), outWidth, outHeight, outMediaType, byref(pFrameHead))
	SetLastError(err_code)
	return err_code

def CameraSetConnectionStatusCallback(hCamera, pCallBack, pContext = 0):
	err_code = _sdk.CameraSetConnectionStatusCallback(hCamera, pCallBack, c_void_p(pContext) )
	SetLastError(err_code)
	return err_code

def CameraSetLightingControllerMode(hCamera, index, mode):
	err_code = _sdk.CameraSetLightingControllerMode(hCamera, index, mode)
	SetLastError(err_code)
	return err_code

def CameraSetLightingControllerState(hCamera, index, state):
	err_code = _sdk.CameraSetLightingControllerState(hCamera, index, state)
	SetLastError(err_code)
	return err_code

def CameraGetEyeCount(hCamera):
	EyeCount = c_int()
	err_code = _sdk.CameraGetEyeCount(hCamera, byref(EyeCount))
	SetLastError(err_code)
	return EyeCount.value

def CameraMultiEyeImageProcess(hCamera, iEyeIndex, pbyIn, pInFrInfo, pbyOut, pOutFrInfo, uOutFormat, uReserved):
	err_code = _sdk.CameraMultiEyeImageProcess(hCamera, iEyeIndex, c_void_p(pbyIn), byref(pInFrInfo), c_void_p(pbyOut), byref(pOutFrInfo), uOutFormat, uReserved)
	SetLastError(err_code)
	return err_code

# CameraGrabber

def CameraGrabber_CreateFromDevicePage():
	Grabber = c_void_p()
	err_code = _sdk.CameraGrabber_CreateFromDevicePage(byref(Grabber))
	SetLastError(err_code)
	if err_code != 0:
		raise CameraException(err_code)
	return Grabber.value

def CameraGrabber_CreateByIndex(Index):
	Grabber = c_void_p()
	err_code = _sdk.CameraGrabber_CreateByIndex(byref(Grabber), Index)
	SetLastError(err_code)
	if err_code != 0:
		raise CameraException(err_code)
	return Grabber.value

def CameraGrabber_CreateByName(Name):
	Grabber = c_void_p()
	err_code = _sdk.CameraGrabber_CreateByName(byref(Grabber), _str_to_string_buffer(Name))
	SetLastError(err_code)
	if err_code != 0:
		raise CameraException(err_code)
	return Grabber.value

def CameraGrabber_Create(pDevInfo):
	Grabber = c_void_p()
	err_code = _sdk.CameraGrabber_Create(byref(Grabber), byref(pDevInfo))
	SetLastError(err_code)
	if err_code != 0:
		raise CameraException(err_code)
	return Grabber.value

def CameraGrabber_Destroy(Grabber):
	err_code = _sdk.CameraGrabber_Destroy(c_void_p(Grabber))
	SetLastError(err_code)
	return err_code

def CameraGrabber_SetHWnd(Grabber, hWnd):
	err_code = _sdk.CameraGrabber_SetHWnd(c_void_p(Grabber), c_void_p(hWnd) )
	SetLastError(err_code)
	return err_code

def CameraGrabber_SetPriority(Grabber, Priority):
	err_code = _sdk.CameraGrabber_SetPriority(c_void_p(Grabber), Priority)
	SetLastError(err_code)
	return err_code

def CameraGrabber_StartLive(Grabber):
	err_code = _sdk.CameraGrabber_StartLive(c_void_p(Grabber))
	SetLastError(err_code)
	return err_code

def CameraGrabber_StopLive(Grabber):
	err_code = _sdk.CameraGrabber_StopLive(c_void_p(Grabber))
	SetLastError(err_code)
	return err_code

def CameraGrabber_SaveImage(Grabber, TimeOut):
	Image = c_void_p()
	err_code = _sdk.CameraGrabber_SaveImage(c_void_p(Grabber), byref(Image), TimeOut)
	SetLastError(err_code)
	if err_code != 0:
		raise CameraException(err_code)
	return Image.value

def CameraGrabber_SaveImageAsync(Grabber):
	err_code = _sdk.CameraGrabber_SaveImageAsync(c_void_p(Grabber))
	SetLastError(err_code)
	return err_code

def CameraGrabber_SaveImageAsyncEx(Grabber, UserData):
	err_code = _sdk.CameraGrabber_SaveImageAsyncEx(c_void_p(Grabber), c_void_p(UserData))
	SetLastError(err_code)
	return err_code

def CameraGrabber_SetSaveImageCompleteCallback(Grabber, Callback, Context = 0):
	err_code = _sdk.CameraGrabber_SetSaveImageCompleteCallback(c_void_p(Grabber), Callback, c_void_p(Context))
	SetLastError(err_code)
	return err_code

def CameraGrabber_SetFrameListener(Grabber, Listener, Context = 0):
	err_code = _sdk.CameraGrabber_SetFrameListener(c_void_p(Grabber), Listener, c_void_p(Context))
	SetLastError(err_code)
	return err_code

def CameraGrabber_SetRawCallback(Grabber, Callback, Context = 0):
	err_code = _sdk.CameraGrabber_SetRawCallback(c_void_p(Grabber), Callback, c_void_p(Context))
	SetLastError(err_code)
	return err_code

def CameraGrabber_SetRGBCallback(Grabber, Callback, Context = 0):
	err_code = _sdk.CameraGrabber_SetRGBCallback(c_void_p(Grabber), Callback, c_void_p(Context))
	SetLastError(err_code)
	return err_code

def CameraGrabber_GetCameraHandle(Grabber):
	hCamera = c_int()
	err_code = _sdk.CameraGrabber_GetCameraHandle(c_void_p(Grabber), byref(hCamera))
	SetLastError(err_code)
	return hCamera.value

def CameraGrabber_GetStat(Grabber):
	stat = tSdkGrabberStat()
	err_code = _sdk.CameraGrabber_GetStat(c_void_p(Grabber), byref(stat))
	SetLastError(err_code)
	return stat

def CameraGrabber_GetCameraDevInfo(Grabber):
	DevInfo = tSdkCameraDevInfo()
	err_code = _sdk.CameraGrabber_GetCameraDevInfo(c_void_p(Grabber), byref(DevInfo))
	SetLastError(err_code)
	return DevInfo

# CameraImage

def CameraImage_Create(pFrameBuffer, pFrameHead, bCopy):
	Image = c_void_p()
	err_code = _sdk.CameraImage_Create(byref(Image), c_void_p(pFrameBuffer), byref(pFrameHead), bCopy)
	SetLastError(err_code)
	return Image.value

def CameraImage_CreateEmpty():
	Image = c_void_p()
	err_code = _sdk.CameraImage_CreateEmpty(byref(Image))
	SetLastError(err_code)
	return Image.value

def CameraImage_Destroy(Image):
	err_code = _sdk.CameraImage_Destroy(c_void_p(Image))
	SetLastError(err_code)
	return err_code

def CameraImage_GetData(Image):
	DataBuffer = c_void_p()
	HeadPtr = c_void_p()
	err_code = _sdk.CameraImage_GetData(c_void_p(Image), byref(DataBuffer), byref(HeadPtr))
	SetLastError(err_code)
	if err_code == 0:
		return (DataBuffer.value, tSdkFrameHead.from_address(HeadPtr.value) )
	else:
		return (0, None)

def CameraImage_GetUserData(Image):
	UserData = c_void_p()
	err_code = _sdk.CameraImage_GetUserData(c_void_p(Image), byref(UserData))
	SetLastError(err_code)
	return UserData.value

def CameraImage_SetUserData(Image, UserData):
	err_code = _sdk.CameraImage_SetUserData(c_void_p(Image), c_void_p(UserData))
	SetLastError(err_code)
	return err_code

def CameraImage_IsEmpty(Image):
	IsEmpty = c_int()
	err_code = _sdk.CameraImage_IsEmpty(c_void_p(Image), byref(IsEmpty))
	SetLastError(err_code)
	return IsEmpty.value

def CameraImage_Draw(Image, hWnd, Algorithm):
	err_code = _sdk.CameraImage_Draw(c_void_p(Image), c_void_p(hWnd), Algorithm)
	SetLastError(err_code)
	return err_code

def CameraImage_DrawFit(Image, hWnd, Algorithm):
	err_code = _sdk.CameraImage_DrawFit(c_void_p(Image), c_void_p(hWnd), Algorithm)
	SetLastError(err_code)
	return err_code

def CameraImage_DrawToDC(Image, hDC, Algorithm, xDst, yDst, cxDst, cyDst):
	err_code = _sdk.CameraImage_DrawToDC(c_void_p(Image), c_void_p(hDC), Algorithm, xDst, yDst, cxDst, cyDst)
	SetLastError(err_code)
	return err_code

def CameraImage_DrawToDCFit(Image, hDC, Algorithm, xDst, yDst, cxDst, cyDst):
	err_code = _sdk.CameraImage_DrawToDCFit(c_void_p(Image), c_void_p(hDC), Algorithm, xDst, yDst, cxDst, cyDst)
	SetLastError(err_code)
	return err_code

def CameraImage_BitBlt(Image, hWnd, xDst, yDst, cxDst, cyDst, xSrc, ySrc):
	err_code = _sdk.CameraImage_BitBlt(c_void_p(Image), c_void_p(hWnd), xDst, yDst, cxDst, cyDst, xSrc, ySrc)
	SetLastError(err_code)
	return err_code

def CameraImage_BitBltToDC(Image, hDC, xDst, yDst, cxDst, cyDst, xSrc, ySrc):
	err_code = _sdk.CameraImage_BitBltToDC(c_void_p(Image), c_void_p(hDC), xDst, yDst, cxDst, cyDst, xSrc, ySrc)
	SetLastError(err_code)
	return err_code

def CameraImage_SaveAsBmp(Image, FileName):
	err_code = _sdk.CameraImage_SaveAsBmp(c_void_p(Image), _str_to_string_buffer(FileName))
	SetLastError(err_code)
	return err_code

def CameraImage_SaveAsJpeg(Image, FileName, Quality):
	err_code = _sdk.CameraImage_SaveAsJpeg(c_void_p(Image), _str_to_string_buffer(FileName), Quality)
	SetLastError(err_code)
	return err_code

def CameraImage_SaveAsPng(Image, FileName):
	err_code = _sdk.CameraImage_SaveAsPng(c_void_p(Image), _str_to_string_buffer(FileName))
	SetLastError(err_code)
	return err_code

def CameraImage_SaveAsRaw(Image, FileName, Format):
	err_code = _sdk.CameraImage_SaveAsRaw(c_void_p(Image), _str_to_string_buffer(FileName), Format)
	SetLastError(err_code)
	return err_code

def CameraImage_IPicture(Image):
	NewPic = c_void_p()
	err_code = _sdk.CameraImage_IPicture(c_void_p(Image), byref(NewPic))
	SetLastError(err_code)
	return NewPic.value
