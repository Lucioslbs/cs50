function checkAnswer(button, isCorrect) {
    const feedback = document.getElementById('mc-feedback');
    if (isCorrect) {
        button.classList.add('correct');
        feedback.textContent = "Correct!";
    } else {
        button.classList.add('incorrect');
        feedback.textContent = "Incorrect";
    }
}

function checkFreeResponse() {
    const input = document.getElementById('free-response');
    const feedback = document.getElementById('fr-feedback');
    const answer = input.value.trim();
    if (answer === "12") {
        input.classList.add('correct');
        feedback.textContent = "Correct!";
    } else {
        input.classList.add('incorrect');
        feedback.textContent = "Incorrect";
    }
}
