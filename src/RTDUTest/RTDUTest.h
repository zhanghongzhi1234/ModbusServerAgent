#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RTDUTest.h"
#include "ModbusServerAgent.h"

using namespace TA_Base_App;

class RTDUTest : public QMainWindow
{
	Q_OBJECT

public:
	RTDUTest(QWidget *parent = Q_NULLPTR);
	~RTDUTest();

private:
	Ui::RTDUTestClass ui;

public slots:
	void btnGetData_Click();
	void btnStartModbusServer_Click();
	void btnWriteData();
	void accept();
	void reject();

private:
	std::string m_dllPath;
	std::string m_iniPath;

	void initRTDU();
	void showResult(int nResult);

	ModbusServerAgent* m_agent;
};
