import speech_recognition as sr
import serial
import time
import pyttsx3  # Import text-to-speech library

# Initialize TTS engine
engine = pyttsx3.init()

def speak(text):  
    engine.say(text)
    engine.runAndWait()

# Set up serial communication with Arduino
try:
    arduino = serial.Serial("COM6", 9600, timeout=1)  # Change COM port as needed
    time.sleep(2)  # Wait for the connection
except serial.SerialException:
    print("Error: Could not open serial port. Check the Arduino connection.")
    arduino = None

# Function to recognize speech
def recognize_speech():
    recognizer = sr.Recognizer()
    mic = sr.Microphone()

    with mic as source:
        print("🔘 Say 'Hey Assistant' to activate...")
        speak("Say 'Hey Assistant' to activate")
        recognizer.adjust_for_ambient_noise(source)
        try:
            audio = recognizer.listen(source, timeout=10)
            text = recognizer.recognize_google(audio).lower()
            print("🎙️ Heard:", text)
            return text
        except sr.UnknownValueError:
            print("❌ Could not understand audio")
            speak("Could not understand audio")
            return ""
        except sr.RequestError:
            print("❌ Speech recognition service is unavailable")
            speak("Speech recognition service is unavailable")
            return ""

# Function to process commands
def process_command():
    while True:
        if "hey assistant" in recognize_speech():
            print("✅ Activated! Listening for command...")
            speak("Activated! Listening for command")
            command_text = recognize_speech()

            if "turn on light" in command_text:
                print("💡 Turning ON Light")
                speak("Turning on light")
                if arduino:
                    arduino.write(b"LIGHT_ON\n")

            elif "turn off light" in command_text:
                print("💡 Turning OFF Light")
                speak("Turning off light")
                if arduino:
                    arduino.write(b"LIGHT_OFF\n")

            elif "blink" in command_text:
                print("💡 Blinking Light for 5 seconds")
                speak("Blinking light for 5 seconds")
                if arduino:
                    arduino.write(b"BLINK\n")

            elif "fan on" in command_text:
                print("🌀 Turning ON Fan")
                speak("Turning on fan")
                if arduino:
                    arduino.write(b"FAN_ON\n")

            elif "fan off" in command_text:
                print("🛑 Turning OFF Fan")
                speak("Turning off fan")
                if arduino:
                    arduino.write(b"FAN_OFF\n")

            else:
                print("🤖 Command not recognized.")
                speak("Command not recognized")

# Run the voice assistant
process_command()
