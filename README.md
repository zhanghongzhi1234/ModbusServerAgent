# ModbusServerAgent
ModbusServerAgent provide an protocol transfer. It read data from VeStore-TSDB realtime database, and put data to Modbus Server. This program plays the role of FEP, Transfer all 3rd party protocol to Modbus, then we can deal with it uniformly.

# Background
## Modbus
Modbus is a data communications protocol originally published by Modicon (now Schneider Electric) in 1979 for use with its programmable logic controllers (PLCs). Modbus has become a de facto standard communication protocol and is now a commonly available means of connecting industrial electronic devices.

Modbus is popular in industrial environments because it is openly published and royalty-free. It was developed for industrial applications, is relatively easy to deploy and maintain compared to other standards, and places few restrictions - other than the datagram (packet) size - on the format of the data to be transmitted.

The Modbus protocol uses character serial communication lines, Ethernet, or the Internet protocol suite as a transport layer.

Modbus supports communication to and from multiple devices connected to the same cable or Ethernet network. For example, there can be a device that measures temperature and another device to measure humidity connected to the same cable, both communicating measurements to the same computer.

Modbus is often used to connect a plant/system supervisory computer with a remote terminal unit (RTU) in supervisory control and data acquisition (SCADA) systems in the electric power industry. Many of the data types are named from industrial control of factory devices, such as ladder logic because of its use in driving relays: A single physical output is called a coil, and a single physical input is called a discrete input or a contact.

The development and update of Modbus protocols have been managed by the Modbus Organization since April 2004, when Schneider Electric transferred rights to that organization. The Modbus Organization is an association of users and suppliers of Modbus-compliant devices that advocates for the continued use of the technology. Modbus Organization, Inc. is a trade association for the promotion and development of Modbus protocol.

### Data Types

Object type	| Access | Size | Address Space
----| ---- | ---- | ----
Coil | Read-write | 1 bit | 0x0000 – 0xFFFF
Discrete input | Read-only | 1 bit | 0x0000 – 0xFFFF
Input register | Read-only | 16 bits | 0x0000 – 0xFFFF
Holding register | Read-write | 16 bits | 0x0000 – 0xFFFF

# Folder Structure
## ModbusComms
Modbus Library, include both client and server
+ DataBlock.h  
    - Define a Modbus DataBlock with start address and endress
+ ModubsException.h, ModbusException.cpp  
    - Define all kinds of ModbusException
+ ModubusInClient.h ModbusInClient.cpp
    - Modbus Client thread to connect to Modbus server and read/write data
+ ModubsService.h ModbusService.cpp
    - Modbus Server thread, listen and accept Modbus Client connection, hold all datas for read/write
## ModbusServerAgent
+ CommonFunction.h, CommonFunction.cpp
    - common functions library
+ DatapointPollingWorker.h DatapointPollingWorker.cpp
    - Polling all datapoints from VeStore-TSDB realtime database periodically by TagNames, send all update to main thread.
+ ModbusPointManager.h + ModbusPointManager.cpp
    - Read all config files, inlucde tagNames file, control DatapointPollingWorker synchronize and ModbusService start/stop.
+ ModbusServerAgent.h + ModbusServerAgent.cpp
    - main thread

# RTDUTest
RTDUTest use QT to make an interface, used to enter the roll call, and then the button to read the value, you can read single or multiple. Note that the controls that QT can provide are common to windows and linux, so there is no rich interface under windows. The degree of beauty also needs to be improved.  

From VS2017, New project, select QT Widget Application, and then double-click to generate the ui file in the project. After dragging the control to edit, set the objectName property, the QML language used inside QT, the QString used inside is unicode. The QString provide two methods, toStdString and fromStdString, for interacting with std::string  
````C++
std::string strResult = "value";
QString qsResult = QString::fromStdString(strResult);
ui.txtResult->setPlainText(qsResult);

connect(ui.btnGetData, SIGNAL(clicked()), this, SLOT(btnGetData_Click()));
````
Can write response function
````C++
void RTDUTest::btnGetData_Click()
{
QString qsTagName = ui.txtTagName->toPlainText();
std::string txtTagName = qsTagName.toStdString();

std::stringstream ss;
ss << "value: "<< pTagData->value << "time:" << pTagData->time << "status: "<< pTagData->status;
ui.txtResult->setPlainText(QString::fromStdString(ss.str()));
}
````

Qt is a widget toolkit for creating graphical user interfaces as well as cross-platform applications that run on various software and hardware platforms such as Linux, Windows, macOS, Android or embedded systems with little or no change in the underlying codebase while still being a native application with native capabilities and speed.  

Qt is used for developing graphical user interfaces (GUIs) and multi-platform applications that run on all major desktop platforms and most mobile or embedded platforms. Most GUI programs created with Qt have a native-looking interface, in which case Qt is classified as a widget toolkit. Non-GUI programs can also be developed, such as command-line tools and consoles for servers. An example of such a non-GUI program using Qt is the Cutelyst web framework

Qt supports various compilers, including the GCC C++ compiler, the Visual Studio suite, PHP via an extension for PHP5,[15] and has extensive internationalization support. Qt also provides Qt Quick, that includes a declarative scripting language called QML that allows using JavaScript to provide the logic. With Qt Quick, rapid application development for mobile devices became possible, while logic can still be written with native code as well to achieve the best possible performance.

# License
This application is under the Apache 2.0 license. See the [LICENSE](LICENSE) file for details..