import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

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

# set datetime object containing current time and date
now = datetime.now()


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    """Show portfolio of stocks"""
    if request.method == "POST":
        if float(request.form.get("cash")) > 0.0:
            total = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]['cash']
            cash = float(request.form.get("cash"))
            total += cash
            db.execute("UPDATE users SET cash = ? WHERE id = ?", total, session["user_id"])
            return redirect("/")

    owns = own_shares()
    total = 0
    for stock, amount in owns.items():
        result = lookup(stock)
        price = result["price"]
        stock_value = amount * price
        total += stock_value
        owns[stock] = (amount, usd(price), usd(stock_value))
    cash = db.execute("SELECT cash FROM users WHERE id = ? ", session["user_id"])[0]['cash']
    total += cash
    return render_template("index.html", owns=owns, cash=usd(cash), total=usd(total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if lookup(request.form.get("symbol")) == None:
            return apology("Incorrect Symbol")
        result = lookup(request.form.get("symbol"))
        if not result:
            return render_template("purchase.html", invalid=True, symbol=request.form.get("symbol"))

        price = result["price"]
        symbol = result["symbol"]
        try:
            if int(request.form.get("shares")) > 0:
                shares = int(request.form.get("shares"))
            else:
                return apology("not proper int")
        except:
            return apology("not an int")
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session['user_id'])[0]['cash']
        remain = cash - price * shares
        if remain < 0:
            return apology("Insufficient Cash. Failed Purchase.")

        db.execute("UPDATE users SET cash = ? WHERE id = ?", remain, session['user_id'])
        dt_string = now.strftime("%d/%m/%Y %H:%M:%S")
        db.execute("INSERT INTO transactions (trans_type, stock, amount, price, time, user_id) VALUES (?, ?, ?, ?, ?, ?)",
                   "buy", symbol, shares, price, dt_string, session['user_id'])

        return redirect("/")
    return render_template("purchase.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT stock, amount, price, time FROM transactions WHERE user_id = ?", session["user_id"])
    return render_template("history.html", rows=rows)


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
    if request.method == "POST":
        if lookup(request.form.get("symbol")) != None:
            sym = lookup(request.form.get("symbol"))
            return render_template("quoted.html", sym=sym)
        else:
            return apology("Incorrect Symbol")
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")

    username = request.form.get("username")
    password = request.form.get("password")
    confirmation = request.form.get("confirmation")

    if username == "" or len(db.execute('SELECT username FROM users WHERE username = ?', username)) > 0:
        return apology("Invalid User")
    if password == "" or password != confirmation:
        return apology("Invalid Pass")
    db.execute('INSERT INTO users (username, hash) \
            VALUES(?, ?)', username, generate_password_hash(password))

    rows = db.execute("SELECT * FROM users WHERE username = ?", username)

    session["user_id"] = rows[0]["id"]

    return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    owns = own_shares()
    if request.method == "GET":
        return render_template("sell.html", owns=owns.keys())

    stock = request.form.get("symbol")
    try:
        if int(request.form.get("shares")) > 0:
            amount = int(request.form.get("shares"))
    except:
        return apology("Invalid amount")

    if owns[stock] < amount:
        return apology("Invalid amount")

    result = lookup(stock)
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session['user_id'])[0]['cash']
    price = result["price"]
    remain = cash + price * amount
    db.execute("UPDATE users SET cash = ? WHERE id = ?", remain, session['user_id'])
    dt_string = now.strftime("%d/%m/%Y %H:%M:%S")
    db.execute("INSERT INTO transactions (trans_type, stock, price, amount, time, user_id) VALUES ('sell', ?, ?, ?, ?, ?)",
               stock, price, -amount, dt_string, session["user_id"])

    return redirect("/")


def own_shares():
    """Return a dictionary {symbol: quantity} of Which stocks, and how many owned."""
    owns = {}
    trans = db.execute("SELECT stock, amount FROM transactions WHERE user_id = ?", session['user_id'])
    for q in trans:
        stock, amount = q["stock"], q["amount"]
        owns[stock] = owns.setdefault(stock, 0) + amount
    # Filter out 0 amounts
    owns = {k: v for k, v in owns.items() if v != 0}
    return owns