import paho.mqtt.client as mqtt
import json

field_data ={
    "a" : ["u", "d", "l"],
    "b" : ["u", "d"],
    "c" : ["u", "r"]
}

payload = json.dumps(field_data)
broker_address = "192.168.100.8"
broker_port = 1883
topic = "Topic/python/Test"

client = mqtt.Client()
client.connect(broker_address, 1883 , 60)
client.publish(topic, payload)
client.disconnect()