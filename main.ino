/*
 * 项目名称: 段码屏/指示灯控制程序
 * 功能描述: 
 * 1. 包含8个小灯 (对应8个输出引脚)
 * 2. 输入数字 (1-8)，对应的第N个小灯亮起
 * 3. (可选) 如果连接的是数码管，则显示对应数字
 */

// 定义8个小灯连接的引脚 (请根据实际硬件修改)
const int ledPins[8] = {2, 3, 4, 5, 6, 7, 8, 9};

// 如果是段码屏，这里定义0-9的段码表 (共阴极)
const byte segmentMap[10] = {
  0x3F, // 0
  0x06, // 1
  0x5B, // 2
  0x4F, // 3
  0x66, // 4
  0x6D, // 5
  0x7D, // 6
  0x07, // 7
  0x7F, // 8
  0x6F  // 9
};

void setup() {
  Serial.begin(9600); // 初始化串口，用于输入数字
  
  // 初始化8个小灯引脚为输出模式
  for (int i = 0; i < 8; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW); // 初始状态全部熄灭
  }
  
  Serial.println("系统已启动，请输入数字 (1-8):");
}

void loop() {
  // 检查是否有串口输入 (满足要求②：输入数字)
  if (Serial.available() > 0) {
    int inputNum = Serial.parseInt(); // 读取输入的数字
    
    // 清除之前的状态 (全部熄灭)
    clearAllLights();
    
    // 判断输入的数字是否在有效范围内 (1-8)
    if (inputNum >= 1 && inputNum <= 8) {
      // 点亮对应的第N个小灯 (数组索引从0开始，所以减1)
      digitalWrite(ledPins[inputNum - 1], HIGH);
      
      Serial.print("输入数字: ");
      Serial.print(inputNum);
      Serial.println(" -> 对应的第 ");
      Serial.print(inputNum);
      Serial.println(" 个小灯已亮起。");
      
    } else if (inputNum >= 0 && inputNum <= 9) {
      // 如果输入的是0-9，并且您连接的是段码屏，这里可以调用段码显示函数
      // displaySegment(inputNum); 
      Serial.print("输入数字: ");
      Serial.print(inputNum);
      Serial.println(" -> 准备在段码屏上显示。");
    } else {
      Serial.println("输入无效，请输入 1-8 之间的数字。");
    }
  }
}

// 辅助函数：熄灭所有小灯
void clearAllLights() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

// 辅助函数：段码屏显示数字 (伪代码，需根据具体驱动芯片实现)
void displaySegment(int num) {
  // 实际操作中，这里会将 segmentMap[num] 写入到段码屏的寄存器
  // 例如：使用 TM1650 或 74HC595 驱动
}
