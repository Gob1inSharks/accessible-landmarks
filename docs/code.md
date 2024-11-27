# Arduino,  Internet of Things, & Code

Our current 3D Puzzle is a "pizza-ed" up Colosseum, on a board filled by several light sensors. Each piece is marked with a two shiny color stamps, Red, Green, or Blue, allowing each color sensor and Arduino to detect each pieces’ placement and align, giving audio feedback through a cell phone app using the MQTT Internet of Things protocol. 

## Color Sensing

We use standard tcs230 color sensors here to detect each piece. Two tcs230s are used to sense pieces in place, as this combination can A. reduce the possibility of inaccurate position sensing B.  sense the direction of each piece C. make the project much more scalable to more complex puzzles with more combinations of color markers. The color sensors are designed to be aligned in a way to correctly detect each piece in both direction and type, ultimately allowing better audio feedback with more input data from the sensors.

Our color sensors are a lacking to be more scalable though; the tcs230s sends Red, Green, and Blue light as output and takes in the amount of Red, Green, and Blue reflected back (see the code on the right). It’s efficient at detecting if a color is mainly Red, or Green, or Blue, yet not any other color like Purple which has almost equal amount of Red and Blue. This is a technical limitation, however it is enough for our current 3-piece design.

## I2C and IoT messaging

The tech has a more streamlined approach, where information flows from the color sensors themselves to the user’s device. We had plans to expand the puzzles to tens, maybe even more then twenty pieces, so we had one Mega control several tcs230 color sensors to be scalable. Using I2C connection, the Mega, the slave, sends which pieces it controls or not to the master, the R4 with Wifi, after a request. The message has a format of <integer> to avoid noise, for example if zero pieces are in place, the R4 receives: <0>. The R4 tallies up each piece in place, which ultimately sends the number of pieces in place to an MQTT server, in the same format of <integer>, which the phone application acquires using such protocol. 

This approach was designed to be efficient for Arduinos with tens of color sensors, with MQTT here for simplicity (also for the fact that we have previous experience with the MQTT protocol) 

## Application and Audio Feedback

Our application is unfortunately still very much in the prototyping phase. It’s a terminal application built on a  Linux 6.8.4 machine using Python 3.12 with a few libraries. Lacking on graphics, we mainly focused on how to create a better experience with audio feedback for the visually disabled. 

# Future Implementations

Time is an issue.