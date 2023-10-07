import sys
sys.path.append("./build")
import demo

def func():
    print("update UI")

demo.set_py_callback(func)
demo.call_func()