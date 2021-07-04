# Coal Mine Monitoring System and Coal Miner's Smart Helmet

### For the most accurate in depth description of the project, please refer to the "FTRI.pptx" file uploaded in the repository.

<i>Refer to the prototype image for an overall idea.</i>

We submitted this project for FTRI as an award application in September, 2019. The results were declared in November, 2019 and we were declared winners. We were felicitated with the award in December, 2019.
This project was also presented at Engineer's Day Expo, 2019, VIT Vellore.

This is a project that includes 3 aspects of a Coal Mine : 

- External for security
- Internal which the supervisor monitors
- Smart Helmet which assists the miner


## EXTERNAL


"LCD_Display_Final.ino" - Just a screen display that welcomes the visitor to the coal mine on the LCD Display.

"Passcode.ino" - A passcode without which you can not access the Coal Mine system.

"Final_Thingspeak.ino" - A demonstration of 3 sensor values, Distance, Humidity and Temperature being sent over the cloud to Thingspeak.
Similar demonstration for the sensor values obtained in the Internal interface makes it possible for the supervisor to supervise the conditions of the system from the comfort of their monitor screen.

A PiCamera is also installed to oversee what's happening inside the coal mine.


## INTERNAL

Each of these parameters are accompanied by a threshold value and a corresponding buzzer/ LED going off in case the threshold is breached.

"Coal_Mine_Internal_Final.ino" features the internal system of the coal mine that the supervisor may monitor. The parameters taken into account are : 

DHT11 Sensor
- Temperature
- Humidity

Keeps a check on the temperature and humidity levels inside the coal mine.
Gives us an idea about the working conditions and if they're safe for the worker or not.

Ultrasonic Sensor
- Checking the distance

Detects distance inside the coal mine from different workers.
Using visualization methods, we can track the relevant activity areas inside the coal mine and draw a heat map.

Water Level Depth Sensor
- Checking for water level inside the coal mine

Detects any potential flood that might occur.

Shock Sensor
- Checking for tremors

Keeps a check on any detected tremors inside the coal mine.

PIR Sensor
- Checking for motion

Keeps a check for any detected motion in restricted areas.

Flame Sensor
- Checking for fire

Keeps a check on any outbreak of fire inside the coal mine.

MQ2 Sensor
- Carbon Monoxide content in the air ( For air toxicity ) 

Checks whether the air inside the coal mine is safe for working conditions or not.


## SMART HELMET

- Heartbeat Sensor, to monitor the vitals
- Avoid Sensor, which gives light whenever there is no object around it. In case of a mishap happens, such as rocks falling onto the miner, and the miner struggling to find path to move out of, this is combined with the buzzer and the LED 
- Big Sound Sensor, so that whenever a loud thud comes, the reasons for which could be anything, including something very dangerous, so this will give an alert for that
- Light Blocking Sensor, which gives a beep whenever the light is gone, can help the miner find the path through which they can force themselves out. If it gets annoying, it can be stopped simply by turning the smart helmet off.
- Flame Sensor

A designated supervisor can be assigned to keep track of any alerts sent related to vitals or other conditions specific to the coal miners.
