#ifndef __PUCLIB_H
#define __PUCLIB_H

/*! 
	@mainpage
	@~english
		@brief This SDK is a Windows-compatible library that controls the PHOTRON high-speed camera "Infinicam" from a PC.@n
			See the quick manual for basic usage of this SDK. This reference describes all available constants, enumerations, structures, and functions.
	@~japanese
		@brief �{SDK�́A�t�H�g���������x�J�����uInfinicam�v��PC����R���g���[������Windows��p�̃��C�u�����ł��B@n
			SDK�̊�{�I�Ȏg�����̓N�C�b�N�}�j���A�����������������B�{�����ł́A���p�\�ȑS�Ă̒萔�A�񋓑́A�\���́A�֐��ɂ��ċL�ڂ��Ă��܂��B
	@copyright Copyright (C) 2020 PHOTRON LIMITED
*/

#ifdef	__cplusplus
extern "C" {
#endif

/*! @~english  @brief Maximum number of connectable devices
	@~japanese @brief �ڑ��\�ȍő�f�o�C�X�� */
#define PUC_MAX_DEVICE				16
/*! @~english  @brief Maximum number of characters.
	@~japanese @brief �ő啶���� */
#define PUC_MAX_LEN					256
/*! @~english  @brief Quantization table count (8*8)
	@~japanese @brief �ʎq���e�[�u���̌�(8*8) */
#define PUC_Q_COUNT					64
/*! @~english  @brief Minimum ring buffer count for continuous transfer.
	@~japanese @brief �A���]�����̍ŏ������O�o�b�t�@�� */
#define PUC_MIN_RING_BUF_COUNT		4
/*! @~english  @brief Maximum ring buffer count for continuous transfer.
	@~japanese @brief �A���]�����̍ő僊���O�o�b�t�@�� */
#define PUC_MAX_RING_BUF_COUNT		65535
/*! @~english  @brief Mode for automatically setting the timeout duration (ms) based on the frame rate when no response is received from the device.
	@~japanese @brief �f�o�C�X���牞�����Ȃ��ꍇ�̃^�C���A�E�g����(ms)���A�B�e���x�ɉ����Ď����Őݒ肷�郂�[�h */
#define PUC_XFER_TIMEOUT_AUTO		0
/*! @~english  @brief Mode for setting the timeout duration (ms) to infinite when no response is received from the device.
	@~japanese @brief �f�o�C�X���牞�����Ȃ��ꍇ�̃^�C���A�E�g����(ms)�𖳌��ɐݒ肷�郂�[�h */
#define PUC_XFER_TIMEOUT_INFINITE	0xFFFFFFFF
/*! @~english  @brief Constant value expressing the output magnification rate of synchronization signal is 0.5.
	@~japanese @brief �����M���o�͔{��0.5�{��\���萔 */
#define PUC_SYNC_OUT_MAGNIFICATION_0_5	0
/*! @~english  @brief Constant value expressing the thread count for multi thread decoding
	@~japanese @brief �}���`�X���b�h�Ńf�R�[�h����ۂ̃X���b�h�ő吔��\���萔 */
#define PUC_MAX_DECODE_THREAD_COUNT	32


/*! @~english  @brief Enumeration for ON/OFF setting
	@~japanese @brief ON�^OFF��\���񋓑� */
typedef enum
{
	/*! @~english  @brief OFF 
		@~japanese @brief OFF */
	PUC_OFF = 0,
	/*! @~english  @brief ON
		@~japanese @brief ON */
	PUC_ON = 1,
} PUC_MODE;

/*! @~english  @brief Enumeration for signal polarity
	@~japanese @brief �M���̋ɐ���\���񋓑� */
typedef enum
{
	/*! @~english  @brief Positive polarity signal
		@~japanese @brief ���ɐ��̐M�� */
	PUC_SIGNAL_POSI = 0,
	/*! @~english  @brief Negative polarity signal
		@~japanese @brief ���ɐ��̐M�� */
	PUC_SIGNAL_NEGA = 1,
} PUC_SIGNAL;

/*! @~english  @brief Enumeration for synchronization
	@~japanese @brief ������\���񋓑� */
typedef enum
{
	/*! @~english  @brief Internal operation
		@~japanese @brief �������� */
	PUC_SYNC_INTERNAL = 0,
	/*! @~english  @brief Synchronize to external signal
		@~japanese @brief �O������̐M���ɓ������� */
	PUC_SYNC_EXTERNAL = 1,
} PUC_SYNC_MODE;

/*! @~english  @brief Enumeration for device color/monochrome setting
	@~japanese @brief �f�o�C�X�̃J���[�^���m�N����\���񋓑� */
typedef enum
{
	/*! @~english  @brief Monochrome
		@~japanese @brief ���m�N�� */
	PUC_COLOR_MONO = 0,
	/*! @~english  @brief Color
		@~japanese @brief �J���[ */
	PUC_COLOR_COLOR = 1,
} PUC_COLOR_TYPE;

/*! @~english  @brief Enumeration for transfer data mode setting
	@~japanese @brief �]���f�[�^���[�h��\���񋓑� */
typedef enum
{
	/*! @~english  @brief Transfer compressed data
		@~japanese @brief ���k�f�[�^�]�� */
	PUC_DATA_COMPRESSED = 0,
	/*! @~english  @brief Transfer decompressed data(gray)
		@~japanese @brief �W�J�ς݂̃f�[�^�]��(�O���[) */
	PUC_DATA_DECOMPRESSED_GRAY = 1,
} PUC_DATA_MODE;


/*! @~english  @brief Device handle
	@~japanese @brief �f�o�C�X��\���n���h�� */
typedef void* PUC_HANDLE;
/*! @~english  @brief Pointer for the device handle
	@~japanese @brief �f�o�C�X��\���n���h���̃|�C���^ */
typedef PUC_HANDLE* PPUC_HANDLE;

/*! @~english  @brief Error code
	@~japanese @brief �G���[�R�[�h */
typedef enum
{
	/*! @~english  @brief Succeeded
		@~japanese @brief ���� */
	PUC_SUCCEEDED = 0,
	/*! @~english  @brief Initialization has not been performed. Please execute the PUC_Initialize function.
		@~japanese @brief ����������Ă��܂���BPUC_Initialize�֐������s���Ă��������B */
	PUC_ERROR_UNINITIALIZE = 1,
	/*! @~english  @brief Initialization is already complete.
		@~japanese @brief ���ɏ���������Ă��܂��B */
	PUC_ERROR_INITIALIZED = 2,
	/*! @~english  @brief The specified device number does not exist.
		@~japanese @brief �w�肳�ꂽ�f�o�C�X�ԍ��͑��݂��܂���B */
	PUC_ERROR_NOT_EXIST_DEVICE_NO = 3,
	/*! @~english  @brief The specified device handle is NULL.
		@~japanese @brief �w�肳�ꂽ�f�o�C�X�n���h����NULL�ł��B */
	PUC_ERROR_ILLEGAL_DEVICE_HANDLE = 4,
	/*! @~english  @brief The specified argument is NULL.
		@~japanese @brief �w�肳�ꂽ������NULL�ł��B */
	PUC_ERROR_ILLEGAL_ARG = 5,
	/*! @~english  @brief The specified resolution cannot be set.
		@~japanese @brief �w�肳�ꂽ�𑜓x�͐ݒ�ł��܂���B */
	PUC_ERROR_ILLEGAL_RESOLUTION = 6,
	/*! @~english  @brief The specified framerate cannot be set.
		@~japanese @brief �w�肳�ꂽ�B�e���x�͐ݒ�ł��܂���B */
	PUC_ERROR_ILLEGAL_FRAME_RATE = 7,
	/*! @~english  @brief The specified exposure time or non-exposure time (clock units) cannot be set.
		@~japanese @brief �w�肳�ꂽ�I�����Ԃ܂��͔�I������(�N���b�N�P��)�͐ݒ�ł��܂���B */
	PUC_ERROR_ILLEGAL_EXPOSE_CLOCK = 8,
	/*! @~english  @brief Failed to open the device.
		@~japanese @brief �f�o�C�X�̃I�[�v���Ɏ��s���܂����B */
	PUC_ERROR_DEVICE_OPEN = 9,
	/*! @~english  @brief The device is not open.
		@~japanese @brief �f�o�C�X���I�[�v������Ă��܂���B */
	PUC_ERROR_DEVICE_NOTOPEN = 10,
	/*! @~english  @brief Failed to read data from the device.
		@~japanese @brief �f�o�C�X����̃f�[�^�ǂݎ��Ɏ��s���܂����B */
	PUC_ERROR_DEVICE_READ = 11,
	/*! @~english  @brief Failed to write data to the device.
		@~japanese @brief �f�o�C�X�ւ̃f�[�^�������݂Ɏ��s���܂����B */
	PUC_ERROR_DEVICE_WRITE = 12,
	/*! @~english  @brief There are modules in the SDK that could not load.
		@~japanese @brief SDK���̈ꕔ���W���[�������[�h�ł��܂���ł����B */
	PUC_ERROR_MODULE_LOAD = 13,
	/*! @~english  @brief The exclusive process of the function has timed out.
		@~japanese @brief �֐��̔r���������^�C���A�E�g���܂����B */
	PUC_ERROR_LOCK_TIMEOUT = 14,
	/*! @~english  @brief Failed to send a GET command to the device.
		@~japanese @brief �f�o�C�X�ւ̎擾�R�}���h���M�Ɏ��s���܂����B */
	PUC_ERROR_GET_CMD = 15,
	/*! @~english  @brief Failed to send a SET command to the device.
		@~japanese @brief �f�o�C�X�ւ̐ݒ�R�}���h���M�Ɏ��s���܂����B */
	PUC_ERROR_SET_CMD = 16,
	/*! @~english  @brief The data of specified size could not be read from the device.
		@~japanese @brief �f�o�C�X����Ӑ}�����T�C�Y�̃f�[�^��ǂݍ��߂܂���ł����B */
	PUC_ERROR_NOTEQUAL_READ_SIZE = 17,
	/*! @~english  @brief The data of specified size could not be written to the device.
		@~japanese @brief �f�o�C�X�ɈӐ}�����T�C�Y�̃f�[�^���������߂܂���ł����B */
	PUC_ERROR_NOTEQUAL_WRITE_SIZE = 18,
	/*! @~english  @brief The header information in the data received from the device is invalid.
		@~japanese @brief �f�o�C�X�����M�����f�[�^�̃w�b�_�[��񂪕s���ł��B */
	PUC_ERROR_XFER_DATA_INVALID_HEADER = 19,
	/*! @~english  @brief Unable to start data transfer.
		@~japanese @brief �f�[�^�]�����J�n�ł��܂���ł����B */
	PUC_ERROR_XFER_DATA_BEGIN = 20,
	/*! @~english  @brief An unexpected error occurred during waiting for a data transfer from the device.
		@~japanese @brief �f�o�C�X����̃f�[�^�]���҂��ňӐ}���ʖ�肪�������܂����B */
	PUC_ERROR_XFER_DATA_WAIT = 21,
	/*! @~english  @brief The data transfer ended abnormally.
		@~japanese @brief �f�[�^�]���I��������ɍs���܂���ł����B */
	PUC_ERROR_XFER_DATA_FINISH = 22,
	/*! @~english  @brief Unable to process as a data transfer is in progress.
		@~japanese @brief �]�����̂��ߏ����ł��܂���ł����B */
	PUC_ERROR_XFERRING = 23,
	/*! @~english  @brief The specified ring buffer count is invalid.
		@~japanese @brief �w�肳�ꂽ�����O�o�b�t�@�����s���ł��B */
	PUC_ERROR_RING_BUF_COUNT = 24,
	/*! @~english  @brief Unable to process as a synchronize to external signal is in progress.
		@~japanese @brief �O���������̂��ߏ����ł��܂���ł����B */
	PUC_ERROR_SYNC_EXTERNAL = 25,
} PUCRESULT;

/*! @~english  @brief The macro to be positive when an error code is normal.
	@~japanese @brief �G���[�R�[�h�����펞�ɐ��ƂȂ�}�N�� */
#define PUC_CHK_SUCCEEDED(res) (res == PUC_SUCCEEDED)
/*! @~english  @brief The macro to be positive when an error code is not normal.
	@~japanese @brief �G���[�R�[�h������ȊO�̎��ɐ��ƂȂ�}�N�� */
#define PUC_CHK_FAILED(res) (res != PUC_SUCCEEDED)


/*!
	@struct PUC_DETECT_INFO
	@~english  @brief Structure for storing device search results
	@~japanese @brief �f�o�C�X�������ʂ��i�[����\����
*/
typedef struct
{
	/*! @~english  @brief Number of detected devices.
		@~japanese @brief ���������f�o�C�X�� */
	UINT32 nDeviceCount;
	/*! @~english  @brief List of device IDs found
		@~japanese @brief ���������f�o�C�X�ԍ��ꗗ */
	UINT32 nDeviceNoList[PUC_MAX_DEVICE];
} PUC_DETECT_INFO, *PPUC_DETECT_INFO;

/*!
	@struct PUC_RESO_LIMIT_INFO
	@~english  @brief Structure for storing resolution limit values
	@~japanese @brief �𑜓x�̌��E�l���i�[����\����
*/
typedef struct
{
	/*! @~english  @brief Maximum horizontal resolution
		@~japanese @brief �ő�𑜓x�� */
	UINT32 nMaxWidth;
	/*! @~english  @brief Maximum vertical resolution
		@~japanese @brief �ő�𑜓x����  */
	UINT32 nMaxHeight;
	/*! @~english  @brief Minimum horizontal resolution
		@~japanese @brief �ŏ��𑜓x�� */
	UINT32 nMinWidth;
	/*! @~english  @brief Minimum vertical resolution
		@~japanese @brief �ŏ��𑜓x���� */
	UINT32 nMinHeight;
	/*! @~english  @brief Minimum unit for altering the horizontal resolution
		@~japanese @brief �𑜓x���̕ύX�\�ȍŏ��P�� */
	UINT32 nUnitWidth;
	/*! @~english  @brief Minimum unit for altering the vertical resolution
		@~japanese @brief �𑜓x�����̕ύX�\�ȍŏ��P�� */
	UINT32 nUnitHeight;
} PUC_RESO_LIMIT_INFO, * PPUC_RESO_LIMIT_INFO;

/*!
	@struct PUC_XFER_DATA_INFO
	@~english  @brief Structure for storing the information of transfer data.
	@~japanese @brief �]���f�[�^�����i�[����\����
*/
typedef struct
{
	/*! @~english  @brief Location for unpacked transfer data. It is necessary to allocate the required amount in advance. The mode of transfer data depends on the transfer data mode setting (COMPRESSED/DECOMPRESSED).
		@~japanese @brief �]���f�[�^�̓W�J��B���炩���ߕK�v�ʊm�ۂ��Ă����K�v����B�]�������f�[�^�͓]���f�[�^���[�h(COMPRESSED/DECOMPRESSED)�Ɉˑ����� */
	PUINT8 pData;
	/*! @~english  @brief The size of transfer data. Stores the size of transfer data.
		@~japanese @brief �]���f�[�^�̃T�C�Y�B�]�����ꂽ�f�[�^�̃T�C�Y���i�[����� */
	UINT32 nDataSize;
	/*! @~english  @brief The sequence number of transfer data.
		@~japanese @brief �]���f�[�^�̃V�[�P���X�ԍ� */
	USHORT nSequenceNo;
} PUC_XFER_DATA_INFO, *PPUC_XFER_DATA_INFO;



/*! @~english  @brief The callback function type called during continuous transfer
	@~japanese @brief �A���]�����ɌĂ΂��R�[���o�b�N�֐��̌^ */
typedef void(*RECIEVE_CALLBACK)(PPUC_XFER_DATA_INFO, void*);




/*!
	@~english
		@brief This initializes the library.
		@details Only use this function once the first time PUCLIB is used. @n The termination operation is automatically performed when a process is terminated.
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
	@~japanese
		@brief �{���C�u���������������܂��B
		@details �����1�x�������s���Ă��������B@n�I�������͖{�v���Z�X�I�����Ɏ����I�ɍs���܂��B
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
*/
PUCRESULT WINAPI PUC_Initialize();

/*!
	@~english
		@brief This searches for the device.
		@details If the device number is already identified, the device can also be opened without searching it.
		@param[out] pDetectInfo Stores the information of detected device.
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_OpenDevice
	@~japanese
		@brief �f�o�C�X���������܂��B
		@details ���Ƀf�o�C�X�ԍ����������Ă���ꍇ�́A���������ɃI�[�v�����邱�Ƃ��\�ł��B
		@param[out] pDetectInfo ���������f�o�C�X�̏�񂪊i�[����܂��B
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_OpenDevice
*/
PUCRESULT WINAPI PUC_DetectDevice(PPUC_DETECT_INFO pDetectInfo);

/*!
	@~english
		@brief This opens the device.
		@details Note that specifying a device number of the opened device closes the device temporarily.
		@param[in] nDeviceNo Specify the retrieved device ID here.
		@param[out] pDeviceHandle Stores the handle to control the opened device.
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_CloseDevice
	@~japanese
		@brief �f�o�C�X���I�[�v�����܂��B
		@details ���ɃI�[�v�����̃f�o�C�X�ԍ����w�肷��ƈ�x�N���[�Y����܂��̂ł����ӂ��������B
		@param[in] nDeviceNo ���������f�o�C�X�ԍ����w�肵�܂��B
		@param[out] pDeviceHandle �I�[�v�������f�o�C�X�𑀍삷�邽�߂̃n���h�����i�[����܂��B
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_CloseDevice
*/
PUCRESULT WINAPI PUC_OpenDevice(UINT32 nDeviceNo, PPUC_HANDLE pDeviceHandle);

/*!
	@~english
		@brief This closes the device.
		@details An error will be returned when specifying an unopened device.
		@param[in] hDevice The device handle to be closed
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_OpenDevice
	@~japanese
		@brief �f�o�C�X���N���[�Y���܂��B
		@details �I�[�v�����Ă��Ȃ��f�o�C�X���w�肳���ƃG���[��Ԃ��܂��B
		@param[in] hDevice �N���[�Y����f�o�C�X�n���h��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_OpenDevice
*/
PUCRESULT WINAPI PUC_CloseDevice(PUC_HANDLE hDevice);

/*!
	@~english
		@brief This retrieves color/monochrome information of the device.
		@param[in] hDevice The device handle to be controlled
		@param[out] pType The storage destination for color/monochrome information
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
	@~japanese
		@brief �f�o�C�X�̃J���[�^���m�N�������擾���܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[out] pType �J���[�^���m�N�����̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
*/
PUCRESULT WINAPI PUC_GetColorType(PUC_HANDLE hDevice, PUC_COLOR_TYPE* pType);

/*!
	@~english
		@brief This retrieves the device name.
		@param[in] hDevice The device handle to be controlled
		@param[out] pID The storage destination for the device name
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
	@~japanese
		@brief �f�o�C�X�̖��O���擾���܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[out] pName �f�o�C�X���̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
*/
PUCRESULT WINAPI PUC_GetDeviceName(PUC_HANDLE hDevice, UINT32* pName);

/*!
	@~english
		@brief This retrieves the device type.
		@param[in] hDevice The device handle to be controlled
		@param[out] pID The storage destination for the device type
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
	@~japanese
		@brief �f�o�C�X�̃^�C�v���擾���܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[out] pType �f�o�C�X�^�C�v�̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
*/
PUCRESULT WINAPI PUC_GetDeviceType(PUC_HANDLE hDevice, UINT32* pType);

/*!
	@~english
		@brief This retrieves device version information.
		@param[in] hDevice The device handle to be controlled
		@param[out] pVersion The storage destination for the version number
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
	@~japanese
		@brief �f�o�C�X�̃o�[�W�������擾���܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[out] pVersion �o�[�W�����ԍ��̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
*/
PUCRESULT WINAPI PUC_GetDeviceVersion(PUC_HANDLE hDevice, UINT32* pVersion);

/*!
	@~english
		@brief This retrieves the device serial number.
		@param[in] hDevice The device handle to be controlled
		@param[out] pSerialNo The storage destination for the serial number
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
	@~japanese
		@brief �f�o�C�X�̃V���A���ԍ����擾���܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[out] pSerialNo �V���A���ԍ��̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
*/
PUCRESULT WINAPI PUC_GetSerialNo(PUC_HANDLE hDevice, UINT64* pSerialNo);

/*!
	@~english
		@brief This retrieves the device resolution.
		@param[in] hDevice The device handle to be controlled
		@param[out] pWidth The storage destination for the horizontal resolution
		@param[out] pHeight The storage destination for the vertical resolution
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_SetResolution
		@see PUC_GetMaxResolution
		@see PUC_GetResolutionLimit
	@~japanese
		@brief �f�o�C�X�̉𑜓x���擾���܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[out] pWidth ���𑜓x�̊i�[��
		@param[out] pHeight �c�𑜓x�̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_SetResolution
		@see PUC_GetMaxResolution
		@see PUC_GetResolutionLimit
*/
PUCRESULT WINAPI PUC_GetResolution(PUC_HANDLE hDevice, UINT32* pWidth, UINT32* pHeight);

/*!
	@~english
		@brief This retrieves the maximum resolution setting allowed for the current frame rate of the device.
		@param[in] hDevice The device handle to be controlled
		@param[out] pCurMaxWidth The storage destination for the maximum horizontal resolution setting allowed for the current framerate
		@param[out] pCurMaxHeight The storage destination for the maximum vertical resolution setting allowed for the current framerate
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_GetResolution
		@see PUC_SetResolution
		@see PUC_GetResolutionLimit
	@~japanese
		@brief �f�o�C�X�̌��݂̎B�e���x�Őݒ�\�ȍő�𑜓x���擾���܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[out] pCurMaxWidth ���݂̎B�e���x�Őݒ�\�ȍő剡�𑜓x�̊i�[��
		@param[out] pCurMaxHeight ���݂̎B�e���x�Őݒ�\�ȍő�c�𑜓x�̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_GetResolution
		@see PUC_SetResolution
		@see PUC_GetResolutionLimit
*/
PUCRESULT WINAPI PUC_GetMaxResolution(PUC_HANDLE hDevice, UINT32* pCurMaxWidth, UINT32* pCurMaxHeight);

/*!
	@~english
		@brief This retrieves the resolution limit for the device, and minimum unit for altering the resolution.
		@param[in] hDevice The device handle to be controlled
		@param[out] pLimitInfo The storage destination for resolution limit, and minimum unit for altering the resolution
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_GetResolution
		@see PUC_SetResolution
		@see PUC_GetMaxResolution
	@~japanese
		@brief �f�o�C�X�̌��E�𑜓x�A�ύX�\�ȍŏ��P�ʂ��擾���܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[out] pLimitInfo ���E�𑜓x�A�ύX�\�ȍŏ��P�ʂ̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_GetResolution
		@see PUC_SetResolution
		@see PUC_GetMaxResolution
*/
PUCRESULT WINAPI PUC_GetResolutionLimit(PUC_HANDLE hDevice, PPUC_RESO_LIMIT_INFO pLimitInfo);

/*!
	@~english
		@brief This sets the device resolution.
		@details Opening the device will reset this setting.
		@param[in] hDevice The device handle to be controlled
		@param[in] nWidth Horizontal resolution
		@param[in] nHeight Vertical resolution
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_GetResolution
		@see PUC_GetResolutionLimit
		@see PUC_GetMaxResolution
	@~japanese
		@brief �f�o�C�X�̉𑜓x��ݒ肵�܂��B
		@details �f�o�C�X�̃I�[�v�����ɐݒ�̓��Z�b�g����܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[in] nWidth ���𑜓x
		@param[in] nHeight �c�𑜓x
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_GetResolution
		@see PUC_GetResolutionLimit
		@see PUC_GetMaxResolution
*/
PUCRESULT WINAPI PUC_SetResolution(PUC_HANDLE hDevice, UINT32 nWidth, UINT32 nHeight);

/*!
	@~english
		@brief This retrieves one set of quantization table data stored to the device.
		@details The number of quantization tables is defined in PUC_Q_COUNT.
		@param[in] hDevice The device handle to be controlled
		@param[in] nPoint The position of the quantization table
		@param[out] pVal The storage destination of the quantization table data
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_SetQuantization
	@~japanese
		@brief �f�o�C�X�Ɋi�[����Ă���ʎq���e�[�u���f�[�^���P�擾���܂��B
		@details �ʎq���e�[�u���̌���PUC_Q_COUNT�Œ�`����Ă��܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[in] nPoint �ʎq���e�[�u���̈ʒu
		@param[out] pVal �ʎq���e�[�u���f�[�^�̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_SetQuantization
*/
PUCRESULT WINAPI PUC_GetQuantization(PUC_HANDLE hDevice, UINT32 nPoint, USHORT* pVal);

/*!
	@~english
		@brief This overwrites one set of quantization table data stored to the device.
		@details The number of quantization tables is defined in PUC_Q_COUNT. @n Restarting the device will reset this setting.
		@param[in] hDevice The device handle to be controlled
		@param[in] nPoint The position of the quantization table
		@param[in] nVal The quantization table data being set
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_GetQuantization
	@~japanese
		@brief �f�o�C�X�Ɋi�[����Ă���ʎq���e�[�u���f�[�^���P���������܂��B
		@details �ʎq���e�[�u���̌���PUC_Q_COUNT�Œ�`����Ă��܂��B@n�f�o�C�X���ċN������Ɛݒ�̓��Z�b�g����܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[in] nPoint �ʎq���e�[�u���̈ʒu
		@param[in] nVal �ݒ肷��ʎq���e�[�u���f�[�^
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_GetQuantization
*/
PUCRESULT WINAPI PUC_SetQuantization(PUC_HANDLE hDevice, UINT32 nPoint, USHORT nVal);

/*!
	@~english
		@brief This retrieves the state of the device fan.
		@param[in] hDevice The device handle to be controlled
		@param[out] nState The storage destination for the fan state (ON/OFF)
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_SetFanState
	@~japanese
		@brief �f�o�C�X�̃t�@���̏�Ԃ��擾���܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[out] nState �t�@����ԁiON�^OFF�j�̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_SetFanState
*/
PUCRESULT WINAPI PUC_GetFanState(PUC_HANDLE hDevice, PUC_MODE* pState);

/*!
	@~english
		@brief This sets the state of the device fan.
		@details Restarting the device will reset this setting.
		@param[in] hDevice The device handle to be controlled
		@param[in] nState The fan state (ON/OFF)
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_GetFanState
	@~japanese
		@brief �f�o�C�X�̃t�@���̏�Ԃ�ݒ肵�܂��B
		@details �f�o�C�X���ċN������Ɛݒ�̓��Z�b�g����܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[in] nState �t�@����ԁiON�^OFF�j
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_GetFanState
*/
PUCRESULT WINAPI PUC_SetFanState(PUC_HANDLE hDevice, PUC_MODE nState);

/*!
	@~english
		@brief This retrieves the synchronous signal input mode for the device.
		@param[in] hDevice The device handle to be controlled
		@param[out] pMode The storage destination for the synchronous signal input mode (Internal/External)
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_SetSyncInMode
	@~japanese
		@brief �f�o�C�X�̓����M�����̓��[�h���擾���܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[out] pMode �����M�����̓��[�h�iInternal�^External�j�̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_SetSyncInMode
*/
PUCRESULT WINAPI PUC_GetSyncInMode(PUC_HANDLE hDevice, PUC_SYNC_MODE* pMode);

/*!
	@~english
		@brief This sets the synchronous signal input mode for the device.
		@details Restarting the device will reset this setting. @n Changing the synchronization signal output mode resets the output magnification rate to x1.
				 @n When setting to external device synchronization, the exposure time is automatically adjusted considering the variation of external devices.
				 Set the exposure time and framerate before setting the external device synchronization.
		@param[in] hDevice The device handle to be controlled
		@param[in] nMode The synchronous signal input mode (Internal/External)
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_GetSyncInMode
	@~japanese
		@brief �f�o�C�X�̓����M�����̓��[�h��ݒ肵�܂��B
		@details �f�o�C�X���ċN������Ɛݒ�̓��Z�b�g����܂��B@n�����M�����̓��[�h��ς���Əo�͔{����x1�{�ɖ߂�܂��B
				 @n�O���@�퓯���ݒ莞�A�O���@��̂΂�����l�������I�����Ԃ֎����Œ�������܂��B���炩���ߎB�e�������I�����ԂƎB�e���x�ɕύX���Ă���A�O���@�퓯����ݒ肵�Ă��������B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[in] nMode �����M�����̓��[�h�iInternal�^External�j
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_GetSyncInMode
*/
PUCRESULT WINAPI PUC_SetSyncInMode(PUC_HANDLE hDevice, PUC_SYNC_MODE nMode);

/*!
	@~english
		@brief This retrieves the synchronization signal output polarity for the device.
		@param[in] hDevice The device handle to be controlled
		@param[out] pSignal The storage destination for the polarity (positive polarity/negative polarity)
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_SetSyncOutSignal
	@~japanese
		@brief �f�o�C�X�̓����M���o�͂̋ɐ����擾���܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[out] pSignal �ɐ��i���ɐ��^���ɐ��j�̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_SetSyncOutSignal
*/
PUCRESULT WINAPI PUC_GetSyncOutSignal(PUC_HANDLE hDevice, PUC_SIGNAL* pSignal);

/*!
	@~english
		@brief This sets the synchronous signal output polarity for the device.
		@details Restarting the device will reset this setting.
		@param[in] hDevice The device handle to be controlled
		@param[in] nSignal The polarity (positive polarity/negative polarity)
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_GetSyncOutSignal
	@~japanese
		@brief �f�o�C�X�̓����M���o�͂̋ɐ���ݒ肵�܂��B
		@details �f�o�C�X���ċN������Ɛݒ�̓��Z�b�g����܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[in] nSignal �ɐ��i���ɐ��^���ɐ��j
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_GetSyncOutSignal
*/
PUCRESULT WINAPI PUC_SetSyncOutSignal(PUC_HANDLE hDevice, PUC_SIGNAL nSignal);

/*!
	@~english
		@brief This retrieves the delay value of device's synchronization signal output in clock units.
		@param[in] hDevice The device handle to be controlled
		@param[out] pDelay The storage destination for the delay amount (clock units)
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_SetSyncOutDelay
	@~japanese
		@brief �f�o�C�X�̓����M���o�͂̒x���ʂ��N���b�N�P�ʂŎ擾���܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[out] pDelay �x����(�N���b�N�P��)�̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_SetSyncOutDelay
*/
PUCRESULT WINAPI PUC_GetSyncOutDelay(PUC_HANDLE hDevice, UINT32* pDelay);

/*!
	@~english
		@brief This sets the delay value of synchronization signal output for the device.
		@details Restarting the device will reset this setting.
		@param[in] hDevice The device handle to be controlled
		@param[in] nDelay The delay (clock units)
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_GetSyncOutDelay
	@~japanese
		@brief �f�o�C�X�̓����M���o�͂̒x���ʂ�ݒ肵�܂��B
		@details �f�o�C�X���ċN������Ɛݒ�̓��Z�b�g����܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[in] nDelay �x����(�N���b�N�P��)
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_GetSyncOutDelay
*/
PUCRESULT WINAPI PUC_SetSyncOutDelay(PUC_HANDLE hDevice, UINT32 nDelay);

/*!
	@~english
		@brief This retrieves the output width of synchronization signal for the device.
		@param[in] hDevice The device handle to be controlled
		@param[out] pWidth The storage destination for the output width (clock units)
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_SetSyncOutWidth
	@~japanese
		@brief �f�o�C�X�̓����M���o�͂̏o�͕����擾���܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[out] pWidth �o�͕�(�N���b�N�P��)�̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_SetSyncOutWidth
*/
PUCRESULT WINAPI PUC_GetSyncOutWidth(PUC_HANDLE hDevice, UINT32* pWidth);

/*!
	@~english
		@brief This sets the output width of synchronization signal for the device.
		@details Restarting the device will reset this setting. @n Changing the output width resets the output magnification rate to x1.
		@param[in] hDevice The device handle to be controlled
		@param[in] nWidth The output width of the synchronous signal (clock units).
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_GetSyncOutWidth
	@~japanese
		@brief �f�o�C�X�̓����M���o�͂̏o�͕���ݒ肵�܂��B
		@details �f�o�C�X���ċN������Ɛݒ�̓��Z�b�g����܂��B@n�o�͕���ς���Əo�͔{����x1�{�ɖ߂�܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[in] nWidth �����M���̏o�͕�(�N���b�N�P��)�B
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_GetSyncOutWidth
*/
PUCRESULT WINAPI PUC_SetSyncOutWidth(PUC_HANDLE hDevice, UINT32 nWidth);

/*!
	@~english
		@brief This retrieves the output magnification rate for the synchronization signal.
		@param[in] hDevice The device handle to be controlled
		@param[out] pMagnification The storage destination for the output magnification
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_SetSyncOutMagnification
		@see PUC_SetSyncOutWidth
		@see PUC_GetSyncOutWidth
	@~japanese
		@brief �����M���̏o�͔{�����擾���܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[out] pMagnification �o�͔{���̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_SetSyncOutMagnification
		@see PUC_SetSyncOutWidth
		@see PUC_GetSyncOutWidth
*/
PUCRESULT WINAPI PUC_GetSyncOutMagnification(PUC_HANDLE hDevice, UINT32* pMagnification);

/*!
	@~english
		@brief This sets the output magnification rate for the synchronization signal.
		@details Opening the device will reset this setting. @n Changing the frame rate or exposure/non-exposure time also resets the output magnification rate to x1.
		@param[in] hDevice The device handle to be controlled
		@param[in] nMagnification The output magnification (e.g.: for 2x set to 2, for 4x set to 4). For 0.5x, set PUC_SYNC_OUT_MAGNIFICATION_0_5.
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_GetSyncOutMagnification
		@see PUC_SetSyncOutWidth
		@see PUC_GetSyncOutWidth
	@~japanese
		@brief �����M���̏o�͔{����ݒ肵�܂��B
		@details �f�o�C�X�̃I�[�v�����ɐݒ�̓��Z�b�g����܂��B@n�B�e���x��I���E��I�����Ԃ�ύX�����ꍇ��x1�{�Ƀ��Z�b�g����܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[in] nMagnification �o�͔{���i��Fx2�̏ꍇ��2�Ax4�̏ꍇ��4�j0.5�{�̏ꍇ��PUC_SYNC_OUT_MAGNIFICATION_0_5���w��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_GetSyncOutMagnification
		@see PUC_SetSyncOutWidth
		@see PUC_GetSyncOutWidth
*/
PUCRESULT WINAPI PUC_SetSyncOutMagnification(PUC_HANDLE hDevice, UINT32 nMagnification);

/*!
	@~english
		@brief This retrieves the LED state of the device.
		@param[in] hDevice The device handle to be controlled
		@param[out] pMode The storage destination for the LED state (ON/OFF)
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_SetLEDMode
	@~japanese
		@brief �f�o�C�X��LED��Ԃ��擾���܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[out] pMode LED�̏�ԁiON�^OFF�j�̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_SetLEDMode
*/
PUCRESULT WINAPI PUC_GetLEDMode(PUC_HANDLE hDevice, PUC_MODE* pMode);

/*!
	@~english
		@brief This sets the LED state of the device.
		@details Restarting the device will reset this setting.
		@param[in] hDevice The device handle to be controlled
		@param[in] nMode The LED state (ON/OFF)
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_GetLEDMode
	@~japanese
		@brief �f�o�C�X��LED��Ԃ�ݒ肵�܂��B
		@details �f�o�C�X���ċN������Ɛݒ�̓��Z�b�g����܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[in] nMode LED�̏�ԁiON�^OFF�j
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_GetLEDMode
*/
PUCRESULT WINAPI PUC_SetLEDMode(PUC_HANDLE hDevice, PUC_MODE nMode);

/*!
	@~english
		@brief This retrieves the device sensor temperature.
		@param[in] hDevice The device handle to be controlled
		@param[out] pTemp The storage destination for the sensor temperature
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
	@~japanese
		@brief �f�o�C�X�̃Z���T�[���x���擾���܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[out] pTemp �Z���T�[�̉��x�̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
*/
PUCRESULT WINAPI PUC_GetSensorTemperature(PUC_HANDLE hDevice, UINT32* pTemp);

/*!
	@~english
		@brief This retrieves the data transfer mode of the device.
		@param[in] hDevice The device handle to be controlled
		@param[out] pDataMode The storage destination for the data mode
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_SetXferDataMode
	@~japanese
		@brief �f�o�C�X�̓]���f�[�^���[�h���擾���܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[out] pDataMode �f�[�^���[�h�̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_SetXferDataMode
*/
PUCRESULT WINAPI PUC_GetXferDataMode(PUC_HANDLE hDevice, PUC_DATA_MODE* pDataMode);

/*!
	@~english
		@brief This sets the data transfer mode of the device.
		@details Opening the device will reset this setting.
		@param[in] hDevice The device handle to be controlled
		@param[in] nDataMode The data mode
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe. If PUC_DATA_DECOMPRESSED_GRAY is specified, decoding will be performed in a single thread.
		@see PUC_GetXferDataMode
	@~japanese
		@brief �f�o�C�X�̓]���f�[�^���[�h��ݒ肵�܂��B
		@details �f�o�C�X�̃I�[�v�����ɐݒ�̓��Z�b�g����܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[in] nDataMode �f�[�^���[�h
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��BPUC_DATA_DECOMPRESSED_GRAY���w�肵���ꍇ�f�R�[�h�̓V���O���X���b�h�ōs���܂��B
		@see PUC_GetXferDataMode
*/
PUCRESULT WINAPI PUC_SetXferDataMode(PUC_HANDLE hDevice, PUC_DATA_MODE nDataMode);

/*!
	@~english
		@brief This retrieves the size of transfer data from the device.
		@details This will vary depending on the current resolution.
		@param[in] hDevice The device handle to be controlled
		@param[in] nDataMode The data mode. The data size for the mode specified here will be returned.
		@param[out] pDataSize The storage destination for the data size
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_GetMaxXferDataSize
	@~japanese
		@brief �f�o�C�X����]�������f�[�^�T�C�Y���擾���܂��B
		@details ���݂̉𑜓x�ɂ�茋�ʂ��قȂ�܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[in] nDataMode �f�[�^���[�h�B�����Ŏw�肳�ꂽ���[�h�ɑ΂���f�[�^�T�C�Y��ԋp���܂��B
		@param[out] pDataSize �f�[�^�T�C�Y�̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_GetMaxXferDataSize
*/
PUCRESULT WINAPI PUC_GetXferDataSize(PUC_HANDLE hDevice, PUC_DATA_MODE nDataMode, UINT32* pDataSize);

/*!
	@~english
		@brief This retrieves the maximum size of transfer data from the device.
		@details This will vary depending on the current resolution.
		@param[in] hDevice The device handle to be controlled
		@param[in] nDataMode The data mode. The data size for the mode specified here will be returned.
		@param[out] pDataSize The storage destination for the maximum data size
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_GetXferDataSize
	@~japanese
		@brief �f�o�C�X����]�������f�[�^�̍ő�T�C�Y���擾���܂��B
		@details ���݂̉𑜓x�ɂ�茋�ʂ��قȂ�܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[in] nDataMode �f�[�^���[�h�B�����Ŏw�肳�ꂽ���[�h�ɑ΂���f�[�^�T�C�Y��ԋp���܂��B
		@param[out] pDataSize �ő�f�[�^�T�C�Y�̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_GetXferDataSize
*/
PUCRESULT WINAPI PUC_GetMaxXferDataSize(PUC_HANDLE hDevice, PUC_DATA_MODE nDataMode, UINT32* pDataSize);

/*!
	@~english
		@brief This retrieves the current live image from the device.
		@details The image may appear fuzzy during continuous transfer. @n
			Retrieve the size of the image data with PUC_GetXferDataSize. @n
			The type of images to be retrieved can be set with PUC_SetXferDataMode. @n
			Compressed data can be unpacked to luminace data with PUC_DecodeData.
		@param[in] hDevice The device handle to be controlled
		@param[out] pXferData The storage destination for transfer data. Retrieve the required memory size with PUC_GetXferDataSize. @n
			When using PUC_DATA_DECOMPRESSED_GRAY, a size rounded up to a multiple of 4 must be allocated for the width.
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_GetXferDataSize
		@see PUC_DecodeData
	@~japanese
		@brief �f�o�C�X����ŐV�̃��C�u�摜��1���擾���܂��B
		@details �A���]�����͉摜���ꕔ�����ꍇ������܂��B@n
			�摜�f�[�^�̃T�C�Y��PUC_GetXferDataSize�Ŏ擾���Ă��������B@n
			�擾����摜�̎�ނ�PUC_SetXferDataMode�Őݒ�ł��܂��B@n
			���k�f�[�^��PUC_DecodeData���g�p���邱�ƂŋP�x�f�[�^�ɓW�J�ł��܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[out] pXferData �]���f�[�^�̊i�[��B�K�v�ȃ������T�C�Y��PUC_GetXferDataSize�Ŏ擾���Ă��������B@n
			PUC_DATA_DECOMPRESSED_GRAY�̏ꍇ�A������4�̔{���ɐ؂�グ���T�C�Y���m�ۂ���Ă���K�v������܂��B
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_GetXferDataSize
		@see PUC_DecodeData
*/
PUCRESULT WINAPI PUC_GetSingleXferData(PUC_HANDLE hDevice, PPUC_XFER_DATA_INFO pXferData);

/*!
	@~english
		@brief This starts continuous transfer.
		@details If the callback function takes a long time to process, sequential image data will be stored to the ring buffer set in PUC_SetRingBufferCount. @n
			If the ring buffer is used up, it will wait until the callback function process is complete. Be aware that any data received during this period will not be stored to the buffer. (Dropped frames)
		@param[in] hDevice The device handle to be controlled
		@param[in] callback This callback function is called every time an image is received from the device in the SDK.
		@param[in] arg The argument passed to the callback function
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_EndXferData
		@see PUC_IsXferring
		@see PUC_SetRingBufferCount
		@see PUC_DecodeData
	@~japanese
		@brief �A���]�����n�߂܂��B
		@details �R�[���o�b�N�֐��̏������Ԃ������ꍇ�APUC_SetRingBufferCount�Őݒ肵�������O�o�b�t�@���ɏ����摜�f�[�^���i�[����܂��B@n
			�����O�o�b�t�@���ꏄ����ƃR�[���o�b�N�֐��̏��������҂��ƂȂ�A���̊Ԃ̎�M�f�[�^�̓o�b�t�@�Ɋi�[����܂���̂ł����ӂ��������B�i�t���[�������j
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[in] callback SDK�����Ńf�o�C�X����1���摜����M���邽�сA���̃R�[���o�b�N�֐����Ă΂�܂��B
		@param[in] arg �R�[���o�b�N�֐��ɓn������
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_EndXferData
		@see PUC_IsXferring
		@see PUC_SetRingBufferCount
		@see PUC_DecodeData
*/
PUCRESULT WINAPI PUC_BeginXferData(PUC_HANDLE hDevice, RECIEVE_CALLBACK callback, void* arg);

/*!
	@~english
		@brief This finishes continuous transfer.
		@param[in] The device handle to be controlled
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_BeginXferData
		@see PUC_IsXferring
	@~japanese
		@brief �A���]�����I�����܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_BeginXferData
		@see PUC_IsXferring
*/
PUCRESULT WINAPI PUC_EndXferData(PUC_HANDLE hDevice);

/*!
	@~english
		@brief This checks whether a continuous transfer is in progress.
		@param[in] hDevice The device handle to be controlled
		@param[out] pIsXferring If a continuous transfer is in progress this will be TRUE, if not this will be FALSE.
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_BeginXferData
		@see PUC_EndXferData
	@~japanese
		@brief �A���]�������ǂ������m�F���܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[out] pIsXferring �A���]�����̏ꍇ��TRUE�A����ȊO��FALSE���i�[���܂��B
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_BeginXferData
		@see PUC_EndXferData
*/
PUCRESULT WINAPI PUC_IsXferring(PUC_HANDLE hDevice, BOOL* pIsXferring);

/*!
	@~english
		@brief This extracts the sequence number from the compressed image data.
		@param[in] pData The compressed image data
		@param[in] nWidth The image width
		@param[in] nHeight The image height
		@param[out] pSeqNo The storage destination for the sequence number extracted
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe. This function can be executed in parallel.
	@~japanese
		@brief ���k�摜�f�[�^����V�[�P���X�ԍ��𒊏o���܂��B
		@param[in] pData ���k�摜�f�[�^
		@param[in] nWidth �摜�̉���
		@param[in] nHeight �摜�̍���
		@param[out] pSeqNo ���o�����V�[�P���X�ԍ��̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B�{�֐��͕�����s���\�ł��B
*/
PUCRESULT WINAPI PUC_ExtractSequenceNo(const PUCHAR pData, UINT32 nWidth, UINT32 nHeight, PUSHORT pSeqNo);

/*!
	@~english
		@brief This unpacks the compressed image data to luminance data.
		@param[out] pDst The buffer at the unpacking destination. The size of the width must be allocated rounded up to a multiple of four. (e.g., If the width is 1246 px, a buffer is required 1248 bytes at least)
		@param[in] nX The upper left coordinate X for starting unpacking. This must be 0, or a multiple of 8.
		@param[in] nY The upper left coordinate Y for starting unpacking. This must be 0, or a multiple of 8.
		@param[in] nWidth The width for unpacking
		@param[in] nHeight The height for unpacking
		@param[in] nLineBytes The number of bytes of the buffer width at the unpacking destination
		@param[in] pSrc The compressed image data
		@param[in] pQVals A quantization table
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe. This function can be executed in parallel.
		@see PUC_GetXferDataSize
		@see PUC_GetMaxXferDataSize
	@~japanese
		@brief ���k�摜�f�[�^���P�x�l�f�[�^�ɓW�J���܂��B
		@param[out] pDst �W�J��o�b�t�@�B������4�̔{���ɐ؂�グ���T�C�Y���m�ۂ���Ă���K�v������܂��B�i��F������1246px�̏ꍇ�A�o�b�t�@��1248�o�C�g�m�ۂ���Ă���K�v����j
		@param[in] nX �W�J�J�n���鍶����WX�B0��������8�̔{���ł���K�v������܂��B
		@param[in] nY �W�J�J�n���鍶����WY�B0��������8�̔{���ł���K�v������܂��B
		@param[in] nWidth �W�J���鉡��
		@param[in] nHeight �W�J���鍂��
		@param[in] nLineBytes �W�J��o�b�t�@�̉����̃o�C�g��
		@param[in] pSrc ���k�摜�f�[�^
		@param[in] pQVals �ʎq���e�[�u��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B�{�֐��͕�����s���\�ł��B
		@see PUC_GetXferDataSize
		@see PUC_GetMaxXferDataSize
*/
PUCRESULT WINAPI PUC_DecodeData(PUINT8 pDst, UINT32 nX, UINT32 nY, UINT32 nWidth, UINT32 nHeight, UINT32 nLineBytes, const PUINT8 pSrc, const PUSHORT pQVals);

/*!
	@~english
		@brief This unpacks the compressed image data to luminance data. This process is multithreaded.
		@param[out] pDst The buffer at the unpacking destination. The size of the width must be allocated rounded up to a multiple of four. (e.g., If the width is 1246 px, a buffer is required 1248 bytes at least)
		@param[in] nX The upper left coordinate X for starting unpacking. This must be 0, or a multiple of 8.
		@param[in] nY The upper left coordinate Y for starting unpacking. This must be 0, or a multiple of 8.
		@param[in] nWidth The width for unpacking
		@param[in] nHeight The height for unpacking
		@param[in] nLineBytes The number of bytes of the buffer width at the unpacking destination
		@param[in] pSrc The compressed image data
		@param[in] pQVals A quantization table
		@param[in] nThreadCount The number of threads to process in multiple threads.
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe. This function can be executed in parallel.
		@see PUC_GetXferDataSize
		@see PUC_GetMaxXferDataSize
		@see PUC_DecodeData
	@~japanese
		@brief ���k�摜�f�[�^���P�x�l�f�[�^�ɓW�J���܂��B���̃f�R�[�h�����̓}���`�X���b�h�ōs���܂��B
		@param[out] pDst �W�J��o�b�t�@�B������4�̔{���ɐ؂�グ���T�C�Y���m�ۂ���Ă���K�v������܂��B�i��F������1246px�̏ꍇ�A�o�b�t�@��1248�o�C�g�m�ۂ���Ă���K�v����j
		@param[in] nX �W�J�J�n���鍶����WX�B0��������8�̔{���ł���K�v������܂��B
		@param[in] nY �W�J�J�n���鍶����WY�B0��������8�̔{���ł���K�v������܂��B
		@param[in] nWidth �W�J���鉡��
		@param[in] nHeight �W�J���鍂��
		@param[in] nLineBytes �W�J��o�b�t�@�̉����̃o�C�g��
		@param[in] pSrc ���k�摜�f�[�^
		@param[in] pQVals �ʎq���e�[�u��
		@param[in] nThreadCount �}���`�X���b�h�ŏ�������X���b�h��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B�{�֐��͕�����s���\�ł��B
		@see PUC_GetXferDataSize
		@see PUC_GetMaxXferDataSize
		@see PUC_DecodeData
*/
PUCRESULT WINAPI PUC_DecodeDataMultiThread(PUINT8 pDst, UINT32 nX, UINT32 nY, UINT32 nWidth, UINT32 nHeight, UINT32 nLineBytes, const PUINT8 pSrc, const PUSHORT pQVals, UINT32 nThreadCount);

/*!
	@~english
		@brief This unpacks the compressed image data to DCT coefficients.
		@param[out] pDst The buffer at the unpacking destination. The size of the width must be allocated rounded up to a multiple of four. (e.g., If the width is 1246 px, a buffer is required 1248 bytes at least)
		@param[in] nX The upper left coordinate X for starting unpacking. This must be 0, or a multiple of 8.
		@param[in] nY The upper left coordinate Y for starting unpacking. This must be 0, or a multiple of 8.
		@param[in] nWidth The width for unpacking
		@param[in] nHeight The height for unpacking
		@param[in] nLineBytes The number of bytes of the buffer width at the unpacking destination
		@param[in] pSrc The compressed image data
		@param[in] pQVals A quantization table
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe. This function can be executed in parallel.
		@see PUC_GetXferDataSize
		@see PUC_GetMaxXferDataSize
	@~japanese
		@brief ���k�摜�f�[�^��DCT�W���ɓW�J���܂��B
		@param[out] pDst �W�J��o�b�t�@�B������4�̔{���ɐ؂�グ���T�C�Y���m�ۂ���Ă���K�v������܂��B�i��F������1246px�̏ꍇ�A�o�b�t�@��1248�o�C�g�m�ۂ���Ă���K�v����j
		@param[in] nX �W�J�J�n���鍶����WX�B0��������8�̔{���ł���K�v������܂��B
		@param[in] nY �W�J�J�n���鍶����WY�B0��������8�̔{���ł���K�v������܂��B
		@param[in] nWidth �W�J���鉡��
		@param[in] nHeight �W�J���鍂��
		@param[in] nLineBytes �W�J��o�b�t�@�̉����̃o�C�g��
		@param[in] pSrc ���k�摜�f�[�^
		@param[in] pQVals �ʎq���e�[�u��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B�{�֐��͕�����s���\�ł��B
		@see PUC_GetXferDataSize
		@see PUC_GetMaxXferDataSize
*/
PUCRESULT WINAPI PUC_DecodeDCTData(PINT16 pDst, UINT32 nX, UINT32 nY, UINT32 nWidth, UINT32 nHeight, UINT32 nLineBytes, const PUINT8 pSrc, const PUSHORT pQVals);

/*!
	@~english
		@brief This retrieves the ring buffer count for continuous transfer.
		@param[in] hDevice The device handle to be controlled
		@param[out] pCount The storage destination for the buffer count
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_SetRingBufferCount
	@~japanese
		@brief �A���]�����̃����O�o�b�t�@�����擾���܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[out] pCount �o�b�t�@���̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_SetRingBufferCount
*/
PUCRESULT WINAPI PUC_GetRingBufferCount(PUC_HANDLE hDevice, UINT32* pCount);

/*!
	@~english
		@brief This sets the ring buffer count for continuous transfer.
		@details Opening the device will reset this setting.
		@param[in] hDevice The device handle to be controlled
		@param[in] nCount The buffer count
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_GetRingBufferCount
	@~japanese
		@brief �A���]�����̃����O�o�b�t�@����ݒ肵�܂��B
		@details �f�o�C�X�̃I�[�v�����ɐݒ�̓��Z�b�g����܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[in] nCount �o�b�t�@��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_GetRingBufferCount
*/
PUCRESULT WINAPI PUC_SetRingBufferCount(PUC_HANDLE hDevice, UINT32 nCount);

/*!
	@~english
		@brief This retrieves the timeout duration (ms) for data transfer from the device.
		@param[in] hDevice The device handle to be controlled
		@param[out] pSingleXferTimeOut The storage destination for the timeout duration (ms) for a single transfer
		@param[out] pContinuousXferTimeOut The storage destination for the timeout duration (ms) for continuous transfer
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_SetXferTimeOut
	@~japanese
		@brief �f�o�C�X�̓]�����̃^�C���A�E�g����(ms)���擾���܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[out] pSingleXferTimeOut �V���O���]���̃^�C���A�E�g����(ms)�̊i�[��
		@param[out] pContinuousXferTimeOut �A���]���̃^�C���A�E�g����(ms)�̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_SetXferTimeOut
*/
PUCRESULT WINAPI PUC_GetXferTimeOut(PUC_HANDLE hDevice, UINT32* pSingleXferTimeOut, UINT32* pContinuousXferTimeOut);

/*!
	@~english
		@brief This sets the timeout duration (ms) for data transfer from the device.
		@details Opening the device will reset this setting. @n
			Set PUC_XFER_TIMEOUT_AUTO to automatically adjust the timeout duration based on the framerate. @n
			Set PUC_XFER_TIMEOUT_INFINITE to disable timeout.
		@param[in] hDevice The device handle to be controlled
		@param[in] nSingleXferTimeOut The timeout duration (ms) for a single transfer
		@param[in] nContinuousXferTimeOut The timeout duration (ms) for continuous transfer
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_GetXferTimeOut
	@~japanese
		@brief �f�o�C�X�̓]�����̃^�C���A�E�g����(ms)��ݒ肵�܂��B
		@details �f�o�C�X�̃I�[�v�����ɐݒ�̓��Z�b�g����܂��B@n
			PUC_XFER_TIMEOUT_AUTO���w�肷��ƁA�B�e���x�ɉ����Ď����Ń^�C���A�E�g�𒲐����܂��B@n
			PUC_XFER_TIMEOUT_INFINITE���w�肷��ƁA�^�C���A�E�g�͂Ȃ��Ȃ�܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[in] nSingleXferTimeOut �V���O���]���̃^�C���A�E�g����(ms)
		@param[in] nContinuousXferTimeOut �A���]���̃^�C���A�E�g����(ms)
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_GetXferTimeOut
*/
PUCRESULT WINAPI PUC_SetXferTimeOut(PUC_HANDLE hDevice, UINT32 nSingleXferTimeOut, UINT32 nContinuousXferTimeOut);

/*!
	@~english
		@brief This retrieves the maximum framerate for the device.
		@param[in] hDevice The device handle to be controlled
		@param[out] pFramerate The storage destination for the maximum framerate
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_GetFramerateShutter
	@~japanese
		@brief �f�o�C�X�̍ő�B�e���x���擾���܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[out] pFramerate �ő�B�e���x�̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_GetFramerateShutter
*/
PUCRESULT WINAPI PUC_GetMaxFramerate(PUC_HANDLE hDevice, UINT32* pFramerate);

/*!
	@~english
		@brief This retrieves the framerate and the shutter speed (1/fps) for the device.
		@details Note that the return value with this function will be invalid if the exposure/non-exposure time is set directly with PUC_SetExposeTime function.
		@param[in] hDevice The device handle to be controlled
		@param[out] pFramerate The storage destination for the framerate
		@param[out] pShutterSpeedFps The storage destination for the shutter speed (1/fps)
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_SetFramerateShutter
		@see PUC_SetExposeTime
	@~japanese
		@brief �f�o�C�X�̎B�e���x����уV���b�^�[���x(1/fps)���擾���܂��B
		@details PUC_SetExposeTime�֐��ɂ��I���E��I�����Ԃ𒼐ڐݒ肵���ꍇ�A�{�֐��ŕԂ����l�͕s���Ȓl�ɂȂ�܂��̂ł����ӂ��������B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[out] pFramerate �B�e���x�̊i�[��
		@param[out] pShutterSpeedFps �V���b�^�[���x(1/fps)�̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_SetFramerateShutter
		@see PUC_SetExposeTime
*/
PUCRESULT WINAPI PUC_GetFramerateShutter(PUC_HANDLE hDevice, UINT32* pFramerate, UINT32* pShutterSpeedFps);

/*!
	@~english
		@brief This sets the framerate and the shutter speed (1/fps) for the device.
		@details Opening the device will reset this setting. @n When executing this function, the return value of PUC_GetExposeTime will change. @n Changing the frame rate resets the output magnification rate of synchronization signal to x1.
		@param[in] hDevice The device handle to be controlled
		@param[in] nFramerate The framerate
		@param[in] nShutterSpeedFps The shutter speed (1/fps)
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_GetExposeTime
		@see PUC_SetExposeTime
	@~japanese
		@brief �f�o�C�X�̎B�e���x����уV���b�^�[���x(1/fps)��ݒ肵�܂��B
		@details �f�o�C�X�̃I�[�v�����ɐݒ�̓��Z�b�g����܂��B@n�{�֐������s����ƁAPUC_GetExposeTime�ŕԋp�����l���ύX����܂��B@n�t���[�����[�g��ς���Ɠ����M���̏o�͔{����x1�{�ɖ߂�܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[in] nFramerate �B�e���x
		@param[in] nShutterSpeedFps �V���b�^�[���x(1/fps)
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_GetExposeTime
		@see PUC_SetExposeTime
*/
PUCRESULT WINAPI PUC_SetFramerateShutter(PUC_HANDLE hDevice, UINT32 nFramerate, UINT32 nShutterSpeedFps);

/*!
	@~english
		@brief This retrieves the exposure/non-exposure time of the device.
		@details The return value of this function will change if the frame rate and shutter speed is changed with PUC_SetFramerateShutter function. @n Changing the exposure/non-exposure time resets the output magnification rate of synchronization signal to x1.
		@param[in] hDevice The device handle to be controlled
		@param[out] pExpOnClk The storage destination for the exposure period (clock units)
		@param[out] pExpOffClk The storage destination for the non-exposure period (clock units)
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_SetExposeTime
		@see PUC_SetFramerateShutter
	@~japanese
		@brief �f�o�C�X�̘I���E��I�����Ԃ��擾���܂��B
		@details PUC_SetFramerateShutter�֐��ŎB�e���x����уV���b�^�[���x���ύX�����ƁA�{�֐��ŕԋp�����l���ς��܂��B@n�I���E��I�����Ԃ�ς���Ɠ����M���̏o�͔{����x1�{�ɖ߂�܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[out] pExpOnClk �I�����ԁi�N���b�N�P�ʁj�̊i�[��
		@param[out] pExpOffClk ��I�����ԁi�N���b�N�P�ʁj�̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_SetExposeTime
		@see PUC_SetFramerateShutter
*/
PUCRESULT WINAPI PUC_GetExposeTime(PUC_HANDLE hDevice, UINT32* pExpOnClk, UINT32* pExpOffClk);

/*!
	@~english
		@brief This sets the exposure/non-exposure time of the device.
		@details Opening the device will reset this setting. @n Note that the return value of PUC_GetFramerateShutter function will be invalid if the exposure/non-exposure time is set directly with this function.
		@param[in] hDevice The device handle to be controlled
		@param[in] nExpOnClk The exposure period (clock units)
		@param[in] nExpOffClk The non-exposure period (clock units)
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_GetExposeTime
		@see PUC_GetFramerateShutter
	@~japanese
		@brief �f�o�C�X�̘I���E��I�����Ԃ�ݒ肵�܂��B
		@details �f�o�C�X�̃I�[�v�����ɐݒ�̓��Z�b�g����܂��B@n�{�֐��ɂ��I���E��I�����Ԃ𒼐ڐݒ肵���ꍇ�APUC_GetFramerateShutter�֐��ŕԂ����l�͕s���Ȓl�ɂȂ�܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[in] nExpOnClk �I�����ԁi�N���b�N�P�ʁj
		@param[in] nExpOffClk ��I�����ԁi�N���b�N�P�ʁj
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_GetExposeTime
		@see PUC_GetFramerateShutter
*/
PUCRESULT WINAPI PUC_SetExposeTime(PUC_HANDLE hDevice, UINT32 nExpOnClk, UINT32 nExpOffClk);

/*!
	@~english
		@brief This retrieves the minimum exposure/non-exposure time of the device.
		@param[in] hDevice The device handle to be controlled
		@param[out] pMinExpOnClk The storage destination for the minimum exposure period (clock units)
		@param[out] pMinExpOffClk The storage destination for the minimum non-exposure period (clock units)
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_SetExposeTime
	@~japanese
		@brief �f�o�C�X�̍ŏ��I���E��I�����Ԃ��擾���܂��B
		@param[in] hDevice ����Ώۂ̃f�o�C�X�n���h��
		@param[out] pMinExpOnClk �ŏ��I�����ԁi�N���b�N�P�ʁj�̊i�[��
		@param[out] pMinExpOffClk �ŏ���I�����ԁi�N���b�N�P�ʁj�̊i�[��
		@return ��������PUC_SUCCEEDED�A���s���͂���ȊO���Ԃ�܂��B
		@note �{�֐��̓X���b�h�Z�[�t�ł��B
		@see PUC_SetExposeTime
*/
PUCRESULT WINAPI PUC_GetMinExposeTime(PUC_HANDLE hDevice, UINT32* pMinExpOnClk, UINT32* pMinExpOffClk);


#ifdef __cplusplus
}
#endif

#endif /* __PUCLIB_H */