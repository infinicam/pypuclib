#ifndef __PUCCONST_H
#define __PUCCONST_H

/*
 *	PUCCONST.h
 *	PHOTRON INFINICAM Control SDK
 *
 *	Copyright (C) 2023 PHOTRON LIMITED
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
	/*! @~english  @brief GPU decode process failed.
		@~japanese @brief GPUデコード処理に失敗しました。 */
	PUC_ERROR_GPU_DECODE_PROCESS = 27,

	/*! @~english  @brief Failed to allocate buffer.
	@~japanese @brief バッファの確保に失敗しました。 */
	PUC_ERROR_ALLOCATE_BUFFUER = 28,

	/*! @~english  @brief Failed to release the buffer.
	@~japanese @brief バッファの解放に失敗しました。 */
	PUC_ERROR_FREE_BUFFER = 29,

	/*! @~english  @brief Failed to synchronize GPU processing.
	@~japanese @brief GPU処理の同期に失敗しました。 */
	PUC_ERROR_GPU_SYNCHRONIZE = 30,

	/*! @~english  @brief Failed to copy GPU memory.
	@~japanese @brief GPUメモリのコピーに失敗しました。 */
	PUC_ERROR_GPU_MEMORY_COPY = 31,

	/*! @~english  @brief The setup required for GPU processing is not done, please run PUC_SetupGPUDecode.
	@~japanese @brief GPU処理に必要なセットアップが行われていません。PUC_SetupGPUDecodeを実行してください。*/
	PUC_ERROR_GPU_UNINITIALIZE=32,


} PUCRESULT;




/*! @~english  @brief The macro to be positive when an error code is normal.
	@~japanese @brief エラーコードが正常時に正となるマクロ */
#define PUC_CHK_SUCCEEDED(res) (res == PUC_SUCCEEDED)
/*! @~english  @brief The macro to be positive when an error code is not normal.
	@~japanese @brief エラーコードが正常以外の時に正となるマクロ */
#define PUC_CHK_FAILED(res) (res != PUC_SUCCEEDED)

#ifdef __cplusplus
}
#endif

#endif /* __PUCCONST_H */