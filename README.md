# 🏠 Hệ thống Nhà Thông Minh Điều khiển Máy Bơm Nước và Thiết bị Bếp

---

## 🎉 Giới thiệu

Dự án này được thực hiện trong môn **Lập trình Nhúng** tại Học viện Công nghệ Bưu chính Viễn thông - Cơ sở TP.HCM.

Hệ thống nhà thông minh điều khiển **máy bơm nước**, **đèn bếp** và **quạt thông gió**, tích hợp cảm biến và giao diện người dùng thân thiện, mang lại sự tiện nghi và hiệu quả cho không gian bếp hiện đại.

Hệ thống sử dụng **vi điều khiển NUCLEO-STM32F429ZI**, các loại cảm biến (siêu âm, chuyển động, ánh sáng), **LCD**, bàn phím và được lập trình nhúng để đảm bảo hoạt động thông minh và ổn định.

### Thông tin dự án:

- **Sinh viên:** Trần Minh Thương  
- **Mã số sinh viên:** N21DCVT101  
- **Lớp:** D21CQVTHI01-N  
- **Giảng viên:** ThS. Phạm Quốc Hợp  
- **Ngày:** 10/05/2025

---

## 🎯 Mục tiêu Dự án

- **Tự động hóa 🤖:** Giám sát và điều khiển thiết bị (máy bơm, đèn, quạt) dựa trên cảm biến và lịch thời gian.  
- **Linh hoạt 🔄:** Hỗ trợ chế độ thủ công và tự động, cùng với cài đặt lịch bật/tắt.  
- **Trải nghiệm người dùng 🖥️:** Giao diện LCD 20x4 trực quan, nhập liệu bằng bàn phím 4x4, có bảo mật mật khẩu.  
- **Hiệu quả ⚡:** Vận hành ổn định, tiết kiệm năng lượng.

---

## 📋 Tính năng Chính

### 🔧 Chế độ Thủ công 🖐️

- Bật/tắt đèn, quạt, máy bơm qua nút nhấn hoặc bàn phím (A/B/C).

### 🤖 Chế độ Tự động

- Máy bơm hoạt động khi mực nước thấp (HC-SR04) và dừng khi đầy.  
- Đèn bếp bật khi có chuyển động (PIR AM312) **và** ánh sáng yếu (LDR NVZ1).  
- Quạt **luôn bật** trong chế độ tự động.

### ⏰ Cài đặt Thời gian

- Đặt lịch bật/tắt cho thiết bị (phím 1/2/3) và đặt giờ hệ thống (phím 4).

### 🔒 Bảo mật

- **1111:** Thủ công  
- **2222:** Tự động  
- **3333:** Cài đặt thời gian  
- **8888:** Mở khóa  
- **9999:** Khóa hệ thống

### 🖥️ Giao diện

- LCD 20x4 hiển thị menu, trạng thái thiết bị, và cảnh báo lỗi.

### 🚨 Phản hồi

- LED (xanh/đỏ) và còi để cảnh báo hoặc phản hồi trạng thái.

---

## 🛠️ Thành phần Phần cứng

