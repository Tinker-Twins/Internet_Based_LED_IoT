# Internet Based LED IoT
The project uses 2 NodeMCUs and is divided into 2 sub-projects:

1. Publishing Data to the Server:

The analog data aquired from sensor (LDR) is first read, sampled and quantized into digital form and then published onto a server (Adafruit.io) using the first NodeMCU.

2. Subscribing Data from Server:

The data of LDR being published continuouslly is subscribed by the second NodeMCU and depend upon its values, an LED is switched ON or OFF.
