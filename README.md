<h1>Purpose/Intention</h1>

This float functions autonomously to collect data for multiple vertical profiles. A vertical profile is a collection of data in a water column showing a correlation between a certain quantity compared to height/altitude, and in this case, that quantity is temperature. The float is meant to independently ascend and descend 2.5 meters two separate times while collecting temperature readings onto an SD card every 5 seconds that will be collected after its mission.  It is also programmed to hover between 2.5 meters and 3 meters for 45 seconds, or 10 readings, before ascending. 

<h1>Buoyancy Engine</h1>

You might notice that the float has an inflatable water bottle sticking out of the top of the PVC cap; this is because it is part of the buoyancy engine. Buoyancy is defined in physics as the upward force that opposes the weight of a partially or fully submerged object, and it is represented by the equation F = pVg. The volume of the object (V), the exterior water pressure (p), and the gravitational force (9.8m/s represented by g) are all equal to the buoyant force, which, when equal to the mass, means that the object is neutrally buoyant. 

In order to make an object move vertically in the water without the use of motors, one of two things must be able to be altered: The overall mass or the amount of water displaced by the float. This design utilizes the latter. 

In order to increase the volume and displace more water, the syringe, controlled by a linear actuator, pushes and pulls air in and out of the exterior pouch. When designing this engine, the most challenging part was figuring out the exact point where the float would be neutrally buoyant. When the pouch is inflated more than this point, it causes the float to ascend because the buoyant force is greater than the weight, and when the air is pulled all the way into the syringe, the float displaces the minimum amount of fluid, causing it to descend. 

<h1>Coding the Linear Actuator</h1>

When deciding how I would approach the buoyancy engine, I knew that using a linear actuator would require more than just the Arduino. Since there are more variables than just on and off that the pins on an Arduino control, we needed to use either relays or a motor driver. 

The main difference between them was that the relays control the actuator by using simple high and low values. Meaning that the relays allow you to make it either open or close; however, there is no way to control the speed at which it works. The motor driver, while being slightly more complicated to develop, allows you to manipulate both. I chose to utilize a motor driver because, even though speed isn't the most important factor, it allowed me to have that extra variable to work with when troubleshooting the buoyancy. 

<h1>Materials and Hardware</h1>

There is a variety of parts that come from a variety of sources on this float. For starters, the sensor and converter for the sensor are both from the company Bluerobotics, while the syringe, pouch, linear actuator, motor driver, and converters are all sourced from Amazon. Even though it may not be the most fancy to look at, the pouch was made out of a water bottle, as water bottles are designed to keep water in and out, and it would be the most reliable material when working underwater. 


<h1>What are Floats like this used for in the real world? </h1>

Autonomous floats such as this one are often used in aquatic research to help scientists track data such as pH, water salinity, oxygen content, and so much more. In addition, they can be used to track ocean currents. All of these factors are crucial in understanding our Earth's lakes, rivers, and oceans. 

By gathering data using these floats, scientists can use it to more accurately predict weather patterns, which can help us to predict extreme weather events and aid in the fight against climate change. 

This float functions very similarly to an Argo float. Argo is a program that has deployed nearly 4000 floats around the world to measure these sorts of conditions. These floats are what provide data to scientists about how global warming is affecting the oceans, and to the Weather Service to help them make forecasts.

<h1>Build Process</h1>

The process for designing this float started back in December. In the beginning, it took a lot of research and rough ideas before I settled on a design. Since there are so many ways you can create a buoyancy engine, I played around with a couple using very rough builds before narrowing it down to two different designs. While both utilized syringes, they applied them in different ways. The first design used the syringe to pull water into a compartment to increase the mass of the float. The second design, and the one I ultimately ended up going with, used an exterior “swim bladder” that could be used to displace more water. 

When putting the first design into motion, I began with the mechanical portion of the build. I prioritized the electrical components, knowing that they would need the most troubleshooting in the end. One of the most challenging aspects of the build was figuring out how to get all of the components to run efficiently off one Arduino. In addition, we utilized a wireless Arduino, so we had to make sure that, when at the surface, it would not lose connection with the computer. 

When developing the code, I pulled certain parts from publicly available code from C++ Libraries, as well as writing the rest of the code with the help of a mentor. The parts reused from libraries mostly included the code to run the sensor, and the code to collect data to the SD card. 

<h1>How does the Data Collection and Retrieval work?</h1>

Since this float is fully autonomous and is not connected to the surface via a tether or any wires, it communicates with my computer via a wifi connection. However, since it travels underneath the surface of the water, and since wifi cannot travel 

Through water, it will lose that connection as soon as it is deployed. 
The way I circumvented this issue was by having an SD card wired to the Arduino, which collects data readings every 5 seconds as it travels. The data feeds into the SD card during its profile, and once it reaches the surface, it is able to transmit all the data it has collected to the computer's dashboard, where we can then graph it to better show the relationship between temperature, depth, and water pressure. 

Inside the tube, the Arduino is placed at the top to ensure that it does not lose connection as we are deploying it. The rest of the electrical components are stored at the bottom of the tube so that the weights of the batteries, motor driver, and converters do not affect the weight distribution. 

