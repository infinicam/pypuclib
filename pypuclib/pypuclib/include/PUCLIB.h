#ifndef __PUCLIB_H
#define __PUCLIB_H

/*! 
	@mainpage
	@~english
		@brief This SDK is a Windows-compatible library that controls the PHOTRON high-speed camera "INFINICAM" from a PC.@n
			See the quick manual for basic usage of this SDK. This reference describes all available constants, enumerations, structures, and functions.
	@copyright Copyright (C) 2022 PHOTRON LIMITED

	@~japanese
		@brief 本SDKは、フォトロン高速度カメラ「INFINICAM」をPCからコントロールするWindows専用のライブラリです。@n
			SDKの基本的な使い方はクイックマニュアルをご覧ください。本資料では、利用可能な全ての定数、列挙体、構造体、関数について記載しています。
	@copyright Copyright (C) 2022 PHOTRON LIMITED
*/

#ifdef	__cplusplus
extern "C" {
#endif

/*! @~english  @brief Maximum number of connectable devices
	@~japanese @brief 接続可能な最大デバイス数 */
#define PUC_MAX_DEVICE				16
/*! @~english  @brief Maximum number of characters.
	@~japanese @brief 最大文字数 */
#define PUC_MAX_LEN					256
/*! @~english  @brief Quantization table count (8*8)
	@~japanese @brief 量子化テーブルの個数(8*8) */
#define PUC_Q_COUNT					64
/*! @~english  @brief Minimum ring buffer count for continuous transfer.
	@~japanese @brief 連続転送時の最小リングバッファ数 */
#define PUC_MIN_RING_BUF_COUNT		4
/*! @~english  @brief Maximum ring buffer count for continuous transfer.
	@~japanese @brief 連続転送時の最大リングバッファ数 */
#define PUC_MAX_RING_BUF_COUNT		65535
/*! @~english  @brief Mode for automatically setting the timeout duration (ms) based on the frame rate when no response is received from the device.
	@~japanese @brief デバイスから応答がない場合のタイムアウト時間(ms)を、撮影速度に応じて自動で設定するモード */
#define PUC_XFER_TIMEOUT_AUTO		0
/*! @~english  @brief Mode for setting the timeout duration (ms) to infinite when no response is received from the device.
	@~japanese @brief デバイスから応答がない場合のタイムアウト時間(ms)を無限に設定するモード */
#define PUC_XFER_TIMEOUT_INFINITE	0xFFFFFFFF
/*! @~english  @brief Constant value expressing the output magnification rate of synchronization signal is 0.5.
	@~japanese @brief 同期信号出力倍率0.5倍を表す定数 */
#define PUC_SYNC_OUT_MAGNIFICATION_0_5	0
/*! @~english  @brief Constant value expressing the thread count for multi thread decoding
	@~japanese @brief マルチスレッドでデコードする際のスレッド最大数を表す定数 */
#define PUC_MAX_DECODE_THREAD_COUNT	32


/*! @~english  @brief Enumeration for ON/OFF setting
	@~japanese @brief ON／OFFを表す列挙体 */
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
	@~japanese @brief 信号の極性を表す列挙体 */
typedef enum
{
	/*! @~english  @brief Positive polarity signal
		@~japanese @brief 正極性の信号 */
	PUC_SIGNAL_POSI = 0,
	/*! @~english  @brief Negative polarity signal
		@~japanese @brief 負極性の信号 */
	PUC_SIGNAL_NEGA = 1,
} PUC_SIGNAL;

/*! @~english  @brief Enumeration for synchronization
	@~japanese @brief 同期を表す列挙体 */
typedef enum
{
	/*! @~english  @brief Internal operation
		@~japanese @brief 内部動作 */
	PUC_SYNC_INTERNAL = 0,
	/*! @~english  @brief Synchronize to external signal
		@~japanese @brief 外部からの信号に同期する */
	PUC_SYNC_EXTERNAL = 1,
} PUC_SYNC_MODE;

/*! @~english  @brief Enumeration for device color/monochrome setting
	@~japanese @brief デバイスのカラー／モノクロを表す列挙体 */
typedef enum
{
	/*! @~english  @brief Monochrome
		@~japanese @brief モノクロ */
	PUC_COLOR_MONO = 0,
	/*! @~english  @brief Color
		@~japanese @brief カラー */
	PUC_COLOR_COLOR = 1,
} PUC_COLOR_TYPE;

/*! @~english  @brief Enumeration for transfer data mode setting
	@~japanese @brief 転送データモードを表す列挙体 */
typedef enum
{
	/*! @~english  @brief Transfer compressed data
		@~japanese @brief 圧縮データ転送 */
	PUC_DATA_COMPRESSED = 0,
	/*! @~english  @brief Transfer decompressed data(gray)
		@~japanese @brief 展開済みのデータ転送(グレー) */
	PUC_DATA_DECOMPRESSED_GRAY = 1,
} PUC_DATA_MODE;


/*! @~english  @brief Device handle
	@~japanese @brief デバイスを表すハンドル */
typedef void* PUC_HANDLE;
/*! @~english  @brief Pointer for the device handle
	@~japanese @brief デバイスを表すハンドルのポインタ */
typedef PUC_HANDLE* PPUC_HANDLE;

/*! @~english  @brief Error code
	@~japanese @brief エラーコード */
typedef enum
{
	/*! @~english  @brief Succeeded
		@~japanese @brief 成功 */
	PUC_SUCCEEDED = 0,
	/*! @~english  @brief Initialization has not been performed. Please execute the PUC_Initialize function.
		@~japanese @brief 初期化されていません。PUC_Initialize関数を実行してください。 */
	PUC_ERROR_UNINITIALIZE = 1,
	/*! @~english  @brief Initialization is already complete.
		@~japanese @brief 既に初期化されています。 */
	PUC_ERROR_INITIALIZED = 2,
	/*! @~english  @brief The specified device number does not exist.
		@~japanese @brief 指定されたデバイス番号は存在しません。 */
	PUC_ERROR_NOT_EXIST_DEVICE_NO = 3,
	/*! @~english  @brief The specified device handle is NULL.
		@~japanese @brief 指定されたデバイスハンドルがNULLです。 */
	PUC_ERROR_ILLEGAL_DEVICE_HANDLE = 4,
	/*! @~english  @brief The specified argument is NULL.
		@~japanese @brief 指定された引数がNULLです。 */
	PUC_ERROR_ILLEGAL_ARG = 5,
	/*! @~english  @brief The specified resolution cannot be set.
		@~japanese @brief 指定された解像度は設定できません。 */
	PUC_ERROR_ILLEGAL_RESOLUTION = 6,
	/*! @~english  @brief The specified framerate cannot be set.
		@~japanese @brief 指定された撮影速度は設定できません。 */
	PUC_ERROR_ILLEGAL_FRAME_RATE = 7,
	/*! @~english  @brief The specified exposure time or non-exposure time (clock units) cannot be set.
		@~japanese @brief 指定された露光期間または非露光期間(クロック単位)は設定できません。 */
	PUC_ERROR_ILLEGAL_EXPOSE_CLOCK = 8,
	/*! @~english  @brief Failed to open the device.
		@~japanese @brief デバイスのオープンに失敗しました。 */
	PUC_ERROR_DEVICE_OPEN = 9,
	/*! @~english  @brief The device is not open.
		@~japanese @brief デバイスがオープンされていません。 */
	PUC_ERROR_DEVICE_NOTOPEN = 10,
	/*! @~english  @brief Failed to read data from the device.
		@~japanese @brief デバイスからのデータ読み取りに失敗しました。 */
	PUC_ERROR_DEVICE_READ = 11,
	/*! @~english  @brief Failed to write data to the device.
		@~japanese @brief デバイスへのデータ書き込みに失敗しました。 */
	PUC_ERROR_DEVICE_WRITE = 12,
	/*! @~english  @brief There are modules in the SDK that could not load.
		@~japanese @brief SDK内の一部モジュールがロードできませんでした。 */
	PUC_ERROR_MODULE_LOAD = 13,
	/*! @~english  @brief The exclusive process of the function has timed out.
		@~japanese @brief 関数の排他処理がタイムアウトしました。 */
	PUC_ERROR_LOCK_TIMEOUT = 14,
	/*! @~english  @brief Failed to send a GET command to the device.
		@~japanese @brief デバイスへの取得コマンド送信に失敗しました。 */
	PUC_ERROR_GET_CMD = 15,
	/*! @~english  @brief Failed to send a SET command to the device.
		@~japanese @brief デバイスへの設定コマンド送信に失敗しました。 */
	PUC_ERROR_SET_CMD = 16,
	/*! @~english  @brief The data of specified size could not be read from the device.
		@~japanese @brief デバイスから意図したサイズのデータを読み込めませんでした。 */
	PUC_ERROR_NOTEQUAL_READ_SIZE = 17,
	/*! @~english  @brief The data of specified size could not be written to the device.
		@~japanese @brief デバイスに意図したサイズのデータを書き込めませんでした。 */
	PUC_ERROR_NOTEQUAL_WRITE_SIZE = 18,
	/*! @~english  @brief The header information in the data received from the device is invalid.
		@~japanese @brief デバイスから受信したデータのヘッダー情報が不正です。 */
	PUC_ERROR_XFER_DATA_INVALID_HEADER = 19,
	/*! @~english  @brief Unable to start data transfer.
		@~japanese @brief データ転送が開始できませんでした。 */
	PUC_ERROR_XFER_DATA_BEGIN = 20,
	/*! @~english  @brief An unexpected error occurred during waiting for a data transfer from the device.
		@~japanese @brief デバイスからのデータ転送待ちで意図せぬ問題が発生しました。 */
	PUC_ERROR_XFER_DATA_WAIT = 21,
	/*! @~english  @brief The data transfer ended abnormally.
		@~japanese @brief データ転送終了が正常に行われませんでした。 */
	PUC_ERROR_XFER_DATA_FINISH = 22,
	/*! @~english  @brief Unable to process as a data transfer is in progress.
		@~japanese @brief 転送中のため処理できませんでした。 */
	PUC_ERROR_XFERRING = 23,
	/*! @~english  @brief The specified ring buffer count is invalid.
		@~japanese @brief 指定されたリングバッファ数が不正です。 */
	PUC_ERROR_RING_BUF_COUNT = 24,
	/*! @~english  @brief Unable to process as a synchronize to external signal is in progress.
		@~japanese @brief 外部同期中のため処理できませんでした。 */
	PUC_ERROR_SYNC_EXTERNAL = 25,
	/*! @~english  @brief This function is not supprted.
		@~japanese @brief この関数はサポートされていません。 */
	PUC_ERROR_NOTSUPPORT = 26,
} PUCRESULT;

/*! @~english  @brief The macro to be positive when an error code is normal.
	@~japanese @brief エラーコードが正常時に正となるマクロ */
#define PUC_CHK_SUCCEEDED(res) (res == PUC_SUCCEEDED)
/*! @~english  @brief The macro to be positive when an error code is not normal.
	@~japanese @brief エラーコードが正常以外の時に正となるマクロ */
#define PUC_CHK_FAILED(res) (res != PUC_SUCCEEDED)


/*!
	@struct PUC_DETECT_INFO
	@~english  @brief Structure for storing device search results
	@~japanese @brief デバイス検索結果を格納する構造体
*/
typedef struct
{
	/*! @~english  @brief Number of detected devices.
		@~japanese @brief 見つかったデバイス個数 */
	UINT32 nDeviceCount;
	/*! @~english  @brief List of device IDs found
		@~japanese @brief 見つかったデバイス番号一覧 */
	UINT32 nDeviceNoList[PUC_MAX_DEVICE];
} PUC_DETECT_INFO, *PPUC_DETECT_INFO;

/*!
	@struct PUC_RESO_LIMIT_INFO
	@~english  @brief Structure for storing resolution limit values
	@~japanese @brief 解像度の限界値を格納する構造体
*/
typedef struct
{
	/*! @~english  @brief Maximum horizontal resolution
		@~japanese @brief 最大解像度幅 */
	UINT32 nMaxWidth;
	/*! @~english  @brief Maximum vertical resolution
		@~japanese @brief 最大解像度高さ  */
	UINT32 nMaxHeight;
	/*! @~english  @brief Minimum horizontal resolution
		@~japanese @brief 最小解像度幅 */
	UINT32 nMinWidth;
	/*! @~english  @brief Minimum vertical resolution
		@~japanese @brief 最小解像度高さ */
	UINT32 nMinHeight;
	/*! @~english  @brief Minimum unit for altering the horizontal resolution
		@~japanese @brief 解像度幅の変更可能な最小単位 */
	UINT32 nUnitWidth;
	/*! @~english  @brief Minimum unit for altering the vertical resolution
		@~japanese @brief 解像度高さの変更可能な最小単位 */
	UINT32 nUnitHeight;
} PUC_RESO_LIMIT_INFO, * PPUC_RESO_LIMIT_INFO;

/*!
	@struct PUC_FRAMERATE_LIMIT_INFO
	@~english  @brief Structure for storing framerate limit values
	@~japanese @brief 撮影速度の限界値を格納する構造体
*/
typedef struct
{
	/*! @~english  @brief Minimum Framerate
	@~japanese @brief 最小撮影速度 */
	UINT32 nMinFrameRate;

	/*! @~english  @brief Maximum Framerate
	@~japanese @brief 最大撮影速度 */
	UINT32 nMaxFrameRate;
}PUC_FRAMERATE_LIMIT_INFO, *PPUC_FRAMERATE_LIMIT_INFO;

/*!
	@struct PUC_XFER_DATA_INFO
	@~english  @brief Structure for storing the information of transfer data.
	@~japanese @brief 転送データ情報を格納する構造体
*/
typedef struct
{
	/*! @~english  @brief Location for unpacked transfer data. It is necessary to allocate the required amount in advance. The mode of transfer data depends on the transfer data mode setting (COMPRESSED/DECOMPRESSED).
		@~japanese @brief 転送データの展開先。あらかじめ必要量確保しておく必要あり。転送されるデータは転送データモード(COMPRESSED/DECOMPRESSED)に依存する */
	PUINT8 pData;
	/*! @~english  @brief The size of transfer data. Stores the size of transfer data.
		@~japanese @brief 転送データのサイズ。転送されたデータのサイズが格納される */
	UINT32 nDataSize;
	/*! @~english  @brief The sequence number of transfer data.
		@~japanese @brief 転送データのシーケンス番号 */
	USHORT nSequenceNo;
} PUC_XFER_DATA_INFO, *PPUC_XFER_DATA_INFO;



/*! @~english  @brief The callback function type called during continuous transfer
	@~japanese @brief 連続転送中に呼ばれるコールバック関数の型 */
typedef void(*RECIEVE_CALLBACK)(PPUC_XFER_DATA_INFO, void*);




/*!
	@~english
		@brief This initializes the library.
		@details Only use this function once the first time PUCLIB is used. @n The termination operation is automatically performed when a process is terminated.
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
	@~japanese
		@brief 本ライブラリを初期化します。
		@details 初回に1度だけ実行してください。@n終了処理は本プロセス終了時に自動的に行われます。
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスを検索します。
		@details 既にデバイス番号が分かっている場合は、検索せずにオープンすることも可能です。
		@param[out] pDetectInfo 見つかったデバイスの情報が格納されます。
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスをオープンします。
		@details 既にオープン中のデバイス番号を指定すると一度クローズされますのでご注意ください。
		@param[in] nDeviceNo 検索したデバイス番号を指定します。
		@param[out] pDeviceHandle オープンしたデバイスを操作するためのハンドルが格納されます。
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスをクローズします。
		@details オープンしていないデバイスが指定されるとエラーを返します。
		@param[in] hDevice クローズするデバイスハンドル
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスのカラー／モノクロ情報を取得します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[out] pType カラー／モノクロ情報の格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスの名前を取得します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[out] pName デバイス名の格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスのタイプを取得します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[out] pType デバイスタイプの格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスのバージョンを取得します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[out] pVersion バージョン番号の格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスのシリアル番号を取得します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[out] pSerialNo シリアル番号の格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスの解像度を取得します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[out] pWidth 横解像度の格納先
		@param[out] pHeight 縦解像度の格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスの現在の撮影速度で設定可能な最大解像度を取得します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[out] pCurMaxWidth 現在の撮影速度で設定可能な最大横解像度の格納先
		@param[out] pCurMaxHeight 現在の撮影速度で設定可能な最大縦解像度の格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスの限界解像度、変更可能な最小単位を取得します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[out] pLimitInfo 限界解像度、変更可能な最小単位の格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスの解像度を設定します。
		@details デバイスのオープン時に設定はリセットされます。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[in] nWidth 横解像度
		@param[in] nHeight 縦解像度
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスに格納されている量子化テーブルデータを１つ取得します。
		@details 量子化テーブルの個数はPUC_Q_COUNTで定義されています。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[in] nPoint 量子化テーブルの位置
		@param[out] pVal 量子化テーブルデータの格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスに格納されている量子化テーブルデータを１つ書き換えます。
		@details 量子化テーブルの個数はPUC_Q_COUNTで定義されています。@nデバイスを再起動すると設定はリセットされます。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[in] nPoint 量子化テーブルの位置
		@param[in] nVal 設定する量子化テーブルデータ
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスのファンの状態を取得します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[out] nState ファン状態（ON／OFF）の格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスのファンの状態を設定します。
		@details デバイスを再起動すると設定はリセットされます。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[in] nState ファン状態（ON／OFF）
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
		@see PUC_GetFanState
*/
PUCRESULT WINAPI PUC_SetFanState(PUC_HANDLE hDevice, PUC_MODE nState);

/*!
	@~english
		@brief This retrieves the synchronous signal input mode for the device.
		@param[in] hDevice The device handle to be controlled
		@param[out] pMode The storage destination for the synchronous signal input mode (Internal/External)
		@param[out] pSignal The storage destination for the polarity (positive polarity/negative polarity), 
					@n It can be obtained only when external synchronization is set.
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_SetSyncInMode
	@~japanese
		@brief デバイスの同期信号入力モードを取得します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[out] pMode 同期信号入力モード（Internal／External）の格納先
		@param[out] pSignal 極性（正極性／負極性）の格納先、外部同期設定時のみ取得できます。
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
		@see PUC_SetSyncInMode
*/
PUCRESULT WINAPI PUC_GetSyncInMode(PUC_HANDLE hDevice, PUC_SYNC_MODE* pMode, PUC_SIGNAL *pSignal);

/*!
	@~english
		@brief This sets the synchronous signal input mode for the device.
		@details Restarting the device will reset this setting. @n Changing the synchronization signal output mode resets the output magnification rate to x1.
				 @n When setting to external device synchronization, the exposure time is automatically adjusted considering the variation of external devices.
				 Set the exposure time and framerate before setting the external device synchronization.
		@param[in] hDevice The device handle to be controlled
		@param[in] nMode The synchronous signal input mode (Internal/External)
		@param[in] nSignal Polarity (positive/negative), Specifying the polarity is not supported for devices prior to version 1.01.
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_GetSyncInMode
	@~japanese
		@brief デバイスの同期信号入力モードを設定します。
		@details デバイスを再起動すると設定はリセットされます。@n同期信号入力モードを変えると出力倍率はx1倍に戻ります。
				 @n外部機器同期設定時、外部機器のばらつきを考慮した露光時間へ自動で調整されます。あらかじめ撮影したい露光時間と撮影速度に変更してから、外部機器同期を設定してください。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[in] nMode 同期信号入力モード（Internal／External）
		@param[in] nSignal 極性（正極性／負極性）、極性の指定はバージョン1.01以前のデバイスでは対応していません。
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
		@see PUC_GetSyncInMode
*/
PUCRESULT WINAPI PUC_SetSyncInMode(PUC_HANDLE hDevice, PUC_SYNC_MODE nMode, PUC_SIGNAL nSignal);

/*!
	@~english
		@brief This retrieves the synchronization signal output polarity for the device.
		@param[in] hDevice The device handle to be controlled
		@param[out] pSignal The storage destination for the polarity (positive polarity/negative polarity)
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_SetSyncOutSignal
	@~japanese
		@brief デバイスの同期信号出力の極性を取得します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[out] pSignal 極性（正極性／負極性）の格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスの同期信号出力の極性を設定します。
		@details デバイスを再起動すると設定はリセットされます。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[in] nSignal 極性（正極性／負極性）
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
		@see PUC_GetSyncOutSignal
*/
PUCRESULT WINAPI PUC_SetSyncOutSignal(PUC_HANDLE hDevice, PUC_SIGNAL nSignal);

/*!
	@~english
		@brief This retrieves the delay value of device's synchronization signal output in nsec.
		@n The value less than 100nsec is rounded up, so an error will occur.
		@param[in] hDevice The device handle to be controlled
		@param[out] pDelay The storage destination for the delay amount (nsec units)
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_SetSyncOutDelay
	@~japanese
		@brief デバイスの同期信号出力の遅延量をnsec単位で取得します。
		@n 100nsec未満は切り上げるため誤差が発生します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[out] pDelay 遅延量(nsec単位)の格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
		@see PUC_SetSyncOutDelay
*/
PUCRESULT WINAPI PUC_GetSyncOutDelay(PUC_HANDLE hDevice, UINT32* pDelay);

/*!
	@~english
		@brief This sets the delay value of device's synchronization signal output in nsec.
		@details Restarting the device will reset this setting.
		@n The value less than 100nsec is rounded up, so an error will occur.
		@param[in] hDevice The device handle to be controlled
		@param[in] nDelay The delay (nsec units)
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_GetSyncOutDelay
	@~japanese
		@brief デバイスの同期信号出力の遅延量を設定します。
		@details デバイスを再起動すると設定はリセットされます。
		@n 100nsec未満は切り上げるため誤差が発生します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[in] nDelay 遅延量(nsec単位)
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
		@see PUC_GetSyncOutDelay
*/
PUCRESULT WINAPI PUC_SetSyncOutDelay(PUC_HANDLE hDevice, UINT32 nDelay);

/*!
	@~english
		@brief This retrieves the output width of synchronization signal for the device.
		@n If it is less than 100nsec, it will be rounded up and an error will occur.
		@param[in] hDevice The device handle to be controlled
		@param[out] pWidth The storage destination for the output width (nsec units)
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_SetSyncOutWidth
	@~japanese
		@brief デバイスの同期信号出力の出力幅を取得します。
		@n 100nsec未満は切り上げるため誤差が発生します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[out] pWidth 出力幅(nsec単位)の格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
		@see PUC_SetSyncOutWidth
*/
PUCRESULT WINAPI PUC_GetSyncOutWidth(PUC_HANDLE hDevice, UINT32* pWidth);

/*!
	@~english
		@brief This sets the output width of synchronization signal for the device.
		@details Restarting the device will reset this setting. 
		@n Changing the output width resets the output magnification rate to x1.
		@n If it is less than 100nsec, it will be rounded up and an error will occur.
		@param[in] hDevice The device handle to be controlled
		@param[in] nWidth The output width of the synchronous signal (nsec units).
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_GetSyncOutWidth
	@~japanese
		@brief デバイスの同期信号出力の出力幅を設定します。
		@details デバイスを再起動すると設定はリセットされます。
		@n 出力幅を変えると出力倍率はx1倍に戻ります。
		@n 100nsec未満は切り上げるため誤差が発生します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[in] nWidth 同期信号の出力幅(nsec単位)。
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief 同期信号の出力倍率を取得します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[out] pMagnification 出力倍率の格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief 同期信号の出力倍率を設定します。
		@details デバイスのオープン時に設定はリセットされます。@n撮影速度や露光・非露光期間を変更した場合もx1倍にリセットされます。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[in] nMagnification 出力倍率（例：x2の場合は2、x4の場合は4）0.5倍の場合はPUC_SYNC_OUT_MAGNIFICATION_0_5を指定
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスのLED状態を取得します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[out] pMode LEDの状態（ON／OFF）の格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスのLED状態を設定します。
		@details デバイスを再起動すると設定はリセットされます。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[in] nMode LEDの状態（ON／OFF）
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスのセンサー温度を取得します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[out] pTemp センサーの温度の格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスの転送データモードを取得します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[out] pDataMode データモードの格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスの転送データモードを設定します。
		@details デバイスのオープン時に設定はリセットされます。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[in] nDataMode データモード
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。PUC_DATA_DECOMPRESSED_GRAYを指定した場合デコードはシングルスレッドで行われます。
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
		@brief デバイスから転送されるデータサイズを取得します。
		@details 現在の解像度により結果が異なります。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[in] nDataMode データモード。ここで指定されたモードに対するデータサイズを返却します。
		@param[out] pDataSize データサイズの格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスから転送されるデータの最大サイズを取得します。
		@details 現在の解像度により結果が異なります。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[in] nDataMode データモード。ここで指定されたモードに対するデータサイズを返却します。
		@param[out] pDataSize 最大データサイズの格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスから最新のライブ画像を1枚取得します。
		@details 連続転送中は画像が一部乱れる場合があります。@n
			画像データのサイズはPUC_GetXferDataSizeで取得してください。@n
			取得する画像の種類はPUC_SetXferDataModeで設定できます。@n
			圧縮データはPUC_DecodeDataを使用することで輝度データに展開できます。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[out] pXferData 転送データの格納先。必要なメモリサイズはPUC_GetXferDataSizeで取得してください。@n
			PUC_DATA_DECOMPRESSED_GRAYの場合、横幅は4の倍数に切り上げたサイズ分確保されている必要があります。
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief 連続転送を始めます。
		@details コールバック関数の処理時間が長い場合、PUC_SetRingBufferCountで設定したリングバッファ内に順次画像データが格納されます。@n
			リングバッファが一巡するとコールバック関数の処理完了待ちとなり、この間の受信データはバッファに格納されませんのでご注意ください。（フレーム落ち）
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[in] callback SDK内部でデバイスから1枚画像を受信するたび、このコールバック関数が呼ばれます。
		@param[in] arg コールバック関数に渡す引数
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief 連続転送を終了します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief 連続転送中かどうかを確認します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[out] pIsXferring 連続転送中の場合にTRUE、それ以外はFALSEを格納します。
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief 圧縮画像データからシーケンス番号を抽出します。
		@param[in] pData 圧縮画像データ
		@param[in] nWidth 画像の横幅
		@param[in] nHeight 画像の高さ
		@param[out] pSeqNo 抽出したシーケンス番号の格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。本関数は並列実行が可能です。
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
		@brief 圧縮画像データを輝度値データに展開します。
		@param[out] pDst 展開先バッファ。横幅は4の倍数に切り上げたサイズ分確保されている必要があります。（例：横幅が1246pxの場合、バッファは1248バイト確保されている必要あり）
		@param[in] nX 展開開始する左上座標X。0もしくは8の倍数である必要があります。
		@param[in] nY 展開開始する左上座標Y。0もしくは8の倍数である必要があります。
		@param[in] nWidth 展開する横幅
		@param[in] nHeight 展開する高さ
		@param[in] nLineBytes 展開先バッファの横幅のバイト数
		@param[in] pSrc 圧縮画像データ
		@param[in] pQVals 量子化テーブル
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。本関数は並列実行が可能です。
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
		@brief 圧縮画像データを輝度値データに展開します。このデコード処理はマルチスレッドで行われます。
		@param[out] pDst 展開先バッファ。横幅は4の倍数に切り上げたサイズ分確保されている必要があります。（例：横幅が1246pxの場合、バッファは1248バイト確保されている必要あり）
		@param[in] nX 展開開始する左上座標X。0もしくは8の倍数である必要があります。
		@param[in] nY 展開開始する左上座標Y。0もしくは8の倍数である必要があります。
		@param[in] nWidth 展開する横幅
		@param[in] nHeight 展開する高さ
		@param[in] nLineBytes 展開先バッファの横幅のバイト数
		@param[in] pSrc 圧縮画像データ
		@param[in] pQVals 量子化テーブル
		@param[in] nThreadCount マルチスレッドで処理するスレッド数
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。本関数は並列実行が可能です。
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
		@brief 圧縮画像データをDCT係数に展開します。
		@param[out] pDst 展開先バッファ。横幅は4の倍数に切り上げたサイズ分確保されている必要があります。（例：横幅が1246pxの場合、バッファは1248バイト確保されている必要あり）
		@param[in] nX 展開開始する左上座標X。0もしくは8の倍数である必要があります。
		@param[in] nY 展開開始する左上座標Y。0もしくは8の倍数である必要があります。
		@param[in] nWidth 展開する横幅
		@param[in] nHeight 展開する高さ
		@param[in] nLineBytes 展開先バッファの横幅のバイト数
		@param[in] pSrc 圧縮画像データ
		@param[in] pQVals 量子化テーブル
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。本関数は並列実行が可能です。
		@see PUC_GetXferDataSize
		@see PUC_GetMaxXferDataSize
*/
PUCRESULT WINAPI PUC_DecodeDCTData(PINT16 pDst, UINT32 nX, UINT32 nY, UINT32 nWidth, UINT32 nHeight, UINT32 nLineBytes, const PUINT8 pSrc, const PUSHORT pQVals);

/*!
	@~english
		@brief Decodes the DC component of compressed image data.
		@param[out] pDst The buffer at the decoding destination. Must be allocated for the total number of blocks included in the decoding range.
		@param[in] nBlockX The block coordinates X for starting decoding
		@param[in] nBlockY The block coordinates Y for starting decoding
		@param[in] nBlockCountX Number of blocks in the X direction to be decoded
		@param[in] nBlockCountY Number of blocks in the Y direction to be decoded
		@param[in] pSrc The compressed image data
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe. This function can be executed in parallel.
		@see PUC_GetXferDataSize
		@see PUC_GetMaxXferDataSize
	@~japanese
		@brief 圧縮画像データのDC成分を展開します。
		@param[out] pDst 展開先バッファ。デコード範囲に含まれるブロックの総数だけ確保する必要があります。
		@param[in] nBlockX 展開開始するブロック座標X。
		@param[in] nBlockY 展開開始するブロック座標Y。
		@param[in] nBlockCountX 展開するX方向のブロック数
		@param[in] nBlockCountY 展開するY方向のブロック数
		@param[in] pSrc 圧縮画像データ
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。本関数は並列実行が可能です。
		@see PUC_GetXferDataSize
		@see PUC_GetMaxXferDataSize
*/
PUCRESULT WINAPI PUC_DecodeDCData(PUINT8 pDst, UINT32 nBlockX, UINT32 nBlockY, UINT32 nBlockCountX, UINT32 nBlockCountY, const PUINT8 pSrc);


/*!
	@~english
		@brief This retrieves the ring buffer count for continuous transfer.
		@param[in] hDevice The device handle to be controlled
		@param[out] pCount The storage destination for the buffer count
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_SetRingBufferCount
	@~japanese
		@brief 連続転送時のリングバッファ数を取得します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[out] pCount バッファ数の格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief 連続転送時のリングバッファ数を設定します。
		@details デバイスのオープン時に設定はリセットされます。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[in] nCount バッファ数
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスの転送時のタイムアウト時間(ms)を取得します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[out] pSingleXferTimeOut シングル転送のタイムアウト時間(ms)の格納先
		@param[out] pContinuousXferTimeOut 連続転送のタイムアウト時間(ms)の格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスの転送時のタイムアウト時間(ms)を設定します。
		@details デバイスのオープン時に設定はリセットされます。@n
			PUC_XFER_TIMEOUT_AUTOを指定すると、撮影速度に応じて自動でタイムアウトを調整します。@n
			PUC_XFER_TIMEOUT_INFINITEを指定すると、タイムアウトはなくなります。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[in] nSingleXferTimeOut シングル転送のタイムアウト時間(ms)
		@param[in] nContinuousXferTimeOut 連続転送のタイムアウト時間(ms)
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
		@see PUC_GetXferTimeOut
*/
PUCRESULT WINAPI PUC_SetXferTimeOut(PUC_HANDLE hDevice, UINT32 nSingleXferTimeOut, UINT32 nContinuousXferTimeOut);

/*!
	@~english
		@brief This retrieves the maximum framerate for the current resolution.
		@param[in] hDevice The device handle to be controlled
		@param[out] pFramerate The storage destination for the maximum framerate
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_GetFramerateShutter
	@~japanese
		@brief 現在の解像度に対する最大撮影速度を取得します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[out] pFramerate 最大撮影速度の格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
		@see PUC_GetFramerateShutter
*/
PUCRESULT WINAPI PUC_GetMaxFramerate(PUC_HANDLE hDevice, UINT32* pFramerate);

/*!
	@~english
		@brief This retrieves the framerate limit information.
		@param[in] hDevice The device handle to be controlled.
		@param[out] pLimitInfo Structure for storing framerate limit values.
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_GetFramerateShutter
	@~japanese
		@brief 限界撮影速度情報を取得します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[out] pLimitInfo 限界撮影速度の格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
		@see PUC_GetFramerateShutter
*/
PUCRESULT WINAPI PUC_GetFramerateLimit(PUC_HANDLE hDevice, PPUC_FRAMERATE_LIMIT_INFO pLimitInfo);

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
		@brief デバイスの撮影速度およびシャッター速度(1/fps)を取得します。
		@details PUC_SetExposeTime関数により露光・非露光期間を直接設定した場合、本関数で返される値は不正な値になりますのでご注意ください。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[out] pFramerate 撮影速度の格納先
		@param[out] pShutterSpeedFps シャッター速度(1/fps)の格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
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
		@brief デバイスの撮影速度およびシャッター速度(1/fps)を設定します。
		@details デバイスのオープン時に設定はリセットされます。@n本関数を実行すると、PUC_GetExposeTimeで返却される値も変更されます。@nフレームレートを変えると同期信号の出力倍率はx1倍に戻ります。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[in] nFramerate 撮影速度
		@param[in] nShutterSpeedFps シャッター速度(1/fps)
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
		@see PUC_GetExposeTime
		@see PUC_SetExposeTime
*/
PUCRESULT WINAPI PUC_SetFramerateShutter(PUC_HANDLE hDevice, UINT32 nFramerate, UINT32 nShutterSpeedFps);

/*!
	@~english
		@brief This retrieves the exposure/non-exposure time of the device.
		@details The return value of this function will change if the frame rate and shutter speed is changed with PUC_SetFramerateShutter function. 
		@n Changing the exposure/non-exposure time resets the output magnification rate of synchronization signal to x1.
		@n If it is less than 100nsec, it will be rounded up and an error will occur.
		@param[in] hDevice The device handle to be controlled
		@param[out] pExpOnTime The storage destination for the exposure period (nsec units)
		@param[out] pExpOffTime The storage destination for the non-exposure period (nsec units)
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_SetExposeTime
		@see PUC_SetFramerateShutter
	@~japanese
		@brief デバイスの露光・非露光期間を取得します。
		@details PUC_SetFramerateShutter関数で撮影速度およびシャッター速度が変更されると、本関数で返却される値も変わります。
		@n 露光・非露光期間を変えると同期信号の出力倍率はx1倍に戻ります。
		@n 100nsec未満は切り上げるため誤差が発生します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[out] pExpOnTime 露光期間（nsec単位）の格納先
		@param[out] pExpOffTime 非露光期間（nsec単位）の格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
		@see PUC_SetExposeTime
		@see PUC_SetFramerateShutter
*/
PUCRESULT WINAPI PUC_GetExposeTime(PUC_HANDLE hDevice, UINT32* pExpOnTime, UINT32* pExpOffTime);

/*!
	@~english
		@brief This retrieves the minimum exposure/non-exposure time of the device.
		@n If it is less than 100nsec, it will be rounded up and an error will occur.
		@param[in] hDevice The device handle to be controlled
		@param[out] pMinExpOnTime The storage destination for the minimum exposure period (nsec units)
		@param[out] pMinExpOffTime The storage destination for the minimum non-exposure period (nsec units)
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_SetExposeTime
	@~japanese
		@brief デバイスの最小露光・非露光期間を取得します。
		@n 100nsec未満は切り上げるため誤差が発生します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[out] pMinExpOnTime 最小露光期間（nsec単位）の格納先
		@param[out] pMinExpOffTime 最小非露光期間（nsec単位）の格納先
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
		@see PUC_SetExposeTime
*/
PUCRESULT WINAPI PUC_GetMinExposeTime(PUC_HANDLE hDevice, UINT32* pMinExpOnTime, UINT32* pMinExpOffTime);

/*!
	@~english
		@brief This sets the exposure/non-exposure time of the device.
		@details Opening the device will reset this setting. 
		@n Note that the return value of PUC_GetFramerateShutter function will be invalid if the exposure/non-exposure time is set directly with this function.
		@n If it is less than 100nsec, it will be rounded up and an error will occur.
		@param[in] hDevice The device handle to be controlled
		@param[in] nExpOnTime The exposure period (nsec units)
		@param[in] nExpOffTime The non-exposure period (nsec units)
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_GetExposeTime
		@see PUC_GetFramerateShutter
	@~japanese
		@brief デバイスの露光・非露光期間を設定します。
		@details デバイスのオープン時に設定はリセットされます。
		@n 本関数により露光・非露光期間を直接設定した場合、PUC_GetFramerateShutter関数で返される値は不正な値になります。
		@n 100nsec未満は切り上げるため誤差が発生します。
		@param[in] hDevice 操作対象のデバイスハンドル
		@param[in] nExpOnTime 露光期間（nsec単位）
		@param[in] nExpOffTime 非露光期間（nsec単位）
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
		@see PUC_GetExposeTime
		@see PUC_GetFramerateShutter
*/
PUCRESULT WINAPI PUC_SetExposeTime(PUC_HANDLE hDevice, UINT32 nExpOnTime, UINT32 nExpOffTime);

/*!
	@~english
		@brief This resets the device.
		@details There is possibility for PUC_OpenDevice to return error even though device is detected. Please set this to resets device.
		@param[in] nDeviceNo Specify the retrieved device ID here.
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
		@see PUC_ResetDevice
	@~japanese
		@brief デバイスをリセットします。
		@details デバイスを認識しPUC_OpenDeviceに失敗する場合、この関数でデバイスをリセットして下さい
		@param[in] nDeviceNo 検索したデバイス番号を指定します。
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
		@see PUC_ResetDevice
*/
PUCRESULT WINAPI PUC_ResetDevice(UINT32 nDeviceNo);


/*!
	@~english
		@brief This resets the sequence number.
		@param[in] hDevice The device handle to be controlled
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note This function is thread-safe.
	@~japanese
		@brief シーケンス番号をリセットします
		@param[in] hDevice 操作対象のデバイスハンドル
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note 本関数はスレッドセーフです。
*/
PUCRESULT WINAPI PUC_ResetSequenceNo(PUC_HANDLE hDevice);

#ifdef __cplusplus
}
#endif

#endif /* __PUCLIB_H */