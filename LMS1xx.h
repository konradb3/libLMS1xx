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

/*!
* @class scanCfg
* @brief Structure containing scan configuration.
*
* @author Konrad Banachowicz
*/
typedef struct _scanCfg {
	/*!
	 * @brief Scanning frequency.
	 */
	int scaningFrequency;

	/*!
	 * @brief Scanning resolution.
	 */
	int angleResolution;

	/*!
	 * @brief Start angle.
	 */
	int startAngle;

	/*!
	 * @brief Stop angle.
	 */
	int stopAngle;
} scanCfg;

/*!
* @class scanDataCfg
* @brief Structure containing scan data configuration.
*
* @author Konrad Banachowicz
*/
typedef struct _scanDataCfg {

	/*!
	 * @brief Output channels.
	 * Defines which output channel is activated.
	 */
	int outputChannel;

	/*!
	 * @brief Remission.
	 * Defines whether remission values are output.
	 */
	int remission;

	/*!
	 * @brief Remission resolution.
	 * Defines whether the remission values are output with 8-bit or 16bit resolution.
	 */
	int resolution;

	/*!
	 * @brief Encoders channels.
	 * Defines which output channel is activated.
	 */
	int encoder;

	/*!
	 * @brief Position.
	 * Defines whether position values are output.
	 */
	int position;

	/*!
	 * @brief Device name.
	 * Determines whether the device name is to be output.
	 */
	int deviceName;

	/*!
	 * @brief Output interval.
	 * Defines which scan is output.
	 */
	int outputInterval;
} scanDataCfg;

/*!
* @class scanData
* @brief Structure containing single scan message.
*
* @author Konrad Banachowicz
*/
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

/*!
* @class LMS1xx
* @brief Class responsible for communicating with LMS1xx device.
*
* @author Konrad Banachowicz
*/

class LMS1xx {
public:
	LMS1xx();
	virtual ~LMS1xx();

	/*!
	* @brief Connect to LMS1xx.
	* @param host LMS1xx host name or ip address.
	* @param port LMS1xx port number.
	*/
	void connect(std::string host, int port = 2111);

	/*!
	* @brief Disconnect from LMS1xx device.
	*/
	void disconnect();

	/*!
	* @brief Get status of connection.
	* @returns connected or not.
	*/
	bool isConnected();

	/*!
	* @brief Start measurements.
	* After receiving this command LMS1xx unit starts spinning laser and measuring.
	*/
	void startMeas();

	/*!
	* @brief Stop measurements.
	* After receiving this command LMS1xx unit stop spinning laser and measuring.
	*/
	void stopMeas();

	/*!
	* @brief Get current status of LMS1xx device.
	* @returns status of LMS1xx device.
	*/
	int queryStatus();

	/*!
	* @brief Log into LMS1xx unit.
	* Increase privilege level, giving ability to change device configuration.
	*/
	void login();

	/*!
	* @brief Get current scan configuration.
	* Get scan configuration :
	* - scanning frequency.
	* - scanning resolution.
	* - start angle.
	* - stop angle.
	* @returns scanCfg structure.
	*/
	scanCfg getScanCfg();

	/*!
	* @brief Set scan configuration.
	* Get scan configuration :
	* - scanning frequency.
	* - scanning resolution.
	* - start angle.
	* - stop angle.
	* @param scanCfg structure containing scan configuration.
	*/
	void setScanCfg(scanCfg &cfg);

	/*!
	* @brief Set scan data configuration.
	* Set format of scan message returned by device.
	* @param scanDataCfg structure containing scan data configuration.
	*/
	void setScanDataCfg(scanDataCfg &cfg);

	/*!
	* @brief Start or stop continuous data acquisition.
	* After reception of this command device start or stop continuous data stream containing scan messages.
	* @param start 1 : start 0 : stop
	*/
	void scanContinous(int start);

	/*!
	* @brief Receive single scan message.
	*
	* @param data pointer to scanData buffer structure.
	*/
	void getData(scanData* data);

private:
	bool connected;
	bool debug;

	int sockDesc;
};

#endif /* LMS1XX_H_ */
