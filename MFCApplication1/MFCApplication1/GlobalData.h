# define MAXSTATION 10

typedef struct StationParam
{
	// ! 工位号
	BYTE stationNo;
	// ！工位名
	BYTE stationName[100];
	// ！转速器控制端口
	BYTE rotatePort;
	// ! 转速名称
	BYTE rotateName[100];

	// ! 温度控制方式 GPIB/RS232 0/1
	BYTE tempControlMode;
	// ! RS232端口
	BYTE port;
	// ! GPIB地址
	BYTE addr;
	// ! 通道号1
	BYTE channel1No;
	// ! 通道号1名称
	BYTE channel1Name[100];
	// ! 通道号1传感器类型
	BYTE channel1TempType;
	// ! 通道号1热电偶或热敏或电阻的子类型
	BYTE channel1TempSubmode;
	// ! 通道号2
	BYTE channel2No;
	// ! 通道号2名称
	BYTE channel2Name[100];
	// ! 通道号2传感器类型
	BYTE channel2TempType;
	// ! 通道号2热电偶或热敏或电阻的子类型
	BYTE channel2TempSubmode;
	// ! 通道号3
	BYTE channel3No;
	// ! 通道号3名称
	BYTE channel3Name[100];
	// ! 通道号1传感器类型
	BYTE channel3TempType;
	// ! 通道号1热电偶或热敏或电阻的子类型
	BYTE channel3TempSubmode;
	// ! 扫描间隔
	int nScanInterval;
	// ! 保留字段
	BYTE resverd[100];
}STATIONPARAM, *PSTATIONPARAM;

typedef struct GlobalParam
{
	// ! 工位数
	int nStation;
	// ! 工位参数
	STATIONPARAM station[MAXSTATION];
	// ! 保留字段
	BYTE resvered[100];
}GLOBALPARAM, *PGLOBALPARAM;

// ! 系统设置工位参数
extern GLOBALPARAM g_Param;
// ！系统文件读取工位参数
extern GLOBALPARAM g_SysParam;
// ! 程序路径
extern CString              g_strExePath;
// ！配置文件名称
extern CString              g_strSysFileName;