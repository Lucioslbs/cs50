import os
from cs50 import SQL
from flask import Flask, render_template, request
from flask_mail import Mail, Message

app = Flask(__name__)

# Configurações de email
app.config["MAIL_DEFAULT_SENDER"] = os.getenv("MAIL_DEFAULT_SENDER")
app.config["MAIL_PASSWORD"] = os.getenv("MAIL_PASSWORD")
app.config["MAIL_PORT"] = 587
app.config["MAIL_SERVER"] = "smtp.gmail.com"
app.config["MAIL_USE_TLS"] = True  # Corrigido de TSL para TLS
app.config["MAIL_USERNAME"] = os.getenv("MAIL_USERNAME")
mail = Mail(app)

# Conexão com o banco de dados
db = SQL("sqlite:///froshims.db")

SPORTS = [
    "Dodgeball",
    "Flag Football",
    "Soccer",
    "Volleyball",
    "Ultimate Frisbee"
]

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)

@app.route("/register", methods=["POST"])
def register():
    email = request.form.get("email")
    sport = request.form.get("sport")

    # Verificação de entrada válida
    if not email or sport not in SPORTS:
        return render_template("error.html", message="Missing email or invalid sport")

    # Inserir dados no banco de dados
    try:
        db.execute("INSERT INTO registrants (email, sport) VALUES(?, ?)", email, sport)
    except Exception as e:
        return render_template("error.html", message=f"Database error: {e}")

    # Enviar email de confirmação
    try:
        message = Message("You are registered!", recipients=[email])
        message.body = f"Hello, you have been successfully registered for {sport}."
        mail.send(message)
    except Exception as e:
        return render_template("error.html", message=f"Email sending error: {e}")

    registrants = db.execute("SELECT * FROM registrants")
    return render_template("registrants.html", email=email, sport=sport, registrants=registrants)

if __name__ == "__main__":
    app.run(debug=True)
