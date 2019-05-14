#ifndef __CAMERA_STATUS_DEF__
#define __CAMERA_STATUS_DEF__

/// @ingroup MV_TYPEDEF
/// \~chinese SDK错误码
/// \~english SDK error code
typedef int CameraSdkStatus;


/*常用的宏*/
#define SDK_SUCCESS(_FUC_)              (_FUC_ == CAMERA_STATUS_SUCCESS)

#define SDK_UNSUCCESS(_FUC_)            (_FUC_ != CAMERA_STATUS_SUCCESS)

#define SDK_UNSUCCESS_RETURN(_FUC_,RET) if((RET = _FUC_) != CAMERA_STATUS_SUCCESS)\
                                        {\
                                            return RET;\
                                        }

#define SDK_UNSUCCESS_BREAK(_FUC_)      if(_FUC_ != CAMERA_STATUS_SUCCESS)\
                                        {\
                                            break;\
                                        }


/// @ingroup MV_MACRO_TYPE 
/// @{
/* 常用错误  */

#define CAMERA_STATUS_SUCCESS                    0   ///< \~chinese 操作成功 \~english Successful
#define CAMERA_STATUS_FAILED                    -1   ///< \~chinese 操作失败 \~english operation failed
#define CAMERA_STATUS_INTERNAL_ERROR            -2   ///< \~chinese 内部错误 \~english internal error
#define CAMERA_STATUS_UNKNOW                    -3   ///< \~chinese 未知错误 \~english unknown error
#define CAMERA_STATUS_NOT_SUPPORTED             -4   ///< \~chinese 不支持该功能 \~english Does not support this feature
#define CAMERA_STATUS_NOT_INITIALIZED           -5   ///< \~chinese 初始化未完成 \~english Incomplete initialization
#define CAMERA_STATUS_PARAMETER_INVALID         -6   ///< \~chinese 参数无效 \~english Invalid argument
#define CAMERA_STATUS_PARAMETER_OUT_OF_BOUND    -7   ///< \~chinese 参数越界 \~english Out of bounds of parameters
#define CAMERA_STATUS_UNENABLED                 -8   ///< \~chinese 未使能 \~english Not enabled
#define CAMERA_STATUS_USER_CANCEL               -9   ///< \~chinese 用户手动取消了，比如roi面板点击取消，返回 \~english The user manually canceled, such as roi panel click cancel, return
#define CAMERA_STATUS_PATH_NOT_FOUND            -10  ///< \~chinese 注册表中没有找到对应的路径 \~english The corresponding path was not found in the registry
#define CAMERA_STATUS_SIZE_DISMATCH             -11  ///< \~chinese 获得图像数据长度和定义的尺寸不匹配 \~english The length of the obtained image data does not match the defined size
#define CAMERA_STATUS_TIME_OUT                  -12  ///< \~chinese 超时错误 \~english Timeout error
#define CAMERA_STATUS_IO_ERROR                  -13  ///< \~chinese 硬件IO错误 \~english Hardware IO error
#define CAMERA_STATUS_COMM_ERROR                -14  ///< \~chinese 通讯错误 \~english Communication error
#define CAMERA_STATUS_BUS_ERROR                 -15  ///< \~chinese 总线错误 \~english Bus error
#define CAMERA_STATUS_NO_DEVICE_FOUND           -16  ///< \~chinese 没有发现设备 \~english No device found
#define CAMERA_STATUS_NO_LOGIC_DEVICE_FOUND     -17  ///< \~chinese 未找到逻辑设备 \~english Logical device not found
#define CAMERA_STATUS_DEVICE_IS_OPENED          -18  ///< \~chinese 设备已经打开 \~english The device is already open
#define CAMERA_STATUS_DEVICE_IS_CLOSED          -19  ///< \~chinese 设备已经关闭 \~english Device is off
#define CAMERA_STATUS_DEVICE_VEDIO_CLOSED       -20  ///< \~chinese 没有打开设备视频，调用录像相关的函数时，如果相机视频没有打开，则回返回该错误。 \~english Without opening the device video, when the video-related function is called, if the camera video is not open, the error is returned back.
#define CAMERA_STATUS_NO_MEMORY                 -21  ///< \~chinese 没有足够系统内存 \~english Not enough system memory
#define CAMERA_STATUS_FILE_CREATE_FAILED        -22  ///< \~chinese 创建文件失败 \~english Failed to create file
#define CAMERA_STATUS_FILE_INVALID              -23  ///< \~chinese 文件格式无效 \~english Invalid file format
#define CAMERA_STATUS_WRITE_PROTECTED           -24  ///< \~chinese 写保护，不可写 \~english Write protection, not write
#define CAMERA_STATUS_GRAB_FAILED               -25  ///< \~chinese 数据采集失败 \~english Data collection failed
#define CAMERA_STATUS_LOST_DATA                 -26  ///< \~chinese 数据丢失，不完整 \~english Loss of data, incomplete
#define CAMERA_STATUS_EOF_ERROR                 -27  ///< \~chinese 未接收到帧结束符 \~english No frame terminator received
#define CAMERA_STATUS_BUSY                      -28  ///< \~chinese 正忙(上一次操作还在进行中)，此次操作不能进行 \~english Busy (last operation is still in progress), this operation cannot be performed
#define CAMERA_STATUS_WAIT                      -29  ///< \~chinese 需要等待(进行操作的条件不成立)，可以再次尝试 \~english Need to wait (condition of operation is not established), can try again
#define CAMERA_STATUS_IN_PROCESS                -30  ///< \~chinese 正在进行，已经被操作过 \~english Ongoing, has been operated
#define CAMERA_STATUS_IIC_ERROR                 -31  ///< \~chinese IIC传输错误 \~english IIC transmission error
#define CAMERA_STATUS_SPI_ERROR                 -32  ///< \~chinese SPI传输错误 \~english SPI transmission error
#define CAMERA_STATUS_USB_CONTROL_ERROR         -33  ///< \~chinese USB控制传输错误 \~english USB control transmission error
#define CAMERA_STATUS_USB_BULK_ERROR            -34  ///< \~chinese USB BULK传输错误 \~english USB BULK transmission error
#define CAMERA_STATUS_SOCKET_INIT_ERROR         -35  ///< \~chinese 网络传输套件初始化失败 \~english Network Transport Suite Initialization Failed
#define CAMERA_STATUS_GIGE_FILTER_INIT_ERROR    -36  ///< \~chinese 网络相机内核过滤驱动初始化失败，请检查是否正确安装了驱动，或者重新安装。 \~english The webcam kernel filter driver failed to initialize. Please check if the driver is installed correctly or reinstall it.
#define CAMERA_STATUS_NET_SEND_ERROR            -37  ///< \~chinese 网络数据发送错误 \~english Network data sending error
#define CAMERA_STATUS_DEVICE_LOST               -38  ///< \~chinese 与网络相机失去连接，心跳检测超时 \~english Lost connection with webcam, heartbeat timeout
#define CAMERA_STATUS_DATA_RECV_LESS            -39  ///< \~chinese 接收到的字节数比请求的少  \~english Received fewer bytes than requested
#define CAMERA_STATUS_FUNCTION_LOAD_FAILED      -40  ///< \~chinese 从文件中加载程序失败 \~english Failed to load program from file
#define CAMERA_STATUS_CRITICAL_FILE_LOST        -41  ///< \~chinese 程序运行所必须的文件丢失。 \~english The file necessary to run the program is missing.
#define CAMERA_STATUS_SENSOR_ID_DISMATCH        -42  ///< \~chinese 固件和程序不匹配，原因是下载了错误的固件。 \~english The firmware and program do not match because the wrong firmware was downloaded.
#define CAMERA_STATUS_OUT_OF_RANGE              -43  ///< \~chinese 参数超出有效范围。 \~english The parameter is out of valid range.
#define CAMERA_STATUS_REGISTRY_ERROR            -44  ///< \~chinese 安装程序注册错误。请重新安装程序，或者运行安装目录Setup/Installer.exe \~english Setup registration error. Please reinstall the program, or run the installation directory Setup/Installer.exe
#define CAMERA_STATUS_ACCESS_DENY               -45  ///< \~chinese 禁止访问。指定相机已经被其他程序占用时，再申请访问该相机，会返回该状态。(一个相机不能被多个程序同时访问) \~english No Access. When the specified camera has been occupied by another program, it will return to this state if you request to access the camera. (A camera cannot be accessed simultaneously by multiple programs)
#define CAMERA_STATUS_CAMERA_NEED_RESET         -46  ///< \~chinese 表示相机需要复位后才能正常使用，此时请让相机断电重启，或者重启操作系统后，便可正常使用。 \~english It means that the camera needs to be reset before it can be used normally. At this time, please make the camera power off and restart, or restart the operating system, then it can be used normally.
#define CAMERA_STATUS_ISP_MOUDLE_NOT_INITIALIZED -47 ///< \~chinese ISP模块未初始化 \~english ISP module is not initialized
#define CAMERA_STATUS_ISP_DATA_CRC_ERROR        -48  ///< \~chinese 数据校验错误 \~english Data check error
#define CAMERA_STATUS_MV_TEST_FAILED            -49  ///< \~chinese 数据测试失败 \~english Data test failed
#define CAMERA_STATUS_INTERNAL_ERR1             -50	 ///< \~chinese 内部错误1 \~english Internal error 1
#define CAMERA_STATUS_U3V_NO_CONTROL_EP			-51	 ///< \~chinese U3V控制端点未找到 \~english U3V control endpoint not found
#define CAMERA_STATUS_U3V_CONTROL_ERROR			-52	 ///< \~chinese U3V控制通讯错误 \~english U3V control communication error
#define CAMERA_STATUS_INVALID_FRIENDLY_NAME		-53	 ///< \~chinese 无效的设备名，名字里不能包含以下字符(\/:*?"<>|") \~english Invalid device name, the name cannot contain the following characters (\/:*?"<>|")



