from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from functools import wraps
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime, timezone, timedelta

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///bdi.db")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


def login_required(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/register", methods=["GET", "POST"])
def register():

    session.clear()

    if request.method == "POST":

        if not request.form.get("role"):
            flash("Missing role!")
            return render_template("register.html")

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        if len(rows) == 1:
            flash("Username already taken!")
            return render_template("register.html")
        
        if request.form.get("password") != request.form.get("confirmation"):
            flash("Passwords don't match!")
            return render_template("register.html")

        hash = generate_password_hash(request.form.get("password"))
        db.execute("INSERT INTO users (username, hash, role) VALUES (?, ?, ?)", request.form.get("username"), hash, request.form.get("role"))
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        session["user_id"] = rows[0]["id"]

        #db.execute("CREATE TABLE IF NOT EXISTS id? (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, symbol TEXT NOT NULL, name TEXT NOT NULL, shares NUMERIC NOT NULL, price DECIMAL, total DECIMAL, datetime DATETIME, current_price DECIMAL, current_total DECIMAL)", session["user_id"])

        role = db.execute("SELECT role FROM users WHERE id=?", session["user_id"])[0]["role"]

        if role == "Therapist":
            flash('Registered!')
            return redirect("/home_therapist")

        else:
            flash('Registered!')
            return redirect("/home_patient")
    
    else:
        return render_template("register.html")


@app.route("/login", methods=["GET", "POST"])
def login():

    session.clear()

    if request.method == "POST":

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            flash("Invalid username and/or password!")
            return render_template("login.html")

        session["user_id"] = rows[0]["id"]

        role = db.execute("SELECT role FROM users WHERE id=?", session["user_id"])[0]["role"]

        if role == str("Therapist"):
            return redirect("/home_therapist")

        else:
            return redirect("/home_patient")

    else:
        return render_template("login.html")


@app.route("/logout")
def logout():

    session.clear()
    return redirect("/")


@app.route("/account_patient")
@login_required
def account_patient():

    username = db.execute("SELECT username FROM users WHERE id=?", session["user_id"])
    role = db.execute("SELECT role FROM users WHERE id=?", session["user_id"])
    return render_template("account_patient.html", username=username, role=role)


@app.route("/account_therapist")
@login_required
def account_therapist():

    username = db.execute("SELECT username FROM users WHERE id=?", session["user_id"])
    role = db.execute("SELECT role FROM users WHERE id=?", session["user_id"])
    return render_template("account_therapist.html", username=username, role=role)


@app.route("/home_therapist")
@login_required
def home_therapist():
    return render_template("home_therapist.html")


@app.route("/home_patient")
@login_required
def home_patient():

    test = db.execute("SELECT test FROM users WHERE id=?", session["user_id"])[0]["test"]

    if test == 1:
        return redirect("/test")

    else:
        return render_template("home_patient.html")


@app.route("/test", methods=["GET", "POST"])
@login_required
def test():

    if request.method =="POST":

        question_1 = int(request.form.get("question_1"))
        question_2 = int(request.form.get("question_2"))
        question_3 = int(request.form.get("question_3"))
        question_4 = int(request.form.get("question_4"))
        question_5 = int(request.form.get("question_5"))
        question_6 = int(request.form.get("question_6"))
        question_7 = int(request.form.get("question_7"))
        question_8 = int(request.form.get("question_8"))
        question_9 = int(request.form.get("question_9"))
        question_10 = int(request.form.get("question_10"))
        question_11 = int(request.form.get("question_11"))
        question_12 = int(request.form.get("question_12"))
        question_13 = int(request.form.get("question_13"))
        question_14 = int(request.form.get("question_14"))
        question_15 = int(request.form.get("question_15"))
        question_16 = int(request.form.get("question_16"))
        question_17 = int(request.form.get("question_17"))
        question_18 = int(request.form.get("question_18"))
        question_19 = int(request.form.get("question_19"))
        question_20 = int(request.form.get("question_20"))
        question_21 = int(request.form.get("question_21"))

        total_points = question_1 + question_2 + question_3 + question_4 + question_5 + question_6 + question_7 + question_8 + question_9 + question_10 + question_11 + question_12 + question_13 + question_14 + question_15 + question_16 + question_17 + question_18 + question_19 + question_20 + question_21
        
        timezone_offset = 2.0
        tzinfo = timezone(timedelta(hours=timezone_offset))
        timestamp = datetime.now(tzinfo).strftime("%Y-%m-%d %H:%M:%S")

        patient = db.execute("SELECT username FROM users WHERE id=?", session["user_id"])[0]["username"]

        db.execute("UPDATE users SET test=0 WHERE id=?", session["user_id"])

        db.execute("UPDATE tests SET sent=?, score=? WHERE patient=? AND score IS NULL", timestamp, total_points, patient)

        flash('BDI-II sent!')
        return redirect("/home_patient")

    else:
        return render_template("test.html")


@app.route("/send", methods=["GET", "POST"])
@login_required
def send():

    patients = db.execute("SELECT username FROM users WHERE role='Patient'")

    if request.method == "POST":

        patient = request.form.get("patient")
        therapist = db.execute("SELECT username FROM users WHERE id=?", session["user_id"])[0]["username"]

        if not patient:
            flash("Select patient!")
            return redirect("/send")
        
        else:
            timezone_offset = 2.0
            tzinfo = timezone(timedelta(hours=timezone_offset))
            timestamp = datetime.now(tzinfo).strftime("%Y-%m-%d %H:%M:%S")

            test_stat = db.execute("SELECT test FROM users WHERE username=?", patient)[0]["test"]

            if test_stat == 0:

                db.execute("INSERT INTO tests (patient, therapist, created) VALUES (?, ?, ?)", patient, therapist, timestamp)
                db.execute("UPDATE users SET test=1 WHERE username=?", patient)

                flash('BDI-II sent!')
                return redirect("/send")

            else:

                flash('Patient already received a test!')
                return redirect("/send")

    else:
        return render_template("send.html", patients=patients)


@app.route("/history_patient")
@login_required
def history_patient():

    patient = db.execute("SELECT username FROM users WHERE id=?", session["user_id"])[0]["username"]
    tests = db.execute("SELECT * FROM tests WHERE patient=?", patient)

    return render_template("history_patient.html", tests=tests)


@app.route("/history_therapist")
@login_required
def history_therapist():

    therapist = db.execute("SELECT username FROM users WHERE id=?", session["user_id"])[0]["username"]
    tests = db.execute("SELECT * FROM tests WHERE therapist=?", therapist)

    return render_template("history_therapist.html", tests=tests)


@app.route("/results", methods=["GET", "POST"])
@login_required
def results():

    patients = db.execute("SELECT username FROM users WHERE role='Patient'")

    if request.method == "POST":

        patient = request.form.get("patient")

        if not patient:
            flash("Select patient!")
            return redirect("/results")
        
        else:

            sent_dict = db.execute("SELECT sent FROM tests WHERE patient=? AND sent IS NOT NULL", patient)
            sent_elements = len(sent_dict)

            sent = []

            for i in range(sent_elements):
                sent.append(db.execute("SELECT sent FROM tests WHERE patient=? AND score IS NOT NULL", patient)[i]["sent"])


            scores_dict = db.execute("SELECT score FROM tests WHERE patient=? AND score IS NOT NULL", patient)
            scores_elements = len(scores_dict)

            scores = []

            for i in range(scores_elements):
                scores.append(db.execute("SELECT score FROM tests WHERE patient=? AND score IS NOT NULL", patient)[i]["score"])

            return render_template("result.html", patient=patient, sent=sent, scores=scores)

    else:
        return render_template("results.html", patients=patients)