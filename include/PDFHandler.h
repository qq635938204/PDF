// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� PDFHANDLER_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// PDFHANDLER_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
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