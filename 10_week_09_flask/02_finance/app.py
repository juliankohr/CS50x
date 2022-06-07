import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime, timezone, timedelta

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    rows = db.execute("SELECT * FROM users")

    if len(rows) == 0:
        return redirect("/register")

    this_positions = db.execute("SELECT DISTINCT symbol FROM id?", session["user_id"])
    total_positions = 0

    for i in range(len(this_positions)):
        this_symbol = db.execute("SELECT DISTINCT symbol FROM id? GROUP BY symbol", session["user_id"])[i]["symbol"]
        this_shares = db.execute("SELECT DISTINCT symbol, SUM(shares) FROM id? GROUP BY symbol",
                                 session["user_id"])[i]["SUM(shares)"]
        current_price = lookup(this_symbol)["price"]
        current_total = current_price * this_shares
        total_positions += current_total
        db.execute("UPDATE id? SET current_price=?, current_total=? WHERE symbol=?",
                   session["user_id"], usd(current_price), usd(current_total), this_symbol)

    positions = db.execute(
        "SELECT DISTINCT symbol, name, SUM(shares), current_price, current_total FROM id? GROUP BY symbol, name HAVING SUM(shares)>0", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])[0]["cash"]
    total = total_positions + cash

    return render_template("index.html", positions=positions, cash=usd(cash), total=usd(total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Set variables
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Query available cash of user
        cash = float(db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])[0]["cash"])

        # If there is no input in symbol, print apology
        if not symbol:
            return apology("missing symbol", 400)

        # Else if there is no input in shares, print apology
        elif not shares:
            return apology("missing shares", 400)

        # Else if there is no input in shares, print apology
        elif shares.isdigit() == False:
            return apology("shares not positive integers", 400)

        # Else if symbol is not valid, print apology
        elif lookup(symbol) == None:
            return apology("invalid symbol", 400)

        # Else if price of shares exceeds cash of user, print apology
        elif (lookup(symbol)["price"] * int(shares)) > cash:
            return apology("can't afford", 400)

        # Else
        else:

            # Get current price of share
            price = lookup(symbol)["price"]

            # Calculate the total price
            total = price * int(shares)

            # Get the name
            name = lookup(symbol)["name"]

            # Get time and date informations
            timezone_offset = 2.0
            tzinfo = timezone(timedelta(hours=timezone_offset))
            timestamp = datetime.now(tzinfo).strftime("%Y-%m-%d %H:%M:%S")

            # Insert all details of transaction into the database
            db.execute("INSERT INTO id? (symbol, name, shares, price, total, datetime, current_price, current_total) VALUES (?, ?, ?, ?, ?, ?, ?, ?)",
                       session["user_id"], symbol.upper(), name, int(shares), usd(price), total, timestamp, price, total)

            # Calculate remaining cash
            rest = cash - total

            # Insert amount of remaining cash in the database
            db.execute("UPDATE users SET cash=? WHERE id=?", rest, session["user_id"])

            # Flash "Bought!" message on screen and redirect to index page
            flash('Bought!')
            return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Query database for bought and sold positions of current user
    positions = db.execute("SELECT symbol, shares, price, datetime FROM id?", session["user_id"])

    # Show query as history
    return render_template("history.html", positions=positions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Set symbol input as variable
        symbol = request.form.get("symbol")

        # If there is no input in symbol, print apology
        if not symbol:
            return apology("missing symbol", 400)

        # Else if symbol is not valid, print apology
        elif lookup(symbol) == None:
            return apology("invalid symbol", 400)

        # Else print the current price of share
        else:
            return render_template("quoted.html", symbol=lookup(symbol), price=usd(lookup(symbol)["price"]))

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    session.clear()

    if request.method == "POST":

        if not request.form.get("username"):
            return apology("must provide username", 400)

        elif not request.form.get("password"):
            return apology("must provide password", 400)

        elif not request.form.get("confirmation"):
            return apology("must confirm password", 400)

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        if len(rows) == 1:
            return apology("username already taken", 400)

        if request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords don't match", 400)

        hash = generate_password_hash(request.form.get("password"))

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get("username"), hash)

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        session["user_id"] = rows[0]["id"]

        db.execute(
            "CREATE TABLE IF NOT EXISTS id? (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, symbol TEXT NOT NULL, name TEXT NOT NULL, shares NUMERIC NOT NULL, price DECIMAL, total DECIMAL, datetime DATETIME, current_price DECIMAL, current_total DECIMAL)", session["user_id"])

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/account", methods=["GET", "POST"])
@login_required
def account():
    if request.method == "POST":

        hash = db.execute("SELECT hash FROM users WHERE id = ?", session["user_id"])

        if not request.form.get("old"):
            return apology("must provide password", 403)

        elif not request.form.get("new"):
            return apology("must provide password", 403)

        elif not request.form.get("new_confirmation"):
            return apology("must confirm password", 403)

        elif not check_password_hash(hash[0]["hash"], request.form.get("old")):
            return apology("old password invalid", 403)

        elif request.form.get("new") != request.form.get("new_confirmation"):
            return apology("passwords don't match", 400)

        elif request.form.get("new") == request.form.get("old"):
            return apology("old & new passwords are the same", 400)

        hashed = generate_password_hash(request.form.get("new_confirmation"))

        db.execute("UPDATE users SET hash=? WHERE id=?", hashed, session["user_id"])

        flash('New Password set!')
        return render_template("account.html")

    else:
        return render_template("account.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    positions = db.execute("SELECT DISTINCT symbol, SUM(shares) FROM id? GROUP BY symbol HAVING SUM(shares)>0", session["user_id"])
    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        selected_position = db.execute("SELECT DISTINCT symbol, SUM(shares) FROM id? WHERE symbol=?", session["user_id"], symbol)

        if not symbol:
            return apology("missing symbol", 400)

        elif not shares:
            return apology("missing shares", 400)

        elif int(shares) > int(selected_position[0]["SUM(shares)"]):
            return apology("too many shares", 400)

        else:
            price = lookup(symbol)["price"]
            total = price * int(shares)
            name = lookup(symbol)["name"]
            timezone_offset = 2.0
            tzinfo = timezone(timedelta(hours=timezone_offset))
            timestamp = datetime.now(tzinfo).strftime("%Y-%m-%d %H:%M:%S")
            cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])[0]["cash"]
            db.execute("INSERT INTO id? (symbol, name, shares, price, total, datetime, current_price, current_total) VALUES (?, ?, ?, ?, ?, ?, ?, ?)",
                       session["user_id"], symbol.upper(), name, (int(shares)-(int(shares)*2)), usd(price), total, timestamp, price, total)
            rest = cash + total
            db.execute("UPDATE users SET cash=? WHERE id=?", rest, session["user_id"])

            flash('Sold!')
            return redirect("/")

    else:
        return render_template("sell.html", positions=positions)