| Linh kiện            | Mô tả |
|----------------------|-------|
| **NUCLEO-STM32F429ZI** | Vi điều khiển ARM Cortex-M4, 180 MHz, 2 MB Flash, 256 KB SRAM |
| **HC-SR04**          | Cảm biến siêu âm đo mực nước (2–450 cm, độ chính xác 3 mm) |
| **PIR AM312**        | Cảm biến phát hiện chuyển động (3–5 m) |
| **LDR NVZ1**         | Cảm biến ánh sáng đo cường độ sáng |
| **Bàn phím 4x4**     | 16 phím ma trận (0–9, A–D, *, #) |
| **LCD 20x4**         | Hiển thị trạng thái (giao tiếp 4-bit hoặc I2C) |
| **Relay 5V**         | Điều khiển thiết bị điện (220V/10A) |
| **LED & Còi**        | Hiển thị trạng thái, cảnh báo lỗi |

### 📸 Hình ảnh Linh kiện

> (Chèn hình ảnh thực tế vào thư mục `media/` và thêm liên kết tại đây nếu có.)

---

## 🔌 Kết nối Chân

- **HC-SR04:** TRIG (PA6), ECHO (PA7)  
- **PIR AM312:** OUT (PA3)  
- **LDR NVZ1:** DO (PG9)  
- **Bàn phím 4x4:**  
  - Hàng: PB3, PB5, PC7, PA15  
  - Cột: PB12, PB13, PB15, PC6  
- **Nút nhấn:** PE9, PE11, PF14, PE13, PF15  
- **Relay:** PF2 (máy bơm), PE6 (quạt)  
- **LED:** PG14, PB6, PB2, PD15, PF12  
- **Còi:** PE10  
- **LCD:** GPIO hoặc I2C qua PCF8574 (SDA/SCL)

---

## 📊 Kiến trúc Hệ thống

Vi điều khiển **STM32F429ZI** là trung tâm điều khiển:

### Giao thức Truyền thông:

- **GPIO 📡:** Điều khiển cảm biến, relay, LED, nút nhấn  
- **Keypad ⌨️:** Quét bàn phím 4x4  
- **HC-SR04 ⏱️:** Đo khoảng cách bằng TRIG/ECHO  
- **LCD 🖥️:** Giao tiếp song song hoặc I2C  
- **Ngắt ⚡:** Phản hồi sự kiện nhanh từ cảm biến/nút nhấn

---

## 💻 Chi tiết Phần mềm

### Môi trường Phát triển

- **IDE:** Visual Studio Code + PlatformIO  
- **Framework:** Arduino cho STM32  
- **Ngôn ngữ:** C/C++  
- **Thư viện:**  
  - `LiquidCrystal_I2C`  
  - `STM32 MUCLEO-F429ZI`

### Kiến trúc Phần mềm

- **FSM 🧠:** Quản lý các chế độ (Thủ công, Tự động, Cài đặt thời gian)  
- **Interrupt-Driven ⚡:** Xử lý ngắt từ nút và cảm biến  
- **Module hóa 🧩:** Tách các chức năng thành module  
- **Soft-RTC ⏲️:** Sử dụng `millis()` và `micros()`  
- **Debounce 🔧:** Chống nhiễu nút nhấn và bàn phím

---

## 📁 Cấu trúc Thư mục

```plaintext
├── include/
│   ├── actuators.h
│   ├── buttons.h
│   ├── display.h
│   ├── keypad.h
│   ├── modes.h
│   ├── security.h
│   ├── sensors.h
│   ├── time_management.h
│   ├── utils.h
├── src/
│   ├── main.cpp
│   ├── actuators.cpp
│   ├── buttons.cpp
│   ├── display.cpp
│   ├── keypad.cpp
│   ├── modes.cpp
│   ├── security.cpp
│   ├── sensors.cpp
│   ├── time_management.cpp
│   ├── utils.cpp
├── platformio.ini
├── README.md
├── media/
│   ├── image23.png
│   ├── image24.png

```

# 🚀 Hướng dẫn Cài đặt và Sử dụng

## ⚙️ Yêu cầu phần mềm

- Visual Studio Code  
- PlatformIO IDE (cài trực tiếp trên VSCode)  
- Driver STLink (cho board STM32 Nucleo)  
- Python 3 (được PlatformIO sử dụng nội bộ)

---

## 📦 Cài đặt môi trường

### 1. Cài đặt Visual Studio Code  
Tải và cài đặt từ: https://code.visualstudio.com/

### 2. Cài đặt PlatformIO Extension  
Mở VSCode → Mở mục **Extensions** (Ctrl+Shift+X)  
Tìm **"PlatformIO IDE"** → Nhấn **Install**

### 3. Clone dự án về máy

```bash
git clone https://github.com/tennguoidung/ten-repo.git
cd ten-repo
```
### 4. Mở thư mục bằng VSCode

Vào File → Open Folder... và chọn thư mục dự án vừa clone.

🔧 Cấu hình PlatformIO
File platformio.ini đã được cấu hình sẵn:

- [env:nucleo_f429zi]

- platform = ststm32

- board = nucleo_f429zi

- framework = arduino

- upload_protocol = stlink

- monitor_speed = 115200

⚠️ Nếu bạn sử dụng bo mạch khác, hãy chỉnh lại board = cho phù hợp với phần cứng của bạn.

🚀 Biên dịch và Upload

- Nhấn PlatformIO: Build (✔️) để biên dịch mã nguồn.

- Nhấn PlatformIO: Upload (➡️) để nạp chương trình vào board.

- Đảm bảo board đã được kết nối với máy tính qua cáp USB.

🖥️ Theo dõi Serial Monitor

Nhấn PlatformIO: Monitor (🔍) để xem log hoặc phản hồi từ vi điều khiển.

## 🔑 Mật khẩu sử dụng

| Mật khẩu | Chức năng                        |
|----------|----------------------------------|
| 1111     | Kích hoạt chế độ **Thủ công**   |
| 2222     | Kích hoạt chế độ **Tự động**    |
| 3333     | **Cài đặt Thời gian & Lịch**    |
| 8888     | **Mở khóa hệ thống**            |
| 9999     | **Khóa hệ thống tạm thời**      |


👉 Nhập mật khẩu bằng bàn phím 4x4 và nhấn # để xác nhận.

📋 Ghi chú sử dụng

- Màn hình LCD 20x4 hiển thị menu, thông báo và lỗi hệ thống.

- Hệ thống có thể sử dụng nút nhấn để điều khiển nhanh các thiết bị.

- Còi cảnh báo sẽ phát tiếng nếu có lỗi hoặc nhập sai mật khẩu.

🧪 Kiểm tra và Thử nghiệm

- Đặt tay trước cảm biến PIR → đèn sẽ bật nếu ánh sáng yếu.

- Đổ nước vào bể thử HC-SR04 → máy bơm sẽ bật/tắt tương ứng.

- Nhấn các nút hoặc nhập lệnh để kiểm tra các chức năng như thời gian, relay.

---

## 💡 Nếu bạn thích dự án này, hãy ⭐️ trên GitHub nhé! 

## 📩 Liên hệ:  
[tranminhthuong08082003@gmail.com](mailto:tranminhthuong08082003@gmail.com)

---

## 📌 Tác giả:  
🚀 **Tran Minh Thuong** 🚀


