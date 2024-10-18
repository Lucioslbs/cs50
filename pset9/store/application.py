from cs50 import SQL
from flask import Flask, redirect, render_template, request, session
from flask_session import Session

# Configure app
app = Flask(__name__)

# Connect to database
db = SQL("sqlite:///store.db")

# Configure sessions
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

@app.route("/")
def index():
    books = db.execute("SELECT * FROM books")
    return render_template("books.html", books=books)

@app.route("/cart", methods=["GET", "POST"])
def cart():

    # Ensure cart exists
    if "cart" not in session:
        session["cart"] = []

    # POST
    if request.method == "POST":
        id = request.form.get("id")
        if id:
            session["cart"].append(id)
        return redirect("/cart")

    # GET
    if session["cart"]:
        # Prepare placeholders for SQL query
        placeholders = ', '.join(['?'] * len(session["cart"]))
        query = f"SELECT * FROM books WHERE id IN ({placeholders})"
        books = db.execute(query, *session["cart"])
    else:
        books = []

    return render_template("cart.html", books=books)

if __name__ == "__main__":
    app.run(debug=True)
