# FanControl
I wanted to make my fan controllable through Google Assisant so I came up with this Arduino project to make my normal fan into a smart Internet controlled fan.

## The Process
I originally thought that I could maybe replicate the commands that the remote sends to the fans. However I realized this method would be complicated because fans and their remotes use RF to communicate instead of IR and I didn't have any RF receivers or transmitters lying around to record and send signals. This led me to use an approach that involved the actual fan remote.

Taking apart the fan remote and getting to the PCB I saw that the bottom of the buttons on the remote are covered with a conductive rubber like material which bridges two closely placed contacts for each button. So in order to simulate a button push I would need to bridge the two contacts for the button.

![Image of a hunter fan remote pcb](https://content.instructables.com/F12/3XQ6/I3BH5I4Y/F123XQ6I3BH5I4Y.jpg?auto=webp&frame=1&width=852&height=1024&fit=bounds&md=cbeea60fbb726c246b09d0b9ca62e6e1)

Above image taken from https://www.instructables.com/Repairing-a-Hunter-Fan-remote-control/

![33515740-c760-4d50-a000-ec539f5cf951](https://github.com/BrianJ-4/FanControl/assets/84641264/79313b5c-986f-4b6d-9dde-b7c5c5352bc6)

Relays were perfect for this situation. I could wire one contact of the button to the "common" terminal on the relay and wire the other contact to the "normally open" terminal on the relay. So if the relay is triggered, the two wires can make contact and simulate a button press on the fan remote.

After some soldering and wiring, I had this ( Ignore the poor soldering job. I did this when I just started to learn soldering :) )
![46e3de23-8ec9-4e95-8430-e999cd5f5771](https://github.com/BrianJ-4/FanControl/assets/84641264/eadec8f0-cb1a-4d5d-92bb-7affa18bf665)

Connecting this to a Arduino Uno and triggering the relays worked perfectly. So the next step was to give it the ability to be controlled through the internet.

In order to do this I switched from a Arduino Uno to a NodeMCU ESP8266 board. The onboard ESP8266 wifi microchip allowed me to control the board through the internet. But, I needed a way to bridge the microcontroller and Google Assistant. And after some research IFTT seemed like the best option. IFTT allowed for me to link custom Google Assistant commands with HTTP Requests that would contain a command word used to control the fan. In order to enable the microcontroller to get these requests I used a service called Remoteme. Remoteme hosted a server that I could send HTTP requests to in order to change the value of variables stored on the server. And then using the Remoteme Arduino library I could have my microcontroller listen for changes in the variables in the server and perform the appropriate actions.

So in order to combine all this, I created a IFTT applet for controlling fan speed, one for controlling light status, and one for turning the fan off. Each applet has a custom Google Assistant command. 
For Example, when controlling fan speed, the assistant command is, "Set fan speed to ___". The blank being the keyword, high, medium, or low. This value is then passed to Remoteme where the speed variable is updated, and then the microcontroller will pick up that a change has happened in the variable and perform the appropriate action.

## Tools/Services/Hardware Used
* 8 Channel 5V Relay - To trigger button presses
* Soldering Iron - For soldering wires to the remote PCB
* IFTT - For bridging Google Assitant with custom HTTP Requests
* Remoteme - For receiving HTTP Requests and updating variables based on the value from the requests
* NodeMCU ESP8266 - For controlling the relays based on variable values in Remoteme

**Note: Project was completed in June 2021**
