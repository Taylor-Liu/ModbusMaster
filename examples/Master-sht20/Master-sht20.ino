#include <ModbusMaster.h>

uint16_t m_startAddress = 1;//要读取的从站起始地址
uint8_t m_length = 2;  //需要读取的数据长度

ModbusMaster node;

void setup()
{
  // use Serial (port 1); initialize Modbus communication baud rate
  // communicate with Modbus slave ID 1 over Serial (port 1)
  Serial1.begin(9600);
  node.begin(1, Serial1);

  Serial.begin(115200);
}

void loop()
{
  uint8_t result;
  uint16_t data[2];
  
  result = node.readInputRegisters(m_startAddress, m_length);
  
  // do something with data if read is successful
  if (result == node.ku8MBSuccess)
  {
//    Serial.println("success!");
    for (uint8_t j = 0; j < 2; j++)
    {
      data[j] = node.getResponseBuffer(j);
    }
    Serial.println("temperature: " + String(data[0]/10.0) + "  humidity: " + String(data[1]/10.0));
  }

  delay(100);
}
