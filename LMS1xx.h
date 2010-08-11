/*
 * LMS1xx.h
 *
 *  Created on: 09-08-2010
 *  Author: Konrad Banachowicz
 ***************************************************************************
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Lesser General Public            *
 *   License as published by the Free Software Foundation; either          *
 *   version 2.1 of the License, or (at your option) any later version.    *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place,                                    *
 *   Suite 330, Boston, MA  02111-1307  USA                                *
 *                                                                         *
 ***************************************************************************/

#ifndef LMS1XX_H_
#define LMS1XX_H_

#include <string>
#include <inttypes.h>

typedef struct _scanCfg {
	int scaningFrequency;
	int angleResolution;
	int startAngle;
	int stopAngle;
} scanCfg;

typedef struct _scanDataCfg {
	int outputChannel; // Defines which output channel is activated.
	int remission; // Defines whether remission values are output
	int resolution; // Defines whether the remission values are output with 8-bit or 16bit resolution
	int encoder; // Defines which output channel is activated.
	int position; // Defines whether position values are output
	int deviceName; // Determines whether the device name is to be output
	int outputInterval; // Defines which scan is output
} scanDataCfg;

typedef struct _scanData {
	int dist_len1;
	uint16_t dist1[1082];
	int dist_len2;
	uint16_t dist2[1082];
	int rssi_len1;
	uint16_t rssi1[1082];
	int rssi_len2;
	uint16_t rssi2[1082];
} scanData;

class LMS1xx {
public:
	LMS1xx();
	virtual ~LMS1xx();

	void connect(std::string host, int port = 2111);
	void disconnect();
	bool isConnected();

	void startMeas();
	void stopMeas();
	int queryStatus();
	void login();
	scanCfg getScanCfg();
	void setScanCfg(scanCfg &cfg);
	void setScanDataCfg(scanDataCfg &cfg);
	void scanContinous(int start);
	void getData(scanData* data);

private:
	bool connected;
	bool debug;

	int sockDesc;
};

#endif /* LMS1XX_H_ */
