import socket
import subprocess
import time
import struct
import threading

# Shared variable to store the angle
shared_angle = None

# Lock to synchronize access to the shared angle
angle_lock = threading.Lock()

def run_cpp_executable():
    # Start the C++ executable
    process = subprocess.Popen(['./hough_socket'])
    return process

def receive_angles():
    global shared_angle
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Attempt to connect to the C++ server
    while True:
        try:
            client_socket.connect(('localhost', 8080))
            break
        except ConnectionRefusedError:
            time.sleep(1)  # Wait a bit before trying again

    try:
        while True:
            data = client_socket.recv(8)  # Receiving 8 bytes for a double
            if not data:
                break
            angle = struct.unpack('f', data)[0]
            
            # Update the shared angle with the new value
            with angle_lock:
                shared_angle = angle
            print(f"Received angle: {angle}")

    except KeyboardInterrupt:
        print("Stopping client.")
    finally:
        client_socket.close()

def main_control_loop():
    global shared_angle
    while True:
        # Perform main control loop operations
        with angle_lock:
            angle = shared_angle
        if angle is not None:
            print(f"Using angle in control loop: {angle}")
        
        # Simulate control loop work (faster than the angle update rate)
        time.sleep(0.1)  # Adjust this delay as needed

if __name__ == "__main__":
    # Run the C++ executable
    cpp_process = run_cpp_executable()

    # Allow some time for the server to start up
    time.sleep(2)

    # Start the angle receiving thread
    angle_thread = threading.Thread(target=receive_angles)
    angle_thread.start()

    # Start the main control loop
    try:
        main_control_loop()
    except KeyboardInterrupt:
        print("Stopping main control loop.")
    finally:
        # Terminate the C++ process and wait for the thread to finish
        cpp_process.terminate()
        cpp_process.wait()
        angle_thread.join()
