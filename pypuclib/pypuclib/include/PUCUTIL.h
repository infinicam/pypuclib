#ifndef __PUCUTIL_H_
#define __PUCUTIL_H_

/*
 *	PUCUTIL.h
 *	PHOTRON INFINICAM Control SDK
 *
 *	Copyright (C) 2023 PHOTRON LIMITED
 */

#include "PUCCONST.h"


#ifdef PUCUTIL_EXPORTS
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

#ifndef DLLAPI
#define DLLAPI extern "C"
#endif




#ifdef __cplusplus
extern "C" {
#endif

/*!
	@struct PUC_GPU_SETUP_PARAM
	@~english  @brief A structure that stores parameters used in GPU decoding
	@~japanese @brief GPUデコードで使用するパラメータを格納する構造体
*/
typedef struct
{
	/*! @~english  @brief The image width on GPU process.
		@~japanese @brief GPU処理で扱う画像の解像度横幅 */
	UINT32 width;

	/*! @~english  @brief The image height on GPU process.
		@~japanese @brief GPU処理で扱う画像の解像度高さ */
	UINT32 height;
} PUC_GPU_SETUP_PARAM, * PPUC_GPU_SETUP_PARAM;


namespace pucutil
{

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
DLL_EXPORT PUCRESULT WINAPI ExtractSequenceNo(const PUCHAR pData, UINT32 nWidth, UINT32 nHeight, PUSHORT pSeqNo);

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
DLL_EXPORT PUCRESULT WINAPI DecodeData(PUINT8 pDst, UINT32 nX, UINT32 nY, UINT32 nWidth, UINT32 nHeight, UINT32 nLineBytes, const PUINT8 pSrc, const PUSHORT pQVals);

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
DLL_EXPORT PUCRESULT WINAPI DecodeDataMultiThread(PUINT8 pDst, UINT32 nX, UINT32 nY, UINT32 nWidth, UINT32 nHeight, UINT32 nLineBytes, const PUINT8 pSrc, const PUSHORT pQVals, UINT32 nThreadCount);

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
DLL_EXPORT PUCRESULT WINAPI DecodeDCTData(PINT16 pDst, UINT32 nX, UINT32 nY, UINT32 nWidth, UINT32 nHeight, UINT32 nLineBytes, const PUINT8 pSrc, const PUSHORT pQVals);

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
DLL_EXPORT PUCRESULT WINAPI DecodeDCData(PUINT8 pDst, UINT32 nBlockX, UINT32 nBlockY, UINT32 nBlockCountX, UINT32 nBlockCountY, const PUINT8 pSrc);

/*!
	@~english
		@brief This retrieves whether the PC is capable of GPU processing.
		@return Returns PUC_SUCCEEDED if GPU processing is possible, otherwise returns PUC_ERROR_NOTSUPPORT.
	@~japanese
		@brief PCがGPU処理可能かを取得します。
		@return GPU処理可能であればPUC_SUCEEDED, 不可能であればPUC_ERROR_NOTSUPPORTが返ります。
*/
DLL_EXPORT PUCRESULT WINAPI GetAvailableGPUProcess();

/*!
	@~english
		@brief Allocates memory for GPU processing.
		@param[in] param This is a configuration parameter.
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
	@~japanese
		@brief GPU処理で使用するメモリを確保します。
		@param[in] param 設定パラメータです。
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
*/
DLL_EXPORT PUCRESULT WINAPI SetupGPUDecode(PUC_GPU_SETUP_PARAM param);

/*!
	@~english
		@brief Releases memory used by GPU processing.
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
		@note It is safe to run after releasing the buffer used for PUC_DecodeGPU.
	@~japanese
		@brief GPU処理で使用したメモリを解放します。
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
		@note PUC_DecodeGPUに使用したバッファを解放後に実行しても問題ありません。
*/
DLL_EXPORT PUCRESULT WINAPI TeardownGPUDecode();

/*!
	@~english
		@brief This unpacks the compressed image data to luminance data.(GPU processing)
		@param[in] download If false is specified, the decoded data is stored in device (GPU) memory; if true is specified, it is stored in host (CPU) memory.
		@param[in] pSrc The original encoded frame data to be decoded.
		@param[out] pDst The decoded processing result frame data, which is output to device memory or host memory depending on the setting of the download argument.
		@param[in] lineBytes The number of bytes of the buffer width at the unpacking destination
		@n If the download argument is true, the data decoded by the GPU is copied to the address specified by this argument.
		@n Therefore, it is necessary to allocate a buffer in host memory in advance.
		@n The size of the width must be allocated rounded up to a multiple of four. (e.g., If the width is 1246 px, a buffer is required 1248 bytes at least)
		@n If the download argument is false, the address of the device memory of the data decoded by the GPU is acquired. Allocation of host memory is not required.
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
	@~japanese
		@brief 圧縮画像データを輝度値データに展開します。(GPU使用)
		@param[in] download falseを指定した場合デコードされたデータはデバイス(GPU)メモリに保存され、trueの場合はホスト(CPU)メモリに保存されます。
		@param[in] pSrc デコード対象のエンコードされた元のフレームデータです。
		@param[out] pDst デコードされた処理結果のフレームデータです。download引数の設定によってデバイスメモリまたはホストメモリに出力されます。
		@param[in] lineBytes 展開先バッファの横幅のバイト数
		@n download引数がtrueの場合、GPUでデコードされたデータをこの引数で指定されたアドレスにコピーします。そのため事前にホストメモリのバッファの確保が必要です。
		@n 横幅は4の倍数に切り上げたサイズ分確保されている必要があります。（例：横幅が1246pxの場合、バッファは1248バイト確保されている必要あり）
		@n download引数がfalseの場合、GPUでデコードされたデータのデバイスメモリのアドレスを取得します。ホストメモリの確保は不要です。
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
*/
DLL_EXPORT PUCRESULT WINAPI DecodeGPU(bool download, unsigned char* pSrc, unsigned char** pDst, UINT32 lineBytes);

/*!
	@~english
		@brief This retrieves the error code from the last GPU processing.
		@param[out] The error code from GPU.
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
	@~japanese
		@brief 最後に発生したGPU処理でのエラーコードを取得します。
		@param[out] errorCode エラーコードです。
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
*/
DLL_EXPORT PUCRESULT WINAPI GetGPULastError(int& errorCode);

/*!
	@~english
		@brief This retrieves whether GPU decode memory is allocated.
		@param[out] status true : allocated, false : not allocated.
		@return If successful, PUC_SUCCEEDED will be returned. If failed, other responses will be returned.
	@~japanese
		@brief GPUデコードのメモリが確保がされているかを取得します。
		@param[out] status true：確保済み、false：確保されていない
		@return 成功時はPUC_SUCCEEDED、失敗時はそれ以外が返ります。
*/
DLL_EXPORT PUCRESULT WINAPI IsSetupGPUDecode(bool& status);

} // namespace pucutil

#ifdef __cplusplus
} // extern C
#endif

#endif //__PUCUTIL_H
