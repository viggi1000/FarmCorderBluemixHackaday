# FarmCorder Bluemix
# [FarmCorder](https://hackaday.io/project/25155-farmcorder-crop-nutrition-deficiency-sensor) Bluemix application

Farming remains to be backbone of developing countries like India and Africa and it is the principal source of livelihood for majority of the population in the countries. Farmers 
however, use antiquated techniques which lead to overuse or under usage of fertiliser,water which leads to disastrous yields. Our solution to this problem is “FarmCorder” system.   
We propose a new simple and intuitive sensor based system which consists of base hand held module. The leaf nutrients are measured by leaf probe which works by multi-spectral spectroscopy. The soil moisture probe which works by capacitive moisture 
sensing. The data logging is performed by a low power micro-controller and data is sent to a remote server with GPS coordinates via a GSM module where the data is processed and  appropriate fertilizer advice is provided over IVRS.

### Raksh Device
<img width="772" alt="screenshot1" src="https://cdn.hackaday.io/images/2386621496298768395.jpg">


## Getting Started
FarmCorder was designed to be simple to develop and the components are modular through the use of the i2c bus and allows additional sensors for farm monitoring.
### Hardware Prerequisites

```
	1. Particle Photon/ Particle Electron (Wifi/GSM MCU)
	2. TSL2561 (I2C Light sensor IC)
	3. HDC1000 (I2C Noncontact Temperature sensor)
	4. 1000mAh LiPo battery
	5. 5V Boost regulator
	6. 650nm LED
	7. [940nm LED] 
	8. [SSD1331 RGB OLED]: https://github.com/adafruit/Adafruit-SSD1331-OLED-Driver-Library-for-Arduino
```
Connections: 
Connect SDA, SCL of MAX30100&MLX90614 to D0,D1 respectively and Vin,Gnd to 3.3V and Gnd in the Particle Photon.


### Software Prerequisites

```
	1. IBM Bluemix
	2. Create a Internet of Things Platform Starter boilerplate app on Bluemix
	3. Add a custom device to the Watson IoT platform using "Add Device"
	4. Note the API Keys and other credentials as soon the Device is added
	5. Add the firmware to Particle Photon Cloud IDE or Particle Desktop and replace relavent details 
	6. Import the package.JSON file into Node-Red to create the application
	7. Generate API keys in the Apps section of the Watson IoT platform and edit the Node-Red device input
```
Visualize the data on the Node-Red dashboard.

### Node-Red Application
The Node-Red application is used to split various sensor values from JSON format and display using charts and dials. Alerts are also configurable and currently email is used to convey patient alerts but in future iterations a phone alarm might be triggered.

<img width="504" alt="noderedflow" src="https://cloud.githubusercontent.com/assets/1295467/25814454/2d770314-343b-11e7-9e5b-fb60995f7756.PNG">


## Built With

* [Watson IoT](https://www.ibm.com/internet-of-things/platform/watson-iot-platform/) - IoT backend
* [Node-Red](https://nodered.org/) - NodeJS based IoT tool
* [IBM Bluemix](https://www.ibm.com/cloud-computing/bluemix/) - Cloud platform service
* [Particle](https://www.particle.io/) - Wifi MCU

## Future Concept 
I aim to move towards a BLE based sensor system to reduce size and power consumption. Such a system would use an MQTT broker in the Mobile or a Raspberry Pi W to send data to Bluemix.

Future HW design: 

<img width="564" alt="capture" src="https://cloud.githubusercontent.com/assets/1295467/25815011/1a796732-343d-11e7-8566-5c762c508fb3.PNG">


Future app design:

![picture3](https://cloud.githubusercontent.com/assets/1295467/25814872/87266db8-343c-11e7-849b-642ce651c501.png)


## Authors

* **Vignesh Ravichandran** - [viggi1000](https://github.com/viggi1000)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Thanks to [oxullo](https://github.com/oxullo/Arduino-MAX30100) for the amazing MAX30100 lib
* IBM & Node-Red team for providing such amazing tools!
* Dad for funding my offshoot ideas as always.


