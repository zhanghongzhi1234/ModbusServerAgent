#include "CommonFunction.h"
#include "RTDUTest.h"
#include <QMessageBox>
#include "RTDBDefine.h"
#include "RTDBInterface.h"
#include <sstream>

RTDUTest::RTDUTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//ui.lineEdit->setText("hello");
	connect(ui.btnGetData, SIGNAL(clicked()), this, SLOT(btnGetData_Click()));
	connect(ui.btnStartModbusServer, SIGNAL(clicked()), this, SLOT(btnStartModbusServer_Click()));
	connect(ui.btnWriteData, SIGNAL(clicked()), this, SLOT(btnWriteData_Click()));
	connect(ui.btnOKCancel, SIGNAL(accepted()), this, SLOT(accept()));
	connect(ui.btnOKCancel, SIGNAL(rejected()), this, SLOT(reject()));

	m_dllPath = "E:\\CPlusPlus\\QT\\RTDUTest\\RTDUTest\\dll";
	m_iniPath = "E:\\CPlusPlus\\QT\\RTDUTest\\RTDUTest\\dll";
	initRTDU();

	m_agent = new ModbusServerAgent();
}

RTDUTest::~RTDUTest()
{
	ReleaseConnect();
}

void RTDUTest::initRTDU()
{
	char* strParameters[4] = { (char*)m_dllPath.data(), (char*)m_iniPath.data(), (char*)"", (char*)"" };
	int nResult = InitConnect(strParameters, 1);
	showResult(nResult);
}

void RTDUTest::showResult(int nResult)
{
	std::string info;
	switch (nResult)
	{
	case(0):
		info = "建立数据库连接成功";
		break;
	case(-1):
		info = "网络连接异常";
		break;
	case(-2):
		info = "数据库连接异常";
		break;
	case(-3):
		info = "系统异常";
		break;
	case(-4):
		info = "其他异常";
		break;
	case(-5):
		info = "测点不存在（单点函数）";
		break;
	case(-6):
		info = "数据不存在";
		break;
	default:
		info = "未知错误";
		break;
	}
	QString qs = QString::fromLocal8Bit(info.c_str());
	QMessageBox::about(this, "Init", qs);
}

void RTDUTest::btnGetData_Click()
{
	QString qsTagName = ui.txtTagName->toPlainText();
	std::string txtTagName = qsTagName.toStdString();
	
	const char delim = '\n';
	std::vector<std::string> svec;
	CommonFunction::tokenize(txtTagName, delim, svec);

	if (svec.size() == 0)
	{
		QMessageBox::about(this, "Error", "No TagName input!");
	}
	else if (svec.size() == 1)
	{	//use single datapoint interface
		std::string tagName = svec.front();
		TagData* pTagData = new TagData();
		int nResult = GetRTDataByTagName(tagName.c_str(), pTagData);		//call single datapoint api
		if (nResult < 0)
		{
			showResult(nResult);
			ReleaseConnect();
		}
		else
		{
			std::stringstream ss;
			ss << "value: " << pTagData->value << "time: " << pTagData->time << "status: " << pTagData->status;
			ui.txtResult->setPlainText(QString::fromStdString(ss.str()));
		}
		delete pTagData;
	}
	else
	{	//use multi datapoint interface
		int nCount = svec.size();
		char** tagNames = CommonFunction::vector2StringArray(svec);
		TagData* pTagData = new TagData[nCount];
		int nResult = GetRTDataByBatch(tagNames, pTagData, nCount);			//call batch datapoint api
		if (nResult < 0)
		{
			showResult(nResult);
			ReleaseConnect();
		}
		else
		{
			std::stringstream ss;
			for (int i = 0; i < nCount; i++)
			{
				ss << "value: " << pTagData[i].value << "time: " << pTagData[i].time << "status: " << pTagData[i].status << "\n";
			}
			ui.txtResult->setPlainText(QString::fromStdString(ss.str()));
		}
		delete[] tagNames;
		delete pTagData;
	}

	std::string strResult = "value";
	QString qsResult = QString::fromStdString(strResult);
	ui.txtResult->setPlainText(qsResult);
}

void RTDUTest::btnWriteData()
{
	QString qsTagName = ui.leTagName->text();
	std::string txtTagName = qsTagName.toStdString();
	bool bChecked = ui.radType->isChecked();
	int nStatus = ui.leStatus->text().toInt();
	double dValue = ui.leValue->text().toDouble();

	InsertData* pInsertData = new InsertData();
	strcpy_s(pInsertData->pointName, txtTagName.size() + 1, txtTagName.c_str());
	pInsertData->status = nStatus;
	pInsertData->value = dValue;
	pInsertData->type = bChecked;
	int nResult = AppendRTTagDataByTagName(pInsertData);
	showResult(nResult);
	delete pInsertData;
}

void RTDUTest::btnStartModbusServer_Click()
{
	return;
	QString qsBtnText = ui.btnStartModbusServer->text();
	std::string txtBtnText = qsBtnText.toStdString();
	if (txtBtnText == "Start Modbus Server")
	{
		QString qsTagName = ui.txtTagName->toPlainText();
		std::string txtTagName = qsTagName.toStdString();
		m_agent->startSynchronise(txtTagName);

		std::string strText = "Stop Modbus Server";
		QString qsText = QString::fromStdString(strText);
		ui.btnStartModbusServer->setText(qsText);
	}
	else
	{
		m_agent->stopSynchronise();
		std::string strText = "Start Modbus Server";
		QString qsText = QString::fromStdString(strText);
		ui.btnStartModbusServer->setText(qsText);
	}
}

void RTDUTest::accept()
{
	this->close();
}

void RTDUTest::reject()
{
	this->close();
}