from cs50 import get_string


def count_letters_words_sentences(text):
    letters = 0
    words = 1
    sentences = 0

    for char in text:
        if char.isalpha():
            letters += 1
        elif char.isspace():
            words += 1
        elif char in ['.', '!', '?']:
            sentences += 1

    return letters, words, sentences


def calculate_index(letters, words, sentences):
    L = (letters / words) * 100
    S = (sentences / words) * 100
    return 0.0588 * L - 0.296 * S - 15.8


def main():
    text = get_string("Text: ")
    letters, words, sentences = count_letters_words_sentences(text)
    index = calculate_index(letters, words, sentences)

    print(f"Index: {index:.2f}")

    if index < 1:
        print("Less than Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")


if __name__ == "__main__":
    main()
