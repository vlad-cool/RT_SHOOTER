#!venv/bin/python3
import random
import json
import os

script_dir = os.path.dirname(os.path.abspath(__file__))
os.chdir(os.path.join(script_dir, "..", "src/assets"))


from flask import Flask, render_template, send_file
print(f"Current directory: {os.getcwd()}")

x = 1920 // 2
y = 1080 // 2
shoot = False

app = Flask(__name__)

app.template_folder = os.path.join(os.getcwd(), "templates")

@app.route('/')
def index():
    return render_template("responce.html")

@app.route("/js/responce.js")
def send_script():
    return send_file(os.path.join(os.getcwd(), "js/responce.js"))

@app.route("/img/<image>")
def get_image(image):
    return send_file(os.path.join(os.getcwd(), f"img/{image}"))

@app.route('/get_data')
def data():
    global x, y, shoot
    # x += random.randint(-32, 32)
    # y += random.randint(-32, 32)
    x = max(0, x)
    x = min(x, 1920 - 1)
    y = max(0, y)
    y = min(y, 720 - 1)
    a = {"x": x, "y": y, "press": 1 if shoot else 0, "hold": 0}
    return json.dumps(a)

@app.route("/control")
def control():
    return render_template("control.html")

@app.route("/control/<cmd>")
def set_data(cmd):
    global x, y, shoot
    STEP = 20
    match cmd:
        case "l":
            x -= STEP
        case "r":
            x += STEP
        case "t":
            y -= STEP
        case "b":
            y += STEP
        case "s":
            shoot = True
    return "Ok"

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)