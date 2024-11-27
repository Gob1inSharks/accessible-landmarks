# Acessible Landmarks 🏛️⚔️

***This project is still IN PROGRESS; no guarantees for usability***

This is the repository for Acessible Landmarks: 3D puzzles of landmarks made for the visually disabled. Our goals are to:

1. Adapt existing puzzles for the visually disabled.

2. Enhance the travel and learning experiences of the visually blind with an empathsis on history and architecture. 

3. Integrate Internet of Things and other technologies to improve the overall product in a meaningful way.

![project default image]()

Our current 3D Puzzle is a "pizza-ed" up Colosseum, on a board filled by several light sensors. Each piece is marked with a two color stamps, Red, Green, or Blue, allowing each color sensor and Arduino to detect each pieces’ placement and align, giving audio feedback through a cell phone app using the MQTT Internet of Things protocol.

## Current Issues

### PROJECT BROKEN/DOES NOT WORK 😱😔😭

There is not enough power supply for each arduino, with a lack of space for more supply.

### STLs

The stls are poorly designed and you WILL need to drill holes.

### Code

To do: a few bugs with code. No clue what's the problem.

## Getting Started

![inside image 1]()

![inside image 2]()
*Top-Down Image*
![outside image 1](https://github.com/Gob1inSharks/accessible-landmarks/blob/main/assets/img/colo.jpg)
*Pretty*

This is mainly an Arduino and 3D Printing project, where all of the models and code are available in this repository, or [here](). You will need the following materials:

|Name            |Type            |Usage          |Quantity               |
|----------------|----------------|---------------|-------------------|
|Arduino Mega    |Chip           |Color Sensor Control/Data|2|
|Arduino R4 Wifi |Chip           |Control and IoT|1|
|Bread Board|Board |Power, Connection, and Oragnization|2|
|Power Delivery|Power|Power|1|
|Puzzle Board Top|Board|Holding Pieces and Detection|1|
|Puzzle Board Top|Board|Holding Materials and Detection|1|
|**MtM** Wires|Wire|Arduino Power and I2C|12|
|**MtF** Wires|Wire|Sensor Power and Input/Output|42|
|TCS230 Color Senors|Sensor|Board Piece Detection| 6|
|4cm*3cm Rectangular Flat **Red** Color Markers|Marker|Board Piece Detection|2|
|4cm*3cm Rectangular Flat **Green** Color Markers|Marker|Board Piece Detection|2|
|4cm*3cm Rectangular Flat **Blue** Color Markers|Marker|Board Piece Detection|2|
|5V 48 Watt Cable|Cable|Power|1|

### 3D Printing

We have all the [**stl** files needed here](https://github.com/Gob1inSharks/accessible-landmarks/tree/main/stl), where you can download and/or modify to your own. The instructions for building the project is shown below (note that most printers are 250mm x 250mm x 250mm, so you'll have to cut them down the middle before printing):

### Arduino and Circuitry

### Code and IoT

We built and ran this program on a Linux 6.8.4 machine with Python 3.12.3, not tested at all with other OSs.

Get started with:

```
# clone the repo
$ git clone https://github.com/Gob1inSharks/accessible-landmarks

# change the working directory to this
$ cd accessible-landmarks

# install the requirements
$ python3 -m pip install -r python-requirements.txt

# run the program
$ python3 start-experience.py
```