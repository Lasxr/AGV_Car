import paho.mqtt.client as mqtt
import json

def on_message(client,userdata,msg) :
    print(f"Received on topic {msg.topic}")
    try:
        data = json.loads(msg.payload.decode())
        for cell,walls in data.items():
            print(f"Cell {cell} has walls: {', ' . join(walls)}")
    except json.JSONDecodeError:
        print("Received non-JSON data : " , msg.payload.decode())        
        
client = mqtt.Client()
client.on_message = on_message

broker_address = "192.168.100.8"
broker_port = 1883
topic = "Network/Python/Car"

client.connect(broker_address,broker_port, 60)
client.subscribe(topic)
client.loop_forever()