//和AIA制定的标准相同
/*#define CAMERA_AIA_SUCCESS                        0x0000 */
#define CAMERA_AIA_PACKET_RESEND                          0x0100 ///< \~chinese 该帧需要重传 \~english The frame needs to be retransmitted
#define CAMERA_AIA_NOT_IMPLEMENTED                        0x8001 ///< \~chinese 设备不支持的命令 \~english Device does not support commands
#define CAMERA_AIA_INVALID_PARAMETER                      0x8002 ///< \~chinese 命令参数非法 \~english Illegal command parameters
#define CAMERA_AIA_INVALID_ADDRESS                        0x8003 ///< \~chinese 不可访问的地址 \~english Inaccessible address
#define CAMERA_AIA_WRITE_PROTECT                          0x8004 ///< \~chinese 访问的对象不可写 \~english The accessed object cannot be written
#define CAMERA_AIA_BAD_ALIGNMENT                          0x8005 ///< \~chinese 访问的地址没有按照要求对齐 \~english Visited address is not aligned as required
#define CAMERA_AIA_ACCESS_DENIED                          0x8006 ///< \~chinese 没有访问权限 \~english No access
#define CAMERA_AIA_BUSY                                   0x8007 ///< \~chinese 命令正在处理中 \~english Command is processing
#define CAMERA_AIA_DEPRECATED                             0x8008 ///< \~chinese 0x8008-0x0800B  0x800F  该指令已经废弃 \~english 0x8008-0x0800B 0x800F This instruction has been deprecated
#define CAMERA_AIA_PACKET_UNAVAILABLE                     0x800C ///< \~chinese 包无效 \~english Invalid package
#define CAMERA_AIA_DATA_OVERRUN                           0x800D ///< \~chinese 数据溢出，通常是收到的数据比需要的多 \~english Data overflow, usually more data than needed
#define CAMERA_AIA_INVALID_HEADER                         0x800E ///< \~chinese 数据包头部中某些区域与协议不匹配 \~english Some areas in the packet header do not match the protocol
#define CAMERA_AIA_PACKET_NOT_YET_AVAILABLE               0x8010 ///< \~chinese 图像分包数据还未准备好，多用于触发模式，应用程序访问超时 \~english Image packet data is not ready yet. It is mostly used in trigger mode. Application access timeout
#define CAMERA_AIA_PACKET_AND_PREV_REMOVED_FROM_MEMORY    0x8011 ///< \~chinese 需要访问的分包已经不存在。多用于重传时数据已经不在缓冲区中 \~english Subcontracts that require access no longer exist. Mostly used for data retransmission is not in the buffer
#define CAMERA_AIA_PACKET_REMOVED_FROM_MEMORY             0x8012 ///< \~chinese CAMERA_AIA_PACKET_AND_PREV_REMOVED_FROM_MEMORY \~english CAMERA_AIA_PACKET_AND_PREV_REMOVED_FROM_MEMORY
#define CAMERA_AIA_NO_REF_TIME                            0x0813 ///< \~chinese 没有参考时钟源。多用于时间同步的命令执行时 \~english There is no reference clock source. When used for time synchronization commands
#define CAMERA_AIA_PACKET_TEMPORARILY_UNAVAILABLE         0x0814 ///< \~chinese 由于信道带宽问题，当前分包暂时不可用，需稍后进行访问 \~english Due to channel bandwidth issues, the current subcontracting is temporarily unavailable and needs to be accessed later
#define CAMERA_AIA_OVERFLOW                               0x0815 ///< \~chinese 设备端数据溢出，通常是队列已满 \~english Data overflow on the device, usually the queue is full
#define CAMERA_AIA_ACTION_LATE                            0x0816 ///< \~chinese 命令执行已经超过有效的指定时间 \~english Command execution has exceeded valid specified time
#define CAMERA_AIA_ERROR                                  0x8FFF ///< \~chinese 错误 \~english error

/// @} end of MV_MACRO_TYPE

                                        

#endif
