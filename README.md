# 🏠 Hệ thống Nhà Thông Minh Điều khiển Máy Bơm Nước và Thiết bị Bếp


## 🎉 Giới thiệu
Dự án này được thực hiện trong môn Lập trình Nhúng tại Học viện Công nghệ Bưu chính Viễn thông - Cơ sở TP.HCM. Hệ thống nhà thông minh điều khiển máy bơm nước, đèn bếp và quạt thông gió, tích hợp cảm biến và giao diện người dùng thân thiện, mang lại sự tiện nghi và hiệu quả cho không gian bếp hiện đại.
Hệ thống sử dụng vi điều khiển NUCLEO-STM32F429ZI, cảm biến siêu âm, cảm biến chuyển động, cảm biến ánh sáng, và giao diện LCD để hiển thị trạng thái, kết hợp lập trình nhúng để đảm bảo hoạt động ổn định và thông minh.
Thông tin dự án:

Sinh viên: Trần Minh Thương  
Mã số sinh viên: N21DCVT101  
Lớp: D21CQVTHI01-N  
Giảng viên: ThS. Phạm Quốc Hợp  
Ngày: 10/05/2025



## 🎯 Mục tiêu Dự án

Tự động hóa 🤖: Giám sát và điều khiển các thiết bị (máy bơm, đèn, quạt) dựa trên cảm biến và lịch thời gian.  
Linh hoạt 🔄: Hỗ trợ chế độ thủ công và tự động, cùng với cài đặt lịch bật/tắt.  
Trải nghiệm người dùng 🖥️: Giao diện trực quan qua LCD 20x4 và bàn phím 4x4, bảo mật bằng mật khẩu.  
Hiệu quả ⚡: Đảm bảo vận hành đáng tin cậy và tiết kiệm năng lượng.


##📋 Tính năng Chính

Chế độ Thủ công 🖐️:  
Bật/tắt đèn, quạt, máy bơm qua nút nhấn hoặc bàn phím (phím A/B/C).


Chế độ Tự động 🤖:  
Máy bơm hoạt động khi mực nước thấp (HC-SR04) và dừng khi đủ.  
Đèn bếp bật khi có chuyển động (PIR AM312) và ánh sáng yếu (LDR NVZ1).  
Quạt luôn bật trong chế độ tự động.


Cài đặt Thời gian ⏰:  
Đặt lịch bật/tắt cho từng thiết bị (phím 1/2/3) và giờ hiện tại (phím 4).


Bảo mật 🔒:  
Mật khẩu:  
1111: Thủ công  
2222: Tự động  
3333: Cài đặt thời gian  
8888: Mở khóa  
9999: Khóa hệ thống




Giao diện 🖥️:  
LCD 20x4 hiển thị menu, trạng thái, và thông báo lỗi.


Phản hồi 🚨:  
LED (xanh/đỏ) và còi báo trạng thái hoặc cảnh báo.

##🛠️ Thành phần Phần cứng

Linh kiện
Mô tả



NUCLEO-STM32F429ZI
Vi điều khiển ARM Cortex-M4, 180 MHz, 2 MB Flash, 256 KB SRAM.


HC-SR04
Cảm biến siêu âm đo mực nước (khoảng cách 2–450 cm, độ chính xác 3 mm).


PIR AM312
Cảm biến chuyển động phát hiện người (khoảng cách 3–5 m).


LDR NVZ1
Cảm biến ánh sáng đo cường độ ánh sáng môi trường.


