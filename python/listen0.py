 import speech_recognition as sr

recognizer = sr.Recognizer()

try:
    with sr.Microphone() as source:
        print("Say something:")
        audio = recognizer.listen(source)

    words = recognizer.recognize_google(audio)

    if "hello" in words:
        print("Hello to you too!")
    elif "how are you" in words:
        print("I am well, thanks")
    elif "goodbye" in words:
        print("Goodbye to you too!")
    else:
        print("Huh?")

except sr.RequestError:
    print("Could not request results; check your internet connection.")
except sr.UnknownValueError:
    print("Sorry, I could not understand what you said.")
