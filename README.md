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
  - STM32 HAL/LL

### Kiến trúc Phần mềm

- **FSM 🧠:** Quản lý các chế độ (Thủ công, Tự động, Cài đặt thời gian)  
- **Interrupt-Driven ⚡:** Xử lý ngắt từ nút và cảm biến  
- **Module hóa 🧩:** Tách các chức năng thành module  
- **Soft-RTC ⏲️:** Sử dụng `millis()` và `micros()`  
- **Debounce 🔧:** Chống nhiễu nút nhấn và bàn phím

---

## 📁 Cấu trúc Thư mục

├── include/
│ ├── actuators.h
│ ├── buttons.h
│ ├── display.h
│ ├── keypad.h
│ ├── modes.h
│ ├── security.h
│ ├── sensors.h
│ ├── time_management.h
│ ├── utils.h
├── src/
│ ├── main.cpp
│ ├── actuators.cpp
│ ├── buttons.cpp
│ ├── display.cpp
│ ├── keypad.cpp
│ ├── modes.cpp
│ ├── security.cpp
│ ├── sensors.cpp
│ ├── time_management.cpp
│ ├── utils.cpp
├── platformio.ini
├── README.md
├── media/
│ ├── image23.png
│ ├── image24.png

---

## 🚀 Hướng dẫn Cài đặt và Sử dụng

### Yêu cầu

**Phần cứng:**  
- NUCLEO-STM32F429ZI  
- HC-SR04, PIR AM312, LDR NVZ1  
- Bàn phím 4x4, LCD 20x4, Relay  
- LED, Còi, nguồn 5V/12V

**Phần mềm:**  
- Visual Studio Code  
- PlatformIO  
- Driver ST-LINK

### Các bước Cài đặt

1. **Clone repo 📥:**

git clone https://github.com/MinhThuongTMT/Full_Code-Project-LTN.git
cd Full_Code-Project-LTN
Mở trong VS Code 💻:

Mở thư mục dự án

PlatformIO tự nhận file platformio.ini

Kết nối Phần cứng 🔌:

Nối thiết bị theo sơ đồ chân

Cấp nguồn 5V cho vi điều khiển/cảm biến, 12V cho relay

Biên dịch & Upload ⚙️:

Mở bảng PlatformIO

Nhấn Build để biên dịch

Nhấn Upload để nạp mã

Kiểm tra 🧪:

LCD hiển thị menu chính

Thử điều khiển bằng nút và bàn phím

## 🔍 Hướng dẫn Sử dụng
Hướng dẫn Sử dụng

Chế độ Hệ thống





Thủ công (Mật khẩu: 1111 hoặc nút BUTTON_MANUAL):





Dùng nút hoặc phím A (đèn), B (quạt), C (máy bơm) để bật/tắt.



LED hiển thị trạng thái (xanh: BẬT, đỏ: TẮT).



Tự động (Mật khẩu: 2222 hoặc nút BUTTON_AUTO):





Máy bơm bật nếu mực nước > 20 cm, tắt nếu < 10 cm.



Đèn bật khi có chuyển động và ánh sáng yếu.



Quạt luôn bật.



Cài đặt Thời gian (Mật khẩu: 3333 hoặc nút BUTTON_SETTING):





Phím 4: Đặt giờ hiện tại (hh:mm, xác nhận bằng #).



Phím 1/2/3: Đặt lịch BẬT/TẮT cho đèn/quạt/máy bơm.



Phím A: Xem trạng thái thiết bị (BẬT/TẮT hoặc "Chưa cài").



Khóa/Mở Hệ thống:





Từ menu chính (phím *), chọn "2. Khoa he thong".



Nhập 8888 (mở) hoặc 9999 (khóa), xác nhận bằng #.



Hệ thống khóa vô hiệu hóa nút nhấn.

Điều hướng Bàn phím







Phím



Chức năng





*



Mở menu chính từ màn hình Home





#



Xác nhận nhập liệu (mật khẩu, thời gian)





A



Bật/tắt đèn (Thủ công) hoặc xem trạng thái





B



Bật/tắt quạt (Thủ công)





C



Bật/tắt máy bơm (Thủ công)





D



Xóa ký tự cuối trong nhập liệu





0–9



Nhập số cho mật khẩu, thời gian, mực nước

Ví dụ Sử dụng





Khởi động 🚀:





Bật nguồn; LCD hiển thị màn hình chính.



Vào Chế độ Thủ công 🖐️:





Nhấn *, chọn "1. Chon che do", nhập 1111, nhấn #.



Nhấn A để bật/tắt đèn; LCD hiển thị "Bat den" hoặc "Tat den".



Cài Mực Nước 💧:





Từ menu, chọn "3. Cai dat muc nuoc".



Nhập mực nước bật (ví dụ: 20 cm), nhấn #, sau đó mực tắt (10 cm), nhấn #.



Khóa Hệ thống 🔒:





Từ menu, chọn "2. Khoa he thong", nhập 9999, nhấn #.



LCD hiển thị "System Locked".



🔍 Hạn chế Dự án





Giới hạn Thiết bị 🚫: Chỉ điều khiển máy bơm, đèn, quạt; chưa hỗ trợ thiết bị khác (bếp từ, tủ lạnh).



Phần cứng ⚠️: Cảm biến dễ bị nhiễu bởi bụi, nhiệt, ánh sáng mạnh.



Giao diện 📺: LCD 20x4 chỉ hiển thị ký tự, thiếu đồ họa hoặc đa ngôn ngữ.



Kết nối 🌐: Không hỗ trợ Internet, không điều khiển từ xa.



Thời gian ⏳: Soft-RTC dễ trôi giờ nếu mất điện.



Bảo mật 🔐: Mật khẩu cố định, không thay đổi động.



🌟 Cải tiến Tương Lai





Kết nối IoT 📱: Thêm Wi-Fi (ESP32) để điều khiển qua ứng dụng/web.



Cảm biến Nâng cao 🌡️: Tích hợp cảm biến nhiệt độ, độ ẩm (DHT22) hoặc khí gas (MQ-2).



Giao diện Hiện đại 🖼️: Sử dụng màn hình cảm ứng TFT hoặc điều khiển bằng giọng nói.



Tiết kiệm Năng lượng ⚡: Thêm chế độ ngủ và giám sát tiêu thụ điện.



Module hóa 🧩: Thiết kế phần cứng/phần mềm plug-and-play.



Bảo mật 🔒: Hỗ trợ mật khẩu động và mã hóa dữ liệu.



📚 Tài liệu Tham khảo





Nguyễn Văn An & Phạm Thị Hồng Nhung, "Thiết kế hệ thống điều khiển tự động máy bơm nước sử dụng vi điều khiển STM32," PTIT, 2022.



Trần Quốc Hùng, "Ứng dụng cảm biến siêu âm HC-SR04 trong đo lường và điều khiển mực nước," HUI, 2021.



Phạm Văn Minh & Lê Thị Thu Hà, "Xây dựng hệ thống nhà thông minh dựa trên giao thức I2C và vi điều khiển STM32," HUST, 2023.



STMicroelectronics, STM32F429ZI Datasheet, 2023.



PlatformIO Documentation, 2023.



🤝 Đóng góp

Chào mừng mọi đóng góp! Để tham gia:





Fork kho mã.



Tạo nhánh mới (git checkout -b ten-nhanh).



Thực hiện thay đổi và commit (git commit -m "Mô tả thay đổi").



Đẩy lên nhánh (git push origin ten-nhanh).



Mở Pull Request.

Vui lòng đảm bảo mã tuân theo phong cách của dự án và có tài liệu đầy đủ.

