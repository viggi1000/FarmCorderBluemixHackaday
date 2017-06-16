# FarmCorder Bluemix
# [FarmCorder](https://hackaday.io/project/25155-farmcorder-crop-nutrition-deficiency-sensor) Bluemix application

Farming remains to be backbone of developing countries like India and Africa and it is the principal source of livelihood for majority of the population in the countries. Farmers 
however, use antiquated techniques which lead to overuse or under usage of fertiliser,water which leads to disastrous yields. Our solution to this problem is “FarmCorder” system.   
We propose a new simple and intuitive sensor based system which consists of base hand held module. The leaf nutrients are measured by leaf probe which works by multi-spectral spectroscopy. The soil moisture probe which works by capacitive moisture 
sensing. The data logging is performed by a low power micro-controller and data is sent to a remote server with GPS coordinates via a GSM module where the data is processed and  appropriate fertilizer advice is provided over IVRS.

### FarmCorder Device
<img width="772" alt="screenshot1" src="https://cdn.hackaday.io/images/1651391497246518585.jpg">


## Getting Started
FarmCorder was designed to be simple to develop and the components are modular through the use of the i2c bus and allows additional sensors for farm monitoring.
### Hardware Prerequisites
1. [Particle Photon/ Particle Electron (Wifi/GSM MCU)]: https://store.particle.io/
2. [Custom TSL2561 (I2C Light sensor IC) PCB]: https://oshpark.com/shared_projects/ZqXfrnV1
3. [HDC1000] (I2C Noncontact Temperature sensor): https://www.tindie.com/products/ftruzzi/hdc1000-tiny-temp--humidity-sensor-pcb-only/
4. [1000mAh LiPo battery]: https://www.sparkfun.com/products/13813
5. [5V Boost regulator]: https://www.pololu.com/product/798
6. [650nm LED]: http://uk.rs-online.com/web/p/visible-leds/6545818/
7. [940nm LED]: http://uk.rs-online.com/web/p/ir-leds/6997714/
8. [SSD1331 RGB OLED]: https://github.com/adafruit/Adafruit-SSD1331-OLED-Driver-Library-for-Arduino
9. [L80 GPS module MTK3339]: https://www.aliexpress.com/store/product/MTK3339-ultra-small-GPS-Module-with-Dual-Antenna-FGPMMOPA6C-PA6C/605000_531702544.html

Connections: 
Connect SDA, SCL of TSL2561 to D0,D1 respectively and Vin,Gnd to 3.3V and Gnd in the Particle Photon. 
Connect the Red LED pin to D3. 
Connect the IR LED pin to D4.
Connect the push button to D2 along with a 10k resistor to Gnd.
Connect the 3.3V, Gnd to the GPS module and the RX pin of GPS to TX of the dev board. Connect the TX pin of GPS to the RX of the GPS.


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



## Built With

* [Watson IoT](https://www.ibm.com/internet-of-things/platform/watson-iot-platform/) - IoT backend
* [Node-Red](https://nodered.org/) - NodeJS based IoT tool
* [Twilio](https://www.twilio.com/) - IVRS call service
* [Particle](https://www.particle.io/) - Wifi MCU

## Future Concept 
I aim to move towards a low powered display (Eink or Shape memory) to enable visiblity in high sunlight. The data from the device is pushed to the Watson IoT platform along with the GPS data. Using the time stamp and GPS fencing the device can be shared by multiple farmers. A Machine Learning based system will be used to analyze the Chlorophyll Content Index by comparing with a database from a crop research database. Then using the weather data in the locality, A fertilizer application suggestion is generated and conveyed to the farmer using the Twilio IVRS call to the farmer.
Future HW design: 

<img width="564" alt="capture" src="https://cdn.hackaday.io/images/8892811497242057966.jpg">




## Authors

* **Vignesh Ravichandran** - [viggi1000](https://github.com/viggi1000)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* IBM & Node-Red team for providing such amazing tools!
* Dad for funding my offshoot ideas as always.


