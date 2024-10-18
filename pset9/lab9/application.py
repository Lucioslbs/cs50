import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # Extrair os dados do formulário POST
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        # Inserir a entrada do usuário no banco de dados
        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)

        # Redirecionar de volta para a página inicial
        return redirect("/")
    else:
        # Consultar o banco de dados para recuperar as entradas existentes
        entries = db.execute("SELECT * FROM birthdays")

        # Exibir as entradas no template "index.html"
        return render_template("index.html", entries=entries)
