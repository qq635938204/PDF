// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 PDFHANDLER_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// PDFHANDLER_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef PDFHANDLER_EXPORTS
#define PDFHANDLER_API __declspec(dllexport)
#else
#define PDFHANDLER_API __declspec(dllimport)
#endif

enum tag_MarkType
{
	MARK_TYPE_TXT = 0,
	MARK_TYPE_BIN,
	MARK_TYPE_FONT_ENCODE
};

enum tag_OmitFlag
{
	OMIT_FLAG_NONE = 0x0000,
	OMIT_FLAG_STREAM = 0x0001,
	OMIT_FLAG_CONTENT_ZIP = 0x0002,
	OMIT_FLAG_ALL = OMIT_FLAG_STREAM | OMIT_FLAG_CONTENT_ZIP,
	MAX_OMIT_FLAG_CNT
};


#define MAX_MARK_SIZE			1024

typedef struct tag_WaterMarkW
{
	long	lType;
	long	lFlag;
	long	lHasPage;
	long	lUnicode;
	long	lSize;
	union{
		BYTE	byMark[MAX_MARK_SIZE];
		WCHAR	cszMark[MAX_MARK_SIZE / 2];
	};
} ST_WATERMARKW, *PST_WATERMARKW;

typedef struct tag_WaterMarkA
{
	long	lType;
	long	lFlag;
	long	lHasPage;
	long	lUnicode;
	long	lSize;
	union{
		BYTE	byMark[MAX_MARK_SIZE];
		char	cszMark[MAX_MARK_SIZE];
	};
} ST_WATERMARKA, *PST_WATERMARKA;

#ifdef _UNICODE
typedef ST_WATERMARKW		ST_WATERMARK, *PST_WATERMARK;
#else
typedef ST_WATERMARKA		ST_WATERMARK, *PST_WATERMARK;
#endif

extern "C"
{
	PDFHANDLER_API long GetPageCount(
		LPCTSTR				lpSrcFile);

	PDFHANDLER_API BOOL ReplacePDFText(
		LPCTSTR				lpSrcFile, 
		LPCTSTR				lpOutFile, 
		LPCTSTR				lpTempFile,
		PST_WATERMARK		parWaterMarks,
		long				lTxtMarkCnt, 
		long				lBinMarkCnt,
		TCHAR				szLog[]);
};