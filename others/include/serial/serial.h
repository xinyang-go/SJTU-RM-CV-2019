#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <Windows.h>

class Serial
{
public:
	Serial(UINT portNo = 1, UINT  baud = CBR_9600, char  parity = 'N', UINT  databits = 8, UINT  stopsbits = 1, DWORD dwCommEvents = EV_RXCHAR);
	~Serial();

	bool InitPort(UINT  portNo = 1, UINT  baud = CBR_9600, char  parity = 'N', UINT  databits = 8, UINT  stopsbits = 1, DWORD dwCommEvents = EV_RXCHAR);
	UINT GetBytesInCOM() const ;
	bool WriteData(const unsigned char* pData, unsigned int length);
	bool ReadData(unsigned char* buffer, unsigned int length);
private:
	bool openPort(UINT  portNo);
	void ClosePort();
	void ErrorHandler();
private:
	HANDLE hComm;
	UINT portNo;
	UINT baud;
	char parity;
	UINT databits;
	UINT stopsbits;
	DWORD dwCommEvents;
};

#endif /* _SERIAL_H_ */
