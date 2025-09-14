# Seeker v1 Arduino Library


## การติดตั้ง

1. โหลดไฟล์ของ `Seeker_v1_bymitas` ทั้งหมด
2. เปิดไฟล์ `Seeker_v1_bymitas` เพื่อใช้งาน

## การเชื่อมต่อ

### Motor Driver (TT6612FNG)
- **Motor A:** 
  - PWM: Pin 3
  - IN1: Pin 4
  - IN2: Pin 5
- **Motor B:**
  - PWM: Pin 6
  - IN1: Pin 7
  - IN2: Pin 8

### Switch
- **SW:** Pin 12 (INPUT_PULLUP)

### Line Sensors
- **Sensor 1:** A0
- **Sensor 2:** A1
- **Sensor 3:** A2
- **Sensor 4:** A3
- **Sensor 5:** A4
- **Sensor 6:** A5
- **Sensor 7:** A6
- **Sensor 8:** A7

## ฟังก์ชันหลัก

### 1. seekersetup()
```cpp
seekersetup()
```
**การทำงาน:** ตั้งค่าเริ่มต้นของระบบ
- กำหนด pin mode สำหรับ motor control
- ตั้งค่า Serial communication (9600 baud)
- ตั้งค่า switch เป็น INPUT_PULLUP
- ปรับความถี่ PWM (Timer2: ~980Hz, Timer0: ~976Hz)

### 2. motor(channel, pwm)
```cpp
motor(int channel, int pwm)
```
**การทำงาน:** ควบคุม motor แต่ละตัว
- **channel:** 1 = Motor A, 2 = Motor B
- **pwm:** ความเร็ว 0-100% (จะถูก map เป็น 0-255)
- **ค่าลบ:** หมุนย้อนกลับ

### 3. wait_sw()
```cpp
wait_sw()
```
**การทำงาน:** รอให้ผู้ใช้กดและปล่อย switch
- รอจนกว่า switch จะถูกกด (HIGH → LOW)
- รอ 50ms เพื่อป้องกันการ bounce
- รอจนกว่า switch จะถูกปล่อย (LOW → HIGH)

## ฟังก์ชันการเคลื่อนที่

### 4. fd(pwm) - Forward
```cpp
fd(int pwm)
```
**การทำงาน:** ไปข้างหน้า
- หมุน motor ทั้งสองไปข้างหน้า
- **pwm > 0:** ทำงาน, **pwm ≤ 0:** หยุด

### 5. bk(pwm) - Backward
```cpp
bk(int pwm)
```
**การทำงาน:** ถอยหลัง
- หมุน motor ทั้งสองไปข้างหลัง
- **pwm > 0:** ทำงาน, **pwm ≤ 0:** หยุด

### 6. sr(pwm) - Spin Right
```cpp
sr(int pwm)
```
**การทำงาน:** เลี้ยวขวา
- Motor A: ไปข้างหน้า
- Motor B: ไปข้างหลัง
- **pwm > 0:** ทำงาน, **pwm ≤ 0:** หยุด

### 7. sl(pwm) - Spin Left
```cpp
sl(int pwm)
```
**การทำงาน:** เลี้ยวซ้าย
- Motor A: ไปข้างหลัง
- Motor B: ไปข้างหน้า
- **pwm > 0:** ทำงาน, **pwm ≤ 0:** หยุด

### 8. ao() - All Off
```cpp
ao()
```
**การทำงาน:** หยุด motor ทั้งหมด
- ตั้งค่า motor ทั้งสองเป็น 0

## ฟังก์ชันทดสอบ

### 9. testmotor()
```cpp
testmotor()
```
**การทำงาน:** ทดสอบการทำงานของ motor
- ไปข้างหน้า 1 วินาที
- ถอยหลัง 1 วินาที
- เลี้ยวขวา 1 วินาที
- เลี้ยวซ้าย 1 วินาที
- หยุด

### 10. calibratesensor()
```cpp
calibratesensor()
```
**การทำงาน:** คาลิเบรต sensor ทั้ง 8 ตัว
- อ่านค่า sensor 400 ครั้ง
- หาค่าต่ำสุดและสูงสุดของแต่ละ sensor
- แสดงผลเป็น array สำหรับใช้ในโค้ด

## ตัวอย่างการใช้งาน

```cpp
void setup() {
  seekersetup();
  wait_sw();  // รอให้กด switch
}

void loop() {
  fd(80);     // ไปข้างหน้า 80%
  delay(2000);
  sr(60);     // เลี้ยวขวา 60%
  delay(1000);
  ao();       // หยุด
  delay(1000);
}
```

## ข้อกำหนด

- Arduino Nano
- Motor Driver TB6612FMG
- DC Motor 2 ตัว
- Line Sensor 8 ตัว

## เวอร์ชัน

- **v1.0** - ฟังก์ชันพื้นฐานสำหรับหุ่นยนต์เดินตามเส้น



