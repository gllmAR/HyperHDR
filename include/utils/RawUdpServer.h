#pragma once

/* RawUdpServer.h
*
*  MIT License
*
*  Copyright (c) 2023 awawa-dev
*
*  Project homesite: https://github.com/awawa-dev/HyperHDR
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in all
*  copies or substantial portions of the Software.

*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*  SOFTWARE.
*/

// utils
#include <utils/Logger.h>
#include <utils/settings.h>

// qt
#include <QVector>

class QUdpSocket;
class NetOrigin;
class HyperHdrInstance;
class QTimer;

class RawUdpServer : public QObject
{
	Q_OBJECT

public:
	RawUdpServer(HyperHdrInstance* hyperhdr, const QJsonDocument& config, QObject* parent = nullptr);
	~RawUdpServer() override;

public slots:
	///
	/// @brief Handle settings update
	/// @param type   The type from enum
	/// @param config The configuration
	///
	void handleSettingsUpdate(settings::type type, const QJsonDocument& config);

	void initServer();

	void readPendingDatagrams();

	void dataTimeout();

private:
	///
	/// @brief Start the server with current _port
	///
	void startServer();

	///
	/// @brief Stop server
	///
	void stopServer();

private:
	QUdpSocket*		_server;
	Logger*			_log;
	quint16			_port;
	int				_priority;
	bool			_initialized;

	HyperHdrInstance*		_hyperhdr;
	const QJsonDocument		_config;
	QTimer*					_inactiveTimer;
};
