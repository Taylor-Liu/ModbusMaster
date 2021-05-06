#include <ModbusMaster.h>

uint16_t m_startAddress = 0;//要读取的从站起始地址
uint8_t m_length = 8;  //需要读取的数据长度

ModbusMaster node;

void setup()
{
  // use Serial (port 1); initialize Modbus communication baud rate
  // communicate with Modbus slave ID 1 over Serial (port 1)
  Serial1.begin(9600);
  node.begin(0xff, Serial1);

  // node.writeSingleCoil(0, 0xff);  // 打开1号继电器（手动模式）
  // node.writeSingleCoil(0, 0);     // 关闭1号继电器（手动模式）
  // node.writeSingleCoil(1, 0xff);  // 打开2号继电器（手动模式）
  // node.writeSingleCoil(1, 0);     // 关闭2号继电器（手动模式）
  
  Serial.begin(115200);
}

void loop()
{
  uint8_t result;
  uint16_t data;
  
  result = node.readCoils(m_startAddress, m_length);
  
  // do something with data if read is successful
  if (result == node.ku8MBSuccess)
  {
    data = node.getResponseBuffer(0);

    Serial.print("relay state: ");
    Serial.print(data & 1 << 0);
    Serial.print(" ");
    Serial.print((data & 1 << 1) >> 1);
    Serial.print("\n");
  }

  delay(100);
}
