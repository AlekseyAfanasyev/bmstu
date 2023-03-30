from fib import fib

from flask import Flask

app = Flask(__name__)

@app.route("/")
def hello_world():
    return "<p>Write number of fibonachi numbers you want to be computed after the / symbol</p>"

@app.route("/<int:n>")
def fibonachi_number(n):
    fib_gen = fib()
    fib_numbers = []
    for i in range(n):
        fib_numbers.append(next(fib_gen))
    return fib_numbers