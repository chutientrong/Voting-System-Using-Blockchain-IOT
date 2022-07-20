# Voting-System-Using-Blockchain-IOT
 Voting System is built in Blockchain Network and IoT Device(ESP8266)

## Technical Used
- Blockchain
- IOT

## Framework and Language

- Frontend: PHP, MySql
- Backend: JavaScript, NodeJs, Express
- Device: C/C++, ResAPI, HTML,CSS,JS

## How to Use 
1. Frontend
- Dowload Xampp and push folder `Frontend-Management` to htdocs
- Start apache and mysql
- Open PHPMyAdmin and create database name `iotblockchain`
- Open new tab in your explore (GoogleChrome) and text `iotblockchain` with `localhost`

2. Backend
- Open folder `Backend` and do in `README`

3. IOT Device
- After begining, we need create new device in `Frontend Management`. Then we have device id
- Open file `blockchainiot` with ArduinoIDE in folder `ESP8266-IoT-Device`
- Replace `device_token` in `blockchainiot` by created `device_id` 
- Connect ESP8266/ESP32 to your PC/Laptop and upload source code
- In `Serial Monitor` you can see ip and port such as `192.168.1.1:2000`
- Then open new tab in explore and text your ip
- Voting (See video demo)


