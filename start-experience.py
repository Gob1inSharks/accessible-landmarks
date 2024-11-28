import pygame
import time
import os

import random
from paho.mqtt import client as mqtt_client

ACTIONS_NUM = 4

DELAY_TIME = 40 #miliseconds
DELAY_TIME = float(DELAY_TIME)/1000

BROKER = 'broker.emqx.io'
PORT = 1883
TOPIC = "/goblinsharksFRFR/accessible-landmarks/experience"
CLIENT_ID = f'aclandApp-{random.randint(0, 1000)}'

MUSIC_DIR = ["assets/music/lofi1.mp3", 
             "assets/music/lofi2.mp3", 
             "assets/music/lofi3.mp3", 
             "assets/music/lofi4.mp3"]

SOUND_EFFECTS_DIR = {"bell":"assets/sound-effects/bell.mp3", 
                     "notes":"assets/sound-effects/notes.mp3",
                     "wrong":"assets/sound-effects/wrong.mp3",
                     "wrongUlt":"assets/sound-effects/wrongUlt.mp3"}

STORIES_DIR = { "1":"assets/audio/Colo1.mp3",
                "2":"assets/audio/Colo2.mp3",      
                "3":"assets/audio/Colo3.mp3",      
                "4":"assets/audio/Colo4.mp3"
                }

pygame.init()
pygame.mixer.init()

class Music():
    def __init__(self, music_dir):

        self.queue = 0
        self.music = music_dir
        self.music_num = len(music_dir)

    def start(self):

        self.queue = 0

        pygame.mixer.music.load(self.music[self.queue])
        pygame.mixer.music.play()

    def next(self):

        pygame.mixer.music.stop()

        self.queue += 1
        if(self.queue == self.music_num):
            self.queue = 0

        pygame.mixer.music.load(self.music[self.queue])
        pygame.mixer.music.play()

    def set_volume(self, volume):
        pygame.mixer.music.set_volume(volume)

class SoundEffects():

    def __init__(self, sound_effects_dir):

        self.sounds = {
            "bell":pygame.mixer.Sound(sound_effects_dir["bell"]),
            "notes":pygame.mixer.Sound(sound_effects_dir["notes"]),
            "wrong":pygame.mixer.Sound(sound_effects_dir["wrong"]),
            "wrongUlt":pygame.mixer.Sound(sound_effects_dir["wrongUlt"])
        }

        self.lengths = {
            "bell":self.sounds["bell"].get_length(),
            "notes":self.sounds["notes"].get_length(),
            "wrong":self.sounds["wrong"].get_length(),
            "wrongUlt":self.sounds["wrongUlt"].get_length()
        }

    def playBell(self):
        self.sounds["bell"].play()

    def playNotes(self):
        self.sounds["notes"].play()

    def playWrong(self):
        self.sounds["wrong"].play()

    def playWrongUlt(self):
        self.sounds["wrongUlt"].play()

class Stories():

    def __init__(self, stories_dir):

        self.stories = {
            "1":pygame.mixer.Sound(stories_dir["1"]),
            "2":pygame.mixer.Sound(stories_dir["2"]),
            "3":pygame.mixer.Sound(stories_dir["3"]),
            "4":pygame.mixer.Sound(stories_dir["4"])}
        
        self.lengths = {
            "1":self.stories["1"].get_length(),
            "2":self.stories["2"].get_length(),
            "3":self.stories["3"].get_length(),
            "4":self.stories["4"].get_length()}

class Feedback():

    def __init__(self,music,soundEffects,stories):

        self.music = music
        self.sound = soundEffects
        self.stories = stories
        self.stories_num = len(stories.stories)
        self.queue = 0

    def playBell(self):
        
        self.music.set_volume(.2)
        self.sound.playBell()
        time.sleep(self.sound.lengths["bell"])
        self.music.set_volume(1)

    def playNotes(self):

        self.music.set_volume(.2)
        self.sound.playNotes()
        time.sleep(self.sound.lengths["notes"])
        self.music.set_volume(1)

    def playWrong(self):

        self.music.set_volume(.2)
        self.sound.playWrong()
        time.sleep(self.sound.lengths["wrong"])
        self.music.set_volume(1)

    def playWrongUlt(self):

        self.music.set_volume(.2)
        self.sound.playWrongUlt()
        time.sleep(self.sound.lengths["wrongUlt"])
        self.music.set_volume(1)

    def playNextStory(self):

        if(self.queue < self.stories_num):

            self.music.set_volume(.2)
            self.stories.stories[str(self.queue+1)].play()
            time.sleep(self.stories.lengths[str(self.queue+1)])
            self.music.set_volume(1)

            self.queue += 1

        else:
            pass

    def nothing(self):
        pass

def connect_mqtt():
    
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)

    client = mqtt_client.Client(CLIENT_ID)
    client.on_connect = on_connect
    client.connect(BROKER, PORT)
    return client

def clean_message(message):

    message = str(message)

    flag = False
    out = ""

    for i in range(len(message)):

        if(message[i] == "<"):
            flag = True
        elif(message[i] == ">"):
            flag = False
        elif(flag):
            out += message[i]

    if(out.isnumeric() and 0 < int(out) < ACTIONS_NUM+1):
        return int(out)
    else:
        return 0

if __name__ == "__main__":

    os.system("clear")

    print("Starting experience...")
    print("""
 ______________________________________
/ Mere nonexistence is a feeble excuse \\
| for declaring a thing unseeable. You |
| *can* see dragons. You just have to  |
| look in the right direction.         |
|                                      |
\ -- John Hasler                       /
 --------------------------------------
\                             .       .
 \                           / `.   .' " 
  \                  .---.  <    > <    >  .---.
   \                 |    \  \ - ~ ~ - /  /    |
         _____          ..-~             ~-..-~
        |     |   \~~~\.'                    `./~~~/
       ---------   \__/                        \__/
      .'  O    \     /               /       \  " 
     (_____,    `._.'               |         }  \/~~~/
      `----.          /       }     |        /    \__/
            `-.      |       /      |       /      `. ,~~|
                ~-.__|      /_ - ~ ^|      /- _      `..-'   
                     |     /        |     /     ~-.     `-. _  _  _
                     |_____|        |_____|         ~ - . _ _ _ _ _>

    """)

    music = Music(MUSIC_DIR)
    music.start()
    music.set_volume(1)

    sounds = SoundEffects(SOUND_EFFECTS_DIR)

    stories = Stories(STORIES_DIR)

    feedback = Feedback(music,sounds,stories)

    actions = {
        0: feedback.nothing,
        1: feedback.playNotes,
        2: feedback.playWrong,
        3: feedback.playBell,
        4: feedback.playNextStory
    }

    def subscribe(client):

        def on_message(client, userdata, msg):

            #for debugging
            #print(f"Received `{msg.payload.decode()}` from `{msg.topic}` topic")

            actions[clean_message(msg.payload.decode())]()

        client.subscribe(TOPIC)
        client.on_message = on_message

    client = connect_mqtt()
    subscribe(client)
    client.loop_start()

    while True:

        time.sleep(DELAY_TIME)

        if(pygame.mixer.music.get_busy()):
            continue
        else:
            music.next()