Bàn phím 4x4
16 phím ma trận để nhập liệu (số, A–D, *, #).


LCD 20x4 (HD44780)
Hiển thị trạng thái và menu (giao tiếp 4-bit hoặc I2C).


Relay 5V
Điều khiển thiết bị công suất cao (220V/10A) như máy bơm, quạt.


LED & Còi
LED báo trạng thái (xanh/đỏ) và còi cảnh báo lỗi hoặc thao tác.


Hình ảnh Linh kiện



HC-SR04
PIR AM312
LDR NVZ1
LCD 20x4









Chú thích: Hình ảnh linh kiện được sử dụng từ nguồn công cộng để minh họa. Đặt hình ảnh thực tế trong thư mục media/ nếu có.
Kết nối Chân

HC-SR04: TRIG (PA6), ECHO (PA7)  
PIR AM312: OUT (PA3)  
LDR NVZ1: DO (PG9)  
Bàn phím 4x4: Hàng (PB3, PB5, PC7, PA15), Cột (PB12, PB13, PB15, PC6)  
Nút nhấn: Manual (PE9), Auto (PE11), Setting (PF14), Relay ON (PE13), Relay OFF (PF15), LED (PF13)  
Relay: Máy bơm (PF2), Quạt (PE6)  
LED: Trạng thái (PG14), LED1 (PB6, xanh), LED2 (PB2, đỏ), LED3 (PD15, xanh), LED4 (PF12, đỏ)  
Còi: PE10  
LCD: Giao tiếp 4-bit (GPIO) hoặc I2C qua PCF8574 (SDA/SCL)


##📊 Kiến trúc Hệ thống
Hệ thống sử dụng vi điều khiển STM32F429ZI làm trung tâm, xử lý tín hiệu từ cảm biến, nút nhấn, bàn phím, và điều khiển thiết bị đầu ra (relay, LED, còi). Sơ đồ khối dưới đây minh họa cấu trúc hệ thống:

Giao thức Truyền thông

GPIO 📡: Điều khiển nút nhấn, LED, relay, cảm biến PIR, LDR.  
Matrix Keypad Scanning ⌨️: Quét bàn phím 4x4 qua 8 chân GPIO.  
HC-SR04 Timing ⏱️: Sử dụng timer và GPIO để đo xung TRIG/ECHO.  
LCD 4-bit Parallel 🖥️: Điều khiển LCD bằng 7 chân GPIO (RS, RW, E, D4–D7).  
I2C (Tùy chọn) 🔌: Giao tiếp LCD qua PCF8574 để tiết kiệm chân.  
Ngắt (Interrupt) ⚡: Xử lý nút nhấn và tín hiệu ECHO cho phản hồi tức thời.


##💻 Chi tiết Phần mềm
Môi trường Phát triển

IDE: Visual Studio Code + PlatformIO.  
Khung công tác: Arduino cho STM32.  
Ngôn ngữ: C/C++.  
Thư viện:  
LiquidCrystal_I2C cho LCD.  
STM32 HAL/LL cho GPIO, timer, ngắt.



Kiến trúc Phần mềm

Finite State Machine (FSM) 🧠: Quản lý 3 chế độ chính (Thủ công, Tự động, Cài đặt thời gian).  
Interrupt-Driven ⚡: Xử lý nút nhấn và cảm biến theo thời gian thực.  
Module hóa 🧩: Các module display, keypad, sensors, actuators, modes, security, time_management, utils.  
Quản lý Thời gian ⏲️: Soft-RTC dùng millis() cho lịch và micros() cho HC-SR04.  
Chống Nhiễu (Debouncing) 🔧: Ổn định tín hiệu từ nút nhấn và bàn phím.

## Cấu trúc Thư mục
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


## 🚀 Hướng dẫn Cài đặt và Sử dụng
Yêu cầu

Phần cứng:  
NUCLEO-STM32F429ZI, HC-SR04, PIR AM312, LDR NVZ1, bàn phím 4x4, LCD 20x4, relay, LED, còi, nguồn 5V/12V.


Phần mềm:  
Visual Studio Code (tải về).  
PlatformIO (hướng dẫn cài).  
Driver ST-LINK (tải về).



Các bước Cài đặt

Sao chép Kho mã 📥:  
git clone https://github.com/MinhThuongTMT/Full_Code-Project-LTN.git
cd Full_Code-Project-LTN


Mở trong VS Code 💻:  

Mở thư mục dự án trong VS Code.  
PlatformIO tự động nhận diện file platformio.ini.


Kết nối Phần cứng 🔌:  

Nối các linh kiện với NUCLEO-F429ZI theo sơ đồ chân.  
Cấp nguồn 5V cho vi điều khiển/cảm biến và 12V cho relay.


Biên dịch và Nạp mã ⚙️:  

Trong VS Code, mở bảng PlatformIO.  
Nhấn Build để biên dịch.  
Kết nối NUCLEO qua USB và nhấn Upload để nạp mã.


Kiểm tra Hệ thống 🧪:  

Bật nguồn; LCD hiển thị màn hình chính ("PTIT", "TRAN MINH THUONG").  
Thử nhấn nút hoặc bàn phím để điều khiển.



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

📜 Giấy phép
Dự án được cấp phép theo Giấy phép MIT.
