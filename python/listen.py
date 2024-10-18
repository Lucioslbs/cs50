# Inteligencia artificial humana

import speech_recognition

words = input("Saying something: ").lower()

if "hello" in words:
    print("hello to you too!")
elif "how are you" in words:
    print("I am well, thanks")
elif "goodbye" in words:
    print("Goodbye to you too!")
else:
    print("Huh?")
